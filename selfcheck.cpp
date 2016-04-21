#include "selfcheck.h"
#include "ui_selfcheck.h"

Selfcheck::Selfcheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selfcheck)
{
    ui->setupUi(this);
    model = new QStandardItemModel(3, 8);
    ui->tableView->setModel(model);

    QModelIndex index = model->index(1, 0);
    model->setData(index, "自检结果");

    index = model->index(2, 0);
    model->setData(index, "运行状态");

     index = model->index(0, 1);
    model->setData(index, "控制盒");

    index = model->index(0, 2);
    model->setData(index, "炮长");

    index = model->index(0, 3);
    model->setData(index, "乘员1");

    index = model->index(0, 4);
    model->setData(index, "乘员2");

    index = model->index(0, 5);
    model->setData(index, "乘员3");

    index = model->index(0,6);
    model->setData(index, "乘员4");

    index = model->index(0, 7);
    model->setData(index, "乘员5");
}

Selfcheck::~Selfcheck()
{
    delete ui;
}
