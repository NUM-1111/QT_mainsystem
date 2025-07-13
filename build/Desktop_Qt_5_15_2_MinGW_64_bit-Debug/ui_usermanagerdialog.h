/********************************************************************************
** Form generated from reading UI file 'usermanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMANAGERDIALOG_H
#define UI_USERMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
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
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_UserManagerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelTitle;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxUserList;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *tableUsers;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnRefresh;
    QPushButton *btnAddUser;
    QPushButton *btnDeleteUser;
    QGroupBox *groupBoxPermission;
    QVBoxLayout *verticalLayout_3;
    QFormLayout *formLayout;
    QLabel *labelUsername;
    QLineEdit *editUsername;
    QLabel *labelGroup;
    QComboBox *comboGroup;
    QLabel *labelRestrictions;
    QGridLayout *gridLayout;
    QCheckBox *checkSubsystem1;
    QCheckBox *checkSubsystem2;
    QCheckBox *checkSubsystem3;
    QCheckBox *checkSubsystem4;
    QCheckBox *checkSubsystem5;
    QLabel *labelPreview;
    QTextEdit *textPreview;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnSave;
    QPushButton *btnReset;
    QStatusBar *statusBar;

    void setupUi(QDialog *UserManagerDialog)
    {
        if (UserManagerDialog->objectName().isEmpty())
            UserManagerDialog->setObjectName(QString::fromUtf8("UserManagerDialog"));
        UserManagerDialog->resize(900, 600);
        verticalLayout = new QVBoxLayout(UserManagerDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelTitle = new QLabel(UserManagerDialog);
        labelTitle->setObjectName(QString::fromUtf8("labelTitle"));
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        labelTitle->setFont(font);
        labelTitle->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(labelTitle);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBoxUserList = new QGroupBox(UserManagerDialog);
        groupBoxUserList->setObjectName(QString::fromUtf8("groupBoxUserList"));
        verticalLayout_2 = new QVBoxLayout(groupBoxUserList);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tableUsers = new QTableWidget(groupBoxUserList);
        tableUsers->setObjectName(QString::fromUtf8("tableUsers"));
        tableUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableUsers->setSortingEnabled(true);

        verticalLayout_2->addWidget(tableUsers);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnRefresh = new QPushButton(groupBoxUserList);
        btnRefresh->setObjectName(QString::fromUtf8("btnRefresh"));

        horizontalLayout_2->addWidget(btnRefresh);

        btnAddUser = new QPushButton(groupBoxUserList);
        btnAddUser->setObjectName(QString::fromUtf8("btnAddUser"));

        horizontalLayout_2->addWidget(btnAddUser);

        btnDeleteUser = new QPushButton(groupBoxUserList);
        btnDeleteUser->setObjectName(QString::fromUtf8("btnDeleteUser"));

        horizontalLayout_2->addWidget(btnDeleteUser);


        verticalLayout_2->addLayout(horizontalLayout_2);


        horizontalLayout->addWidget(groupBoxUserList);

        groupBoxPermission = new QGroupBox(UserManagerDialog);
        groupBoxPermission->setObjectName(QString::fromUtf8("groupBoxPermission"));
        verticalLayout_3 = new QVBoxLayout(groupBoxPermission);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        labelUsername = new QLabel(groupBoxPermission);
        labelUsername->setObjectName(QString::fromUtf8("labelUsername"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelUsername);

        editUsername = new QLineEdit(groupBoxPermission);
        editUsername->setObjectName(QString::fromUtf8("editUsername"));
        editUsername->setReadOnly(true);

        formLayout->setWidget(0, QFormLayout::FieldRole, editUsername);

        labelGroup = new QLabel(groupBoxPermission);
        labelGroup->setObjectName(QString::fromUtf8("labelGroup"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelGroup);

        comboGroup = new QComboBox(groupBoxPermission);
        comboGroup->addItem(QString());
        comboGroup->addItem(QString());
        comboGroup->addItem(QString());
        comboGroup->setObjectName(QString::fromUtf8("comboGroup"));

        formLayout->setWidget(1, QFormLayout::FieldRole, comboGroup);


        verticalLayout_3->addLayout(formLayout);

        labelRestrictions = new QLabel(groupBoxPermission);
        labelRestrictions->setObjectName(QString::fromUtf8("labelRestrictions"));

        verticalLayout_3->addWidget(labelRestrictions);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkSubsystem1 = new QCheckBox(groupBoxPermission);
        checkSubsystem1->setObjectName(QString::fromUtf8("checkSubsystem1"));

        gridLayout->addWidget(checkSubsystem1, 0, 0, 1, 1);

        checkSubsystem2 = new QCheckBox(groupBoxPermission);
        checkSubsystem2->setObjectName(QString::fromUtf8("checkSubsystem2"));

        gridLayout->addWidget(checkSubsystem2, 0, 1, 1, 1);

        checkSubsystem3 = new QCheckBox(groupBoxPermission);
        checkSubsystem3->setObjectName(QString::fromUtf8("checkSubsystem3"));

        gridLayout->addWidget(checkSubsystem3, 1, 0, 1, 1);

        checkSubsystem4 = new QCheckBox(groupBoxPermission);
        checkSubsystem4->setObjectName(QString::fromUtf8("checkSubsystem4"));

        gridLayout->addWidget(checkSubsystem4, 1, 1, 1, 1);

        checkSubsystem5 = new QCheckBox(groupBoxPermission);
        checkSubsystem5->setObjectName(QString::fromUtf8("checkSubsystem5"));

        gridLayout->addWidget(checkSubsystem5, 2, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        labelPreview = new QLabel(groupBoxPermission);
        labelPreview->setObjectName(QString::fromUtf8("labelPreview"));

        verticalLayout_3->addWidget(labelPreview);

        textPreview = new QTextEdit(groupBoxPermission);
        textPreview->setObjectName(QString::fromUtf8("textPreview"));
        textPreview->setReadOnly(true);
        textPreview->setMaximumHeight(80);

        verticalLayout_3->addWidget(textPreview);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        btnSave = new QPushButton(groupBoxPermission);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout_3->addWidget(btnSave);

        btnReset = new QPushButton(groupBoxPermission);
        btnReset->setObjectName(QString::fromUtf8("btnReset"));

        horizontalLayout_3->addWidget(btnReset);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout->addWidget(groupBoxPermission);


        verticalLayout->addLayout(horizontalLayout);

        statusBar = new QStatusBar(UserManagerDialog);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));

        verticalLayout->addWidget(statusBar);


        retranslateUi(UserManagerDialog);

        QMetaObject::connectSlotsByName(UserManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *UserManagerDialog)
    {
        UserManagerDialog->setWindowTitle(QCoreApplication::translate("UserManagerDialog", "\347\224\250\346\210\267\346\235\203\351\231\220\347\256\241\347\220\206", nullptr));
        labelTitle->setText(QCoreApplication::translate("UserManagerDialog", "\347\224\250\346\210\267\346\235\203\351\231\220\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        groupBoxUserList->setTitle(QCoreApplication::translate("UserManagerDialog", "\347\224\250\346\210\267\345\210\227\350\241\250", nullptr));
        btnRefresh->setText(QCoreApplication::translate("UserManagerDialog", "\345\210\267\346\226\260\345\210\227\350\241\250", nullptr));
        btnAddUser->setText(QCoreApplication::translate("UserManagerDialog", "\346\267\273\345\212\240\347\224\250\346\210\267", nullptr));
        btnDeleteUser->setText(QCoreApplication::translate("UserManagerDialog", "\345\210\240\351\231\244\347\224\250\346\210\267", nullptr));
        groupBoxPermission->setTitle(QCoreApplication::translate("UserManagerDialog", "\346\235\203\351\231\220\350\256\276\347\275\256", nullptr));
        labelUsername->setText(QCoreApplication::translate("UserManagerDialog", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        labelGroup->setText(QCoreApplication::translate("UserManagerDialog", "\346\235\203\351\231\220\347\273\204\357\274\232", nullptr));
        comboGroup->setItemText(0, QCoreApplication::translate("UserManagerDialog", "\346\227\240\346\235\203\351\231\220\347\273\204", nullptr));
        comboGroup->setItemText(1, QCoreApplication::translate("UserManagerDialog", "\346\235\203\351\231\220\347\273\2041 (\345\210\206\347\263\273\347\273\2371-3)", nullptr));
        comboGroup->setItemText(2, QCoreApplication::translate("UserManagerDialog", "\346\235\203\351\231\220\347\273\2042 (\345\210\206\347\263\273\347\273\2374-5)", nullptr));

        labelRestrictions->setText(QCoreApplication::translate("UserManagerDialog", "\344\270\252\344\272\272\346\235\203\351\231\220\351\231\220\345\210\266\357\274\210\345\213\276\351\200\211\350\241\250\347\244\272\347\246\201\346\255\242\350\256\277\351\227\256\357\274\211\357\274\232", nullptr));
        checkSubsystem1->setText(QCoreApplication::translate("UserManagerDialog", "\347\246\201\346\255\242\350\256\277\351\227\256\345\210\206\347\263\273\347\273\2371", nullptr));
        checkSubsystem2->setText(QCoreApplication::translate("UserManagerDialog", "\347\246\201\346\255\242\350\256\277\351\227\256\345\210\206\347\263\273\347\273\2372", nullptr));
        checkSubsystem3->setText(QCoreApplication::translate("UserManagerDialog", "\347\246\201\346\255\242\350\256\277\351\227\256\345\210\206\347\263\273\347\273\2373", nullptr));
        checkSubsystem4->setText(QCoreApplication::translate("UserManagerDialog", "\347\246\201\346\255\242\350\256\277\351\227\256\345\210\206\347\263\273\347\273\2374", nullptr));
        checkSubsystem5->setText(QCoreApplication::translate("UserManagerDialog", "\347\246\201\346\255\242\350\256\277\351\227\256\345\210\206\347\263\273\347\273\2375", nullptr));
        labelPreview->setText(QCoreApplication::translate("UserManagerDialog", "\346\234\200\347\273\210\346\235\203\351\231\220\351\242\204\350\247\210\357\274\232", nullptr));
        btnSave->setText(QCoreApplication::translate("UserManagerDialog", "\344\277\235\345\255\230\346\235\203\351\231\220\350\256\276\347\275\256", nullptr));
        btnReset->setText(QCoreApplication::translate("UserManagerDialog", "\351\207\215\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserManagerDialog: public Ui_UserManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMANAGERDIALOG_H
