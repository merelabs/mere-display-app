#include "app.h"
#include "screen.h"

#include "mere/display/meredisplaymanager.h"

#include <unistd.h>
#include <QCommandLineParser>

App::App(int &argc, char **argv)
    : QApplication(argc, argv)/*,

//      m_display(nullptr)*/
{
    setObjectName("MereDisplayApp");
//    setAppCode(Mere::Sticky::AppCode);
    setApplicationName(Mere::Sticky::AppName);
    setApplicationVersion(Mere::Sticky::AppVersion);

//    QCommandLineParser parser;
//    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsCompactedShortOptions);
//    parser.setApplicationDescription("Description: Mere Display Manager");
//    parser.addHelpOption();
//    parser.addVersionOption();

//    parser.addOptions({
//        {"d",
//            QApplication::translate("main", "Run display manager as daemon")},
//        {{"c", "config"},
//            QApplication::translate("main", "Configuration file to use"),
//            QApplication::translate("main", "file")},
//        {{"s", "session"},
//            QApplication::translate("main", "X Session to use"),
//            QApplication::translate("main", "session")}
//    });

//    parser.process(*this);
//    if (parser.isSet("config"))
//    {
//        // validate if this a valid file.
//    }

//    // check if its running by root/menshen
//    uid_t uid = getuid();
//    if (uid != 0)
//    {
//        qCritical() << "menshen needs to be run by root user.";
//        std::exit(1);
//    }

    m_win = new Win();

    qDebug() << "KI OBOSTHA?";
}

void App::init()
{
//    MereDefaultApp::init();

    qDebug() << "KI BOLE?";
//    m_prompt = new MereDisplayScreen();

//    m_display = new Mere::Display::MereDisplayManager(this);
//    m_display->registerUI(m_prompt);

//    connect(m_display, SIGNAL(ready(MereDisplayServer *)), this, SLOT(serverReady(MereDisplayServer *)));
}

void App::start()
{
//    if (m_display != NULL)
//        m_display->start();

    m_win->showFullScreen();
}

void App::stop()
{

}

void App::serverReady(MereDisplayServer *server)
{
    qDebug() << "YES DISPLAY SERVE READY! NOW SHOW LOGIN PROMPT";
}


