#ifndef SELECTPATH_H
#define SELECTPATH_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class SelectPath;
}

class SelectPath : public QDialog
{
    Q_OBJECT

public:
    explicit SelectPath(QWidget *parent = 0);
    ~SelectPath();

private:
    Ui::SelectPath *ui;
    QFileSystemModel *filemodel;

};

#endif // SELECTPATH_H
