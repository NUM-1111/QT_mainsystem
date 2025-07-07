#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H

#include "struct.h"
#include <QVector>

/**
 * @brief 权限组管理类
 * 提供对groups表的增删查改操作，支持权限组的添加、删除、修改、查询等功能。
 */
class GroupManager {
public:
    /**
     * @brief 添加权限组
     * @param group 权限组结构体，包含组ID、组名和权限
     * @return 是否添加成功
     */
    static bool addGroup(const Group& group);

    /**
     * @brief 删除权限组
     * @param group_id 权限组ID
     * @return 是否删除成功
     */
    static bool deleteGroup(int group_id);

    /**
     * @brief 修改权限组信息（包括权限）
     * @param group 权限组结构体，包含组ID、组名和权限
     * @return 是否修改成功
     */
    static bool updateGroup(const Group& group);

    /**
     * @brief 查询所有权限组
     * @return 权限组列表
     */
    static QVector<Group> getAllGroups();

    /**
     * @brief 根据ID查询单个权限组
     * @param group_id 权限组ID
     * @param group 查询结果存入此结构体
     * @return 是否查询成功
     */
    static bool getGroupById(int group_id, Group& group);
};

#endif // GROUPMANAGER_H
