#include "manu.h"
#include "ui_manu.h"

manu::manu(QWidget *parent, Posix_QextSerialPort *pSerialDevice, Posix_QextSerialPort *pSerial) :
    QWidget(parent),
    ui(new Ui::manu)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    pSerialDev = pSerialDevice;
    pSerialHost = pSerial;

}

manu::~manu()
{
    delete ui;
}
