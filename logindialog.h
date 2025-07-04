#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "databasemanager.h"

namespace Ui {
class loginDialog;
}

class loginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit loginDialog(QWidget *parent = nullptr);
    ~loginDialog();

private slots:
    /**
     * @brief 登录按钮点击事件
     */
    void on_loginBtn_clicked();
    
    /**
     * @brief 注册按钮点击事件
     */
    void on_registerBtn_clicked();
    
    /**
     * @brief 用户名输入框回车事件
     */
    void on_usernameinput_returnPressed();
    
    /**
     * @brief 密码输入框回车事件
     */
    void on_passwordinput_returnPressed();

private:
    /**
     * @brief 验证输入内容
     * @return 验证是否通过
     */
    bool validateInput();
    
    /**
     * @brief 执行登录操作
     * @return 登录是否成功
     */
    bool performLogin();

private:
    Ui::loginDialog *ui;
    DatabaseManager& m_dbManager;  ///< 数据库管理器引用
};

#endif // LOGINDIALOG_H
