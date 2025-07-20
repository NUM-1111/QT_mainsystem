#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "subsystemclient.h"
#include "subsystemmanager.h"

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
    
    // 子系统1客户端事件处理
    void onSubsystem1Started();
    void onSubsystem1Stopped();
    void onSubsystem1Error(const QString &error);
    void onSubsystem1Connected();
    void onSubsystem1Disconnected();
    void onSubsystem1ConnectionError(const QString &error);
    void onSubsystem1ResponseReceived(const QString &response);
    
    // 子系统2客户端事件处理
    void onSubsystem2Started();
    void onSubsystem2Stopped();
    void onSubsystem2Error(const QString &error);
    void onSubsystem2Connected();
    void onSubsystem2Disconnected();
    void onSubsystem2ConnectionError(const QString &error);
    void onSubsystem2ResponseReceived(const QString &response);
    
    // 定时器槽函数
    void onSubsystem1ConnectionTimerTimeout();
    void onSubsystem2ConnectionTimerTimeout();

private:
    void setupSubsystemClient();
    void setupSubsystemInfo();
    void updateSubsystem1Button();
    void updateSubsystem2Button();
    void showStatusMessage(const QString &message);
    void applyPermissionControl();


private:
    Ui::MainWindow *ui;
    SubsystemClient *m_subsystemClient1;  // 子系统客户端1
    SubsystemClient *m_subsystemClient2;  // 子系统客户端2
    QTimer *m_connectionTimer1;           // 连接重试定时器子系统1
    QTimer *m_connectionTimer2;           // 连接重试定时器子系统2
    bool m_isSubsystem1Running;          // 子系统1运行状态
    bool m_isSubsystem2Running;          // 子系统2运行状态
    bool m_isSubsystem1Connected;        // 子系统1连接状态
    bool m_isSubsystem2Connected;        // 子系统2连接状态
    SubsystemManager *m_subsystemManager; // 子系统管理器
};

#endif // MAINWINDOW_H
