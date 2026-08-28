#include "gpiointerrupt.h"
#include <QDebug>
#include <unistd.h>
#include <cstring>

GpioInterrupt::GpioInterrupt(QObject *parent)
    : QObject(parent)
    , m_chipName("")
    , m_lineOffset(-1)
    , m_chip(nullptr)
    , m_line(nullptr)
    , m_listenThread(nullptr)
    , m_isListening(false)
    , m_edge(GpioEdge::RisingEdge)
{
}

GpioInterrupt::~GpioInterrupt()
{
    stopInterrupt();
}

bool GpioInterrupt::initialize(const char *chipName, int lineOffset, GpioEdge::Type edge, const QString& consumer)
{
    // 1. 参数校验
    if (chipName == nullptr || strlen(chipName) == 0) {
        emit errorOccurred("GPIO芯片名不能为空");
        return false;
    }
    if (lineOffset < 0 || lineOffset > 53) {
        emit errorOccurred(QString("无效的GPIO引脚号：%1（范围0-53）").arg(lineOffset));
        return false;
    }

    // 2. 释放已有资源
    if (m_chip != nullptr || m_line != nullptr) {
        releaseResources();
    }

    // 3. 保存配置
    m_chipName = QString(chipName);
    m_lineOffset = lineOffset;
    m_edge = edge;

    m_chip = gpiod_chip_open_by_name(chipName);
    if (!m_chip) {
        emit errorOccurred(QString("打开GPIO芯片%1失败").arg(m_chipName));
        releaseResources();
        return false;
    }

    // 5. 获取GPIO引脚
    m_line = gpiod_chip_get_line(m_chip, m_lineOffset);
    if (!m_line) {
        emit errorOccurred(QString("获取GPIO引脚%1失败").arg(m_lineOffset));
        releaseResources();
        return false;
    }

    // 6. 根据边缘类型请求GPIO模式
    int ret = -1;
    const char* consumerStr = consumer.toUtf8().constData();
    switch (m_edge) {
    case GpioEdge::RisingEdge:
        ret = gpiod_line_request_rising_edge_events(m_line, consumerStr);
        break;
    case GpioEdge::FallingEdge:
        ret = gpiod_line_request_falling_edge_events(m_line, consumerStr);
        break;
    case GpioEdge::BothEdges:
        ret = gpiod_line_request_input(m_line, consumerStr);
        break;
    default:
        emit errorOccurred("无效的中断触发边缘");
        releaseResources();
        return false;
    }

    // 7. 检查请求结果
    if (ret != 0) {
        emit errorOccurred(QString("请求GPIO%1模式失败，错误码：%2").arg(m_lineOffset).arg(ret));
        releaseResources();
        return false;
    }

    // 8. 启动监听线程
    m_isListening = true;
    m_listenThread = new QThread(this);
    moveToThread(m_listenThread);

    if (m_edge == GpioEdge::BothEdges) {
        connect(m_listenThread, &QThread::started, this, &GpioInterrupt::listenForBothEdges);
    } else {
        connect(m_listenThread, &QThread::started, this, &GpioInterrupt::listenForRisingFallingEdge);
    }
    connect(m_listenThread, &QThread::finished, m_listenThread, &QThread::deleteLater);
    m_listenThread->start();

    qDebug() << QString("GPIO%1（芯片%2）中断初始化成功，触发边缘：%3")
                .arg(m_lineOffset)
                .arg(m_chipName)
                .arg(static_cast<int>(m_edge));
    return true;
}

void GpioInterrupt::stopInterrupt()
{
    if (!m_isListening) return;

    m_isListening = false;
    if (m_listenThread) {
        m_listenThread->quit();
        m_listenThread->wait(1000);
    }
    releaseResources();

    qDebug() << QString("GPIO%1（芯片%2）中断已停止").arg(m_lineOffset).arg(m_chipName);
}

void GpioInterrupt::listenForRisingFallingEdge()
{
    struct gpiod_line_event event;
    int ret;
    struct timespec timeout = {0, 100000000};

    while (m_isListening) {
        ret = gpiod_line_event_wait(m_line, &timeout);
        if (ret < 0) {
            emit errorOccurred(QString("监听GPIO%1中断失败，错误码：%2").arg(m_lineOffset).arg(ret));
            break;
        } else if (ret == 0) {
            continue;
        }

        ret = gpiod_line_event_read(m_line, &event);
        if (ret < 0) {
            emit errorOccurred(QString("读取GPIO%1中断事件失败，错误码：%2").arg(m_lineOffset).arg(ret));
            break;
        }

        int level = gpiod_line_get_value(m_line);
        emit interruptTriggered(level);

        const char* edgeType = (event.event_type == GPIOD_LINE_EVENT_RISING_EDGE) ? "上升沿" : "下降沿";
        qDebug() << QString("GPIO%1中断触发，电平：%2，事件类型：%3")
                    .arg(m_lineOffset)
                    .arg(level)
                    .arg(edgeType);
    }

    m_isListening = false;
}

void GpioInterrupt::listenForBothEdges()
{
    int lastLevel = -1;
    const int debounceMs = 10;

    while (m_isListening) {
        int currentLevel = gpiod_line_get_value(m_line);

        if (currentLevel == -1) {
            emit errorOccurred(QString("读取GPIO%1电平失败").arg(m_lineOffset));
            usleep(debounceMs * 1000);
            continue;
        }

        if (currentLevel != lastLevel) {
            if (lastLevel != -1) {
                emit interruptTriggered(currentLevel);
                qDebug() << QString("GPIO%1双边沿中断触发，电平：%2（上一次：%3）")
                            .arg(m_lineOffset)
                            .arg(currentLevel)
                            .arg(lastLevel);
            }
            lastLevel = currentLevel;
        }

        usleep(debounceMs * 1000);
    }

    m_isListening = false;
}

void GpioInterrupt::releaseResources()
{
    if (m_line) {
        gpiod_line_release(m_line);
        m_line = nullptr;
    }
    if (m_chip) {
        gpiod_chip_close(m_chip);
        m_chip = nullptr;
    }
    m_lineOffset = -1;
    m_chipName = "";
}
