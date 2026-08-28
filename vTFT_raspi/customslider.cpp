#include "customslider.h"
#include <QDebug>

CustomSlider::CustomSlider(QWidget *parent, const QString &path, int width, int height) : QWidget(parent)
  , m_sliderImagePath(path)
{
    setFixedSize(width, height);
    // 设置鼠标追踪（可选，优化交互）
    setMouseTracking(true);
    m_cropRect = QRect(0, 0, 40, 40);
    this->setSliderImagePath(path);
}

void CustomSlider::setMinimum(int min)
{
    m_min = min;
    // 保证值的合法性
    if (m_value < m_min)
        setValue(m_min);
    update(); // 重绘
}

void CustomSlider::setMaximum(int max)
{
    m_max = max;
    // 保证值的合法性
    if (m_value > m_max)
        setValue(m_max);
    update(); // 重绘
}

void CustomSlider::setValue(int value)
{
    // 限制值在[min, max]范围内
    int newValue = qBound(m_min, value, m_max);
    if (m_value != newValue) {
        m_value = newValue;
        emit valueChanged(m_value);
        update(); // 重绘
    }
}

void CustomSlider::setSliderImagePath(const QString &path)
{
    m_sliderImagePath = path;
    // 加载图片
    QPixmap fullImage(path);
    if (!fullImage.isNull() && !m_cropRect.isEmpty()) {
        // 从大图中截取指定区域
        m_sliderPixmap = fullImage.copy(m_cropRect);
        // 更新滑块尺寸
        m_sliderWidth = m_cropRect.width();
        m_sliderHeight = m_cropRect.height();
    } else if (!fullImage.isNull()) {
        // 如果未指定截取区域，使用整张图片
        m_sliderPixmap = fullImage;
        m_sliderWidth = fullImage.width();
        m_sliderHeight = fullImage.height();
    } else {
        qWarning() << "加载滑块图片失败：" << path;
    }
    update();
}

void CustomSlider::setCropRect(const QRect &rect)
{
    m_cropRect = rect;
    // 重新加载图片（应用新的截取区域）
    if (!m_sliderImagePath.isEmpty())
        setSliderImagePath(m_sliderImagePath);
}

int CustomSlider::sliderX() const
{
    // 计算滑块的x坐标（适配控件宽度）
    int usableWidth = width() - m_sliderWidth;
    if (usableWidth <= 0)
        return 0;
    double ratio = (m_value - m_min) / (double)(m_max - m_min);
    return qRound(ratio * usableWidth);
}

int CustomSlider::valueFromPos(int x) const
{
    // 根据鼠标x坐标计算对应的值
    int usableWidth = width() - m_sliderWidth;
    if (usableWidth <= 0)
        return m_min;
    // 限制x坐标范围
    x = qBound(0, x - m_sliderWidth/2, usableWidth);
    double ratio = x / (double)usableWidth;
    return qRound(m_min + ratio * (m_max - m_min));
}

void CustomSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    // 1. 绘制滑动条背景（灰色底）
    QRect bgRect(0, height()/2, width(), 6);
    painter.setBrush(QColor(72, 72, 72));
    painter.setPen(Qt::NoPen);
    painter.drawRoundedRect(bgRect, 3, 3);

    // 2. 绘制红色调节区域（已滑动的部分）
    QRect redRect(0, height()/2 - 2, sliderX() + m_sliderWidth/2, 10);
    painter.setBrush(QColor(255, 0, 0)); // 红色
    painter.drawRoundedRect(redRect, 5, 5);

    // 3. 绘制滑块
    if (!m_sliderPixmap.isNull()) {
        // 滑块居中显示
        int sliderY = (height() - m_sliderHeight) / 2 +2;
        painter.drawPixmap(sliderX(), sliderY, m_sliderPixmap);
    } else {
        // 备用滑块样式（如果图片加载失败）
        QRect sliderRect(sliderX(), (height() - m_sliderHeight)/2, m_sliderWidth, m_sliderHeight);
        painter.setBrush(QColor(255, 80, 80));
        painter.drawRoundedRect(sliderRect, 5, 5);
    }
}

void CustomSlider::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 检查是否点击了滑块
        QRect sliderRect(sliderX(), (height() - m_sliderHeight)/2, m_sliderWidth, m_sliderHeight);
        if (sliderRect.contains(event->pos())) {
            m_isDragging = true;
        } else {
            // 点击滑动条空白处，直接跳转到对应位置
            setValue(valueFromPos(event->x()));
            m_isDragging = true;
        }
    }
}

void CustomSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isDragging && event->buttons() & Qt::LeftButton) {
        setValue(valueFromPos(event->x()));
    }
}

void CustomSlider::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDragging = false;
    }
}
