#include "logindialog.h"
#include "ui_logindialog.h"
#include "registerdialog.h"
#include <QDebug>

loginDialog::loginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::loginDialog)
    , m_dbManager(DatabaseManager::getInstance())
{
    ui->setupUi(this);
    
    // 设置窗口标题
    setWindowTitle("用户登录");
    
    // 设置密码输入框为密码模式
    ui->passwordinput->setEchoMode(QLineEdit::Password);
    
    // 设置输入框占位符文本
    ui->usernameinput->setPlaceholderText("请输入用户名");
    ui->passwordinput->setPlaceholderText("请输入密码");
    
    // 连接信号和槽
    connect(ui->loginBtn, &QPushButton::clicked, this, &loginDialog::on_loginBtn_clicked);
    connect(ui->registerBtn, &QPushButton::clicked, this, &loginDialog::on_registerBtn_clicked);
    connect(ui->usernameinput, &QLineEdit::returnPressed, this, &loginDialog::on_usernameinput_returnPressed);
    connect(ui->passwordinput, &QLineEdit::returnPressed, this, &loginDialog::on_passwordinput_returnPressed);
    
    // 设置默认焦点到用户名输入框
    ui->usernameinput->setFocus();
    
    qDebug() << "登录对话框初始化完成";
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::on_loginBtn_clicked()
{
    qDebug() << "登录按钮被点击";
    if (performLogin()) {
        accept();  // 登录成功，关闭对话框
    }
}

void loginDialog::on_registerBtn_clicked()
{
    qDebug() << "注册按钮被点击";
    
    // 创建并显示注册对话框
    registerDialog regDialog(this);
    if (regDialog.exec() == QDialog::Accepted) {
        // 注册成功，清空密码输入框，保持用户名
        ui->passwordinput->clear();
        ui->passwordinput->setFocus();
        qDebug() << "用户注册成功，返回登录界面";
    }
}

void loginDialog::on_usernameinput_returnPressed()
{
    qDebug() << "用户名输入框回车";
    // 回车时焦点移到密码输入框
    ui->passwordinput->setFocus();
}

void loginDialog::on_passwordinput_returnPressed()
{
    qDebug() << "密码输入框回车";
    // 回车时执行登录
    if (performLogin()) {
        accept();
    }
}

bool loginDialog::validateInput()
{
    QString username = ui->usernameinput->text().trimmed();
    QString password = ui->passwordinput->text();
    
    // 检查用户名是否为空
    if (username.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入用户名");
        ui->usernameinput->setFocus();
        return false;
    }
    
    // 检查密码是否为空
    if (password.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入密码");
        ui->passwordinput->setFocus();
        return false;
    }
    
    // 检查用户名长度
    if (username.length() < 3) {
        QMessageBox::warning(this, "输入错误", "用户名长度不能少于3个字符");
        ui->usernameinput->setFocus();
        return false;
    }
    
    // 检查密码长度
    if (password.length() < 6) {
        QMessageBox::warning(this, "输入错误", "密码长度不能少于6个字符");
        ui->passwordinput->setFocus();
        return false;
    }
    
    return true;
}

bool loginDialog::performLogin()
{
    // 验证输入
    if (!validateInput()) {
        return false;
    }
    
    QString username = ui->usernameinput->text().trimmed();
    QString password = ui->passwordinput->text();
    
    qDebug() << "尝试登录用户:" << username;
    
    // 检查数据库连接
    if (!m_dbManager.isConnected()) {
        QMessageBox::critical(this, "系统错误", "数据库连接失败，请检查系统配置");
        qDebug() << "数据库未连接";
        return false;
    }
    
    // 执行登录验证
    if (m_dbManager.loginUser(username, password)) {
        QMessageBox::information(this, "登录成功", QString("欢迎回来，%1！").arg(username));
        qDebug() << "用户" << username << "登录成功";
        return true;
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重试");
        qDebug() << "用户" << username << "登录失败";
        
        // 清空密码输入框，保持用户名
        ui->passwordinput->clear();
        ui->passwordinput->setFocus();
        return false;
    }
}
