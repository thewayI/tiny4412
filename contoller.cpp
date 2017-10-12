#include "contoller.h"
#include "ui_contoller.h"

Contoller::Contoller(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::Contoller)
{
    QString strTemp;
    u_int32_t loop = 0;
    ui->setupUi(this);

    pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    //pTimer->start();

    ui->btn_ctrlvariable->hide();

    pSerial = serial;
    pKeyboard = new keyBoard;
    pChanTest = new channelTest(this, pSerial);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    sendSerialCommand(pSerial, CMD_GET_MINIMUM, &strTemp);
    ui->btn_ctrlMAX1->setText(strTemp.right(strTemp.length() - QString("1 R+ ").length()));
    strTemp = QString("");
    sendSerialCommand(pSerial, CMD_GET_MAXIMUM, &strTemp);
    ui->btn_ctrlMAX2->setText(strTemp.right(strTemp.length() - QString("1 R- ").length()));
    strTemp = QString("");
    sendSerialCommand(pSerial, CMD_GET_UNIT_CODE, &strTemp);
    strTemp = strTemp.right(strTemp.length() - QString("1 ").length());
    for(loop = 0; loop < 40; loop++)
    {
        if(strTemp.toInt() == gUnitChange[loop].code)
        {
            ui->btn_ctrlMAX3->setText(gUnitChange[loop].unitInfo);
            break;
        }
    }

    editctrlMax1Flag = false;
    editctrlMax2Flag = false;
    editctrlMax3Flag = false;

    ui->btn_ctrlMAX1->setEnabled(false);
    ui->btn_ctrlMAX2->setEnabled(false);
    ui->btn_ctrlMAX3->setEnabled(false);

    ui->btn_ctrlstab1->setEnabled(false);
    strTemp = QString("");
    sendSerialCommand(pSerial, CMD_GET_FS_ACCURACY, &strTemp);
    ui->btn_ctrlstab1->setText(strTemp.right(strTemp.length() - QString("1 FS ").length()));


    editctrlstab1Flag = false;
    editctrlstab2Flag = false;

    editctrlMAX1_2Flag = false;
    editctrlvariableFlag = false;

    pChanTest->close();
}

Contoller::~Contoller()
{
    delete ui;
}

void Contoller::onTimeOut()
{
    if(ui->comboBox->currentIndex() == 3)
    {
        ui->btn_ctrlvariable->show();
    }
    else
    {
        ui->btn_ctrlvariable->hide();
    }

    if(editctrlMax1Flag)
    {
        if(pKeyboard->editFlag)
        {
            ui->btn_ctrlMAX1->setText(pKeyboard->str);
        }
        else
        {
            editctrlMax1Flag = false;
        }
    }

    if(editctrlMax2Flag)
    {
        if(pKeyboard->editFlag)
        {
            ui->btn_ctrlMAX2->setText(pKeyboard->str);
        }
        else
        {
            editctrlMax2Flag = false;
        }
    }
    if(editctrlMax3Flag)
    {
        if(pKeyboard->editFlag)
        {
            ui->btn_ctrlMAX3->setText(pKeyboard->str);
        }
        else
        {
            editctrlMax3Flag = false;
        }

    }

    if(editctrlstab1Flag)
    {
        if(pKeyboard->editFlag)
        {
            ui->btn_ctrlstab1->setText(pKeyboard->str);
        }
        else
        {
            editctrlstab1Flag = false;
        }
    }
    if(editctrlstab2Flag)
    {
        if(pKeyboard->editFlag)
        {
            ui->btn_ctrlstab2->setText(pKeyboard->str);
        }
        else
        {
            editctrlstab2Flag = false;
        }
    }

    if(editctrlMAX1_2Flag)
    {
        if(pKeyboard->editFlag)
        {
            ui->btn_ctrlMAX1_2->setText(pKeyboard->str);

        }
        else
        {
            editctrlMAX1_2Flag = false;
        }
    }
    if(editctrlvariableFlag)
    {
        if(pKeyboard->editFlag)
        {
            ui->btn_ctrlvariable->setText(pKeyboard->str);
        }
        else
        {
            editctrlvariableFlag = false;
        }
    }

}

void Contoller::on_btn_ctrlvariable_clicked()
{
    pKeyboard->str = QString("");
    editctrlvariableFlag = true;
    pKeyboard->editFlag = true;
    pKeyboard->show();
    pKeyboard->move(800, 240);
}

void Contoller::on_btn_ctrlMAX1_2_clicked()
{
    pKeyboard->str = QString("");
    pKeyboard->editFlag = true;
    editctrlvariableFlag = true;
    pKeyboard->show();
    pKeyboard->move(800, 240);
}

void Contoller::on_btn_ctrlMAX1_clicked()
{
    pKeyboard->str = QString("");
    pKeyboard->editFlag = true;
    editctrlMax1Flag = true;
    pKeyboard->show();
    pKeyboard->move(800, 240);
}

void Contoller::on_btn_ctrlMAX2_clicked()
{
    pKeyboard->str = QString("");
    pKeyboard->editFlag = true;
    editctrlMax2Flag = true;
    pKeyboard->show();
    pKeyboard->move(800, 240);
}

void Contoller::on_btn_ctrlMAX3_clicked()
{
    pKeyboard->str = QString("");
    pKeyboard->editFlag = true;
    editctrlMax3Flag = true;
    pKeyboard->show();
    pKeyboard->move(800, 240);
}

void Contoller::on_btn_ctrlstab1_clicked()
{
    pKeyboard->str = QString("");
    pKeyboard->editFlag = true;
    editctrlstab1Flag = true;
    pKeyboard->show();
    pKeyboard->move(800, 240);
}

void Contoller::on_btn_ctrlstab2_clicked()
{
    pKeyboard->str = QString("");
    pKeyboard->editFlag = true;
    editctrlstab2Flag = true;
    pKeyboard->show();
    pKeyboard->move(800, 240);
}

void Contoller::on_btn_ctrlMAX3_3_clicked()
{
    this->close();
}

void Contoller::on_btn_ctrlMAX3_2_clicked()
{
    pChanTest->show();
}
