#ifndef SUBSYSTEMCLIENT_H
#define SUBSYSTEMCLIENT_H

#include <QObject>
#include <QProcess>
#include <QTcpSocket>
#include <QString>
#include <QMap>

class SubsystemClient : public QObject
{
    Q_OBJECT

public:
    explicit SubsystemClient(const QString &host,
                             quint16 port,
                             const QString &path,
                             QObject *parent = nullptr);
    ~SubsystemClient();

    // 进程管理
    bool startSubsystem();
    void stopSubsystem();
    bool isSubsystemRunning() const;

    // 网络通信
    bool connectToSubsystem(const QString &host, quint16 port);
    void disconnectFromSubsystem();
    bool isConnected() const;

    // 命令发送
    bool sendShowUiCommand();
    bool sendUserIdCommand(const QString &userId);
    bool sendStatusCommand();
    bool sendCommand(const QString &command);

signals:
    // 进程相关信号
    void subsystemStarted();
    void subsystemStopped();
    void subsystemError(const QString &error);

    // 网络相关信号
    void connected();
    void disconnected();
    void connectionError(const QString &error);

    // 响应相关信号
    void responseReceived(const QString &response);

private slots:
    // 进程相关槽函数
    void onProcessStarted();
    void onProcessFinished(int exitCode, QProcess::ExitStatus exitStatus);
    void onProcessError(QProcess::ProcessError error);

    // 网络相关槽函数
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError error);
    void onSocketReadyRead();

    void onProcessStdOutput();
    void onProcessStdError();

private:
    QProcess *m_process;                    // 进程管理
    QTcpSocket *m_socket;                   // 网络通信
    bool m_isConnected;                     // 连接状态
    bool m_isSubsystemRunning;              // 子系统运行状态
    QString m_host;                         // 主机地址
    quint16 m_port;                         // 端口号
    QMap<QString, QWidget *> m_userWindows; // 用户窗口映射
    QString m_subsystemPath;
};

#endif // SUBSYSTEMCLIENT_H
