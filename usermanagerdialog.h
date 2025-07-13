#ifndef USERMANAGERDIALOG_H
#define USERMANAGERDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCheckBox>
#include <QComboBox>
#include <QTextEdit>
#include <QStatusBar>
#include "struct.h"
#include "usermanager.h"
#include "groupmanager.h"
#include "permissionmanager.h"
#include "registerdialog.h"

namespace Ui {
class UserManagerDialog;
}

class UserManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UserManagerDialog(QWidget *parent = nullptr);
    ~UserManagerDialog();

private slots:
    // 用户列表相关
    void on_btnRefresh_clicked();
    void on_btnAddUser_clicked();
    void on_btnDeleteUser_clicked();
    void on_tableUsers_itemSelectionChanged();
    
    // 权限设置相关
    void on_comboGroup_currentIndexChanged(int index);
    void on_checkSubsystem1_toggled(bool checked);
    void on_checkSubsystem2_toggled(bool checked);
    void on_checkSubsystem3_toggled(bool checked);
    void on_checkSubsystem4_toggled(bool checked);
    void on_checkSubsystem5_toggled(bool checked);
    
    // 保存和重置
    void on_btnSave_clicked();
    void on_btnReset_clicked();

private:
    void setupUserTable();
    void loadUserList();
    void updatePermissionPreview();
    void loadUserPermissions(const User& user);
    void saveUserPermissions();
    void showStatusMessage(const QString& message);
    void clearPermissionForm();
    
    // 获取当前选中的用户
    User getCurrentUser();
    
    // 从UI控件获取权限设置
    RightToSystem getPermissionRestrictionsFromUI();
    
    // 设置UI控件显示权限
    void setPermissionRestrictionsToUI(const RightToSystem& restrictions);

private:
    Ui::UserManagerDialog *ui;
    QVector<User> m_users;           // 用户列表
    QVector<Group> m_groups;         // 权限组列表
    User m_currentUser;              // 当前选中的用户
    bool m_isLoading;                // 是否正在加载数据（防止信号循环）
    // comboBox index <-> group字段 映射
    int comboIndexToGroup(int index);
    int groupToComboIndex(int group);
};

#endif // USERMANAGERDIALOG_H
