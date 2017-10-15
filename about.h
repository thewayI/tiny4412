#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include "posix_qextserialport.h"
#include "commandList.h"
#include "contoller.h"
#include <QTimer>

namespace Ui {
class about;
}

class about : public QWidget
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~about();

private slots:
    void on_pushButton_clicked();
    void onTimeOut();

    void on_btn_configureMachine_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::about *ui;
public:
    Posix_QextSerialPort *pSerial;

    QTimer *pTimer;

    Contoller *pConfigure;
};

#endif // ABOUT_H
