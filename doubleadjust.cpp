#include "doubleadjust.h"
#include "ui_doubleadjust.h"

doubleAdjust::doubleAdjust(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::doubleAdjust)
{
    ui->setupUi(this);

    pSerial = serial;

    pKeyBoard = new keyBoard;

    pKeyBoard->close();

    //creator a timer
    pTimer1 = new QTimer(this);
    pTimer1->setInterval(1000);
    connect(pTimer1, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    bEditFirstEXcept = false;
    bEditSecondEXcept = false;

    firstExcept = 0.0;
    firstCurrent = 0.0;
    secondCurrent = 0.0;
    secondExcept = 0.0;


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

    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

doubleAdjust::~doubleAdjust()
{
    delete ui;
}

void doubleAdjust::onTimeOut()
{
    QString str;
    QString strsms;

    if(g8ConnectFlag)
    {
        sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &strsms);

        if(strsms.length() != 0)
        {
            //get the valid pressure
            str = strsms.right(strsms.length() - QString("1 ").length());
            ui->lineEdit_current->setText(str);
        }
        if(bEditFirstEXcept)
        {
            if(pKeyBoard->editFlag)
            {
                ui->btn_ok_3->setText(pKeyBoard->str);
            }
            else
            {
                bEditFirstEXcept = false;
                firstExcept = ui->btn_ok_3->text().toDouble();
                firstCurrent = ui->lineEdit_current->text().toDouble();
            }
        }

        if(bEditSecondEXcept)
        {
            if(pKeyBoard->editFlag)
            {
                ui->btn_ok_5->setText(pKeyBoard->str);
            }
            else
            {
                bEditSecondEXcept = false;
                secondExcept = ui->btn_ok_5->text().toDouble();
                secondCurrent = ui->lineEdit_current->text().toDouble();
            }
        }
    }
}

void doubleAdjust::on_btn_ok_4_clicked()
{
    pTimer1->stop();
    this->close();
}

void doubleAdjust::on_btn_ok_3_clicked()
{
    bEditFirstEXcept = true;
    pKeyBoard->str = QString("");
    pKeyBoard->editFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(0, 500);
}

void doubleAdjust::on_btn_ok_5_clicked()
{
    bEditSecondEXcept = true;
    pKeyBoard->str = QString("");
    pKeyBoard->editFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(0, 500);
}

void doubleAdjust::on_btn_ok_2_clicked()
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

    pressure = secondExcept - firstExcept;
    pressureTemp = secondExcept - firstCurrent;

    pressureTemp = pressure / pressureTemp;

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
