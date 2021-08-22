#include "simplescreen.h"
#include "promptscreen.h"
#include "clockview.h"
#include "actionview.h"
#include "sessionview.h"

#include <QLabel>
#include <QDateTime>
#include <QScreen>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
SimpleScreen::SimpleScreen(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("SimpleScreen");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    initUI();
}

void SimpleScreen::initUI()
{
    initHeaderUI();
    initContentUI();
    initFooterUI();
}

void SimpleScreen::initHeaderUI()
{
    QHBoxLayout *hLayout = new QHBoxLayout();

    QWidget *header = new QWidget(this);
    header->setLayout(hLayout);
    header->setMaximumHeight(64);
    layout()->addWidget(header);

    ClockView *timerLabel = new ClockView(this);
    hLayout->addWidget(timerLabel);
}

void SimpleScreen::initContentUI()
{
    QSpacerItem *spacer1 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout()->addItem(spacer1);

    QWidget *prompt = new PromptScreen(this);
    connect(prompt, SIGNAL(authenticate(const std::string &, const std::string &)), this, SIGNAL(authenticate(const std::string &, const std::string &)));
    layout()->addWidget(prompt);

    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    layout()->addItem(spacer);

    QWidget *session = new SessionView(this);
    layout()->addWidget(session);
}

void SimpleScreen::initFooterUI()
{
    ActionView *action = new ActionView(this);
    connect(action, &ActionView::reboot, [=](){emit reboot(-1);});
    connect(action, &ActionView::shutdown, [=](){ emit shutdown(-1);});

    layout()->addWidget(action);
}

void SimpleScreen::action(bool ok, const std::string &message)
{
    setErrorMessage(QString::fromStdString(message));
}

void SimpleScreen::setErrorMessage(const QString &message)
{
    QLabel *errorMessage = this->findChild<QLabel* >("SimpleScreenFormError");
    errorMessage->setText(message);
}

void SimpleScreen::setTipOfTheDay(const QString &tip)
{

}
