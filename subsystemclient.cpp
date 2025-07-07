#include "subsystemclient.h"
#include <QHostAddress>

/**
 * @brief 构造函数 - 初始化TCP客户端
 * @param parent 父对象指针
 * 
 * 这是Qt TCP客户端编程的初始化阶段，主要完成以下工作：
 * 1. 创建QTcpSocket对象
 * 2. 设置信号槽连接（这是Qt异步编程的核心）
 * 3. 创建重连定时器
 * 4. 初始化状态变量
 */
SubsystemClient::SubsystemClient(QObject *parent)
    : QObject(parent)
    , m_socket(nullptr)
    , m_isConnected(false)
    , m_port(8080)
    , m_reconnectTimer(nullptr)
{
    // 创建TCP套接字对象
    // QTcpSocket是Qt提供的TCP客户端套接字类
    // 它继承自QAbstractSocket，提供了完整的TCP客户端功能
    m_socket = new QTcpSocket(this);
    
    // ===== 信号槽连接设置 =====
    // 这是Qt异步编程的核心机制，用于处理网络事件
    
    // 连接成功信号：当TCP连接建立成功时发出
    // 参数说明：信号源对象，信号函数，接收对象，槽函数
    connect(m_socket, &QTcpSocket::connected, this, &SubsystemClient::handleConnected);
    
    // 连接断开信号：当TCP连接断开时发出
    connect(m_socket, &QTcpSocket::disconnected, this, &SubsystemClient::handleDisconnected);
    
    // 错误信号：当连接过程中发生错误时发出
    connect(m_socket, &QTcpSocket::errorOccurred, this, &SubsystemClient::handleError);
    
    // 数据到达信号：当有新的数据可读时发出
    // 这是接收服务器响应的关键信号
    connect(m_socket, &QTcpSocket::readyRead, this, &SubsystemClient::handleReadyRead);
    
    // ===== 重连机制设置 =====
    // 创建单次触发的定时器，用于自动重连
    m_reconnectTimer = new QTimer(this);
    m_reconnectTimer->setSingleShot(true);  // 设置为单次触发，不会重复执行
    
    // 使用lambda表达式连接定时器超时信号
    // 当定时器超时时，如果还未连接，则尝试重新连接
    connect(m_reconnectTimer, &QTimer::timeout, [this]() {
        if (!m_isConnected) {
            qDebug() << "尝试重新连接到分系统...";
            connectToSubsystem(m_host, m_port);
        }
    });
    
    // 初始化连接状态描述
    m_connectionStatus = "未连接";
    
    qDebug() << "SubsystemClient 初始化完成";
}

/**
 * @brief 析构函数 - 清理资源
 * 
 * 负责清理所有网络连接和定时器资源。
 * 由于使用了Qt的父子对象机制，大部分资源会自动清理。
 */
SubsystemClient::~SubsystemClient()
{
    qDebug() << "SubsystemClient 开始销毁...";
    
    // 主动断开连接
    disconnectFromSubsystem();
    
    // 注意：不需要手动删除m_socket和m_reconnectTimer
    // 因为它们都有父对象（this），Qt会自动清理
    qDebug() << "SubsystemClient 销毁完成";
}

/**
 * @brief 连接到分系统服务器
 * @param host 服务器主机地址
 * @param port 服务器端口号
 * @return 是否成功发起连接请求
 * 
 * 重要说明：
 * 1. 这个函数是异步的，它只是发起连接请求
 * 2. 实际的连接结果会通过信号通知（connected或connectionError）
 * 3. 如果已经连接，会直接返回true，不会重复连接
 */
bool SubsystemClient::connectToSubsystem(const QString &host, quint16 port)
{
    // 检查是否已经连接，避免重复连接
    if (m_isConnected) {
        qDebug() << "已经连接到分系统，无需重复连接";
        return true;
    }
    
    // 保存连接参数，供重连时使用
    m_host = host;
    m_port = port;
    m_connectionStatus = "正在连接...";
    
    qDebug() << "正在连接到分系统:" << host << ":" << port;
    
    // 发起TCP连接
    // connectToHost是异步操作，不会阻塞当前线程
    // 连接结果会通过信号通知
    m_socket->connectToHost(host, port);
    
    // 返回true表示连接请求已发起
    // 注意：这不表示连接已经成功
    return true;
}

/**
 * @brief 断开与分系统的连接
 * 
 * 主动断开TCP连接，停止重连定时器。
 * 断开后会自动发出disconnected信号。
 */
void SubsystemClient::disconnectFromSubsystem()
{
    // 检查是否已连接，避免重复断开
    if (!m_isConnected) {
        return;
    }
    
    qDebug() << "断开与分系统的连接";
    
    // 停止重连定时器，防止在断开后自动重连
    m_reconnectTimer->stop();
    
    // 断开TCP连接
    // disconnectFromHost会优雅地关闭连接
    m_socket->disconnectFromHost();
    
    // 更新内部状态
    m_isConnected = false;
    m_connectionStatus = "已断开";
}

/**
 * @brief 发送命令到分系统
 * @param command 要发送的命令字符串
 * @return 是否成功发送
 * 
 * 发送过程详解：
 * 1. 检查连接状态
 * 2. 将字符串转换为UTF-8字节数组
 * 3. 通过TCP socket发送数据
 * 4. 验证发送的字节数
 * 5. 发出相应的信号
 */
bool SubsystemClient::sendCommand(const QString &command)
{
    // 检查连接状态，未连接时无法发送
    if (!m_isConnected) {
        QString errorMsg = "未连接到分系统，无法发送命令";
        qDebug() << errorMsg;
        emit commandFailed(command, errorMsg);
        return false;
    }
    
    // 将字符串转换为UTF-8字节数组
    // TCP传输的是字节流，需要将字符串编码为字节
    QByteArray data = command.toUtf8();
    
    // 通过TCP socket发送数据
    // write函数返回实际写入的字节数
    qint64 bytesWritten = m_socket->write(data);
    
    // 验证发送是否完整
    if (bytesWritten == data.size()) {
        // 发送成功
        qDebug() << "命令发送成功:" << command;
        emit commandSent(command);
        return true;
    } else {
        // 发送不完整
        QString errorMsg = QString("命令发送失败，已发送 %1/%2 字节").arg(bytesWritten).arg(data.size());
        qDebug() << errorMsg;
        emit commandFailed(command, errorMsg);
        return false;
    }
}

/**
 * @brief 检查是否已连接到服务器
 * @return 连接状态
 * 
 * 这个状态是客户端内部维护的，用于业务逻辑判断。
 * 注意：这个状态可能与实际的网络连接状态略有不同。
 */
bool SubsystemClient::isConnected() const
{
    return m_isConnected;
}

/**
 * @brief 获取连接状态的文字描述
 * @return 状态描述字符串
 * 
 * 提供用户友好的状态描述，用于界面显示。
 */
QString SubsystemClient::getConnectionStatus() const
{
    return m_connectionStatus;
}

/**
 * @brief 获取最后收到的服务器响应
 * @return 最后一次接收到的响应内容
 * 
 * 主要用于调试和日志记录。
 */
QString SubsystemClient::getLastResponse() const
{
    return m_lastResponse;
}

// ===== 私有槽函数 - 处理Qt信号 =====

/**
 * @brief 处理连接成功事件
 * 
 * 这是QTcpSocket::connected信号的槽函数。
 * 当TCP连接成功建立时，Qt会自动调用此函数。
 */
void SubsystemClient::handleConnected()
{
    // 更新内部连接状态
    m_isConnected = true;
    m_connectionStatus = QString("已连接到 %1:%2").arg(m_host).arg(m_port);
    
    qDebug() << "成功连接到分系统";
    
    // 发出连接成功信号，通知外部对象
    emit connected();
}

/**
 * @brief 处理连接断开事件
 * 
 * 这是QTcpSocket::disconnected信号的槽函数。
 * 当TCP连接断开时，Qt会自动调用此函数。
 */
void SubsystemClient::handleDisconnected()
{
    // 更新内部连接状态
    m_isConnected = false;
    m_connectionStatus = "连接已断开";
    
    qDebug() << "与分系统的连接已断开";
    
    // 发出连接断开信号，通知外部对象
    emit disconnected();
    
    // 启动重连定时器，5秒后自动重连
    // 这是自动重连机制的核心
    m_reconnectTimer->start(5000);
}

/**
 * @brief 处理连接错误事件
 * @param error Qt定义的错误类型枚举
 * 
 * 这是QTcpSocket::errorOccurred信号的槽函数。
 * 当连接过程中发生错误时，Qt会自动调用此函数。
 */
void SubsystemClient::handleError(QAbstractSocket::SocketError error)
{
    // 获取详细的错误信息
    QString errorString = m_socket->errorString();
    m_connectionStatus = QString("连接错误: %1").arg(errorString);
    
    qDebug() << "连接错误:" << errorString;
    
    // 发出连接错误信号，通知外部对象
    emit connectionError(errorString);
}

/**
 * @brief 处理数据接收事件
 * 
 * 这是QTcpSocket::readyRead信号的槽函数。
 * 当有新的数据到达时，Qt会自动调用此函数。
 * 
 * 重要说明：
 * TCP是流式协议，数据可能会分多次到达。
 * 这里使用readAll()读取所有可用数据，实际项目中可能需要
 * 更复杂的数据包解析逻辑。
 */
void SubsystemClient::handleReadyRead()
{
    // 读取所有可用的数据
    // readAll()会读取socket缓冲区中的所有数据
    QByteArray data = m_socket->readAll();
    
    // 将字节数据转换为字符串
    // 假设服务器发送的是UTF-8编码的文本
    QString response = QString::fromUtf8(data).trimmed();
    
    // 保存最后收到的响应
    m_lastResponse = response;
    
    qDebug() << "收到分系统响应:" << response;
    
    // 发出响应接收信号，通知外部对象
    emit responseReceived(response);
}
