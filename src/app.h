#ifndef MEREDISPLAYAPP_H
#define MEREDISPLAYAPP_H

#include "win.h"

#include "mere/widgets/defaultapp.h"
#include "mere/display/meredisplaymanager.h"
#include "mere/display/meredisplayprompt.h"

namespace Mere
{
    namespace Sticky
    {
        #ifdef APP_CODE
        const QString AppCode   = APP_CODE;
        #else
        const QString AppCode   = "display";
        #endif

        #ifdef APP_NAME
        const QString AppName   = APP_NAME;
        #else
        const QString AppName   = "mere-display";
        #endif

        #ifdef APP_VERSION
        const QString AppVersion= APP_VERSION;
        #else
        const QString AppVersion= "0.0.0b";
        #endif
    }
}

class MereDisplayServer;
//class MereDisplayManager;
//class MereDisplayPrompt;

class App : public QApplication
{
    Q_OBJECT
public:
    explicit App(int &argc, char **argv);
    void init();
    void start();
    void stop();

signals:

private slots:
    void serverReady(MereDisplayServer *server);

private:
    Win *m_win;

//    Mere::Display::MereDisplayManager *m_display;
//    Mere::Display::MereDisplayPrompt *m_prompt;
};

#endif // MEREDISPLAYAPP_H
