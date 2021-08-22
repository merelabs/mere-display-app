#ifndef DISPLAYSESSION_H
#define DISPLAYSESSION_H

#include "mere/xdg/xsessiondirectorytraverser.h"

#include <QLabel>
#include <QWidget>
#include <QAbstractButton>

class SessionView : public QWidget
{
    Q_OBJECT
public:
    explicit SessionView(QWidget *parent = nullptr);

    Mere::XDG::DesktopEntry session() const;

private:
    void init();
    void initUI();

    std::string name(const Mere::XDG::DesktopEntry &session) const;
    std::string comment(const Mere::XDG::DesktopEntry &session) const;

private slots:
    void select(QAbstractButton * button);

signals:

private:
    Mere::XDG::DesktopEntry m_session;
    std::vector<Mere::XDG::DesktopEntry> m_sessions;
};

#endif // DISPLAYSESSION_H
