#include "passer.h"
#include "screen.h"

#include <QApplication>
Passer::Passer(QObject *parent)
    : QObject(parent)
{
    for(QScreen *screen : QApplication::screens())
    {
        auto *s = new Screen(screen);
        connect(s, &Screen::passed, this, [&](){
            passed();
        });
        m_screens.push_back(s);
    }
}

int Passer::pass()
{
    for(auto *screen : m_screens)
        screen->pass();

    return 0;
}

