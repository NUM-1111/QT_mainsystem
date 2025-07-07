#include "usermanager.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

// 添加用户
bool UserManager::addUser(const User& user) {
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    query.prepare("INSERT INTO users (username, password, `group`, isRightToSystem1, isRightToSystem2, isRightToSystem3, isRightToSystem4, isRightToSystem5) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(user.name);
    query.addBindValue(user.password);
    query.addBindValue(user.group);
    for (int i = 0; i < 5; ++i) {
        query.addBindValue(user.rights.isRightToSystem[i] ? 1 : 0);
    }
    if (!query.exec()) {
        qDebug() << "Failed to add user:" << query.lastError().text();
        return false;
    }
    return true;
}

// 删除用户
bool UserManager::deleteUser(int user_id) {
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    query.prepare("DELETE FROM users WHERE id = ?");
    query.addBindValue(user_id);
    if (!query.exec()) {
        qDebug() << "Failed to delete user:" << query.lastError().text();
        return false;
    }
    return true;
}

// 修改用户信息
bool UserManager::updateUser(const User& user) {
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    query.prepare("UPDATE users SET username = ?, password = ?, `group` = ?, isRightToSystem1 = ?, isRightToSystem2 = ?, isRightToSystem3 = ?, isRightToSystem4 = ?, isRightToSystem5 = ? WHERE id = ?");
    query.addBindValue(user.name);
    query.addBindValue(user.password);
    query.addBindValue(user.group);
    for (int i = 0; i < 5; ++i) {
        query.addBindValue(user.rights.isRightToSystem[i] ? 1 : 0);
    }
    query.addBindValue(user.id);
    if (!query.exec()) {
        qDebug() << "Failed to update user:" << query.lastError().text();
        return false;
    }
    return true;
}

// 查询所有用户
QVector<User> UserManager::getAllUsers() {
    QVector<User> users;
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return users;
    QSqlQuery query(db);
    if (!query.exec("SELECT id, username, password, `group`, isRightToSystem1, isRightToSystem2, isRightToSystem3, isRightToSystem4, isRightToSystem5 FROM users")) {
        qDebug() << "Failed to query all users:" << query.lastError().text();
        return users;
    }
    while (query.next()) {
        User user;
        user.id = query.value(0).toInt();
        user.name = query.value(1).toString();
        user.password = query.value(2).toString();
        user.group = query.value(3).toInt();
        for (int i = 0; i < 5; ++i) {
            user.rights.isRightToSystem[i] = query.value(4 + i).toInt() != 0;
        }
        users.append(user);
    }
    return users;
}

// 根据ID查询单个用户
bool UserManager::getUserById(int user_id, User& user) {
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    query.prepare("SELECT id, username, password, `group`, isRightToSystem1, isRightToSystem2, isRightToSystem3, isRightToSystem4, isRightToSystem5 FROM users WHERE id = ?");
    query.addBindValue(user_id);
    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to get user by id:" << query.lastError().text();
        return false;
    }
    user.id = query.value(0).toInt();
    user.name = query.value(1).toString();
    user.password = query.value(2).toString();
    user.group = query.value(3).toInt();
    for (int i = 0; i < 5; ++i) {
        user.rights.isRightToSystem[i] = query.value(4 + i).toInt() != 0;
    }
    return true;
}

// 根据用户名查询单个用户
bool UserManager::getUserByName(const QString& username, User& user) {
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    query.prepare("SELECT id, username, password, `group`, isRightToSystem1, isRightToSystem2, isRightToSystem3, isRightToSystem4, isRightToSystem5 FROM users WHERE username = ?");
    query.addBindValue(username);
    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to get user by name:" << query.lastError().text();
        return false;
    }
    user.id = query.value(0).toInt();
    user.name = query.value(1).toString();
    user.password = query.value(2).toString();
    user.group = query.value(3).toInt();
    for (int i = 0; i < 5; ++i) {
        user.rights.isRightToSystem[i] = query.value(4 + i).toInt() != 0;
    }
    return true;
}
