/**
 * @file SubsystemManager.h
 * @brief 子系统管理器头文件，负责管理所有子系统客户端
 */

#ifndef SUBSYSTEMMANAGER_H
#define SUBSYSTEMMANAGER_H

#include <QObject>
#include <QMap>
#include "SubsystemClient.h"
#include "SubsystemInfo.h"

/**
 * @brief 子系统管理类
 * 
 * 负责管理所有子系统客户端的生命周期和通信
 */
class SubsystemManager : public QObject
{
    Q_OBJECT
public:
    explicit SubsystemManager(QObject *parent = nullptr);

    /**
     * @brief 注册子系统信息
     * @param info 子系统信息对象
     */
    void registerSubsystem(const SubsystemInfo& info);

    bool getSubsystemInfo(const QString& name, SubsystemInfo& info);

private:
    QMap<QString, SubsystemClient*> m_clients;  ///< 子系统客户端映射表
    QMap<QString, SubsystemInfo> m_infos;      ///< 子系统信息映射表
};

#endif // SUBSYSTEMMANAGER_H
