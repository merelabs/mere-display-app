#ifndef MESSAGECLIENT_H
#define MESSAGECLIENT_H

#include "mere/rpc/client.h"

#include <iostream>
#include <QObject>

class Client : public QObject
{
    Q_OBJECT
public:
    ~Client();
    explicit Client(QObject *parent = nullptr);

    void authenticate(const std::string &user, const std::string &pass);
    void reboot(int time);
    void shutdown(int time);

signals:
    void action(bool ok, const std::string &message);

private:
    bool m_ready;
    Mere::RPC::Client *m_client;
};

#endif // MESSAGECLIENT_H
