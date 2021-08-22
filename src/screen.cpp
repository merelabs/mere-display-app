#include "screen.h"
#include "theme.h"
#include "config.h"

#include "mere/utils/fileutils.h"
#include "mere/utils/stringutils.h"

#include <iostream>
#include <QLabel>
#include <QScreen>
#include <QWindow>
#include <QVBoxLayout>
#include <QApplication>
Screen::Screen(QScreen *screen, QWidget *parent)
    : QWidget(parent),
      m_screen(screen)
{
    setObjectName("DisplayScreen");

    //setWindowFlags (Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAutoFillBackground(true);

    initUI();

    if(screen == QApplication::primaryScreen())
        new Theme(screen, this);
}

void Screen::pass()
{
    showFullScreen();
    windowHandle()->setScreen(m_screen);
    setVisible(true);
}

void Screen::initUI()
{
    setBackground();
    setScreenLogo();
}

void Screen::setBackground()
{
    QPalette pal = palette();

    Config *config = Config::instance();

    QColor color = config->screenBackgroundColor();
    if (color.isValid())
        pal.setColor(QPalette::Window, color);

    QPixmap pixmap = config->screenBackgroundImage();
    if (!pixmap.isNull())
    {
        pixmap = pixmap.scaled(m_screen->availableVirtualSize(), Qt::IgnoreAspectRatio);
        pal.setBrush(QPalette::Window, pixmap);
    }

    setPalette(pal);
}

void Screen::setScreenLogo()
{
    Config *config = Config::instance();
    if(!config->logoshow()) return;

    QString logo(config->logo().c_str());
    if (logo.isEmpty()) return;

    QPixmap pixmap(logo);
    if (pixmap.isNull())
    {
        std::cout << "Unable to create image for screen logo; please check the image path." << logo.toStdString() << std::endl;
        return;
    }

    QLabel *label = new QLabel(this);
    label->setScaledContents(true);
    label->setMaximumSize(QSize(128, 35));
    label->setPixmap(pixmap);

    QSize size = m_screen->availableVirtualSize();

    label->move(25, size.height() - label->height() - 25);
}
