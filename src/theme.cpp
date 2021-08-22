#include "theme.h"
#include "themes/simple/simplescreen.h"

#include <QScreen>
#include <QVBoxLayout>

Theme::~Theme()
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

Theme::Theme(QScreen *screen, QWidget *parent)
    : QWidget(parent)
{
    setObjectName("MereDisplayWin");
    resize(screen->availableGeometry().size());

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(15, 15, 15, 15);
    setLayout(layout);

    m_screen = new SimpleScreen();
    connect(m_screen, SIGNAL(authenticate(const std::string &, const std::string &)), this, SLOT(authenticate(const std::string &, const std::string &)));
    connect(m_screen, SIGNAL(reboot(int)), this, SLOT(reboot(int)));
    connect(m_screen, SIGNAL(shutdown(int)), this, SLOT(shutdown(int)));

    layout->addWidget(m_screen);

    m_client = new Client();
    connect(m_client, SIGNAL(action(bool, const std::string &)), m_screen, SLOT(action(bool, const std::string &)));
}

void Theme::authenticate(const std::string &username, const std::string &password) const
{
    m_client->authenticate(username, password);
}

void Theme::reboot(int time)
{
    m_client->reboot(time);
}

void Theme::shutdown(int time)
{
    m_client->shutdown(time);
}
