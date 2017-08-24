#include "configure.h"
#include "ui_configure.h"

configure::configure(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::configure)
{
    ui->setupUi(this);
    pSerial = serial;
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

configure::~configure()
{
    delete ui;
}

void configure::on_btn_ok_clicked()
{
    this->close();
}

void configure::on_btn_default_clicked()
{
    ui->comboBox_chanFunc->setCurrentIndex(1);
    ui->comboBox_Mode->setCurrentIndex(0);

    ui->comboBox_chanFunc_2->setCurrentIndex(1);
    ui->comboBox_Mode_2->setCurrentIndex(1);
}

void configure::on_btn_state_clicked()
{
    ui->comboBox_chanFunc->setCurrentIndex(3);
    ui->comboBox_Mode->setCurrentIndex(1);

    ui->comboBox_chanFunc_2->setCurrentIndex(2);
    ui->comboBox_Mode_2->setCurrentIndex(0);
}
