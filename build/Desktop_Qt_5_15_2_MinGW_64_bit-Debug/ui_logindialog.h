/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *loginwidget;
    QHBoxLayout *usernameLayout;
    QLabel *username;
    QLineEdit *usernameinput;
    QHBoxLayout *passwordLayout;
    QLabel *password;
    QLineEdit *passwordinput;
    QHBoxLayout *btnLayout;
    QPushButton *loginBtn;
    QPushButton *registerBtn;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(400, 300);
        verticalLayoutWidget = new QWidget(LoginDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 70, 241, 141));
        loginwidget = new QVBoxLayout(verticalLayoutWidget);
        loginwidget->setObjectName(QString::fromUtf8("loginwidget"));
        loginwidget->setContentsMargins(0, 0, 0, 0);
        usernameLayout = new QHBoxLayout();
        usernameLayout->setObjectName(QString::fromUtf8("usernameLayout"));
        username = new QLabel(verticalLayoutWidget);
        username->setObjectName(QString::fromUtf8("username"));

        usernameLayout->addWidget(username);

        usernameinput = new QLineEdit(verticalLayoutWidget);
        usernameinput->setObjectName(QString::fromUtf8("usernameinput"));

        usernameLayout->addWidget(usernameinput);


        loginwidget->addLayout(usernameLayout);

        passwordLayout = new QHBoxLayout();
        passwordLayout->setObjectName(QString::fromUtf8("passwordLayout"));
        password = new QLabel(verticalLayoutWidget);
        password->setObjectName(QString::fromUtf8("password"));

        passwordLayout->addWidget(password);

        passwordinput = new QLineEdit(verticalLayoutWidget);
        passwordinput->setObjectName(QString::fromUtf8("passwordinput"));

        passwordLayout->addWidget(passwordinput);


        loginwidget->addLayout(passwordLayout);

        btnLayout = new QHBoxLayout();
        btnLayout->setObjectName(QString::fromUtf8("btnLayout"));
        loginBtn = new QPushButton(verticalLayoutWidget);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));

        btnLayout->addWidget(loginBtn);

        registerBtn = new QPushButton(verticalLayoutWidget);
        registerBtn->setObjectName(QString::fromUtf8("registerBtn"));

        btnLayout->addWidget(registerBtn);


        loginwidget->addLayout(btnLayout);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        username->setText(QCoreApplication::translate("LoginDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        password->setText(QCoreApplication::translate("LoginDialog", "\345\257\206\347\240\201    ", nullptr));
        loginBtn->setText(QCoreApplication::translate("LoginDialog", "\347\231\273\345\275\225", nullptr));
        registerBtn->setText(QCoreApplication::translate("LoginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
