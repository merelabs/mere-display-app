#ifndef SIMPLESCREEN_H
#define SIMPLESCREEN_H

#include <QWidget>
#include <QLineEdit>

class SimpleScreen : public QWidget
{
    Q_OBJECT
public:
    explicit SimpleScreen(QWidget *parent = nullptr);

    void initUI();

private:
    void initHeaderUI();
    void initContentUI();
    void initFooterUI();

private slots:
    void authenticate();
    void reboot();
    void shutdown();

signals:
    void authenticate(const std::string &username, const std::string &password);

    void reboot(const int &time);
    void shutdown(const int &time);

private:
    QLineEdit *m_usernameEdit;
    QLineEdit *m_passwordEdit;
};

#endif // SIMPLESCREEN_H
