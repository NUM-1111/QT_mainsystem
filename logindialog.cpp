#include "logindialog.h"
#include "ui_logindialog.h"
#include "registerdialog.h"
#include <QDebug>
#include "usermanager.h"
#include <QCryptographicHash>

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
    connect(ui->loginBtn, &QPushButton::clicked, this, &loginDialog::handleLoginBtnClicked);
    connect(ui->registerBtn, &QPushButton::clicked, this, &loginDialog::handleRegisterBtnClicked);
    connect(ui->usernameinput, &QLineEdit::returnPressed, this, &loginDialog::handleUsernameReturnPressed);
    connect(ui->passwordinput, &QLineEdit::returnPressed, this, &loginDialog::handlePasswordReturnPressed);
    
    // 设置默认焦点到用户名输入框
    ui->usernameinput->setFocus();
    
    qDebug() << "登录对话框初始化完成";
}

loginDialog::~loginDialog()
{
    delete ui;
}

void loginDialog::handleLoginBtnClicked()
{
    qDebug() << "登录按钮被点击";
    if (performLogin()) {
        accept();  // 登录成功，关闭对话框
    }
}

void loginDialog::handleRegisterBtnClicked()
{
    qDebug() << "=== 登录对话框：注册按钮被点击 ===";
    
    // 创建并显示注册对话框
    qDebug() << "创建注册对话框...";
    registerDialog regDialog(this);
    qDebug() << "显示注册对话框...";
    
    // 显示注册对话框，不管结果如何都继续
    regDialog.exec();
    qDebug() << "注册对话框已关闭";
    
    // 注册对话框关闭后，清空密码输入框，保持用户名
    ui->passwordinput->clear();
    ui->passwordinput->setFocus();
    qDebug() << "返回登录界面，密码框已清空";
}

void loginDialog::handleUsernameReturnPressed()
{
    qDebug() << "用户名输入框回车";
    // 回车时焦点移到密码输入框
    ui->passwordinput->setFocus();
}

void loginDialog::handlePasswordReturnPressed()
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

    // 查询用户
    User user;
    if (!UserManager::getUserByName(username, user)) {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重试");
        qDebug() << "用户" << username << "不存在";
        ui->passwordinput->clear();
        ui->passwordinput->setFocus();
        return false;
    }

    // 密码加密比对
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    if (user.password == hashedPassword) {
        UserManager::setCurrentUser(user);
        QMessageBox::information(this, "登录成功", QString("欢迎回来，%1！").arg(username));
        qDebug() << "用户" << username << "登录成功";
        return true;
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误，请重试");
        qDebug() << "用户" << username << "密码错误";
        ui->passwordinput->clear();
        ui->passwordinput->setFocus();
        return false;
    }
}
