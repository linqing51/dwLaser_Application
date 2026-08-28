#ifndef GPIOINTERRUPT_H
#define GPIOINTERRUPT_H

#include <QObject>
#include <QThread>
#include <gpiod.h>
#include <QString>
#include <time.h>

// 枚举定义：命名空间隔离避免宏冲突
namespace GpioEdge {
    enum Type {
        RisingEdge = 0,   // 上升沿
        FallingEdge = 1,  // 下降沿
        BothEdges = 2     // 双边沿
    };
}

// GPIO中断输入类（适配libgpiod v1.x）
class GpioInterrupt : public QObject
{
    Q_OBJECT
public:
    explicit GpioInterrupt(QObject *parent = nullptr);
    ~GpioInterrupt();

    // 核心修改：chipName参数改为const char*
    bool initialize(const char *chipName, int lineOffset, GpioEdge::Type edge, const QString& consumer = "qt-gpio-interrupt");
    void stopInterrupt();
    int lineOffset() const { return m_lineOffset; }
    QString chipName() const { return m_chipName; } // 仍返回QString，方便上层使用

signals:
    void interruptTriggered(int level);
    void errorOccurred(const QString& error);

private slots:
    void listenForRisingFallingEdge();
    void listenForBothEdges();

private:
    void releaseResources();

    QString m_chipName;        // 内部仍用QString存储，方便日志/调试
    int m_lineOffset;
    struct gpiod_chip* m_chip;
    struct gpiod_line* m_line;
    QThread* m_listenThread;
    bool m_isListening;
    GpioEdge::Type m_edge;
};

#endif // GPIOINTERRUPT_H
