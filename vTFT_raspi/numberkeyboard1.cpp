#include "numberkeyboard1.h"
#include <QDebug>

NumberKeyboard1::NumberKeyboard1(QWidget *parent)
    : QWidget(parent)
{
    // 设置控件固定大小（根据你的雪碧图调整）
    setFixedSize(585, 614);
    setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground, false);
    setWindowOpacity(0.6);
    // 初始化按键布局
    initKeyLayout();
    // 清空初始输入
    m_inputNumber = "";

    m_originalPixmap.load(":/images/numberkeyboard1.png");
    // 加载失败时提示
    if (m_originalPixmap.isNull()) {
        qWarning() << "Failed to load sprite image:" << ":/images/numberkeyboard1.png";
    };
    clickedKey = nullptr;
    // 刷新绘制
    update();


}

void NumberKeyboard1::setKeySprite(const QString &spritePath)
{
    // 加载雪碧图
    m_spritePixmap.load(spritePath);
    // 加载失败时提示
    if (m_spritePixmap.isNull()) {
        qWarning() << "Failed to load sprite image:" << spritePath;
    }
    // 刷新绘制
    update();
}

void NumberKeyboard1::initKeyLayout()
{
    // *************************
    // 关键：根据你的雪碧图调整以下参数
    // 格式：{控件内显示区域, 雪碧图截取区域, 按键值}
    // *************************
    // 数字键 1-9
    m_keyList << KeyInfo1{{68, 144, 106, 70}, {0, 3610, 106, 70}, "1"};    // 1键
    m_keyList << KeyInfo1{{182, 144, 106, 70}, {114, 3610, 106, 70}, "2"};   // 2键
    m_keyList << KeyInfo1{{298, 144, 106, 70}, {230, 3610, 106, 70}, "3"};  // 3键
    m_keyList << KeyInfo1{{68, 222, 106, 70}, {460, 3610, 106, 70}, "4"};   // 4键
    m_keyList << KeyInfo1{{182, 222, 106, 70}, {574, 3610, 106, 70}, "5"};  // 5键
    m_keyList << KeyInfo1{{298, 222, 106, 70}, {690, 3610, 106, 70}, "6"}; // 6键
    m_keyList << KeyInfo1{{68, 299, 106, 70}, {917, 3610, 106, 70}, "7"};  // 7键
    m_keyList << KeyInfo1{{182, 299, 106, 70}, {1031, 3610, 106, 70}, "8"}; // 8键
    m_keyList << KeyInfo1{{298, 299, 106, 70}, {1147, 3610, 106, 70}, "9"};// 9键

    // 0键、回格键、ENTER键、s键、ms键、us键
    m_keyList << KeyInfo1{{68, 375, 106, 70}, {1377, 3610, 106, 70}, "0"};    // 0键
    m_keyList << KeyInfo1{{182, 375, 106, 70}, {1491, 3610, 106, 70}, "backspace"}; // 回格键
    m_keyList << KeyInfo1{{298, 375, 106, 70}, {1607, 3610, 106, 70}, "back"}; // 回格键
    m_keyList << KeyInfo1{{412, 375, 106, 70}, {1721, 3610, 106, 70}, "enter"};    // ENTER键
    m_keyList << KeyInfo1{{412, 144, 106, 70}, {344, 3610, 106, 70}, "s"};  // s键
    m_keyList << KeyInfo1{{412, 222, 106, 70}, {804, 3610, 106, 70}, "ms"};  // ms键
    m_keyList << KeyInfo1{{412, 299, 106, 70}, {1261, 3610, 106, 70}, "us"};  // us键
    m_keyList << KeyInfo1{{188, 516, 212, 60}, {1837, 3610, 212, 60}, "cancel"};  // cancel键
}

void NumberKeyboard1::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿，让文字更清晰


    if (!m_originalPixmap.isNull()) {
        // 方式1：拉伸裁剪后的图片填满整个控件
        painter.drawPixmap(rect(), m_originalPixmap);

        // 方式2：居中显示裁剪后的图片（保持原尺寸）
        // QPoint centerPos = rect().center() - m_originalPixmap.rect().center();
        // painter.drawPixmap(centerPos, m_originalPixmap);

        // 方式3：平铺裁剪后的图片
        // painter.drawTiledPixmap(rect(), m_originalPixmap);
    }

//    // 如果雪碧图未加载，绘制默认矩形占位
//    if (m_spritePixmap.isNull()) {
//        for (const KeyInfo &key : m_keyList) {
//            painter.drawRect(key.rect);
//            painter.drawText(key.rect, Qt::AlignCenter, key.value);
//        }
//        return;
//    }

    QFont font1;
    font1.setPixelSize(48); // 设置字符高度
    painter.setFont(font1);
    painter.drawText(78, 88, m_inputNumber);

    if (clickedKey) {
        painter.drawPixmap(clickedKey->rect, m_spritePixmap, clickedKey->spriteRect);
    }

}

NumberKeyboard1::KeyInfo1* NumberKeyboard1::getKeyAtPos(const QPoint &pos)
{
    // 遍历按键，判断点击位置是否在按键区域内
    for (KeyInfo1 &key : m_keyList) {
        if (key.rect.contains(pos)) {
            return &key;
        }
    }
    return nullptr;
}

void NumberKeyboard1::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    // 获取点击的按键
    clickedKey = getKeyAtPos(event->pos());
    if (!clickedKey) {
        return;
    };


    // 处理不同按键逻辑
    const QString &keyValue = clickedKey->value;
    qDebug() << clickedKey->value ;
    if (keyValue == "backspace") {
        // 回格键：删除最后一个字符
        if (!m_inputNumber.isEmpty()) {
            m_inputNumber.chop(1);
        }
    } else if (keyValue == "back") {
        qDebug() << "back键按下" ;
        m_inputNumber.clear();
    } else if (keyValue == "s") {
        qDebug() << "s键按下" ;
    } else if (keyValue == "ms") {
        qDebug() << "ms键按下" ;
    } else if (keyValue == "us") {
        qDebug() << "us键按下" ;
    } else if (keyValue == "cancel") {
        this->hide();
        qDebug() << "cancel键按下" ;
    } else if (keyValue == "enter") {
        this->hide();
        qDebug() << "enter键按下" ;
        emit numberConfirmed(m_inputNumber);
        //m_inputNumber.clear();
    } else {
        // 数字键：追加到输入字符串
        m_inputNumber += keyValue;
    }

    if (clickedKey) {
        // 刷新绘制
        update();
    };

    qDebug() << "Current input:" << m_inputNumber;
}


void NumberKeyboard1::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    // 获取点击的按键
    clickedKey = nullptr;
    // 刷新绘制
    update();

}




void NumberKeyboard1::clearInput()
{
    m_inputNumber.clear();
    clickedKey = nullptr;
}
