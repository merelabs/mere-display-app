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

Client::Client(QObject *parent) : QObject(parent)
{
    // A client pointing to the service path
    // service path = /server/service
    try
    {
        m_client = new Mere::RPC::Client("mms://display");
    }
    catch(...)
    {
        // catch exception
    }
}

void Client::authenticate(const std::string &user, const std::string &pass) const
{
    m_client->service("auth")->method("authenticate")->with({QString::fromStdString(user), QString::fromStdString(pass)})->call([](QVariant res, QVariant err, void *context){
        qDebug() << "Got it:" << res;

        bool ok = res.toBool();
        Client *client = static_cast<Client*>(context);
        if (client)
        {
            if(ok)
                client->loginSucceed();
            else
                client->loginFailed();
        }

    }, (void*) this);
}
