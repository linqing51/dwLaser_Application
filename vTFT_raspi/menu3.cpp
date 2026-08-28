#include "menu3.h"
#include "ui_menu3.h"
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>
#include "customdoublespinbox.h"
#include <QLabel>
#include <QProcess>

menu3::menu3(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu3)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);



    valueLabel = new QLabel("1", ui->widget);
    valueLabel->setAlignment(Qt::AlignCenter);
    valueLabel->setStyleSheet(R"(
        QLabel {
            color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
            font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
            font-size: 28px;           /* 字体大小 */
        }
    )");
    valueLabel->resize(90,36);
    valueLabel->move(1394,672);
    valueLabel->show();


    valueLabel1 = new QLabel("1", ui->widget);
    valueLabel1->setAlignment(Qt::AlignCenter);
    valueLabel1->setStyleSheet(R"(
        QLabel {
            color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
            font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
            font-size: 28px;           /* 字体大小 */
        }
    )");
    valueLabel1->resize(90,36);
    valueLabel1->move(1394,732);
    valueLabel1->show();


    // 创建数字键盘控件
    keyboard = new NumberKeyboard1(this);
    keyboard->setStyleSheet("QWidget { background-color: rgba(255, 255, 255, 128); }");
    // 设置雪碧图路径（替换为你的实际图片路径）
    keyboard->setKeySprite(":/images/sprite.png");
    keyboard->move(668,333);
    keyboard->hide();

    // 创建数字键盘控件
    keyboard1 = new NumberKeyboard1(this);
    keyboard1->setStyleSheet("QWidget { background-color: rgba(255, 255, 255, 128); }");
    // 设置雪碧图路径（替换为你的实际图片路径）
    keyboard1->setKeySprite(":/images/sprite.png");
    keyboard1->move(668,333);
    keyboard1->hide();

    // 连接ENTER键信号
    QObject::connect(keyboard, &NumberKeyboard1::numberConfirmed, [=](const QString &number) {
        keyboard->hide();
        valueLabel->setText(number);
    });
    // 连接ENTER键信号
    QObject::connect(keyboard1, &NumberKeyboard1::numberConfirmed, [=](const QString &number) {
        keyboard1->hide();
        valueLabel1->setText(number);
    });





    slider1 = new ArcSlider(ui->widget,760+64,760+64);
    slider2 = new ArcSlider(ui->widget,680+64,680+64);
    slider3 = new ArcSlider(ui->widget,600+64,600+64);

    // 配置自定义参数
    slider1->setStartAngle(220);  // 起始角度（上，270°）
    slider1->setEndAngle(36);    // 终止角度（下，90°）
    slider1->setArcWidth(10);    // 弧形宽度
    slider1->setArcColor(Qt::gray); // 背景色
    slider1->setProgressColor(Qt::red); // 进度色
    slider1->setSliderImage(":/images/sprite.png"); // 滑块图片（替换为你的图片路径）
    slider1->setMinValue(0);
    slider1->setMaxValue(100);
    slider1->move(160-32,260-32);
    slider1->setsliderImageVisible(false);
    slider1->setSingleStep(1);

    slider2->setStartAngle(227);  // 起始角度（上，270°）
    slider2->setEndAngle(38);    // 终止角度（下，90°）
    slider2->setArcWidth(10);    // 弧形宽度
    slider2->setArcColor(Qt::gray); // 背景色
    slider2->setProgressColor(Qt::red); // 进度色
    slider2->setSliderImage(":/images/sprite.png"); // 滑块图片（替换为你的图片路径）
    slider2->setMinValue(0);
    slider2->setMaxValue(100);
    slider2->move(206-32,300-32);
    slider2->setsliderImageVisible(false);
    slider2->setSingleStep(1);

    slider3->setStartAngle(238);  // 起始角度（上，270°）
    slider3->setEndAngle(38);    // 终止角度（下，90°）
    slider3->setArcWidth(10);    // 弧形宽度
    slider3->setArcColor(Qt::gray); // 背景色
    slider3->setProgressColor(Qt::red); // 进度色
    slider3->setSliderImage(":/images/sprite.png"); // 滑块图片（替换为你的图片路径）
    slider3->setMinValue(0);
    slider3->setMaxValue(100);
    slider3->move(247-32,340-32);
    slider3->setsliderImageVisible(false);
    slider3->setSingleStep(1);



    customBtn_minus1 = new CustomImageButton(ui->widget,84, 84);
    customBtn_minus1->setLeaveImageRect(QRect(0, 3715, 84, 84));
    customBtn_minus1->setEnterImageRect(QRect(0, 3715, 84, 84));
    customBtn_minus1->setPressImageRect(QRect(220, 3715, 84, 84));
    customBtn_minus1->setReleaseImageRect(QRect(0, 3715, 84, 84));
    connect(customBtn_minus1, &QPushButton::clicked, []() {
        qDebug() << "自定义按钮customBtn_minus1被点击";
    });
    customBtn_minus1->move(470,830);
    customBtn_minus1->lower();
    customBtn_minus1->show();

    customBtn_plus1 = new CustomImageButton(ui->widget,84, 84);
    customBtn_plus1->setLeaveImageRect(QRect(110, 3715, 84, 84));
    customBtn_plus1->setEnterImageRect(QRect(110, 3715, 84, 84));
    customBtn_plus1->setPressImageRect(QRect(330, 3715, 84, 84));
    customBtn_plus1->setReleaseImageRect(QRect(110, 3715, 84, 84));
    connect(customBtn_plus1, &QPushButton::clicked, []() {
        qDebug() << "自定义按钮customBtn_plus1被点击";
    });
    customBtn_plus1->move(580,830);
    customBtn_plus1->lower();
    customBtn_plus1->show();

    // 连接点击信号（可以用默认的clicked信号）
    connect(customBtn_minus1, &QPushButton::clicked, this, [=]() {
         on_Minus_Clicked();
    });
    // 连接点击信号（可以用默认的clicked信号）
    connect(customBtn_plus1, &QPushButton::clicked, this, [=]() {
         on_Plus_Clicked();
    });
//    connect(customBtn_minus1, &QPushButton::clicked, this, &menu3::on_Minus_Clicked);
//    connect(customBtn_plus1, &QPushButton::clicked, this, &menu3::on_Plus_Clicked);

    slider1Label = new QLabel("0.0", ui->widget);
    slider1Label->setAlignment(Qt::AlignRight);
    slider1Label->setStyleSheet(R"(
        QLabel {
            color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
            font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
            font-size: 128px;           /* 字体大小 */
        }
    )");
    slider1Label->resize(280,150);
    slider1Label->move(355,524);
    slider1Label->show();

    slider2Label = new QLabel("0.0", ui->widget);
    slider2Label->setAlignment(Qt::AlignRight);
    slider2Label->setStyleSheet(R"(
        QLabel {
            color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
            font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
            font-size: 128px;           /* 字体大小 */
        }
    )");
    slider2Label->resize(280,150);
    slider2Label->move(355,524);
    slider2Label->hide();


    slider3Label = new QLabel("0.0", ui->widget);
    slider3Label->setAlignment(Qt::AlignRight);
    slider3Label->setStyleSheet(R"(
        QLabel {
            color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
            font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
            font-size: 128px;           /* 字体大小 */
        }
    )");
    slider3Label->resize(280,150);
    slider3Label->move(355,524);
    slider3Label->hide();

    QObject::connect(slider1, &ArcSlider::valueChanged, [=](int value) {
        slider1Label->setText(QString::number(value));
    });

    QObject::connect(slider2, &ArcSlider::valueChanged, [=](int value) {
        slider2Label->setText(QString::number(value));
    });

    QObject::connect(slider3, &ArcSlider::valueChanged, [=](int value) {
        slider3Label->setText(QString::number(value));
    });



    // 创建自定义复选框
   checkBox1470nm = new CustomCheckBox(ui->widget);
   checkBox980nm = new CustomCheckBox(ui->widget);
   checkBox625nm = new CustomCheckBox(ui->widget);
   checkBox1470nm->setFixedSize(150, 150);
   checkBox980nm->setFixedSize(150, 150);
   checkBox625nm->setFixedSize(150, 150);
   // 1. 加载包含四种状态的大图（替换为你的图片路径）
   checkBox1470nm->setBackgroundPixmap(":/images/sprite.png");
   checkBox980nm->setBackgroundPixmap(":/images/sprite.png");
   checkBox625nm->setBackgroundPixmap(":/images/sprite.png");
   // 2. 设置每种状态对应的截图区域（根据你的大图实际坐标调整）
   checkBox1470nm->setStateRect(State_Release_Unchecked, QRect(300, 3000, 150, 150));
   checkBox1470nm->setStateRect(State_Release_Checked, QRect(500, 3000, 150, 150));
   checkBox1470nm->setStateRect(State_Press_Unchecked, QRect(300, 3000, 150, 150));
   checkBox1470nm->setStateRect(State_Press_Checked, QRect(500, 3000, 150, 150));
   checkBox1470nm->setChecked(false);
   checkBox1470nm->move(789,440);

   checkBox980nm->setStateRect(State_Release_Unchecked, QRect(700, 3000, 150, 150));
   checkBox980nm->setStateRect(State_Release_Checked, QRect(900, 3000, 150, 150));
   checkBox980nm->setStateRect(State_Press_Unchecked, QRect(700, 3000, 150, 150));
   checkBox980nm->setStateRect(State_Press_Checked, QRect(900, 3000, 150, 150));
   checkBox980nm->setChecked(false);
   checkBox980nm->move(804,592);

   checkBox625nm->setStateRect(State_Release_Unchecked, QRect(1100, 3000, 150, 150));
   checkBox625nm->setStateRect(State_Release_Checked, QRect(1300, 3000, 150, 150));
   checkBox625nm->setStateRect(State_Press_Unchecked, QRect(1100, 3000, 150, 150));
   checkBox625nm->setStateRect(State_Press_Checked, QRect(1300, 3000, 150, 150));
   checkBox625nm->setChecked(false);
   checkBox625nm->move(767,738);
   // 连接选中状态改变信号
   QObject::connect(checkBox1470nm, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox_1470nm中状态：" << checked;
   });
   QObject::connect(checkBox980nm, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox_980nm中状态：" << checked;
   });
   QObject::connect(checkBox625nm, &CustomCheckBox::checkedChanged, [](bool checked) {
       qDebug() << "复选框选checkBox_625nm中状态：" << checked;
   });

   // 连接点击信号（可以用默认的clicked信号）
   connect(checkBox1470nm, &CustomCheckBox::checkedChanged1, this, [=]() {
        on_checkBox1470nm_clicked();
   });
   // 连接点击信号（可以用默认的clicked信号）
   connect(checkBox980nm, &CustomCheckBox::checkedChanged1, this, [=]() {
        on_checkBox980nm_clicked();
   });
   // 连接点击信号（可以用默认的clicked信号）
   connect(checkBox625nm, &CustomCheckBox::checkedChanged1, this, [=]() {
        on_checkBox625nm_clicked();
   });

//   QObject::connect(checkBox1470nm, &CustomCheckBox::checkedChanged, this, &on_checkBox1470nm_clicked);
//   QObject::connect(checkBox980nm, &CustomCheckBox::checkedChanged, this, &on_checkBox980nm_clicked);
//   QObject::connect(checkBox625nm, &CustomCheckBox::checkedChanged, this, &on_checkBox625nm_clicked);
   checkBox1470nm->raise();
   checkBox980nm->raise();
   checkBox625nm->raise();


   CustomImageButton *customBtn_save = new CustomImageButton(ui->widget,149, 75);
   customBtn_save->setLeaveImageRect(QRect(1900, 3000, 149, 75));
   customBtn_save->setEnterImageRect(QRect(1900, 3000, 149, 75));
   customBtn_save->setPressImageRect(QRect(2100, 3000, 149, 75));
   customBtn_save->setReleaseImageRect(QRect(1900, 3000, 149, 75));
   connect(customBtn_save, &QPushButton::clicked, []() {
       qDebug() << "自定义按钮customBtn_save被点击";
   });
   customBtn_save->move(1516,91);

   CustomImageButton *customBtn_home = new CustomImageButton(ui->widget,149, 75);
   customBtn_home->setLeaveImageRect(QRect(1500, 3000, 149, 75));
   customBtn_home->setEnterImageRect(QRect(1500, 3000, 149, 75));
   customBtn_home->setPressImageRect(QRect(1700, 3000, 149, 75));
   customBtn_home->setReleaseImageRect(QRect(1500, 3000, 149, 75));
   connect(customBtn_home, &QPushButton::clicked, []() {
       qDebug() << "自定义按钮customBtn_home被点击";
   });
   customBtn_home->move(1706,90);


   CustomImageButton *customBtn_cw = new CustomImageButton(ui->widget,188, 73);
   customBtn_cw->setLeaveImageRect(QRect(200, 3200, 188, 73));
   customBtn_cw->setEnterImageRect(QRect(200, 3200, 188, 73));
   customBtn_cw->setPressImageRect(QRect(400, 3200, 188, 73));
   customBtn_cw->setReleaseImageRect(QRect(200, 3200, 188, 73));
   connect(customBtn_cw, &QPushButton::clicked, []() {
       qDebug() << "自定义按钮customBtn_cw被点击";
   });
   customBtn_cw->move(1196,569);

   CustomImageButton *customBtn_plus = new CustomImageButton(ui->widget,188, 73);
   customBtn_plus->setLeaveImageRect(QRect(600, 3200, 188, 73));
   customBtn_plus->setEnterImageRect(QRect(600, 3200, 188, 73));
   customBtn_plus->setPressImageRect(QRect(800, 3200, 188, 73));
   customBtn_plus->setReleaseImageRect(QRect(600, 3200, 188, 73));
   connect(customBtn_plus, &QPushButton::clicked, []() {
       qDebug() << "自定义按钮customBtn_plus被点击";
   });
   customBtn_plus->move(1441,569);

   CustomImageButton *customBtn_ready = new CustomImageButton(ui->widget,287, 105);
   customBtn_ready->setLeaveImageRect(QRect(999, 3200, 287, 105));
   customBtn_ready->setEnterImageRect(QRect(999, 3200, 287, 105));
   customBtn_ready->setPressImageRect(QRect(1300, 3200, 287, 105));
   customBtn_ready->setReleaseImageRect(QRect(999, 3200, 287, 105));
   connect(customBtn_ready, &QPushButton::clicked, []() {
       qDebug() << "自定义按钮customBtn_ready被点击";
   });
   customBtn_ready->move(1273,819);

   // 连接点击信号（可以用默认的clicked信号）
   connect(customBtn_home, &QPushButton::clicked, this, [=]() {
        on_btnToMain_clicked();
   });
//   connect(customBtn_home, &QPushButton::clicked, this, &menu3::on_btnToMain_clicked);



   //    // 加载包含所有状态的大图（替换为你的图片路径）
   //    QPixmap bigImage(":/images/sprite.png");
   //    if (bigImage.isNull()) {
   //        qWarning() << "加载图片失败，请检查路径";
   //        return ;
   //    }

       // 创建自定义控件
   //    CustomDoubleSpinBox *spinBox = new CustomDoubleSpinBox(this,236, 60,"");
       spinBox = new CustomDoubleSpinBox(this,236, 60,"");
       // 设置数值范围和步长
       spinBox->setMinimum(0.0);
       spinBox->setMaximum(100.0);
       spinBox->setSingleStep(1.0);
       spinBox->setValue(0.0);
       spinBox->move(1506,287);




       // 创建进度条
       progressBar = new QProgressBar(ui->widget);
       progressBar->setRange(0, 100);  // 设置进度范围
       progressBar->setValue(0);     // 设置初始进度值
       progressBar->setFixedHeight(14); // 固定进度条高度，方便控制圆角大小
       progressBar->setFixedWidth(650);

       // 核心：设置带圆角的QSS样式
       progressBar->setStyleSheet(R"(
           QProgressBar {
               background-color: #cccccc;    /* 底色：浅灰色 */
               border: none;                 /* 移除默认边框 */
               border-radius: 7px;          /* 圆角值=高度的一半，实现半圆 */
               text-align: center;           /* 文字居中（隐藏后无影响） */
           }

           QProgressBar::chunk {
               background-color: #ff0000;    /* 进程色：红色 */
               border-radius: 7px;          /* 进度块圆角与整体一致 */
           }
       )");

       // 隐藏进度提示文字
       progressBar->setTextVisible(false);
       progressBar->move(1080,366);
       progressBar->show();

    // 连接数值变化信号
    QObject::connect(spinBox, &CustomDoubleSpinBox::valueChanged, [=](double value) {
        progressBar->setValue((int)value);
        qDebug() << "当前数值：" << value;
    });


   // ========== 核心步骤1：安装事件过滤器 ==========
   // 给Form自身安装事件过滤器，监听者是this（Form自己）
   this->installEventFilter(this);
   valueLabel->installEventFilter(this);
   valueLabel1->installEventFilter(this);


}

menu3::~menu3()
{
    delete ui;
}

void menu3::on_checkBox1470nm_clicked()
{
    if (checkBox1470nm->isChecked() == true)
    {
       slider1->setsliderImageVisible(true);
       slider2->setsliderImageVisible(false);
       slider3->setsliderImageVisible(false);
       slider1->raise();
       slider2->lower();
       slider3->lower();
       checkBox1470nm->raise();
       checkBox980nm->raise();
       checkBox625nm->raise();
       checkBox980nm->setChecked(false);
       checkBox625nm->setChecked(false);
       customBtn_minus1->raise();
       customBtn_plus1->raise();
       slider_order = 1;
       slider1Label->show();
       slider2Label->hide();
       slider3Label->hide();
       qDebug() << "2复选框选checkBox_1470nm中状态：";
    }
    else
    {
        customBtn_minus1->lower();
        customBtn_plus1->lower();
        slider1->setsliderImageVisible(false);
        slider_order = 0;
        qDebug() << "3复选框选checkBox_1470nm中状态：" ;
    }
}

void menu3::on_checkBox980nm_clicked()
{
    if (checkBox980nm->isChecked() == true)
    {
       slider1->setsliderImageVisible(false);
       slider2->setsliderImageVisible(true);
       slider3->setsliderImageVisible(false);
       slider1->lower();
       slider2->raise();
       slider3->lower();
       checkBox1470nm->raise();
       checkBox980nm->raise();
       checkBox625nm->raise();
       checkBox1470nm->setChecked(false);
       checkBox625nm->setChecked(false);
       customBtn_minus1->raise();
       customBtn_plus1->raise();
       slider_order = 2;
       slider1Label->hide();
       slider2Label->show();
       slider3Label->hide();
       qDebug() << "2复选框选checkBox_980nm中状态：";
    }
    else
    {
        customBtn_minus1->lower();
        customBtn_plus1->lower();
        slider2->setsliderImageVisible(false);
        slider_order = 0;
        qDebug() << "3复选框选checkBox_980nm中状态：" ;
    }
}

void menu3::on_checkBox625nm_clicked()
{
    if (checkBox625nm->isChecked() == true)
    {
       slider1->setsliderImageVisible(false);
       slider2->setsliderImageVisible(false);
       slider3->setsliderImageVisible(true);
       slider1->lower();
       slider2->lower();
       slider3->raise();
       checkBox1470nm->raise();
       checkBox980nm->raise();
       checkBox625nm->raise();
       checkBox1470nm->setChecked(false);
       checkBox980nm->setChecked(false);
       customBtn_minus1->raise();
       customBtn_plus1->raise();
       slider_order = 3;
       slider1Label->hide();
       slider2Label->hide();
       slider3Label->show();
       qDebug() << "2复选框选checkBox_625nm中状态：" ;
    }
    else
    {
        customBtn_minus1->lower();
        customBtn_plus1->lower();
        slider3->setsliderImageVisible(false);
        slider_order = 0;
        qDebug() << "3复选框选checkBox_625nm中状态：" ;
    }
}

void menu3::showmenu()
{
    this->show();
}

void menu3::on_btnToMain_clicked()
{
    this->hide();
    emit switchToMain();
}



//void menu3::on_labelTokeyboard_clicked()
//{
//    keyboard->show();
//}


void menu3::on_Minus_Clicked()
{
    switch (slider_order) {
    case 1:
        if (slider1->value() > slider1->singleStep())
            slider1->setValue(slider1->value() - slider1->singleStep());
        break;
    case 2:
        if (slider2->value() > slider2->singleStep())
            slider2->setValue(slider2->value() - slider2->singleStep());
        break;
    case 3:
        if (slider3->value() > slider3->singleStep())
            slider3->setValue(slider3->value() - slider3->singleStep());
        break;
    default:
        break;
    }
}


void menu3::on_Plus_Clicked()
{
    switch (slider_order) {
    case 1:
        if (slider1->value() <  (slider1->maxValue() - slider1->singleStep()))
            slider1->setValue(slider1->value() + slider1->singleStep());
        break;
    case 2:
        if (slider2->value() <  (slider2->maxValue() - slider2->singleStep()))
            slider2->setValue(slider2->value() + slider2->singleStep());
        break;
    case 3:
        if (slider3->value() <  (slider3->maxValue() - slider3->singleStep()))
            slider3->setValue(slider3->value() + slider3->singleStep());
        break;
    default:
        break;
    }
}



// ========== 核心步骤2：实现事件过滤器逻辑 ==========
bool menu3::eventFilter(QObject *watched, QEvent *event)
{
    // 1. 判断被监听的对象（watched）
    if (watched == this) { // 监听的是Form自身
        // 2. 判断事件类型
        switch (event->type()) {
        case QEvent::MouseButtonPress: { // 鼠标按下事件
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            qDebug() << "Form被鼠标按下，位置：" << mouseEvent->pos();
            // 如果返回true，事件会被拦截，不会继续传递
            // return true;
            break;
        }
        case QEvent::KeyPress: { // 键盘按下事件
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            qDebug() << "Form按下了按键：" << keyEvent->key();
            break;
        }
        // 可以添加更多事件类型（如QEvent::Resize、QEvent::Paint等）
        default:
            break;
        }
    }
    if (watched == valueLabel) { // 监听的是valueLabel自身
        // 2. 判断事件类型
        switch (event->type()) {
        case QEvent::MouseButtonPress: { // 鼠标按下事件
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            qDebug() << "Form被鼠标按下，位置：" << mouseEvent->pos();
            if (keyboard->isHidden())
            {
                keyboard->clearInput();
                keyboard->show();
            }else
            {
                keyboard->clearInput();
                keyboard->hide();
            };
            // 如果返回true，事件会被拦截，不会继续传递
            // return true;
            break;
        }

        // 可以添加更多事件类型（如QEvent::Resize、QEvent::Paint等）
        default:
            break;
        }
    }
    if (watched == valueLabel1) { // 监听的是valueLabel自身
        // 2. 判断事件类型
        switch (event->type()) {
        case QEvent::MouseButtonPress: { // 鼠标按下事件
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            qDebug() << "Form被鼠标按下，位置：" << mouseEvent->pos();
            if (keyboard1->isHidden())
            {
                keyboard1->clearInput();
                keyboard1->show();
            }else
            {
                keyboard1->clearInput();
                keyboard1->hide();
            };
            // 如果返回true，事件会被拦截，不会继续传递
            // return true;
            break;
        }

        // 可以添加更多事件类型（如QEvent::Resize、QEvent::Paint等）
        default:
            break;
        }
    }

    // 【重要】返回false表示不拦截事件，让事件继续传递；
    // 如果需要拦截特定事件，在对应分支return true即可
    return QWidget::eventFilter(watched, event);
}





