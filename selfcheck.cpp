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

    socket = new QUdpSocket(this);

    char Data[30];
    Data[0] = 1;
    Data[1] = 0;
    Data[2] = 14;
    Data[3] = 0;
    Data[4] = 0;
    Data[5] = 1;
    Data[6] = 127;
    //source address, i ve not count it, just set it as 127.0.0.1
    Data[7] = 0;
    Data[8] = 0;
    Data[9] = 1;
    Data[10] = 192;
    Data[11] = 168;
    Data[12] = 0;
    Data[13] = 2;
    Data[14] = 0;   //length
    Data[15] =
    Data[16] = 0;   //first send, if not received , have to try it third times. And if third times ,tihs byte need to be set as 1.
    Data[17] = 0;
    Data[18] = 0;
    Data[19] = 0;
    Data[20] = 1;
    Data[21] = 0;
    Data[22] = 0;
    // two bytes for crc, just set  it 0, i ven't count it
    Data[23] = 0;
    Data[24] = 0;
    QByteArray myData(Data, 25);
    //qDebug() << myData;
    socket->writeDatagram(myData, QHostAddress("192.168.0.2"), 8888);
    if (socket->waitForReadyRead(200)){
        ui->label->setText("SelfCheck Succeed");
    }
   QByteArray Buffer;
   Buffer.resize(socket->pendingDatagramSize());
   Buffer = socket->readAll();// may be error here, cause you only need to read a host. so you need to use the 'readDatagram()' function instead.
    //this place write the Buffer to a file.
   QFile file("out.txt");   //the data received all write to the out.txt file. so we can rebuild the list model and view it.
    file.open(QIODevice::WriteOnly | QIODevice::Text);
   QTextStream out(&file);
   out << Buffer << "\n";
   file.close();
   //write model there
   qDebug() << "do write model there";
   socket->close();
}

Selfcheck::~Selfcheck()
{
    delete ui;
}
