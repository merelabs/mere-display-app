#ifndef PASSER_H
#define PASSER_H

#include <QDebug>
#include <QObject>

class Screen;

class Passer : public QObject
{
    Q_OBJECT
public:
    explicit Passer(QObject *parent = nullptr);
    int pass();

signals:
    void passed();

private:
    std::vector<Screen *> m_screens;
};

#endif // PASSER_H
