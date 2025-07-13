/********************************************************************************
** Form generated from reading UI file 'groupmanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPMANAGERDIALOG_H
#define UI_GROUPMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_GroupManagerDialog
{
public:

    void setupUi(QDialog *GroupManagerDialog)
    {
        if (GroupManagerDialog->objectName().isEmpty())
            GroupManagerDialog->setObjectName(QString::fromUtf8("GroupManagerDialog"));
        GroupManagerDialog->resize(400, 300);

        retranslateUi(GroupManagerDialog);

        QMetaObject::connectSlotsByName(GroupManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *GroupManagerDialog)
    {
        GroupManagerDialog->setWindowTitle(QCoreApplication::translate("GroupManagerDialog", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupManagerDialog: public Ui_GroupManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPMANAGERDIALOG_H
