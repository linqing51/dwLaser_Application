#ifndef SERIALPORTMANAGER_H
#define SERIALPORTMANAGER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QSocketNotifier>
#include <QMutex>
#include <QDebug>

// 串口管理类（封装UART0，对应GPIO14/TXD0、GPIO15/RXD0）
class SerialPortManager : public QObject
{
    Q_OBJECT
public:
    // 获取单例实例（避免多实例冲突）
    static SerialPortManager* getInstance();

    // 串口初始化（参数：波特率、数据位、校验位、停止位）
    bool initSerialPort(qint32 baudRate = QSerialPort::Baud115200,
                        QSerialPort::DataBits dataBits = QSerialPort::Data8,
                        QSerialPort::Parity parity = QSerialPort::NoParity,
                        QSerialPort::StopBits stopBits = QSerialPort::OneStop);

    // 发送数据
    bool sendData(const QByteArray& data);

    // 静态共享数据（全局可访问，线程安全）
    static QByteArray sharedSerialData;  // 串口共享数据区
    static QMutex sharedDataMutex;       // 共享数据互斥锁

signals:
    // 串口数据接收中断信号（外部可绑定槽函数处理）
    void dataReceived(const QByteArray& data);

private slots:
    // 串口读中断处理函数（核心中断逻辑）
    void handleSerialReadInterrupt();

private:
    // 私有构造函数（单例模式）
    explicit SerialPortManager(QObject *parent = nullptr);
    ~SerialPortManager();

    // 禁用拷贝构造和赋值
    SerialPortManager(const SerialPortManager&) = delete;
    SerialPortManager& operator=(const SerialPortManager&) = delete;

    QSerialPort* m_serialPort;         // 串口对象
    QSocketNotifier* m_readNotifier;   // 读中断通知器（实现中断机制）
};

#endif // SERIALPORTMANAGER_H

