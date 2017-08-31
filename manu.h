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

private slots:
    void on_btn_configureSensor_clicked();
    void on_btn_remoteSerial_clicked();
    void on_btn_remoteMachine_clicked();
    void on_btn_remoteETH_clicked();
    void on_btn_about_clicked();
    void on_btn_debugInfo_clicked();
};

#endif // MANU_H

