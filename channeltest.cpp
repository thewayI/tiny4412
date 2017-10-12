#include "channeltest.h"
#include "ui_channeltest.h"

channelTest::channelTest(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::channelTest)
{
    ui->setupUi(this);
    QString str;
    bEditFlag = false;
    pSerial = serial;
    pKeyBoard = new keyBoard;
    pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    str = QString("");
    sendSerialCommand(pSerial, CMD_GET_FLITER, &str);
    ui->pushButton->setText(str.right(str.length() - QString("1 FL ").length()));
}

channelTest::~channelTest()
{
    delete ui;
}

void channelTest::onTimeout()
{
    QString str;
    QString strResult = QString("");
    if(bEditFlag)
    {
        if(pKeyBoard->editFlag)
            ui->pushButton->setText(pKeyBoard->str);
        else
        {
            str = QString(" ") + pKeyBoard->str;
            bEditFlag = false;
            sendSerialCommandArg(pSerial, CMD_SET_FLITER, str, &strResult);
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

void channelTest::on_pushButton_clicked()
{
    pKeyBoard->str = QString("");
    pKeyBoard->editFlag = true;
    bEditFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(80, 200);
}

void channelTest::on_pushButton_4_clicked()
{
    this->close();
}
