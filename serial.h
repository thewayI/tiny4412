#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <qtimer.h>
#include "posix_qextserialport.h"
#include "commandList.h"
#define TIME_OUT 10

namespace Ui {
class Serial;
}

class Serial : public QWidget
{
    Q_OBJECT

public:
    explicit Serial(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~Serial();

private slots:
    void on_Startsmsbtn_clicked();

    void on_Stopsmsbtn_clicked();

    void setComboBoxEnabled(bool status);

    void onTimeOut();

private:
    Ui::Serial *ui;

public:
    Posix_QextSerialPort *pSerial;
    QTimer *pTimer;
};

#endif // SERIAL_H
