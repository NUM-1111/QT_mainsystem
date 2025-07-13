# 主系统与分系统交互说明

## 系统架构

### 主系统 (mainsystem.exe)
- **功能**: 作为控制中心，管理多个分系统
- **组件**: 
  - `MainWindow`: 主界面，提供子系统控制按钮
  - `SubsystemClient`: 子系统客户端，负责与分系统通信
  - 用户管理和权限管理功能

### 分系统1 (system1.exe)
- **功能**: 被控制的子系统，提供具体功能
- **组件**:
  - `TcpServer`: TCP服务端，监听主系统命令
  - `UiManager`: 界面管理器，动态创建界面
  - `MainWindow`: 具体的功能界面

## 交互流程

### 1. 启动流程
```
主系统启动
    ↓
用户点击"启动子系统1"按钮
    ↓
SubsystemClient启动system1.exe进程
    ↓
分系统1启动，启动TCP服务端(端口8080)
    ↓
主系统自动连接到分系统1
    ↓
连接建立，可以发送控制命令
```

### 2. 界面显示流程
```
用户点击"显示子系统1界面"按钮
    ↓
主系统发送"/show_ui"命令
    ↓
分系统1接收命令，创建新的MainWindow
    ↓
新界面显示，用户可以操作
    ↓
可以多次发送命令，创建多个界面
```

## 关键组件详解

### SubsystemClient (主系统端)
```cpp
// 进程管理
bool startSubsystem(const QString &subsystemPath);
void stopSubsystem();
bool isSubsystemRunning() const;

// 网络通信
bool connectToSubsystem(const QString &host, quint16 port);
void disconnectFromSubsystem();
bool isConnected() const;

// 命令发送
bool sendShowUiCommand();
bool sendStatusCommand();
bool sendCommand(const QString &command);
```

### TcpServer (分系统端)
```cpp
// 服务端管理
bool startServer(quint16 port = 8080);
void stopServer();
bool isRunning() const;

// 信号
void showUiRequested();  // 收到显示界面命令
void clientConnected(const QString &clientAddress);
void clientDisconnected(const QString &clientAddress);
```

## 支持的命令

| 命令 | 功能 | 说明 |
|------|------|------|
| `/show_ui` | 显示界面 | 创建新的MainWindow界面 |
| `/status` | 查询状态 | 返回分系统运行状态 |
| `/help` | 帮助信息 | 返回支持的命令列表 |

## 状态管理

### 主系统状态
- `m_isSubsystem1Running`: 分系统1是否运行
- `m_isSubsystem1Connected`: 是否已连接到分系统1

### 按钮状态变化
1. **未运行**: 按钮显示"启动子系统1"
2. **运行中，未连接**: 按钮显示"连接子系统1"
3. **已连接**: 按钮显示"显示子系统1界面"

## 错误处理

### 常见错误及处理
1. **进程启动失败**: 检查分系统路径是否正确
2. **连接失败**: 检查分系统是否已启动，端口是否被占用
3. **命令发送失败**: 检查网络连接状态
4. **分系统崩溃**: 自动检测并更新状态

### 日志输出
- 所有操作都有详细的日志输出
- 错误信息会显示在状态栏和弹窗中
- 调试信息输出到控制台

## 测试方法

### 1. 编译
```bash
# 编译分系统1
cd system1
qmake system1.pro
mingw32-make

# 编译主系统
cd ../mainsystem
qmake mainsystem.pro
mingw32-make
```

### 2. 运行测试
1. 启动主系统
2. 点击"启动子系统1"按钮
3. 等待连接建立
4. 点击"显示子系统1界面"按钮
5. 观察分系统1是否显示界面

### 3. 验证要点
- [ ] 分系统1成功启动
- [ ] 主系统成功连接到分系统1
- [ ] 发送命令后分系统1正确响应
- [ ] 界面正确显示
- [ ] 可以多次创建界面

## 扩展说明

### 添加新的分系统
1. 创建新的分系统项目
2. 实现TcpServer和命令处理
3. 在主系统中添加对应的SubsystemClient
4. 添加控制按钮和事件处理

### 添加新的命令
1. 在分系统端添加命令处理逻辑
2. 在主系统端添加命令发送函数
3. 更新UI和状态管理

## 注意事项

1. **路径配置**: 确保分系统路径配置正确
2. **端口冲突**: 避免多个分系统使用相同端口
3. **资源管理**: 及时清理不需要的界面和连接
4. **错误恢复**: 实现自动重连和错误恢复机制 