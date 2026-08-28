#include "arcslider.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtMath>

ArcSlider::ArcSlider(QWidget *parent, int width, int height) : QWidget(parent)
{
    // 设置鼠标追踪，支持拖动
    setMouseTracking(true);
    // 设置最小尺寸，避免控件过小
    setMinimumSize(120, 120);
    setFixedSize(width, height);
}

// 获取起始角度
int ArcSlider::startAngle() const
{
    return m_startAngle;
}

// 设置起始角度（确保为0-360范围）
void ArcSlider::setStartAngle(int angle)
{
    m_startAngle = angle % 360;
    update(); // 重绘控件
}

// 获取终止角度
int ArcSlider::endAngle() const
{
    return m_endAngle;
}

// 设置终止角度（确保为0-360范围）
void ArcSlider::setEndAngle(int angle)
{
    m_endAngle = angle % 360;
    update();
}

// 获取当前值
int ArcSlider::value() const
{
    return m_value;
}

// 设置当前值
void ArcSlider::setValue(int value)
{
    int clamped = clampValue(value);
    if (m_value != clamped)
    {
        m_value = clamped;
        emit valueChanged(m_value);
        update();
    }
}

// 获取最小值
int ArcSlider::minValue() const
{
    return m_minValue;
}

// 设置最小值
void ArcSlider::setMinValue(int min)
{
    m_minValue = min;
    setValue(m_value); // 重新校准当前值
    update();
}

// 获取最大值
int ArcSlider::maxValue() const
{
    return m_maxValue;
}

// 设置最大值
void ArcSlider::setMaxValue(int max)
{
    m_maxValue = max;
    setValue(m_value); // 重新校准当前值
    update();
}


void ArcSlider::setSingleStep(int step)
{
    if (step > 0) m_singleStep = step;
}

int ArcSlider::singleStep() const
{
    return m_singleStep;
}






// 获取弧形背景色
QColor ArcSlider::arcColor() const
{
    return m_arcColor;
}

// 设置弧形背景色
void ArcSlider::setArcColor(const QColor &color)
{
    m_arcColor = color;
    update();
}

// 获取进度条颜色
QColor ArcSlider::progressColor() const
{
    return m_progressColor;
}

// 设置进度条颜色
void ArcSlider::setProgressColor(const QColor &color)
{
    m_progressColor = color;
    update();
}

// 获取弧形宽度
int ArcSlider::arcWidth() const
{
    return m_arcWidth;
}

// 设置弧形宽度
void ArcSlider::setArcWidth(int width)
{
    m_arcWidth = width > 0 ? width : 1; // 确保宽度>0
    update();
}

// 获取滑块图片路径
QString ArcSlider::sliderImage() const
{
    return m_sliderImagePath;
}

// 设置滑块图片路径
void ArcSlider::setSliderImage(const QString &path)
{
//    m_sliderImagePath = path;
//    m_sliderPixmap.load(path); // 加载图片
        QPixmap m_sliderPixmap1;
        m_sliderPixmap1.load(path);
        m_sliderPixmap =m_sliderPixmap1.copy(0,3000,64,64);
    update();
}


bool ArcSlider::sliderImageVisible() const
{
    return m_visible;
}
void ArcSlider::setsliderImageVisible(const bool Visible)
{
    m_visible = Visible;
    update();

}




// 绘制事件
void ArcSlider::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿

    // 计算绘制区域（居中，留出滑块空间）
    int side = qMin(width(), height());
//    QRectF drawRect((width() - side) / 2 + m_arcWidth/2,
//                    (height() - side) / 2 + m_arcWidth/2,
//                    side - m_arcWidth,
//                    side - m_arcWidth);
    QRectF drawRect((width() - side) / 2 + m_arcWidth/2 + (64 - m_arcWidth)/2,
                    (height() - side) / 2 + m_arcWidth/2 + (64 - m_arcWidth)/2,
                    side - m_arcWidth - 64,
                    side - m_arcWidth - 64);

    // 1. 绘制弧形背景
    QPen pen(m_arcColor, m_arcWidth);
    pen.setCapStyle(Qt::FlatCap); // 线条端点平直
    painter.setPen(pen);
    // 计算弧形跨度：startAngle → endAngle 顺时针的角度差
    int spanAngle = m_startAngle - m_endAngle ;
    if (spanAngle == 0) spanAngle = 360; // 避免无跨度
    painter.drawArc(drawRect, m_startAngle * 16, -spanAngle * 16); // QT中角度单位是1/16度，负值为顺时针

    // 2. 绘制进度条
    int currentAngle = valueToAngle(m_value);
    int progressSpan =- (currentAngle - m_startAngle ); // 已进度的角度差
    pen.setColor(m_progressColor);
    painter.setPen(pen);
    painter.drawArc(drawRect, m_startAngle * 16, -progressSpan * 16);

    // 3. 绘制滑块
    if (m_visible == true)
    {
        if (!m_sliderPixmap.isNull())
        {
            // 计算滑块中心坐标
            qreal radian = qDegreesToRadians(360.0 - currentAngle); // 转换为弧度（QT坐标系y轴向下，需反转）
            qreal centerX = drawRect.center().x() + drawRect.width()/2 * qCos(radian);
            qreal centerY = drawRect.center().y() + drawRect.height()/2 * qSin(radian);

            // 调整滑块位置（居中）
            QRect sliderRect(centerX - m_sliderPixmap.width()/2,
                             centerY - m_sliderPixmap.height()/2,
                             m_sliderPixmap.width(),
                             m_sliderPixmap.height());
            painter.drawPixmap(sliderRect, m_sliderPixmap);
        }

    }
}

// 鼠标按下事件
void ArcSlider::mousePressEvent(QMouseEvent *event)
{
    if (m_visible == true)
    {
        if (!m_sliderPixmap.isNull())
        {
        if (event->button() == Qt::LeftButton)
        {
            setValue(posToValue(event->pos()));
        }
        };
        QWidget::mousePressEvent(event);
    }
}

// 鼠标移动事件
void ArcSlider::mouseMoveEvent(QMouseEvent *event)
{
    if (m_visible == true)
    {
        if (!m_sliderPixmap.isNull())
        {
        if (event->buttons() & Qt::LeftButton)
        {
            setValue(posToValue(event->pos()));
        }
        };
        QWidget::mouseMoveEvent(event);
    }
}

// 数值转角度（核心映射：值增大→角度减小）
int ArcSlider::valueToAngle(int value) const
{
    int clampedVal = clampValue(value);
    // 计算数值占比
    qreal ratio = (clampedVal - m_minValue) / (qreal)(m_maxValue - m_minValue);
    // 角度映射：startAngle → endAngle（值0对应startAngle，值max对应endAngle）
//    int angleRange = (m_endAngle - m_startAngle + 360) % 360;
    int angleRange = m_startAngle - m_endAngle;
    int targetAngle = m_startAngle - ratio * angleRange;
    return clampAngle(targetAngle);
}

// 坐标转数值
int ArcSlider::posToValue(const QPoint &pos) const
{
    // 计算控件中心
    QPointF center(width()/2, height()/2);
//    QPointF center(width()/2 - 64, height()/2 - 64);
    // 计算鼠标到中心的向量
    QPointF vec = pos - center;
    // 计算角度（0-360，0为右，顺时针增大）
    int angle = qAtan2(vec.y(), vec.x()) * 180 / M_PI;
    angle = (360 - angle) % 360; // 转换为QT弧形的角度方向

    // 角度转数值
    int angleRange = (m_endAngle - m_startAngle + 360) % 360;
    if (angleRange == 0) angleRange = 360;
    qreal ratio = (m_startAngle - angle) / (qreal)angleRange;
    int value = m_minValue + ratio * (m_maxValue - m_minValue);
    return clampValue(value);
}

// 限制数值在[min, max]
int ArcSlider::clampValue(int value) const
{
    return qBound(m_minValue, value, m_maxValue);
}

// 限制角度在有效范围
int ArcSlider::clampAngle(int angle) const
{
    angle = angle % 360;
    if (angle < 0) angle += 360;
    // 确保角度在startAngle→endAngle顺时针范围内
    int start = m_startAngle;
    int end = m_endAngle;
    if (start > end)
    {
        if (angle <= start && angle >= end) return angle;
        else if (angle > start) return start;
        else return end;
    }
    else
    {
        if (angle >= start && angle <= end) return angle;
        else if (angle < start) return start;
        else return end;
    }
}
