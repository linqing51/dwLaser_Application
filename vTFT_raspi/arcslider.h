#ifndef ARCSLIDER_H
#define ARCSLIDER_H

#include <QWidget>
#include <QColor>
#include <QPixmap>

class ArcSlider : public QWidget
{
    Q_OBJECT
    // 提供Qt属性系统支持，可在UI设计师中编辑
    Q_PROPERTY(int startAngle READ startAngle WRITE setStartAngle)
    Q_PROPERTY(int endAngle READ endAngle WRITE setEndAngle)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int minValue READ minValue WRITE setMinValue)
    Q_PROPERTY(int maxValue READ maxValue WRITE setMaxValue)
    Q_PROPERTY(QColor arcColor READ arcColor WRITE setArcColor)
    Q_PROPERTY(QColor progressColor READ progressColor WRITE setProgressColor)
    Q_PROPERTY(int arcWidth READ arcWidth WRITE setArcWidth)
    Q_PROPERTY(QString sliderImage READ sliderImage WRITE setSliderImage)
    Q_PROPERTY(bool sliderImageVisible READ sliderImageVisible WRITE setsliderImageVisible)

public:
    explicit ArcSlider(QWidget *parent = nullptr, int width = 150, int height = 150);

    // 获取/设置起始角度（角度值，0为右向，顺时针增大，如90为下，180为左，270为上）
    int startAngle() const;
    void setStartAngle(int angle);

    // 获取/设置终止角度
    int endAngle() const;
    void setEndAngle(int angle);

    void setSingleStep(int step);
    int singleStep() const;

    // 获取/设置当前值
    int value() const;
    void setValue(int value);

    // 获取/设置数值范围
    int minValue() const;
    void setMinValue(int min);
    int maxValue() const;
    void setMaxValue(int max);

    // 获取/设置弧形背景颜色
    QColor arcColor() const;
    void setArcColor(const QColor &color);

    // 获取/设置进度条颜色
    QColor progressColor() const;
    void setProgressColor(const QColor &color);

    // 获取/设置弧形宽度
    int arcWidth() const;
    void setArcWidth(int width);

    // 获取/设置滑块图片路径
    QString sliderImage() const;
    void setSliderImage(const QString &path);

    bool sliderImageVisible() const;
    void setsliderImageVisible(const bool Visible);

    QPixmap m_sliderPixmap;   // 滑块图片

signals:
    // 值变化信号
    void valueChanged(int value);

protected:
    // 重写绘制事件
    void paintEvent(QPaintEvent *event) override;
    // 重写鼠标按下事件
    void mousePressEvent(QMouseEvent *event) override;
    // 重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    // 计算指定数值对应的角度
    int valueToAngle(int value) const;
    // 计算指定坐标对应的数值
    int posToValue(const QPoint &pos) const;
    // 限制数值在有效范围内
    int clampValue(int value) const;
    // 限制角度在起始→终止的顺时针范围内
    int clampAngle(int angle) const;

    // 配置参数
    int m_startAngle = 270;   // 默认起始角度（上，270°）
    int m_endAngle = 90;      // 默认终止角度（下，90°）
    int m_minValue = 0;       // 默认最小值
    int m_maxValue = 100;     // 默认最大值
    int m_value = 0;          // 当前值
    QColor m_arcColor = Qt::lightGray;  // 弧形背景色
    QColor m_progressColor = Qt::blue;  // 进度条颜色
    int m_arcWidth = 10;      // 弧形宽度
    QString m_sliderImagePath; // 滑块图片路径
    bool m_visible = true;
    int m_singleStep = 1;
};

#endif // ARCSLIDER_H
