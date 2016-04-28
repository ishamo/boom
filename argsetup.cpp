#include "argsetup.h"
#include "ui_argsetup.h"
#include "mydata.h"
#include <stdlib.h>
Argsetup::Argsetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Argsetup)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
    socket->bind(8888);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

Argsetup::~Argsetup()
{
    delete ui;
}

void Argsetup::on_pushButton_clicked()
{
    //lookup arguments
    MyData Data;
    Data.Header[17] = 0;
    Data.Header[18] = 0;
    Data.Header[19] = 0;
    Data.Header[20] = 16;

    quint16 tmp = Data.crc(Data.Header+14, 9);
    Data.Header[23] = tmp >> 8;
    Data.Header[24] = (quint8)tmp;

    qint64 ret = socket->writeDatagram(Data.Header, 25, QHostAddress("192.168.0.100"), 8888);
    if (ret < 0) qDebug() << "Send Error";
}

void Argsetup::on_pushButton_2_clicked()
{
    //arg change
    QVariant str1 = ui->lineEdit->text();
    QVariant str2 = ui->lineEdit_2->text();
    QVariant str3 = ui->lineEdit_3->text();
    QVariant str4 = ui->lineEdit_4->text();
    QVariant str5 = ui->lineEdit_5->text();
    MyData mydata;
    QByteArray Data = mydata.Header;
    Data[17] = 0;
    Data[18] = 0;
    Data[19] = 0;
    Data[20] = 17;
    Data[21] = 0;
    Data[22] = 32;
    Data[23] = str1.toInt();
    Data[24] = str2.toInt();
    Data[25] = str3.toInt();
    Data[26] = str4.toInt();
    Data[27] = str5.toInt();
    Data.append("\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
    quint16 tmp =   mydata.crc(Data.data() + 14, 45);
    Data.append(quint8(tmp >> 8));
    Data.append(quint8(tmp));
    socket->writeDatagram(Data, QHostAddress("192.168.0.100"), 8888);
}

void Argsetup::readyRead()
{
    QByteArray Buffer;
    Buffer.resize(socket->pendingDatagramSize());
    QHostAddress Sender;
    quint16 Port;
    socket->readDatagram(Buffer.data(), Buffer.size(), &Sender, &Port);

    qDebug() << Buffer;

    ui->label_9->setText(QVariant(Buffer[35]).toString()); //xindao

    ui->label_5->setText(QVariant(Buffer[23]).toString());
    ui->label_6->setText(QVariant(Buffer[24]).toString());
    ui->label_7->setText(QVariant(Buffer[25]).toString());
    ui->label_8->setText(QVariant(Buffer[26]).toString());

    ui->label_19->setText(QVariant(Buffer[27]).toString());
    ui->label_20->setText(QVariant(Buffer[28]).toString());
    ui->label_21->setText(QVariant(Buffer[29]).toString());
    ui->label_22->setText(QVariant(Buffer[30]).toString());

    ui->label_12->setText(QVariant(Buffer[31]).toString());
    ui->label_13->setText(QVariant(Buffer[32]).toString());
    ui->label_14->setText(QVariant(Buffer[33]).toString());
    ui->label_15->setText(QVariant(Buffer[34]).toString());


  //  ui->label_9->setText(QVariant(Buffer[28]).toString());

    socket->close();
}
