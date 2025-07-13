#include "subsystemclient.h"
#include <QDebug>
#include <QWidget>

SubsystemClient::SubsystemClient(QObject *parent)
    : QObject(parent)
{
    m_process = nullptr;
    m_socket = nullptr;
    m_isConnected = false;
    m_isSubsystemRunning = false;

    // 初始化网络通信
    m_socket = new QTcpSocket(this);
    connect(m_socket, &QTcpSocket::connected, this, &SubsystemClient::onSocketConnected);
    connect(m_socket, &QTcpSocket::disconnected, this, &SubsystemClient::onSocketDisconnected);
    connect(m_socket, &QTcpSocket::errorOccurred, this, &SubsystemClient::onSocketError);
    connect(m_socket, &QTcpSocket::readyRead, this, &SubsystemClient::onSocketReadyRead);

    // 初始化进程管理
    m_process = new QProcess(this);
    connect(m_process, &QProcess::started, this, &SubsystemClient::onProcessStarted);
    connect(m_process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished), 
            this, &SubsystemClient::onProcessFinished);
    connect(m_process, &QProcess::errorOccurred, this, &SubsystemClient::onProcessError);

    // 初始化子系统运行状态
    m_isSubsystemRunning = false;
    m_isConnected = false;

    // 初始化主机名和端口号
    m_host = "localhost";
    m_port = 8080;

    // 初始化用户窗口映射
    m_userWindows.clear();
}

SubsystemClient::~SubsystemClient()
{
    // 停止子系统
    if (m_isSubsystemRunning) {
        stopSubsystem();
    }
    
    // 断开连接
    if (m_isConnected) {
        disconnectFromSubsystem();
    }
    
    // 清理资源
    if (m_process) {
        m_process->deleteLater();
        m_process = nullptr;
    }
    
    if (m_socket) {
        m_socket->deleteLater();
        m_socket = nullptr;
    }
}

bool SubsystemClient::startSubsystem(const QString &subsystemPath)
{
    if (m_isSubsystemRunning)
    {
        qWarning() << "子系统已运行，无法重复启动";
        return false;
    }
    
    qDebug() << "正在启动子系统:" << subsystemPath;
    m_process->start(subsystemPath);
    return true;
}

void SubsystemClient::stopSubsystem()
{
    if (!m_isSubsystemRunning)
    {
        qWarning() << "子系统未运行，无法停止";
        return;
    }
    
    qDebug() << "正在停止子系统...";
    m_process->terminate();
    
    // 等待进程结束，最多等待5秒
    if (!m_process->waitForFinished(5000)) {
        qWarning() << "子系统未能在5秒内正常结束，强制终止";
        m_process->kill();
    }
}

bool SubsystemClient::isSubsystemRunning() const
{
    return m_isSubsystemRunning;
}

bool SubsystemClient::connectToSubsystem(const QString &host, quint16 port)
{
    if (m_isConnected)
    {
        qWarning() << "已连接到子系统，无法重复连接";
        return false;
    }
    
    m_host = host;
    m_port = port;
    
    qDebug() << "正在连接到子系统:" << host << ":" << port;
    m_socket->connectToHost(host, port);
    return true;
}

void SubsystemClient::disconnectFromSubsystem()
{
    if (!m_isConnected)
    {
        qWarning() << "未连接到子系统，无法断开连接";
        return;
    }
    
    qDebug() << "正在断开与子系统的连接...";
    m_socket->disconnectFromHost();
}

bool SubsystemClient::isConnected() const
{
    return m_isConnected;
}

bool SubsystemClient::sendShowUiCommand()
{
    return sendCommand("/show_ui");
}

bool SubsystemClient::sendStatusCommand()
{
    return sendCommand("/status");
}

bool SubsystemClient::sendCommand(const QString &command)
{
    if (!m_isConnected) {
        qWarning() << "未连接到子系统，无法发送命令";
        return false;
    }
    
    if (command.isEmpty()) {
        qWarning() << "命令不能为空";
        return false;
    }
    
    QByteArray data = command.toUtf8();
    qint64 bytesWritten = m_socket->write(data);
    
    if (bytesWritten == data.size()) {
        qDebug() << "命令发送成功:" << command;
        return true;
    } else {
        qWarning() << "命令发送失败:" << command;
        return false;
    }
}

// 进程相关槽函数
void SubsystemClient::onProcessStarted()
{
    m_isSubsystemRunning = true;
    qDebug() << "✅ 子系统启动成功";
    emit subsystemStarted();
}

void SubsystemClient::onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    m_isSubsystemRunning = false;
    
    if (exitStatus == QProcess::NormalExit) {
        qDebug() << "✅ 子系统正常退出，退出码:" << exitCode;
    } else {
        qDebug() << "⚠️ 子系统异常退出，退出码:" << exitCode;
    }
    
    emit subsystemStopped();
}

void SubsystemClient::onProcessError(QProcess::ProcessError error)
{
    m_isSubsystemRunning = false;
    QString errorMsg;
    
    switch (error) {
        case QProcess::FailedToStart:
            errorMsg = "子系统启动失败";
            break;
        case QProcess::Crashed:
            errorMsg = "子系统崩溃";
            break;
        case QProcess::Timedout:
            errorMsg = "子系统启动超时";
            break;
        case QProcess::WriteError:
            errorMsg = "子系统写入错误";
            break;
        case QProcess::ReadError:
            errorMsg = "子系统读取错误";
            break;
        case QProcess::UnknownError:
        default:
            errorMsg = "子系统未知错误";
            break;
    }
    
    qWarning() << "❌ 子系统错误:" << errorMsg;
    emit subsystemError(errorMsg);
}

// 网络相关槽函数
void SubsystemClient::onSocketConnected()
{
    m_isConnected = true;
    qDebug() << "✅ 已连接到子系统";
    emit connected();
}

void SubsystemClient::onSocketDisconnected()
{
    m_isConnected = false;
    qDebug() << "⚠️ 与子系统的连接已断开";
    emit disconnected();
}

void SubsystemClient::onSocketError(QAbstractSocket::SocketError error)
{
    m_isConnected = false;
    QString errorMsg = m_socket->errorString();
    
    qWarning() << "❌ 网络连接错误:" << errorMsg;
    emit connectionError(errorMsg);
}

void SubsystemClient::onSocketReadyRead()
{
    while (m_socket->canReadLine()) {
        QByteArray data = m_socket->readLine().trimmed();
        QString response = QString::fromUtf8(data);
        
        qDebug() << "收到子系统响应:" << response;
        emit responseReceived(response);
    }
}
