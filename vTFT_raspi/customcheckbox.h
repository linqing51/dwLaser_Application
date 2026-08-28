#ifndef CUSTOMCHECKBOX_H
#define CUSTOMCHECKBOX_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>

// 定义复选框的状态枚举（覆盖四种核心状态）
enum CheckBoxState {
    State_Release_Unchecked,  // 释放-未选中（默认）
    State_Release_Checked,    // 释放-选中
    State_Press_Unchecked,    // 按下-未选中
    State_Press_Checked       // 按下-选中
};

class CustomCheckBox : public QWidget
{
    Q_OBJECT
    //Q_PROPERTY(bool checked READ isChecked WRITE setChecked NOTIFY checkedChanged)
    Q_PROPERTY(bool checked READ isChecked WRITE setChecked)

public:
    explicit CustomCheckBox(QWidget *parent = nullptr);

    // 设置背景大图（包含四种状态的图片）
    void setBackgroundPixmap(const QString &pixmapPath);
    // 设置每种状态对应的图片在大图中的矩形区域（x,y,宽,高）
    void setStateRect(CheckBoxState state, const QRect &rect);
    // 设置/获取选中状态
    void setChecked(bool checked);
    bool isChecked() const;

signals:
    // 选中状态改变信号
    void checkedChanged(bool checked);
    void checkedChanged1();
    // 点击信号（同原生QCheckBox的clicked信号）
    void clicked(bool checked);

protected:
    // 重写事件处理函数
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    // 更新当前绘制状态
    void updateCurrentState();

    QPixmap m_backgroundPixmap;  // 背景大图
    bool m_checked = false;      // 是否选中
    bool m_pressed = false;      // 是否按下
    bool m_hovered = false;      // 是否悬浮
    CheckBoxState m_currentState = State_Release_Unchecked;  // 当前状态

    // 存储每种状态对应的截图区域
    QMap<CheckBoxState, QRect> m_stateRectMap;
};

#endif // CUSTOMCHECKBOX_H
