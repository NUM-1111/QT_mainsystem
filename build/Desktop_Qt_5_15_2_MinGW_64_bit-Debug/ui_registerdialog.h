/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

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

class Ui_registerDialog
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *registerwidget;
    QHBoxLayout *usernameLayout;
    QLabel *username;
    QLineEdit *usernameinput;
    QHBoxLayout *passwordLayout;
    QLabel *password;
    QLineEdit *passwordinput;
    QHBoxLayout *passwordsureLaout;
    QLabel *passwordsure;
    QLineEdit *passwordsureinput;
    QHBoxLayout *btnlayout;
    QPushButton *registerBtn;
    QPushButton *backtologinBtn;

    void setupUi(QDialog *registerDialog)
    {
        if (registerDialog->objectName().isEmpty())
            registerDialog->setObjectName(QString::fromUtf8("registerDialog"));
        registerDialog->resize(400, 300);
        verticalLayoutWidget = new QWidget(registerDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(80, 60, 221, 161));
        registerwidget = new QVBoxLayout(verticalLayoutWidget);
        registerwidget->setObjectName(QString::fromUtf8("registerwidget"));
        registerwidget->setContentsMargins(0, 0, 0, 0);
        usernameLayout = new QHBoxLayout();
        usernameLayout->setObjectName(QString::fromUtf8("usernameLayout"));
        username = new QLabel(verticalLayoutWidget);
        username->setObjectName(QString::fromUtf8("username"));

        usernameLayout->addWidget(username);

        usernameinput = new QLineEdit(verticalLayoutWidget);
        usernameinput->setObjectName(QString::fromUtf8("usernameinput"));

        usernameLayout->addWidget(usernameinput);


        registerwidget->addLayout(usernameLayout);

        passwordLayout = new QHBoxLayout();
        passwordLayout->setObjectName(QString::fromUtf8("passwordLayout"));
        password = new QLabel(verticalLayoutWidget);
        password->setObjectName(QString::fromUtf8("password"));

        passwordLayout->addWidget(password);

        passwordinput = new QLineEdit(verticalLayoutWidget);
        passwordinput->setObjectName(QString::fromUtf8("passwordinput"));

        passwordLayout->addWidget(passwordinput);


        registerwidget->addLayout(passwordLayout);

        passwordsureLaout = new QHBoxLayout();
        passwordsureLaout->setObjectName(QString::fromUtf8("passwordsureLaout"));
        passwordsure = new QLabel(verticalLayoutWidget);
        passwordsure->setObjectName(QString::fromUtf8("passwordsure"));

        passwordsureLaout->addWidget(passwordsure);

        passwordsureinput = new QLineEdit(verticalLayoutWidget);
        passwordsureinput->setObjectName(QString::fromUtf8("passwordsureinput"));

        passwordsureLaout->addWidget(passwordsureinput);


        registerwidget->addLayout(passwordsureLaout);

        btnlayout = new QHBoxLayout();
        btnlayout->setObjectName(QString::fromUtf8("btnlayout"));
        registerBtn = new QPushButton(verticalLayoutWidget);
        registerBtn->setObjectName(QString::fromUtf8("registerBtn"));

        btnlayout->addWidget(registerBtn);

        backtologinBtn = new QPushButton(verticalLayoutWidget);
        backtologinBtn->setObjectName(QString::fromUtf8("backtologinBtn"));

        btnlayout->addWidget(backtologinBtn);


        registerwidget->addLayout(btnlayout);


        retranslateUi(registerDialog);

        QMetaObject::connectSlotsByName(registerDialog);
    } // setupUi

    void retranslateUi(QDialog *registerDialog)
    {
        registerDialog->setWindowTitle(QCoreApplication::translate("registerDialog", "Dialog", nullptr));
        username->setText(QCoreApplication::translate("registerDialog", "\347\224\250\346\210\267\345\220\215", nullptr));
        password->setText(QCoreApplication::translate("registerDialog", "\345\257\206\347\240\201    ", nullptr));
        passwordsure->setText(QCoreApplication::translate("registerDialog", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        registerBtn->setText(QCoreApplication::translate("registerDialog", "\346\263\250\345\206\214", nullptr));
        backtologinBtn->setText(QCoreApplication::translate("registerDialog", "\350\277\224\345\233\236\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registerDialog: public Ui_registerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
