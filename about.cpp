#include "about.h"
#include "ui_about.h"
#include "commandList.h"

about::about(QWidget *parent, Posix_QextSerialPort *serial) :
    QWidget(parent),
    ui(new Ui::about)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    ui->label->setText(QString::fromUtf8("Mensor CorPoration\n201  Barnes  Drive\nSam  Marcos,  Texas  78666\nVoice: (800) 984-4200\nFax: (512) 396-1820\nhttp://www.mensor.com\ntech.support@mensor.com\n\nModel : CPC600\n\n序列号: 612095\n软件版本 : 2.70.0\nIEEE-400 版本 : 2.6.3\n"));
    ui->label->setFrameShape (QFrame::Box);
    pSerial = serial;
}

about::~about()
{
    delete ui;
}

void about::on_pushButton_clicked()
{
    this->close();
}
