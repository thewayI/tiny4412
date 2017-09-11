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

    pTimer = new QTimer(this);
    pTimer->setInterval(10);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
}

leakTest::~leakTest()
{
    delete ui;
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
        ui->lineEdit_D_value->setText(str);
        str = QString::number(m_currentPressure, 'f', 6);
        ui->label_view->setText(str);
    }

    m_timer += 0.01;
    str = QString::number(m_timer, 'f', 2);
    ui->lineEdit_time->setText(str);

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
    pTimer->start();
}

void leakTest::on_pushButton_2_clicked()
{
    pTimer->stop();
    this->close();
}
