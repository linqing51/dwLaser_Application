#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

class CustomSlider : public QWidget
{
    Q_OBJECT
    // 提供属性支持，可在Qt Designer中编辑
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(int maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(QString sliderImagePath READ sliderImagePath WRITE setSliderImagePath)
    Q_PROPERTY(QRect cropRect READ cropRect WRITE setCropRect) // 截取区域

public:
    explicit CustomSlider(QWidget *parent = nullptr, const QString &path = ":/images/sprite.png", int width = 300, int height = 60);

    // 获取/设置最小值
    int minimum() const { return m_min; }
    void setMinimum(int min);

    // 获取/设置最大值
    int maximum() const { return m_max; }
    void setMaximum(int max);

    // 获取/设置当前值
    int value() const { return m_value; }
    void setValue(int value);

    // 设置滑块图片路径
    QString sliderImagePath() const { return m_sliderImagePath; }
    void setSliderImagePath(const QString &path);

    // 设置图片截取区域
    QRect cropRect() const { return m_cropRect; }
    void setCropRect(const QRect &rect);

signals:
    void valueChanged(int value); // 值变化信号

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    // 计算滑块的x坐标（根据当前值）
    int sliderX() const;
    // 计算当前值（根据鼠标x坐标）
    int valueFromPos(int x) const;

    int m_min = 0;          // 最小值
    int m_max = 100;        // 最大值
    int m_value = 0;        // 当前值
    bool m_isDragging = false; // 是否正在拖动滑块
    QPixmap m_sliderPixmap; // 滑块图片
    QString m_sliderImagePath; // 滑块图片路径
    QRect m_cropRect;      // 图片截取区域（x,y,宽,高）
    int m_sliderWidth = 20; // 滑块宽度（默认，可通过截取区域调整）
    int m_sliderHeight = 20;// 滑块高度（默认）
};

#endif // CUSTOMSLIDER_H
