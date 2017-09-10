#include "adjust.h"
#include "ui_adjust.h"
#include "commandList.h"
#include <QMessageBox>

adjust::adjust(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::adjust)
{
    ui->setupUi(this);

    pSerial = serial;
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    ui->tblwidget_adjustTitle->setItem(0,0,new QTableWidgetItem(QString::fromUtf8("校准日期表")));

    ui->tblwidget_adjustItem->setItem(0,0,new QTableWidgetItem(QString::fromUtf8("序列号")));

    ui->tblwidget_adjustItem->setItem(1,0,new QTableWidgetItem(QString::fromUtf8("DOC")));

    ui->tblwidget_adjustItem->setItem(2,0,new QTableWidgetItem(QString::fromUtf8("零点")));

    ui->tblwidget_adjustItem->setItem(3,0,new QTableWidgetItem(QString::fromUtf8("满量程")));

    ui->tblwidget_adjustItem->setItem(4,0,new QTableWidgetItem(QString::fromUtf8("高程修正")));
    ui->tblwidget_adjustItem->setItem(4,1,new QTableWidgetItem(QString::fromUtf8("1.000000")));

    ui->tblwidget_adjustTitle->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->tblwidget_adjustItem->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->tblwidget_adjustItem->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->tblwidget_adjustItem->item(2,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    //ui->tblwidget_adjustItem->item(2,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(3,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    //ui->tblwidget_adjustItem->item(3,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(4,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->tblwidget_adjustItem->item(4,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->btn_adjustOk->hide();
    ui->cmb_adjust->hide();

    pSimple = new SimpleAdjust(this, pSerial);
    pKeyBoard = new keyBoard;


    pLogin  = new login;
    pTimer2 = new QTimer(this);
    pTimer2->setInterval(1000);
    connect(pTimer2, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    //pTimer2->start();
    pLogin->close();
    pSimple->close();
    pKeyBoard->close();

    ui->btn_adjustUnit->setEnabled(false);

    btime = false;
    badjust = false;

    ui->btn_adjustAir->hide();
    ui->btn_adjustMeasure->hide();
    ui->btn_adjustUnit->hide();
    ui->edit_adjustView->hide();
    ui->btn_adjustUnlock->hide();
    ui->btn_adjustclose->hide();
    ui->cmb_adjust->hide();
    ui->btn_adjustOk->hide();
}

adjust::~adjust()
{
    delete ui;
}

void adjust::on_btn_adjustMeasure_clicked()
{
    QString str = QString("");
    u_int32_t loop = 0;

    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &str);

    if(str.length() != 0)
    {
        //get the valid pressure
        str = str.right(str.length() - QString("1 ").length());
        ui->edit_adjustView->setText(str);
    }
    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_UNIT_CODE, &str);
    if(str.length() != 0)
    {
        //get the valid pressure
        str = str.right(str.length() - QString("1 ").length());
        for(loop = 0 ;loop < 40; loop++)
        {
            if(str.toInt() == gUnitChange[loop].code)
            {
                ui->edit_adjustView->setText(gUnitChange[loop].unitInfo);
                break;
            }
        }
    }
}

void adjust::onTimeOut()
{
    QString str = QString("");
    QString strTemp = QString("");
    u_int32_t loop = 0;
    switch(ui->cmb_adjust->currentIndex())
    {
    case 3:
        if(btime)
        {
            if(pKeyBoard->editFlag)
            {
                ui->tblwidget_adjustItem->setItem(1,1,new QTableWidgetItem(pKeyBoard->str));
                ui->tblwidget_adjustItem->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            }
            else
            {
                sendSerialCommand(pSerial, CMD_DISABLE_PASSWD, &str);
                sendSerialCommandArg(pSerial, CMD_SET_CALIBRATION_DATE, pKeyBoard->str, &strTemp);
                sendSerialCommand(pSerial, CMD_SAVE_ALL_DATA, &strTemp);
                btime = false;
            }
        }
        break;
    case 4:
        if(badjust)
        {
            ui->tblwidget_adjustItem->setItem(4,1,new QTableWidgetItem(pKeyBoard->str));
            ui->tblwidget_adjustItem->item(4,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
        break;
    default:
        break;
    }

    //get id
    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_ID, &str);

    if(str.length() == 0)
    {
        ui->tblwidget_adjustItem->setItem(0,1,new QTableWidgetItem(QString::fromUtf8("6012095")));
        ui->tblwidget_adjustItem->item(0,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    else
    {
        ui->tblwidget_adjustItem->setItem(0,1,new QTableWidgetItem((str.right(str.length() - QString("1 ID Mensor DPT 6000, SN ").length())).left(8)));
        ui->tblwidget_adjustItem->item(0,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

    //get the date of calibration
    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_CALIBRATION_DATE, &str);

    if(str.length() == 0)
    {
        ui->tblwidget_adjustItem->setItem(1,1,new QTableWidgetItem(QString::fromUtf8("2017-08-24")));
        ui->tblwidget_adjustItem->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    else
    {
        ui->tblwidget_adjustItem->setItem(1,1,new QTableWidgetItem((str.right(str.length() - QString("1 DC ").length())).left(6)));
        ui->tblwidget_adjustItem->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    //get zero correction value
    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_ZERO_CORRECTION, &str);
    if(str.length() != 0)
    {
        ui->tblwidget_adjustItem->setItem(2,1,new QTableWidgetItem((str.right(str.length() - QString("1 ZC ").length())).left(str.length() - QString("1 ZC ").length() - QString("\r\n").length())));
        ui->tblwidget_adjustItem->item(2,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    else
    {
         ui->tblwidget_adjustItem->setItem(2,1,new QTableWidgetItem(QString::fromUtf8("0.000000")));
         ui->tblwidget_adjustItem->item(2,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

    //get the maximum range
    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_MAXIMUM, &str);
    if(str.length() != 0)
    {
        ui->tblwidget_adjustItem->setItem(3,1,new QTableWidgetItem((str.right(str.length() - QString("1 R+ ").length())).left(str.length() - QString("1 R+ ").length() - QString("\r\n").length())));
        ui->tblwidget_adjustItem->item(3,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
    else
    {
        ui->tblwidget_adjustItem->setItem(3,1,new QTableWidgetItem(QString::fromUtf8("1.000000")));
        ui->tblwidget_adjustItem->item(3,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &str);
    if(str.length() != 0)
    {
        //get the valid pressure
        str = str.right(str.length() - QString("1 ").length());
        ui->edit_adjustView->setText(str);
    }
    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_UNIT_CODE, &str);
    if(str.length() != 0)
    {
        //get the valid uni code
        str = str.right(str.length() - QString("1 U ").length());
        for(loop = 0 ;loop < 40; loop++)
        {
            if(str.toInt() == gUnitChange[loop].code)
            {
                ui->btn_adjustUnit->setText(gUnitChange[loop].unitInfo);
                break;
            }
        }

    }
}

void adjust::on_btn_adjustclose_clicked()
{
    //ui->tblwidget_adjustLock_2->setStyleSheet("border-image: url(:/new/prefix1/image/lock.png)");
    ui->btn_adjustOk->hide();
    ui->cmb_adjust->hide();
    pTimer2->stop();
    this->close();
}

void adjust::on_btn_adjustUnlock_clicked()
{
    QString str;
    //ui->tblwidget_adjustLock_2->setStyleSheet("border-image: url(:/new/prefix1/image/unlock.png)");
    ui->btn_adjustOk->show();
    ui->cmb_adjust->show();
    sendSerialCommand(pSerial, CMD_DISABLE_PASSWD, &str);
    //pLogin->show();
    //pLogin->move((QApplication::desktop()->width() - pLogin->width())/2,(QApplication::desktop()->height() - pLogin->height())/2);
}

void adjust::on_btn_adjustOk_clicked()
{
    QString str = QString("1");
    QString strTemp = QString("");
    switch(ui->cmb_adjust->currentIndex())
    {
    case 0:
        pSimple->pTimer1->start();
        pSimple->show();
        pSimple->move((QApplication::desktop()->width() - pSimple->width())/2,(QApplication::desktop()->height() - pSimple->height())/2);
        break;
    case 1:
        spanAdjust();
        break;
    case 2:
        str = QString("1");
        strTemp = QString("");
        sendSerialCommandArg(pSerial, CMD_SWITCH_CAL, str, &strTemp);
        break;
    case 3:
        btime = true;
        pKeyBoard->str = QString("");
        pKeyBoard->editFlag = true;
        pKeyBoard->show();
        pKeyBoard->move(600, 300);
        break;
    case 4:
        badjust = true;
        pKeyBoard->str = QString("");
        pKeyBoard->editFlag = true;
        pKeyBoard->show();
        pKeyBoard->move(600, 300);
        break;
    case 5:
    default:
        break;
    }
}

void adjust::btn_show()
{
    ui->btn_adjustOk->hide();
    ui->cmb_adjust->hide();
}

void adjust::btn_close()
{
    ui->btn_adjustOk->show();
    ui->cmb_adjust->show();
}

void adjust::on_btn_adjustAuto_clicked()
{
    QString str;
    double zero = 0.0;
    double zeroTemp = 0.0;
    QString strTemp = QString("1 ZC ");
    //1. send #*ZC?   get current zero
    sendSerialCommand(pSerial, CMD_GET_ZERO_CORRECTION, &str);
    str = str.right(str.length() - strTemp.length());
    zero = str.toDouble();
    //2. send #*PW    disable password
    sendSerialCommand(pSerial, CMD_DISABLE_PASSWD, &str);
    //3. send #*ZC 0  send a new zero
    strTemp = QString("0");
    sendSerialCommandArg(pSerial, CMD_SET_ZERO_CORRECTION, strTemp, &str);
    //4. send #*?     get current pressure
    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &str);
    str = str.right(10);
    ui->edit_adjustView->setText(str);
    zeroTemp = str.toDouble();
    //5. send #*PW    disbale passwd
    sendSerialCommand(pSerial, CMD_DISABLE_PASSWD, &str);
    //6. send #*ZC ... send a new zero
    strTemp = QString(" ");
    strTemp.append(QString::number(zero - zeroTemp, 'f', 6));
    sendSerialCommandArg(pSerial, CMD_SET_ZERO_CORRECTION, strTemp, &str);
    //7. send #*SAVE  save enviment
    sendSerialCommand(pSerial, CMD_SAVE_ALL_DATA, &str);
    ui->tblwidget_adjustItem->setItem(2,1,new QTableWidgetItem(QString::number(zero - zeroTemp, 'f', 6)));
    //8. send #*?
    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &str);
    str = str.right(10);
    ui->edit_adjustView->setText(str);
}

void adjust::spanAdjust(void)
{
    QString str;
    double zero = 0.0;
    double zeroTemp = 0.0;
    QString strTemp = QString("1 SC ");
    //1. send #*SC?   get current zero
    sendSerialCommand(pSerial, CMD_GET_CORRECTION_MULTIPLIER, &str);
    str = str.right(str.length() - strTemp.length());
    zero = str.toDouble();
    //2. send #*PW    disable password
    sendSerialCommand(pSerial, CMD_DISABLE_PASSWD, &str);
    //3. send #*SC 1  send a new zero
    strTemp = QString(" 1");
    sendSerialCommandArg(pSerial, CMD_LOAD_CORRECTION_MULTIPLIER, strTemp, &str);
    //4. send #*?     get current pressure
    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &str);
    str = str.right(10);
    ui->edit_adjustView->setText(str);
    zeroTemp = str.toDouble();
    //5. send #*PW    disbale passwd
    sendSerialCommand(pSerial, CMD_DISABLE_PASSWD, &str);
    //6. send #*SC ... send a new zero
    strTemp = QString(" ");
    strTemp.append(QString::number(zero - zeroTemp, 'f', 6));
    sendSerialCommandArg(pSerial, CMD_LOAD_CORRECTION_MULTIPLIER, strTemp, &str);
    //7. send #*SAVE  save enviment
    sendSerialCommand(pSerial, CMD_SAVE_ALL_DATA, &str);
    ui->tblwidget_adjustItem->setItem(2,1,new QTableWidgetItem(QString::number(zero - zeroTemp, 'f', 6)));
    //8. send #*?
    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &str);
    str = str.right(10);
    ui->edit_adjustView->setText(str);
}

void adjust::on_btn_configureMachine_2_clicked()
{
    pTimer2->stop();
    this->close();
}

void adjust::on_pushButton_38_clicked()
{
    pTimer2->stop();
    this->close();
}
