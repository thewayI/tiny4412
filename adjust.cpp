#include "adjust.h"
#include "ui_adjust.h"

adjust::adjust(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::adjust)
{
    ui->setupUi(this);
    pSerial = serial;
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    ui->tblwidget_adjustTitle->setItem(0,0,new QTableWidgetItem(QString::fromUtf8("校准日期表")));
    ui->tblwidget_adjustItem->setItem(0,0,new QTableWidgetItem(QString::fromUtf8("序列号")));
    ui->tblwidget_adjustItem->setItem(0,1,new QTableWidgetItem(QString::fromUtf8("612095")));
    ui->tblwidget_adjustItem->setItem(1,0,new QTableWidgetItem(QString::fromUtf8("DOC")));
    ui->tblwidget_adjustItem->setItem(1,1,new QTableWidgetItem(QString::fromUtf8("2012-09-17")));
    ui->tblwidget_adjustItem->setItem(2,0,new QTableWidgetItem(QString::fromUtf8("零点")));
    ui->tblwidget_adjustItem->setItem(2,1,new QTableWidgetItem(QString::fromUtf8("0.000")));
    ui->tblwidget_adjustItem->setItem(3,0,new QTableWidgetItem(QString::fromUtf8("满量程")));
    ui->tblwidget_adjustItem->setItem(3,1,new QTableWidgetItem(QString::fromUtf8("1.000000")));
    ui->tblwidget_adjustItem->setItem(4,0,new QTableWidgetItem(QString::fromUtf8("高程修正")));
    ui->tblwidget_adjustItem->setItem(4,1,new QTableWidgetItem(QString::fromUtf8("1.000000")));

    ui->tblwidget_adjustTitle->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(0,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(0,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(1,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(2,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(2,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(3,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(3,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(4,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    ui->tblwidget_adjustItem->item(4,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    ui->btn_adjustOk->hide();
    ui->cmb_adjust->hide();

    pSimple = new SimpleAdjust;
    pLogin  = new login;
    pTimer2 = new QTimer(this);
    pTimer2->setInterval(100);
    connect(pTimer2, SIGNAL(timeout()), this, SLOT(onTimeOut()));

    pTimer2->start();

    ui->btn_num_0->hide();
    ui->btn_num_1->hide();
    ui->btn_num_2->hide();
    ui->btn_num_3->hide();
    ui->btn_num_4->hide();
    ui->btn_num_5->hide();
    ui->btn_num_6->hide();
    ui->btn_num_7->hide();
    ui->btn_num_8->hide();
    ui->btn_num_9->hide();
    ui->btn_num_10->hide();
    ui->btn_num_Point->hide();
    ui->btn_num_add->hide();
    ui->btn_num_sub->hide();
    ui->btn_num_clr->hide();

    str = QString("");
    btime = false;
    badjust = false;
}

adjust::~adjust()
{
    delete ui;
}

void adjust::on_btn_adjustMeasure_clicked()
{

}

void adjust::onTimeOut()
{
    switch(ui->cmb_adjust->currentIndex())
    {
    case 3:
        if(btime)
        {
            ui->tblwidget_adjustItem->setItem(1,1,new QTableWidgetItem(str));
            ui->tblwidget_adjustItem->item(1,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
        break;
    case 4:
        if(badjust)
        {
            ui->tblwidget_adjustItem->setItem(4,1,new QTableWidgetItem(str));
            ui->tblwidget_adjustItem->item(4,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
        break;
    default:
        break;
    }
}

void adjust::on_btn_adjustclose_clicked()
{
    ui->tblwidget_adjustLock_2->setStyleSheet("border-image: url(:/new/prefix1/image/lock.png)");
    ui->btn_adjustOk->hide();
    ui->cmb_adjust->hide();
    this->close();
}

void adjust::on_btn_adjustUnlock_clicked()
{
    ui->tblwidget_adjustLock_2->setStyleSheet("border-image: url(:/new/prefix1/image/unlock.png)");
    ui->btn_adjustOk->show();
    ui->cmb_adjust->show();

    pLogin->show();
    pLogin->move((QApplication::desktop()->width() - pLogin->width())/2,(QApplication::desktop()->height() - pLogin->height())/2);
}

void adjust::on_btn_adjustOk_clicked()
{
    switch(ui->cmb_adjust->currentIndex())
    {
    case 0:
        pSimple->show();
        pSimple->move((QApplication::desktop()->width() - pSimple->width())/2,(QApplication::desktop()->height() - pSimple->height())/2);
        break;
    case 1:
    case 2:
        break;
    case 3:
        this->btn_show();
        btime = true;
        break;
    case 4:
        badjust = true;
        this->btn_show();
        break;
    case 5:
    default:
        break;
    }
}

void adjust::btn_show()
{
    ui->btn_num_0->show();
    ui->btn_num_1->show();
    ui->btn_num_2->show();
    ui->btn_num_3->show();
    ui->btn_num_4->show();
    ui->btn_num_5->show();
    ui->btn_num_6->show();
    ui->btn_num_7->show();
    ui->btn_num_8->show();
    ui->btn_num_9->show();
    ui->btn_num_10->show();
    ui->btn_num_Point->show();
    ui->btn_num_add->show();
    ui->btn_num_sub->show();
    ui->btn_num_clr->show();

    ui->btn_adjustOk->hide();
    ui->cmb_adjust->hide();
}

void adjust::btn_close()
{
    ui->btn_num_0->hide();
    ui->btn_num_1->hide();
    ui->btn_num_2->hide();
    ui->btn_num_3->hide();
    ui->btn_num_4->hide();
    ui->btn_num_5->hide();
    ui->btn_num_6->hide();
    ui->btn_num_7->hide();
    ui->btn_num_8->hide();
    ui->btn_num_9->hide();
    ui->btn_num_10->hide();
    ui->btn_num_Point->hide();
    ui->btn_num_add->hide();
    ui->btn_num_sub->hide();
    ui->btn_num_clr->hide();

    ui->btn_adjustOk->show();
    ui->cmb_adjust->show();
}

void adjust::on_btn_num_1_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"1");
}

void adjust::on_btn_num_2_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"2");
}

void adjust::on_btn_num_3_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"3");
}

void adjust::on_btn_num_4_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"4");
}

void adjust::on_btn_num_5_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"5");
}

void adjust::on_btn_num_6_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"6");
}

void adjust::on_btn_num_7_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"7");
}

void adjust::on_btn_num_8_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"8");
}

void adjust::on_btn_num_9_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"9");
}

void adjust::on_btn_num_Point_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),".");
}

void adjust::on_btn_num_0_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"0");
}

void adjust::on_btn_num_sub_clicked()
{
    str.sprintf("%s%s",str.toLatin1().data(),"-");
}

void adjust::on_btn_num_clr_clicked()
{
    str = QString("");
}

void adjust::on_btn_num_10_clicked()
{
    str = QString("");
    this->btn_close();
    badjust = false;
    btime = false;
}
