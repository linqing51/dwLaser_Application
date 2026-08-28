#include "customdoublespinbox.h"
#include <QPainter>
#include <QCursor>
#include <QDebug>
#include "customimagebutton.h"


const QPixmap& CustomDoubleSpinBox::bigPixmap()
{
    // static局部变量：第一次调用时初始化，后续调用直接返回，保证全局唯一
    static const QPixmap s_bigPixmap(":/images/sprite.png");

    // 调试：检查图片是否加载成功
    if (s_bigPixmap.isNull()) {
        qWarning() << "CustomDoubleSpinBox大图加载失败，请检查资源路径：:/images/sprite.png";
    }
    return s_bigPixmap;
}

//CustomDoubleSpinBox::CustomDoubleSpinBox(QWidget *parent, const QPixmap& bigImage, int width, int height, QString unit)
//    : QWidget(parent)
//    , m_value(0.1)
//    , m_min(0.0)
//    , m_max(100.0)
//    , m_singleStep(1.0)
//    , m_bigImage(bigImage)
//    , m_unit(unit)
//    {

CustomDoubleSpinBox::CustomDoubleSpinBox(QWidget *parent, int width, int height, QString unit)
    : QWidget(parent)
    , m_unit(unit)
    , m_value(0.1)
    , m_min(0.0)
    , m_max(100.0)
    , m_singleStep(1.0)
{

    const QPixmap& bigImg = bigPixmap();
    m_bigImage = bigImg.copy(0,3340,width,height);

    m_valueLabel = new QLabel(QString::number(m_value), this);

    if ((width == 380) && (height == 70))
    {
        m_bigImage = bigImg.copy(0,3340,380,70);
        m_minusLabel = new CustomImageButton(this,30, 60);
        m_minusLabel->setLeaveImageRect(QRect(6, 3345, 30, 60));
        m_minusLabel->setEnterImageRect(QRect(6, 3345, 30, 60));
        m_minusLabel->setPressImageRect(QRect(386, 3345, 30, 60));
        m_minusLabel->setReleaseImageRect(QRect(6, 3345, 30, 60));
        connect(m_minusLabel, &QPushButton::clicked, []() {
            qDebug() << "自定义按钮m_minusLabel被点击";
        });
        m_minusLabel->move(6,5);
        m_plusLabel = new CustomImageButton(this,30, 60);
        m_plusLabel->setLeaveImageRect(QRect(342, 3345, 30, 60));
        m_plusLabel->setEnterImageRect(QRect(342, 3345, 30, 60));
        m_plusLabel->setPressImageRect(QRect(722, 3345, 30, 60));
        m_plusLabel->setReleaseImageRect(QRect(342, 3345, 30, 60));
        connect(m_plusLabel, &QPushButton::clicked, []() {
            qDebug() << "自定义按钮m_plusLabel被点击";
        });
        m_plusLabel->move(342,5);

        m_valueLabel->setAlignment(Qt::AlignCenter);
        m_valueLabel->setStyleSheet(R"(
            QLabel {
                color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
                font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
                font-size: 42px;           /* 字体大小 */
            }
        )");
        m_valueLabel->resize(120,60);
        m_valueLabel->move(136,5);

        connect(m_minusLabel, &QPushButton::clicked, this, &CustomDoubleSpinBox::onMinusClicked);
        connect(m_plusLabel, &QPushButton::clicked, this, &CustomDoubleSpinBox::onPlusClicked);
    } else
    {
        if ((width == 236) && (height == 60))
        {
            m_bigImage = bigImg.copy(786,3350,236,60);
            m_minusLabel = new CustomImageButton(this,48, 48);
            m_minusLabel->setLeaveImageRect(QRect(792, 3356,48, 48));
            m_minusLabel->setEnterImageRect(QRect(792, 3356,48, 48));
            m_minusLabel->setPressImageRect(QRect(1062, 3356,48, 48));
            m_minusLabel->setReleaseImageRect(QRect(792, 3356,48, 48));
            connect(m_minusLabel, &QPushButton::clicked, []() {
                qDebug() << "自定义按钮m_minusLabel被点击";
            });
            m_minusLabel->move(6,6);
            m_plusLabel = new CustomImageButton(this,48, 48);
            m_plusLabel->setLeaveImageRect(QRect(964, 3356,48, 48));
            m_plusLabel->setEnterImageRect(QRect(964, 3356,48, 48));
            m_plusLabel->setPressImageRect(QRect(1234, 3356,48, 48));
            m_plusLabel->setReleaseImageRect(QRect(964, 3356,48, 48));
            connect(m_plusLabel, &QPushButton::clicked, []() {
                qDebug() << "自定义按钮m_plusLabel被点击";
            });
            m_plusLabel->move(178,6);

            m_valueLabel->setAlignment(Qt::AlignCenter);
            m_valueLabel->setStyleSheet(R"(
                QLabel {
                    color: white;                /* 字体颜色（支持英文/十六进制/#FF0000） */
                    font-family: "Microsoft YaHei"; /* 字体（中文用微软雅黑/宋体） */
                    font-size: 36px;           /* 字体大小 */
                }
            )");
            m_valueLabel->resize(120,60);
            m_valueLabel->move(56,0);

            connect(m_minusLabel, &QPushButton::clicked, this, &CustomDoubleSpinBox::onMinusClicked);
            connect(m_plusLabel, &QPushButton::clicked, this, &CustomDoubleSpinBox::onPlusClicked);
        }
    }



    mainLayout = new QGridLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);



    setFixedSize(width, height);
}

// 以下原有方法完全不变，无需修改
double CustomDoubleSpinBox::value() const
{
    return m_value;
}

void CustomDoubleSpinBox::setValue(double value)
{
    if (value < m_min) value = m_min;
    if (value > m_max) value = m_max;

    if (qFuzzyCompare(m_value, value)) return;

    m_value = value;
    m_valueLabel->setText(QString::number(m_value, 'f', 1)+m_unit);
    emit valueChanged(m_value);
}

void CustomDoubleSpinBox::setMinimum(double min)
{
    m_min = min;
    if (m_value < m_min) setValue(m_min);
}

double CustomDoubleSpinBox::minimum() const
{
    return m_min;
}

void CustomDoubleSpinBox::setMaximum(double max)
{
    m_max = max;
    if (m_value > m_max) setValue(m_max);
}

double CustomDoubleSpinBox::maximum() const
{
    return m_max;
}

void CustomDoubleSpinBox::setSingleStep(double step)
{
    if (step > 0) m_singleStep = step;
}

double CustomDoubleSpinBox::singleStep() const
{
    return m_singleStep;
}


// 设置背景大图
//void CustomDoubleSpinBox::setBigImage(const QPixmap& bigImage)
//{
//    m_bigImage  = bigImage;
//    update(); // 刷新绘制
//}

void CustomDoubleSpinBox::setUnit(QString s)
{
    m_unit = s;
    update(); // 刷新绘制
}

void CustomDoubleSpinBox::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if (!m_bigImage.isNull()) {
        painter.drawPixmap(rect(), m_bigImage);
    }
    // 调用父类绘制事件，保证控件正常显示
    QWidget::paintEvent(event);


}

void CustomDoubleSpinBox::onMinusClicked()
{
    setValue(m_value - m_singleStep);
}

void CustomDoubleSpinBox::onPlusClicked()
{
    setValue(m_value + m_singleStep);
}
