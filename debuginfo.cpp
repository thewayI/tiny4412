#include "debuginfo.h"
#include "ui_debuginfo.h"

debugInfo::debugInfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::debugInfo)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

debugInfo::~debugInfo()
{
    delete ui;
}
