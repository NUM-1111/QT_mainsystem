#ifndef USERMANAGER_H
#define USERMANAGER_H

#include "struct.h"
#include <QVector>

class UserManager {
public:
    // 添加用户
    static bool addUser(const User& user);
    // 删除用户
    static bool deleteUser(int user_id);
    // 修改用户信息（包括权限组、特权等）
    static bool updateUser(const User& user);
    // 查询所有用户
    static QVector<User> getAllUsers();
    // 根据ID查询单个用户
    static bool getUserById(int user_id, User& user);
    // 根据用户名查询单个用户
    static bool getUserByName(const QString& username, User& user);
    static User currentUser;
    static void setCurrentUser(const User& user) { currentUser = user; }
    static User getCurrentUser() { return currentUser; }
};

#endif // USERMANAGER_H
