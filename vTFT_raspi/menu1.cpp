#include "menu1.h"
#include "ui_menu1.h"
#include "customcheckbox.h"
#include "customimagebutton.h"
#include <QDebug>

menu1::menu1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu1)
{
    ui->setupUi(this);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);

    // 创建自定义按钮
    CustomImageButton *customBtn_ok = new CustomImageButton(ui->widget,149, 78);
    customBtn_ok->setLeaveImageRect(QRect(400, 2300, 149, 78));
    customBtn_ok->setEnterImageRect(QRect(400, 2300, 149, 78));
    customBtn_ok->setPressImageRect(QRect(600, 2300, 149, 78));
    customBtn_ok->setReleaseImageRect(QRect(400, 2300, 149, 78));
    connect(customBtn_ok, &QPushButton::clicked, []() {
        qDebug() << "自定义按钮customBtn_ok被点击";
    });
    customBtn_ok->move(1702,90);

    CustomImageButton *customBtn_return = new CustomImageButton(ui->widget,149, 78);
    customBtn_return->setLeaveImageRect(QRect(0, 2300, 149, 78));
    customBtn_return->setEnterImageRect(QRect(000, 2300, 149, 78));
    customBtn_return->setPressImageRect(QRect(200, 2300, 149, 78));
    customBtn_return->setReleaseImageRect(QRect(0, 2300, 149, 78));
    connect(customBtn_return, &QPushButton::clicked, []() {
        qDebug() << "自定义按钮customBtn_return被点击";
    });
    customBtn_return->move(1516,91);

    // 创建自定义复选框
   CustomCheckBox *checkBox1 = new CustomCheckBox(ui->widget);
   CustomCheckBox *checkBox2 = new CustomCheckBox(ui->widget);
   CustomCheckBox *checkBox3 = new CustomCheckBox(ui->widget);
   CustomCheckBox *checkBox4 = new CustomCheckBox(ui->widget);
   CustomCheckBox *checkBox5 = new CustomCheckBox(ui->widget);
   CustomCheckBox *checkBox6 = new CustomCheckBox(ui->widget);
   CustomCheckBox *checkBox7 = new CustomCheckBox(ui->widget);
   CustomCheckBox *checkBox8 = new CustomCheckBox(ui->widget);
   CustomCheckBox *checkBox9 = new CustomCheckBox(ui->widget);
   CustomCheckBox *checkBox10 = new CustomCheckBox(ui->widget);
   // 设置大小（建议和图片区域大小一致）
   checkBox1->setFixedSize(339, 339);
   checkBox2->setFixedSize(339, 339);
   checkBox3->setFixedSize(339, 339);
   checkBox4->setFixedSize(339, 339);
   checkBox5->setFixedSize(339, 339);
   checkBox6->setFixedSize(339, 339);
   checkBox7->setFixedSize(339, 339);
   checkBox8->setFixedSize(339, 339);
   checkBox9->setFixedSize(339, 339);
   checkBox10->setFixedSize(339, 339);

   // 1. 加载包含四种状态的大图（替换为你的图片路径）
   checkBox1->setBackgroundPixmap(":/images/sprite.png");
   checkBox2->setBackgroundPixmap(":/images/sprite.png");
   checkBox3->setBackgroundPixmap(":/images/sprite.png");
   checkBox4->setBackgroundPixmap(":/images/sprite.png");
   checkBox5->setBackgroundPixmap(":/images/sprite.png");
   checkBox6->setBackgroundPixmap(":/images/sprite.png");
   checkBox7->setBackgroundPixmap(":/images/sprite.png");
   checkBox8->setBackgroundPixmap(":/images/sprite.png");
   checkBox9->setBackgroundPixmap(":/images/sprite.png");
   checkBox10->setBackgroundPixmap(":/images/sprite.png");

   // 2. 设置每种状态对应的截图区域（根据你的大图实际坐标调整）
   checkBox1->setStateRect(State_Release_Unchecked, QRect(0, 300, 339, 339));
   checkBox1->setStateRect(State_Release_Checked, QRect(800, 300, 339, 339));
   checkBox1->setStateRect(State_Press_Unchecked, QRect(0, 300, 339, 339));
   checkBox1->setStateRect(State_Press_Checked, QRect(800, 300, 339, 339));
   checkBox1->move(71,271);

   checkBox2->setStateRect(State_Release_Unchecked, QRect(1200, 300, 339, 339));
   checkBox2->setStateRect(State_Release_Checked, QRect(2000, 300, 339, 339));
   checkBox2->setStateRect(State_Press_Unchecked, QRect(1200, 300, 339, 339));
   checkBox2->setStateRect(State_Press_Checked, QRect(2000, 300, 339, 339));
   checkBox2->move(435,271);

   checkBox3->setStateRect(State_Release_Unchecked, QRect(0, 700, 339, 339));
   checkBox3->setStateRect(State_Release_Checked, QRect(800, 700, 339, 339));
   checkBox3->setStateRect(State_Press_Unchecked, QRect(0, 700, 339, 339));
   checkBox3->setStateRect(State_Press_Checked, QRect(800, 700, 339, 339));
   checkBox3->move(790,271);

   checkBox4->setStateRect(State_Release_Unchecked, QRect(1200, 700, 339, 339));
   checkBox4->setStateRect(State_Release_Checked, QRect(2000, 700, 339, 339));
   checkBox4->setStateRect(State_Press_Unchecked, QRect(1200, 700, 339, 339));
   checkBox4->setStateRect(State_Press_Checked, QRect(2000, 700, 339, 339));
   checkBox4->move(1151,271);

   checkBox5->setStateRect(State_Release_Unchecked, QRect(0, 1100, 339, 339));
   checkBox5->setStateRect(State_Release_Checked, QRect(800, 1100, 339, 339));
   checkBox5->setStateRect(State_Press_Unchecked, QRect(0, 1100, 339, 339));
   checkBox5->setStateRect(State_Press_Checked, QRect(800, 1100, 339, 339));
   checkBox5->move(1510,271);

   checkBox6->setStateRect(State_Release_Unchecked, QRect(1200, 1100, 339, 339));
   checkBox6->setStateRect(State_Release_Checked, QRect(2000, 1100, 339, 339));
   checkBox6->setStateRect(State_Press_Unchecked, QRect(1200, 1100, 339, 339));
   checkBox6->setStateRect(State_Press_Checked, QRect(2000, 1100, 339, 339));
   checkBox6->move(71,631);

   checkBox7->setStateRect(State_Release_Unchecked, QRect(0, 1500, 339, 339));
   checkBox7->setStateRect(State_Release_Checked, QRect(800, 1500, 339, 339));
   checkBox7->setStateRect(State_Press_Unchecked, QRect(0, 1500, 339, 339));
   checkBox7->setStateRect(State_Press_Checked, QRect(800, 1500, 339, 339));
   checkBox7->move(435,631);

   checkBox8->setStateRect(State_Release_Unchecked, QRect(1200, 1500, 339, 339));
   checkBox8->setStateRect(State_Release_Checked, QRect(2000, 1500, 339, 339));
   checkBox8->setStateRect(State_Press_Unchecked, QRect(1200, 1500, 339, 339));
   checkBox8->setStateRect(State_Press_Checked, QRect(2000, 1500, 339, 339));
   checkBox8->move(790,631);

   checkBox9->setStateRect(State_Release_Unchecked, QRect(0, 1900, 339, 339));
   checkBox9->setStateRect(State_Release_Checked, QRect(800, 1900, 339, 339));
   checkBox9->setStateRect(State_Press_Unchecked, QRect(0, 1900, 339, 339));
   checkBox9->setStateRect(State_Press_Checked, QRect(800, 1900, 339, 339));
   checkBox9->move(1151,631);

   checkBox10->setStateRect(State_Release_Unchecked, QRect(1200, 1900, 339, 339));
   checkBox10->setStateRect(State_Release_Checked, QRect(2000, 1900, 339, 339));
   checkBox10->setStateRect(State_Press_Unchecked, QRect(1200, 1900, 339, 339));
   checkBox10->setStateRect(State_Press_Checked, QRect(2000, 1900, 339, 339));
   checkBox10->move(1510,631);




   // 连接选中状态改变信号
   QObject::connect(checkBox1, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox1中状态：" << checked;
   });
   QObject::connect(checkBox2, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox2中状态：" << checked;
   });
   QObject::connect(checkBox3, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox3中状态：" << checked;
   });
   QObject::connect(checkBox4, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox4中状态：" << checked;
   });
   QObject::connect(checkBox5, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox5中状态：" << checked;
   });
   QObject::connect(checkBox6, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox6中状态：" << checked;
   });
   QObject::connect(checkBox7, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox7中状态：" << checked;
   });
   QObject::connect(checkBox8, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox8中状态：" << checked;
   });
   QObject::connect(checkBox9, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox9中状态：" << checked;
   });
   QObject::connect(checkBox10, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox10中状态：" << checked;
   });

   // 连接点击信号（可以用默认的clicked信号）
   connect(customBtn_return, &QPushButton::clicked, this, [=]() {
        on_btnToMain_clicked();
   });
   //connect(customBtn_return, &QPushButton::clicked, this, &menu1::on_btnToMain_clicked);


}

menu1::~menu1()
{
    delete ui;
}

void menu1::on_btnToMain_clicked()
{
    this->hide();
    emit switchToMain();
}


void menu1::showmenu()
{
    this->show();
}


