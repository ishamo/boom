#include "telegram.h"
#include "ui_telegram.h"

Telegram::Telegram(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Telegram)
{
    ui->setupUi(this);
}

Telegram::~Telegram()
{
    delete ui;
}
