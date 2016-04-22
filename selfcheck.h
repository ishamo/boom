#ifndef SELFCHECK_H
#define SELFCHECK_H

#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QtWidgets>
#include <QUdpSocket>

namespace Ui {
class Selfcheck;
}

class Selfcheck : public QDialog
{
    Q_OBJECT

public:
    explicit Selfcheck(QWidget *parent = 0);
    ~Selfcheck();

private:
    Ui::Selfcheck *ui;
    QStandardItemModel *model;
    QUdpSocket *socket;
};

#endif // SELFCHECK_H
