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
    pTimer->setInterval(100);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    pTimer->start();
    beditFlag = false;
    appendInfo = QString("");

    ui->edit_debugInfo->verticalScrollBar()->setStyleSheet("QScrollBar:vertical {"

                                                                   "border:0px solid grey;"

                                                                   "width: 35px;"

                                                                   "}"

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

                                                                   "}");
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