#ifndef MERE_DISPLAY_APP_H
#define MERE_DISPLAY_APP_H

#include "win.h"
#include "mere/widgets/defaultapp.h"

class App : public Mere::DefaultApp
{
    Q_OBJECT
public:
    ~App();
    explicit App(int &argc, char **argv);
    void init();
    void start();
    void stop();

private:
    Win *m_win;
};

#endif // MERE_DISPLAY_APP_H
