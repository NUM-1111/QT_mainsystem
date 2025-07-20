#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usermanagerdialog.h"
#include "groupmanagerdialog.h"
#include "usermanager.h"
#include "groupmanager.h"
#include "subsystemmanager.h"
#include <QMessageBox>
#include <QDebug>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_subsystemClient1(nullptr)
    , m_subsystemClient2(nullptr)
    , m_connectionTimer1(nullptr)
    , m_connectionTimer2(nullptr)
    , m_isSubsystem1Running(false)
    , m_isSubsystem2Running(false)
    , m_isSubsystem1Connected(false)
    , m_isSubsystem2Connected(false)
{
    ui->setupUi(this);

    // 创建子系统信息
    setupSubsystemInfo();

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
    // 停止子系统1的定时器
    if (m_connectionTimer1) {
        m_connectionTimer1->stop();
        delete m_connectionTimer1;
    }

    // 停止子系统2的定时器
    if (m_connectionTimer2) {
        m_connectionTimer2->stop();
        delete m_connectionTimer2;
    }
    if (m_subsystemClient1) {
        delete m_subsystemClient1;
    }
    if (m_subsystemClient2) {
        delete m_subsystemClient2;
    }

    delete ui;
}

void MainWindow:: setupSubsystemInfo()
{
    // 创建子系统管理器
    m_subsystemManager = new SubsystemManager(this);

     // 注册子系统信息
    m_subsystemManager->registerSubsystem({"system1", "D:/Tools/Qt/projects/system1/build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/system1.exe", "localhost", 8080});
    m_subsystemManager->registerSubsystem({"system2", "D:/Tools/Qt/projects/system2/build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/system2.exe", "localhost", 8081});
}

void MainWindow::setupSubsystemClient()
{
    // 创建子系统客户端
    SubsystemInfo info;
    if (m_subsystemManager->getSubsystemInfo("system1", info)) {
        m_subsystemClient1 = new SubsystemClient(info.host, info.port, info.path, this);
    }
    if (m_subsystemManager->getSubsystemInfo("system2", info)) {
        m_subsystemClient2 = new SubsystemClient(info.host, info.port, info.path, this);
    }

    // 连接信号到槽函数->子系统1
    connect(m_subsystemClient1, &SubsystemClient::subsystemStarted,
            this, &MainWindow::onSubsystem1Started);
    connect(m_subsystemClient1, &SubsystemClient::subsystemStopped,
            this, &MainWindow::onSubsystem1Stopped);
    connect(m_subsystemClient1, &SubsystemClient::subsystemError,
            this, &MainWindow::onSubsystem1Error);
    connect(m_subsystemClient1, &SubsystemClient::connected,
            this, &MainWindow::onSubsystem1Connected);
    connect(m_subsystemClient1, &SubsystemClient::disconnected,
            this, &MainWindow::onSubsystem1Disconnected);
    connect(m_subsystemClient1, &SubsystemClient::connectionError,
            this, &MainWindow::onSubsystem1ConnectionError);
    connect(m_subsystemClient1, &SubsystemClient::responseReceived,
            this, &MainWindow::onSubsystem1ResponseReceived);

    // 创建连接重试定时器
    m_connectionTimer1 = new QTimer(this);
    m_connectionTimer1->setSingleShot(true);
    connect(m_connectionTimer1, &QTimer::timeout, this, &MainWindow::onSubsystem1ConnectionTimerTimeout);

    // 连接信号到槽函数->子系统2
    connect(m_subsystemClient2, &SubsystemClient::subsystemStarted,
            this, &MainWindow::onSubsystem2Started);
    connect(m_subsystemClient2, &SubsystemClient::subsystemStopped,
            this, &MainWindow::onSubsystem2Stopped);
    connect(m_subsystemClient2, &SubsystemClient::subsystemError,
            this, &MainWindow::onSubsystem2Error);
    connect(m_subsystemClient2, &SubsystemClient::connected,
            this, &MainWindow::onSubsystem2Connected);
    connect(m_subsystemClient2, &SubsystemClient::disconnected,
            this, &MainWindow::onSubsystem2Disconnected);
    connect(m_subsystemClient2, &SubsystemClient::connectionError,
            this, &MainWindow::onSubsystem2ConnectionError);
    connect(m_subsystemClient2, &SubsystemClient::responseReceived,
            this, &MainWindow::onSubsystem2ResponseReceived);

        // 创建连接重试定时器
    m_connectionTimer2 = new QTimer(this);
    m_connectionTimer2->setSingleShot(true);
    connect(m_connectionTimer2, &QTimer::timeout, this, &MainWindow::onSubsystem2ConnectionTimerTimeout);
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
    SubsystemInfo info;
    if(!m_subsystemManager->getSubsystemInfo("system1", info)){
        QMessageBox::warning(this,"严重错误","不存在该系统");
    }else{
        if (!user.canAccessSubsystem(0)) {
            QMessageBox::warning(this, "权限不足", "您没有访问分系统1的权限");
            return;
        }
        if (!m_isSubsystem1Running) {
            // 启动子系统1
            showStatusMessage("正在启动子系统1...");

            // 启动子系统进程
            if (m_subsystemClient1->startSubsystem()){
                qDebug() << "子系统1启动命令已发送";
            } else {
                showStatusMessage("子系统1启动失败");
                QMessageBox::warning(this, "错误", "子系统1启动失败");
            }
        } else if (!m_isSubsystem1Connected) {
            // 尝试连接
            showStatusMessage("正在连接子系统1...");
            if (m_subsystemClient1->connectToSubsystem(info.host, info.port)) {
                qDebug() << "连接命令已发送";
            } else {
                showStatusMessage("连接失败");
                QMessageBox::warning(this, "错误", "连接子系统1失败");
            }
        } else {
            // 发送显示界面命令
            showStatusMessage("正在发送显示界面命令...");
            if (m_subsystemClient1->sendShowUiCommand()) {
                qDebug() << "显示界面命令已发送";
            } else {
                showStatusMessage("命令发送失败");
                QMessageBox::warning(this, "错误", "发送命令失败");
            }
        }
    }
}

void MainWindow::on_btnSubsystem2_clicked()
{
    User user = UserManager::getCurrentUser();
    user = PermissionManager::getInstance().calculateUserFinalRights(user);
    SubsystemInfo info;
    if (!m_subsystemManager->getSubsystemInfo("system2", info))
    {
        QMessageBox::warning(this, "严重错误", "不存在该系统");
    }
    else
    {
        if (!user.canAccessSubsystem(1))
        {
            QMessageBox::warning(this, "权限不足", "您没有访问分系统2的权限");
            return;
        }
        if (!m_isSubsystem2Running)
        {
            // 启动子系统2
            showStatusMessage("正在启动子系统2...");

            // 启动子系统进程
            if (m_subsystemClient2->startSubsystem())
            {
                qDebug() << "子系统2启动命令已发送";
            }
            else
            {
                showStatusMessage("子系统2启动失败");
                QMessageBox::warning(this, "错误", "子系统2启动失败");
            }
        }
        else if (!m_isSubsystem2Connected)
        {
            // 尝试连接
            showStatusMessage("正在连接子系统2...");
            if (m_subsystemClient2->connectToSubsystem(info.host, info.port))
            {
                qDebug() << "连接命令已发送";
            }
            else
            {
                showStatusMessage("连接失败");
                QMessageBox::warning(this, "错误", "连接子系统2失败");
            }
        }
        else
        {
            // 发送显示界面命令
            showStatusMessage("正在发送显示界面命令...");
            if (m_subsystemClient2->sendShowUiCommand())
            {
                qDebug() << "显示界面命令已发送";
            }
            else
            {
                showStatusMessage("命令发送失败");
                QMessageBox::warning(this, "错误", "发送命令失败");
            }
        }
    }
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

void MainWindow::onSubsystem1Started()
{
    m_isSubsystem1Running = true;
    showStatusMessage("子系统1已启动，正在连接...");
    updateSubsystem1Button();

    // 延迟2秒后尝试连接
    m_connectionTimer1->start(2000);
}

void MainWindow::onSubsystem1Stopped()
{
    m_isSubsystem1Running = false;
    m_isSubsystem1Connected = false;
    showStatusMessage("子系统1已停止");
    updateSubsystem1Button();
}

void MainWindow::onSubsystem1Error(const QString &error)
{
    m_isSubsystem1Running = false;
    m_isSubsystem1Connected = false;
    showStatusMessage("子系统1错误: " + error);
    updateSubsystem1Button();

    QMessageBox::critical(this, "子系统错误", "子系统1发生错误:\n" + error);
}

void MainWindow::onSubsystem1Connected()
{
    m_isSubsystem1Connected = true;
    showStatusMessage("已连接到子系统1");
    updateSubsystem1Button();
}

void MainWindow::onSubsystem1Disconnected()
{
    m_isSubsystem1Connected = false;
    showStatusMessage("与子系统1的连接已断开");
    updateSubsystem1Button();
}

void MainWindow::onSubsystem1ConnectionError(const QString &error)
{
    m_isSubsystem1Connected = false;
    showStatusMessage("连接错误: " + error);
    updateSubsystem1Button();

    QMessageBox::warning(this, "连接错误", "连接子系统1失败:\n" + error);
}

void MainWindow::onSubsystem1ResponseReceived(const QString &response)
{
    showStatusMessage("收到响应: " + response);

    // 根据响应内容处理
    if (response.contains("UI_SHOWN", Qt::CaseInsensitive)) {
        QMessageBox::information(this, "成功", "子系统1界面已显示");
    } else if (response.contains("ERROR", Qt::CaseInsensitive)) {
        QMessageBox::warning(this, "错误", "子系统1返回错误:\n" + response);
    }
}

void MainWindow::onSubsystem1ConnectionTimerTimeout()
{
    SubsystemInfo info;
    if (!m_subsystemManager->getSubsystemInfo("system1", info)) {
        showStatusMessage("子系统1信息获取失败");
        return;
    }
    if (m_isSubsystem1Running && !m_isSubsystem1Connected) {
        showStatusMessage("正在连接子系统1...");
        m_subsystemClient1->connectToSubsystem(info.host, info.port);
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

void MainWindow::onSubsystem2Started()
{
    m_isSubsystem2Running = true;
    showStatusMessage("子系统2已启动，正在连接...");
    updateSubsystem2Button();

    // 延迟2秒后尝试连接
    m_connectionTimer2->start(2000);
}

void MainWindow::onSubsystem2Stopped()
{
    m_isSubsystem2Running = false;
    m_isSubsystem2Connected = false;
    showStatusMessage("子系统2已停止");
    updateSubsystem2Button();
}

void MainWindow::onSubsystem2Error(const QString &error)
{
    m_isSubsystem2Running = false;
    m_isSubsystem2Connected = false;
    showStatusMessage("子系统2错误: " + error);
    updateSubsystem2Button();

    QMessageBox::critical(this, "子系统错误", "子系统2发生错误:\n" + error);
}

void MainWindow::onSubsystem2Connected()
{
    m_isSubsystem2Connected = true;
    showStatusMessage("已连接到子系统2");
    updateSubsystem2Button();
}

void MainWindow::onSubsystem2Disconnected()
{
    m_isSubsystem2Connected = false;
    showStatusMessage("与子系统2的连接已断开");
    updateSubsystem2Button();
}

void MainWindow::onSubsystem2ConnectionError(const QString &error)
{
    m_isSubsystem2Connected = false;
    showStatusMessage("连接错误: " + error);
    updateSubsystem2Button();

    QMessageBox::warning(this, "连接错误", "连接子系统2失败:\n" + error);
}

void MainWindow::onSubsystem2ResponseReceived(const QString &response)
{
    showStatusMessage("收到响应: " + response);

    // 根据响应内容处理
    if (response.contains("UI_SHOWN", Qt::CaseInsensitive)) {
        QMessageBox::information(this, "成功", "子系统2界面已显示");
    } else if (response.contains("ERROR", Qt::CaseInsensitive)) {
        QMessageBox::warning(this, "错误", "子系统2返回错误:\n" + response);
    }
}

void MainWindow::onSubsystem2ConnectionTimerTimeout()
{
    SubsystemInfo info;
    if (!m_subsystemManager->getSubsystemInfo("system2", info)) {
        showStatusMessage("子系统2信息获取失败");
        return;
    }
    if (m_isSubsystem2Running && !m_isSubsystem2Connected) {
        showStatusMessage("正在连接子系统2...");
        m_subsystemClient2->connectToSubsystem(info.host, info.port);
    }
}

void MainWindow::updateSubsystem2Button()
{
    QString buttonText;
    QString statusText;

    if (!m_isSubsystem2Running) {
        buttonText = "启动子系统2";
        statusText = "未运行";
    } else if (!m_isSubsystem2Connected) {
        buttonText = "连接子系统2";
        statusText = "运行中，未连接";
    } else {
        buttonText = "显示子系统2界面";
        statusText = "已连接";
    }

    ui->btnSubsystem2->setText(buttonText);
    showStatusMessage("子系统2状态: " + statusText);
}

void MainWindow::showStatusMessage(const QString &message)
{
    statusBar()->showMessage(message);
    qDebug() << "[主系统]" << message;
}
