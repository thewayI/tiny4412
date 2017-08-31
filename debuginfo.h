#ifndef DEBUGINFO_H
#define DEBUGINFO_H

#include <QWidget>

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
};

#endif // DEBUGINFO_H
