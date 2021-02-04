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
    SimpleScreen *screen = new SimpleScreen(this);
    connect(screen, SIGNAL(authenticate(const std::string &, const std::string &)), this, SIGNAL(authenticate(const std::string &, const std::string &)));

    layout()->addWidget(screen);
}

const QString Screen::username() const
{
    return m_username.text();
}

const QString Screen::password() const
{
    return m_password.text();
}

const QString Screen::session() const
{
    return "mere-session";
}

void Screen::loginFailed()
{
    QMessageBox::information(
        this,
        tr("Application Name"),
        tr("An information message.") );
}

