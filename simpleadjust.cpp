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

    //creator a timer
    pTimer1 = new QTimer(this);
    pTimer1->setInterval(100);
    connect(pTimer1, SIGNAL(timeout()), this, SLOT(onTimeOut()));


    ui->lineEdit_current->setText(QString("0.1000"));
    ui->lineEdit_max->setText(QString("0.1500"));
    ui->lineEdit_min->setText(QString("0.0050"));
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

SimpleAdjust::~SimpleAdjust()
{
    delete ui;
}

void SimpleAdjust::onTimeOut()
{

    QString str;
    QString strTemp = QString("");
    str.sprintf("%d.%d", mExceptValueInt, mExceptValueFloat);
    ui->lineEdit_except->setText(str);

    //get current pressure
    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &strTemp);

    if(strTemp.length() != 0)
    {
        //get the valid pressure
        strTemp = strTemp.right(strTemp.length() - QString("1 ").length());
        // display data
        ui->lineEdit_current->setText(strTemp);
    }

    //get the maximum range
    strTemp = QString("");
    sendSerialCommand(pSerial, CMD_GET_MAXIMUM, &strTemp);
    if(strTemp.length() != 0)
    {
        //qDebug("strTemp = %s\n", qPrintable(strTemp));
        ui->lineEdit_max->setText((strTemp.right(strTemp.length() - QString("1 R+ ").length())).left(strTemp.length() - QString("1 R+ ").length() - QString("\r\n").length()));

    }
    //get the minimum range
    strTemp = QString("");
    sendSerialCommand(pSerial, CMD_GET_MINIMUM, &strTemp);
    if(strTemp.length() != 0)
    {
        //qDebug("strTemp = %s\n", qPrintable(strTemp));
        ui->lineEdit_min->setText((strTemp.right(strTemp.length() - QString("1 R- ").length())).left(strTemp.length() - QString("1 R+ ").length() - QString("\r\n").length()));

    }
}

void SimpleAdjust::on_btn_num_clr_clicked()
{
    mExceptValueFloat = 0;
    mExceptValueInt = 0;
    point = false;
}

void SimpleAdjust::on_btn_num_0_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
    }
}

void SimpleAdjust::on_btn_num_Point_clicked()
{
    point = true;
}

void SimpleAdjust::on_btn_num_1_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mExceptValueFloat += 1;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
        mExceptValueInt += 1;
    }
}

void SimpleAdjust::on_btn_num_2_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mExceptValueFloat += 2;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
        mExceptValueInt += 2;
    }
}

void SimpleAdjust::on_btn_num_3_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mExceptValueFloat += 3;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
        mExceptValueInt += 3;
    }
}

void SimpleAdjust::on_btn_num_4_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mExceptValueFloat += 4;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
        mExceptValueInt += 4;
    }
}

void SimpleAdjust::on_btn_num_5_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mExceptValueFloat += 5;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
        mExceptValueInt += 5;
    }
}

void SimpleAdjust::on_btn_num_6_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mExceptValueFloat += 6;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
        mExceptValueInt += 6;
    }
}

void SimpleAdjust::on_btn_num_7_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mExceptValueFloat += 7;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
        mExceptValueInt += 7;
    }
}

void SimpleAdjust::on_btn_num_8_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mExceptValueFloat += 8;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
        mExceptValueInt += 8;
    }
}

void SimpleAdjust::on_btn_num_9_clicked()
{
    if(point)
    {
        mExceptValueFloat *= 10;
        mExceptValueFloat += 9;
        mcount++;
    }
    else
    {
        mExceptValueInt *= 10;
        mExceptValueInt += 9;
    }
}

void SimpleAdjust::on_btn_ok_clicked()
{
    pTimer1->stop();
    this->close();
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
    pressureTemp = ui->lineEdit_except->text().toDouble() / pressure;

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
}
