#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QApplication>
#include <QProcess>
#include <QTimer>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_subsystemClient(nullptr)
    , m_subsystem1Process(nullptr)
{
    ui->setupUi(this);
    
    // 设置窗口标题
    setWindowTitle("主系统 - 分系统管理");
    
    // 创建分系统客户端
    m_subsystemClient = new SubsystemClient(this);
    
    // 创建分系统1进程管理器
    m_subsystem1Process = new QProcess(this);
    
    // 连接按钮信号
    connect(ui->connectBtn, &QPushButton::clicked, this, &MainWindow::handleConnectBtnClicked);
    connect(ui->startSubsystem1Btn, &QPushButton::clicked, this, &MainWindow::handleStartSubsystem1BtnClicked);
    connect(ui->disconnectBtn, &QPushButton::clicked, this, &MainWindow::handleDisconnectBtnClicked);
    connect(ui->system1Btn, &QPushButton::clicked, this, &MainWindow::handleSystem1BtnClicked);
    connect(ui->statusBtn, &QPushButton::clicked, this, &MainWindow::handleStatusBtnClicked);
    connect(ui->helpBtn, &QPushButton::clicked, this, &MainWindow::handleHelpBtnClicked);
    connect(ui->sendCommandBtn, &QPushButton::clicked, this, &MainWindow::handleSendCommandBtnClicked);
    connect(ui->clearLogBtn, &QPushButton::clicked, this, &MainWindow::handleClearLogBtnClicked);
    
    // 连接分系统客户端信号
    connect(m_subsystemClient, &SubsystemClient::connected, this, &MainWindow::handleSubsystemConnected);
    connect(m_subsystemClient, &SubsystemClient::disconnected, this, &MainWindow::handleSubsystemDisconnected);
    connect(m_subsystemClient, &SubsystemClient::connectionError, this, &MainWindow::handleSubsystemConnectionError);
    connect(m_subsystemClient, &SubsystemClient::responseReceived, this, &MainWindow::handleSubsystemResponseReceived);
    connect(m_subsystemClient, &SubsystemClient::commandSent, this, &MainWindow::handleCommandSent);
    connect(m_subsystemClient, &SubsystemClient::commandFailed, this, &MainWindow::handleCommandFailed);
    
    // 连接分系统1进程信号
    connect(m_subsystem1Process, &QProcess::started, this, &MainWindow::handleSubsystem1Started);
    connect(m_subsystem1Process, &QProcess::errorOccurred, this, &MainWindow::handleSubsystem1Error);
    connect(m_subsystem1Process, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished), 
            this, &MainWindow::handleSubsystem1Finished);
    
    // 初始化界面
    updateConnectionStatus();
    updateButtonStates();
    
    // 添加启动日志
    addLogMessage("主系统启动完成");
    addLogMessage("请点击'启动分系统1程序'按钮来启动分系统");
    
    // 注释掉自动启动，改为手动启动
    // startSubsystem1();
    
    qDebug() << "主系统界面已创建";
}

MainWindow::~MainWindow()
{
    stopSubsystem1();
    delete ui;
    qDebug() << "主系统界面已销毁";
}

void MainWindow::startSubsystem1()
{
    if (m_subsystem1Process->state() == QProcess::Running) {
        addLogMessage("分系统1已在运行");
        return;
    }
    
    addLogMessage("正在启动分系统1...");
    
    // 获取分系统1的可执行文件路径
    QString currentDir = QApplication::applicationDirPath();
    QStringList possiblePaths;
    
    // 添加可能的路径
    possiblePaths << currentDir + "/../system1/system1.exe";
    possiblePaths << currentDir + "/system1.exe";
    possiblePaths << currentDir + "/../system1/debug/system1.exe";
    possiblePaths << currentDir + "/../system1/release/system1.exe";
    possiblePaths << currentDir + "/debug/system1.exe";
    possiblePaths << currentDir + "/release/system1.exe";
    possiblePaths << currentDir + "/../system1/build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/system1.exe";
    possiblePaths << currentDir + "/../system1/build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug/release/system1.exe";
    
    // 基于当前主系统的build目录结构推断system1的路径
    QString buildDir = currentDir;
    if (buildDir.contains("/debug/")) {
        buildDir = buildDir.replace("/debug/", "/");
        possiblePaths << buildDir + "/../system1/build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug/debug/system1.exe";
    } else if (buildDir.contains("/release/")) {
        buildDir = buildDir.replace("/release/", "/");
        possiblePaths << buildDir + "/../system1/build/Desktop_Qt_5_15_2_MinGW_64_bit-Debug/release/system1.exe";
    }
    
    possiblePaths << "system1.exe";  // 当前工作目录
    
    QString subsystem1Path;
    bool found = false;
    
    addLogMessage("搜索分系统1可执行文件...");
    for (const QString &path : possiblePaths) {
        addLogMessage("检查路径：" + path);
        if (QFile::exists(path)) {
            subsystem1Path = path;
            found = true;
            addLogMessage("✅ 找到分系统1：" + path);
            break;
        }
    }
    
    if (!found) {
        addLogMessage("❌ 找不到分系统1可执行文件");
        addLogMessage("请确保system1.exe已编译并位于以下路径之一：");
        for (const QString &path : possiblePaths) {
            addLogMessage("  - " + path);
        }
        
        QMessageBox::warning(this, "启动错误", 
            "找不到分系统1可执行文件，请确保system1.exe已编译并位于正确位置。\n\n"
            "请先编译system1项目，或者将system1.exe复制到主系统目录。");
        return;
    }
    
    addLogMessage("分系统1路径：" + subsystem1Path);
    
    // 启动分系统1
    m_subsystem1Process->start(subsystem1Path);
}

void MainWindow::stopSubsystem1()
{
    if (m_subsystem1Process->state() == QProcess::Running) {
        addLogMessage("正在停止分系统1...");
        m_subsystem1Process->terminate();
        
        // 等待进程结束，最多等待5秒
        if (!m_subsystem1Process->waitForFinished(5000)) {
            addLogMessage("强制终止分系统1...");
            m_subsystem1Process->kill();
        }
    }
}

void MainWindow::addLogMessage(const QString &message)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString logMessage = QString("[%1] %2").arg(timestamp, message);
    
    ui->logTextEdit->append(logMessage);
    
    // 滚动到底部
    QTextCursor cursor = ui->logTextEdit->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logTextEdit->setTextCursor(cursor);
}

void MainWindow::updateConnectionStatus()
{
    QString status = m_subsystemClient->getConnectionStatus();
    ui->connectionStatusLabel->setText("连接状态：" + status);
}

void MainWindow::updateButtonStates()
{
    bool isConnected = m_subsystemClient->isConnected();
    
    ui->connectBtn->setEnabled(!isConnected);
    ui->disconnectBtn->setEnabled(isConnected);
    ui->system1Btn->setEnabled(isConnected);
    ui->statusBtn->setEnabled(isConnected);
    ui->helpBtn->setEnabled(isConnected);
    ui->sendCommandBtn->setEnabled(isConnected);
    ui->commandInput->setEnabled(isConnected);
}

void MainWindow::handleConnectBtnClicked()
{
    addLogMessage("正在连接分系统1...");
    
    if (!m_subsystemClient->connectToSubsystem("localhost", 8080)) {
        addLogMessage("❌ 连接请求失败");
        QMessageBox::warning(this, "连接错误", "无法发起连接请求");
    }
}

void MainWindow::handleStartSubsystem1BtnClicked()
{
    startSubsystem1();
}

void MainWindow::handleDisconnectBtnClicked()
{
    addLogMessage("正在断开与分系统1的连接...");
    m_subsystemClient->disconnectFromSubsystem();
}

void MainWindow::handleSystem1BtnClicked()
{
    addLogMessage("发送命令：/show_ui");
    m_subsystemClient->sendCommand("/show_ui");
}

void MainWindow::handleStatusBtnClicked()
{
    addLogMessage("发送命令：/status");
    m_subsystemClient->sendCommand("/status");
}

void MainWindow::handleHelpBtnClicked()
{
    addLogMessage("发送命令：/help");
    m_subsystemClient->sendCommand("/help");
}

void MainWindow::handleSendCommandBtnClicked()
{
    QString command = ui->commandInput->text().trimmed();
    if (command.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入要发送的命令");
        return;
    }
    
    addLogMessage("发送自定义命令：" + command);
    m_subsystemClient->sendCommand(command);
    
    // 清空输入框
    ui->commandInput->clear();
}

void MainWindow::handleClearLogBtnClicked()
{
    ui->logTextEdit->clear();
    ui->responseTextEdit->clear();
    addLogMessage("日志已清空");
}

void MainWindow::handleSubsystemConnected()
{
    addLogMessage("✅ 成功连接到分系统1");
    updateConnectionStatus();
    updateButtonStates();
}

void MainWindow::handleSubsystemDisconnected()
{
    addLogMessage("❌ 与分系统1的连接已断开");
    updateConnectionStatus();
    updateButtonStates();
}

void MainWindow::handleSubsystemConnectionError(const QString &errorString)
{
    addLogMessage("❌ 连接错误：" + errorString);
    updateConnectionStatus();
    updateButtonStates();
}

void MainWindow::handleSubsystemResponseReceived(const QString &response)
{
    addLogMessage("📨 收到响应：" + response);
    ui->responseTextEdit->setText(response);
}

void MainWindow::handleCommandSent(const QString &command)
{
    addLogMessage("✅ 命令发送成功：" + command);
}

void MainWindow::handleCommandFailed(const QString &command, const QString &errorString)
{
    addLogMessage("❌ 命令发送失败：" + command + " - " + errorString);
}

void MainWindow::handleSubsystem1Started()
{
    addLogMessage("✅ 分系统1启动成功");
    
    // 等待2秒后自动连接
    QTimer::singleShot(2000, [this]() {
        addLogMessage("自动连接分系统1...");
        handleConnectBtnClicked();
    });
}

void MainWindow::handleSubsystem1Error(QProcess::ProcessError error)
{
    QString errorMsg;
    switch (error) {
        case QProcess::FailedToStart:
            errorMsg = "启动失败";
            break;
        case QProcess::Crashed:
            errorMsg = "程序崩溃";
            break;
        case QProcess::Timedout:
            errorMsg = "启动超时";
            break;
        case QProcess::WriteError:
            errorMsg = "写入错误";
            break;
        case QProcess::ReadError:
            errorMsg = "读取错误";
            break;
        case QProcess::UnknownError:
        default:
            errorMsg = "未知错误";
            break;
    }
    
    addLogMessage("❌ 分系统1启动错误：" + errorMsg);
    QMessageBox::warning(this, "启动错误", "分系统1启动失败：" + errorMsg);
}

void MainWindow::handleSubsystem1Finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    QString statusStr = (exitStatus == QProcess::NormalExit) ? "正常退出" : "异常退出";
    addLogMessage(QString("分系统1已退出，退出码：%1，状态：%2").arg(exitCode).arg(statusStr));
    
    // 如果主系统还在运行，可以询问是否重新启动
    if (exitCode != 0 || exitStatus != QProcess::NormalExit) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "分系统退出", 
            "分系统1异常退出，是否重新启动？",
            QMessageBox::Yes | QMessageBox::No
        );
        
        if (reply == QMessageBox::Yes) {
            startSubsystem1();
        }
    }
}
