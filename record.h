#ifndef RECORD_H
#define RECORD_H

#include <QDialog>
#include "selectpath.h"
#include <QtCore>
#include <QProcess>

namespace Ui {
class Record;
}

class Record : public QDialog
{
    Q_OBJECT

public:
    explicit Record(QWidget *parent = 0);
    ~Record();

private slots:
    void on_pushButton_4_clicked();
    void ReceiveData(QString data);

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::Record *ui;
    QWidget *filesystem;
    SelectPath *savepath;
    QProcess *myProcess;
};

#endif // RECORD_H
