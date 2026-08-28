#ifndef SPIMODBUSMASTER_H
#define SPIMODBUSMASTER_H

#include <QObject>
#include <QFile>
#include <QMutex>
#include <linux/spi/spidev.h>
#include <pigpio.h> // 引入pigpio头文件
#include <gpiod.h>
#include "gpiocontrol.h"

// SPI Modbus主站类：实现Modbus RTU通过SPI通信
class SpiModbusMaster : public QObject
{
    Q_OBJECT
public:
    // 通信模式枚举
    enum ModbusFunc {
        ReadCoils = 0x01,
        ReadDiscreteInputs = 0x02,
        ReadHoldingRegisters = 0x03,
        ReadInputRegisters = 0x04,
        WriteSingleCoil = 0x05,
        WriteSingleRegister = 0x06,
        WriteMultipleCoils = 0x0F,
        WriteMultipleRegisters = 0x10
    };

    explicit SpiModbusMaster(QObject *parent = nullptr);
    ~SpiModbusMaster();

    // 初始化SPI
    bool initSpi(const QString &spiDev = "/dev/spidev0.0",
                 uint32_t speed = 1000000,  // 1MHz
                 uint8_t mode = SPI_MODE_3,
                 uint8_t bits = 8);

    // 关闭SPI
    void closeSpi();

    // ====================== 核心Modbus功能函数 ======================
    // 读保持寄存器 (最常用)
    bool readHoldingRegisters(quint8 slaveAddr, quint16 regAddr, quint16 regNum, QVector<quint16> &result);

    // 读输入寄存器
    bool readInputRegisters(quint8 slaveAddr, quint16 regAddr, quint16 regNum, QVector<quint16> &result);

    // 写单个寄存器
    bool writeSingleRegister(quint8 slaveAddr, quint16 regAddr, quint16 value);

    // 写多个寄存器
    bool writeMultipleRegisters(quint8 slaveAddr, quint16 startAddr, const QVector<quint16> &values);

private:
    // SPI文件句柄
    QFile m_spiFile;
    // SPI配置参数
    uint32_t m_speed;
    uint8_t m_mode;
    uint8_t m_bits;
    // 线程安全互斥锁
    QMutex m_mutex;

    // 底层SPI收发函数
    bool spiTransfer(const uint8_t *txBuf, uint8_t *rxBuf, uint32_t len);

    // Modbus CRC16校验
    uint16_t calcModbusCrc(const uint8_t *data, uint16_t len);

    // 组装Modbus报文并发送接收
    bool sendModbusFrame(const QByteArray &sendFrame, QByteArray &recvFrame, int recvLen);

    GpioControl *gpio;

};

#endif // SPIMODBUSMASTER_H
