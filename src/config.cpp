#include "config.h"

Config::Config(QObject *parent) : QObject(parent)
{

}

QString Config::pidfile() const
{
    return "/var/run/menshen.pid";
}
