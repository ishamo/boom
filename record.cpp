#include "record.h"
#include "ui_record.h"



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
    savepath = new SelectPath(this);
    connect(savepath, SIGNAL(SendData(QString)), this, SLOT(ReceiveData(QString)));
    savepath->setModal(true);
    savepath->exec();
}

void Record::ReceiveData(QString data)
{
    ui->label->setText(data);
}
