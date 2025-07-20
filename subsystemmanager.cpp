#include "SubsystemManager.h"

/**
 * @brief 构造函数
 * @param parent 父对象指针
 */
SubsystemManager::SubsystemManager(QObject *parent) : QObject(parent) {}

/**
 * @brief 注册子系统信息
 * @param info 子系统信息对象
 * 
 * 将子系统信息添加到管理器的信息映射表中
 */
void SubsystemManager::registerSubsystem(const SubsystemInfo &info)
{
    m_infos[info.name] = info;
}


bool SubsystemManager::getSubsystemInfo(const QString &name, SubsystemInfo &info)
{
    if (!m_infos.contains(name))
        return false;
    info = m_infos[name];
    return true;
}

