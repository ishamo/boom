#ifndef PLAYER_H
#define PLAYER_H

#include <QDialog>
#include "file.h"

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

private:
    Ui::Player *ui;
    File *file;

};

#endif // PLAYER_H
