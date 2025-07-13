#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermanagerdialog.h"
#include "groupmanagerdialog.h"
#include "usermanager.h"
#include "groupmanager.h"
#include <QMessageBox>
#include <QDebug>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_subsystemClient(nullptr)
    , m_connectionTimer(nullptr)
    , m_isSubsystem1Running(false)
    , m_isSubsystem1Connected(false)
{
    ui->setupUi(this);

    // 设置窗口标题
    setWindowTitle("主系统 - 子系统管理");

    // 初始化子系统客户端
    setupSubsystemClient();

    // 初始化状态栏
    statusBar()->showMessage("就绪");

    // 更新按钮状态
    updateSubsystem1Button();

    // 应用权限控制
    applyPermissionControl();
}

MainWindow::~MainWindow()
{
    // 停止定时器
    if (m_connectionTimer) {
        m_connectionTimer->stop();
        delete m_connectionTimer;
    }

    // 清理子系统客户端
    if (m_subsystemClient) {
        delete m_subsystemClient;
    }

    delete ui;
}

void MainWindow::setupSubsystemClient()
{
    // 创建子系统客户端
    m_subsystemClient = new SubsystemClient(this);

    // 连接信号到槽函数
    connect(m_subsystemClient, &SubsystemClient::subsystemStarted,
            this, &MainWindow::onSubsystemStarted);
    connect(m_subsystemClient, &SubsystemClient::subsystemStopped,
            this, &MainWindow::onSubsystemStopped);
    connect(m_subsystemClient, &SubsystemClient::subsystemError,
            this, &MainWindow::onSubsystemError);
    connect(m_subsystemClient, &SubsystemClient::connected,
            this, &MainWindow::onConnected);
    connect(m_subsystemClient, &SubsystemClient::disconnected,
            this, &MainWindow::onDisconnected);
    connect(m_subsystemClient, &SubsystemClient::connectionError,
            this, &MainWindow::onConnectionError);
    connect(m_subsystemClient, &SubsystemClient::responseReceived,
            this, &MainWindow::onResponseReceived);

    // 创建连接重试定时器
    m_connectionTimer = new QTimer(this);
    m_connectionTimer->setSingleShot(true);
    connect(m_connectionTimer, &QTimer::timeout, this, &MainWindow::onConnectionTimer);
}

void MainWindow::applyPermissionControl()
{
    User user = UserManager::getCurrentUser();
    // 计算最终权限
    user = PermissionManager::getInstance().calculateUserFinalRights(user);
    // 分系统按钮
    ui->btnSubsystem1->setEnabled(user.canAccessSubsystem(0));
    ui->btnSubsystem2->setEnabled(user.canAccessSubsystem(1));
    ui->btnSubsystem3->setEnabled(user.canAccessSubsystem(2));
    ui->btnSubsystem4->setEnabled(user.canAccessSubsystem(3));
    ui->btnSubsystem5->setEnabled(user.canAccessSubsystem(4));
    // 管理员功能
    bool isAdmin = (user.group == 0);
    ui->btnViewUsers->setEnabled(isAdmin);
    ui->btnViewGroups->setEnabled(isAdmin);
}

void MainWindow::on_btnSubsystem1_clicked()
{
    User user = UserManager::getCurrentUser();
    user = PermissionManager::getInstance().calculateUserFinalRights(user);
    if (!user.canAccessSubsystem(0)) {
        QMessageBox::warning(this, "权限不足", "您没有访问分系统1的权限");
        return;
    }
    if (!m_isSubsystem1Running) {
        // 启动子系统1
        showStatusMessage("正在启动子系统1...");

        // 启动子系统进程
        if (m_subsystemClient->startSubsystem()) {
            qDebug() << "子系统1启动命令已发送";
        } else {
            showStatusMessage("子系统1启动失败");
            QMessageBox::warning(this, "错误", "子系统1启动失败");
        }
    } else if (!m_isSubsystem1Connected) {
        // 尝试连接
        showStatusMessage("正在连接子系统1...");
        if (m_subsystemClient->connectToSubsystem()) {
            qDebug() << "连接命令已发送";
        } else {
            showStatusMessage("连接失败");
            QMessageBox::warning(this, "错误", "连接子系统1失败");
        }
    } else {
        // 发送显示界面命令
        showStatusMessage("正在发送显示界面命令...");
        if (m_subsystemClient->sendShowUiCommand()) {
            qDebug() << "显示界面命令已发送";
        } else {
            showStatusMessage("命令发送失败");
            QMessageBox::warning(this, "错误", "发送命令失败");
        }
    }
}

void MainWindow::on_btnSubsystem2_clicked()
{
    User user = UserManager::getCurrentUser();
    user = PermissionManager::getInstance().calculateUserFinalRights(user);
    if (!user.canAccessSubsystem(1)) {
        QMessageBox::warning(this, "权限不足", "您没有访问分系统2的权限");
        return;
    }
    QMessageBox::information(this, "提示", "子系统2功能待实现");
}

void MainWindow::on_btnSubsystem3_clicked()
{
    User user = UserManager::getCurrentUser();
    user = PermissionManager::getInstance().calculateUserFinalRights(user);
    if (!user.canAccessSubsystem(2)) {
        QMessageBox::warning(this, "权限不足", "您没有访问分系统3的权限");
        return;
    }
    QMessageBox::information(this, "提示", "子系统3功能待实现");
}

void MainWindow::on_btnSubsystem4_clicked()
{
    User user = UserManager::getCurrentUser();
    user = PermissionManager::getInstance().calculateUserFinalRights(user);
    if (!user.canAccessSubsystem(3)) {
        QMessageBox::warning(this, "权限不足", "您没有访问分系统4的权限");
        return;
    }
    QMessageBox::information(this, "提示", "子系统4功能待实现");
}

void MainWindow::on_btnSubsystem5_clicked()
{
    User user = UserManager::getCurrentUser();
    user = PermissionManager::getInstance().calculateUserFinalRights(user);
    if (!user.canAccessSubsystem(4)) {
        QMessageBox::warning(this, "权限不足", "您没有访问分系统5的权限");
        return;
    }
    QMessageBox::information(this, "提示", "子系统5功能待实现");
}

void MainWindow::on_btnViewUsers_clicked()
{
    User user = UserManager::getCurrentUser();
    if (user.group != 0) {
        QMessageBox::warning(this, "权限不足", "只有管理员可以访问用户管理功能");
        return;
    }
    // 创建并显示用户管理对话框
    UserManagerDialog *userDialog = new UserManagerDialog(this);
    userDialog->setAttribute(Qt::WA_DeleteOnClose);
    userDialog->show();
    
    showStatusMessage("用户管理界面已打开");
}

void MainWindow::on_btnViewGroups_clicked()
{
    User user = UserManager::getCurrentUser();
    if (user.group != 0) {
        QMessageBox::warning(this, "权限不足", "只有管理员可以访问权限组管理功能");
        return;
    }
    GroupManagerDialog *groupDialog = new GroupManagerDialog(this);
    groupDialog->setAttribute(Qt::WA_DeleteOnClose);
    groupDialog->show();
    showStatusMessage("权限组管理界面已打开");
}

void MainWindow::onSubsystemStarted()
{
    m_isSubsystem1Running = true;
    showStatusMessage("子系统1已启动，正在连接...");
    updateSubsystem1Button();

    // 延迟2秒后尝试连接
    m_connectionTimer->start(2000);
}

void MainWindow::onSubsystemStopped()
{
    m_isSubsystem1Running = false;
    m_isSubsystem1Connected = false;
    showStatusMessage("子系统1已停止");
    updateSubsystem1Button();
}

void MainWindow::onSubsystemError(const QString &error)
{
    m_isSubsystem1Running = false;
    m_isSubsystem1Connected = false;
    showStatusMessage("子系统1错误: " + error);
    updateSubsystem1Button();

    QMessageBox::critical(this, "子系统错误", "子系统1发生错误:\n" + error);
}

void MainWindow::onConnected()
{
    m_isSubsystem1Connected = true;
    showStatusMessage("已连接到子系统1");
    updateSubsystem1Button();
}

void MainWindow::onDisconnected()
{
    m_isSubsystem1Connected = false;
    showStatusMessage("与子系统1的连接已断开");
    updateSubsystem1Button();
}

void MainWindow::onConnectionError(const QString &error)
{
    m_isSubsystem1Connected = false;
    showStatusMessage("连接错误: " + error);
    updateSubsystem1Button();

    QMessageBox::warning(this, "连接错误", "连接子系统1失败:\n" + error);
}

void MainWindow::onResponseReceived(const QString &response)
{
    showStatusMessage("收到响应: " + response);

    // 根据响应内容处理
    if (response.contains("UI_SHOWN", Qt::CaseInsensitive)) {
        QMessageBox::information(this, "成功", "子系统1界面已显示");
    } else if (response.contains("ERROR", Qt::CaseInsensitive)) {
        QMessageBox::warning(this, "错误", "子系统1返回错误:\n" + response);
    }
}

void MainWindow::onConnectionTimer()
{
    if (m_isSubsystem1Running && !m_isSubsystem1Connected) {
        showStatusMessage("正在连接子系统1...");
        m_subsystemClient->connectToSubsystem();
    }
}

void MainWindow::updateSubsystem1Button()
{
    QString buttonText;
    QString statusText;

    if (!m_isSubsystem1Running) {
        buttonText = "启动子系统1";
        statusText = "未运行";
    } else if (!m_isSubsystem1Connected) {
        buttonText = "连接子系统1";
        statusText = "运行中，未连接";
    } else {
        buttonText = "显示子系统1界面";
        statusText = "已连接";
    }

    ui->btnSubsystem1->setText(buttonText);
    showStatusMessage("子系统1状态: " + statusText);
}

void MainWindow::showStatusMessage(const QString &message)
{
    statusBar()->showMessage(message);
    qDebug() << "[主系统]" << message;
}
