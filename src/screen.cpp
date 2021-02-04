#include "screen.h"
#include "simplescreen.h"

#include <QRect>
#include <QDesktopWidget>
#include <QApplication>
#include <QTextBrowser>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QTextBlock>
#include <QMessageBox>

Screen::~Screen()
{
}

Screen::Screen(QWidget *parent)
    : Prompt(parent)
{
    setObjectName(QString::fromUtf8("MereDisplayScreen"));

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    initUI();
}

void Screen::init()
{

}

void Screen::initUI()
{
    m_screen = new SimpleScreen(this);
    connect(m_screen, SIGNAL(authenticate(const std::string &, const std::string &)), this, SIGNAL(authenticate(const std::string &, const std::string &)));

    layout()->addWidget(m_screen);
}

const QString Screen::username() const
{
    return "";
}

const QString Screen::password() const
{
    return "";
}

const QString Screen::session() const
{
    return "mere-session";
}

void Screen::loginFailed()
{
    m_screen->setErrorMessage("Unable to authenticate!");
}

void Screen::authenticated(bool ok, const std::string &message)
{
    m_screen->setErrorMessage(QString::fromStdString(message));
}
