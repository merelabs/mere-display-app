#ifndef DISPLAYCLOCK_H
#define DISPLAYCLOCK_H

#include <QLabel>
#include <QWidget>

class ClockView : public QWidget
{
    Q_OBJECT
public:
    explicit ClockView(QWidget *parent = nullptr);

private:
    void initUI();

private slots:
    void updateTime();

signals:

private:
    QLabel *m_time;
};

#endif // DISPLAYCLOCK_H
