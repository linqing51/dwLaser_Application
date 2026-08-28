#include "gpioqueryinput.h"
#include <QDebug>

GpioQueryInput::GpioQueryInput(const char *chipName, int lineOffset, QObject *parent)
    : QObject(parent), m_chipName(chipName), m_lineNum(lineOffset), m_isInit(false)
{
    // 1. 打开GPIO芯片
    m_chip = gpiod_chip_open_by_name(m_chipName);
    if (!m_chip) {
        qCritical() << "打开GPIO芯片" << m_chipName << "失败";
        return;
    }

    // 2. 获取GPIO线路（偏移量对应BCM编号）
    m_line = gpiod_chip_get_line(m_chip, m_lineNum);
    if (!m_line) {
        qCritical() << "获取GPIO线路失败，偏移量：" << m_lineNum;
        gpiod_chip_close(m_chip);
        m_chip = nullptr;
        return;
    }
    qInfo() << "成功打开GPIO芯片和BCM" << m_lineNum << "线路";
}

GpioQueryInput::~GpioQueryInput()
{
    // 释放资源
    if (m_line) {
        gpiod_line_release(m_line);
    }
    if (m_chip) {
        gpiod_chip_close(m_chip);
    }
    qInfo() << "GPIO资源已释放" << m_lineNum << "线路";
}



bool GpioQueryInput::initInput()
{
    if (!m_chip || !m_line) {
        qCritical() << "GPIO芯片/线路未初始化";
        return false;
    }

    int ret = gpiod_line_request_input(m_line, "qt-gpio-query");
    if (ret != 0) {
        qCritical() << "设置GPIO为输入模式失败，错误码：" << ret;
        gpiod_chip_close(m_chip);
        gpiod_line_release(m_line);
        return false;
    }


    m_isInit = true;
    qInfo() << "BCM" << m_lineNum << "已设置为输入模式";
    return true;
}




bool GpioQueryInput::getGpioLevel()
{
    if (!m_isInit) {
        qCritical() << "GPIO未初始化，无法设置电平";
        return false;
    }

    // 读取电平：1=高电平，0=低电平
    int level = gpiod_line_get_value(m_line);
    if (level < 0) {
        qCritical() << "读取GPIO电平失败，错误码：" << level;
        return false;
    }

    return (level == 1);
}


