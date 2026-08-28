#include "CustomImageCheckBox.h"
#include <QPainter>

CustomImageCheckBox::CustomImageCheckBox(QWidget *parent)
    : QAbstractButton(parent)

    , m_isHover(false)
    , m_isPressed(false)
{
    // 设置按钮可选中，支持checkable状态
    setCheckable(true);
    // 取消默认的焦点框绘制
    setFocusPolicy(Qt::NoFocus);
}

void CustomImageCheckBox::setUncheckedImage(const QPixmap &pixmap)
{
    m_uncheckedImage = pixmap;
    update(); // 刷新绘制
}

void CustomImageCheckBox::setCheckedImage(const QPixmap &pixmap)
{
    m_checkedImage = pixmap;
    update();
}

void CustomImageCheckBox::setHoverImage(const QPixmap &pixmap)
{
    m_hoverImage = pixmap;
    update();
}

void CustomImageCheckBox::setPressImage(const QPixmap &pixmap)
{
    m_pressImage = pixmap;
    update();
}

QSize CustomImageCheckBox::sizeHint() const
{
    // 如果有未选中图片，返回图片大小，否则返回默认大小
    if (!m_uncheckedImage.isNull()) {
        return m_uncheckedImage.size();
    }
    return QSize(24, 24); // 默认大小
}

void CustomImageCheckBox::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform); // 平滑缩放

    QPixmap currentPixmap;

    // 确定当前要绘制的图片
    if (m_isPressed && !m_pressImage.isNull()) {
        // 按下状态优先
        currentPixmap = m_pressImage;
    } else if (m_isHover && !m_hoverImage.isNull()) {
        // 悬停状态
        currentPixmap = m_hoverImage;
    } else if (isChecked() && !m_checkedImage.isNull()) {
        // 选中状态
        currentPixmap = m_checkedImage;
    } else if (!m_uncheckedImage.isNull()) {
        // 未选中状态
        currentPixmap = m_uncheckedImage;
    }

    if (!currentPixmap.isNull()) {
        // 居中绘制图片
        int x = (width() - currentPixmap.width()) / 2;
        int y = (height() - currentPixmap.height()) / 2;
        painter.drawPixmap(x, y, currentPixmap);
    }
}

void CustomImageCheckBox::enterEvent(QEvent *e)
{
    m_isHover = true;
    update(); // 刷新绘制
    QAbstractButton::enterEvent(e);
}

void CustomImageCheckBox::leaveEvent(QEvent *e)
{
    m_isHover = false;
    update();
    QAbstractButton::leaveEvent(e);
}

void CustomImageCheckBox::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_isPressed = true;
        update();
    }
    QAbstractButton::mousePressEvent(e);
}

void CustomImageCheckBox::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        m_isPressed = false;
        update();
    }
    QAbstractButton::mouseReleaseEvent(e);
}

bool CustomImageCheckBox::hitButton(const QPoint &pos) const
{
    // 只响应图片区域的点击（如果有图片）
    if (!m_uncheckedImage.isNull()) {
        QRect rect(0, 0, m_uncheckedImage.width(), m_uncheckedImage.height());
        rect.moveCenter(geometry().center());
        return rect.contains(pos);
    }
    return QAbstractButton::hitButton(pos);
}
