#include "unitchange.h"
#include "ui_unitchange.h"

S_CONVER_PSI gSconver[] = {
    {0, 1.0, QString("psi")},
    {1, 2.036020, QString("inHg@0°C")},
    {2, 2.041772, QString("inHg@60°F")},
    {3, 27.68067, QString("inH2O@4°C")},
    {4, 27.72977, QString("inH2O@20°C")},
    {5, 27.70759, QString("inH2O@60°F")},
    {6, 2.306726, QString("ftH2O@4°C")},
    {7, 2.310814, QString("ftH2O@20°C")},
    {8, 2.308966, QString("ftH2O@60°F")},
    {9, 51715.08, QString("mtorr (@0°C)")},
    {10,26.92334, QString("inSW @ 0°C ")},
    {11,2.243611, QString("ftSW @ 0°C")},
    {12,0.06804596, QString("atm")},
    {13,0.06894757, QString("Bars")},
    {14,68.94757, QString("mBars")},
    {15,703.0890, QString("mmH2O@4°C")},
    {16,70.30890, QString("cmH2O@4°C")},
    {17,0.7030890, QString("mH2O@4°C")},
    {18,51.71508, QString("mmHg@0°C")},
    {19,5.171508, QString("cmHg@0°C")},
    {20,51.71508, QString("Torr")},
    {21,6.894757, QString("Kpa")},
    {22,6894.757, QString("Pa")},
    {23,68947.57, QString("Dynes/cm2")},
    {24,70.30697, QString("g/cm2")},
    {25,0.07030697, QString("kg/cm2")},
    {26,0.6838528, QString("mSW @ 0°C")},
    {27,16, QString("oz/in2")},
    {28,144, QString("psf")},
    {29,0.072, QString("tsf")},
    //{30,, QString("% Full Scale")},
    {31,51715.08, QString("microns Hg @ 0°C")},
    {32,0.0005, QString("tsi")},
    {34,68.94757, QString("HPa")},
    {35,0.006894757, QString("MPa")},
    //{35,, QString("")},
};

unitChange::unitChange(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::unitChange)
{
    ui->setupUi(this);
    pSerial = serial;
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAllbuttonEnable();
    QString str = QString("");
    sendSerialCommand(pSerial, CMD_GET_UNIT_CODE, &str);
    if(str.size() != 0)
    {
        str = str.right(str.length() - QString("1 U ").length());
        m32UnitState = str.toInt() - 1;
        baseConver = gSconver[m32UnitState].coefficient;
        switch (m32UnitState) {
        case 21:
            ui->pushButton_27->setEnabled(false);
            break;
        default:
            break;
        };
    }
    else
    {
        m32UnitState= 0;
    }
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

unitChange::~unitChange()
{
    delete ui;
}

void unitChange::on_pushButton_38_clicked()
{
    this->close();
}

void unitChange::setAllbuttonEnable(void)
{
   ui->pushButton_7->setEnabled(true);
   ui->pushButton_28->setEnabled(true);
   ui->pushButton_25->setEnabled(true);
   ui->pushButton_14->setEnabled(true);
   ui->pushButton->setEnabled(true);

   ui->pushButton_16->setEnabled(true);
   ui->pushButton_30->setEnabled(true);
   ui->pushButton_37->setEnabled(true);
   ui->pushButton_8->setEnabled(true);
   ui->pushButton_3->setEnabled(true);
   ui->pushButton_32->setEnabled(true);
   ui->pushButton_24->setEnabled(true);
   ui->pushButton_2->setEnabled(true);
   ui->pushButton_15->setEnabled(true);
   ui->pushButton_9->setEnabled(true);
   ui->pushButton_34->setEnabled(true);
   ui->pushButton_13->setEnabled(true);
   ui->pushButton_39->setEnabled(true);
   ui->pushButton_18->setEnabled(true);
   ui->pushButton_4->setEnabled(true);

   ui->pushButton_12->setEnabled(true);

   ui->pushButton_19->setEnabled(true);
   ui->pushButton_11->setEnabled(true);
   ui->pushButton_10->setEnabled(true);
   ui->pushButton_17->setEnabled(true);
   ui->pushButton_23->setEnabled(true);
   ui->pushButton_38->setEnabled(true);
   ui->pushButton_36->setEnabled(true);
   ui->pushButton_5->setEnabled(true);
   ui->pushButton_20->setEnabled(true);
   ui->pushButton_21->setEnabled(true);
   ui->pushButton_29->setEnabled(true);
   ui->pushButton_35->setEnabled(true);
   ui->pushButton_26->setEnabled(true);
   ui->pushButton_6->setEnabled(true);
   ui->pushButton_31->setEnabled(true);
   ui->pushButton_33->setEnabled(true);
   ui->pushButton_27->setEnabled(true);
}

void unitChange::getcoefficient(int index)
{
    int loop = 0;
    for(loop = 0; loop < CONVERSION_COUNT; loop++)
    {
        if(index == gSconver[loop].index)
        {
            conversiontoPSI = gSconver[loop].coefficient;
            unitName = gSconver[loop].name;
            return;
        }
    }

}

void unitChange::on_pushButton_clicked()
{
    m32UnitState= 0;
    getcoefficient(m32UnitState);
    setAllbuttonEnable();
    ui->pushButton->setEnabled(false);
}

void unitChange::on_pushButton_5_clicked()
{
    m32UnitState= 1;
    getcoefficient(m32UnitState);
    setAllbuttonEnable();
    ui->pushButton_5->setEnabled(false);
}

void unitChange::on_pushButton_4_clicked()
{
    m32UnitState= 2;
    getcoefficient(m32UnitState);
   setAllbuttonEnable();
    ui->pushButton_4->setEnabled(false);
}

void unitChange::on_pushButton_20_clicked()
{
    m32UnitState= 3;
    getcoefficient(m32UnitState);
    setAllbuttonEnable();
    ui->pushButton_20->setEnabled(false);
}

void unitChange::on_pushButton_24_clicked()
{
    m32UnitState= 4;
    getcoefficient(m32UnitState);
    setAllbuttonEnable();
    ui->pushButton_24->setEnabled(false);
}

void unitChange::on_pushButton_19_clicked()
{
    m32UnitState= 5;
    getcoefficient(m32UnitState);
    setAllbuttonEnable();
    ui->pushButton_19->setEnabled(false);
}

void unitChange::on_pushButton_3_clicked()
{
    m32UnitState= 6;
   getcoefficient(m32UnitState);
   setAllbuttonEnable();
    ui->pushButton_3->setEnabled(false);
}

void unitChange::on_pushButton_2_clicked()
{
    m32UnitState= 7;
    getcoefficient(m32UnitState);
    setAllbuttonEnable();
    ui->pushButton_2->setEnabled(false);
}

void unitChange::on_pushButton_6_clicked()
{
    m32UnitState= 8;
    getcoefficient(m32UnitState);
    setAllbuttonEnable();
    ui->pushButton_6->setEnabled(false);
}

void unitChange::on_pushButton_21_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 9;
    getcoefficient(m32UnitState);
    ui->pushButton_21->setEnabled(false);
}

void unitChange::on_pushButton_23_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 10;
    getcoefficient(m32UnitState);
    ui->pushButton_23->setEnabled(false);
}

void unitChange::on_pushButton_8_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 11;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
    ui->pushButton_8->setEnabled(false);
}

void unitChange::on_pushButton_12_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 12;
    getcoefficient(m32UnitState);
    ui->pushButton_12->setEnabled(false);
}

void unitChange::on_pushButton_7_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 13;
    getcoefficient(m32UnitState);
    ui->pushButton_7->setEnabled(false);
}

void unitChange::on_pushButton_26_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 14;
    getcoefficient(m32UnitState);
    ui->pushButton_26->setEnabled(false);
}

void unitChange::on_pushButton_30_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 15;
    getcoefficient(m32UnitState);
    ui->pushButton_30->setEnabled(false);
}

void unitChange::on_pushButton_25_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 16;
    getcoefficient(m32UnitState);
    ui->pushButton_25->setEnabled(false);
}

void unitChange::on_pushButton_10_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 17;
    getcoefficient(m32UnitState);
    ui->pushButton_10->setEnabled(false);
}

void unitChange::on_pushButton_9_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 18;
    getcoefficient(m32UnitState);
    ui->pushButton_9->setEnabled(false);
}

void unitChange::on_pushButton_11_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 19;
    getcoefficient(m32UnitState);
    ui->pushButton_11->setEnabled(false);
}

void unitChange::on_pushButton_28_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 20;
    getcoefficient(m32UnitState);
    ui->pushButton_28->setEnabled(false);
}

void unitChange::on_pushButton_27_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 21;
    getcoefficient(m32UnitState);
    ui->pushButton_27->setEnabled(false);
}

void unitChange::on_pushButton_29_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 22;
    getcoefficient(m32UnitState);
    ui->pushButton_29->setEnabled(false);
}

void unitChange::on_pushButton_14_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 23;
    getcoefficient(m32UnitState);
    ui->pushButton_14->setEnabled(false);
}

void unitChange::on_pushButton_18_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 24;
    getcoefficient(m32UnitState);
    ui->pushButton_18->setEnabled(false);
}

void unitChange::on_pushButton_13_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 25;
    getcoefficient(m32UnitState);
    ui->pushButton_13->setEnabled(false);
}

void unitChange::on_pushButton_32_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 26;
    getcoefficient(m32UnitState);
    ui->pushButton_32->setEnabled(false);
}

void unitChange::on_pushButton_36_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 27;
    getcoefficient(m32UnitState);
    ui->pushButton_36->setEnabled(false);
}

void unitChange::on_pushButton_31_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 28;
    getcoefficient(m32UnitState);
    ui->pushButton_31->setEnabled(false);
}

void unitChange::on_pushButton_16_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 29;
    getcoefficient(m32UnitState);
    ui->pushButton_16->setEnabled(false);
}

void unitChange::on_pushButton_15_clicked()
{
    setAllbuttonEnable();
    //conversiontoPSI = 51715.08;
}

void unitChange::on_pushButton_17_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 31;
    getcoefficient(m32UnitState);
    ui->pushButton_17->setEnabled(false);
}

void unitChange::on_pushButton_34_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 32;
    getcoefficient(m32UnitState);
    ui->pushButton_34->setEnabled(false);
}

void unitChange::on_pushButton_33_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 34;
    getcoefficient(m32UnitState);
    ui->pushButton_33->setEnabled(false);
}

void unitChange::on_pushButton_35_clicked()
{
    setAllbuttonEnable();
    m32UnitState= 35;
    getcoefficient(m32UnitState);
    ui->pushButton_35->setEnabled(false);
}

void unitChange::on_btn_configureMachine_2_clicked()
{
    this->close();
}

void unitChange::on_pushButton_39_clicked()
{
    this->close();
}
