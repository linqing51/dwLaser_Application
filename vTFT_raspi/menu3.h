#ifndef MENU3_H
#define MENU3_H

#include <QWidget>
#include "arcslider.h"
#include "customcheckbox.h"
#include "customimagebutton.h"
#include <QLabel>
#include <QProgressBar>
#include "numberkeyboard1.h"
#include <QMouseEvent>
#include "customdoublespinbox.h"

namespace Ui {
class menu3;
}

class menu3 : public QWidget
{
    Q_OBJECT

public:
    explicit menu3(QWidget *parent = 0);
    ~menu3();
    // 声明事件过滤器函数（必须是protected或public，返回bool，参数为QObject*和QEvent*）
    bool eventFilter(QObject *watched, QEvent *event) override;
public slots:
//    void on_checkBox1470nm_clicked();
//    void on_checkBox980nm_clicked();
//    void on_checkBox625nm_clicked();
    void showmenu();
//    void on_labelTokeyboard_clicked();
private:
    Ui::menu3 *ui;
    ArcSlider *slider1;
    ArcSlider *slider2;
    ArcSlider *slider3;
    CustomCheckBox *checkBox1470nm;
    CustomCheckBox *checkBox980nm;
    CustomCheckBox *checkBox625nm;
    CustomImageButton *customBtn_minus1;
    CustomImageButton *customBtn_plus1;
    QLabel *valueLabel;
    QLabel *valueLabel1;
    QLabel *slider1Label;
    QLabel *slider2Label;
    QLabel *slider3Label;
    NumberKeyboard1 *keyboard;
    NumberKeyboard1 *keyboard1;
    CustomDoubleSpinBox *spinBox;
    QProgressBar *progressBar;
    int slider_order = 0;
    void on_btnToMain_clicked();
    void on_Minus_Clicked();
    void on_Plus_Clicked();
    void on_checkBox1470nm_clicked();
    void on_checkBox980nm_clicked();
    void on_checkBox625nm_clicked();
private slots:
//    void on_btnToMain_clicked();
//    void on_Minus_Clicked();
//    void on_Plus_Clicked();
signals:
    void switchToMain();  // 切换到主窗口
    void switchToQLabel();

};

#endif // MENU3_H
