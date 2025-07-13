#ifndef STRUCT_H
#define STRUCT_H

#include <QString>
#include <QStringList>
#include <array>

// 分系统访问权限结构体
struct RightToSystem {
    // isRightToSystem[0] 表示分系统1，依次类推
    std::array<bool, 5> isRightToSystem;

    RightToSystem() {
        isRightToSystem.fill(false);
    }
    
    // 设置特定分系统权限
    void setSubsystemRight(int subsystemId, bool hasRight) {
        if (subsystemId >= 0 && subsystemId < 5) {
            isRightToSystem[subsystemId] = hasRight;
        }
    }
    
    // 获取特定分系统权限
    bool getSubsystemRight(int subsystemId) const {
        if (subsystemId >= 0 && subsystemId < 5) {
            return isRightToSystem[subsystemId];
        }
        return false;
    }
    
    // 权限计算：组权限 - 个人限制权限
    RightToSystem operator-(const RightToSystem& restrictions) const {
        RightToSystem result;
        for (int i = 0; i < 5; ++i) {
            // 最终权限 = 组权限 AND (NOT 个人限制)
            result.isRightToSystem[i] = isRightToSystem[i] && !restrictions.isRightToSystem[i];
        }
        return result;
    }
    
    // 获取可访问的分系统列表
    QStringList getAccessibleSubsystems() const {
        QStringList accessible;
        for (int i = 0; i < 5; ++i) {
            if (isRightToSystem[i]) {
                accessible << QString("分系统%1").arg(i + 1);
            }
        }
        return accessible;
    }
    
    // 获取不可访问的分系统列表
    QStringList getInaccessibleSubsystems() const {
        QStringList inaccessible;
        for (int i = 0; i < 5; ++i) {
            if (!isRightToSystem[i]) {
                inaccessible << QString("分系统%1").arg(i + 1);
            }
        }
        return inaccessible;
    }
    
    // 检查是否有访问特定分系统的权限
    bool canAccessSubsystem(int subsystemId) const {
        return getSubsystemRight(subsystemId);
    }
    
    // 设置所有权限为false
    void clearAllRights() {
        isRightToSystem.fill(false);
    }
    
    // 设置所有权限为true
    void setAllRights() {
        isRightToSystem.fill(true);
    }
};

// 用户结构体
struct User {
    int id;
    QString name;
    QString password;
    int group; // 0: 管理员, 1: 权限组1, 2: 权限组2, -1: 无权限
    RightToSystem rights; // 用户个人限制权限（勾选表示禁止访问）
    RightToSystem finalRights; // 最终计算权限（实际可访问的权限）

    User() : id(-1), group(-1) {}
    
    // 计算最终权限
    void calculateFinalRights(const RightToSystem& groupRights) {
        if (group == 0) {
            // 管理员拥有所有权限
            finalRights.setAllRights();
        } else if (group > 0) {
            // 普通用户：组权限 - 个人限制
            finalRights = groupRights - rights;
        } else {
            // 无权限组用户
            finalRights.clearAllRights();
        }
    }
    
    // 检查是否有访问特定分系统的权限
    bool canAccessSubsystem(int subsystemId) const {
        return finalRights.canAccessSubsystem(subsystemId);
    }
    
    // 获取用户类型描述
    QString getUserTypeDescription() const {
        switch (group) {
            case 0: return "管理员";
            case 1: return "权限组1";
            case 2: return "权限组2";
            case -1: return "无权限组";
            default: return "未知";
        }
    }
    
    // 获取最终权限描述
    QString getFinalRightsDescription() const {
        QStringList accessible = finalRights.getAccessibleSubsystems();
        if (accessible.isEmpty()) {
            return "无权限";
        } else {
            return accessible.join(", ");
        }
    }
};

// 权限组结构体
struct Group {
    int group_id; // 1, 2
    QString group_name;
    RightToSystem rights; // 组默认权限

    Group() : group_id(-1) {}
    
    // 设置权限组默认权限
    void setDefaultPermissions() {
        if (group_id == 1) {
            // 权限组1：能访问分系统1-3
            rights.setSubsystemRight(0, true); // 分系统1
            rights.setSubsystemRight(1, true); // 分系统2
            rights.setSubsystemRight(2, true); // 分系统3
            rights.setSubsystemRight(3, false); // 分系统4
            rights.setSubsystemRight(4, false); // 分系统5
            group_name = "权限组1 (分系统1-3)";
        } else if (group_id == 2) {
            // 权限组2：能访问分系统4-5
            rights.setSubsystemRight(0, false); // 分系统1
            rights.setSubsystemRight(1, false); // 分系统2
            rights.setSubsystemRight(2, false); // 分系统3
            rights.setSubsystemRight(3, true); // 分系统4
            rights.setSubsystemRight(4, true); // 分系统5
            group_name = "权限组2 (分系统4-5)";
        }
    }
    
    // 获取权限组描述
    QString getGroupDescription() const {
        QStringList accessible = rights.getAccessibleSubsystems();
        if (accessible.isEmpty()) {
            return QString("%1 (无权限)").arg(group_name);
        } else {
            return QString("%1 (%2)").arg(group_name).arg(accessible.join(", "));
        }
    }
};

#endif // STRUCT_H
