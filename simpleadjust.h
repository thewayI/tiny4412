#ifndef SIMPLEADJUST_H
#define SIMPLEADJUST_H

#include <QWidget>
#include <QSettings>
#include <qtimer.h>

#include "posix_qextserialport.h"
#include "commandList.h"
#include "keyboard.h"
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

    void on_btn_ok_2_clicked();

    void on_btn_ok_3_clicked();

    void on_btn_ok_4_clicked();

private:
    Ui::SimpleAdjust *ui;

public:
    double mExceptVal;
    bool bAdjust;
    int mExceptValueInt;
    int mExceptValueFloat;

    int mcount;
    bool point;

    keyBoard *pKeyBoard;
    QTimer *pTimer1;
    Posix_QextSerialPort *pSerial;
};

#endif // SIMPLEADJUST_H
