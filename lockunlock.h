#ifndef LOCKUNLOCK_H
#define LOCKUNLOCK_H

#include <QWidget>
#include "keyboard.h"
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
    bool eventFilter(QObject *,QEvent *);

    void on_btn_unlock_clicked();

    void onTimeOut();

private:
    Ui::lockUnLock *ui;

public:
    keyBoard *pKeyBoard;
    QTimer * pTimer;

    bool bunlockEditFlag;
    bool bchangeEditFlag;
};

#endif // LOCKUNLOCK_H
