#include "login.h"
#include "ui_login.h"

login::login(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    pSerial = serial;
    ui->lineEdit->installEventFilter(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
}

login::~login()
{
    delete ui;
}

//zdren for git test
bool login::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->lineEdit)
    {
        if (event->type()==QEvent::FocusIn)
        {
            //this->close();
        }
    }
    return QWidget::eventFilter(obj,event);
}

void login::on_btn_ok_clicked()
{
    this->close();
}
