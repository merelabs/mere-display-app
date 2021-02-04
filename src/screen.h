#ifndef MERE_DISPLAY_SCREEN_H
#define MERE_DISPLAY_SCREEN_H

#include "mere/display/prompt.h"
#include "mere/auth/user/user.h"

class SimpleScreen;

class Screen : public Mere::Display::Prompt
{
    Q_OBJECT
public:
    ~Screen() override;
    explicit Screen(QWidget *parent = nullptr);
    void init() override;

    const QString username() const override;
    const QString password() const override;
    const QString session() const override;

private:
    void initUI();

public slots:
    void action(bool ok, const std::string &message);

signals:
    void authenticate(const std::string &username, const std::string &password);
    void reboot(int time);
    void shutdown(int time);

private:
    SimpleScreen *m_screen;
};

#endif // MERE_DISPLAY_SCREEN_H
