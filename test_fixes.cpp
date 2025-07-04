#include <QCoreApplication>
#include <QDebug>
#include "databasemanager.h"

/**
 * @brief 测试注册和登录功能，验证bug修复
 */
void testRegistrationAndLogin()
{
    qDebug() << "=== 测试注册和登录功能 ===";
    
    DatabaseManager& dbManager = DatabaseManager::getInstance();
    
    // 初始化数据库
    bool initResult = dbManager.initDatabase("test_fixes.db");
    qDebug() << "数据库初始化:" << (initResult ? "成功" : "失败");
    
    if (!initResult) {
        qDebug() << "❌ 数据库初始化失败，无法继续测试";
        return;
    }
    
    // 测试1：注册新用户
    QString testUser = "testuser_fix";
    QString testPass = "password123";
    
    qDebug() << "\n--- 测试1：注册新用户 ---";
    bool registerResult = dbManager.registerUser(testUser, testPass);
    qDebug() << "注册结果:" << (registerResult ? "成功" : "失败");
    
    if (!registerResult) {
        qDebug() << "❌ 注册失败";
        return;
    }
    
    // 测试2：验证用户存在
    qDebug() << "\n--- 测试2：验证用户存在 ---";
    bool exists = dbManager.isUserExists(testUser);
    qDebug() << "用户存在:" << (exists ? "是" : "否");
    
    // 测试3：登录验证
    qDebug() << "\n--- 测试3：登录验证 ---";
    bool loginResult = dbManager.loginUser(testUser, testPass);
    qDebug() << "登录结果:" << (loginResult ? "成功" : "失败");
    
    // 测试4：重复注册（应该失败）
    qDebug() << "\n--- 测试4：重复注册测试 ---";
    bool duplicateResult = dbManager.registerUser(testUser, "newpassword");
    qDebug() << "重复注册结果:" << (duplicateResult ? "成功（错误）" : "失败（正确）");
    
    // 测试5：错误密码登录（应该失败）
    qDebug() << "\n--- 测试5：错误密码登录 ---";
    bool wrongLoginResult = dbManager.loginUser(testUser, "wrongpassword");
    qDebug() << "错误密码登录:" << (wrongLoginResult ? "成功（错误）" : "失败（正确）");
    
    // 总结
    qDebug() << "\n=== 测试总结 ===";
    qDebug() << "注册功能:" << (registerResult ? "✅" : "❌");
    qDebug() << "用户存在检查:" << (exists ? "✅" : "❌");
    qDebug() << "登录功能:" << (loginResult ? "✅" : "❌");
    qDebug() << "重复注册防护:" << (!duplicateResult ? "✅" : "❌");
    qDebug() << "错误密码拒绝:" << (!wrongLoginResult ? "✅" : "❌");
    
    if (registerResult && exists && loginResult && !duplicateResult && !wrongLoginResult) {
        qDebug() << "🎉 所有测试通过！Bug修复成功！";
    } else {
        qDebug() << "❌ 部分测试失败，需要进一步检查";
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    testRegistrationAndLogin();
    
    // 延迟退出
    QTimer::singleShot(1000, &app, &QCoreApplication::quit);
    
    return app.exec();
} 