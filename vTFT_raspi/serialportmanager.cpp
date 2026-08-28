#include "serialportmanager.h"

// 初始化静态共享数据
QByteArray SerialPortManager::sharedSerialData;
QMutex SerialPortManager::sharedDataMutex;

// 单例实例初始化
SerialPortManager* SerialPortManager::getInstance()
{
    static SerialPortManager instance;
    return &instance;
}

// 构造函数
SerialPortManager::SerialPortManager(QObject *parent)
    : QObject(parent)
    , m_serialPort(new QSerialPort(this))
    , m_readNotifier(nullptr)
{
    // 设置串口名称（树莓派UART0对应/dev/ttyAMA0）
    // 注意：CM5需确保GPIO14/15映射到UART0，可通过raspi-config开启串口
    m_serialPort->setPortName("/dev/ttyAMA0");
//     m_serialPort->setPortName("/dev/ttyAMA4");
}

// 析构函数
SerialPortManager::~SerialPortManager()
{
    if (m_serialPort->isOpen()) {
        m_serialPort->close();
    }
    if (m_readNotifier) {
        m_readNotifier->deleteLater();
    }
}

// 串口初始化
bool SerialPortManager::initSerialPort(qint32 baudRate, QSerialPort::DataBits dataBits,
                                       QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    // 关闭已打开的串口
    if (m_serialPort->isOpen()) {
        m_serialPort->close();
    }

    // 配置串口参数
    m_serialPort->setBaudRate(baudRate);
    m_serialPort->setDataBits(dataBits);
    m_serialPort->setParity(parity);
    m_serialPort->setStopBits(stopBits);
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);

    // 打开串口（读写模式）
    if (!m_serialPort->open(QIODevice::ReadWrite)) {
        qCritical() << "串口打开失败：" << m_serialPort->errorString();
        return false;
    }

    // 创建读中断通知器（文件描述符可读时触发中断）
    if (m_readNotifier) {
        m_readNotifier->deleteLater();
    }
    m_readNotifier = new QSocketNotifier(m_serialPort->handle(), QSocketNotifier::Read, this);
    // 绑定中断处理槽函数（核心：实现串口接收中断）
    connect(m_readNotifier, &QSocketNotifier::activated, this, &SerialPortManager::handleSerialReadInterrupt);

    qInfo() << "串口0初始化成功：/dev/ttyAMA0 (GPIO14/TXD0, GPIO15/RXD0)";
//    qInfo() << "串口4初始化成功：/dev/ttyAMA4 (GPIO12/TXD0, GPIO13/RXD0)";
    return true;
}

// 串口读中断处理（数据接收时触发）
void SerialPortManager::handleSerialReadInterrupt()
{
    // 禁用中断通知（避免重复触发）
    m_readNotifier->setEnabled(false);

    // 读取串口数据
    QByteArray recvData = m_serialPort->readAll();
    if (recvData.isEmpty()) {
        m_readNotifier->setEnabled(true);
        return;
    }

    // 线程安全更新静态共享数据
    QMutexLocker locker(&sharedDataMutex);
    sharedSerialData = recvData;  // 覆盖或追加可根据需求调整（如sharedSerialData.append(recvData)）
    locker.unlock();

    // 发送数据接收信号（供外部处理）
    emit dataReceived(recvData);

    // 重新启用中断通知
    m_readNotifier->setEnabled(true);

//    qDebug() << "中断接收数据：" << recvData.toHex() << "（原始：" << recvData << "）";
}

// 发送数据
bool SerialPortManager::sendData(const QByteArray& data)
{
    if (!m_serialPort->isOpen()) {
        qCritical() << "串口0未打开，发送失败";
        return false;
    }

    qint64 written = m_serialPort->write(data);
    if (written == -1) {
        qCritical() << "数据发送失败：" << m_serialPort->errorString();
        return false;
    }

    // 确保数据立即发送
    m_serialPort->flush();

//    qDebug() << "发送数据：" << data.toHex() << "（原始：" << data << "）";
    return true;
}



