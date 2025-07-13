#ifndef GROUPMANAGERDIALOG_H
#define GROUPMANAGERDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QStatusBar>
#include "struct.h"
#include "groupmanager.h"

namespace Ui {
class GroupManagerDialog;
}

class GroupManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GroupManagerDialog(QWidget *parent = nullptr);
    ~GroupManagerDialog();

private slots:
    void on_btnAddGroup_clicked();
    void on_btnDeleteGroup_clicked();
    void on_btnSave_clicked();
    void on_btnReset_clicked();
    void on_tableGroups_itemSelectionChanged();
    void on_checkSubsystem1_toggled(bool checked);
    void on_checkSubsystem2_toggled(bool checked);
    void on_checkSubsystem3_toggled(bool checked);
    void on_checkSubsystem4_toggled(bool checked);
    void on_checkSubsystem5_toggled(bool checked);

private:
    void setupGroupTable();
    void loadGroupList();
    void loadGroupDetail(const Group& group);
    void saveGroupDetail();
    void clearGroupDetail();
    RightToSystem getRightsFromUI();
    void setRightsToUI(const RightToSystem& rights);
    void showStatusMessage(const QString& message);

    Ui::GroupManagerDialog *ui;
    QVector<Group> m_groups;
    Group m_currentGroup;
    bool m_isLoading;
};

#endif // GROUPMANAGERDIALOG_H
