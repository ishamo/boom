#ifndef PLAYER_H
#define PLAYER_H

#include <QDialog>
//#include "file.h"
#include <QUdpSocket>
#include <QtWidgets>
#include <QFileSystemModel>
#include "myfilepath.h"

namespace Ui {
class Player;
}

class Player : public QDialog
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = 0);
    ~Player();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void receiveData(QString data);

    void on_listView_clicked(const QModelIndex &index);

private:
    Ui::Player *ui;
   // File *file;
    QUdpSocket *socket;
    MyFilePath *filepath;
    QFileSystemModel *filemodel;
    QString labelpath;
    QString filename;

};

#endif // PLAYER_H
