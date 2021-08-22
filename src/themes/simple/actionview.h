#ifndef DISPLAYACTION_H
#define DISPLAYACTION_H

#include <QWidget>

class ActionView : public QWidget
{
    Q_OBJECT
public:
    explicit ActionView(QWidget *parent = nullptr);

private:
    void initUI();

signals:
    void reboot();
    void shutdown();

};

#endif // DISPLAYACTION_H
