#include "gpiocontrol.h"

GpioControl::GpioControl(const char *chipName, int lineNum, QObject *parent)
    : QObject(parent), m_chipName(chipName), m_lineNum(lineNum), m_isInit(false)
{
    // 打开GPIO芯片
    m_chip = gpiod_chip_open_by_name(m_chipName);
    if (!m_chip) {
        qCritical() << "打开GPIO芯片" << m_chipName << "失败";
        return;
    }

    // 获取指定BCM编号的线路
    m_line = gpiod_chip_get_line(m_chip, m_lineNum);
    if (!m_line) {
        qCritical() << "获取BCM" << m_lineNum << "线路失败（编号无效）";
        gpiod_chip_close(m_chip);
        m_chip = nullptr;
        return;
    }
    qInfo() << "成功打开GPIO芯片和BCM" << m_lineNum << "线路";
}

GpioControl::~GpioControl()
{
    if (m_isInit) {
        // 释放线路
        gpiod_line_release(m_line);
    }
    if (m_chip) {
        gpiod_chip_close(m_chip);
    }
    qInfo() << "GPIO资源已释放" << m_lineNum << "线路";
}

bool GpioControl::initOutput()
{
    if (!m_chip || !m_line) {
        qCritical() << "GPIO芯片/线路未初始化";
        return false;
    }

    // 请求将线路设置为输出，初始电平低
    int ret = gpiod_line_request_output(m_line, "qt_gpio_control", 0);
    if (ret < 0) {
        qCritical() << "设置BCM" << m_lineNum << "为输出失败（可能被占用）";
        return false;
    }

    m_isInit = true;
    qInfo() << "BCM" << m_lineNum << "已设置为输出模式";
    return true;
}

bool GpioControl::setValue(bool isHigh)
{
    if (!m_isInit) {
        qCritical() << "GPIO未初始化，无法设置电平";
        return false;
    }

    // 设置电平：1=高，0=低
    int ret = gpiod_line_set_value(m_line, isHigh ? 1 : 0);
    if (ret < 0) {
        qCritical() << "设置BCM" << m_lineNum << "电平失败";
        return false;
    }

    qInfo() << "BCM" << m_lineNum << "设置为：" << (isHigh ? "高电平" : "低电平");
    return true;
}

bool GpioControl::getValue(bool &value)
{
    if (!m_isInit) {
        qCritical() << "GPIO未初始化，无法读取电平";
        return false;
    }

    int val = gpiod_line_get_value(m_line);
    if (val < 0) {
        qCritical() << "读取BCM" << m_lineNum << "电平失败";
        return false;
    }

    value = (val == 1);
    qInfo() << "BCM" << m_lineNum << "当前电平：" << (value ? "高电平" : "低电平");
    return true;
}

