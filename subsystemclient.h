#ifndef SUBSYSTEMCLIENT_H
#define SUBSYSTEMCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QTimer>
#include <QDebug>

/**
 * @brief 分系统客户端类
 * 
 * 这个类负责与分系统（如system1）建立TCP连接并发送命令。
 * 它是Qt TCP客户端编程的典型示例，展示了如何使用QTcpSocket进行网络通信。
 * 
 * Qt TCP编程基本概念：
 * 1. QTcpSocket: Qt提供的TCP套接字类，用于客户端连接
 * 2. 信号槽机制: Qt的事件处理机制，用于异步处理网络事件
 * 3. 异步通信: 网络操作是异步的，不会阻塞主线程
 * 4. 状态管理: 需要跟踪连接状态（未连接、连接中、已连接、错误等）
 * 
 * 主要功能：
 * - 建立TCP连接到服务器
 * - 发送命令到服务器
 * - 接收服务器响应
 * - 处理连接状态变化
 * - 自动重连机制
 * - 错误处理和日志记录
 */
class SubsystemClient : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief 构造函数
     * @param parent 父对象指针，用于Qt对象树管理
     * 
     * 在Qt中，所有QObject派生类都应该有父对象，这样Qt会自动管理内存。
     * 当父对象被销毁时，所有子对象也会被自动销毁。
     */
    explicit SubsystemClient(QObject *parent = nullptr);
    
    /**
     * @brief 析构函数
     * 
     * 负责清理资源，断开网络连接，停止定时器等。
     * 由于使用了Qt的父子对象机制，大部分资源会自动清理。
     */
    ~SubsystemClient();

    /**
     * @brief 连接到分系统服务器
     * @param host 服务器主机地址，默认"localhost"（本机）
     * @param port 服务器端口号，默认8080
     * @return 是否成功发起连接请求
     * 
     * 注意：这个函数只是发起连接请求，实际连接是异步的。
     * 连接成功或失败会通过信号通知（connected信号或connectionError信号）。
     * 
     * 常见的host参数：
     * - "localhost" 或 "127.0.0.1": 连接本机
     * - "192.168.1.100": 连接局域网内的特定IP
     * - "example.com": 连接远程服务器
     */
    bool connectToSubsystem(const QString &host = "localhost", quint16 port = 8080);

    /**
     * @brief 断开与分系统的连接
     * 
     * 主动断开TCP连接，停止重连定时器。
     * 断开后会自动发出disconnected信号。
     */
    void disconnectFromSubsystem();

    /**
     * @brief 发送命令到分系统
     * @param command 要发送的命令字符串
     * @return 是否成功发送（仅表示发送请求是否成功，不保证数据到达）
     * 
     * 发送过程：
     * 1. 检查连接状态
     * 2. 将字符串转换为UTF-8字节数组
     * 3. 通过TCP socket发送数据
     * 4. 验证发送的字节数是否正确
     * 5. 发出成功或失败信号
     * 
     * 注意：TCP是流式协议，数据可能会被分割或合并传输。
     * 这里使用简单的字符串传输，实际项目中可能需要更复杂的协议。
     */
    bool sendCommand(const QString &command);

    /**
     * @brief 检查是否已连接到服务器
     * @return 连接状态（true=已连接，false=未连接）
     * 
     * 这个状态是客户端内部维护的，可能与实际的网络连接状态略有不同。
     * 主要用于界面状态更新和业务逻辑判断。
     */
    bool isConnected() const;

    /**
     * @brief 获取连接状态的文字描述
     * @return 状态描述字符串
     * 
     * 可能的状态：
     * - "未连接": 初始状态或连接失败后
     * - "正在连接...": 发起连接请求后
     * - "已连接到 localhost:8080": 连接成功
     * - "连接已断开": 连接断开后
     * - "连接错误: xxx": 发生错误时
     */
    QString getConnectionStatus() const;

    /**
     * @brief 获取最后收到的服务器响应
     * @return 最后一次接收到的响应内容
     * 
     * 这个值在每次收到新响应时会被更新。
     * 主要用于调试和日志记录。
     */
    QString getLastResponse() const;

signals:
    /**
     * @brief 连接成功信号
     * 
     * 当TCP连接成功建立时发出此信号。
     * 接收者可以更新界面状态，启用相关功能等。
     * 
     * 使用示例：
     * connect(client, &SubsystemClient::connected, this, &MainWindow::onConnected);
     */
    void connected();

    /**
     * @brief 连接断开信号
     * 
     * 当TCP连接断开时发出此信号。
     * 可能是主动断开、网络问题或服务器关闭等原因。
     * 
     * 注意：连接断开后，客户端会自动启动重连定时器。
     */
    void disconnected();

    /**
     * @brief 连接错误信号
     * @param errorString 详细的错误信息
     * 
     * 当连接过程中发生错误时发出此信号。
     * 常见的错误：
     * - "Connection refused": 服务器未启动或端口错误
     * - "Network unreachable": 网络不可达
     * - "Host not found": 主机名解析失败
     * - "Connection timed out": 连接超时
     */
    void connectionError(const QString &errorString);

    /**
     * @brief 收到服务器响应信号
     * @param response 服务器返回的响应内容
     * 
     * 每当从服务器接收到数据时发出此信号。
     * 接收者可以解析响应内容，更新界面显示等。
     */
    void responseReceived(const QString &response);

    /**
     * @brief 命令发送成功信号
     * @param command 成功发送的命令内容
     * 
     * 当命令成功发送到网络缓冲区时发出此信号。
     * 注意：这不保证数据已经到达服务器，只是本地发送成功。
     */
    void commandSent(const QString &command);

    /**
     * @brief 命令发送失败信号
     * @param command 发送失败的命令内容
     * @param errorString 失败原因
     * 
     * 当命令发送失败时发出此信号。
     * 常见原因：未连接、网络错误、缓冲区满等。
     */
    void commandFailed(const QString &command, const QString &errorString);

private slots:
    /**
     * @brief 处理连接成功事件
     * 
     * 这是QTcpSocket::connected信号的槽函数。
     * 当TCP连接成功建立时，Qt会自动调用此函数。
     * 
     * 主要工作：
     * 1. 更新内部连接状态
     * 2. 更新连接状态描述
     * 3. 发出connected信号通知外部
     */
    void handleConnected();

    /**
     * @brief 处理连接断开事件
     * 
     * 这是QTcpSocket::disconnected信号的槽函数。
     * 当TCP连接断开时，Qt会自动调用此函数。
     * 
     * 主要工作：
     * 1. 更新内部连接状态
     * 2. 更新连接状态描述
     * 3. 发出disconnected信号通知外部
     * 4. 启动重连定时器（5秒后自动重连）
     */
    void handleDisconnected();

    /**
     * @brief 处理连接错误事件
     * @param error Qt定义的错误类型枚举
     * 
     * 这是QTcpSocket::errorOccurred信号的槽函数。
     * 当连接过程中发生错误时，Qt会自动调用此函数。
     * 
     * 主要工作：
     * 1. 获取详细的错误信息
     * 2. 更新连接状态描述
     * 3. 发出connectionError信号通知外部
     * 
     * 常见的错误类型：
     * - QAbstractSocket::ConnectionRefusedError: 连接被拒绝
     * - QAbstractSocket::RemoteHostClosedError: 远程主机关闭
     * - QAbstractSocket::HostNotFoundError: 主机未找到
     * - QAbstractSocket::SocketTimeoutError: 连接超时
     */
    void handleError(QAbstractSocket::SocketError error);

    /**
     * @brief 处理数据接收事件
     * 
     * 这是QTcpSocket::readyRead信号的槽函数。
     * 当有新的数据到达时，Qt会自动调用此函数。
     * 
     * 主要工作：
     * 1. 读取所有可用的数据
     * 2. 将字节数据转换为字符串
     * 3. 保存最后收到的响应
     * 4. 发出responseReceived信号通知外部
     * 
     * 注意：TCP是流式协议，数据可能会分多次到达。
     * 这里使用readAll()读取所有可用数据，实际项目中可能需要
     * 更复杂的数据包解析逻辑。
     */
    void handleReadyRead();

private:
    QTcpSocket *m_socket;           ///< TCP套接字对象，负责网络通信
    QString m_lastResponse;         ///< 最后收到的服务器响应内容
    QString m_connectionStatus;     ///< 当前连接状态的文字描述
    bool m_isConnected;             ///< 内部维护的连接状态标志
    QTimer *m_reconnectTimer;       ///< 重连定时器，用于自动重连
    QString m_host;                 ///< 服务器主机地址
    quint16 m_port;                 ///< 服务器端口号
};

#endif // SUBSYSTEMCLIENT_H
