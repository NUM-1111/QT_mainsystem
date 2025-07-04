#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include <QProcess>
#include "subsystemclient.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /**
     * @brief 添加日志信息
     * @param message 日志消息
     */
    void addLogMessage(const QString &message);

    /**
     * @brief 更新连接状态显示
     */
    void updateConnectionStatus();

    /**
     * @brief 更新按钮状态
     */
    void updateButtonStates();

    /**
     * @brief 启动分系统1
     */
    void startSubsystem1();

    /**
     * @brief 停止分系统1
     */
    void stopSubsystem1();

private slots:
    /**
     * @brief 连接按钮点击事件
     */
    void handleConnectBtnClicked();

    /**
     * @brief 启动分系统1程序按钮点击事件
     */
    void handleStartSubsystem1BtnClicked();

    /**
     * @brief 断开连接按钮点击事件
     */
    void handleDisconnectBtnClicked();

    /**
     * @brief 启动分系统1界面按钮点击事件
     */
    void handleSystem1BtnClicked();

    /**
     * @brief 查询状态按钮点击事件
     */
    void handleStatusBtnClicked();

    /**
     * @brief 获取帮助按钮点击事件
     */
    void handleHelpBtnClicked();

    /**
     * @brief 发送命令按钮点击事件
     */
    void handleSendCommandBtnClicked();

    /**
     * @brief 清空日志按钮点击事件
     */
    void handleClearLogBtnClicked();

    /**
     * @brief 分系统连接成功事件
     */
    void handleSubsystemConnected();

    /**
     * @brief 分系统连接断开事件
     */
    void handleSubsystemDisconnected();

    /**
     * @brief 分系统连接错误事件
     * @param errorString 错误信息
     */
    void handleSubsystemConnectionError(const QString &errorString);

    /**
     * @brief 收到分系统响应事件
     * @param response 响应内容
     */
    void handleSubsystemResponseReceived(const QString &response);

    /**
     * @brief 命令发送成功事件
     * @param command 发送的命令
     */
    void handleCommandSent(const QString &command);

    /**
     * @brief 命令发送失败事件
     * @param command 失败的命令
     * @param errorString 错误信息
     */
    void handleCommandFailed(const QString &command, const QString &errorString);

    /**
     * @brief 分系统1进程启动成功事件
     */
    void handleSubsystem1Started();

    /**
     * @brief 分系统1进程错误事件
     * @param error 错误类型
     */
    void handleSubsystem1Error(QProcess::ProcessError error);

    /**
     * @brief 分系统1进程结束事件
     * @param exitCode 退出码
     * @param exitStatus 退出状态
     */
    void handleSubsystem1Finished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    Ui::MainWindow *ui;
    SubsystemClient *m_subsystemClient;  ///< 分系统客户端
    QProcess *m_subsystem1Process;       ///< 分系统1进程
};
#endif // MAINWINDOW_H
