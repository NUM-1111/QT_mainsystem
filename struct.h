#ifndef STRUCT_H
#define STRUCT_H

#include <QString>
#include <array>

// 分系统访问权限结构体
struct RightToSystem {
    // isRightToSystem[0] 表示分系统1，依次类推
    std::array<bool, 5> isRightToSystem;

    RightToSystem() {
        isRightToSystem.fill(false);
    }
};

// 用户结构体
struct User {
    int id;
    QString name;
    QString password;
    int group; // 0: 管理员, 1: 权限组1, 2: 权限组2, -1: 无权限
    RightToSystem rights; // 用户特权

    User() : id(-1), group(-1) {}
};

// 权限组结构体
struct Group {
    int group_id; // 1, 2
    QString group_name;
    RightToSystem rights; // 组默认权限

    Group() : group_id(-1) {}
};

#endif // STRUCT_H
