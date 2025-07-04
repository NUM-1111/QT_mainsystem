#include "mainwindow.h"
#include "logindialog.h"
#include "databasemanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 初始化数据库
    DatabaseManager::getInstance().initDatabase("mainsystem.db");
    
    // 显示登录对话框
    loginDialog login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }
    return 0;
}
