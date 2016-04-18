#include "file.h"
#include "ui_file.h"

File::File(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::File)
{
    ui->setupUi(this);
    filename = new QFileSystemModel(this);
    dirname = new QFileSystemModel(this);
    QString spath = "/home/ishamo";
    filename->setRootPath(spath);
    dirname->setRootPath(spath);
    filename->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    dirname->setFilter(QDir::NoDotAndDotDot | QDir::AllDirs);
    ui->treeView->setModel(dirname);
    ui->listView->setModel(filename);
}

File::~File()
{
    delete ui;
}

void File::on_treeView_clicked(const QModelIndex &index)
{
    QString sPath = dirname->fileInfo(index).absoluteFilePath();
    ui->listView->setRootIndex(filename->setRootPath(sPath));
}

void File::on_listView_clicked(const QModelIndex &index)
{
    filepath = filename->fileInfo(index).absoluteFilePath();
}

void File::on_buttonBox_accepted()
{
    emit SendData(filepath);
}
