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

    this->layout()->addWidget(m_screen);

    m_client = new Client();
    connect(m_client, SIGNAL(loginFailed()), m_screen, SLOT(loginFailed()));
}

void Win::authenticate(const std::string &username, const std::string &password) const
{
    m_client->authenticate(username, password);
}
