#include "mainwindow.h"
#include "logindialog.h"
#include "databasemanager.h"
#include <QApplication>
#include <QDebug>
#include <QMessageBox>

/**
 * @brief 运行数据库功能测试
 */
void runDatabaseTest()
{
    qDebug() << "=== 开始数据库功能测试 ===";
    
    DatabaseManager& dbManager = DatabaseManager::getInstance();
    
    // 测试1：数据库初始化
    qDebug() << "\n--- 测试1：数据库初始化 ---";
    bool initResult = dbManager.initDatabase("test_mainsystem.db");
    qDebug() << "数据库初始化结果:" << (initResult ? "成功" : "失败");
    
    if (!initResult) {
        qDebug() << "❌ 数据库初始化失败";
        return;
    }
    
    // 测试2：用户注册
    qDebug() << "\n--- 测试2：用户注册 ---";
    QString testUsername = "testuser1";
    QString testPassword = "password123";
    bool registerResult = dbManager.registerUser(testUsername, testPassword);
    qDebug() << "注册用户" << testUsername << "结果:" << (registerResult ? "成功" : "失败");
    
    // 测试3：用户登录
    qDebug() << "\n--- 测试3：用户登录 ---";
    bool loginResult = dbManager.loginUser(testUsername, testPassword);
    qDebug() << "用户" << testUsername << "登录结果:" << (loginResult ? "成功" : "失败");
    
    // 测试4：错误密码登录
    qDebug() << "\n--- 测试4：错误密码登录 ---";
    bool wrongLoginResult = dbManager.loginUser(testUsername, "wrongpassword");
    qDebug() << "错误密码登录结果:" << (wrongLoginResult ? "成功" : "失败");
    
    // 测试5：重复注册
    qDebug() << "\n--- 测试5：重复注册 ---";
    bool duplicateResult = dbManager.registerUser(testUsername, "newpassword");
    qDebug() << "重复注册结果:" << (duplicateResult ? "成功" : "失败");
    
    qDebug() << "\n=== 数据库功能测试完成 ===";
    
    // 显示测试结果
    QString testSummary = QString("数据库测试结果:\n"
                                 "初始化: %1\n"
                                 "注册: %2\n"
                                 "登录: %3\n"
                                 "错误密码拒绝: %4\n"
                                 "重复注册阻止: %5")
                                 .arg(initResult ? "✅" : "❌")
                                 .arg(registerResult ? "✅" : "❌")
                                 .arg(loginResult ? "✅" : "❌")
                                 .arg(!wrongLoginResult ? "✅" : "❌")
                                 .arg(!duplicateResult ? "✅" : "❌");
    
    QMessageBox::information(nullptr, "数据库测试", testSummary);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    // 运行数据库测试
    runDatabaseTest();
    
    // 初始化数据库
    DatabaseManager::getInstance().initDatabase("mainsystem.db");
    
    // 显示登录对话框
    LoginDialog login;
    if (login.exec() == QDialog::Accepted) {
        MainWindow w;
        w.show();
        return a.exec();
    }
    return 0;
}
