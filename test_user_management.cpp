#include <QApplication>
#include <QDebug>
#include "usermanagerdialog.h"
#include "databasemanager.h"
#include "usermanager.h"
#include "groupmanager.h"
#include "permissionmanager.h"

/**
 * @brief 用户管理界面测试程序
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    qDebug() << "=== 用户管理界面测试 ===";
    
    // 初始化数据库
    DatabaseManager& dbManager = DatabaseManager::getInstance();
    if (!dbManager.initDatabase("test_user_management.db")) {
        qDebug() << "❌ 数据库初始化失败";
        return -1;
    }
    
    // 初始化权限管理器（创建默认权限组）
    PermissionManager::getInstance().initializeDefaultGroups();
    
    // 创建一些测试用户
    qDebug() << "创建测试用户...";
    
    // 创建管理员用户
    User adminUser;
    adminUser.id = 1;
    adminUser.name = "admin";
    adminUser.password = "admin123";
    adminUser.group = 0; // 管理员
    UserManager::addUser(adminUser);
    
    // 创建权限组1用户
    User user1;
    user1.id = 2;
    user1.name = "user1";
    user1.password = "user123";
    user1.group = 1; // 权限组1
    user1.rights.setSubsystemRight(1, true); // 禁止访问分系统2
    UserManager::addUser(user1);
    
    // 创建权限组2用户
    User user2;
    user2.id = 3;
    user2.name = "user2";
    user2.password = "user123";
    user2.group = 2; // 权限组2
    user2.rights.setSubsystemRight(3, true); // 禁止访问分系统4
    UserManager::addUser(user2);
    
    // 创建无权限用户
    User user3;
    user3.id = 4;
    user3.name = "user3";
    user3.password = "user123";
    user3.group = -1; // 无权限组
    UserManager::addUser(user3);
    
    qDebug() << "✅ 测试用户创建完成";
    
    // 显示用户管理界面
    qDebug() << "打开用户管理界面...";
    UserManagerDialog dialog;
    dialog.show();
    
    qDebug() << "用户管理界面已打开，请测试以下功能：";
    qDebug() << "1. 查看用户列表";
    qDebug() << "2. 选择不同用户查看权限设置";
    qDebug() << "3. 修改权限组和个人权限限制";
    qDebug() << "4. 查看权限预览效果";
    qDebug() << "5. 保存权限设置";
    
    return app.exec();
} 