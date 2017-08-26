#ifndef ADJUST_H
#define ADJUST_H

#include <QWidget>
#include <QMainWindow>
#include <QApplication>
#include <QString>
#include <QFile>
#include <QWidget>
#include <QtGui>

#include "simpleadjust.h"
#include "login.h"
#include "posix_qextserialport.h"
#include "commandList.h"
namespace Ui {
class adjust;
}

class adjust : public QWidget
{
    Q_OBJECT

public:
    explicit adjust(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~adjust();

private slots:
    void on_btn_adjustMeasure_clicked();

    void on_btn_adjustclose_clicked();

    void on_btn_adjustUnlock_clicked();

    void on_btn_adjustOk_clicked();

    void on_btn_num_1_clicked();

    void on_btn_num_2_clicked();

    void on_btn_num_3_clicked();

    void on_btn_num_4_clicked();

    void on_btn_num_5_clicked();

    void on_btn_num_6_clicked();

    void on_btn_num_7_clicked();

    void on_btn_num_8_clicked();

    void on_btn_num_9_clicked();

    void on_btn_num_Point_clicked();

    void on_btn_num_0_clicked();

    void on_btn_num_sub_clicked();

    void on_btn_num_clr_clicked();

    void on_btn_num_10_clicked();

    void btn_close();
    void btn_show();
    void onTimeOut();
    void spanAdjust();
    void on_btn_adjustAuto_clicked();


private:
    Ui::adjust *ui;
public:
    SimpleAdjust *pSimple;
    login *pLogin;
    QString str;
    bool btime;
    bool badjust;

    QTimer *pTimer2;
    Posix_QextSerialPort *pSerial;
};

#endif // ADJUST_H
