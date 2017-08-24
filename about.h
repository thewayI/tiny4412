#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include "posix_qextserialport.h"
#include "commandList.h"

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

private:
    Ui::about *ui;
public:
    Posix_QextSerialPort *pSerial;
};

#endif // ABOUT_H
