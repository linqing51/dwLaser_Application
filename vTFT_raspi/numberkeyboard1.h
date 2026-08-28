#ifndef NUMBERKEYBOARD1_H
#define NUMBERKEYBOARD1_H

#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QMouseEvent>
#include <QPainter>

class NumberKeyboard1 : public QWidget
{
    Q_OBJECT
public:
    explicit NumberKeyboard1(QWidget *parent = 0);
    // 设置按键雪碧图
    void setKeySprite(const QString &spritePath);
    QPixmap m_originalPixmap;  // 背景图
    QPixmap m_spritePixmap;    // 按键雪碧图
    QString m_inputNumber;     // 当前输入的数字

protected:
    // 重写绘制事件，绘制按键
    void paintEvent(QPaintEvent *event) override;
    // 重写鼠标点击事件，处理按键交互
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    // 按键结构体，存储位置、尺寸和对应值
    struct KeyInfo1 {
        QRect rect;       // 按键在控件中的显示区域
        QRect spriteRect; // 按键在雪碧图中的截取区域
        QString value;    // 按键对应的值（数字/enter/backspace）
    };

    KeyInfo1 *clickedKey;
    QList<KeyInfo1> m_keyList;  // 所有按键信息列表

    // 初始化按键布局和雪碧图截取区域（需根据你的雪碧图调整）
    void initKeyLayout();
    // 根据点击位置获取对应的按键
    KeyInfo1* getKeyAtPos(const QPoint &pos);

signals:
    // ENTER键按下时发射的信号，携带输入的数字
    //void numberConfirmed(const QString &number);
    void numberConfirmed(const QString &number);

public slots:
    // 清空输入的数字
    void clearInput();
};

#endif // NUMBERKEYBOARD_H
