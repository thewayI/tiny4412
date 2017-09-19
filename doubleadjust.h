#ifndef DOUBLEADJUST_H
#define DOUBLEADJUST_H

#include <QWidget>
#include <QTimer>
#include "posix_qextserialport.h"
#include "commandList.h"
#include "keyboard.h"

namespace Ui {
class doubleAdjust;
}

class doubleAdjust : public QWidget
{
    Q_OBJECT

public:
    explicit doubleAdjust(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~doubleAdjust();

private slots:
    void on_btn_ok_4_clicked();

    void on_btn_ok_3_clicked();

    void on_btn_ok_5_clicked();

    void onTimeOut();

    void on_btn_ok_2_clicked();

private:
    Ui::doubleAdjust *ui;

public:

    bool bEditFirstEXcept;
    bool bEditSecondEXcept;

    double firstExcept;
    double firstCurrent;
    double secondExcept;
    double secondCurrent;

    keyBoard *pKeyBoard;
    QTimer *pTimer1;
    Posix_QextSerialPort *pSerial;
};

#endif // DOUBLEADJUST_H
