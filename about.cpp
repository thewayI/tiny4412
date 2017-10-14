#include <QSettings>

#include "about.h"
#include "ui_about.h"
#include "commandList.h"

about::about(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    //ui->label->setText(QString::fromUtf8("Mensor CorPoration\n201  Barnes  Drive\nSam  Marcos,  Texas  78666\nVoice: (800) 984-4200\nFax: (512) 396-1820\nhttp://www.mensor.com\ntech.support@mensor.com\n\nModel : CPC600\n\n序列号: 612095\n软件版本 : 2.70.0\nIEEE-400 版本 : 2.6.3\n"));
    //ui->label->setFrameShape (QFrame::Box);
    pSerial = serial;
    QString str;


    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
    str = configIniWrite->value("about/company").toString();
    QByteArray ba = str.toLatin1();
    char *mm = ba.data();

    ui->tblWidget_baseInfo->setItem(0,0,new QTableWidgetItem(QString::fromUtf8("公司")));
    ui->tblWidget_baseInfo->setItem(0,1,new QTableWidgetItem(QString::fromUtf8(mm)));
    ui->tblWidget_baseInfo->setItem(1,0,new QTableWidgetItem(QString::fromUtf8("地址")));
    str = configIniWrite->value("about/addr").toString();
    ba = str.toLatin1();
    mm = ba.data();
    ui->tblWidget_baseInfo->setItem(1,1,new QTableWidgetItem(QString::fromUtf8(mm)));
    ui->tblWidget_baseInfo->setItem(2,0,new QTableWidgetItem(QString::fromUtf8("联系方式")));
    str = configIniWrite->value("about/contact").toString();
    ba = str.toLatin1();
    mm = ba.data();
    ui->tblWidget_baseInfo->setItem(2,1,new QTableWidgetItem(QString::fromUtf8((mm))));
    ui->tblWidget_baseInfo->setItem(3,0,new QTableWidgetItem(QString::fromUtf8("网址")));
    str = configIniWrite->value("about/web").toString();
    ba = str.toLatin1();
    mm = ba.data();
    ui->tblWidget_baseInfo->setItem(3,1,new QTableWidgetItem(QString::fromUtf8(mm)));

    ui->tblWidget_devInfo->setItem(0,0,new QTableWidgetItem(QString::fromUtf8("型号")));    
    ui->tblWidget_devInfo->setItem(1,0,new QTableWidgetItem(QString::fromUtf8("模式")));
    ui->tblWidget_devInfo->setItem(2,0,new QTableWidgetItem(QString::fromUtf8("序列号")));
    ui->tblWidget_devInfo->setItem(3,0,new QTableWidgetItem(QString::fromUtf8("软件版本")));
    ui->tblWidget_devInfo->setItem(0,1,new QTableWidgetItem());
    ui->tblWidget_devInfo->setItem(1,1,new QTableWidgetItem());
    ui->tblWidget_devInfo->setItem(2,1,new QTableWidgetItem());
    ui->tblWidget_devInfo->setItem(3,1,new QTableWidgetItem());

    ui->tblWidget_devInfo_2->setItem(0,0,new QTableWidgetItem(QString::fromUtf8("单位")));
    ui->tblWidget_devInfo_2->setItem(1,0,new QTableWidgetItem(QString::fromUtf8("最小值")));
    ui->tblWidget_devInfo_2->setItem(2,0,new QTableWidgetItem(QString::fromUtf8("最大值")));
    ui->tblWidget_devInfo_2->setItem(3,0,new QTableWidgetItem());
    ui->tblWidget_devInfo_2->setItem(0,1,new QTableWidgetItem());
    ui->tblWidget_devInfo_2->setItem(2,1,new QTableWidgetItem());
    ui->tblWidget_devInfo_2->setItem(1,1,new QTableWidgetItem());
    ui->tblWidget_devInfo_2->setItem(3,1,new QTableWidgetItem());

    u_int8_t loop = 0;
    u_int8_t subLoop = 0;

    for(loop = 0; loop < 4; loop++)
    {
        for(subLoop = 0; subLoop < 2; subLoop++)
        {
            ui->tblWidget_baseInfo->item(loop, subLoop)->setFlags(ui->tblWidget_baseInfo->item(loop, subLoop)->flags() & (~Qt::ItemIsSelectable));
        }
    }
    for(loop = 0; loop < 4; loop++)
    {
        for(subLoop = 0; subLoop < 2; subLoop++)
        {
            ui->tblWidget_devInfo->item(loop, subLoop)->setFlags(ui->tblWidget_devInfo->item(loop, subLoop)->flags() & (~Qt::ItemIsSelectable));
        }
    }
    for(loop = 0; loop < 4; loop++)
    {
        for(subLoop = 0; subLoop < 2; subLoop++)
        {
            ui->tblWidget_devInfo_2->item(loop, subLoop)->setFlags(ui->tblWidget_devInfo_2->item(loop, subLoop)->flags() & (~Qt::ItemIsSelectable));
        }
    }

    pTimer = new QTimer(this);
    pTimer->setInterval(2000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    ui->pushButton->hide();

    delete configIniWrite;

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

about::~about()
{
    delete ui;
}

void about::on_pushButton_clicked()
{
    pTimer->stop();
    this->close();
}

void about::onTimeOut(void)
{
    QString str = QString("");
    u_int32_t loop = 0;

    if(g8ConnectFlag)
    {
        //get id
        sendSerialCommand(pSerial, CMD_GET_ID, &str);

        if(str.length() == 0)
        {
            ui->tblWidget_devInfo->setItem(1,1,new QTableWidgetItem(QString::fromUtf8("6012095")));
        }
        else
        {
            ui->tblWidget_devInfo->item(0,1)->setText(((str.right(str.length() - QString("1 ID Mensor    ").length())).left(8)));
            ui->tblWidget_devInfo->item(1,1)->setText(((str.right(str.length() - QString("1 ID ").length())).left(8)));
            ui->tblWidget_devInfo->item(2,1)->setText(((str.right(str.length() - QString("1 ID Mensor DPT 6000, SN ").length())).left(8)));
            ui->tblWidget_devInfo->item(3,1)->setText(((str.right(str.length() - QString("1 ID Mensor DPT 6000, SN 41000F1F, ").length())).left(5)));
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
                    ui->tblWidget_devInfo_2->item(0,1)->setText((gUnitChange[loop].unitInfo));
                    break;
                }
            }
        }

        //get the maximum range
        str = QString("");
        sendSerialCommand(pSerial, CMD_GET_MAXIMUM, &str);
        if(str.length() != 0)
        {
            //qDebug("strTemp = %s\n", qPrintable(strTemp));
            //ui->lineEdit_max->setText((str.right(str.length() - QString("1 R+ ").length())).left(str.length() - QString("1 R+ ").length() - QString("\r\n").length()));
            ui->tblWidget_devInfo_2->item(2,1)->setText((((str.right(str.length() - QString("1 R+ ").length())).left(str.length() - QString("1 R+ ").length() - QString("\r\n").length()))));
        }
        //get the minimum range
        str = QString("");
        sendSerialCommand(pSerial, CMD_GET_MINIMUM, &str);
        if(str.length() != 0)
        {
            //qDebug("strTemp = %s\n", qPrintable(strTemp));
            //ui->lineEdit_min->setText((str.right(str.length() - QString("1 R- ").length())).left(str.length() - QString("1 R+ ").length() - QString("\r\n").length()));
            ui->tblWidget_devInfo_2->item(1,1)->setText((((str.right(str.length() - QString("1 R- ").length())).left(str.length() - QString("1 R+ ").length() - QString("\r\n").length()))));
        }
    }

}

void about::on_btn_configureMachine_2_clicked()
{
    pTimer->stop();
    this->close();
}
