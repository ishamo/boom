#ifndef ARGSETUP_H
#define ARGSETUP_H

#include <QDialog>

namespace Ui {
class Argsetup;
}

class Argsetup : public QDialog
{
    Q_OBJECT

public:
    explicit Argsetup(QWidget *parent = 0);
    ~Argsetup();

private:
    Ui::Argsetup *ui;
};

#endif // ARGSETUP_H
