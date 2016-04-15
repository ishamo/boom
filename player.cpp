#include "player.h"
#include "ui_player.h"
#include <QDir>
#include <QFileSystemModel>
#include <QTreeView>

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
    qDebug("Doing sth...");
}

void Player::on_pushButton_2_clicked()
{
    QFileSystemModel *model = new QFileSystemModel;
    model->setRootPath(QDir::currentPath());
    QTreeView *tree = new QTreeView;
    tree->setModel(model);
    tree->setRootIndex(model->index(QDir::currentPath()));
    tree->show();
}
