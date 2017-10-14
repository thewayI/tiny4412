#include "serial.h"
#include "ui_serial.h"
#include <QMessageBox>

Serial::Serial(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::Serial)
{
    ui->setupUi(this);
    //QString portName = "/dev/" + ui->portNameComboBoxGPS->currentText();   //获取串口名
    //pSerial = new Posix_QextSerialPort(portName, QextSerialBase::Polling);
    pSerial = serial;
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    ui->Stopsmsbtn->hide();
    ui->Stopsmsbtn->setEnabled(false);

    switch(g32styleMode)
    {
    case 0:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/1.png);"));
        break;
    case 1:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_01.png);"));
        break;
    case 2:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_02.png);"));
        break;
    case 3:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_03.png);"));
        break;
    case 4:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_04.png);"));
        break;
    case 5:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_05.png);"));
        break;
    default:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/1.png);"));
        break;
    }

}

Serial::~Serial()
{
    delete ui;
}

void Serial::on_Startsmsbtn_clicked()
{
    //这里QextSerialBase::QueryMode应该使用QextSerialBase::Polling

    pSerial->close();

    if(pSerial->open(QIODevice::ReadWrite)){
        //ui->statusBar->setText(tr("open success"));
    }else{
        //ui->statusBar->setText(tr("open fail"));
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

    //ui->Startsmsbtn->setEnabled();
//    ui->Startsmsbtn->setStyleSheet(QString::fromUtf8("border-top-left-radius:6px;\n"
//                                                     "color: rgb(255, 255, 255);\n"
//                                                     "border:2px solid rgba(255, 255, 255,70);\n"
//                                                     "background-color: rgba(255, 255, 255, 0);\n"
//                                                     "border-top-right-radius:6px;\n"
//                                                     "border-bottom-left-radius:6px;\n"
//                                                     "border-bottom-right-radius:6px;"));
//    ui->Stopsmsbtn->setEnabled(true);
//    ui->Stopsmsbtn->setStyleSheet(QString::fromUtf8("border-top-left-radius:6px;\n"
//                                                    "color: rgb(255, 255, 255);\n"
//                                                    "border:2px solid rgba(255, 255, 255,70);\n"
//                                                    "background-color: rgba(255, 255, 255, 20);\n"
//                                                    "border-top-right-radius:6px;\n"
//                                                    "border-bottom-left-radius:6px;\n"
//                                                    "border-bottom-right-radius:6px;"));

}


void Serial::setComboBoxEnabled(bool status)
{
    //ui->portNameComboBoxGPS->setEnabled(status);
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
    //ui->statusBar->setText(tr("COM Close"));
    setComboBoxEnabled(true);

    ui->Stopsmsbtn->setEnabled(false);
    ui->Stopsmsbtn->setStyleSheet(QString::fromUtf8("border-top-left-radius:6px;\n"
                                                    "color: rgb(255, 255, 255);\n"
                                                    "border:2px solid rgba(255, 255, 255,70);\n"
                                                    "background-color: rgba(255, 255, 255, 20);\n"
                                                    "border-top-right-radius:6px;\n"
                                                    "border-bottom-left-radius:6px;\n"
                                                    "border-bottom-right-radius:6px;"));
    ui->Startsmsbtn->setEnabled(true);
    ui->Startsmsbtn->setStyleSheet(QString::fromUtf8("border-top-left-radius:6px;\n"
                                                     "color: rgb(255, 255, 255);\n"
                                                     "border:2px solid rgba(255, 255, 255,70);\n"
                                                     "background-color: rgba(255, 255, 255, 0);\n"
                                                     "border-top-right-radius:6px;\n"
                                                     "border-bottom-left-radius:6px;\n"
                                                     "border-bottom-right-radius:6px;"));

}

void Serial::on_btn_configureMachine_2_clicked()
{
    this->close();
}
