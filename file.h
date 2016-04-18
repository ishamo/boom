#ifndef FILE_H
#define FILE_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class File;
}

class File : public QDialog
{
    Q_OBJECT

public:
    explicit File(QWidget *parent = 0);
    ~File();

private slots:
    void on_treeView_clicked(const QModelIndex &index);
    void on_listView_clicked(const QModelIndex &index);

    void on_buttonBox_accepted();

signals:
    void SendData(QString);

private:
    Ui::File *ui;
    QFileSystemModel *dirname;
    QFileSystemModel *filename;
    QString filepath;
};

#endif // FILE_H
