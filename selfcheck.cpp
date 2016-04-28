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
    socket->bind(8888);
    MyData Data;
    quint16 tmp = Data.crc(Data.Header+14, 9);


    Data.Header[23] = tmp >> 8;
    Data.Header[24] = (qint8)tmp;

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    QByteArray sendBuf(Data.Header, 25);
    qint64 ret = socket->writeDatagram(sendBuf, QHostAddress("192.168.0.100"), 8888);
    if (ret<=0) qDebug() << "Send error";
    /*
    if (socket->waitForReadyRead(200)){
        ui->label->setText("SelfCheck Succeed");
    }else
        ui->label->setText("Error accured!");
        */
   //socket->close();
}

Selfcheck::~Selfcheck()
{
    delete ui;
}

void Selfcheck::setlabel(quint8 data, QModelIndex index)
{
    quint8 flag = 1;
    QString message;
    if (data == 0xff) {
        message = "状态未知";
        model->setData(index, message);
        return;
    }
    if (data == 0) {
        message = "无故障";
        model->setData(index, message);
        return;
    }
    if (data & flag) message += "未知故障";
    if (data & flag << 1) message += "主控单元故障";
    if (data & flag << 2) message += "音频单元故障";
    if (data & flag << 3) message += "无线单元故障";
    if (data & flag << 4) message += "无线模块故障";
    model->setData(index, message);
}

void Selfcheck::readyRead()
{
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());
    //Buffer = socket->readAll();
    QHostAddress Sender;
    quint16 Port;
    ui->label->setText("SelfCheck succeed");
    socket->readDatagram(Buffer.data(), Buffer.size(), &Sender, &Port);
    qDebug() << Buffer;
    setlabel(Buffer[23], model->index(1, 1));
    setlabel(Buffer[24], model->index(1, 2));
    setlabel(Buffer[25], model->index(1, 3));
    setlabel(Buffer[26], model->index(1, 4));
    setlabel(Buffer[27], model->index(1, 5));
    setlabel(Buffer[28], model->index(1, 6));
    setlabel(Buffer[29], model->index(1, 7));


    setlabel(Buffer[41], model->index(2, 1));
    setlabel(Buffer[42], model->index(2, 2));
    setlabel(Buffer[43], model->index(2, 3));
    setlabel(Buffer[44], model->index(2, 4));
    setlabel(Buffer[45], model->index(2, 5));
    setlabel(Buffer[46], model->index(2, 6));
    setlabel(Buffer[47], model->index(2, 7));

    /*
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
    */
}
