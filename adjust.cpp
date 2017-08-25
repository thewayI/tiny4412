#include "adjust.h"
#include "ui_adjust.h"
#include "commandList.h"
#include <QMessageBox>

adjust::adjust(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::adjust)
{
    ui->setupUi(this);
    QString str;
    pSerial = serial;
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    ui->tblwidget_adjustTitle->setItem(0,0,new QTableWidgetItem(QString::fromUtf8("校准日期表")));
    ui->tblwidget_adjustItem->setItem(0,0,new QTableWidgetItem(QString::fromUtf8("序列号")));
    //get id
    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_ID, &str);

    if(str.length() == 0)
    {
        ui->tblwidget_adjustItem->setItem(0,1,new QTableWidgetItem(QString::fromUtf8("6012095")));
    }
    else
    {
        ui->tblwidget_adjustItem->setItem(0,1,new QTableWidgetItem((str.right(str.length() - QString("1 ID Mensor DPT 6000, SN ").length())).left(6)));
    }
    ui->tblwidget_adjustItem->setItem(1,0,new QTableWidgetItem(QString::fromUtf8("DOC")));
    //get the date of calibration
    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_CALIBRATION_DATE, &str);

    if(str.length() == 0)
    {
        ui->tblwidget_adjustItem->setItem(1,1,new QTableWidgetItem(QString::fromUtf8("2017-08-24")));
    }
    else
    {
        ui->tblwidget_adjustItem->setItem(1,1,new QTableWidgetItem(str.right(str.length() - QString("1 DC ").length())));
    }
    ui->tblwidget_adjustItem->setItem(2,0,new QTableWidgetItem(QString::fromUtf8("零点")));
    //get zero correction value
    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_ZERO_CORRECTION, &str);

    ui->tblwidget_adjustItem->setItem(2,1,new QTableWidgetItem(str.right(str.length() - QString("1 ZC ").length())));
    ui->tblwidget_adjustItem->setItem(3,0,new QTableWidgetItem(QString::fromUtf8("满量程")));
    ui->tblwidget_adjustItem->setItem(3,1,new QTableWidgetItem(QString::fromUtf8("1.000000")));
    ui->tblwidget_adjustItem->setItem(4,0,new QTableWidgetItem(QString::fromUtf8("高程修正")));
    ui->tblwidget_adjustItem->setItem(4,1,new QTableWidgetItem(QString::fromUtf8("1.000000")));

    ui->tblwidget_adjustTitle->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(0,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(2,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(2,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(3,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(3,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(4,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(4,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->btn_adjustOk->hide();
    ui->cmb_adjust->hide();

    pSimple = new SimpleAdjust;
    pLogin  = new login;
    pTimer2 = new QTimer(this);
    pTimer2->setInterval(100);
    connect(pTimer2, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    pTimer2->start();

    ui->btn_num_0->hide();
    ui->btn_num_1->hide();
    ui->btn_num_2->hide();
    ui->btn_num_3->hide();
    ui->btn_num_4->hide();
    ui->btn_num_5->hide();
    ui->btn_num_6->hide();
    ui->btn_num_7->hide();
    ui->btn_num_8->hide();
    ui->btn_num_9->hide();
    ui->btn_num_10->hide();
    ui->btn_num_Point->hide();
    ui->btn_num_add->hide();
    ui->btn_num_sub->hide();
    ui->btn_num_clr->hide();

    str = QString("");
    btime = false;
    badjust = false;
}

adjust::~adjust()
{
    delete ui;
}

void adjust::on_btn_adjustMeasure_clicked()
{

}

void adjust::onTimeOut()
{
    switch(ui->cmb_adjust->currentIndex())
    {
    case 3:
        if(btime)
        {
            ui->tblwidget_adjustItem->setItem(1,1,new QTableWidgetItem(str));
            ui->tblwidget_adjustItem->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
        break;
    case 4:
        if(badjust)
        {
            ui->tblwidget_adjustItem->setItem(4,1,new QTableWidgetItem(str));
            ui->tblwidget_adjustItem->item(4,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
        break;
    default:
        break;
    }
}

void adjust::on_btn_adjustclose_clicked()
{
    ui->tblwidget_adjustLock_2->setStyleSheet("border-image: url(:/new/prefix1/image/lock.png)");
    ui->btn_adjustOk->hide();
    ui->cmb_adjust->hide();
    this->close();
}

void adjust::on_btn_adjustUnlock_clicked()
{
    QString str;
    ui->tblwidget_adjustLock_2->setStyleSheet("border-image: url(:/new/prefix1/image/unlock.png)");
    ui->btn_adjustOk->show();
    ui->cmb_adjust->show();
    sendSerialCommand(pSerial, CMD_DISABLE_PASSWD, &str);
    //pLogin->show();
    //pLogin->move((QApplication::desktop()->width() - pLogin->width())/2,(QApplication::desktop()->height() - pLogin->height())/2);
}

void adjust::on_btn_adjustOk_clicked()
{
    switch(ui->cmb_adjust->currentIndex())
    {
    case 0:
        pSimple->show();
        pSimple->move((QApplication::desktop()->width() - pSimple->width())/2,(QApplication::desktop()->height() - pSimple->height())/2);
        break;
    case 1:
        spanAdjust();
        break;
    case 2:
        break;
    case 3:
        this->btn_show();
        btime = true;
        break;
    case 4:
        badjust = true;
        this->btn_show();
        break;
    case 5:
    default:
        break;
    }
}

void adjust::btn_show()
{
    ui->btn_num_0->show();
    ui->btn_num_1->show();
    ui->btn_num_2->show();
    ui->btn_num_3->show();
    ui->btn_num_4->show();
    ui->btn_num_5->show();
    ui->btn_num_6->show();
    ui->btn_num_7->show();
    ui->btn_num_8->show();
    ui->btn_num_9->show();
    ui->btn_num_10->show();
    ui->btn_num_Point->show();
    ui->btn_num_add->show();
    ui->btn_num_sub->show();
    ui->btn_num_clr->show();

    ui->btn_adjustOk->hide();
    ui->cmb_adjust->hide();
}

void adjust::btn_close()
{
    ui->btn_num_0->hide();
    ui->btn_num_1->hide();
    ui->btn_num_2->hide();
    ui->btn_num_3->hide();
    ui->btn_num_4->hide();
    ui->btn_num_5->hide();
    ui->btn_num_6->hide();
    ui->btn_num_7->hide();
    ui->btn_num_8->hide();
    ui->btn_num_9->hide();
    ui->btn_num_10->hide();
    ui->btn_num_Point->hide();
    ui->btn_num_add->hide();
    ui->btn_num_sub->hide();
    ui->btn_num_clr->hide();

    ui->btn_adjustOk->show();
    ui->cmb_adjust->show();
}

void adjust::on_btn_num_1_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"1");
}

void adjust::on_btn_num_2_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"2");
}

void adjust::on_btn_num_3_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"3");
}

void adjust::on_btn_num_4_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"4");
}

void adjust::on_btn_num_5_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"5");
}

void adjust::on_btn_num_6_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"6");
}

void adjust::on_btn_num_7_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"7");
}

void adjust::on_btn_num_8_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"8");
}

void adjust::on_btn_num_9_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"9");
}

void adjust::on_btn_num_Point_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),".");
}

void adjust::on_btn_num_0_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"0");
}

void adjust::on_btn_num_sub_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"-");
}

void adjust::on_btn_num_clr_clicked()
{
    str = QString("");
}

void adjust::on_btn_num_10_clicked()
{
    str = QString("");
    this->btn_close();
    badjust = false;
    btime = false;
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
    strTemp = QString(" 0");
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
