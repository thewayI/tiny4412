#include "lockunlock.h"
#include "ui_lockunlock.h"

lockUnLock::lockUnLock(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::lockUnLock)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    pKeyBoard = new keyBoard;

    pTimer = new QTimer(this);
    pTimer->setInterval(100);
    connect(pTimer, SIGNAL(timeout()), this, SLOT(onTimeOut()));
    pTimer->start();


    bunlockEditFlag = false;
    bchangeEditFlag = false;
}

lockUnLock::~lockUnLock()
{
    delete ui;
}


void lockUnLock::onTimeOut()
{
#if 0
    if(bunlockEditFlag)
    {
        if(pKeyBoard->editFlag)
        {
            ui->lineEdit_unlock->setText(pKeyBoard->str);
        }
        else
        {
            bunlockEditFlag = false;
        }
    }
    if(bchangeEditFlag)
    {
        if(pKeyBoard->editFlag)
        {
            ui->lineEdit_change->setText(pKeyBoard->str);
        }
        else
        {
            bchangeEditFlag = false;
        }
    }
#endif
}

bool lockUnLock::eventFilter(QObject *watched, QEvent *event)
{
#if 0
     if (watched==ui->lineEdit_unlock)         //首先判断控件(这里指 lineEdit1)
     {
          if (event->type()==QEvent::MouseButtonPress)     //然后再判断控件的具体事件 (这里指获得焦点事件)
          {
               pKeyBoard->show();
               pKeyBoard->move(700, 400);
               pKeyBoard->editFlag = true;
               bunlockEditFlag = true;
                qDebug("enter lineedit1");
          }
          else if (event->type()==QEvent::FocusOut)    // 这里指 lineEdit1 控件的失去焦点事件
          {
              qDebug("exit lineedit1");
          }
     }
     if (watched==ui->lineEdit_change)           //这里来处理 lineEdit2 , 和处理lineEdit1 是一样的
     {
          if (event->type()==QEvent::FocusIn)
         {
              pKeyBoard->show();
              pKeyBoard->move(700, 400);
              pKeyBoard->editFlag = true;
              bchangeEditFlag = true;
              qDebug("enter lineedit2");
          }
         else if (event->type()==QEvent::FocusOut)
         {
qDebug("exit lineedit2");
         }
     }
 return QWidget::eventFilter(watched,event);     // 最后将事件交给上层对话框
#endif
}

void lockUnLock::on_btn_unlock_clicked()
{
    this->close();
}

void lockUnLock::on_btn_configureMachine_2_clicked()
{
    this->close();
}

void lockUnLock::on_btn_unlock_2_clicked()
{

}
