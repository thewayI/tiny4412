#ifndef MANU_H
#define MANU_H

#include <QWidget>
#include "posix_qextserialport.h"

namespace Ui {
class manu;
}

class manu : public QWidget
{
    Q_OBJECT

public:
    explicit manu(QWidget *parent = 0, Posix_QextSerialPort *pSerialDevice = NULL, Posix_QextSerialPort *pSerial = NULL);
    ~manu();

private:
    Ui::manu *ui;

public:
    Posix_QextSerialPort *pSerialDev;
    Posix_QextSerialPort *pSerialHost;

};

#endif // MANU_H
