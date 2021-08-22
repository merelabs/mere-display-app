#ifndef SIMPLESCREEN_H
#define SIMPLESCREEN_H

#include <QWidget>
#include <QLineEdit>

class SimpleScreen : public QWidget
{
    Q_OBJECT
public:
    explicit SimpleScreen(QWidget *parent = nullptr);
    void init();

    void setErrorMessage(const QString &message);
    void setTipOfTheDay(const QString &tip);

private:
    void initUI();
    void initHeaderUI();
    void initContentUI();
    void initFooterUI();

public slots:
    void action(bool ok, const std::string &message);

signals:
    void authenticate(const std::string &username, const std::string &password);

    void reboot(const int &time);
    void shutdown(const int &time);

private:
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
};

#endif // SIMPLESCREEN_H
