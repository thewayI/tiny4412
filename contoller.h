#ifndef CONTOLLER_H
#define CONTOLLER_H

#include <QWidget>
#include "posix_qextserialport.h"
#include "qtimer.h"
#include "keyboard.h"
#include "commandList.h"

namespace Ui {
class Contoller;
}

class Contoller : public QWidget
{
    Q_OBJECT

public:
    explicit Contoller(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~Contoller();

private slots:
    void on_btn_ctrlvariable_clicked();

    void onTimeOut();

    void on_btn_ctrlMAX1_2_clicked();

    void on_btn_ctrlMAX1_clicked();

    void on_btn_ctrlMAX2_clicked();

    void on_btn_ctrlMAX3_clicked();

    void on_btn_ctrlstab1_clicked();

    void on_btn_ctrlstab2_clicked();

    void on_btn_ctrlMAX3_3_clicked();

private:
    Ui::Contoller *ui;

public:
    QTimer *pTimer;
    Posix_QextSerialPort *pSerial;
    keyBoard *pKeyboard;

    bool editctrlMax1Flag;
    bool editctrlMax2Flag;
    bool editctrlMax3Flag;

    bool editctrlstab1Flag;
    bool editctrlstab2Flag;

    bool editctrlMAX1_2Flag;
    bool editctrlvariableFlag;


};

#endif // CONTOLLER_H
