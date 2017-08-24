#ifndef CONFIGURE_H
#define CONFIGURE_H

#include <QWidget>
#include "posix_qextserialport.h"
#include "commandList.h"

namespace Ui {
class configure;
}

class configure : public QWidget
{
    Q_OBJECT

public:
    explicit configure(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~configure();

private slots:
    void on_btn_ok_clicked();

    void on_btn_default_clicked();

    void on_btn_state_clicked();

private:
    Ui::configure *ui;

public:
    Posix_QextSerialPort *pSerial;
};

#endif // CONFIGURE_H
