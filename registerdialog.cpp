#include "registerdialog.h"
#include "ui_registerdialog.h"
#include <QDebug>
#include <QRegExp>

registerDialog::registerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registerDialog)
    , m_dbManager(DatabaseManager::getInstance())
{
    ui->setupUi(this);
    
    // 设置窗口标题
    setWindowTitle("用户注册");
    
    // 设置密码输入框为密码模式
    ui->passwordinput->setEchoMode(QLineEdit::Password);
    ui->passwordsureinput->setEchoMode(QLineEdit::Password);
    
    // 设置输入框占位符文本
    ui->usernameinput->setPlaceholderText("请输入用户名（3-20个字符）");
    ui->passwordinput->setPlaceholderText("请输入密码（6-20个字符）");
    ui->passwordsureinput->setPlaceholderText("请再次输入密码");
    
    // 连接信号和槽
    connect(ui->registerBtn, &QPushButton::clicked, this, &registerDialog::on_registerBtn_clicked);
    connect(ui->backtologinBtn, &QPushButton::clicked, this, &registerDialog::on_backtologinBtn_clicked);
    connect(ui->usernameinput, &QLineEdit::returnPressed, this, &registerDialog::on_usernameinput_returnPressed);
    connect(ui->passwordinput, &QLineEdit::returnPressed, this, &registerDialog::on_passwordinput_returnPressed);
    connect(ui->passwordsureinput, &QLineEdit::returnPressed, this, &registerDialog::on_passwordsureinput_returnPressed);
    
    // 设置默认焦点到用户名输入框
    ui->usernameinput->setFocus();
    
    qDebug() << "注册对话框初始化完成";
}

registerDialog::~registerDialog()
{
    delete ui;
}

void registerDialog::on_registerBtn_clicked()
{
    qDebug() << "注册按钮被点击";
    if (performRegistration()) {
        accept();  // 注册成功，关闭对话框
    }
}

void registerDialog::on_backtologinBtn_clicked()
{
    qDebug() << "返回登录按钮被点击";
    reject();  // 返回登录界面
}

void registerDialog::on_usernameinput_returnPressed()
{
    qDebug() << "用户名输入框回车";
    // 回车时焦点移到密码输入框
    ui->passwordinput->setFocus();
}

void registerDialog::on_passwordinput_returnPressed()
{
    qDebug() << "密码输入框回车";
    // 回车时焦点移到确认密码输入框
    ui->passwordsureinput->setFocus();
}

void registerDialog::on_passwordsureinput_returnPressed()
{
    qDebug() << "确认密码输入框回车";
    // 回车时执行注册
    if (performRegistration()) {
        accept();
    }
}

bool registerDialog::validateInput()
{
    QString username = ui->usernameinput->text().trimmed();
    QString password = ui->passwordinput->text();
    QString passwordConfirm = ui->passwordsureinput->text();
    
    // 检查用户名是否为空
    if (username.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入用户名");
        ui->usernameinput->setFocus();
        return false;
    }
    
    // 检查用户名长度
    if (username.length() < 3 || username.length() > 20) {
        QMessageBox::warning(this, "输入错误", "用户名长度必须在3-20个字符之间");
        ui->usernameinput->setFocus();
        return false;
    }
    
    // 检查用户名格式（只允许字母、数字、下划线）
    QRegExp usernameRegex("^[a-zA-Z0-9_]+$");
    if (!usernameRegex.exactMatch(username)) {
        QMessageBox::warning(this, "输入错误", "用户名只能包含字母、数字和下划线");
        ui->usernameinput->setFocus();
        return false;
    }
    
    // 检查密码是否为空
    if (password.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入密码");
        ui->passwordinput->setFocus();
        return false;
    }
    
    // 检查密码长度
    if (password.length() < 6 || password.length() > 20) {
        QMessageBox::warning(this, "输入错误", "密码长度必须在6-20个字符之间");
        ui->passwordinput->setFocus();
        return false;
    }
    
    // 检查确认密码是否为空
    if (passwordConfirm.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请确认密码");
        ui->passwordsureinput->setFocus();
        return false;
    }
    
    // 检查两次密码是否一致
    if (password != passwordConfirm) {
        QMessageBox::warning(this, "输入错误", "两次输入的密码不一致");
        ui->passwordsureinput->clear();
        ui->passwordsureinput->setFocus();
        return false;
    }
    
    return true;
}

bool registerDialog::isUsernameAvailable(const QString &username)
{
    // 检查数据库连接
    if (!m_dbManager.isConnected()) {
        QMessageBox::critical(this, "系统错误", "数据库连接失败，请检查系统配置");
        return false;
    }
    
    // 检查用户名是否已存在
    return !m_dbManager.isUserExists(username);
}

bool registerDialog::performRegistration()
{
    // 验证输入
    if (!validateInput()) {
        return false;
    }
    
    QString username = ui->usernameinput->text().trimmed();
    QString password = ui->passwordinput->text();
    
    qDebug() << "尝试注册用户:" << username;
    
    // 检查数据库连接
    if (!m_dbManager.isConnected()) {
        QMessageBox::critical(this, "系统错误", "数据库连接失败，请检查系统配置");
        qDebug() << "数据库未连接";
        return false;
    }
    
    // 检查用户名是否可用
    if (!isUsernameAvailable(username)) {
        QMessageBox::warning(this, "注册失败", "用户名已存在，请选择其他用户名");
        ui->usernameinput->setFocus();
        ui->usernameinput->selectAll();
        qDebug() << "用户名" << username << "已存在";
        return false;
    }
    
    // 执行注册
    if (m_dbManager.registerUser(username, password)) {
        QMessageBox::information(this, "注册成功", QString("用户 %1 注册成功！\n请返回登录界面进行登录。").arg(username));
        qDebug() << "用户" << username << "注册成功";
        return true;
    } else {
        QMessageBox::critical(this, "注册失败", "注册过程中发生错误，请重试");
        qDebug() << "用户" << username << "注册失败";
        return false;
    }
}
