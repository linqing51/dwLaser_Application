#ifndef MENU5_H
#define MENU5_H

#include <QWidget>
#include "customimagebutton.h"

namespace Ui {
class menu5;
}

class menu5 : public QWidget
{
    Q_OBJECT

public:
    explicit menu5(QWidget *parent = 0);
    ~menu5();
public slots:
    void showmenu();
signals:
    void switchToMain();  // 切换到主窗口

private slots:
//    void on_btnToMain_clicked();

private:
    Ui::menu5 *ui;
    void on_btnToMain_clicked();
};

#endif // MENU5_H
