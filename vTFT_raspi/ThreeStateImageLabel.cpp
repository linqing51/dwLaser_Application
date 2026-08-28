#include "ThreeStateImageLabel.h"
#include <QDebug>

ThreeStateImageLabel::ThreeStateImageLabel(QWidget *parent)
    : QLabel(parent)
{
    setAlignment(Qt::AlignCenter);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setFixedSize(50, 50);
}

// 原有方法：设置独立图片（不变）
void ThreeStateImageLabel::setStateImages(const QString& state1Path,
                                          const QString& state2Path,
                                          const QString& state3Path)
{
    m_state1Pixmap.load(state1Path);
    m_state2Pixmap.load(state2Path);
    m_state3Pixmap.load(state3Path);

    if (m_state1Pixmap.isNull())
        qWarning() << "状态1图片加载失败：" << state1Path;
    if (m_state2Pixmap.isNull())
        qWarning() << "状态2图片加载失败：" << state2Path;
    if (m_state3Pixmap.isNull())
        qWarning() << "状态3图片加载失败：" << state3Path;
}

// 修正后的：从大图截取三个状态的区域
void ThreeStateImageLabel::setStateImageFromBigImage(const QString& bigImagePath,
                                                    const QRect& state1Rect,
                                                    const QRect& state2Rect,
                                                    const QRect& state3Rect)
{
    QPixmap bigPixmap(bigImagePath);
    if (bigPixmap.isNull()) {
        qCritical() << "大图加载失败：" << bigImagePath;
        return;
    }

    // 关键修正：将QSize转为QRect（大图的矩形区域：从(0,0)到(width,height)）
    QRect bigImageRect = QRect(0, 0, bigPixmap.width(), bigPixmap.height());

    // 修正检查逻辑：用QRect的contains判断截取区域是否完全在大图范围内
    auto checkRectValid = [&](const QRect& rect, const QString& state) {
        if (!bigImageRect.contains(rect)) {  // 这里改用QRect的contains
            qWarning() << state << "截取区域超出大图范围！大图区域："
                      << bigImageRect << "截取区域：" << rect;
            return false;
        }
        return true;
    };

    // 截取各状态图片
    if (checkRectValid(state1Rect, "状态1")) {
        m_state1Pixmap = cropPixmapFromBigImage(bigPixmap, state1Rect);
    }
    if (checkRectValid(state2Rect, "状态2")) {
        m_state2Pixmap = cropPixmapFromBigImage(bigPixmap, state2Rect);
    }
    if (checkRectValid(state3Rect, "状态3")) {
        m_state3Pixmap = cropPixmapFromBigImage(bigPixmap, state3Rect);
    }
}

// 从大图截取指定区域的图片（不变）
QPixmap ThreeStateImageLabel::cropPixmapFromBigImage(const QPixmap& bigPixmap, const QRect& rect)
{
    return bigPixmap.copy(rect);
}

// 槽函数：根据VALUE切换图片（不变）
void ThreeStateImageLabel::onValueChanged(int value)
{
    if (value == 0) {
        displayPixmap(m_state1Pixmap);
    } else if (value < 20) {
        displayPixmap(m_state2Pixmap);
    } else if (value <= 100) {
        displayPixmap(m_state3Pixmap);
    } else {
        qWarning() << "无效的状态值：" << value << "，显示默认状态1图片";
        displayPixmap(m_state1Pixmap);
    }
}

// 自适应显示图片（不变）
void ThreeStateImageLabel::displayPixmap(const QPixmap& pixmap)
{
    if (pixmap.isNull()) {
        clear();
        return;
    }

    QPixmap scaledPixmap = pixmap.scaled(this->size(),
                                        Qt::KeepAspectRatio,
                                        Qt::SmoothTransformation);
    setPixmap(scaledPixmap);
}

// 获取当前值
int ThreeStateImageLabel::value() const
{
    return m_value;
}

// 设置当前值
void ThreeStateImageLabel::setValue(int value)
{
    m_value = value;
    onValueChanged(m_value);
    update();
}


