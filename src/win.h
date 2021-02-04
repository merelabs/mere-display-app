#ifndef MEREDISPLAYWIN_H
#define MEREDISPLAYWIN_H

#include "screen.h"
#include "client.h"

#include <QWidget>

class Win : public QWidget
{
    Q_OBJECT
public:
    ~Win();
    explicit Win(QWidget *parent = nullptr);

signals:

public slots:
    void authenticate(const std::string &username, const std::string &password) const;

private:
    Screen *m_screen;
    Client *m_client;

};

#endif // MEREDISPLAYWIN_H
