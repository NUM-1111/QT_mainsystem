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
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_GroupManagerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxGroupList;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableGroups;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnAddGroup;
    QPushButton *btnDeleteGroup;
    QGroupBox *groupBoxGroupDetail;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout;
    QLabel *labelGroupName;
    QLineEdit *editGroupName;
    QLabel *labelGroupRights;
    QGridLayout *gridLayout;
    QCheckBox *checkSubsystem1;
    QCheckBox *checkSubsystem2;
    QCheckBox *checkSubsystem3;
    QCheckBox *checkSubsystem4;
    QCheckBox *checkSubsystem5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnSave;
    QPushButton *btnReset;
    QStatusBar *statusBar;

    void setupUi(QDialog *GroupManagerDialog)
    {
        if (GroupManagerDialog->objectName().isEmpty())
            GroupManagerDialog->setObjectName(QString::fromUtf8("GroupManagerDialog"));
        GroupManagerDialog->resize(800, 500);
        verticalLayout = new QVBoxLayout(GroupManagerDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelTitle = new QLabel(GroupManagerDialog);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBoxGroupList = new QGroupBox(GroupManagerDialog);
        groupBoxGroupList->setObjectName(QString::fromUtf8("groupBoxGroupList"));
        verticalLayout_2 = new QVBoxLayout(groupBoxGroupList);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableGroups = new QTableWidget(groupBoxGroupList);
        tableGroups->setObjectName(QString::fromUtf8("tableGroups"));
        tableGroups->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableGroups->setSortingEnabled(true);

        verticalLayout_2->addWidget(tableGroups);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnAddGroup = new QPushButton(groupBoxGroupList);
        btnAddGroup->setObjectName(QString::fromUtf8("btnAddGroup"));

        horizontalLayout_2->addWidget(btnAddGroup);

        btnDeleteGroup = new QPushButton(groupBoxGroupList);
        btnDeleteGroup->setObjectName(QString::fromUtf8("btnDeleteGroup"));

        horizontalLayout_2->addWidget(btnDeleteGroup);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(groupBoxGroupList);

        groupBoxGroupDetail = new QGroupBox(GroupManagerDialog);
        groupBoxGroupDetail->setObjectName(QString::fromUtf8("groupBoxGroupDetail"));
        verticalLayout_3 = new QVBoxLayout(groupBoxGroupDetail);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        labelGroupName = new QLabel(groupBoxGroupDetail);
        labelGroupName->setObjectName(QString::fromUtf8("labelGroupName"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelGroupName);

        editGroupName = new QLineEdit(groupBoxGroupDetail);
        editGroupName->setObjectName(QString::fromUtf8("editGroupName"));

        formLayout->setWidget(0, QFormLayout::FieldRole, editGroupName);


        verticalLayout_3->addLayout(formLayout);

        labelGroupRights = new QLabel(groupBoxGroupDetail);
        labelGroupRights->setObjectName(QString::fromUtf8("labelGroupRights"));

        verticalLayout_3->addWidget(labelGroupRights);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkSubsystem1 = new QCheckBox(groupBoxGroupDetail);
        checkSubsystem1->setObjectName(QString::fromUtf8("checkSubsystem1"));

        gridLayout->addWidget(checkSubsystem1, 0, 0, 1, 1);

        checkSubsystem2 = new QCheckBox(groupBoxGroupDetail);
        checkSubsystem2->setObjectName(QString::fromUtf8("checkSubsystem2"));

        gridLayout->addWidget(checkSubsystem2, 0, 1, 1, 1);

        checkSubsystem3 = new QCheckBox(groupBoxGroupDetail);
        checkSubsystem3->setObjectName(QString::fromUtf8("checkSubsystem3"));

        gridLayout->addWidget(checkSubsystem3, 1, 0, 1, 1);

        checkSubsystem4 = new QCheckBox(groupBoxGroupDetail);
        checkSubsystem4->setObjectName(QString::fromUtf8("checkSubsystem4"));

        gridLayout->addWidget(checkSubsystem4, 1, 1, 1, 1);

        checkSubsystem5 = new QCheckBox(groupBoxGroupDetail);
        checkSubsystem5->setObjectName(QString::fromUtf8("checkSubsystem5"));

        gridLayout->addWidget(checkSubsystem5, 2, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnSave = new QPushButton(groupBoxGroupDetail);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout_3->addWidget(btnSave);

        btnReset = new QPushButton(groupBoxGroupDetail);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));

        horizontalLayout_3->addWidget(btnReset);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout->addWidget(groupBoxGroupDetail);


        verticalLayout->addLayout(horizontalLayout);

        statusBar = new QStatusBar(GroupManagerDialog);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        verticalLayout->addWidget(statusBar);


        retranslateUi(GroupManagerDialog);

        QMetaObject::connectSlotsByName(GroupManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *GroupManagerDialog)
    {
        GroupManagerDialog->setWindowTitle(QCoreApplication::translate("GroupManagerDialog", "\346\235\203\351\231\220\347\273\204\347\256\241\347\220\206", nullptr));
        labelTitle->setText(QCoreApplication::translate("GroupManagerDialog", "\346\235\203\351\231\220\347\273\204\347\256\241\347\220\206", nullptr));
        groupBoxGroupList->setTitle(QCoreApplication::translate("GroupManagerDialog", "\346\235\203\351\231\220\347\273\204\345\210\227\350\241\250", nullptr));
        btnAddGroup->setText(QCoreApplication::translate("GroupManagerDialog", "\346\267\273\345\212\240\347\273\204", nullptr));
        btnDeleteGroup->setText(QCoreApplication::translate("GroupManagerDialog", "\345\210\240\351\231\244\347\273\204", nullptr));
        groupBoxGroupDetail->setTitle(QCoreApplication::translate("GroupManagerDialog", "\347\273\204\350\257\246\346\203\205", nullptr));
        labelGroupName->setText(QCoreApplication::translate("GroupManagerDialog", "\347\273\204\345\220\215\357\274\232", nullptr));
        labelGroupRights->setText(QCoreApplication::translate("GroupManagerDialog", "\345\217\257\350\256\277\351\227\256\345\210\206\347\263\273\347\273\237\357\274\232", nullptr));
        checkSubsystem1->setText(QCoreApplication::translate("GroupManagerDialog", "\345\210\206\347\263\273\347\273\2371", nullptr));
        checkSubsystem2->setText(QCoreApplication::translate("GroupManagerDialog", "\345\210\206\347\263\273\347\273\2372", nullptr));
        checkSubsystem3->setText(QCoreApplication::translate("GroupManagerDialog", "\345\210\206\347\263\273\347\273\2373", nullptr));
        checkSubsystem4->setText(QCoreApplication::translate("GroupManagerDialog", "\345\210\206\347\263\273\347\273\2374", nullptr));
        checkSubsystem5->setText(QCoreApplication::translate("GroupManagerDialog", "\345\210\206\347\263\273\347\273\2375", nullptr));
        btnSave->setText(QCoreApplication::translate("GroupManagerDialog", "\344\277\235\345\255\230", nullptr));
        btnReset->setText(QCoreApplication::translate("GroupManagerDialog", "\351\207\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GroupManagerDialog: public Ui_GroupManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPMANAGERDIALOG_H
