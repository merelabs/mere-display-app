#include "actionview.h"

#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
ActionView::ActionView(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("ActionView");

    setMaximumHeight(75);

    QHBoxLayout *layout = new QHBoxLayout(this);
    setLayout(layout);

    initUI();
}

void ActionView::initUI()
{
    QSpacerItem *spacer = new QSpacerItem(20, 40, QSizePolicy::Expanding, QSizePolicy::Minimum);
    layout()->addItem(spacer);

    QPushButton *rebootButton = new QPushButton(QIcon(":/display/reboot.png"), tr("ActionReboot"), this);
    rebootButton->setFocusPolicy(Qt::NoFocus);
    rebootButton->setFlat(true);
    layout()->addWidget(rebootButton);

    QFrame *vLine = new QFrame(this);
    vLine->setObjectName("verticleLine");
    vLine->setFrameShape(QFrame::VLine);
    vLine->setMaximumHeight(rebootButton->height());
    layout()->addWidget(vLine);

    QPushButton *powerOffButton = new QPushButton(QIcon(":/display/poweroff.png"), tr("ActionPowerOff"), this);
    powerOffButton->setFocusPolicy(Qt::NoFocus);
    powerOffButton->setFlat(true);

    layout()->addWidget(powerOffButton);

    connect(rebootButton, SIGNAL(released()), this, SIGNAL(action()));
    connect(powerOffButton, SIGNAL(released()), this, SIGNAL(shutdown()));
}
