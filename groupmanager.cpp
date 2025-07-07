#include "groupmanager.h"
#include "databasemanager.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

/**
 * @brief 添加权限组
 *
 * 1. 获取数据库连接。
 * 2. 构造SQL插入语句，将group_id、group_name和5个权限字段插入groups表。
 * 3. 执行SQL语句，返回是否成功。
 */
bool GroupManager::addGroup(const Group& group) {
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    query.prepare("INSERT INTO groups (group_id, group_name, isRightToSystem1, isRightToSystem2, isRightToSystem3, isRightToSystem4, isRightToSystem5) VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(group.group_id);
    query.addBindValue(group.group_name);
    for (int i = 0; i < 5; ++i) {
        query.addBindValue(group.rights.isRightToSystem[i] ? 1 : 0);
    }
    if (!query.exec()) {
        qDebug() << "Failed to add group:" << query.lastError().text();
        return false;
    }
    return true;
}

/**
 * @brief 删除权限组
 *
 * 1. 获取数据库连接。
 * 2. 构造SQL删除语句，根据group_id删除groups表中的记录。
 * 3. 执行SQL语句，返回是否成功。
 */
bool GroupManager::deleteGroup(int group_id) {
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    query.prepare("DELETE FROM groups WHERE group_id = ?");
    query.addBindValue(group_id);
    if (!query.exec()) {
        qDebug() << "Failed to delete group:" << query.lastError().text();
        return false;
    }
    return true;
}

/**
 * @brief 修改权限组
 *
 * 1. 获取数据库连接。
 * 2. 构造SQL更新语句，根据group_id更新组名和5个权限字段。
 * 3. 执行SQL语句，返回是否成功。
 */
bool GroupManager::updateGroup(const Group& group) {
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    query.prepare("UPDATE groups SET group_name = ?, isRightToSystem1 = ?, isRightToSystem2 = ?, isRightToSystem3 = ?, isRightToSystem4 = ?, isRightToSystem5 = ? WHERE group_id = ?");
    query.addBindValue(group.group_name);
    for (int i = 0; i < 5; ++i) {
        query.addBindValue(group.rights.isRightToSystem[i] ? 1 : 0);
    }
    query.addBindValue(group.group_id);
    if (!query.exec()) {
        qDebug() << "Failed to update group:" << query.lastError().text();
        return false;
    }
    return true;
}

/**
 * @brief 查询所有权限组
 *
 * 1. 获取数据库连接。
 * 2. 执行SQL查询，获取groups表所有记录。
 * 3. 遍历结果集，将每条记录转换为Group结构体并加入返回列表。
 */
QVector<Group> GroupManager::getAllGroups() {
    QVector<Group> groups;
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return groups;
    QSqlQuery query(db);
    if (!query.exec("SELECT group_id, group_name, isRightToSystem1, isRightToSystem2, isRightToSystem3, isRightToSystem4, isRightToSystem5 FROM groups")) {
        qDebug() << "Failed to query all groups:" << query.lastError().text();
        return groups;
    }
    while (query.next()) {
        Group group;
        group.group_id = query.value(0).toInt();
        group.group_name = query.value(1).toString();
        for (int i = 0; i < 5; ++i) {
            group.rights.isRightToSystem[i] = query.value(2 + i).toInt() != 0;
        }
        groups.append(group);
    }
    return groups;
}

/**
 * @brief 查询单个权限组
 *
 * 1. 获取数据库连接。
 * 2. 构造SQL查询语句，根据group_id查找groups表。
 * 3. 如果找到，填充Group结构体并返回true，否则返回false。
 */
bool GroupManager::getGroupById(int group_id, Group& group) {
    QSqlDatabase db = DatabaseManager::getInstance().getDatabase();
    if (!db.isOpen()) return false;
    QSqlQuery query(db);
    query.prepare("SELECT group_id, group_name, isRightToSystem1, isRightToSystem2, isRightToSystem3, isRightToSystem4, isRightToSystem5 FROM groups WHERE group_id = ?");
    query.addBindValue(group_id);
    if (!query.exec() || !query.next()) {
        qDebug() << "Failed to get group by id:" << query.lastError().text();
        return false;
    }
    group.group_id = query.value(0).toInt();
    group.group_name = query.value(1).toString();
    for (int i = 0; i < 5; ++i) {
        group.rights.isRightToSystem[i] = query.value(2 + i).toInt() != 0;
    }
    return true;
}
