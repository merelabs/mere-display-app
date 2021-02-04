#include "win.h"

#include <QVBoxLayout>

Win::~Win()
{
    if (m_screen)
    {
        delete m_screen;
        m_screen = nullptr;
    }

    if (m_client)
    {
        delete m_client;
        m_client = nullptr;
    }
}

Win::Win(QWidget *parent) : QWidget(parent)
{
    setObjectName("MereDisplayWin");
    setLayout(new QVBoxLayout);

    m_screen = new Screen;
    connect(m_screen, SIGNAL(authenticate(const std::string &, const std::string &)), this, SLOT(authenticate(const std::string &, const std::string &)));
    connect(m_screen, SIGNAL(reboot(int)), this, SLOT(reboot(int)));
    connect(m_screen, SIGNAL(shutdown(int)), this, SLOT(shutdown(int)));

    this->layout()->addWidget(m_screen);

    m_client = new Client();
    connect(m_client, SIGNAL(action(bool, const std::string &)), m_screen, SLOT(action(bool, const std::string &)));
}

void Win::authenticate(const std::string &username, const std::string &password) const
{
    m_client->authenticate(username, password);
}

void Win::reboot(int time)
{
    m_client->reboot(time);
}

void Win::shutdown(int time)
{
    m_client->shutdown(time);
}
