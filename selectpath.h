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

private slots:
    void on_buttonBox_accepted();

    void on_treeView_clicked(const QModelIndex &index);

signals:
    void SendData(QString);

private:
    Ui::SelectPath *ui;
    QFileSystemModel *filemodel;
    QString filepath;


};

#endif // SELECTPATH_H
