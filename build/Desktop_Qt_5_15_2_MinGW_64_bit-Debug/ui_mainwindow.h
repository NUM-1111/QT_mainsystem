/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacerTop;
    QPushButton *btnSubsystem1;
    QPushButton *btnSubsystem2;
    QPushButton *btnSubsystem3;
    QPushButton *btnSubsystem4;
    QPushButton *btnSubsystem5;
    QPushButton *btnViewUsers;
    QPushButton *btnViewGroups;
    QSpacerItem *verticalSpacerBottom;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(318, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(16);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacerTop = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacerTop);

        btnSubsystem1 = new QPushButton(centralwidget);
        btnSubsystem1->setObjectName(QString::fromUtf8("btnSubsystem1"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        btnSubsystem1->setFont(font);

        verticalLayout->addWidget(btnSubsystem1);

        btnSubsystem2 = new QPushButton(centralwidget);
        btnSubsystem2->setObjectName(QString::fromUtf8("btnSubsystem2"));
        btnSubsystem2->setFont(font);

        verticalLayout->addWidget(btnSubsystem2);

        btnSubsystem3 = new QPushButton(centralwidget);
        btnSubsystem3->setObjectName(QString::fromUtf8("btnSubsystem3"));
        btnSubsystem3->setFont(font);

        verticalLayout->addWidget(btnSubsystem3);

        btnSubsystem4 = new QPushButton(centralwidget);
        btnSubsystem4->setObjectName(QString::fromUtf8("btnSubsystem4"));
        btnSubsystem4->setFont(font);

        verticalLayout->addWidget(btnSubsystem4);

        btnSubsystem5 = new QPushButton(centralwidget);
        btnSubsystem5->setObjectName(QString::fromUtf8("btnSubsystem5"));
        btnSubsystem5->setFont(font);

        verticalLayout->addWidget(btnSubsystem5);

        btnViewUsers = new QPushButton(centralwidget);
        btnViewUsers->setObjectName(QString::fromUtf8("btnViewUsers"));
        btnViewUsers->setFont(font);

        verticalLayout->addWidget(btnViewUsers);

        btnViewGroups = new QPushButton(centralwidget);
        btnViewGroups->setObjectName(QString::fromUtf8("btnViewGroups"));
        btnViewGroups->setFont(font);

        verticalLayout->addWidget(btnViewGroups);

        verticalSpacerBottom = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacerBottom);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        btnSubsystem1->setText(QCoreApplication::translate("MainWindow", "\345\255\220\347\263\273\347\273\2371", nullptr));
        btnSubsystem2->setText(QCoreApplication::translate("MainWindow", "\345\255\220\347\263\273\347\273\2372", nullptr));
        btnSubsystem3->setText(QCoreApplication::translate("MainWindow", "\345\255\220\347\263\273\347\273\2373", nullptr));
        btnSubsystem4->setText(QCoreApplication::translate("MainWindow", "\345\255\220\347\263\273\347\273\2374", nullptr));
        btnSubsystem5->setText(QCoreApplication::translate("MainWindow", "\345\255\220\347\263\273\347\273\2375", nullptr));
        btnViewUsers->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\346\211\200\346\234\211\347\224\250\346\210\267\344\277\241\346\201\257", nullptr));
        btnViewGroups->setText(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213\346\235\203\351\231\220\347\273\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
