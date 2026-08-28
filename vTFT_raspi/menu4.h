#ifndef MENU4_H
#define MENU4_H

#include <QWidget>
#include "customimagebutton.h"
#include "customslider.h"

namespace Ui {
class menu4;
}

class menu4 : public QWidget
{
    Q_OBJECT

public:
    explicit menu4(QWidget *parent = 0);
    ~menu4();
public slots:
    void showmenu();
signals:
    void switchToMain();  // 切换到主窗口

private slots:
//    void on_btnToMain_clicked();

private:
    Ui::menu4 *ui;
    CustomSlider *sounds_slider;
    CustomSlider *brightness_slider;
    CustomSlider *aimingbeam_slider;
    void on_btnToMain_clicked();
};

#endif // MENU4_H
