#include "sensor.h"
#include "ui_sensor.h"

sensor::sensor(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::sensor)
{
    ui->setupUi(this);
    pSerial = serial;
    pAdjust = new adjust(this, pSerial);

    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

sensor::~sensor()
{
    delete ui;
}

void sensor::on_btn_adjust_clicked()
{
    pAdjust->show();
    this->close();
}
