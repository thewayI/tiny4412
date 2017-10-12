#ifndef MACHINE_H
#define MACHINE_H

#include <QWidget>
#include <QTimer>
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

    void on_btn_default_2_clicked();

    void on_btn_configureMachine_2_clicked();

    void on_btn_default_7_clicked();

    void on_btn_default_5_clicked();

    void on_btn_default_4_clicked();

    void on_btn_default_6_clicked();

    void on_btn_default_3_clicked();

    void onTimeOut();

private:
    Ui::Machine *ui;

public:
    QTimer *pTimer;
};

#endif // MACHINE_H
