# 权限管理系统说明

## 🎯 系统概述

本权限管理系统实现了基于权限组和个人权限限制的细粒度访问控制，满足以下需求：

1. **用户默认无权限** - 新用户创建后没有任何权限
2. **权限组管理** - 管理员可以将用户移入权限组1或2
3. **权限组权限**：
   - 权限组1：能访问分系统1-3
   - 权限组2：能访问分系统4-5
4. **个人权限覆盖** - 管理员可以单独控制用户权限，覆盖权限组权限
5. **UI权限控制** - 通过按钮是否可点击（变灰）来区分权限

## 🏗️ 系统架构

### 数据结构设计

#### RightToSystem 权限结构
```cpp
struct RightToSystem {
    std::array<bool, 5> isRightToSystem; // 5个分系统的权限
    
    // 权限计算：组权限 - 个人限制
    RightToSystem operator-(const RightToSystem& restrictions) const;
};
```

#### User 用户结构
```cpp
struct User {
    int id;
    QString name;
    QString password;
    int group; // 0:管理员, 1:权限组1, 2:权限组2, -1:无权限
    RightToSystem rights; // 个人限制权限
    RightToSystem finalRights; // 最终计算权限
    
    void calculateFinalRights(const RightToSystem& groupRights);
    bool canAccessSubsystem(int subsystemId) const;
};
```

#### Group 权限组结构
```cpp
struct Group {
    int group_id; // 1, 2
    QString group_name;
    RightToSystem rights; // 组默认权限
    
    void setDefaultPermissions(); // 设置默认权限
};
```

### 权限计算逻辑

```
用户最终权限 = 权限组权限 - 个人限制权限
```

**示例场景**：
1. 用户1在权限组1（可访问分系统1-3）
2. 管理员特别禁止用户1访问分系统2
3. 最终权限：可访问分系统1、3，不可访问分系统2

## 🖥️ 界面功能

### 主界面权限控制

- **动态按钮状态**：根据用户权限自动启用/禁用按钮
- **视觉反馈**：无权限的按钮变灰显示
- **实时更新**：权限变化时按钮状态自动更新

### 权限管理界面

#### 用户列表区域
- **用户信息显示**：ID、用户名、权限组、当前状态
- **权限状态预览**：显示用户最终可访问的分系统
- **操作按钮**：刷新、添加、删除用户

#### 权限设置区域
- **权限组分配**：下拉选择权限组1或2
- **个人权限限制**：复选框控制每个分系统的访问权限
- **实时预览**：显示用户最终权限效果
- **保存/重置**：保存设置或重置为原始状态

## 🔧 核心功能实现

### 1. 权限计算引擎

```cpp
void User::calculateFinalRights(const RightToSystem& groupRights) {
    if (group == 0) {
        // 管理员拥有所有权限
        finalRights.isRightToSystem.fill(true);
    } else if (group > 0) {
        // 普通用户：组权限 - 个人限制
        finalRights = groupRights - rights;
    } else {
        // 无权限组用户
        finalRights.isRightToSystem.fill(false);
    }
}
```

### 2. 权限组默认设置

```cpp
void Group::setDefaultPermissions() {
    if (group_id == 1) {
        // 权限组1：能访问分系统1-3
        rights.setSubsystemRight(0, true); // 分系统1
        rights.setSubsystemRight(1, true); // 分系统2
        rights.setSubsystemRight(2, true); // 分系统3
        rights.setSubsystemRight(3, false); // 分系统4
        rights.setSubsystemRight(4, false); // 分系统5
    } else if (group_id == 2) {
        // 权限组2：能访问分系统4-5
        rights.setSubsystemRight(0, false); // 分系统1
        rights.setSubsystemRight(1, false); // 分系统2
        rights.setSubsystemRight(2, false); // 分系统3
        rights.setSubsystemRight(3, true); // 分系统4
        rights.setSubsystemRight(4, true); // 分系统5
    }
}
```

### 3. 界面权限控制

```cpp
void MainWindow::applyPermissionControl() {
    // 根据用户权限控制按钮状态
    ui->btnSubsystem1->setEnabled(currentUser.canAccessSubsystem(0));
    ui->btnSubsystem2->setEnabled(currentUser.canAccessSubsystem(1));
    ui->btnSubsystem3->setEnabled(currentUser.canAccessSubsystem(2));
    ui->btnSubsystem4->setEnabled(currentUser.canAccessSubsystem(3));
    ui->btnSubsystem5->setEnabled(currentUser.canAccessSubsystem(4));
    
    // 管理员功能控制
    bool isAdmin = (currentUser.group == 0);
    ui->btnViewUsers->setEnabled(isAdmin);
    ui->btnViewGroups->setEnabled(isAdmin);
}
```

## 📊 权限矩阵

| 用户类型 | 分系统1 | 分系统2 | 分系统3 | 分系统4 | 分系统5 | 管理功能 |
|----------|---------|---------|---------|---------|---------|----------|
| 管理员 | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| 权限组1 | ✅ | ✅ | ✅ | ❌ | ❌ | ❌ |
| 权限组2 | ❌ | ❌ | ❌ | ✅ | ✅ | ❌ |
| 无权限组 | ❌ | ❌ | ❌ | ❌ | ❌ | ❌ |

## 🎮 使用流程

### 管理员操作流程

1. **登录系统** - 使用管理员账号登录
2. **进入权限管理** - 点击"查看所有用户信息"按钮
3. **选择用户** - 在用户列表中点击要管理的用户
4. **设置权限组** - 在下拉菜单中选择权限组1或2
5. **设置个人限制** - 勾选要禁止访问的分系统
6. **预览效果** - 查看最终权限预览
7. **保存设置** - 点击"保存权限设置"按钮

### 用户使用流程

1. **登录系统** - 使用普通用户账号登录
2. **查看可用功能** - 只有有权限的按钮才会启用
3. **使用分系统** - 点击可用的分系统按钮进行操作

## 🔍 权限验证示例

### 场景1：权限组1用户
- **权限组权限**：可访问分系统1-3
- **个人限制**：禁止访问分系统2
- **最终权限**：可访问分系统1、3

### 场景2：权限组2用户
- **权限组权限**：可访问分系统4-5
- **个人限制**：无
- **最终权限**：可访问分系统4、5

### 场景3：管理员用户
- **权限组权限**：所有权限
- **个人限制**：忽略
- **最终权限**：可访问所有分系统

## 🛠️ 扩展功能

### 1. 添加新的权限组
```cpp
// 在Group::setDefaultPermissions()中添加
else if (group_id == 3) {
    // 权限组3：自定义权限
    rights.setSubsystemRight(0, true);  // 分系统1
    rights.setSubsystemRight(1, false); // 分系统2
    rights.setSubsystemRight(2, true);  // 分系统3
    rights.setSubsystemRight(3, false); // 分系统4
    rights.setSubsystemRight(4, true);  // 分系统5
}
```

### 2. 添加新的分系统
```cpp
// 修改RightToSystem结构
std::array<bool, 6> isRightToSystem; // 扩展到6个分系统
```

### 3. 权限继承机制
```cpp
// 可以实现权限组继承
struct Group {
    int parent_group_id; // 父权限组ID
    RightToSystem inherited_rights; // 继承的权限
};
```

## ⚠️ 注意事项

1. **权限缓存** - 权限变化后需要刷新界面状态
2. **数据一致性** - 确保数据库中的权限数据与界面显示一致
3. **安全性** - 权限验证应该在服务端进行，客户端仅用于显示
4. **性能优化** - 大量用户时考虑权限计算的性能优化
5. **日志记录** - 记录权限变更操作，便于审计

## 🧪 测试建议

### 功能测试
- [ ] 权限组分配功能
- [ ] 个人权限限制功能
- [ ] 权限计算准确性
- [ ] 界面状态同步
- [ ] 数据持久化

### 边界测试
- [ ] 无权限组用户
- [ ] 管理员权限覆盖
- [ ] 权限冲突处理
- [ ] 数据异常处理

### 用户体验测试
- [ ] 界面响应速度
- [ ] 操作流程合理性
- [ ] 错误提示友好性
- [ ] 权限预览准确性 