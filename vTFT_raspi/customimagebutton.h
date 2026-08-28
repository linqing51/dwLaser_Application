#ifndef CUSTOMIMAGEBUTTON_H
#define CUSTOMIMAGEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QPixmap>

class CustomImageButton : public QPushButton
{
    Q_OBJECT

public:
    // 构造函数：parent为父控件，bigImage为包含所有状态图的大图
    explicit CustomImageButton(QWidget *parent = 0, int width = 149, int height = 78);
    ~CustomImageButton() override = default;

    // 设置大图素材（全局只需设置一次）
    static bool setGlobalBigImage(const QString &imagePath);
    // 设置各种状态对应的图片截取区域
    void setEnterImageRect(const QRect& rect);      // 鼠标进入
    void setLeaveImageRect(const QRect& rect);      // 鼠标离开
    void setPressImageRect(const QRect& rect);      // 鼠标按下
    void setReleaseImageRect(const QRect& rect);    // 鼠标松开

    // 设置背景大图
//    void setBigImage(const QPixmap& bigImage);

protected:
    // 重写事件处理函数
    void enterEvent(QEvent *event) override;        // 鼠标进入事件
    void leaveEvent(QEvent *event) override;        // 鼠标离开事件
    void mousePressEvent(QMouseEvent *event) override; // 鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *event) override; // 鼠标松开事件
    void paintEvent(QPaintEvent *event) override;   // 绘制事件

private:
    QPixmap m_bigImage;
    QRect m_enterRect;           // 鼠标进入状态的截取区域
    QRect m_leaveRect;           // 鼠标离开状态的截取区域
    QRect m_pressRect;           // 鼠标按下状态的截取区域
    QRect m_releaseRect;         // 鼠标松开状态的截取区域
    QRect m_currentRect;         // 当前显示的截取区域

    // 关键修改：使用QSharedPointer延迟加载，避免静态QPixmap提前初始化
    static QSharedPointer<QPixmap> m_globalBigImage;

    // 获取全局大图（内部辅助函数）
    static QPixmap* getGlobalBigImage();

};

#endif // CUSTOMIMAGEBUTTON_H
