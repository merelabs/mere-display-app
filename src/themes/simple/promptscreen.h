#ifndef MERE_DISPLAY_SCREEN_H
#define MERE_DISPLAY_SCREEN_H

#include <QLineEdit>

class PromptScreen : public QWidget
{
    Q_OBJECT
public:
    ~PromptScreen();
    explicit PromptScreen(QWidget *parent = nullptr);

private:
    void initUI();

private slots:
    void authenticate();

signals:
    void authenticate(const std::string &username, const std::string &password);

private:
    QLineEdit *m_username;
    QLineEdit *m_password;
};

#endif // MERE_DISPLAY_SCREEN_H
