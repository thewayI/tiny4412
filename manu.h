#ifndef MANU_H
#define MANU_H

#include <QWidget>
#include "posix_qextserialport.h"
#include "configure.h"
#include "about.h"
#include "adjust.h"
//#include "sensor.h"
#include "serial.h"
#include "contoller.h"
#include "machine.h"
#include "remoteeth.h"
#include "commandList.h"
#include "manu.h"
#include "debuginfo.h"
#include "lockunlock.h"
#include "leaktest.h"

namespace Ui {
class manu;
}

class manu : public QWidget
{
    Q_OBJECT

public:
    explicit manu(QWidget *parent = 0, Posix_QextSerialPort *pSerialDevice = NULL, Posix_QextSerialPort *pSerial = NULL);
    ~manu();

private:
    Ui::manu *ui;

public:
    Posix_QextSerialPort *pSerialDev;
    Posix_QextSerialPort *pSerialHost;
    configure *pConfigure;
    about *pAbout;
    adjust *pAdjust;
    //sensor *pSensor;
    Serial *pSerialUI;
    Contoller *pController;
    Machine *pMachine;
    RemoteEth *pRemoteETH;
    debugInfo *pDebugInfo;
    lockUnLock *pLock;
    leakTest   *pLeakTest;

    bool bShowFlag;

private slots:
    void on_btn_configureSensor_clicked();
    void on_btn_about_clicked();
    void on_btn_debugInfo_clicked();
    void on_btn_configureChan_clicked();
    void on_btn_configureMachine_clicked();
    void on_btn_configureSerial_clicked();
    void on_btn_configureETH_clicked();
    void on_btn_leakTest_clicked();
    void on_btn_lockUnlock_clicked();
    void on_btn_configureMachine_2_clicked();
};

#endif // MANU_H



