#ifndef MEREDISPLAYWIN_H
#define MEREDISPLAYWIN_H

#include "client.h"

#include <QWidget>

class SimpleScreen;
class Theme : public QWidget
{
    Q_OBJECT
public:
    ~Theme();
    explicit Theme(QScreen *screen, QWidget *parent = nullptr);

signals:

public slots:
    void authenticate(const std::string &username, const std::string &password) const;
    void session(const std::string &session) const;
    void reboot(int time);
    void shutdown(int time);

private:
    Client *m_client;
    SimpleScreen *m_screen;
};

#endif // MEREDISPLAYWIN_H
