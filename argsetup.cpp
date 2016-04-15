#include "argsetup.h"
#include "ui_argsetup.h"

Argsetup::Argsetup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Argsetup)
{
    ui->setupUi(this);
}

Argsetup::~Argsetup()
{
    delete ui;
}
