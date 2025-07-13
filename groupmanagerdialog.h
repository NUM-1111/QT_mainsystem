#ifndef GROUPMANAGERDIALOG_H
#define GROUPMANAGERDIALOG_H

#include <QDialog>

namespace Ui {
class GroupManagerDialog;
}

class GroupManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GroupManagerDialog(QWidget *parent = nullptr);
    ~GroupManagerDialog();

private:
    Ui::GroupManagerDialog *ui;
};

#endif // GROUPMANAGERDIALOG_H
