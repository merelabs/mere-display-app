#ifndef MEREDISPLAYSCREEN_H
#define MEREDISPLAYSCREEN_H

#include "mere/display/prompt.h"
#include "mere/auth/user/user.h"

#include <QDebug>
#include <QLineEdit>

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
    void loginFailed();

signals:
    void authenticated(Mere::Auth::User &user);
    void authenticate(const std::string &username, const std::string &password);



private:
    QLineEdit m_username;
    QLineEdit m_password;
};

#endif // MEREDISPLAYSCREEN_H
