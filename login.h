#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "posix_qextserialport.h"
#include "commandList.h"
namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~login();

private slots:
    bool eventFilter(QObject *obj, QEvent *event);
    void on_btn_ok_clicked();

private:
    Ui::login *ui;

public:
    Posix_QextSerialPort *pSerial;
};

#endif // LOGIN_H
