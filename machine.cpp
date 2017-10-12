#include "machine.h"
#include "ui_machine.h"

Machine::Machine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Machine)
{
    ui->setupUi(this);
    ui->label->setText(QString("Emulation\nMode"));
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

}

Machine::~Machine()
{
    delete ui;
}

void Machine::onTimeOut(void)
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

void Machine::on_btn_default_clicked()
{
    this->close();
}

void Machine::on_btn_default_2_clicked()
{
    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);

    configIniWrite->setValue("style/mode", "0");
    g32styleMode = 0;

    delete configIniWrite;
}

void Machine::on_btn_configureMachine_2_clicked()
{
    this->pTimer->stop();
    this->close();
}

void Machine::on_btn_default_7_clicked()
{
    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);

    configIniWrite->setValue("style/mode", "2");
    g32styleMode = 2;

    delete configIniWrite;
}

void Machine::on_btn_default_5_clicked()
{
    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);

    configIniWrite->setValue("style/mode", "3");
    g32styleMode = 3;

    delete configIniWrite;
}

void Machine::on_btn_default_4_clicked()
{
    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);

    configIniWrite->setValue("style/mode", "4");
    g32styleMode = 4;

    delete configIniWrite;
}

void Machine::on_btn_default_6_clicked()
{
    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);

    configIniWrite->setValue("style/mode", "5");
    g32styleMode = 5;

    delete configIniWrite;
}

void Machine::on_btn_default_3_clicked()
{
    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);

    configIniWrite->setValue("style/mode", "1");
    g32styleMode = 1;

    delete configIniWrite;
}
