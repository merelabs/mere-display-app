#include "simplescreen.h"

#include <QLabel>
#include <QDateTime>
#include <QPushButton>
#include <QVBoxLayout>

SimpleScreen::SimpleScreen(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("SimpleScreen");
    QVBoxLayout *layout = new QVBoxLayout();
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

    QLabel *timerLabel = new QLabel(this);
    timerLabel->setText(QDateTime::currentDateTime().toString());
    hLayout->addWidget(timerLabel);
}

void SimpleScreen::initContentUI()
{
    QWidget *content = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignCenter);
    content->setLayout(vLayout);
    layout()->addWidget(content);

    QWidget *logo = new QWidget();
    logo->setLayout(new QHBoxLayout);

    QLabel *osLabel = new QLabel(this);
    osLabel->setScaledContents(true);
    osLabel->setMaximumSize(QSize(96, 94));

    QPixmap pixmap(":/display/freebsd-logo.png");
    osLabel->setPixmap(pixmap);
    logo->layout()->addWidget(osLabel);

    vLayout->addWidget(logo);

    QWidget *loginForm = new QWidget(this);
    loginForm->setObjectName("SimpleScreenForm");
    loginForm->setMinimumSize(350, 150);
    loginForm->setMaximumSize(400, 200);

    loginForm->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    vLayout->addWidget(loginForm);


    QGridLayout *contentLayout = new QGridLayout(loginForm);
    contentLayout->setContentsMargins(50, 35, 50, 35);
    contentLayout->setRowMinimumHeight(2, 20);
    contentLayout->setHorizontalSpacing(15);
    contentLayout->setVerticalSpacing(10);

    QLabel *usernameLabel = new QLabel("Username");
    contentLayout->addWidget(usernameLabel, 0, 0);

    m_usernameEdit = new QLineEdit();
    contentLayout->addWidget(m_usernameEdit, 0, 1);

    QLabel *passwordLabel = new QLabel("Password");
    contentLayout->addWidget(passwordLabel, 1, 0);

    m_passwordEdit = new QLineEdit();
    m_passwordEdit->setObjectName("SimpleScreenFormPassword");
    m_passwordEdit->setEchoMode(QLineEdit::Password);
    contentLayout->addWidget(m_passwordEdit, 1, 1);

    QPushButton *loginButton = new QPushButton("Login");
    loginButton->setObjectName("SimpleScreenFormButton");
    contentLayout->addWidget(loginButton, 3, 0, 1, 2);

    loginForm->setLayout(contentLayout);

    connect(loginButton, SIGNAL(released()), this, SLOT(authenticate()));

    QLabel *actionLabel = new QLabel("");
    actionLabel->setObjectName("SimpleScreenFormError");
    actionLabel->setAlignment(Qt::AlignHCenter);
    vLayout->addWidget(actionLabel);
}

void SimpleScreen::initFooterUI()
{
    QHBoxLayout *hLayout = new QHBoxLayout();

    QWidget *footer = new QWidget(this);
    footer->setObjectName("footer");
    footer->setLayout(hLayout);
    footer->setMaximumHeight(75);
    layout()->addWidget(footer);

    QLabel *mereLabel = new QLabel(this);
    mereLabel->setScaledContents(true);
    mereLabel->setMaximumSize(QSize(128, 35));

    QPixmap pixmap(":/display/mere-logo.png");
    mereLabel->setPixmap(pixmap);

    hLayout->addWidget(mereLabel);

    QSpacerItem *hSpacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hLayout->addItem(hSpacer);

    QPushButton *rebootButton = new QPushButton(QIcon(":/display/reboot.png"), "Reboot", this);
    rebootButton->setFocusPolicy(Qt::NoFocus);
    rebootButton->setFlat(true);
    hLayout->addWidget(rebootButton);

    QFrame *vLine = new QFrame(this);
    vLine->setObjectName("verticleLine");
    vLine->setFrameShape(QFrame::VLine);
    vLine->setMaximumHeight(rebootButton->height());
    hLayout->addWidget(vLine);

    QPushButton *powerOffButton = new QPushButton(QIcon(":/display/poweroff.png"), "Power Off", this);
    powerOffButton->setFocusPolicy(Qt::NoFocus);
    powerOffButton->setFlat(true);

    hLayout->addWidget(powerOffButton);

    connect(rebootButton, SIGNAL(released()), this, SLOT(reboot()));
    connect(powerOffButton, SIGNAL(released()), this, SLOT(shutdown()));
}

void SimpleScreen::setErrorMessage(const QString &message)
{
    QLabel *errorMessage = this->findChild<QLabel* >("SimpleScreenFormError");
    errorMessage->setText(message);
}

void SimpleScreen::setTipOfTheDay(const QString &tip)
{

}

void SimpleScreen::authenticate()
{
    QLabel *errorMessage = this->findChild<QLabel* >("SimpleScreenFormError");
    errorMessage->setText("");

    const std::string &username = m_usernameEdit->text().toStdString();
    const std::string &password = m_passwordEdit->text().toStdString();
    emit authenticate(username, password);
}

void SimpleScreen::reboot()
{
    emit reboot(-1);
}

void SimpleScreen::shutdown()
{
    emit shutdown(-1);
}
