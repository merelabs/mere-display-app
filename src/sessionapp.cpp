#include "sessionapp.h"

#include <QScreen>

SessionApp::~SessionApp()
{
    if(m_win)
    {
        delete m_win;
        m_win = nullptr;
    }
}

SessionApp::SessionApp(int &argc, char **argv)
    : Mere::DefaultApp(argc, argv)
{
    setAppCode("display");
    setApplicationName("display");
    m_win = new Win();
}

void SessionApp::init()
{
    Mere::DefaultApp::init();
}

void SessionApp::start()
{
    // hanlde primary screen change
    QScreen *screen = QGuiApplication::primaryScreen();
    m_win->setGeometry(screen->geometry());
    m_win->show();
}

void SessionApp::stop()
{

}
