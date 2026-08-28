#include "modbusuart4master.h"
#include <QSerialPortInfo>
#include <QDebug>

ModbusUart4Master::ModbusUart4Master(QObject *parent)
    : QObject{parent}
{
    // 1. 创建Modbus RTU主站
    m_modbusMaster = new QModbusRtuSerialMaster(this);

    // 2. 绑定信号槽
    connect(m_modbusMaster, &QModbusClient::errorOccurred,
            this, &ModbusUart4Master::handleError);
    connect(m_modbusMaster, &QModbusClient::stateChanged,
            this, &ModbusUart4Master::handleStateChanged);
}

ModbusUart4Master::~ModbusUart4Master()
{
    disconnectUart4();
    m_modbusMaster->deleteLater();
}

// ===================== 连接UART4 =====================
bool ModbusUart4Master::connectUart4()
{
    if (!m_modbusMaster || m_modbusMaster->state() == QModbusDevice::ConnectedState) {
        return false;
    }

    // 设置串口参数
#ifdef Q_OS_WIN
    m_modbusMaster->setConnectionParameter(QModbusDevice::SerialPortNameParameter, UART4_PORT_WIN);
#else
    m_modbusMaster->setConnectionParameter(QModbusDevice::SerialPortNameParameter, UART4_PORT_LINUX);
#endif
    m_modbusMaster->setConnectionParameter(QModbusDevice::SerialBaudRateParameter, BAUDRATE);
    m_modbusMaster->setConnectionParameter(QModbusDevice::SerialParityParameter, PARITY);
    m_modbusMaster->setConnectionParameter(QModbusDevice::SerialDataBitsParameter, DATA_BITS);
    m_modbusMaster->setConnectionParameter(QModbusDevice::SerialStopBitsParameter, STOP_BITS);

    // 超时时间
    m_modbusMaster->setTimeout(RESPONSE_TIME);
    // 重试次数
    m_modbusMaster->setNumberOfRetries(1);

    // 连接串口
    return m_modbusMaster->connectDevice();
}

// ===================== 断开连接 =====================
void ModbusUart4Master::disconnectUart4()
{
    if (m_modbusMaster && m_modbusMaster->state() == QModbusDevice::ConnectedState) {
        m_modbusMaster->disconnectDevice();
    }
}

bool ModbusUart4Master::isConnected() const
{
    return m_modbusMaster && m_modbusMaster->state() == QModbusDevice::ConnectedState;
}

// ===================== 读保持寄存器 0x03 =====================
bool ModbusUart4Master::readHoldingRegisters(int slaveAddr, int startAddr, int regNum)
{
    if (!isConnected()) {
        emit modbusError("UART4未连接");
        return false;
    }

    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, startAddr, regNum);
    QModbusReply *reply = m_modbusMaster->sendReadRequest(readUnit, slaveAddr);

    if (!reply) {
        emit modbusError("读请求发送失败: " + m_modbusMaster->errorString());
        return false;
    }

    // 收到响应
    connect(reply, &QModbusReply::finished, this, [=]() {
        onModbusReplyFinished(reply);
    });
    return true;
}

// ===================== 写单个寄存器 0x06 =====================
bool ModbusUart4Master::writeSingleRegister(int slaveAddr, int regAddr, quint16 value)
{
    if (!isConnected()) {
        emit modbusError("UART4未连接");
        return false;
    }

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, regAddr, 1);
    writeUnit.setValue(0, value);

    QModbusReply *reply = m_modbusMaster->sendWriteRequest(writeUnit, slaveAddr);
    if (!reply) {
        emit modbusError("写单寄存器请求失败: " + m_modbusMaster->errorString());
        return false;
    }

    connect(reply, &QModbusReply::finished, this, [=]() {
        onModbusReplyFinished(reply);
    });
    return true;
}

// ===================== 写多个寄存器 0x10 =====================
bool ModbusUart4Master::writeMultipleRegisters(int slaveAddr, int startAddr, const QList<quint16> &values)
{
    if (!isConnected()) {
        emit modbusError("UART4未连接");
        return false;
    }

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, startAddr, values.size());
    for (int i = 0; i < values.size(); i++) {
        writeUnit.setValue(i, values[i]);
    }

    QModbusReply *reply = m_modbusMaster->sendWriteRequest(writeUnit, slaveAddr);
    if (!reply) {
        emit modbusError("写多寄存器失败: " + m_modbusMaster->errorString());
        return false;
    }

    connect(reply, &QModbusReply::finished, this, [=]() {
        onModbusReplyFinished(reply);
    });
    return true;
}

// ===================== 响应处理 =====================
void ModbusUart4Master::onModbusReplyFinished(QModbusReply *reply)
{
    if (reply->error() != QModbusDevice::NoError) {
        emit modbusError(QString("从站响应错误: %1").arg(reply->errorString()));
        reply->deleteLater();
        return;
    }

    QModbusDataUnit unit = reply->result();

    // 读取数据
    QList<quint16> values;
    for (quint16 val : unit.values()) {
        values.append(val);
    }
    emit readDataReady(reply->serverAddress(), unit.startAddress(), values);
    // 写入数据
    emit writeSuccess(reply->serverAddress(), unit.startAddress());

    reply->deleteLater();
}

// ===================== 错误与状态 =====================
void ModbusUart4Master::handleError(QModbusDevice::Error error)
{
    Q_UNUSED(error)
    emit modbusError("Modbus错误: " + m_modbusMaster->errorString());
}

void ModbusUart4Master::handleStateChanged(QModbusDevice::State state)
{
    bool connected = (state == QModbusDevice::ConnectedState);
    emit connectStateChanged(connected);
}
