#ifndef PERMISSIONMANAGER_H
#define PERMISSIONMANAGER_H

#include "struct.h"
#include "usermanager.h"
#include "groupmanager.h"
#include <QObject>

/**
 * @brief 权限管理工具类
 * 
 * 负责权限组的初始化、权限计算和权限验证等功能
 */
class PermissionManager : public QObject
{
    Q_OBJECT

public:
    static PermissionManager& getInstance();
    
    /**
     * @brief 初始化默认权限组
     * 检查权限组1和2是否存在，不存在则创建
     */
    bool initializeDefaultGroups();
    
    /**
     * @brief 计算用户的最终权限
     * @param user 用户对象
     * @return 计算后的用户对象（包含最终权限）
     */
    User calculateUserFinalRights(const User& user);
    
    /**
     * @brief 验证用户是否有访问特定分系统的权限
     * @param user 用户对象
     * @param subsystemId 分系统ID（0-4）
     * @return 是否有权限
     */
    bool canUserAccessSubsystem(const User& user, int subsystemId);
    
    /**
     * @brief 获取用户权限描述
     * @param user 用户对象
     * @return 权限描述字符串
     */
    QString getUserRightsDescription(const User& user);
    
    /**
     * @brief 检查权限组是否存在
     * @param groupId 权限组ID
     * @return 是否存在
     */
    bool isGroupExists(int groupId);
    
    /**
     * @brief 创建默认权限组
     * @param groupId 权限组ID（1或2）
     * @return 是否创建成功
     */
    bool createDefaultGroup(int groupId);

private:
    PermissionManager() = default;
    ~PermissionManager() = default;
    PermissionManager(const PermissionManager&) = delete;
    PermissionManager& operator=(const PermissionManager&) = delete;
};

#endif // PERMISSIONMANAGER_H 