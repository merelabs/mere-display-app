#ifndef MEREDISPLAYCONFIG_H
#define MEREDISPLAYCONFIG_H

#include <QObject>

class Config : public QObject
{
    Q_OBJECT
public:
    explicit Config(QObject *parent = nullptr);

    QString pidfile() const;

signals:

public slots:
};

#endif // MEREDISPLAYCONFIG_H
