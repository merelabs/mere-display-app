#ifndef MERE_DISPLAY_APP_H
#define MERE_DISPLAY_APP_H

#include "displaywin.h"
#include "mere/widgets/defaultapp.h"

class DisplayApp : public Mere::DefaultApp
{
    Q_OBJECT
public:
    ~DisplayApp();
    explicit DisplayApp(int &argc, char **argv);
    void init();
    void start();
    void stop();

private:
    DisplayWin *m_win;
};

#endif // MERE_DISPLAY_APP_H
