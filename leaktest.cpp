#include "leaktest.h"
#include "ui_leaktest.h"

leakTest::leakTest(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::leakTest)
{
    ui->setupUi(this);
    pSerial = serial;

    m_timer = 0.0;
    m_basePressure = 0.0;
    m_currentPressure = 0.0;
    btimeStartFlag =false;

    pTimer = new QTimer(this);
    pTimer->setInterval(10);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    pTimer1 = new QTimer(this);
    pTimer1->setInterval(1000);
    connect(pTimer1, SIGNAL(timeout()), this, SLOT(onTimeOut1()));

    ui->label_view->setText(QString("0.000000"));
    ui->lineEdit_time->setText(QString("0.00"));
    ui->pushButton_2->setEnabled(false);
}

leakTest::~leakTest()
{
    delete ui;
}

void leakTest::onTimeOut1(void)
{
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

void leakTest::onTimeOut(void)
{
    QString str;
    QString strsms;

    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &strsms);

    if(strsms.length() != 0)
    {

        //get the valid pressure
        str = strsms.right(strsms.length() - QString("1 ").length());
        m_currentPressure = str.toDouble();

        str = QString::number((m_currentPressure - m_basePressure), 'f', 6);
        if(btimeStartFlag)
            ui->lineEdit_D_value->setText(str);
        str = QString::number(m_currentPressure, 'f', 6);
        ui->label_view->setText(str);
    }

    if(btimeStartFlag)
    {
        m_timer += 0.01;
        str = QString::number(m_timer, 'f', 2);
        ui->lineEdit_time->setText(str);
    }
}

void leakTest::on_pushButton_clicked()
{
    QString strsms;
    QString str;
    sendSerialCommand(pSerial, CMD_GET_PRESSURE_READING, &strsms);

    if(strsms.length() != 0)
    {
        //get the valid pressure
        str = strsms.right(strsms.length() - QString("1 ").length());
        m_basePressure = str.toDouble();
        m_currentPressure = m_basePressure;
        str = QString::number(m_currentPressure, 'f', 6);
        ui->label_view->setText(str);
    }
    m_timer = 0;
    btimeStartFlag = true;
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setStyleSheet(QString::fromUtf8("border-top-left-radius:6px;\n"
"color: rgb(255, 255, 255);\n"
"border:2px solid rgba(255, 255, 255,70);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-top-right-radius:6px;\n"
"border-bottom-left-radius:6px;\n"
"border-bottom-right-radius:6px;"));
    ui->pushButton_2->setStyleSheet(QString::fromUtf8("border-top-left-radius:6px;\n"
"color: rgb(255, 255, 255);\n"
"border:2px solid rgba(255, 255, 255,70);\n"
"background-color: rgba(255, 255, 255, 20);\n"
"border-top-right-radius:6px;\n"
"border-bottom-left-radius:6px;\n"
"border-bottom-right-radius:6px;"));
}

void leakTest::on_pushButton_2_clicked()
{    
    btimeStartFlag = false;
    ui->pushButton->setEnabled(true);
    ui->pushButton->setStyleSheet(QString::fromUtf8("border-top-left-radius:6px;\n"
"color: rgb(255, 255, 255);\n"
"border:2px solid rgba(255, 255, 255,70);\n"
"background-color: rgba(255, 255, 255, 20);\n"
"border-top-right-radius:6px;\n"
"border-bottom-left-radius:6px;\n"
"border-bottom-right-radius:6px;"));
    ui->pushButton_2->setStyleSheet(QString::fromUtf8("border-top-left-radius:6px;\n"
"color: rgb(255, 255, 255);\n"
"border:2px solid rgba(255, 255, 255,70);\n"
"background-color: rgba(255, 255, 255, 0);\n"
"border-top-right-radius:6px;\n"
"border-bottom-left-radius:6px;\n"
"border-bottom-right-radius:6px;"));
}

void leakTest::on_btn_configureMachine_2_clicked()
{
    pTimer1->stop();
    pTimer->stop();
    ui->label_view->setText(QString("0.000000"));
    ui->lineEdit_time->setText(QString("0.00"));
    this->close();
}
