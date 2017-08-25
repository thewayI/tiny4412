#include "mainwindow.h"
#include "ui_mainwindow.h"

mainWindow::mainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    QString portName = "/dev/ttySAC2";   //获取串口名
    pSerialDev = new Posix_QextSerialPort(portName, QextSerialBase::Polling);
    pSerialDev->open(QIODevice::ReadWrite);
    //设置波特率
    pSerialDev->setBaudRate((BaudRateType)(BAUD115200));

    //设置数据位
    pSerialDev->setDataBits((DataBitsType)(DATA_8));

    //设置校验
    pSerialDev->setParity((ParityType)(PAR_NONE));

    //设置停止位
    pSerialDev->setStopBits((StopBitsType)(STOP_1));
    //设置数据流控制
    pSerialDev->setFlowControl(FLOW_OFF);
    //设置延时
    pSerialDev->setTimeout(TIME_OUT);

    pUnit      = new unitChange(this, pSerialDev);
    pConfigure = new configure(this, pSerialDev);
    pAbout     = new about(this, pSerialDev);
    pSensor    = new sensor(this, pSerialDev);
    pSerialUI  = new Serial(this, pSerialHost);
    pController= new Contoller(this, pSerialDev);
    pMachine   = new Machine;
    pRemoteETH = new RemoteEth;
    pUnit->close();
    pConfigure->close();
    pAbout->close();
    pSensor->close();
    pSerialUI->close();
    pController->close();
    pMachine->close();
    pRemoteETH->close();
    //pAdjust    = new adjust;

    //creator a timer
    pTimer = new QTimer(this);
    pTimer->setInterval(500);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    pTimer->start();

    ui->btn_unitChange->setText(tr("MPa A"));
    ui->dsb_step->setSingleStep(0.0005); // 步长
    ui->dsb_setpoint->setSingleStep(1); // 步长
    ui->dsb_range->setSingleStep(0.0005); // 步长

    ui->dsb_step->setValue(0.001);
    ui->dsb_setpoint->setValue(1);
    ui->dsb_range->setValue(1.031);

    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    m32ButtonClick = 0;
    m32ButtonClickRemote = 0;
    m32ButtonClickManu = 0;
    m32ButtonClickControl = 0;
    m32ButtonClickControlStep = 0;
    m32ButtonClickControlSetPoint = 0;
    m32ButtonClickControlRange = 0;


    ui->dsb_range->hide();
    ui->dsb_setpoint->hide();
    ui->dsb_step->hide();
    ui->label_step->hide();
    ui->label_setpoint->hide();
    ui->label_range->hide();
}

mainWindow::~mainWindow()
{
    delete ui;
}

void mainWindow::onTimeOut()
{
    double data = 10.10403;
    QString strsms;
    QString str;
    double testData;
    sendSerialCommand(pSerialDev, CMD_GET_PRESSURE_READING, &strsms);


    //transmit device response
    //if(pSerialHost != NULL)
    //    pSerialHost->write(strsms.toAscii());

    if(strsms.length() != 0)
    {
        //get the valid pressure
        str = strsms.right(strsms.length() - QString("1 ").length());
        testData = str.toDouble();
        testData = testData * pUnit->conversiontoPSI;
        str = QString::number(testData, 'f', (ui->dsb_setpoint->text().toInt()));
        testData = str.toDouble();
        // display data
        ui->lcdNumber_2->display(testData);
    }
    else
    {
        ui->lcdNumber_2->display(data * pUnit->conversiontoPSI);
    }
    //send a basic query pressure readings

    ui->btn_unitChange->setText(pUnit->unitName);
    ui->lcdNumber->display(pUnit->conversiontoPSI);

}

void mainWindow::close_manu()
{
    ui->btn_configure->hide();
    ui->btn_measure->hide();
    ui->btn_standby->hide();
    ui->btn_procedure->hide();
    ui->btn_about->hide();
    ui->btn_air->hide();
    ui->btn_control->hide();
    ui->btn_remote->hide();
    ui->btn_serial->hide();
}

void mainWindow::show_manu()
{
    ui->btn_configure->show();
    ui->btn_measure->show();
    ui->btn_standby->show();
    ui->btn_procedure->show();
    ui->btn_about->show();
    ui->btn_air->show();
    ui->btn_control->show();
    ui->btn_remote->show();
    ui->btn_serial->show();
}

void mainWindow::closeSubConfigureMenu()
{
    ui->btn_configureChan->hide();
    ui->btn_configureSensor->hide();
    ui->btn_configureControl->hide();

}

void mainWindow::showSubConfigureMenu()
{
    ui->btn_configureChan->show();
    ui->btn_configureSensor->show();
    ui->btn_configureControl->show();
    //ui->btn_configureAdjust->show();

}

void mainWindow::showSubRemoteMenu()
{
    ui->btn_remoteMachine->show();
    ui->btn_remoteSerial->show();
    ui->btn_remoteETH->show();

}

void mainWindow::closeSubRemoteMenu()
{
    ui->btn_remoteMachine->hide();
    ui->btn_remoteSerial->hide();
    ui->btn_remoteETH->hide();

}

void mainWindow::showSubControlMenu()
{
    ui->btn_controlstep->show();
    ui->btn_controlsetpoint->show();
    ui->btn_controlrange->show();

}

void mainWindow::closeSubControlMenu()
{
    ui->btn_controlstep->hide();
    ui->btn_controlsetpoint->hide();
    ui->btn_controlrange->hide();

}

void mainWindow::on_btn_manu_clicked()
{
    m32ButtonClickManu++;

    if(m32ButtonClickManu % 2)
        this->show_manu();
    else
    {
        this->close_manu();
        this->closeSubConfigureMenu();
        this->closeSubRemoteMenu();
        this->closeSubControlMenu();
        m32ButtonClickControl &= ~0x01;
        m32ButtonClickRemote &= ~0x01;
        m32ButtonClick &= ~0x01;
    }
}

void mainWindow::on_btn_configure_clicked()
{
    m32ButtonClick++;

    if(m32ButtonClick % 2)
    {
        this->showSubConfigureMenu();

    }
    else
    {
        this->closeSubConfigureMenu();

    }

    this->closeSubControlMenu();
    this->closeSubRemoteMenu();
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClickControl &= ~0x01;
}

void mainWindow::on_btn_standby_clicked()
{
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
}

void mainWindow::on_btn_measure_clicked()
{
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
}

void mainWindow::on_btn_control_clicked()
{
    m32ButtonClickControl++;

    if(m32ButtonClickControl % 2)
    {
        this->showSubControlMenu();
    }
    else
    {
        this->closeSubControlMenu();
    }

    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
}

void mainWindow::on_btn_air_clicked()
{
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
}

void mainWindow::on_btn_remote_clicked()
{
    m32ButtonClickRemote++;

    if(m32ButtonClickRemote % 2)
    {
        this->showSubRemoteMenu();
        this->closeSubConfigureMenu();
    }
    else
    {
        this->closeSubRemoteMenu();

    }

    this->closeSubControlMenu();
    m32ButtonClickControl &= ~0x01;

}

void mainWindow::on_btn_procedure_clicked()
{
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
}

void mainWindow::on_btn_serial_clicked()
{
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    pSerialUI->show();
    pSerialUI->move((QApplication::desktop()->width() - pSerialUI->width())/2,(QApplication::desktop()->height() - pSerialUI->height())/2);
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
}

void mainWindow::on_btn_about_clicked()
{
    pAbout->show();
    pAbout->move((QApplication::desktop()->width() - pAbout->width())/2,(QApplication::desktop()->height() - pAbout->height())/2);
    //::information(this,QString::fromUtf8("关于"),QString::fromUtf8("anything you want tell user\n显示信息\n"));
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;
}

void mainWindow::on_btn_configureChan_clicked()
{
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    pConfigure->show();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;
}

void mainWindow::on_btn_configureSensor_clicked()
{
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    pSensor->show();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;
}

void mainWindow::on_btn_configureControl_clicked()
{
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    pController->show();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;

}

void mainWindow::on_btn_remoteMachine_clicked()
{
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    pMachine->show();
    pMachine->move((QApplication::desktop()->width() - pMachine->width())/2,(QApplication::desktop()->height() - pMachine->height())/2);
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;
}

void mainWindow::on_btn_remoteSerial_clicked()
{
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    pSerialUI->show();
    pSerialUI->move((QApplication::desktop()->width() - pSerialUI->width())/2,(QApplication::desktop()->height() - pSerialUI->height())/2);
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;
}

void mainWindow::on_btn_remoteETH_clicked()
{
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    pRemoteETH->show();
    pRemoteETH->move((QApplication::desktop()->width() - pRemoteETH->width())/2,(QApplication::desktop()->height() - pRemoteETH->height())/2);
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;
}

void mainWindow::on_btn_unitChange_clicked()
{
    pUnit->show();
}

void mainWindow::on_btn_controlstep_clicked()
{
    m32ButtonClickControlStep++;

    if(m32ButtonClickControlStep % 2)
    {
        ui->label_step->show();
        ui->dsb_step->show();
    }
    else
    {
        ui->label_step->hide();
        ui->dsb_step->hide();
    }
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;

}

void mainWindow::on_btn_controlsetpoint_clicked()
{
    m32ButtonClickControlSetPoint++;
    if(m32ButtonClickControlSetPoint % 2)
    {
        ui->label_setpoint->show();
        ui->dsb_setpoint->show();
    }
    else
    {
        ui->label_setpoint->hide();
        ui->dsb_setpoint->hide();
    }
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;

}

void mainWindow::on_btn_controlrange_clicked()
{
    m32ButtonClickControlRange++;
    if(m32ButtonClickControlRange % 2)
    {
        ui->label_range->show();
        ui->dsb_range->show();
    }
    else
    {
        ui->label_range->hide();
        ui->dsb_range->hide();
    }
    this->close_manu();
    this->closeSubConfigureMenu();
    this->closeSubRemoteMenu();
    this->closeSubControlMenu();
    m32ButtonClickControl &= ~0x01;
    m32ButtonClickRemote &= ~0x01;
    m32ButtonClick &= ~0x01;
    m32ButtonClickManu &= ~0x01;
}
