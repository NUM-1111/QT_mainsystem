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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *systemSelect;
    QPushButton *system1;
    QPushButton *system3;
    QPushButton *system2;
    QPushButton *system4;
    QPushButton *system5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(290, 130, 191, 201));
        systemSelect = new QVBoxLayout(verticalLayoutWidget);
        systemSelect->setObjectName(QString::fromUtf8("systemSelect"));
        systemSelect->setContentsMargins(0, 0, 0, 0);
        system1 = new QPushButton(verticalLayoutWidget);
        system1->setObjectName(QString::fromUtf8("system1"));

        systemSelect->addWidget(system1);

        system3 = new QPushButton(verticalLayoutWidget);
        system3->setObjectName(QString::fromUtf8("system3"));

        systemSelect->addWidget(system3);

        system2 = new QPushButton(verticalLayoutWidget);
        system2->setObjectName(QString::fromUtf8("system2"));

        systemSelect->addWidget(system2);

        system4 = new QPushButton(verticalLayoutWidget);
        system4->setObjectName(QString::fromUtf8("system4"));

        systemSelect->addWidget(system4);

        system5 = new QPushButton(verticalLayoutWidget);
        system5->setObjectName(QString::fromUtf8("system5"));

        systemSelect->addWidget(system5);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        system1->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\345\210\206\347\263\273\347\273\2371", nullptr));
        system3->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\345\210\206\347\263\273\347\273\2373", nullptr));
        system2->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\345\210\206\347\263\273\347\273\2372", nullptr));
        system4->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\345\210\206\347\263\273\347\273\2374", nullptr));
        system5->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\345\210\206\347\263\273\347\273\2375", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
