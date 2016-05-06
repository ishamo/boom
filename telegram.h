#ifndef TELEGRAM_H
#define TELEGRAM_H

#include <QDialog>
#include <QStringListModel>

namespace Ui {
class Telegram;
}

class Telegram : public QDialog
{
    Q_OBJECT

public:
    explicit Telegram(QWidget *parent = 0);
    ~Telegram();

private:
    Ui::Telegram *ui;
    QStringListModel *listmodel;
};

#endif // TELEGRAM_H
