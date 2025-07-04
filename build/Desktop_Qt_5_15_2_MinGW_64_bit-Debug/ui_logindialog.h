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

class Ui_loginDialog
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

    void setupUi(QDialog *loginDialog)
    {
        if (loginDialog->objectName().isEmpty())
            loginDialog->setObjectName(QString::fromUtf8("loginDialog"));
        loginDialog->resize(400, 300);
        verticalLayoutWidget = new QWidget(loginDialog);
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


        retranslateUi(loginDialog);

        QMetaObject::connectSlotsByName(loginDialog);
    } // setupUi

    void retranslateUi(QDialog *loginDialog)
    {
        loginDialog->setWindowTitle(QCoreApplication::translate("loginDialog", "Dialog", nullptr));
        username->setText(QCoreApplication::translate("loginDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        password->setText(QCoreApplication::translate("loginDialog", "\345\257\206\347\240\201    ", nullptr));
        loginBtn->setText(QCoreApplication::translate("loginDialog", "\347\231\273\345\275\225", nullptr));
        registerBtn->setText(QCoreApplication::translate("loginDialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginDialog: public Ui_loginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
