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
    void on_btn_configureMachine_2_clicked();
    void on_btn_configureMachine_3_clicked();
};

#endif // DEBUGINFO_H
