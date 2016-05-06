#include "telegram.h"
#include "ui_telegram.h"

Telegram::Telegram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Telegram)
{
    ui->setupUi(this);
    listmodel = new QStringListModel(this);
    QStringList list;
    list << "a" << "b" << "c";
    listmodel->setStringList(list);
    ui->listView->setModel(listmodel);
}

Telegram::~Telegram()
{
    delete ui;
}
