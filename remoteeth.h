#ifndef REMOTEETH_H
#define REMOTEETH_H

#include <QWidget>
#include "keyboard.h"
#include "qtimer.h"
#include "commandList.h"
namespace Ui {
class RemoteEth;
}

class RemoteEth : public QWidget
{
    Q_OBJECT

public:
    explicit RemoteEth(QWidget *parent = 0);
    ~RemoteEth();

private slots:
    void on_ok_clicked();

    void on_btn_IP_clicked();

    void on_btn_netmask_clicked();

    void on_btn_gateway_clicked();

    void on_btn_netport_clicked();

    void onTimeOut();

    void on_btn_configureMachine_2_clicked();

private:
    Ui::RemoteEth *ui;

public:
    keyBoard *pKeyBoard;
    QTimer *pTimer;

    bool bIPFlag;
    bool bNetMaskFlag;
    bool bGateWayFlag;
    bool bNetPortFlag;
};

#endif // REMOTEETH_H
