#ifndef MERE_DISPLAY_APP_H
#define MERE_DISPLAY_APP_H

#include "config.h"
#include "mere/widgets/defaultapp.h"

namespace Mere
{
    namespace Display
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

class Passer;
class Theme;

class DisplayApp : public Mere::Widgets::DefaultApp
{
    Q_OBJECT
public:
    ~DisplayApp();
    explicit DisplayApp(int &argc, char **argv);
    int init() override;
    int start();
    int stop();

private:
    Config *m_config;
    Passer *m_passer;
};

#endif // MERE_DISPLAY_APP_H
