#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDate>
#include "argsetup.h"
#include "selfcheck.h"
#include "record.h"
#include "player.h"
#include "telegram.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Selfcheck selfcheck;
    selfcheck.setModal(true);
    selfcheck.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    Argsetup argsetup;
   argsetup.setModal(true);
   argsetup.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    Record record;
    record.setModal(true);
    record.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    Player player;
    player.setModal(true);
    player.exec();
}


