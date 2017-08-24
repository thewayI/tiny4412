#include "remoteeth.h"
#include "ui_remoteeth.h"

RemoteEth::RemoteEth(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RemoteEth)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    pKeyBoard = new keyBoard;

    pTimer = new QTimer(this);
    pTimer->setInterval(100);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    pTimer->start();

    bIPFlag = false;
    bNetMaskFlag = false;
    bGateWayFlag = false;
    bNetPortFlag = false;

    ui->btn_IP->setText(QString("10.0.0.20"));
    ui->btn_netmask->setText(QString("255.255.255.0"));
    ui->btn_gateway->setText(QString("10.0.0.5"));
    ui->btn_netport->setText(QString("49405"));
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
