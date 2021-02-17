#include "displaywin.h"

#include <QVBoxLayout>

DisplayWin::~DisplayWin()
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

DisplayWin::DisplayWin(QWidget *parent) : QWidget(parent)
{
    setObjectName("MereDisplayWin");
    setLayout(new QVBoxLayout);

    m_screen = new Screen();
    connect(m_screen, SIGNAL(authenticate(const std::string &, const std::string &)), this, SLOT(authenticate(const std::string &, const std::string &)));
    connect(m_screen, SIGNAL(reboot(int)), this, SLOT(reboot(int)));
    connect(m_screen, SIGNAL(shutdown(int)), this, SLOT(shutdown(int)));

    this->layout()->addWidget(m_screen);

    m_client = new Client();
    connect(m_client, SIGNAL(action(bool, const std::string &)), m_screen, SLOT(action(bool, const std::string &)));
}

void DisplayWin::authenticate(const std::string &username, const std::string &password) const
{
    m_client->authenticate(username, password);
}

void DisplayWin::reboot(int time)
{
    m_client->reboot(time);
}

void DisplayWin::shutdown(int time)
{
    m_client->shutdown(time);
}
