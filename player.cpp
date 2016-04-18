#include "player.h"
#include "ui_player.h"


Player::Player(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    ui->label_6->setText(QDir::currentPath());
}

Player::~Player()
{
    delete ui;
}

void Player::on_pushButton_clicked()
{
    //this place uses to player sound!
    qDebug("Doing sth...");
}

void Player::on_pushButton_2_clicked()
{
    file = new File;
    connect(file, SIGNAL(SendData(QString)), this, SLOT(receiveData(QString)));
   // connect(file, SIGNAL(SendData(QString)), this, SLOT(receiveData(QString)));
    file->setModal(true);
    file->exec();
}

void Player::receiveData(QString data)
{
    ui->label_6->setText(data);
}
