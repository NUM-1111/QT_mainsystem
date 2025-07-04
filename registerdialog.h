#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include "databasemanager.h"

namespace Ui {
class registerDialog;
}

class registerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit registerDialog(QWidget *parent = nullptr);
    ~registerDialog();

private slots:
    /**
     * @brief 注册按钮点击事件
     */
    void handleRegisterBtnClicked();
    
    /**
     * @brief 返回登录按钮点击事件
     */
    void handleBackToLoginBtnClicked();
    
    /**
     * @brief 用户名输入框回车事件
     */
    void handleUsernameReturnPressed();
    
    /**
     * @brief 密码输入框回车事件
     */
    void handlePasswordReturnPressed();
    
    /**
     * @brief 确认密码输入框回车事件
     */
    void handlePasswordConfirmReturnPressed();

private:
    /**
     * @brief 验证输入内容
     * @return 验证是否通过
     */
    bool validateInput();
    
    /**
     * @brief 执行注册操作
     * @return 注册是否成功
     */
    bool performRegistration();
    
    /**
     * @brief 检查用户名是否可用
     * @param username 用户名
     * @return 是否可用
     */
    bool isUsernameAvailable(const QString &username);

private:
    Ui::registerDialog *ui;
    DatabaseManager& m_dbManager;  ///< 数据库管理器引用
};

#endif // REGISTERDIALOG_H
