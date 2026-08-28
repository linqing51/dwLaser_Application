

#ifndef GPIOCONTROL_H
#define GPIOCONTROL_H

#include <QObject>
#include <QDebug>
#include <gpiod.h>
#include <unistd.h>

class GpioControl : public QObject
{
    Q_OBJECT
public:
    // 参数：chip名称（CM5默认gpiochip0）、BCM编号
    explicit GpioControl(const char *chipName = "gpiochip0", int lineNum = 18, QObject *parent = nullptr);
    ~GpioControl();

    // 初始化GPIO（设置为输出）
    bool initOutput();
    // 设置电平：true=高，false=低
    bool setValue(bool isHigh);
    // 读取电平（返回true=高，false=低）
    bool getValue(bool &value);

private:
    struct gpiod_chip *m_chip;    // GPIO芯片对象
    struct gpiod_line *m_line;    // GPIO线路（对应BCM编号）
    const char *m_chipName;       // 芯片名称
    int m_lineNum;                // BCM编号
    bool m_isInit;                // 是否已初始化
};

#endif // GPIOCONTROL_H

