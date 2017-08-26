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
    pTimer->setInterval(100);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    pTimer->start();

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
