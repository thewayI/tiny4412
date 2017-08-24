#ifndef SENSOR_H
#define SENSOR_H

#include <QWidget>
#include "adjust.h"

#include "posix_qextserialport.h"
#include "commandList.h"

namespace Ui {
class sensor;
}

class sensor : public QWidget
{
    Q_OBJECT

public:
    explicit sensor(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~sensor();

private slots:
    void on_btn_adjust_clicked();

private:
    Ui::sensor *ui;

public :
    adjust *pAdjust;
    Posix_QextSerialPort *pSerial;

};

#endif // SENSOR_H
