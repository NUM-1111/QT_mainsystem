#include "databasemanager.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

/**
 * @brief 数据库功能测试类
 */
class DatabaseTest
{
public:
    /**
     * @brief 运行所有测试
     */
    void runAllTests()
    {
        qDebug() << "=== 开始数据库功能测试 ===";
        
        // 测试1：数据库初始化
        testDatabaseInitialization();
        
        // 测试2：用户注册
        testUserRegistration();
        
        // 测试3：用户存在性检查
        testUserExistence();
        
        // 测试4：用户登录
        testUserLogin();
        
        // 测试5：重复注册测试
        testDuplicateRegistration();
        
        // 测试6：错误密码登录
        testWrongPasswordLogin();
        
        // 测试7：不存在的用户登录
        testNonExistentUserLogin();
        
        qDebug() << "=== 数据库功能测试完成 ===";
    }

private:
    /**
     * @brief 测试数据库初始化
     */
    void testDatabaseInitialization()
    {
        qDebug() << "\n--- 测试1：数据库初始化 ---";
        
        DatabaseManager& dbManager = DatabaseManager::getInstance();
        
        // 测试初始化
        bool initResult = dbManager.initDatabase("test_mainsystem.db");
        qDebug() << "数据库初始化结果:" << (initResult ? "成功" : "失败");
        
        // 测试连接状态
        bool connected = dbManager.isConnected();
        qDebug() << "数据库连接状态:" << (connected ? "已连接" : "未连接");
        
        if (!initResult || !connected) {
            qDebug() << "❌ 数据库初始化测试失败";
        } else {
            qDebug() << "✅ 数据库初始化测试通过";
        }
    }
    
    /**
     * @brief 测试用户注册
     */
    void testUserRegistration()
    {
        qDebug() << "\n--- 测试2：用户注册 ---";
        
        DatabaseManager& dbManager = DatabaseManager::getInstance();
        
        // 测试注册新用户
        QString testUsername = "testuser1";
        QString testPassword = "password123";
        
        bool registerResult = dbManager.registerUser(testUsername, testPassword);
        qDebug() << "注册用户" << testUsername << "结果:" << (registerResult ? "成功" : "失败");
        
        if (registerResult) {
            qDebug() << "✅ 用户注册测试通过";
        } else {
            qDebug() << "❌ 用户注册测试失败";
        }
    }
    
    /**
     * @brief 测试用户存在性检查
     */
    void testUserExistence()
    {
        qDebug() << "\n--- 测试3：用户存在性检查 ---";
        
        DatabaseManager& dbManager = DatabaseManager::getInstance();
        
        QString existingUser = "testuser1";
        QString nonExistingUser = "nonexistentuser";
        
        // 测试存在的用户
        bool exists1 = dbManager.isUserExists(existingUser);
        qDebug() << "用户" << existingUser << "存在性:" << (exists1 ? "存在" : "不存在");
        
        // 测试不存在的用户
        bool exists2 = dbManager.isUserExists(nonExistingUser);
        qDebug() << "用户" << nonExistingUser << "存在性:" << (exists2 ? "存在" : "不存在");
        
        if (exists1 && !exists2) {
            qDebug() << "✅ 用户存在性检查测试通过";
        } else {
            qDebug() << "❌ 用户存在性检查测试失败";
        }
    }
    
    /**
     * @brief 测试用户登录
     */
    void testUserLogin()
    {
        qDebug() << "\n--- 测试4：用户登录 ---";
        
        DatabaseManager& dbManager = DatabaseManager::getInstance();
        
        QString username = "testuser1";
        QString correctPassword = "password123";
        
        // 测试正确密码登录
        bool loginResult = dbManager.loginUser(username, correctPassword);
        qDebug() << "用户" << username << "登录结果:" << (loginResult ? "成功" : "失败");
        
        if (loginResult) {
            qDebug() << "✅ 用户登录测试通过";
        } else {
            qDebug() << "❌ 用户登录测试失败";
        }
    }
    
    /**
     * @brief 测试重复注册
     */
    void testDuplicateRegistration()
    {
        qDebug() << "\n--- 测试5：重复注册测试 ---";
        
        DatabaseManager& dbManager = DatabaseManager::getInstance();
        
        QString username = "testuser1";  // 已存在的用户
        QString password = "newpassword";
        
        // 尝试重复注册
        bool registerResult = dbManager.registerUser(username, password);
        qDebug() << "重复注册用户" << username << "结果:" << (registerResult ? "成功" : "失败");
        
        // 重复注册应该失败
        if (!registerResult) {
            qDebug() << "✅ 重复注册测试通过（正确阻止了重复注册）";
        } else {
            qDebug() << "❌ 重复注册测试失败（不应该允许重复注册）";
        }
    }
    
    /**
     * @brief 测试错误密码登录
     */
    void testWrongPasswordLogin()
    {
        qDebug() << "\n--- 测试6：错误密码登录 ---";
        
        DatabaseManager& dbManager = DatabaseManager::getInstance();
        
        QString username = "testuser1";
        QString wrongPassword = "wrongpassword";
        
        // 测试错误密码登录
        bool loginResult = dbManager.loginUser(username, wrongPassword);
        qDebug() << "用户" << username << "使用错误密码登录结果:" << (loginResult ? "成功" : "失败");
        
        // 错误密码登录应该失败
        if (!loginResult) {
            qDebug() << "✅ 错误密码登录测试通过（正确拒绝了错误密码）";
        } else {
            qDebug() << "❌ 错误密码登录测试失败（不应该接受错误密码）";
        }
    }
    
    /**
     * @brief 测试不存在的用户登录
     */
    void testNonExistentUserLogin()
    {
        qDebug() << "\n--- 测试7：不存在的用户登录 ---";
        
        DatabaseManager& dbManager = DatabaseManager::getInstance();
        
        QString nonExistentUser = "nonexistentuser";
        QString password = "anypassword";
        
        // 测试不存在的用户登录
        bool loginResult = dbManager.loginUser(nonExistentUser, password);
        qDebug() << "不存在用户" << nonExistentUser << "登录结果:" << (loginResult ? "成功" : "失败");
        
        // 不存在的用户登录应该失败
        if (!loginResult) {
            qDebug() << "✅ 不存在用户登录测试通过（正确拒绝了不存在的用户）";
        } else {
            qDebug() << "❌ 不存在用户登录测试失败（不应该接受不存在的用户）";
        }
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    
    // 创建测试实例并运行测试
    DatabaseTest test;
    test.runAllTests();
    
    // 延迟退出，确保所有输出都能看到
    QTimer::singleShot(1000, &app, &QCoreApplication::quit);
    
    return app.exec();
} 