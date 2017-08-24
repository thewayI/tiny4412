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
    {33,68.94757, QString("HPa")},
    {34,0.006894757, QString("MPa")},
    //{35,, QString("")},
};

unitChange::unitChange(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::unitChange)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    m32UnitState= 0;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
    pSerial = serial;
}

unitChange::~unitChange()
{
    delete ui;
}

void unitChange::on_pushButton_38_clicked()
{
    this->close();
}

void unitChange::on_pushButton_clicked()
{
    m32UnitState= 0;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_5_clicked()
{
    m32UnitState= 1;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_4_clicked()
{
    m32UnitState= 2;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_20_clicked()
{
    m32UnitState= 3;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_24_clicked()
{
    m32UnitState= 4;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_19_clicked()
{
    m32UnitState= 5;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_3_clicked()
{
    m32UnitState= 6;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_2_clicked()
{
    m32UnitState= 7;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_6_clicked()
{
    m32UnitState= 8;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_22_clicked()
{



}

void unitChange::on_pushButton_21_clicked()
{
    m32UnitState= 9;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_23_clicked()
{
    m32UnitState= 10;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_8_clicked()
{
    m32UnitState= 11;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_12_clicked()
{
    m32UnitState= 12;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_7_clicked()
{
    m32UnitState= 13;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_26_clicked()
{
    m32UnitState= 14;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_30_clicked()
{
    m32UnitState= 15;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_25_clicked()
{
    m32UnitState= 16;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_10_clicked()
{
    m32UnitState= 17;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_9_clicked()
{
    m32UnitState= 18;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_11_clicked()
{
    m32UnitState= 19;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_28_clicked()
{
    m32UnitState= 20;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_27_clicked()
{
    m32UnitState= 21;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_29_clicked()
{
    m32UnitState= 22;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_14_clicked()
{
    m32UnitState= 23;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_18_clicked()
{
    m32UnitState= 24;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_13_clicked()
{
    m32UnitState= 25;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_32_clicked()
{
    m32UnitState= 26;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_36_clicked()
{
    m32UnitState= 27;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_31_clicked()
{
    m32UnitState= 28;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_16_clicked()
{
    m32UnitState= 29;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_15_clicked()
{
    //conversiontoPSI = 51715.08;
}

void unitChange::on_pushButton_17_clicked()
{
    m32UnitState= 31;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_34_clicked()
{
    m32UnitState= 32;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_33_clicked()
{
    m32UnitState= 33;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}

void unitChange::on_pushButton_35_clicked()
{
    m32UnitState= 34;
    conversiontoPSI = gSconver[m32UnitState].coefficient;
    unitName = gSconver[m32UnitState].name;
}
