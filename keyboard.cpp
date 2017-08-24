#include "keyboard.h"
#include "ui_keyboard.h"

keyBoard::keyBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::keyBoard)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    str = QString("");
    editFlag = false;
}

keyBoard::~keyBoard()
{
    delete ui;
}

void keyBoard::on_btn_num_1_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"1");
}

void keyBoard::on_btn_num_2_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"2");
}

void keyBoard::on_btn_num_3_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"3");
}

void keyBoard::on_btn_num_4_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"4");
}

void keyBoard::on_btn_num_5_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"5");
}

void keyBoard::on_btn_num_6_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"6");
}

void keyBoard::on_btn_num_7_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"7");
}

void keyBoard::on_btn_num_8_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"8");
}

void keyBoard::on_btn_num_9_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"9");
}

void keyBoard::on_btn_num_Point_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),".");
}

void keyBoard::on_btn_num_0_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"0");
}

void keyBoard::on_btn_num_clr_clicked()
{
    str = QString("");
}

void keyBoard::on_btn_num_add_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"+");
}

void keyBoard::on_btn_num_sub_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"-");
}

void keyBoard::on_btn_num_ok_clicked()
{
    this->editFlag = false;
    this->close();
}
