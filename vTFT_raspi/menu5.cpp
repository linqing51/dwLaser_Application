#include "menu5.h"
#include "ui_menu5.h"
#include <QMouseEvent>
#include <QDebug>
#include "customdoublespinbox.h"

menu5::menu5(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu5)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);


    CustomImageButton *customBtn_ready = new CustomImageButton(this,287, 105);
    customBtn_ready->setLeaveImageRect(QRect(999, 3200, 287, 105));
    customBtn_ready->setEnterImageRect(QRect(999, 3200, 287, 105));
    customBtn_ready->setPressImageRect(QRect(1300, 3200, 287, 105));
    customBtn_ready->setReleaseImageRect(QRect(999, 3200, 287, 105));
    connect(customBtn_ready, &QPushButton::clicked, []() {
        qDebug() << "自定义按钮customBtn_ready被点击";
    });
    customBtn_ready->move(1273,819);

    // 连接点击信号（可以用默认的clicked信号）
    connect(customBtn_ready, &QPushButton::clicked, this, [=]() {
         on_btnToMain_clicked();
    });
//    connect(customBtn_ready, &QPushButton::clicked, this, &menu5::on_btnToMain_clicked);

    // 加载包含所有状态的大图（替换为你的图片路径）
    QPixmap bigImage(":/images/sprite.png");
    if (bigImage.isNull()) {
        qWarning() << "加载图片失败，请检查路径";
        return ;
    }

    // 创建自定义控件
//    CustomDoubleSpinBox *spinBox1 = new CustomDoubleSpinBox(ui->widget,bigImage.copy(0,3340,380,70),380, 70,"J");
    CustomDoubleSpinBox *spinBox1 = new CustomDoubleSpinBox(ui->widget,380, 70,"J");
    // 设置数值范围和步长
    spinBox1->setMinimum(0.0);
    spinBox1->setMaximum(50.0);
    spinBox1->setSingleStep(0.1);
    spinBox1->setValue(0.0);
    spinBox1->move(1220,360);

    // 连接数值变化信号
    QObject::connect(spinBox1, &CustomDoubleSpinBox::valueChanged, [](double value) {
        qDebug() << "spinBox1当前数值：" << value;
    });

//    CustomDoubleSpinBox *spinBox2 = new CustomDoubleSpinBox(ui->widget,bigImage.copy(0,3340,380,70),380, 70,"S");
    CustomDoubleSpinBox *spinBox2 = new CustomDoubleSpinBox(ui->widget,380, 70,"S");
    // 设置数值范围和步长
    spinBox2->setMinimum(0.0);
    spinBox2->setMaximum(50.0);
    spinBox2->setSingleStep(0.1);
    spinBox2->setValue(0.0);
    spinBox2->move(1220,600);

    // 连接数值变化信号
    QObject::connect(spinBox2, &CustomDoubleSpinBox::valueChanged, [](double value) {
        qDebug() << "spinBox2当前数值：" << value;
    });








}

menu5::~menu5()
{
    delete ui;
}



void menu5::showmenu()
{
    this->show();
}

void menu5::on_btnToMain_clicked()
{
    this->hide();
    emit switchToMain();
}


