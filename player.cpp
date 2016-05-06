#include "player.h"
#include "ui_player.h"
#include <unistd.h>

Player::Player(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    QString spath = QDir::currentPath();
    spath += "/speech/";
    ui->label_6->setText(spath);
    socket = new QUdpSocket(this);
    socket->bind(61001);
    filemodel = new QFileSystemModel(this);
    filemodel->setRootPath(ui->label_6->text());
    filemodel->setFilter(QDir::NoDotAndDotDot | QDir::Files);
    ui->listView->setModel(filemodel);
    ui->listView->setRootIndex(filemodel->setRootPath(ui->label_6->text()));
}

Player::~Player()
{
    delete ui;
}

void Player::on_pushButton_clicked()
{
    //this place uses to player sound!
    qDebug("Doing sth...");
    QFile myfile(filename);
    myfile.open(QIODevice::ReadOnly | QIODevice::Text);
    while (!myfile.atEnd()){
        QByteArray packet;
        packet.resize(361);
        for (int i = 0; i < 361; i++) packet[i] = 0;

        myfile.read(packet.data()+35, 320);

        myfile.flush();
            qDebug() << packet;
            socket->writeDatagram(packet, QHostAddress("192.168.0.100"), 61001);
            usleep(40000);
            //socket->waitForBytesWritten(40);
    }


}

void Player::on_pushButton_2_clicked()
{
    //file = new File;
   // connect(file, SIGNAL(SendData(QString)), this, SLOT(receiveData(QString)));
   // connect(file, SIGNAL(SendData(QString)), this, SLOT(receiveData(QString)));
   // file->setModal(true);
    //file->exec();
    filepath = new MyFilePath(this);
    connect(filepath, SIGNAL(SendPath(QString)), this, SLOT(receiveData(QString)));
    filepath->setModal(true);
    filepath->exec();
}

void Player::receiveData(QString data)
{
    ui->label_6->setText(data);
    ui->listView->setRootIndex(filemodel->setRootPath(data));
}

void Player::on_listView_clicked(const QModelIndex &index)
{
    filename = filemodel->fileInfo(index).absoluteFilePath();
}
