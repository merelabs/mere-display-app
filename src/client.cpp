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
        emit authenticated(false, "Client and server connection is not ready.");
        return;
    }

    m_client->service("auth")->method("authenticate")->with({QString::fromStdString(user), QString::fromStdString(pass)})->call([](QVariant res, QVariant err, void *context){
        qDebug() << "Got it:" << res;
        Client *client = static_cast<Client*>(context);
        if (!client) return;

        bool ok = res.toBool();

        std::string message;
        if(ok)
            message = "Succeed to authenticate user.";
        else
            message = "Unable to authenticate user.";

        client->authenticated(false, message);

    }, (void*) this);
}
