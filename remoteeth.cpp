#include "remoteeth.h"
#include <QSettings>
#include "ui_remoteeth.h"

RemoteEth::RemoteEth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteEth)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);


    pKeyBoard = new keyBoard;

    pTimer = new QTimer(this);
    pTimer->setInterval(100);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    pTimer->start();

    bIPFlag = false;
    bNetMaskFlag = false;
    bGateWayFlag = false;
    bNetPortFlag = false;

    ui->btn_IP->setText(configIniWrite->value("eth/ip").toString());
    ui->btn_netmask->setText(configIniWrite->value("eth/netMask").toString());
    ui->btn_gateway->setText(configIniWrite->value("eth/gateWay").toString());
    ui->btn_netport->setText(configIniWrite->value("eth/port").toString());


}

RemoteEth::~RemoteEth()
{
    delete ui;
}

void RemoteEth::onTimeOut()
{
    if(bIPFlag)
    {
        if(pKeyBoard->editFlag)
        {            
            ui->btn_IP->setText(pKeyBoard->str);
            QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
            configIniWrite->setValue("/eth/ip", pKeyBoard->str);
            delete configIniWrite;
        }
        else
        {            
            bIPFlag = false;
        }
    }
    if(bNetMaskFlag)
    {
        if(pKeyBoard->editFlag)
        {
            ui->btn_netmask->setText(pKeyBoard->str);

            QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
            configIniWrite->setValue("/eth/netMask", pKeyBoard->str);
            delete configIniWrite;
        }
        else
        {
            bNetMaskFlag = false;
        }
    }
    if(bGateWayFlag)
    {
        if(pKeyBoard->editFlag)
        {
            ui->btn_gateway->setText(pKeyBoard->str);

            QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
            configIniWrite->setValue("/eth/gateWay", pKeyBoard->str);
            delete configIniWrite;
        }
        else
        {
            bGateWayFlag = false;
        }
    }
    if(bNetPortFlag)
    {
        if(pKeyBoard->editFlag)
        {
            ui->btn_netport->setText(pKeyBoard->str);

            QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
            configIniWrite->setValue("/eth/port", pKeyBoard->str);
            delete configIniWrite;
        }
        else
        {
            bNetPortFlag = false;
        }
    }
}

void RemoteEth::on_ok_clicked()
{
    this->close();
}

void RemoteEth::on_btn_IP_clicked()
{
    pKeyBoard->str = QString("");
    bIPFlag = true;
    pKeyBoard->editFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(800, 240);
}

void RemoteEth::on_btn_netmask_clicked()
{
    pKeyBoard->str = QString("");
    bNetMaskFlag = true;
    pKeyBoard->editFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(800, 240);
}

void RemoteEth::on_btn_gateway_clicked()
{
    pKeyBoard->str = QString("");
    bGateWayFlag = true;
    pKeyBoard->editFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(800, 240);
}

void RemoteEth::on_btn_netport_clicked()
{
    pKeyBoard->str = QString("");
    bNetPortFlag = true;
    pKeyBoard->editFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(800, 240);
}

void RemoteEth::on_btn_configureMachine_2_clicked()
{
    this->close();
}
