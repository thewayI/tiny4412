#ifndef LOCKUNLOCK_H
#define LOCKUNLOCK_H

#include <QWidget>
#include "keyboard.h"
#include <QSettings>
#include <QTimer>

namespace Ui {
class lockUnLock;
}

class lockUnLock : public QWidget
{
    Q_OBJECT

public:
    explicit lockUnLock(QWidget *parent = 0);
    ~lockUnLock();

private slots:

    void on_btn_unlock_clicked();

    void onTimeOut();

    void on_btn_configureMachine_2_clicked();

    void on_btn_unlock_2_clicked();

    void on_btn_change_2_clicked();

    void on_btn_change_clicked();

private:
    Ui::lockUnLock *ui;

public:
    keyBoard *pKeyBoard;
    QTimer * pTimer;

    QString m_QStringPasswd;
    QString m_QStringChange;
    bool bunlockEditFlag;
    bool bchangeEditFlag;
    bool bclickFlag;
    bool bLockFlag;
};

#endif // LOCKUNLOCK_H
