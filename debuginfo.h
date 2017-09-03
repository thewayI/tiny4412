#ifndef DEBUGINFO_H
#define DEBUGINFO_H

#include <QWidget>
#include <QTimer>

namespace Ui {
class debugInfo;
}

class debugInfo : public QWidget
{
    Q_OBJECT

public:
    explicit debugInfo(QWidget *parent = 0);
    ~debugInfo();


private:
    Ui::debugInfo *ui;

public:
    QString editInfo;
    QString appendInfo;
    bool    beditFlag;
    QTimer *pTimer;

private slots:
    void onTimeOut();
    void on_pushButton_clicked();
};

#endif // DEBUGINFO_H
