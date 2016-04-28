#include "argsetup.h"
#include "ui_argsetup.h"

Argsetup::Argsetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Argsetup)
{
    ui->setupUi(this);
    socket = new QUdpSocket(this);
}

Argsetup::~Argsetup()
{
    delete ui;
}

void Argsetup::on_pushButton_clicked()
{
    //lookup arguments
    MyData Data;
    *(quint32 *)(Data.Header+17) = quint32(0x0001);
    quint16 tmp = Data.crc(Data.Header+14, 12);
    Data.Header[24] = tmp >> 8;
    Data.Header[25] = (quint8)tmp;

    socket->writeDatagram(Data.Header, 26, QHostAddress("127.0.0.1"), 8888);
    if (socket->waitForReadyRead(200)){
        QByteArray Buffer;
        Buffer.resize(socket->pendingDatagramSize());
        Buffer = socket->readAll();
        //wrong
        /*
        ui->label_5->setText(buffer[24]);
        ui->label_6->setText(Buffer[25]);
        ui->label_7->setText(Buffer[26]);
        ui->label_8->setText(Buffer[27]);
        ui->label_9->setText(Buffer[28]);
        */

    }
}
