#include "manu.h"
#include "ui_manu.h"

manu::manu(QWidget *parent, Posix_QextSerialPort *pSerialDevice, Posix_QextSerialPort *pSerial) :
    QWidget(parent),
    ui(new Ui::manu)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    pSerialDev = pSerialDevice;
    pSerialHost = pSerial;

    //create sub-UI
    pConfigure = new configure(this, pSerialDev);
    pAbout     = new about(this, pSerialDev);
    pAdjust = new adjust(this, pSerialDev);
    pLeakTest = new leakTest(this, pSerialDev);
    pSerialUI  = new Serial(this, pSerialHost);
    pMachine   = new Machine;
    pRemoteETH = new RemoteEth;
    pDebugInfo = new debugInfo;
    pLock      = new lockUnLock;
    pConfigure->close();
    pAbout->close();
    pAdjust->close();
    pSerialUI->close();
    pLeakTest->close();
    pMachine->close();
    pRemoteETH->close();
    pDebugInfo->close();
    pLock->close();

    pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    //ui->btn_configureMachine->setEnabled(true);
    bShowFlag = false;
}

manu::~manu()
{
    delete ui;
}

void manu::onTimeOut(void)
{

    switch(g32styleMode)
    {
    case 0:
        ui->frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/1.png);"));
        break;
    case 1:
        ui->frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_01.png);"));
        break;
    case 2:
        ui->frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_02.png);"));
        break;
    case 3:
        ui->frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_03.png);"));
        break;
    case 4:
        ui->frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_04.png);"));
        break;
    case 5:
        ui->frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_05.png);"));
        break;
    default:
        ui->frame_2->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/1.png);"));
        break;
    }
}

void manu::on_btn_configureSensor_clicked()
{
    if(pLock->bLockFlag)
    {
        QMessageBox::information(NULL, QString::fromUtf8("提示信息"), QString::fromUtf8("请解除锁定"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    else
    {
        pAdjust->pTimer2->start();
        pAdjust->show();
    }
}

void manu::on_btn_about_clicked()
{
    pAbout->pTimer->start();
    pAbout->show();
}

void manu::on_btn_debugInfo_clicked()
{
    pDebugInfo->pTimer->start();
    pDebugInfo->show();
}

void manu::on_btn_configureChan_clicked()
{
    pConfigure->show();
}

void manu::on_btn_configureMachine_clicked()
{
    pMachine->pTimer->start();
    pMachine->show();
}

void manu::on_btn_configureSerial_clicked()
{
    pSerialUI->pTimer->start();
    pSerialUI->show();
}

void manu::on_btn_configureETH_clicked()
{
    pRemoteETH->pTimer->start();
    pRemoteETH->show();
}

void manu::on_btn_leakTest_clicked()
{
    pLeakTest->pTimer->start();
    pLeakTest->pTimer1->start();
    pLeakTest->show();
}

void manu::on_btn_lockUnlock_clicked()
{
    pLock->pTimer->start();
    pLock->show();
}

void manu::on_btn_configureMachine_2_clicked()
{    
    pTimer->stop();
    bShowFlag = false;
    this->close();
}
