#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "subsystemclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // 子系统控制槽函数
    void on_btnSubsystem1_clicked();
    void on_btnSubsystem2_clicked();
    void on_btnSubsystem3_clicked();
    void on_btnSubsystem4_clicked();
    void on_btnSubsystem5_clicked();
    
    // 用户管理槽函数
    void on_btnViewUsers_clicked();
    void on_btnViewGroups_clicked();
    
    // 子系统客户端事件处理
    void onSubsystemStarted();
    void onSubsystemStopped();
    void onSubsystemError(const QString &error);
    void onConnected();
    void onDisconnected();
    void onConnectionError(const QString &error);
    void onResponseReceived(const QString &response);
    
    // 定时器槽函数
    void onConnectionTimer();

private:
    void setupSubsystemClient();
    void updateSubsystem1Button();
    void showStatusMessage(const QString &message);
    void applyPermissionControl();

private:
    Ui::MainWindow *ui;
    SubsystemClient *m_subsystemClient;  // 子系统客户端
    QTimer *m_connectionTimer;           // 连接重试定时器
    bool m_isSubsystem1Running;          // 子系统1运行状态
    bool m_isSubsystem1Connected;        // 子系统1连接状态
};

#endif // MAINWINDOW_H
