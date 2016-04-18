#include "record.h"
#include "ui_record.h"
#include <QFileSystemModel>
#include <QTreeView>
#include <QDir>
#include <QString>
#include <QDebug>
#include <QLayout>

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
    QString path = "..";
    QDir dir;
    dir.setCurrent(path);
    if (!dir.exists())
        qDebug() << "path is not exist";
    QFileSystemModel *dirname = new QFileSystemModel;
    QFileSystemModel *filename = new QFileSystemModel;
    dirname->setRootPath(path);
    filename->setRootPath(path);

    filesystem = new QWidget(this);

    filesystem->show();
    /*
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    QTreeView *tree = new QTreeView;
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));
    tree->show();
    */
}
