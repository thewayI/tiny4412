#ifndef CHANNELTEST_H
#define CHANNELTEST_H

#include <QWidget>
#include <QTimer>
#include "keyboard.h"
#include "commandList.h"
#include "posix_qextserialport.h"


namespace Ui {
class channelTest;
}

class channelTest : public QWidget
{
    Q_OBJECT

public:
    explicit channelTest(QWidget *parent = 0, Posix_QextSerialPort *serial = NULL);
    ~channelTest();

private slots:
    void on_pushButton_clicked();

    void onTimeout();

    void on_pushButton_4_clicked();

private:
    Ui::channelTest *ui;

public:
    keyBoard *pKeyBoard;
    QTimer *pTimer;
    Posix_QextSerialPort *pSerial;

    bool bEditFlag;
};

#endif // CHANNELTEST_H
