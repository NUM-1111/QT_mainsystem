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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *leftPanel;
    QVBoxLayout *leftLayout;
    QLabel *titleLabel;
    QLabel *connectionStatusLabel;
    QPushButton *startSubsystem1Btn;
    QPushButton *connectBtn;
    QPushButton *disconnectBtn;
    QPushButton *system1Btn;
    QPushButton *statusBtn;
    QPushButton *helpBtn;
    QLineEdit *commandInput;
    QPushButton *sendCommandBtn;
    QSpacerItem *verticalSpacer;
    QPushButton *clearLogBtn;
    QWidget *rightPanel;
    QVBoxLayout *rightLayout;
    QLabel *logTitleLabel;
    QTextEdit *logTextEdit;
    QLabel *lastResponseLabel;
    QTextEdit *responseTextEdit;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leftPanel = new QWidget(centralwidget);
        leftPanel->setObjectName(QString::fromUtf8("leftPanel"));
        leftPanel->setMaximumSize(QSize(300, 16777215));
        leftLayout = new QVBoxLayout(leftPanel);
        leftLayout->setObjectName(QString::fromUtf8("leftLayout"));
        titleLabel = new QLabel(leftPanel);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        titleLabel->setFont(font);
        titleLabel->setAlignment(Qt::AlignCenter);

        leftLayout->addWidget(titleLabel);

        connectionStatusLabel = new QLabel(leftPanel);
        connectionStatusLabel->setObjectName(QString::fromUtf8("connectionStatusLabel"));
        connectionStatusLabel->setAlignment(Qt::AlignCenter);

        leftLayout->addWidget(connectionStatusLabel);

        startSubsystem1Btn = new QPushButton(leftPanel);
        startSubsystem1Btn->setObjectName(QString::fromUtf8("startSubsystem1Btn"));

        leftLayout->addWidget(startSubsystem1Btn);

        connectBtn = new QPushButton(leftPanel);
        connectBtn->setObjectName(QString::fromUtf8("connectBtn"));

        leftLayout->addWidget(connectBtn);

        disconnectBtn = new QPushButton(leftPanel);
        disconnectBtn->setObjectName(QString::fromUtf8("disconnectBtn"));
        disconnectBtn->setEnabled(false);

        leftLayout->addWidget(disconnectBtn);

        system1Btn = new QPushButton(leftPanel);
        system1Btn->setObjectName(QString::fromUtf8("system1Btn"));
        system1Btn->setEnabled(false);

        leftLayout->addWidget(system1Btn);

        statusBtn = new QPushButton(leftPanel);
        statusBtn->setObjectName(QString::fromUtf8("statusBtn"));
        statusBtn->setEnabled(false);

        leftLayout->addWidget(statusBtn);

        helpBtn = new QPushButton(leftPanel);
        helpBtn->setObjectName(QString::fromUtf8("helpBtn"));
        helpBtn->setEnabled(false);

        leftLayout->addWidget(helpBtn);

        commandInput = new QLineEdit(leftPanel);
        commandInput->setObjectName(QString::fromUtf8("commandInput"));
        commandInput->setEnabled(false);

        leftLayout->addWidget(commandInput);

        sendCommandBtn = new QPushButton(leftPanel);
        sendCommandBtn->setObjectName(QString::fromUtf8("sendCommandBtn"));
        sendCommandBtn->setEnabled(false);

        leftLayout->addWidget(sendCommandBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        leftLayout->addItem(verticalSpacer);

        clearLogBtn = new QPushButton(leftPanel);
        clearLogBtn->setObjectName(QString::fromUtf8("clearLogBtn"));

        leftLayout->addWidget(clearLogBtn);


        horizontalLayout->addWidget(leftPanel);

        rightPanel = new QWidget(centralwidget);
        rightPanel->setObjectName(QString::fromUtf8("rightPanel"));
        rightLayout = new QVBoxLayout(rightPanel);
        rightLayout->setObjectName(QString::fromUtf8("rightLayout"));
        logTitleLabel = new QLabel(rightPanel);
        logTitleLabel->setObjectName(QString::fromUtf8("logTitleLabel"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        logTitleLabel->setFont(font1);

        rightLayout->addWidget(logTitleLabel);

        logTextEdit = new QTextEdit(rightPanel);
        logTextEdit->setObjectName(QString::fromUtf8("logTextEdit"));
        logTextEdit->setReadOnly(true);

        rightLayout->addWidget(logTextEdit);

        lastResponseLabel = new QLabel(rightPanel);
        lastResponseLabel->setObjectName(QString::fromUtf8("lastResponseLabel"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        lastResponseLabel->setFont(font2);

        rightLayout->addWidget(lastResponseLabel);

        responseTextEdit = new QTextEdit(rightPanel);
        responseTextEdit->setObjectName(QString::fromUtf8("responseTextEdit"));
        responseTextEdit->setMaximumSize(QSize(16777215, 100));
        responseTextEdit->setReadOnly(true);

        rightLayout->addWidget(responseTextEdit);


        horizontalLayout->addWidget(rightPanel);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 17));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\344\270\273\347\263\273\347\273\237 - \345\210\206\347\263\273\347\273\237\347\256\241\347\220\206", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\345\210\206\347\263\273\347\273\237\346\216\247\345\210\266", nullptr));
        connectionStatusLabel->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\347\212\266\346\200\201\357\274\232\346\234\252\350\277\236\346\216\245", nullptr));
        startSubsystem1Btn->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\345\210\206\347\263\273\347\273\2371\347\250\213\345\272\217", nullptr));
        connectBtn->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245\345\210\206\347\263\273\347\273\2371", nullptr));
        disconnectBtn->setText(QCoreApplication::translate("MainWindow", "\346\226\255\345\274\200\350\277\236\346\216\245", nullptr));
        system1Btn->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\345\210\206\347\263\273\347\273\2371\347\225\214\351\235\242", nullptr));
        statusBtn->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242\345\210\206\347\263\273\347\273\237\347\212\266\346\200\201", nullptr));
        helpBtn->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\345\270\256\345\212\251\344\277\241\346\201\257", nullptr));
        commandInput->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\350\207\252\345\256\232\344\271\211\345\221\275\344\273\244...", nullptr));
        sendCommandBtn->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201\345\221\275\344\273\244", nullptr));
        clearLogBtn->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\346\227\245\345\277\227", nullptr));
        logTitleLabel->setText(QCoreApplication::translate("MainWindow", "\351\200\232\344\277\241\346\227\245\345\277\227", nullptr));
        logTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\351\200\232\344\277\241\346\227\245\345\277\227\345\260\206\345\234\250\350\277\231\351\207\214\346\230\276\347\244\272...", nullptr));
        lastResponseLabel->setText(QCoreApplication::translate("MainWindow", "\346\234\200\345\220\216\345\223\215\345\272\224\357\274\232", nullptr));
        responseTextEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\210\206\347\263\273\347\273\237\347\232\204\345\223\215\345\272\224\345\260\206\345\234\250\350\277\231\351\207\214\346\230\276\347\244\272...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
