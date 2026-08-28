#ifndef MENU2_H
#define MENU2_H

#include <QWidget>
#include "numberkeyboard.h"

namespace Ui {
class menu2;
}

class menu2 : public QWidget
{
    Q_OBJECT

public:
    explicit menu2(QWidget *parent = 0);
    ~menu2();
signals:
    void switchToMain();  // 切换到主窗口

private:
    Ui::menu2 *ui;
    NumberKeyboard *keyboard;
public slots:
    void showmenu();
};

#endif // MENU2_H
