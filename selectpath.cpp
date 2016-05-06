#include "selectpath.h"
#include "ui_selectpath.h"

SelectPath::SelectPath(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectPath)
{
    ui->setupUi(this);
    filemodel = new QFileSystemModel(this);
    QString spath = QDir::currentPath();
    filemodel->setRootPath(spath);
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->treeView->setModel(filemodel);
}

SelectPath::~SelectPath()
{
    delete ui;
}

void SelectPath::on_buttonBox_accepted()
{
    emit SendData(filepath);
}

void SelectPath::on_treeView_clicked(const QModelIndex &index)
{
    filepath = filemodel->fileInfo(index).absoluteFilePath();
}
