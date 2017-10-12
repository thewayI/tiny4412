#ifndef LEAKTEST_H
#define LEAKTEST_H

#include <QWidget>
#include <QTimer>
#include <QString>
#include <QSettings>
#include "commandList.h"
#include "posix_qextserialport.h"

namespace Ui {
class leakTest;
}

class leakTest : public QWidget
{
    Q_OBJECT

public:
    explicit leakTest(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~leakTest();

private slots:
    void on_pushButton_clicked();

    void onTimeOut(void);
    void onTimeOut1(void);

    void on_pushButton_2_clicked();

    void on_btn_configureMachine_2_clicked();

private:
    Ui::leakTest *ui;

public:
    Posix_QextSerialPort *pSerial;
    QTimer *pTimer;
    QTimer *pTimer1;

    bool btimeStartFlag;
    double m_timer;
    double m_basePressure;
    double m_currentPressure;
};

#endif // LEAKTEST_H
