#ifndef MODBUSUART4MASTER_H
#define MODBUSUART4MASTER_H

#include <QObject>
#include <QModbusRtuSerialMaster>
#include <QModbusDataUnit>
#include <QModbusReply>
#include <QSerialPort>
#include <QSerialPortInfo>

// Modbus RTU 主站类（UART4）
class ModbusUart4Master : public QObject
{
    Q_OBJECT
public:
    explicit ModbusUart4Master(QObject *parent = nullptr);
    ~ModbusUart4Master() override;

    // ===================== 基础配置 =====================
    // 连接UART4（根据系统自动适配：Linux/dev/ttyS4 / WindowsCOM4）
    bool connectUart4();
    // 断开连接
    void disconnectUart4();
    // 判断是否已连接
    bool isConnected() const;

    // ===================== Modbus 功能 =====================
    /**
     * @brief 读保持寄存器 (功能码 0x03)
     * @param slaveAddr 从站地址
     * @param startAddr 起始寄存器地址
     * @param regNum 读取长度
     * @return 发送成功返回true
     */
    bool readHoldingRegisters(int slaveAddr, int startAddr, int regNum);

    /**
     * @brief 写单个寄存器 (功能码 0x06)
     */
    bool writeSingleRegister(int slaveAddr, int regAddr, quint16 value);

    /**
     * @brief 写多个寄存器 (功能码 0x10)
     */
    bool writeMultipleRegisters(int slaveAddr, int startAddr, const QList<quint16> &values);

private slots:
    // 接收Modbus响应
    void onModbusReplyFinished(QModbusReply *reply);
    // 错误处理
    void handleError(QModbusDevice::Error error);
    // 状态变化
    void handleStateChanged(QModbusDevice::State state);

signals:
    // 信号：读取到寄存器数据
    void readDataReady(int slaveAddr, int startAddr, const QList<quint16> &regValues);
    // 信号：写入成功
    void writeSuccess(int slaveAddr, int regAddr);
    // 信号：错误信息
    void modbusError(const QString &errorStr);
    // 信号：连接状态变化
    void connectStateChanged(bool connected);

private:
    QModbusRtuSerialMaster *m_modbusMaster = nullptr;  // Modbus主站对象

    // 串口配置（根据你的硬件修改！）
    const QString UART4_PORT_LINUX  = "/dev/ttyAMA4";
    const QString UART4_PORT_WIN    = "COM4";
    const int     BAUDRATE          = 115200;
//    const int     BAUDRATE          = 256000;
    const QSerialPort::Parity       PARITY = QSerialPort::NoParity;
    const QSerialPort::DataBits     DATA_BITS = QSerialPort::Data8;
    const QSerialPort::StopBits     STOP_BITS = QSerialPort::OneStop;
    const int     RESPONSE_TIME     = 1000;  // 从站响应超时 ms
};

#endif // MODBUSUART4MASTER_H
