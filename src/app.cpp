#include "app.h"

#include <QScreen>

App::~App()
{
    if(m_win)
    {
        delete m_win;
        m_win = nullptr;
    }
}

App::App(int &argc, char **argv)
    : Mere::DefaultApp(argc, argv)
{
    setAppCode("display");
    setApplicationName("display");
    m_win = new Win();
}

void App::init()
{
    Mere::DefaultApp::init();
}

void App::start()
{
    // hanlde primary screen change
    QScreen *screen = QGuiApplication::primaryScreen();
    m_win->setGeometry(screen->geometry());
    m_win->show();
}

void App::stop()
{

}
