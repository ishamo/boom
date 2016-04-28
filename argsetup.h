#ifndef ARGSETUP_H
#define ARGSETUP_H

#include <QDialog>
#include <QUdpSocket>
#include "mydata.h"
namespace Ui {
class Argsetup;
}

class Argsetup : public QDialog
{
    Q_OBJECT

public:
    explicit Argsetup(QWidget *parent = 0);
    ~Argsetup();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Argsetup *ui;
    QUdpSocket *socket;
};

#endif // ARGSETUP_H
