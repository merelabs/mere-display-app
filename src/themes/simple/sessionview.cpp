#include "sessionview.h"

#include <QButtonGroup>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
SessionView::SessionView(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(3);

    init();
    initUI();
}

void SessionView::init()
{
    Mere::XDG::XSessionDirectoryTraverser traverser;
    m_sessions = traverser.traverse();
}

void SessionView::initUI()
{
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setAlignment(Qt::AlignCenter);
    hLayout->setSpacing(3);

    QWidget *list = new QWidget(this);
    list->setLayout(hLayout);

    QButtonGroup *group = new QButtonGroup(this);
    connect(group, SIGNAL(buttonClicked(QAbstractButton *)), this, SLOT(select(QAbstractButton *)));

    int counter = 1;
    for(auto const &sesssion : m_sessions)
    {
        QPushButton *view = new QPushButton(this);
        view->setObjectName("DisplaySession");
        view->setText(QString::number(counter++));
        view->setProperty("session",  QVariant::fromValue(sesssion));
        view->setToolTip(comment(sesssion).c_str());
        view->setCheckable(true);
        hLayout->addWidget(view);

        group->addButton(view);
    }

    layout()->addWidget(list);

    QLabel *label = new QLabel(this);
    label->setObjectName("SessionNameLabel");
    label->setAlignment(Qt::AlignCenter);
    layout()->addWidget(label);

    QList<QAbstractButton *> buttons = group->buttons();
    if (buttons.size())
        buttons.at(0)->click();
}

void SessionView::select(QAbstractButton *button)
{
    QVariant object = button->property("session");
    m_session = qvariant_cast<Mere::XDG::DesktopEntry>(object);

    QLabel *label = findChild<QLabel *>("SessionNameLabel");
    if (label)
    {
        label->setText(name(m_session).c_str());
    }
}

Mere::XDG::DesktopEntry SessionView::session() const
{
    return m_session;
}

std::string SessionView::name(const Mere::XDG::DesktopEntry &session) const
{
    QLocale locale = QLocale::system();

    std::string key("Name");
    bool set = false;
    std::string value = session.get(key + "[" + locale.name().toStdString() +"]", &set);
    if (set) return value;

    value = session.get(key + "[" + locale.bcp47Name().toStdString() +"]", &set);
    if (set) return value;

    return session.name();
}

std::string SessionView::comment(const Mere::XDG::DesktopEntry &session) const
{
    QLocale locale = QLocale::system();

    std::string key("Comment");
    bool set = false;
    std::string value = session.get(key + "[" + locale.name().toStdString() +"]", &set);
    if (set) return value;

    value = session.get(key + "[" + locale.bcp47Name().toStdString() +"]", &set);
    if (set) return value;

    return session.comment();
}
