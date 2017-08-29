#include "serial.h"
#include "ui_serial.h"
#include <QMessageBox>

Serial::Serial(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::Serial)
{
    ui->setupUi(this);
    QString portName = "/dev/" + ui->portNameComboBoxGPS->currentText();   //获取串口名
    pSerial = new Posix_QextSerialPort(portName, QextSerialBase::Polling);
    serial = pSerial;
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    pTimer->start();
    ui->Stopsmsbtn->setEnabled(false);
}

Serial::~Serial()
{
    delete ui;
}

void Serial::onTimeOut()
{
    if(pSerial->isOpen())
    {
    QByteArray temp = pSerial->readAll();

    QString strsms=QString(temp);
    //ui->lineEdit_serialView->clear();
    //ui->lineEdit_serialView->setText(strsms);

    QString qStrCmd = "hello";
    pSerial->write(qStrCmd.toAscii());
    }
}


void Serial::on_Startsmsbtn_clicked()
{
    //这里QextSerialBase::QueryMode应该使用QextSerialBase::Polling

    if(pSerial->open(QIODevice::ReadWrite)){
        ui->statusBar->setText(tr("open success"));
    }else{
        ui->statusBar->setText(tr("open fail"));
        return;
    }
    //设置波特率
    pSerial->setBaudRate((BaudRateType)ui->baudRateComboBoxGPS->currentIndex());

    //设置数据位
    pSerial->setDataBits((DataBitsType)ui->dataBitsComboBoxGPS->currentIndex());

    //设置校验
    pSerial->setParity((ParityType)ui->parityComboBoxGPS->currentIndex());

    //设置停止位
    pSerial->setStopBits((StopBitsType)ui->stopBitsComboBoxGPS->currentIndex());
    //设置数据流控制
    pSerial->setFlowControl(FLOW_OFF);
    //设置延时
    pSerial->setTimeout(TIME_OUT);

    ui->Startsmsbtn->setEnabled(false);
    ui->Stopsmsbtn->setEnabled(true);
}


void Serial::setComboBoxEnabled(bool status)
{
    ui->portNameComboBoxGPS->setEnabled(status);
    ui->baudRateComboBoxGPS->setEnabled(status);
    ui->dataBitsComboBoxGPS->setEnabled(status);
    ui->parityComboBoxGPS->setEnabled(status);
    ui->stopBitsComboBoxGPS->setEnabled(status);
}

void Serial::on_Stopsmsbtn_clicked()
{
    pSerial->close();
    //delete pSerial;
    //readTimer->stop();
    ui->statusBar->setText(tr("COM Close"));
    setComboBoxEnabled(true);
    ui->Startsmsbtn->setEnabled(true);
    ui->Stopsmsbtn->setEnabled(false);
    this->close();
}
