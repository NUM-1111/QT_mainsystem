#include "groupmanagerdialog.h"
#include "ui_groupmanagerdialog.h"

GroupManagerDialog::GroupManagerDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GroupManagerDialog)
{
    ui->setupUi(this);
}

GroupManagerDialog::~GroupManagerDialog()
{
    delete ui;
}
