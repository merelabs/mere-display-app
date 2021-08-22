#include "displayapp.h"
#include "passer.h"
#include "theme.h"

#include "mere/utils/apputils.h"
#include "mere/utils/i18nutils.h"

#include <QScreen>
#include <QCommandLineParser>

DisplayApp::~DisplayApp()
{
    if(m_passer)
    {
        delete m_passer;
        m_passer = nullptr;
    }
}

DisplayApp::DisplayApp(int &argc, char **argv)
    : Mere::Widgets::DefaultApp(argc, argv)
{
    setObjectName("LockDisplay");

    setAppCode(Mere::Display::AppCode.toStdString());
    setApplicationName(Mere::Display::AppName);
    setApplicationVersion(Mere::Display::AppVersion);

    Mere::Utils::I18nUtils::apply();

    QCommandLineParser parser;
    parser.setApplicationDescription(QCoreApplication::translate("DisplayApp", "DisplayAppDescription"));
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption configOption(QStringList() << "c" << "config", QCoreApplication::translate("DisplayArg", "DisplayArgConfig"),
                                    "path",
                                    "mere/display.conf");

    QCommandLineOption strictOption("strict", QCoreApplication::translate("DisplayArg", "DisplayArgStrict"));


    parser.addOptions({configOption, strictOption});

    parser.process(QCoreApplication::arguments());

    m_config = Config::instance(parser.value(configOption).toStdString(),
                                            parser.isSet(strictOption)
                                                ? Mere::Config::Spec::Strict::Hard
                                                : Mere::Config::Spec::Strict::Soft);
    std::cout << DisplayApp::tr("DisplayConfigApply").toStdString() << "\n - " << m_config->path() << std::endl;

    try
    {
        m_config->load();
    }
    catch (const std::exception &ex)
    {
        std::cout << DisplayApp::tr("DisplayConfigLoadFailed").toStdString() << "\n - " << m_config->path() << std::endl;
        std::exit(1);
    }

    if (parser.isSet(strictOption) && m_config->validate())
    {
        std::cout << DisplayApp::tr("DisplayConfigValidCheckFailed").toStdString() << "\n - " << m_config->path() << std::endl;
        std::exit(1);
    }

    m_passer = new Passer(this);
    connect(m_passer, &Passer::passed, [&](){
        quit();
    });
}

int DisplayApp::init()
{
    Mere::Widgets::DefaultApp::init();

    return 0;
}

int DisplayApp::start()
{
    m_passer->pass();

    return 0;
}

int DisplayApp::stop()
{
    return 0;
}
