#include "usermanagerdialog.h"
#include "ui_usermanagerdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QHeaderView>

UserManagerDialog::UserManagerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::UserManagerDialog)
    , m_isLoading(false)
{
    ui->setupUi(this);
    
    // 设置窗口标题
    setWindowTitle("用户权限管理");
    
    // 强制设置comboGroup条目顺序
    ui->comboGroup->clear();
    ui->comboGroup->addItem("无权限组");   // -1
    ui->comboGroup->addItem("管理员");     // 0
    ui->comboGroup->addItem("权限组1 (分系统1-3)"); // 1
    ui->comboGroup->addItem("权限组2 (分系统4-5)"); // 2
    
    // 初始化界面
    setupUserTable();
    
    // 加载数据
    loadUserList();
    
    // 初始化状态栏
    ui->statusBar->showMessage("就绪");
    
    // 清空权限表单
    clearPermissionForm();
}

UserManagerDialog::~UserManagerDialog()
{
    delete ui;
}

// comboBox index -> group
int UserManagerDialog::comboIndexToGroup(int index) {
    switch (index) {
        case 0: return -1; // 无权限组
        case 1: return 0;  // 管理员
        case 2: return 1;  // 权限组1
        case 3: return 2;  // 权限组2
        default: return -1;
    }
}
// group -> comboBox index
int UserManagerDialog::groupToComboIndex(int group) {
    switch (group) {
        case -1: return 0;
        case 0:  return 1;
        case 1:  return 2;
        case 2:  return 3;
        default: return 0;
    }
}

void UserManagerDialog::setupUserTable()
{
    // 设置表格列
    ui->tableUsers->setColumnCount(4);
    ui->tableUsers->setHorizontalHeaderLabels({"用户ID", "用户名", "权限组", "状态"});
    
    // 设置表格属性
    ui->tableUsers->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableUsers->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableUsers->setAlternatingRowColors(true);
    ui->tableUsers->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // 设置列宽
    ui->tableUsers->horizontalHeader()->setStretchLastSection(true);
    ui->tableUsers->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableUsers->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableUsers->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
}

void UserManagerDialog::loadUserList()
{
    // 清空表格
    ui->tableUsers->setRowCount(0);
    
    // 加载用户列表
    m_users = UserManager::getAllUsers();
    
    // 加载权限组列表
    m_groups = GroupManager::getAllGroups();
    
    // 填充表格
    for (const User& user : m_users) {
        qDebug() << "User:" << user.id << user.name << "group=" << user.group;
        int row = ui->tableUsers->rowCount();
        ui->tableUsers->insertRow(row);
        
        // 用户ID
        ui->tableUsers->setItem(row, 0, new QTableWidgetItem(QString::number(user.id)));
        
        // 用户名
        ui->tableUsers->setItem(row, 1, new QTableWidgetItem(user.name));
        
        // 权限组
        QString groupText = user.getUserTypeDescription();
        ui->tableUsers->setItem(row, 2, new QTableWidgetItem(groupText));
        
        // 状态（计算最终权限）
        User userWithRights = PermissionManager::getInstance().calculateUserFinalRights(user);
        QString status = userWithRights.getFinalRightsDescription();
        ui->tableUsers->setItem(row, 3, new QTableWidgetItem(status));
    }
    
    showStatusMessage(QString("已加载 %1 个用户").arg(m_users.size()));
}

void UserManagerDialog::on_btnRefresh_clicked()
{
    loadUserList();
}

void UserManagerDialog::on_btnAddUser_clicked()
{
    QMessageBox::information(this, "提示", "添加用户功能需要实现注册对话框");
}

void UserManagerDialog::on_btnDeleteUser_clicked()
{
    int currentRow = ui->tableUsers->currentRow();
    if (currentRow < 0) {
        QMessageBox::warning(this, "警告", "请先选择要删除的用户");
        return;
    }
    
    int userId = ui->tableUsers->item(currentRow, 0)->text().toInt();
    QString userName = ui->tableUsers->item(currentRow, 1)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "确认删除", 
        QString("确定要删除用户 '%1' 吗？").arg(userName),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        if (UserManager::deleteUser(userId)) {
            showStatusMessage(QString("用户 '%1' 删除成功").arg(userName));
            loadUserList();
        } else {
            QMessageBox::critical(this, "错误", "删除用户失败");
        }
    }
}

void UserManagerDialog::on_tableUsers_itemSelectionChanged()
{
    int currentRow = ui->tableUsers->currentRow();
    if (currentRow >= 0 && currentRow < m_users.size()) {
        m_currentUser = m_users[currentRow];
        loadUserPermissions(m_currentUser);
    } else {
        clearPermissionForm();
    }
}

void UserManagerDialog::loadUserPermissions(const User& user)
{
    m_isLoading = true;
    
    // 设置用户名
    ui->editUsername->setText(user.name);
    
    // 设置权限组
    int groupIndex = groupToComboIndex(user.group);
    if (groupIndex >= 0 && groupIndex < ui->comboGroup->count()) {
        ui->comboGroup->setCurrentIndex(groupIndex);
    }
    
    // 设置个人权限限制
    setPermissionRestrictionsToUI(user.rights);
    
    // 更新权限预览
    updatePermissionPreview();
    
    m_isLoading = false;
}

void UserManagerDialog::setPermissionRestrictionsToUI(const RightToSystem& restrictions)
{
    ui->checkSubsystem1->setChecked(restrictions.getSubsystemRight(0));
    ui->checkSubsystem2->setChecked(restrictions.getSubsystemRight(1));
    ui->checkSubsystem3->setChecked(restrictions.getSubsystemRight(2));
    ui->checkSubsystem4->setChecked(restrictions.getSubsystemRight(3));
    ui->checkSubsystem5->setChecked(restrictions.getSubsystemRight(4));
}

RightToSystem UserManagerDialog::getPermissionRestrictionsFromUI()
{
    RightToSystem restrictions;
    restrictions.setSubsystemRight(0, ui->checkSubsystem1->isChecked());
    restrictions.setSubsystemRight(1, ui->checkSubsystem2->isChecked());
    restrictions.setSubsystemRight(2, ui->checkSubsystem3->isChecked());
    restrictions.setSubsystemRight(3, ui->checkSubsystem4->isChecked());
    restrictions.setSubsystemRight(4, ui->checkSubsystem5->isChecked());
    return restrictions;
}

void UserManagerDialog::on_comboGroup_currentIndexChanged(int index)
{
    if (!m_isLoading) {
        updatePermissionPreview();
    }
}

void UserManagerDialog::on_checkSubsystem1_toggled(bool checked)
{
    if (!m_isLoading) {
        updatePermissionPreview();
    }
}

void UserManagerDialog::on_checkSubsystem2_toggled(bool checked)
{
    if (!m_isLoading) {
        updatePermissionPreview();
    }
}

void UserManagerDialog::on_checkSubsystem3_toggled(bool checked)
{
    if (!m_isLoading) {
        updatePermissionPreview();
    }
}

void UserManagerDialog::on_checkSubsystem4_toggled(bool checked)
{
    if (!m_isLoading) {
        updatePermissionPreview();
    }
}

void UserManagerDialog::on_checkSubsystem5_toggled(bool checked)
{
    if (!m_isLoading) {
        updatePermissionPreview();
    }
}

void UserManagerDialog::updatePermissionPreview()
{
    if (m_currentUser.id == -1) {
        ui->textPreview->setText("请先选择用户");
        return;
    }
    
    // 获取当前权限组
    int groupIndex = ui->comboGroup->currentIndex();
    int groupId = comboIndexToGroup(groupIndex); // 0->-1, 1->0, 2->1, 3->2
    
    // 获取个人权限限制
    RightToSystem restrictions = getPermissionRestrictionsFromUI();
    
    // 计算最终权限
    User tempUser = m_currentUser;
    tempUser.group = groupId;
    tempUser.rights = restrictions;
    
    User userWithRights = PermissionManager::getInstance().calculateUserFinalRights(tempUser);
    
    // 生成预览文本
    QString previewText;
    if (groupId == 0) {
        previewText = "管理员权限：可以访问所有分系统";
    } else if (groupId > 0) {
        QStringList accessibleSystems = userWithRights.finalRights.getAccessibleSubsystems();
        QStringList restrictedSystems = userWithRights.finalRights.getInaccessibleSubsystems();
        
        previewText = QString("最终权限：\n");
        if (!accessibleSystems.isEmpty()) {
            previewText += QString("✅ 可访问：%1\n").arg(accessibleSystems.join(", "));
        }
        if (!restrictedSystems.isEmpty()) {
            previewText += QString("❌ 不可访问：%1").arg(restrictedSystems.join(", "));
        }
    } else {
        previewText = "无权限组：无法访问任何分系统";
    }
    
    ui->textPreview->setText(previewText);
}

void UserManagerDialog::on_btnSave_clicked()
{
    if (m_currentUser.id == -1) {
        QMessageBox::warning(this, "警告", "请先选择用户");
        return;
    }
    
    // 获取当前设置
    int groupIndex = ui->comboGroup->currentIndex();
    int groupId = comboIndexToGroup(groupIndex);
    RightToSystem restrictions = getPermissionRestrictionsFromUI();
    
    // 更新用户信息
    User updatedUser = m_currentUser;
    updatedUser.group = groupId;
    updatedUser.rights = restrictions;
    
    // 保存到数据库
    if (UserManager::updateUser(updatedUser)) {
        showStatusMessage(QString("用户 '%1' 权限设置保存成功").arg(updatedUser.name));
        loadUserList(); // 刷新列表
    } else {
        QMessageBox::critical(this, "错误", "保存权限设置失败");
    }
}

void UserManagerDialog::on_btnReset_clicked()
{
    if (m_currentUser.id != -1) {
        loadUserPermissions(m_currentUser);
    }
}

void UserManagerDialog::clearPermissionForm()
{
    ui->editUsername->clear();
    ui->comboGroup->setCurrentIndex(0);
    ui->checkSubsystem1->setChecked(false);
    ui->checkSubsystem2->setChecked(false);
    ui->checkSubsystem3->setChecked(false);
    ui->checkSubsystem4->setChecked(false);
    ui->checkSubsystem5->setChecked(false);
    ui->textPreview->clear();
}

User UserManagerDialog::getCurrentUser()
{
    return m_currentUser;
}

void UserManagerDialog::showStatusMessage(const QString& message)
{
    ui->statusBar->showMessage(message);
    qDebug() << "[用户管理]" << message;
}
