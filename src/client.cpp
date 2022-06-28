#include "client.h"

#include <QJsonObject>
#include <QJsonDocument>

Client::~Client()
{
    if(m_client)
    {
        delete m_client;
        m_client = nullptr;
    }
}

Client::Client(QObject *parent)
    : QObject(parent),
      m_client(nullptr)
{
    setObjectName("DisplayClient");

    try
    {
        m_client = new Mere::RPC::Client("mms://display");
        m_ready = true;
    }
    catch(...)
    {
        m_ready = false;
    }
}

void Client::authenticate(const std::string &user, const std::string &pass)
{
    if (!m_ready)
    {
        emit action(false, tr("DisplayClientNotReady").toStdString());
        return;
    }

    m_client->service("auth")->method("authenticate")->with({QString::fromStdString(user), QString::fromStdString(pass)})->call([](QVariant res, QVariant err, void *context){
        Client *client = static_cast<Client*>(context);
        if (!client) return;

        bool ok = res.toBool();

        std::string message;
        if(ok)
            message = "Succeed to authenticate user.";
        else
            message = "Unable to authenticate user.";

        client->action(ok, message);

    }, (void*) this);
}

void Client::session(const std::string &session)
{
    if (!m_ready)
    {
        emit action(false, tr("DisplayClientNotReady").toStdString());
        return;
    }

    m_client->service("session")->method("session")->with({QString::fromStdString(session)})->call([](QVariant res, QVariant err, void *context){
        Client *client = static_cast<Client*>(context);
        if (!client) return;

        bool ok = res.toBool();

        std::string message;
        if(ok)
            message = "Succeed to set session.";
        else
            message = "Unable to set session.";

        client->action(ok, message);

    }, (void*) this);
}

void Client::reboot(int time)
{
    if (!m_ready)
    {
        emit action(false, tr("DisplayClientNotReady").toStdString());
        return;
    }

    m_client->service("power")->method("reboot")->with({QVariant(time)})->call([](QVariant res, QVariant err, void *context){
        Client *client = static_cast<Client*>(context);
        if (!client) return;

        bool ok = res.toBool();

        std::string message;
        if(ok)
            message = "System is rebooting now....";
        else
            message = "Unable to reboot the system.";

        client->action(ok, message);

    }, (void*) this);

}

void Client::shutdown(int time)
{
    if (!m_ready)
    {
        emit action(false, tr("DisplayClientNotReady").toStdString());
        return;
    }

    m_client->service("power")->method("reboot")->with({QVariant(time)})->call([](QVariant res, QVariant err, void *context){
        Client *client = static_cast<Client*>(context);
        if (!client) return;

        bool ok = res.toBool();

        std::string message;
        if(ok)
            message = "System is shuting down now....";
        else
            message = "Unable to shutdown the system.";

        client->action(ok, message);

    }, (void*) this);
}
