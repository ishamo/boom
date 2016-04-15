#include "selfcheck.h"
#include "ui_selfcheck.h"

Selfcheck::Selfcheck(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Selfcheck)
{
    ui->setupUi(this);
}

Selfcheck::~Selfcheck()
{
    delete ui;
}
