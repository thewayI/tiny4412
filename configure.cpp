#include "configure.h"
#include "ui_configure.h"

u_int8_t g8checkSts = 0;
u_int8_t g8Accuracy = 0;

configure::configure(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::configure)
{
    ui->setupUi(this);
    pSerial = serial;
    ui->cmb_accuracy->setCurrentIndex(2);
    g8Accuracy = ui->cmb_accuracy->currentText().toInt();
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

    ui->checkBox->setCheckState(Qt::Unchecked);
    ui->checkBox_2->setCheckState(Qt::Unchecked);
    ui->checkBox_4->setCheckState(Qt::Unchecked);
    ui->checkBox_5->setCheckState(Qt::Unchecked);
    ui->checkBox_6->setCheckState(Qt::Unchecked);
    ui->checkBox_7->setCheckState(Qt::Unchecked);
}

void configure::on_btn_state_clicked()
{
    ui->comboBox_chanFunc->setCurrentIndex(3);
    ui->comboBox_Mode->setCurrentIndex(1);

    ui->comboBox_chanFunc_2->setCurrentIndex(2);
    ui->comboBox_Mode_2->setCurrentIndex(0);
}

void configure::on_btn_configureMachine_2_clicked()
{
    this->close();
}

void configure::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->checkState() == Qt::Checked)
    {
        ui->checkBox->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                      "background-color: rgba(255, 255, 255, 20);"));
        g8checkSts |= CHAN_A_PEAK_CHECK;
    }
    else
    {
        ui->checkBox->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        g8checkSts &= ~CHAN_A_PEAK_CHECK;
    }

}

void configure::on_checkBox_2_stateChanged(int arg1)
{
    if(ui->checkBox_2->checkState() == Qt::Checked)
    {
        ui->checkBox_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                      "background-color: rgba(255, 255, 255, 20);"));
        g8checkSts |= CHAN_A_RATE_CHECK;
    }
    else
    {
        ui->checkBox_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        g8checkSts &= ~CHAN_A_RATE_CHECK;
    }
}

void configure::on_checkBox_4_stateChanged(int arg1)
{
    if(ui->checkBox_4->checkState() == Qt::Checked)
    {
        ui->checkBox_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                      "background-color: rgba(255, 255, 255, 20);"));
        g8checkSts |= CHAN_A_ADJUST_ZERO_PEAK;
    }
    else
    {
        ui->checkBox_4->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        g8checkSts &= ~CHAN_A_ADJUST_ZERO_PEAK;
    }
}

void configure::on_checkBox_3_stateChanged(int arg1)
{
    if(ui->checkBox_3->checkState() == Qt::Checked)
    {
        ui->checkBox_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                      "background-color: rgba(255, 255, 255, 20);"));
        g8checkSts |= CHAN_A_PRESSURE_PEAK;
    }
    else
    {
        ui->checkBox_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        g8checkSts &= ~CHAN_A_PRESSURE_PEAK;
    }
}

void configure::on_cmb_accuracy_currentIndexChanged(int index)
{
    g8Accuracy = ui->cmb_accuracy->currentText().toInt();
}

void configure::on_checkBox_7_stateChanged(int arg1)
{
    if(ui->checkBox_7->checkState() == Qt::Checked)
    {
        ui->checkBox_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                      "background-color: rgba(255, 255, 255, 20);"));
        g8checkSts |= CHAN_B_PEAK_CHECK;
    }
    else
    {
        ui->checkBox_7->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        g8checkSts &= ~CHAN_B_PEAK_CHECK;
    }
}

void configure::on_checkBox_6_stateChanged(int arg1)
{
    if(ui->checkBox_6->checkState() == Qt::Checked)
    {
        ui->checkBox_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                      "background-color: rgba(255, 255, 255, 20);"));
        g8checkSts |= CHAN_B_RATE_CHECK;
    }
    else
    {
        ui->checkBox_6->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        g8checkSts &= ~CHAN_B_RATE_CHECK;
    }
}

void configure::on_checkBox_5_stateChanged(int arg1)
{
    if(ui->checkBox_5->checkState() == Qt::Checked)
    {
        ui->checkBox_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
                                                      "background-color: rgba(255, 255, 255, 20);"));
        g8checkSts |= CHAN_B_ADJUST_ZERO_PEAK;
    }
    else
    {
        ui->checkBox_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));
        g8checkSts &= ~CHAN_B_ADJUST_ZERO_PEAK;
    }
}
