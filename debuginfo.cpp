#include "debuginfo.h"
#include "ui_debuginfo.h"
#include <QScrollBar>

debugInfo::debugInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::debugInfo)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);

    pTimer = new QTimer(this);
    pTimer->setInterval(1000);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    //pTimer->start();
    beditFlag = false;
    appendInfo = QString("");

    ui->edit_debugInfo->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"

                                                                   "border:0px solid grey;"

                                                                   "width: 35px;"

                                                                   "}"
#if 0
                                                                   " QScrollBar::handle:vertical {"

                                                                   " background: #8080FF;"

                                                                   " border: 3px solid grey;"

                                                                   " border-radius:5px;"

                                                                   " min-height: 20px;"

                                                                   " }"

                                                                   " QScrollBar::add-line:vertical {"

                                                                   " height: 26px;"

                                                                   " subcontrol-position: bottom;"

                                                                   " }"

                                                                   " QScrollBar::sub-line:vertical {"

                                                                   " height: 26px;"

                                                                   " subcontrol-position: top;"

                                                                   " }"

                                                                   "QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"

                                                                   " background: none;"

                                                               "}"
 #endif

                                                           );

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

debugInfo::~debugInfo()
{
    delete ui;
}

void debugInfo::onTimeOut()
{
    editInfo = ui->edit_debugInfo->toPlainText();
    if(beditFlag)
    {
        editInfo.append("\r\n");
        editInfo.append(appendInfo);
        beditFlag = false;
        ui->edit_debugInfo->setText(editInfo);
        QTextCursor cursor = ui->edit_debugInfo->textCursor();
        cursor.movePosition(QTextCursor::End);
        ui->edit_debugInfo->setTextCursor(cursor);
    }

}

void debugInfo::on_btn_configureMachine_2_clicked()
{
    pTimer->stop();
    this->close();
}

void debugInfo::on_btn_configureMachine_3_clicked()
{
    ui->edit_debugInfo->setText(QString(""));
}
