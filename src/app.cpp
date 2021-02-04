#include "app.h"

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
    m_win->showFullScreen();
}

void App::stop()
{

}
