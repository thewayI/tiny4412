#ifndef SIMPLEADJUST_H
#define SIMPLEADJUST_H

#include <QWidget>
#include <qtimer.h>

#include "posix_qextserialport.h"
#include "commandList.h"
namespace Ui {
class SimpleAdjust;
}

class SimpleAdjust : public QWidget
{
    Q_OBJECT

public:
    explicit SimpleAdjust(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~SimpleAdjust();

private slots:
    void onTimeOut();

    void on_btn_num_clr_clicked();

    void on_btn_num_0_clicked();

    void on_btn_num_Point_clicked();

    void on_btn_num_1_clicked();

    void on_btn_num_2_clicked();

    void on_btn_num_3_clicked();

    void on_btn_num_4_clicked();

    void on_btn_num_5_clicked();

    void on_btn_num_6_clicked();

    void on_btn_num_7_clicked();

    void on_btn_num_8_clicked();

    void on_btn_num_9_clicked();

    void on_btn_ok_clicked();

    void on_btn_ok_2_clicked();

private:
    Ui::SimpleAdjust *ui;

public:
    double mExceptVal;
    int mExceptValueInt;
    int mExceptValueFloat;

    int mcount;
    bool point;

    QTimer *pTimer1;
    Posix_QextSerialPort *pSerial;
};

#endif // SIMPLEADJUST_H
