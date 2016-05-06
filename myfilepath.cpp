#include "myfilepath.h"
#include "ui_myfilepath.h"

MyFilePath::MyFilePath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyFilePath)
{
    ui->setupUi(this);
    filemodel = new QFileSystemModel(this);
    filemodel->setRootPath(QDir::currentPath());
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->treeView->setModel(filemodel);

}

MyFilePath::~MyFilePath()
{
    delete ui;
}

void MyFilePath::on_treeView_clicked(const QModelIndex &index)
{
    dirpath = filemodel->fileInfo(index).absoluteFilePath();
    //dirpath = filemodel->fileInfo(index).absoluteDir().absolutePath();
    emit SendPath(dirpath);
}
