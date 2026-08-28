#include "menu2.h"
#include "ui_menu2.h"
#include <QLabel>
#include <QVBoxLayout>
#include "numberkeyboard.h"

menu2::menu2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::menu2)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);


    // 创建数字键盘控件
    keyboard = new NumberKeyboard(ui->widget);
    // 设置雪碧图路径（替换为你的实际图片路径）
    keyboard->setKeySprite(":/images/sprite.png");


    // 连接ENTER键信号
    QObject::connect(keyboard, &NumberKeyboard::numberConfirmed, [=](const QString &number) {
        this->hide();
        emit switchToMain();
    });

}

menu2::~menu2()
{
    delete ui;
}

void menu2::showmenu()
{
    this->keyboard->clearInput();
    this->keyboard->show();
    this->show();
}
