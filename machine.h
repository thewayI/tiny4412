#ifndef MACHINE_H
#define MACHINE_H

#include <QWidget>
#include "commandList.h"
namespace Ui {
class Machine;
}

class Machine : public QWidget
{
    Q_OBJECT

public:
    explicit Machine(QWidget *parent = 0);
    ~Machine();

private slots:
    void on_btn_default_clicked();

private:
    Ui::Machine *ui;
};

#endif // MACHINE_H
