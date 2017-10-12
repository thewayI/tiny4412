#include "simpleadjust.h"
#include "ui_simpleadjust.h"
#include <QtCore/qmath.h>

SimpleAdjust::SimpleAdjust(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::SimpleAdjust)
{
    ui->setupUi(this);
    pSerial = serial;
    mExceptVal = 0.0;
    mcount = 0;
    mExceptValueInt = 0;
    mExceptValueFloat = 0;
    point = false;

    pKeyBoard = new keyBoard;

    pKeyBoard->close();

    //creator a timer
    pTimer1 = new QTimer(this);
    pTimer1->setInterval(1000);
    connect(pTimer1, SIGNAL(timeout()), this, SLOT(onTimeOut()));


    ui->lineEdit_current->setText(QString("0.1000"));

    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);


    bAdjust = false;
}

SimpleAdjust::~SimpleAdjust()
{
    delete ui;
}

void SimpleAdjust::onTimeOut()
{
    QString strTemp = QString("");

    //get current pressure
    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &strTemp);

    if(strTemp.length() != 0)
    {
        //get the valid pressure
        strTemp = strTemp.right(strTemp.length() - QString("1 ").length());
        // display data
        ui->lineEdit_current->setText(strTemp);
    }
    if(bAdjust)
    {
        if(pKeyBoard->editFlag)
        {
            ui->btn_ok_3->setText(pKeyBoard->str);
        }
        else
        {
            bAdjust = false;
        }
    }

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

void SimpleAdjust::on_btn_ok_2_clicked()
{
    QString str = QString("");
    double pressure = 0.0;
    double pressureTemp = 0.0;
    //1. send #*SC? get current span cal
    QString strTemp = QString("1 SC ");
    //1. send #*ZC?   get current zero
    sendSerialCommand(pSerial, CMD_GET_CORRECTION_MULTIPLIER, &str);

    //2. send #*PW    disable password
    sendSerialCommand(pSerial, CMD_DISABLE_PASSWD, &str);
    //3. send #*SC 1  send a new zero
    strTemp = QString("1");
    sendSerialCommandArg(pSerial, CMD_LOAD_CORRECTION_MULTIPLIER, strTemp, &str);
    //4. send #*?     get current pressure
    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &str);
    str = str.right(str.length() - QString("1 ").length());
    //ui->edit_adjustView->setText(str);
    pressure = str.toDouble();

    //ui->lineEdit_except->text().toDouble()
    pressureTemp = ui->btn_ok_3->text().toDouble() / pressure;

    strTemp = QString::number(pressureTemp, 'f', 6);

    //2. send #*PW    disable password
    sendSerialCommand(pSerial, CMD_DISABLE_PASSWD, &str);
    //3. send #*SC 1  send a new zero
    //strTemp = QString("1");
    strTemp = QString::number(pressureTemp, 'f', 6);
    sendSerialCommandArg(pSerial, CMD_LOAD_CORRECTION_MULTIPLIER, strTemp, &str);
    //7. send #*SAVE  save enviment
    sendSerialCommand(pSerial, CMD_SAVE_ALL_DATA, &str);
    //8. send #*?
    //sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &str);
    //str = str.right(str.length() - QString("1 ").length());

    bAdjust = false;
    //this->close();
}

void SimpleAdjust::on_btn_ok_3_clicked()
{
    bAdjust = true;
    pKeyBoard->str = QString("");
    pKeyBoard->editFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(0, 500);
}

void SimpleAdjust::on_btn_ok_4_clicked()
{
    pTimer1->stop();
    this->close();
}
