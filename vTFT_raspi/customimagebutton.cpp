#include "customimagebutton.h"
#include <QApplication>
#include "QDebug"

QSharedPointer<QPixmap> CustomImageButton::m_globalBigImage = QSharedPointer<QPixmap>();

CustomImageButton::CustomImageButton(QWidget *parent,  int width, int height)
    : QPushButton(parent)
{
    // 设置按钮无边框、透明背景，只显示自定义图片
    setFlat(true);
    setStyleSheet("QPushButton { border: none; }");
    setFixedSize(width, height);

    // 如果全局大图未加载且传入了路径，则尝试加载
    if (getGlobalBigImage() == nullptr) {
        setGlobalBigImage(":/images/sprite.png");
    }


}

// 全局大图加载函数（核心：延迟创建QPixmap，确保在QApplication之后）
bool CustomImageButton::setGlobalBigImage(const QString &imagePath)
{
    // 检查QGuiApplication是否已创建
    if (QApplication::instance() == nullptr) {
        qCritical() << "Error: QApplication not created before loading pixmap!";
        return false;
    }

    // 延迟创建QPixmap对象（此时QApplication已存在）
    QSharedPointer<QPixmap> tempPixmap(new QPixmap());
    if (!tempPixmap->load(imagePath)) {
        qCritical() << "Failed to load big image:" << imagePath;
        return false;
    }

    m_globalBigImage = tempPixmap;
    qDebug() << "Global big image loaded successfully, size:" << tempPixmap->size();

    return true;
}

// 获取全局大图的辅助函数
QPixmap* CustomImageButton::getGlobalBigImage()
{
    if (m_globalBigImage.isNull()) {
        return nullptr;
    }
    return m_globalBigImage.data();
}


// 设置鼠标进入状态的截取区域
void CustomImageButton::setEnterImageRect(const QRect& rect)
{
    m_enterRect = rect;
    // 如果按钮还没设置大小，默认用该区域大小
    if (size().isEmpty()) {
        setFixedSize(rect.size());
    }
}

// 设置鼠标离开状态的截取区域
void CustomImageButton::setLeaveImageRect(const QRect& rect)
{
    m_leaveRect = rect;
    m_currentRect = rect; // 更新当前显示区域
    // 如果按钮还没设置大小，默认用该区域大小
    if (size().isEmpty()) {
        setFixedSize(rect.size());
    }
    update(); // 刷新绘制
}

// 设置鼠标按下状态的截取区域
void CustomImageButton::setPressImageRect(const QRect& rect)
{
    m_pressRect = rect;
    // 如果按钮还没设置大小，默认用该区域大小
    if (size().isEmpty()) {
        setFixedSize(rect.size());
    }
}

// 设置鼠标松开状态的截取区域
void CustomImageButton::setReleaseImageRect(const QRect& rect)
{
    m_releaseRect = rect;
    // 如果按钮还没设置大小，默认用该区域大小
    if (size().isEmpty()) {
        setFixedSize(rect.size());
    }
}

//// 设置背景大图
//void CustomImageButton::setBigImage(const QPixmap& bigImage)
//{
//    m_bigImage = bigImage;
//    update(); // 刷新绘制
//}

// 鼠标进入事件
void CustomImageButton::enterEvent(QEvent *event)
{
    m_currentRect = m_enterRect;
    update(); // 触发重绘
    QPushButton::enterEvent(event); // 调用父类事件处理
}

// 鼠标离开事件
void CustomImageButton::leaveEvent(QEvent *event)
{
    m_currentRect = m_leaveRect;
    update(); // 触发重绘
    QPushButton::leaveEvent(event); // 调用父类事件处理
}

// 鼠标按下事件
void CustomImageButton::mousePressEvent(QMouseEvent *event)
{
    // 只处理左键按下
    if (event->button() == Qt::LeftButton) {
        m_currentRect = m_pressRect;
        update(); // 触发重绘
    }
    QPushButton::mousePressEvent(event); // 调用父类事件处理
}

// 鼠标松开事件
void CustomImageButton::mouseReleaseEvent(QMouseEvent *event)
{
    // 只处理左键松开
    if (event->button() == Qt::LeftButton) {
        m_currentRect = m_releaseRect;
        update(); // 触发重绘
    }
    QPushButton::mouseReleaseEvent(event); // 调用父类事件处理
}

// 绘制事件：核心是从大图截取指定区域并绘制
void CustomImageButton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // 获取全局大图（确保不为空）
    QPixmap* bigImage = getGlobalBigImage();
    if (bigImage == nullptr || bigImage->isNull() || m_currentRect.isEmpty()) {
      // 如果没有大图或当前区域为空，调用父类绘制（显示默认按钮）
      QPushButton::paintEvent(event);
      return;
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform); // 抗锯齿

    // 从大图中截取当前区域的图片，并绘制到按钮上
    QPixmap currentPixmap = bigImage->copy(m_currentRect);
    painter.drawPixmap(rect(), currentPixmap);

}
