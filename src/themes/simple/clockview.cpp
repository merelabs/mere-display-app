#include "clockview.h"

#include <QTime>
#include <QTimer>
#include <QLabel>
#include <QVBoxLayout>
ClockView::ClockView(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &ClockView::updateTime);
    timer->start(1000);

    initUI();
}

void ClockView::initUI()
{
    m_time = new QLabel(this);
    m_time->setText(QDateTime::currentDateTime().toString());
    layout()->addWidget(m_time);
}

void ClockView::updateTime()
{
    m_time->setText(QDateTime::currentDateTime().toString());
}
