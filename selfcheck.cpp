#include "selfcheck.h"
#include "ui_selfcheck.h"
#include "mydata.h"

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

    socket = new QUdpSocket(this);

    MyData Data;
    quint16 tmp = Data.crc(Data.Header+14, 12);
    Data.Header[24] = tmp >> 8;
    Data.Header[25] = (quint8)tmp;

    QByteArray sendBuf(Data.Header, 26);
    socket->writeDatagram(sendBuf, QHostAddress("192.168.0.2"), 8888);
    if (socket->waitForReadyRead(200)){
        ui->label->setText("SelfCheck Succeed");
        QByteArray Buffer;
        Buffer.resize(socket->pendingDatagramSize());
        Buffer = socket->readAll();
        for (int i = 0; i < 7; ++i){
            quint8 flag = 1;
            if (Buffer[23+i] & flag) model->setData(model->index(1,i+1), "未知故障");
            if (Buffer[23+i] & flag << 1) model->setData(model->index(1,i+1), "主控单元故障");
            if (Buffer[23+i] & flag << 2) model->setData(model->index(1,i+1), "音频单元故障");
            if (Buffer[23+i] & flag << 3) model->setData(model->index(1,i+1), "无线单元故障");
            if (Buffer[23+i] & flag << 4) model->setData(model->index(1,i+1), "无线模块故障");
        }
        for (int i = 0; i < 7; ++i){
            quint8 flag = 1;
            if (Buffer[43+i] & flag) model->setData(model->index(1,i+1), "未知故障");
            if (Buffer[43+i] & flag << 1) model->setData(model->index(1,i+1), "主控单元故障");
            if (Buffer[43+i] & flag << 2) model->setData(model->index(1,i+1), "音频单元故障");
            if (Buffer[43+i] & flag << 3) model->setData(model->index(1,i+1), "无线单元故障");
            if (Buffer[43+i] & flag << 4) model->setData(model->index(1,i+1), "无线模块故障");
        }
    }else
        ui->label->setText("Error accured!");
   socket->close();
}

Selfcheck::~Selfcheck()
{
    delete ui;
}
