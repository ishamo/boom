#include "record.h"
#include "ui_record.h"
#include <QFileSystemModel>
#include <QTreeView>
#include <QDir>

Record::Record(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Record)
{
    ui->setupUi(this);
    ui->label->setText(QDir::currentPath());
}

Record::~Record()
{
    delete ui;
}

void Record::on_pushButton_4_clicked()
{
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    QTreeView *tree = new QTreeView;
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));
    tree->show();
}
