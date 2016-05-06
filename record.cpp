#include "record.h"
#include "ui_record.h"
#include <stdlib.h>


Record::Record(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Record)
{
    ui->setupUi(this);
    ui->label->setText(QDir::currentPath());
    myProcess = NULL;

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

void Record::on_pushButton_3_clicked()
{
    if (myProcess)
        myProcess->close();

    qDebug() << "recorder stopped";
}

void Record::on_pushButton_clicked()
{
    //QString program = "/home/ishamo/code/qt/boom/recorder";
   // QStringList arguments;
    //arguments << "-style" << "fusion";

    myProcess = new QProcess(this);
    //myProcess->start(program, arguments);
    //myProcess->start("/home/ishamo/zdw/zdw/test");
    myProcess->start("./recorder");

    qDebug() << "recorder start??";
}
