#ifndef CUSTOMDOUBLESPINBOX_H
#define CUSTOMDOUBLESPINBOX_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QPixmap>
#include <QMouseEvent>
#include <QString>
#include "customimagebutton.h"

class CustomDoubleSpinBox : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(double minimum READ minimum WRITE setMinimum)
    Q_PROPERTY(double maximum READ maximum WRITE setMaximum)
    Q_PROPERTY(double singleStep READ singleStep WRITE setSingleStep)

public:
//    explicit CustomDoubleSpinBox(QWidget *parent = nullptr, const QPixmap& bigImage = QPixmap(), int width = 120, int height = 30, QString unit = "S");
    explicit CustomDoubleSpinBox(QWidget *parent = nullptr, int width = 120, int height = 30, QString unit = "S");

    double value() const;
    void setValue(double value);
    void setUnit(QString s);
    void setMinimum(double min);
    double minimum() const;
    void setMaximum(double max);
    double maximum() const;
    void setSingleStep(double step);
    double singleStep() const;
//    // 设置背景大图
//    void setBigImage(const QPixmap& bigImage);
signals:
    void valueChanged(double value);
protected:
    void paintEvent(QPaintEvent *event) override;
private slots:
    void onMinusClicked();
    void onPlusClicked();

private:
    QString m_unit;
    double m_value;
    double m_min;
    double m_max;
    double m_singleStep;
    QGridLayout *mainLayout;

    QLabel *m_valueLabel;
    QPixmap m_minusPixmap;
    QPixmap m_plusPixmap;
    CustomImageButton *m_minusLabel;
    CustomImageButton *m_plusLabel;
    static const QPixmap& bigPixmap(); // 加载获取大图的方法
    QPixmap m_bigImage;          // 包含所有状态的大图

};

#endif // CUSTOMDOUBLESPINBOX_H
