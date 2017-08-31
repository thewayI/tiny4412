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
    pSerialUI  = new Serial(this, pSerialHost);
    pMachine   = new Machine;
    pRemoteETH = new RemoteEth;
    pDebugInfo = new debugInfo;
    pConfigure->close();
    pAbout->close();
    pAdjust->close();
    pSerialUI->close();
    pMachine->close();
    pRemoteETH->close();
}

manu::~manu()
{
    delete ui;
}

void manu::on_btn_configureSensor_clicked()
{
    pAdjust->pTimer2->start();
    pAdjust->show();
}

void manu::on_btn_remoteSerial_clicked()
{
    pSerialUI->show();
}

void manu::on_btn_remoteMachine_clicked()
{
    pMachine->show();
}

void manu::on_btn_remoteETH_clicked()
{
    pRemoteETH->show();
}

void manu::on_btn_about_clicked()
{
    pAbout->show();
}

void manu::on_btn_debugInfo_clicked()
{

}
