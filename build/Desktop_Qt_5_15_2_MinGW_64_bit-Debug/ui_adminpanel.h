/********************************************************************************
** Form generated from reading UI file 'adminpanel.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADMINPANEL_H
#define UI_ADMINPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_adminpanel
{
public:

    void setupUi(QWidget *adminpanel)
    {
        if (adminpanel->objectName().isEmpty())
            adminpanel->setObjectName(QString::fromUtf8("adminpanel"));
        adminpanel->resize(400, 300);

        retranslateUi(adminpanel);

        QMetaObject::connectSlotsByName(adminpanel);
    } // setupUi

    void retranslateUi(QWidget *adminpanel)
    {
        adminpanel->setWindowTitle(QCoreApplication::translate("adminpanel", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class adminpanel: public Ui_adminpanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADMINPANEL_H
