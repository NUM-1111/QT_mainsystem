#include "permissionmanager.h"
#include <QDebug>

PermissionManager& PermissionManager::getInstance()
{
    static PermissionManager instance;
    return instance;
}

bool PermissionManager::initializeDefaultGroups()
{
    qDebug() << "开始初始化默认权限组...";
    
    bool success = true;
    
    // 检查并创建权限组1
    if (!isGroupExists(1)) {
        qDebug() << "权限组1不存在，正在创建...";
        if (!createDefaultGroup(1)) {
            qDebug() << "创建权限组1失败";
            success = false;
        } else {
            qDebug() << "权限组1创建成功";
        }
    } else {
        qDebug() << "权限组1已存在";
    }
    
    // 检查并创建权限组2
    if (!isGroupExists(2)) {
        qDebug() << "权限组2不存在，正在创建...";
        if (!createDefaultGroup(2)) {
            qDebug() << "创建权限组2失败";
            success = false;
        } else {
            qDebug() << "权限组2创建成功";
        }
    } else {
        qDebug() << "权限组2已存在";
    }
    
    if (success) {
        qDebug() << "默认权限组初始化完成";
    } else {
        qDebug() << "默认权限组初始化失败";
    }
    
    return success;
}

User PermissionManager::calculateUserFinalRights(const User& user)
{
    User result = user;
    
    if (user.group == 0) {
        // 管理员拥有所有权限
        result.finalRights.setAllRights();
        qDebug() << "用户" << user.name << "是管理员，拥有所有权限";
    } else if (user.group > 0) {
        // 普通用户：组权限 - 个人限制
        Group group;
        if (GroupManager::getGroupById(user.group, group)) {
            // 如果权限组没有设置默认权限，则设置
            if (group.group_name.isEmpty()) {
                group.setDefaultPermissions();
            }
            result.calculateFinalRights(group.rights);
            qDebug() << "用户" << user.name << "权限组" << user.group 
                     << "，最终权限：" << result.getFinalRightsDescription();
        } else {
            qDebug() << "用户" << user.name << "权限组" << user.group << "不存在，无权限";
            result.finalRights.clearAllRights();
        }
    } else {
        // 无权限组用户
        result.finalRights.clearAllRights();
        qDebug() << "用户" << user.name << "无权限组，无权限";
    }
    
    return result;
}

bool PermissionManager::canUserAccessSubsystem(const User& user, int subsystemId)
{
    if (subsystemId < 0 || subsystemId >= 5) {
        qDebug() << "无效的分系统ID:" << subsystemId;
        return false;
    }
    
    User userWithRights = calculateUserFinalRights(user);
    bool canAccess = userWithRights.canAccessSubsystem(subsystemId);
    
    qDebug() << "用户" << user.name << "访问分系统" << (subsystemId + 1) 
             << "权限检查结果:" << (canAccess ? "有权限" : "无权限");
    
    return canAccess;
}

QString PermissionManager::getUserRightsDescription(const User& user)
{
    User userWithRights = calculateUserFinalRights(user);
    return userWithRights.getFinalRightsDescription();
}

bool PermissionManager::isGroupExists(int groupId)
{
    Group group;
    return GroupManager::getGroupById(groupId, group);
}

bool PermissionManager::createDefaultGroup(int groupId)
{
    if (groupId != 1 && groupId != 2) {
        qDebug() << "无效的权限组ID:" << groupId;
        return false;
    }
    
    Group group;
    group.group_id = groupId;
    group.setDefaultPermissions();
    
    bool success = GroupManager::addGroup(group);
    if (success) {
        qDebug() << "权限组" << groupId << "创建成功:" << group.getGroupDescription();
    } else {
        qDebug() << "权限组" << groupId << "创建失败";
    }
    
    return success;
} 