#ifndef RECORD_H
#define RECORD_H

#include <QDialog>
#include "selectpath.h"

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

private:
    Ui::Record *ui;
    QWidget *filesystem;
    SelectPath *savepath;
};

#endif // RECORD_H
