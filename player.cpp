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
    file->setModal(true);
    file->exec();
}
