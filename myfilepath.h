#ifndef MYFILEPATH_H
#define MYFILEPATH_H

#include <QDialog>
#include <QtWidgets>
#include <QFileSystemModel>
#include <QString>
namespace Ui {
class MyFilePath;
}

class MyFilePath : public QDialog
{
    Q_OBJECT

public:
    explicit MyFilePath(QWidget *parent = 0);
    ~MyFilePath();

signals:
    void SendPath(QString);

private slots:
    void on_treeView_clicked(const QModelIndex &index);

private:
    Ui::MyFilePath *ui;
    QFileSystemModel *filemodel;
    QString dirpath;
};

#endif // MYFILEPATH_H
