#include "customcheckbox.h"

CustomCheckBox::CustomCheckBox(QWidget *parent)
    : QWidget(parent)
{
    // 设置鼠标追踪，确保悬浮状态能及时更新
    setMouseTracking(true);
    // 设置widget可点击
    setAttribute(Qt::WA_TransparentForMouseEvents, false);
}

void CustomCheckBox::setBackgroundPixmap(const QString &pixmapPath)
{
    m_backgroundPixmap.load(pixmapPath);
    // 加载图片后更新绘制
    update();
}

void CustomCheckBox::setStateRect(CheckBoxState state, const QRect &rect)
{
    m_stateRectMap[state] = rect;
    // 设置区域后更新绘制
    updateCurrentState();
    update();
}

void CustomCheckBox::setChecked(bool checked)
{
    if (m_checked != checked) {
        m_checked = checked;
        updateCurrentState();
        emit checkedChanged(checked);
        emit checkedChanged1();
        update();
    }
}

bool CustomCheckBox::isChecked() const
{
    return m_checked;
}

void CustomCheckBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);  // 抗锯齿

    // 如果未设置对应状态的区域或图片未加载，直接返回
    if (!m_stateRectMap.contains(m_currentState) || m_backgroundPixmap.isNull()) {
        return;
    }

    // 获取当前状态对应的截图区域
    QRect srcRect = m_stateRectMap[m_currentState];
    // 绘制截取的图片（适配widget大小）
    painter.drawPixmap(this->rect(), m_backgroundPixmap, srcRect);
}

void CustomCheckBox::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressed = true;
        updateCurrentState();
        update();
    }
    QWidget::mousePressEvent(event);
}

void CustomCheckBox::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_pressed = false;
        // 鼠标释放时切换选中状态（点击区域内才生效）
        if (this->rect().contains(event->pos())) {
            setChecked(!m_checked);
            emit clicked(m_checked);
        }
        updateCurrentState();
        update();
    }
    QWidget::mouseReleaseEvent(event);
}

void CustomCheckBox::enterEvent(QEvent *event)
{
    m_hovered = true;
    updateCurrentState();
    update();
    QWidget::enterEvent(event);
}

void CustomCheckBox::leaveEvent(QEvent *event)
{
    m_hovered = false;
    updateCurrentState();
    update();
    QWidget::leaveEvent(event);
}

void CustomCheckBox::updateCurrentState()
{
    // 根据按下/选中状态，更新当前绘制状态
    if (m_pressed) {
        m_currentState = m_checked ? State_Press_Checked : State_Press_Unchecked;
    } else {
        m_currentState = m_checked ? State_Release_Checked : State_Release_Unchecked;
    }
}
