#ifndef UNITCHANGE_H
#define UNITCHANGE_H

#include <QWidget>
#include <QString>
#include "commandList.h"
#include "posix_qextserialport.h"

typedef struct conversiontoPSI{
    unsigned char index;
    double coefficient;
    QString name;
}S_CONVER_PSI;

namespace Ui {
class unitChange;
}

class unitChange : public QWidget
{
    Q_OBJECT

public:
    explicit unitChange(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~unitChange();

private slots:

    void getcoefficient(int index);

    void on_pushButton_38_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_24_clicked();

    void on_pushButton_19_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    //void on_pushButton_22_clicked();

    void on_pushButton_21_clicked();

    void on_pushButton_23_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_26_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_25_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_27_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_32_clicked();

    void on_pushButton_36_clicked();

    void on_pushButton_31_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_34_clicked();

    void on_pushButton_33_clicked();

    void on_pushButton_35_clicked();

    void setAllbuttonEnable();

    void on_btn_configureMachine_2_clicked();

    void on_pushButton_39_clicked();

private:
    Ui::unitChange *ui;

public :
    int m32UnitState;
    double conversiontoPSI;
    double baseConver;
    QString unitName;
    Posix_QextSerialPort *pSerial;
};
#define CONVERSION_COUNT    36
extern S_CONVER_PSI gSconver[CONVERSION_COUNT];

#endif // UNITCHANGE_H
