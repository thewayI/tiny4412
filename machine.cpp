#include "machine.h"
#include "ui_machine.h"

Machine::Machine(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Machine)
{
    ui->setupUi(this);
    ui->label->setText(QString("Emulation\nMode"));
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

Machine::~Machine()
{
    delete ui;
}

void Machine::on_btn_default_clicked()
{
    this->close();
}
