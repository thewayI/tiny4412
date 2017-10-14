#include "lockunlock.h"
#include <QMessageBox>
#include "ui_lockunlock.h"

lockUnLock::lockUnLock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lockUnLock)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    pKeyBoard = new keyBoard;

    pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
    QString lockFlag=configIniWrite->value("/private/lockFlag").toString();

    m_QStringPasswd = QString("");
    if(lockFlag == QString("true"))
    {
        bLockFlag = true;
        bclickFlag = true;
        ui->btn_change->hide();
        ui->btn_change_2->hide();
        ui->btn_unlock->setText(QString::fromUtf8("解锁"));
        ui->btn_unlock->move(800, 350);
        ui->btn_unlock_2->move(380, 350);
    }
    else
    {
        bLockFlag = false;
        bclickFlag = false;
        ui->btn_change->show();
        ui->btn_change_2->show();
        ui->btn_unlock->setText(QString::fromUtf8("锁定"));
        ui->btn_unlock->move(800, 250);
        ui->btn_unlock_2->move(380, 250);
    }

    bunlockEditFlag = false;
    bchangeEditFlag = false;

    switch(g32styleMode)
    {
    case 0:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/1.png);"));
        break;
    case 1:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_01.png);"));
        break;
    case 2:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_02.png);"));
        break;
    case 3:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_03.png);"));
        break;
    case 4:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_04.png);"));
        break;
    case 5:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/bg_05.png);"));
        break;
    default:
        ui->frame->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/image/1.png);"));
        break;
    }
}

lockUnLock::~lockUnLock()
{
    delete ui;
}


void lockUnLock::onTimeOut()
{
    int loop = 0;
    QString strTemp = QString("");
    ui->btn_unlock_2->setText(QString(""));
#if 1
    if(bunlockEditFlag)
    {
        if(pKeyBoard->editFlag)
        {
            m_QStringPasswd = pKeyBoard->str;
            for(loop = 0; loop < pKeyBoard->str.length(); loop++)
            {
                strTemp = ui->btn_unlock_2->text();
                strTemp.append(QString("*"));
                ui->btn_unlock_2->setText(strTemp);
                ui->btn_unlock->setEnabled(false);
                ui->btn_configureMachine_2->setEnabled(false);
            }

        }
        else
        {
            for(loop = 0; loop < m_QStringPasswd.length(); loop++)
            {
                strTemp = ui->btn_unlock_2->text();
                strTemp.append(QString("*"));
                ui->btn_unlock_2->setText(strTemp);
            }
            bunlockEditFlag = false;
            ui->btn_unlock->setEnabled(true);
            ui->btn_configureMachine_2->setEnabled(true);
        }
    }
    else
    {
        strTemp = QString("");
        ui->btn_unlock_2->setText(strTemp);
        for(loop = 0; loop < m_QStringPasswd.length(); loop++)
        {
            strTemp = ui->btn_unlock_2->text();
            strTemp.append(QString("*"));
            ui->btn_unlock_2->setText(strTemp);
        }
    }
    if(bchangeEditFlag)
    {
        if(pKeyBoard->editFlag)
        {
            ui->btn_change_2->setText(pKeyBoard->str);
            ui->btn_change->setEnabled(false);
            ui->btn_configureMachine_2->setEnabled(false);
        }
        else
        {
            ui->btn_change->setEnabled(true);
            bchangeEditFlag = false;
            ui->btn_configureMachine_2->setEnabled(true);
        }
    }
#endif
}


void lockUnLock::on_btn_unlock_clicked()
{
    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
    QString passwd=configIniWrite->value("/private/passwd").toString();

    if(bclickFlag)
    {
        bclickFlag = false;
        if(passwd == m_QStringPasswd)
        {
            bLockFlag = false;
            ui->btn_change->show();
            ui->btn_change_2->show();
            ui->btn_unlock->setText(QString::fromUtf8("锁定"));
            configIniWrite->setValue("/private/lockFlag", "false");
            ui->btn_unlock->move(800, 250);
            ui->btn_unlock_2->move(380, 250);
        }
        else
        {
            QMessageBox::information(NULL, QString::fromUtf8("提示信息"), QString::fromUtf8("密码错误"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }

    }
    else
    {
        bclickFlag = true;

        if(passwd == m_QStringPasswd)
        {
            bLockFlag = true;
            ui->btn_change->hide();
            ui->btn_change_2->hide();
            ui->btn_unlock->setText(QString::fromUtf8("解锁"));
            configIniWrite->setValue("/private/lockFlag", "true");
            ui->btn_unlock->move(800, 350);
            ui->btn_unlock_2->move(380, 350);
        }
        else
        {
            QMessageBox::information(NULL, QString::fromUtf8("提示信息"), QString::fromUtf8("密码错误"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        }
    }
    delete configIniWrite;

}

void lockUnLock::on_btn_configureMachine_2_clicked()
{
    m_QStringPasswd = QString("");
    pTimer->stop();
    this->close();
}

void lockUnLock::on_btn_unlock_2_clicked()
{
    bunlockEditFlag = true;
    bchangeEditFlag = false;
    m_QStringPasswd = QString("");
    pKeyBoard->str = QString("");
    pKeyBoard->editFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(0, 500);
}

void lockUnLock::on_btn_change_2_clicked()
{
    bunlockEditFlag = false;
    bchangeEditFlag = true;
    pKeyBoard->str = QString("");
    pKeyBoard->editFlag = true;
    pKeyBoard->show();
    pKeyBoard->move(0, 500);
}

void lockUnLock::on_btn_change_clicked()
{
    QSettings *configIniWrite = new QSettings("config.ini", QSettings::IniFormat);
    configIniWrite->setValue("/private/passwd", ui->btn_change_2->text());
    delete configIniWrite;
    ui->btn_change_2->setText(QString(""));
}
