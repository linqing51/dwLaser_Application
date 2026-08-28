#ifndef THREESTATEIMAGELABEL_H
#define THREESTATEIMAGELABEL_H

#include <QLabel>
#include <QPixmap>
#include <QRect>

// 自定义三状态图片标签控件（从大图截取区域）
class ThreeStateImageLabel : public QLabel
{
    Q_OBJECT
    Q_PROPERTY(int value READ value WRITE setValue)
public:
    // 构造函数
    explicit ThreeStateImageLabel(QWidget *parent = nullptr);

    // 重载1：设置独立图片（保留原有功能）
    void setStateImages(const QString& state1Path,
                        const QString& state2Path,
                        const QString& state3Path);

    // 重载2：从一张大图中截取三个状态的区域
    void setStateImageFromBigImage(const QString& bigImagePath,
                                  const QRect& state1Rect,  // 状态1截取区域
                                  const QRect& state2Rect,  // 状态2截取区域
                                  const QRect& state3Rect); // 状态3截取区域
    // 获取/设置当前值
    int value() const;
    void setValue(int value);

public slots:
    // 根据VALUE参数切换显示对应状态的图片
    void onValueChanged(int value);

private:
    QPixmap m_state1Pixmap;  // 状态1图片
    QPixmap m_state2Pixmap;  // 状态2图片
    QPixmap m_state3Pixmap;  // 状态3图片
    int m_value = 0;          // 当前值

    // 自适应显示图片
    void displayPixmap(const QPixmap& pixmap);

    // 从大图截取指定区域
    QPixmap cropPixmapFromBigImage(const QPixmap& bigPixmap, const QRect& rect);
};

#endif // THREESTATEIMAGELABEL_H
