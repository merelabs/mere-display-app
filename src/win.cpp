#include "win.h"

#include <QVBoxLayout>
Win::Win(QWidget *parent) : QWidget(parent)
{
    qDebug() << "???????????????????";
    setLayout(new QVBoxLayout);

    m_screen = new Screen;
    connect(m_screen, SIGNAL(authenticate(const std::string &, const std::string &)), this, SLOT(authenticate(const std::string &, const std::string &)));

    this->layout()->addWidget(m_screen);

    m_client = new Client();
    connect(m_client, SIGNAL(loginFailed()), m_screen, SLOT(loginFailed()));
}

void Win::authenticate(const std::string &username, const std::string &password) const
{
    qDebug() << "AUTHENTICATE?";
    m_client->authenticate(username, password);
}
