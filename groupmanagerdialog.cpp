#include "groupmanagerdialog.h"
#include "ui_groupmanagerdialog.h"
#include <QMessageBox>
#include <QDebug>
#include <QHeaderView>

GroupManagerDialog::GroupManagerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GroupManagerDialog)
    , m_isLoading(false)
{
    ui->setupUi(this);
    Q_ASSERT(ui->editGroupName);
    Q_ASSERT(ui->checkSubsystem1);
    Q_ASSERT(ui->checkSubsystem2);
    Q_ASSERT(ui->checkSubsystem3);
    Q_ASSERT(ui->checkSubsystem4);
    Q_ASSERT(ui->checkSubsystem5);
    qDebug() << "[DEBUG] 所有UI控件初始化完毕";
    setWindowTitle("权限组管理");
    // 组名不可编辑
    ui->editGroupName->setReadOnly(true);
    // 初始化表格
    setupGroupTable();
    // 加载数据
    loadGroupList();
    // 状态栏
    ui->statusBar->showMessage("就绪");
    // 清空详情
    clearGroupDetail();
    qDebug() << "[DEBUG] 构造函数结束";
}

GroupManagerDialog::~GroupManagerDialog()
{
    delete ui;
}

void GroupManagerDialog::setupGroupTable()
{
    ui->tableGroups->setColumnCount(3);
    ui->tableGroups->setHorizontalHeaderLabels({"组ID", "组名", "可访问分系统"});
    ui->tableGroups->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableGroups->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableGroups->setAlternatingRowColors(true);
    ui->tableGroups->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableGroups->horizontalHeader()->setStretchLastSection(true);
    ui->tableGroups->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    ui->tableGroups->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableGroups->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
}

void GroupManagerDialog::loadGroupList()
{
    ui->tableGroups->setRowCount(0);
    m_groups = GroupManager::getAllGroups();
    for (const Group& group : m_groups) {
        int row = ui->tableGroups->rowCount();
        ui->tableGroups->insertRow(row);
        ui->tableGroups->setItem(row, 0, new QTableWidgetItem(QString::number(group.group_id)));
        ui->tableGroups->setItem(row, 1, new QTableWidgetItem(group.group_name));
        ui->tableGroups->setItem(row, 2, new QTableWidgetItem(group.rights.getAccessibleSubsystems().join(", ")));
    }
    showStatusMessage(QString("已加载 %1 个权限组").arg(m_groups.size()));
    if (ui->tableGroups->rowCount() > 0)
        ui->tableGroups->selectRow(0);
}

void GroupManagerDialog::on_tableGroups_itemSelectionChanged()
{
    int row = ui->tableGroups->currentRow();
    qDebug() << "[DEBUG] 当前选中行:" << row << "m_groups.size()=" << m_groups.size();
    if (row >= 0 && row < m_groups.size()) {
        m_currentGroup = m_groups[row];
        loadGroupDetail(m_currentGroup);
    } else {
        clearGroupDetail();
    }
}

void GroupManagerDialog::loadGroupDetail(const Group& group)
{
    m_isLoading = true;
    qDebug() << "[DEBUG] 加载组:" << group.group_id << group.group_name;
    if (ui->editGroupName) ui->editGroupName->setText(group.group_name);
    setRightsToUI(group.rights);
    m_isLoading = false;
}

void GroupManagerDialog::setRightsToUI(const RightToSystem& rights)
{
    qDebug() << "[DEBUG] setRightsToUI begin";
    if (ui->checkSubsystem1) { qDebug() << "[DEBUG] set checkSubsystem1"; ui->checkSubsystem1->setChecked(rights.getSubsystemRight(0)); }
    if (ui->checkSubsystem2) { qDebug() << "[DEBUG] set checkSubsystem2"; ui->checkSubsystem2->setChecked(rights.getSubsystemRight(1)); }
    if (ui->checkSubsystem3) { qDebug() << "[DEBUG] set checkSubsystem3"; ui->checkSubsystem3->setChecked(rights.getSubsystemRight(2)); }
    if (ui->checkSubsystem4) { qDebug() << "[DEBUG] set checkSubsystem4"; ui->checkSubsystem4->setChecked(rights.getSubsystemRight(3)); }
    if (ui->checkSubsystem5) { qDebug() << "[DEBUG] set checkSubsystem5"; ui->checkSubsystem5->setChecked(rights.getSubsystemRight(4)); }
    qDebug() << "[DEBUG] setRightsToUI end";
}

RightToSystem GroupManagerDialog::getRightsFromUI()
{
    RightToSystem rights;
    rights.setSubsystemRight(0, ui->checkSubsystem1->isChecked());
    rights.setSubsystemRight(1, ui->checkSubsystem2->isChecked());
    rights.setSubsystemRight(2, ui->checkSubsystem3->isChecked());
    rights.setSubsystemRight(3, ui->checkSubsystem4->isChecked());
    rights.setSubsystemRight(4, ui->checkSubsystem5->isChecked());
    return rights;
}

void GroupManagerDialog::on_btnAddGroup_clicked()
{
    QMessageBox::information(this, "提示", "添加组功能暂未实现");
}

void GroupManagerDialog::on_btnDeleteGroup_clicked()
{
    QMessageBox::information(this, "提示", "删除组功能暂未实现");
}

void GroupManagerDialog::on_btnSave_clicked()
{
    if (m_currentGroup.group_id == -1) {
        QMessageBox::warning(this, "警告", "请先选择要编辑的权限组");
        return;
    }
    // 只允许编辑权限
    RightToSystem newRights = getRightsFromUI();
    Group updatedGroup = m_currentGroup;
    updatedGroup.rights = newRights;
    if (GroupManager::updateGroup(updatedGroup)) {
        showStatusMessage(QString("权限组 '%1' 权限已保存").arg(updatedGroup.group_name));
        loadGroupList();
        // 重新选中当前组
        for (int row = 0; row < ui->tableGroups->rowCount(); ++row) {
            if (ui->tableGroups->item(row, 0)->text().toInt() == updatedGroup.group_id) {
                ui->tableGroups->selectRow(row);
                break;
            }
        }
    } else {
        QMessageBox::critical(this, "错误", "保存权限失败");
    }
}

void GroupManagerDialog::on_btnReset_clicked()
{
    if (m_currentGroup.group_id != -1) {
        loadGroupDetail(m_currentGroup);
    }
}

void GroupManagerDialog::on_checkSubsystem1_toggled(bool) { if (!m_isLoading) {} }
void GroupManagerDialog::on_checkSubsystem2_toggled(bool) { if (!m_isLoading) {} }
void GroupManagerDialog::on_checkSubsystem3_toggled(bool) { if (!m_isLoading) {} }
void GroupManagerDialog::on_checkSubsystem4_toggled(bool) { if (!m_isLoading) {} }
void GroupManagerDialog::on_checkSubsystem5_toggled(bool) { if (!m_isLoading) {} }

void GroupManagerDialog::clearGroupDetail()
{
    qDebug() << "[DEBUG] clearGroupDetail";
    qDebug() << "[DEBUG] editGroupName pointer:" << ui->editGroupName;
    qDebug() << "[DEBUG] editGroupName metaObject:" << (ui->editGroupName ? ui->editGroupName->metaObject()->className() : "nullptr");
    Q_ASSERT(ui->editGroupName);
    ui->editGroupName->clear();
    qDebug() << "[DEBUG] editGroupName cleared";
    setRightsToUI(RightToSystem());
    qDebug() << "[DEBUG] clearGroupDetail end";
}

void GroupManagerDialog::showStatusMessage(const QString& message)
{
    ui->statusBar->showMessage(message);
    qDebug() << "[权限组管理]" << message;
}
