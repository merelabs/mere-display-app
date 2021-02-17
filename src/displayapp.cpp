#include "displayapp.h"

#include "mere/utils/apputils.h"
#include "mere/utils/i18nutils.h"

#include <QScreen>

DisplayApp::~DisplayApp()
{
    if(m_win)
    {
        delete m_win;
        m_win = nullptr;
    }
}

DisplayApp::DisplayApp(int &argc, char **argv)
    : Mere::DefaultApp(argc, argv)
{
    Mere::Utils::AppUtils::setAppCode("display");

    setAppCode("display");
    setApplicationName("display");

    Mere::Utils::I18nUtils::apply();

    m_win = new DisplayWin();
}

void DisplayApp::init()
{
    Mere::DefaultApp::init();
}

void DisplayApp::start()
{
    // hanlde primary screen change
    QScreen *screen = QGuiApplication::primaryScreen();
    m_win->setGeometry(screen->geometry());
    m_win->show();
}

void DisplayApp::stop()
{

}
