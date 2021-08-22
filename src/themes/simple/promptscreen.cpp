#include "promptscreen.h"

#include "mere/utils/stringutils.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
PromptScreen::~PromptScreen()
{
}

PromptScreen::PromptScreen(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("PromptScreen");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

    initUI();
}

void PromptScreen::initUI()
{
    QWidget *content = new QWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout();
    vLayout->setAlignment(Qt::AlignCenter);
    content->setLayout(vLayout);
    layout()->addWidget(content);

    QWidget *logo = new QWidget();
    logo->setLayout(new QHBoxLayout);

    QLabel *osLabel = new QLabel(this);
    osLabel->setScaledContents(true);
    osLabel->setMaximumSize(QSize(96, 94));

    QPixmap pixmap("/usr/local/share/mere/display/freebsd-logo.png");
    osLabel->setPixmap(pixmap);
    logo->layout()->addWidget(osLabel);

    vLayout->addWidget(logo);

    QWidget *loginForm = new QWidget(this);
    loginForm->setObjectName("SimpleScreenForm");
    loginForm->setMinimumSize(350, 150);
    loginForm->setMaximumSize(400, 200);

    loginForm->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    vLayout->addWidget(loginForm);


    QGridLayout *contentLayout = new QGridLayout(loginForm);
    contentLayout->setContentsMargins(50, 35, 50, 35);
    contentLayout->setRowMinimumHeight(2, 20);
    contentLayout->setHorizontalSpacing(15);
    contentLayout->setVerticalSpacing(10);

    QLabel *usernameLabel = new QLabel(tr("PromptUsername"));
    contentLayout->addWidget(usernameLabel, 0, 0);

    m_username = new QLineEdit();
    m_username->setFocus();
    contentLayout->addWidget(m_username, 0, 1);

    QLabel *passwordLabel = new QLabel(tr("PromptPassword"));
    contentLayout->addWidget(passwordLabel, 1, 0);

    m_password = new QLineEdit();
    m_password->setObjectName("SimpleScreenFormPassword");
    m_password->setEchoMode(QLineEdit::Password);
    contentLayout->addWidget(m_password, 1, 1);

    QPushButton *loginButton = new QPushButton(tr("PromptLogin"));
    loginButton->setObjectName("SimpleScreenFormButton");
    contentLayout->addWidget(loginButton, 3, 0, 1, 2);

    loginForm->setLayout(contentLayout);

    QLabel *actionLabel = new QLabel("");
    actionLabel->setObjectName("SimpleScreenFormError");
    actionLabel->setAlignment(Qt::AlignHCenter);
    vLayout->addWidget(actionLabel);

    connect(m_username, SIGNAL(returnPressed()), this, SLOT(authenticate()));
    connect(m_password, SIGNAL(returnPressed()), this, SLOT(authenticate()));
    connect(loginButton, SIGNAL(released()), this, SLOT(authenticate()));

    showFullScreen();
}

void PromptScreen::authenticate()
{
    QLabel *errorMessage = this->findChild<QLabel* >("SimpleScreenFormError");
    errorMessage->setText("");

    const std::string &username = m_username->text().toStdString();
    if (Mere::Utils::StringUtils::isBlank(username))
    {
        errorMessage->setText("No username entered, Please enter username.");
        m_username->setFocus();
        return;
    }

    const std::string &password = m_password->text().toStdString();
    if (Mere::Utils::StringUtils::isBlank(password))
    {
        errorMessage->setText("No password entered, Please enter password.");
        m_password->setFocus();
        return;
    }
    emit authenticate(username, password);
}
