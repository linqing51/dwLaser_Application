#include "numberkeyboard.h"
#include <QDebug>

NumberKeyboard::NumberKeyboard(QWidget *parent)
    : QWidget(parent)
{
    // 设置控件固定大小（根据你的雪碧图调整）
    setFixedSize(1920, 1080);
    // 初始化按键布局
    initKeyLayout();
    // 清空初始输入
    m_inputNumber = "";

    m_originalPixmap.load(":/images/numberkeyboard.png");
    // 加载失败时提示
    if (m_originalPixmap.isNull()) {
        qWarning() << "Failed to load sprite image:" << ":/images/numberkeyboard.png";
    };

    // 刷新绘制
    update();


}

void NumberKeyboard::setKeySprite(const QString &spritePath)
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

void NumberKeyboard::initKeyLayout()
{
    // *************************
    // 关键：根据你的雪碧图调整以下参数
    // 格式：{控件内显示区域, 雪碧图截取区域, 按键值}
    // *************************
    // 数字键 1-9
    m_keyList << KeyInfo{{771, 332, 101, 100}, {110, 0, 101, 100}, "1"};    // 1键
    m_keyList << KeyInfo{{908, 332, 101, 100}, {330, 0, 101, 100}, "2"};   // 2键
    m_keyList << KeyInfo{{1049, 332, 101, 100}, {550, 0, 101, 100}, "3"};  // 3键
    m_keyList << KeyInfo{{770, 471, 101, 100}, {770, 0, 101, 100}, "4"};   // 4键
    m_keyList << KeyInfo{{908, 471, 101, 100}, {990, 0, 101, 100}, "5"};  // 5键
    m_keyList << KeyInfo{{1049, 471, 101, 100}, {1210, 0, 101, 100}, "6"}; // 6键
    m_keyList << KeyInfo{{771, 610, 101, 100}, {1430, 0, 101, 100}, "7"};  // 7键
    m_keyList << KeyInfo{{908, 610, 101, 100}, {1650, 0, 101, 100}, "8"}; // 8键
    m_keyList << KeyInfo{{1049, 610, 101, 100}, {1870, 0, 101, 100}, "9"};// 9键

    // 0键、回格键、ENTER键
    m_keyList << KeyInfo{{908, 749, 101, 100}, {2090, 0, 101, 100}, "0"};    // 0键
    m_keyList << KeyInfo{{770, 928, 150, 72}, {200, 150, 150, 72}, "backspace"}; // 回格键
    m_keyList << KeyInfo{{1001, 928, 150, 72}, {600, 150, 150, 72}, "enter"};    // ENTER键
}

void NumberKeyboard::paintEvent(QPaintEvent *event)
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
    painter.drawText(800, 260, m_inputNumber);

    if (clickedKey) {
        painter.drawPixmap(clickedKey->rect, m_spritePixmap, clickedKey->spriteRect);
    }

}

NumberKeyboard::KeyInfo* NumberKeyboard::getKeyAtPos(const QPoint &pos)
{
    // 遍历按键，判断点击位置是否在按键区域内
    for (KeyInfo &key : m_keyList) {
        if (key.rect.contains(pos)) {
            return &key;
        }
    }
    return nullptr;
}

void NumberKeyboard::mousePressEvent(QMouseEvent *event)
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
    if (keyValue == "backspace") {
        // 回格键：删除最后一个字符
        if (!m_inputNumber.isEmpty()) {
            m_inputNumber.chop(1);
        }
    } else if (keyValue == "enter") {
        this->hide();

        // ENTER键：发射信号并清空输入
        emit numberConfirmed(m_inputNumber);
        clearInput();
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


void NumberKeyboard::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) {
        return;
    }

    // 获取点击的按键
    clickedKey = nullptr;
    // 刷新绘制
    update();

}




void NumberKeyboard::clearInput()
{
    m_inputNumber.clear();
    clickedKey = nullptr;
}
