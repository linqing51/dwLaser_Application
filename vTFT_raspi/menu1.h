#ifndef MENU1_H
#define MENU1_H

#include <QWidget>

namespace Ui {
class menu1;
}

class menu1 : public QWidget
{
    Q_OBJECT

public:
    explicit menu1(QWidget *parent = 0);
    ~menu1();
signals:
    void switchToMain();  // 切换到主窗口

private:
    Ui::menu1 *ui;
    void on_btnToMain_clicked();
public slots:
    void showmenu();
private slots:
//    void on_btnToMain_clicked();
};

#endif // MENU1_H
