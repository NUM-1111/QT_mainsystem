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
 * 负责与分系统（如system1）建立TCP连接并发送命令
 * 支持连接状态监控、命令发送、响应接收等功能
 */
class SubsystemClient : public QObject
{
    Q_OBJECT

public:
    explicit SubsystemClient(QObject *parent = nullptr);
    ~SubsystemClient();

    /**
     * @brief 连接到分系统
     * @param host 主机地址，默认localhost
     * @param port 端口号，默认8080
     * @return 是否成功发起连接
     */
    bool connectToSubsystem(const QString &host = "localhost", quint16 port = 8080);

    /**
     * @brief 断开与分系统的连接
     */
    void disconnectFromSubsystem();

    /**
     * @brief 发送命令到分系统
     * @param command 命令字符串
     * @return 是否成功发送
     */
    bool sendCommand(const QString &command);

    /**
     * @brief 检查是否已连接
     * @return 连接状态
     */
    bool isConnected() const;

    /**
     * @brief 获取连接状态字符串
     * @return 状态描述
     */
    QString getConnectionStatus() const;

    /**
     * @brief 获取最后收到的响应
     * @return 响应内容
     */
    QString getLastResponse() const;

signals:
    /**
     * @brief 连接成功信号
     */
    void connected();

    /**
     * @brief 连接断开信号
     */
    void disconnected();

    /**
     * @brief 连接错误信号
     * @param errorString 错误信息
     */
    void connectionError(const QString &errorString);

    /**
     * @brief 收到响应信号
     * @param response 响应内容
     */
    void responseReceived(const QString &response);

    /**
     * @brief 命令发送成功信号
     * @param command 发送的命令
     */
    void commandSent(const QString &command);

    /**
     * @brief 命令发送失败信号
     * @param command 失败的命令
     * @param errorString 错误信息
     */
    void commandFailed(const QString &command, const QString &errorString);

private slots:
    /**
     * @brief 处理连接成功
     */
    void handleConnected();

    /**
     * @brief 处理连接断开
     */
    void handleDisconnected();

    /**
     * @brief 处理连接错误
     * @param error 错误类型
     */
    void handleError(QAbstractSocket::SocketError error);

    /**
     * @brief 处理数据接收
     */
    void handleReadyRead();

private:
    QTcpSocket *m_socket;           ///< TCP套接字
    QString m_lastResponse;         ///< 最后收到的响应
    QString m_connectionStatus;     ///< 连接状态描述
    bool m_isConnected;             ///< 连接状态
    QTimer *m_reconnectTimer;       ///< 重连定时器
    QString m_host;                 ///< 主机地址
    quint16 m_port;                 ///< 端口号
};

#endif // SUBSYSTEMCLIENT_H
