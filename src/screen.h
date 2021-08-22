#ifndef DISPLAYSCREEN_H
#define DISPLAYSCREEN_H

#include <QWidget>

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QScreen *screen, QWidget *parent = nullptr);
    void pass();

private:
    void initUI();
    void setBackground();
    void setScreenLogo();

signals:
    void passed();

private:
    QScreen *m_screen;
};

#endif // DISPLAYSCREEN_H
