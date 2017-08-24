#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include "commandList.h"
namespace Ui {
class keyBoard;
}

class keyBoard : public QWidget
{
    Q_OBJECT

public:
    explicit keyBoard(QWidget *parent = 0);
    ~keyBoard();

private slots:
    void on_btn_num_1_clicked();

    void on_btn_num_2_clicked();

    void on_btn_num_3_clicked();

    void on_btn_num_4_clicked();

    void on_btn_num_5_clicked();

    void on_btn_num_6_clicked();

    void on_btn_num_7_clicked();

    void on_btn_num_8_clicked();

    void on_btn_num_9_clicked();

    void on_btn_num_Point_clicked();

    void on_btn_num_0_clicked();

    void on_btn_num_clr_clicked();

    void on_btn_num_add_clicked();

    void on_btn_num_sub_clicked();

    void on_btn_num_ok_clicked();

private:
    Ui::keyBoard *ui;

public:
    QString str;
    bool editFlag;
};

#endif // KEYBOARD_H
