#include "subsystemclient.h"
#include <QHostAddress>

SubsystemClient::SubsystemClient(QObject *parent)
    : QObject(parent)
    , m_socket(nullptr)
    , m_isConnected(false)
    , m_port(8080)
    , m_reconnectTimer(nullptr)
{
    // 创建TCP套接字
    m_socket = new QTcpSocket(this);
    
    // 连接信号和槽
    connect(m_socket, &QTcpSocket::connected, this, &SubsystemClient::handleConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &SubsystemClient::handleDisconnected);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &SubsystemClient::handleError);
    connect(m_socket, &QTcpSocket::readyRead, this, &SubsystemClient::handleReadyRead);
    
    // 创建重连定时器
    m_reconnectTimer = new QTimer(this);
    m_reconnectTimer->setSingleShot(true);
    connect(m_reconnectTimer, &QTimer::timeout, [this]() {
        if (!m_isConnected) {
            qDebug() << "尝试重新连接到分系统...";
            connectToSubsystem(m_host, m_port);
        }
    });
    
    m_connectionStatus = "未连接";
}

SubsystemClient::~SubsystemClient()
{
    disconnectFromSubsystem();
}

bool SubsystemClient::connectToSubsystem(const QString &host, quint16 port)
{
    if (m_isConnected) {
        qDebug() << "已经连接到分系统，无需重复连接";
        return true;
    }
    
    m_host = host;
    m_port = port;
    m_connectionStatus = "正在连接...";
    
    qDebug() << "正在连接到分系统:" << host << ":" << port;
    
    // 发起连接
    m_socket->connectToHost(host, port);
    
    return true;
}

void SubsystemClient::disconnectFromSubsystem()
{
    if (!m_isConnected) {
        return;
    }
    
    qDebug() << "断开与分系统的连接";
    
    // 停止重连定时器
    m_reconnectTimer->stop();
    
    // 断开连接
    m_socket->disconnectFromHost();
    
    m_isConnected = false;
    m_connectionStatus = "已断开";
}

bool SubsystemClient::sendCommand(const QString &command)
{
    if (!m_isConnected) {
        QString errorMsg = "未连接到分系统，无法发送命令";
        qDebug() << errorMsg;
        emit commandFailed(command, errorMsg);
        return false;
    }
    
    QByteArray data = command.toUtf8();
    qint64 bytesWritten = m_socket->write(data);
    
    if (bytesWritten == data.size()) {
        qDebug() << "命令发送成功:" << command;
        emit commandSent(command);
        return true;
    } else {
        QString errorMsg = QString("命令发送失败，已发送 %1/%2 字节").arg(bytesWritten).arg(data.size());
        qDebug() << errorMsg;
        emit commandFailed(command, errorMsg);
        return false;
    }
}

bool SubsystemClient::isConnected() const
{
    return m_isConnected;
}

QString SubsystemClient::getConnectionStatus() const
{
    return m_connectionStatus;
}

QString SubsystemClient::getLastResponse() const
{
    return m_lastResponse;
}

void SubsystemClient::handleConnected()
{
    m_isConnected = true;
    m_connectionStatus = QString("已连接到 %1:%2").arg(m_host).arg(m_port);
    
    qDebug() << "成功连接到分系统";
    emit connected();
}

void SubsystemClient::handleDisconnected()
{
    m_isConnected = false;
    m_connectionStatus = "连接已断开";
    
    qDebug() << "与分系统的连接已断开";
    emit disconnected();
    
    // 启动重连定时器（5秒后重连）
    m_reconnectTimer->start(5000);
}

void SubsystemClient::handleError(QAbstractSocket::SocketError error)
{
    QString errorString = m_socket->errorString();
    m_connectionStatus = QString("连接错误: %1").arg(errorString);
    
    qDebug() << "连接错误:" << errorString;
    emit connectionError(errorString);
}

void SubsystemClient::handleReadyRead()
{
    QByteArray data = m_socket->readAll();
    QString response = QString::fromUtf8(data).trimmed();
    
    m_lastResponse = response;
    
    qDebug() << "收到分系统响应:" << response;
    emit responseReceived(response);
}
