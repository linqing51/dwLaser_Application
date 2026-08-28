#include "menu4.h"
#include "ui_menu4.h"
#include <QLabel>
#include <QDebug>
#include "customslider.h"
#include "ThreeStateImageLabel.h"

menu4::menu4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu4)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);

    CustomImageButton *customBtn_home = new CustomImageButton(ui->widget,149, 75);
    customBtn_home->setLeaveImageRect(QRect(1500, 3000, 149, 75));
    customBtn_home->setEnterImageRect(QRect(1500, 3000, 149, 75));
    customBtn_home->setPressImageRect(QRect(1700, 3000, 149, 75));
    customBtn_home->setReleaseImageRect(QRect(1500, 3000, 149, 75));
    connect(customBtn_home, &QPushButton::clicked, []() {
        qDebug() << "自定义按钮customBtn_home被点击";
    });
    customBtn_home->move(1706,90);

    // 连接点击信号（可以用默认的clicked信号）
    connect(customBtn_home, &QPushButton::clicked, this, [=]() {
         on_btnToMain_clicked();
    });
    //connect(customBtn_home, &QPushButton::clicked, this, &menu4::on_btnToMain_clicked);

    QLabel *sounds_label = new QLabel("0", this);
    sounds_label->setStyleSheet(R"(
        QLabel {
            color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
            font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
            font-size: 32px;           /* 字体大小 */
        }
    )");
    sounds_label->resize(60,40);
    sounds_label->move(1694,380);
    sounds_label->show();
    sounds_slider = new CustomSlider(this,":/images/sprite.png",1070,60);
    sounds_slider->setCropRect(QRect(1332, 3360, 40, 40)); // 截取区域（x,y,宽,高）
    sounds_slider->setSliderImagePath(":/images/sprite.png");
    // 设置滑块范围和初始值
    sounds_slider->setMinimum(0);
    sounds_slider->setMaximum(100);
    sounds_slider->setValue(0);
    sounds_slider->move(590,367);
    // 关联值变化信号
    QObject::connect(sounds_slider, &CustomSlider::valueChanged, [=](int value) {
        sounds_label->setText(QString("%1").arg(value));
    });
    // 创建自定义三状态图片控件
    ThreeStateImageLabel* sounds_imageLabel = new ThreeStateImageLabel(this);
    // 关键：设置大图路径和各状态截取区域
    // QRect参数：x坐标, y坐标, 宽度, 高度
    // 请根据你的实际大图尺寸和需要截取的区域修改这些数值
    QRect state1Rect(1445, 3357, 50, 50);               // 状态1：截取大图左上角100x100区域
    QRect state2Rect(1545, 3357, 50, 50);               // 状态2：截取大图x=100,y=0的100x100区域
    QRect state3Rect(1645, 3357, 50, 50);               // 状态3：截取大图x=200,y=0的100x100区域
    sounds_imageLabel->setStateImageFromBigImage(":/images/sprite.png", state1Rect, state2Rect, state3Rect);
    sounds_imageLabel->move(490,376);
    sounds_imageLabel->setValue(0);
    sounds_imageLabel->show();
    QObject::connect(sounds_slider, &CustomSlider::valueChanged, [=](int value) {
        sounds_imageLabel->onValueChanged(value);
    });




    QLabel *brightness_label = new QLabel("0", this);
    brightness_label->setStyleSheet(R"(
        QLabel {
            color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
            font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
            font-size: 32px;           /* 字体大小 */
        }
    )");
    brightness_label->resize(60,40);
    brightness_label->move(1694,466);
    brightness_label->show();
    brightness_slider = new CustomSlider(this,":/images/sprite.png",1070,60);
    brightness_slider->setCropRect(QRect(1332, 3360, 40, 40)); // 截取区域（x,y,宽,高）
    brightness_slider->setSliderImagePath(":/images/sprite.png");
    // 设置滑块范围和初始值
    brightness_slider->setMinimum(0);
    brightness_slider->setMaximum(100);
    brightness_slider->setValue(0);
    brightness_slider->move(590,452);
    // 关联值变化信号
    QObject::connect(brightness_slider, &CustomSlider::valueChanged, [=](int value) {
        brightness_label->setText(QString("%1").arg(value));
    });
    // 创建自定义三状态图片控件
    ThreeStateImageLabel* brightness_imageLabel = new ThreeStateImageLabel(this);
    // 关键：设置大图路径和各状态截取区域
    // QRect参数：x坐标, y坐标, 宽度, 高度
    // 请根据你的实际大图尺寸和需要截取的区域修改这些数值
    QRect state4Rect(1445, 3357, 50, 50);               // 状态1：截取大图左上角100x100区域
    QRect state5Rect(1545, 3357, 50, 50);               // 状态2：截取大图x=100,y=0的100x100区域
    QRect state6Rect(1645, 3357, 50, 50);               // 状态3：截取大图x=200,y=0的100x100区域
    brightness_imageLabel->setStateImageFromBigImage(":/images/sprite.png", state4Rect, state5Rect, state6Rect);
    brightness_imageLabel->move(490,460);
    brightness_imageLabel->setValue(0);
    brightness_imageLabel->show();
    QObject::connect(brightness_slider, &CustomSlider::valueChanged, [=](int value) {
        brightness_imageLabel->onValueChanged(value);
    });


    QLabel *aimingbeam_label = new QLabel("0", this);
    aimingbeam_label->setStyleSheet(R"(
        QLabel {
            color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
            font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
            font-size: 32px;           /* 字体大小 */
        }
    )");
    aimingbeam_label->resize(60,40);
    aimingbeam_label->move(1694,552);
    aimingbeam_label->show();
    aimingbeam_slider = new CustomSlider(this,":/images/sprite.png",1070,60);
    aimingbeam_slider->setCropRect(QRect(1332, 3360, 40, 40)); // 截取区域（x,y,宽,高）
    aimingbeam_slider->setSliderImagePath(":/images/sprite.png");
    // 设置滑块范围和初始值
    aimingbeam_slider->setMinimum(0);
    aimingbeam_slider->setMaximum(100);
    aimingbeam_slider->setValue(0);
    aimingbeam_slider->move(590,539);
    // 关联值变化信号
    QObject::connect(aimingbeam_slider, &CustomSlider::valueChanged, [=](int value) {
        aimingbeam_label->setText(QString("%1").arg(value));
    });
    // 创建自定义三状态图片控件
    ThreeStateImageLabel* aimingbeam_imageLabel = new ThreeStateImageLabel(this);
    // 关键：设置大图路径和各状态截取区域
    // QRect参数：x坐标, y坐标, 宽度, 高度
    // 请根据你的实际大图尺寸和需要截取的区域修改这些数值
    QRect state7Rect(1445, 3357, 50, 50);               // 状态1：截取大图左上角100x100区域
    QRect state8Rect(1545, 3357, 50, 50);               // 状态2：截取大图x=100,y=0的100x100区域
    QRect state9Rect(1645, 3357, 50, 50);               // 状态3：截取大图x=200,y=0的100x100区域
    aimingbeam_imageLabel->setStateImageFromBigImage(":/images/sprite.png", state7Rect, state8Rect, state9Rect);
    aimingbeam_imageLabel->move(490,547);
    aimingbeam_imageLabel->setValue(0);
    aimingbeam_imageLabel->show();
    QObject::connect(aimingbeam_slider, &CustomSlider::valueChanged, [=](int value) {
        aimingbeam_imageLabel->onValueChanged(value);
    });





}

menu4::~menu4()
{
    delete ui;
}



void menu4::showmenu()
{
    this->show();
}

void menu4::on_btnToMain_clicked()
{
    this->hide();
    emit switchToMain();
}

