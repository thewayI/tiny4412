#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QString>
#include <QFile>
#include <QWidget>
#include <QtGui>

#include "unitchange.h"
#include "configure.h"
#include "about.h"
#include "adjust.h"
//#include "sensor.h"
#include "serial.h"
#include "contoller.h"
#include "machine.h"
#include "remoteeth.h"
#include "commandList.h"
#include "posix_qextserialport.h"
//#include "adjust.h"

namespace Ui {
class mainWindow;
}

class mainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit mainWindow(QWidget *parent = 0);
    ~mainWindow();

private slots:
    void onTimeOut();
    void on_btn_manu_clicked();
    void show_manu();
    void showSubConfigureMenu();
    void showSubRemoteMenu();
    void showSubControlMenu();
    void close_manu();
    void closeSubConfigureMenu();
    void closeSubRemoteMenu();
    void closeSubControlMenu();


    void on_btn_configure_clicked();

    void on_btn_standby_clicked();

    void on_btn_measure_clicked();

    void on_btn_control_clicked();

    void on_btn_air_clicked();

    void on_btn_remote_clicked();

    void on_btn_procedure_clicked();

    void on_btn_serial_clicked();

    void on_btn_about_clicked();

    void on_btn_configureChan_clicked();

    void on_btn_configureSensor_clicked();

    void on_btn_configureControl_clicked();

    void on_btn_remoteMachine_clicked();

    void on_btn_remoteSerial_clicked();

    void on_btn_remoteETH_clicked();

    void on_btn_unitChange_clicked();

    void on_btn_controlstep_clicked();

    void on_btn_controlsetpoint_clicked();

    void on_btn_controlrange_clicked();

//    void on_pushButton_clicked();

private:
    Ui::mainWindow *ui;

public :
    QTimer *pTimer;
    int m32ButtonClick;
    int m32ButtonClickRemote;
    int m32ButtonClickManu;
    int m32ButtonClickControl;
    int m32ButtonClickControlStep;
    int m32ButtonClickControlSetPoint;
    int m32ButtonClickControlRange;
    int testloop;

    unitChange *pUnit;
    configure *pConfigure;
    about *pAbout;
    adjust *pAdjust;
    //sensor *pSensor;
    Serial *pSerialUI;
    Contoller *pController;
    Machine *pMachine;
    RemoteEth *pRemoteETH;
    Posix_QextSerialPort *pSerialHost;
    Posix_QextSerialPort *pSerialDev;
    //adjust *pAdjust;

};

#endif // MAINWINDOW_H
