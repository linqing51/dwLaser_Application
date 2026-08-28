#include "spimodbusmaster.h"
#include <QDebug>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <cstdint>


SpiModbusMaster::SpiModbusMaster(QObject *parent)
    : QObject(parent),
      m_speed(1000000),
      m_mode(SPI_MODE_3),
      m_bits(8)
{
    gpio = new GpioControl("gpiochip0", 8,this);
    if (!gpio->initOutput()) {
       qCritical() << "GPIO未初始化，无法读取电平";
    };
    gpio->setValue(true);  // 高电平

}

SpiModbusMaster::~SpiModbusMaster()
{
    closeSpi();
}

// ====================== SPI初始化 ======================
bool SpiModbusMaster::initSpi(const QString &spiDev, uint32_t speed, uint8_t mode, uint8_t bits)
{
    if (m_spiFile.isOpen()) {
        qWarning() << "SPI已打开";
        return true;
    }

    m_speed = speed;
    m_mode = mode;
    m_bits = bits;

    // 打开SPI设备
    m_spiFile.setFileName(spiDev);
    if (!m_spiFile.open(QIODevice::ReadWrite | QIODevice::Unbuffered)) {
        qCritical() << "打开SPI失败:" << m_spiFile.errorString();
        return false;
    }

    int fd = m_spiFile.handle();
    // 设置SPI模式
    if (ioctl(fd, SPI_IOC_WR_MODE, &m_mode) < 0) {
        qCritical() << "设置SPI模式失败";
        m_spiFile.close();
        return false;
    }

    // 设置数据位
    if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &m_bits) < 0) {
        qCritical() << "设置SPI数据位失败";
        m_spiFile.close();
        return false;
    }

    // 设置时钟
    if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &m_speed) < 0) {
        qCritical() << "设置SPI时钟失败";
        m_spiFile.close();
        return false;
    }

    qDebug() << "SPI初始化成功:" << spiDev << "速度:" << speed/1000 << "kHz";
    return true;
}

// 关闭SPI
void SpiModbusMaster::closeSpi()
{
    if (m_spiFile.isOpen()) {
        m_spiFile.close();
        qDebug() << "SPI已关闭";
    }
}

// ====================== 底层SPI数据收发 ======================
bool SpiModbusMaster::spiTransfer(const uint8_t *txBuf, uint8_t *rxBuf, uint32_t len)
{
    if (!m_spiFile.isOpen()) return false;

    spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)txBuf,
        .rx_buf = (unsigned long)rxBuf,
        .len = len,
        .speed_hz = m_speed,
        .delay_usecs = 0,
        .bits_per_word = m_bits,
        .cs_change = 0,  // 保持片选有效（主从一对一）
        .tx_nbits = 0,
        .rx_nbits = 0,
        .word_delay_usecs = 0,
        .pad = 0,
    };

    int ret = ioctl(m_spiFile.handle(), SPI_IOC_MESSAGE(1), &tr);
    return ret >= 0;
}

// ====================== Modbus CRC16校验 ======================
//uint16_t SpiModbusMaster::calcModbusCrc(const uint8_t *data, uint16_t len)
//{
//    uint16_t crc = 0xFFFF;
//    for (uint16_t i = 0; i < len; i++) {
//        crc ^= data[i];
//        for (uint8_t j = 0; j < 8; j++) {
//            if (crc & 1) {
//                crc >>= 1;
//                crc ^= 0xA001;
//            } else {
//                crc >>= 1;
//            }
//        }
//    }
//    return crc;
//}


uint16_t SpiModbusMaster::calcModbusCrc(const uint8_t *data, uint16_t len)
{
    std::uint16_t crc = 0xFFFFU;
    for (std::uint16_t i = 0; i < len; ++i)
    {
        crc ^= data[i];
        for (std::uint8_t j = 0U; j < 8U; ++j)
        {
            if ((crc & 0x0001U) != 0U)
            {
                crc >>= 1U;
                crc ^= 0xA001U;
            }
            else
            {
                crc >>= 1U;
            }
        }
    }
    return crc;
}





// ====================== 发送Modbus帧 ======================
bool SpiModbusMaster::sendModbusFrame(const QByteArray &sendFrame, QByteArray &recvFrame, int recvLen)
{
    QMutexLocker locker(&m_mutex);
    recvFrame.clear();

    if (!m_spiFile.isOpen()) {
        qCritical() << "SPI未初始化";
        return false;
    }

    // 发送缓冲区 + 接收缓冲区
    QByteArray txData = sendFrame;
    QByteArray rxData(recvLen, 0x00);


    // SPI全双工收发
    if (!spiTransfer((uint8_t*)txData.constData(), (uint8_t*)rxData.data(), txData.size())) {
        qCritical() << "SPI传输失败";
        return false;
    }

    // 从机响应延时（Modbus标准）
    usleep(2000);
//    usleep(100);

    // 读取从机响应
//    if (!spiTransfer(nullptr, (uint8_t*)rxData.data(), recvLen)) {
//        qCritical() << "读取SPI响应失败";
//        return false;
//    }
    int tmp = 0,len = recvLen;
    while (len > 4)
    {
        if (!spiTransfer(nullptr, (uint8_t*)rxData.data()+tmp, 4)) {
            qCritical() << "读取SPI响应失败";
            return false;
        }
        len = len - 4;
        tmp = tmp + 4;

    }
    if (!spiTransfer(nullptr, (uint8_t*)rxData.data()+tmp, recvLen - tmp)) {
        qCritical() << "读取SPI响应失败";
        return false;
    }

    recvFrame = rxData;
    return true;
}

// ====================== 读保持寄存器 ======================
bool SpiModbusMaster::readHoldingRegisters(quint8 slaveAddr, quint16 regAddr, quint16 regNum, QVector<quint16> &result)
{
    result.clear();


    // 组装Modbus报文
    QByteArray frame;
    frame.append(0xAA);
    frame.append(slaveAddr);
    frame.append(ReadHoldingRegisters);
    frame.append((regAddr >> 8) & 0xFF);
    frame.append(regAddr & 0xFF);
    frame.append((regNum >> 8) & 0xFF);
    frame.append(regNum & 0xFF);
    for (uint8_t i = 0; i < 240; i++) {
        frame.append(i);
    }

    // 追加CRC
    quint16 crc = calcModbusCrc((uint8_t*)frame.constData(), frame.size());
    frame.append(crc & 0xFF);
    frame.append((crc >> 8) & 0xFF);
    frame.append(0x55);
    gpio->setValue(false);
    usleep(10);

    if (!m_spiFile.isOpen()) {
        qCritical() << "SPI未初始化";
        return false;
    }
    QByteArray txData = frame;
    QByteArray rxData(txData.size(), 0x00);
    if (!spiTransfer((uint8_t*)txData.constData(), (uint8_t*)rxData.data(), txData.size())) {
            qCritical() << "读取SPI响应失败";
            return false;
    }
    usleep(400);
    txData = rxData;
    if (!spiTransfer((uint8_t*)txData.constData(), (uint8_t*)rxData.data(), txData.size())) {
            qCritical() << "读取SPI响应失败";
            return false;
    }
    qDebug() << "接收数据 hex:" << rxData.toHex(' ');

    gpio->setValue(true);


//    if((quint8)rxData.at(0) == 0xAA && (quint8)rxData.at(rxData.size() -1) == 0x55)
//    {
//            uint16_t recv_len = rxData.at(3)+2+2;
//            quint16 recvCrc = (rxData.at(recv_len-1+1) << 8) | rxData.at(recv_len-2+1);
//            quint16 calcCrc = calcModbusCrc((uint8_t*)rxData.at(1), recv_len-2);
//            if (recvCrc != calcCrc) {
//                qCritical() << "CRC校验错误";
//                return false;
//            }
//             return recv_len;
//    }
    return 0;




//    // 组装Modbus报文
//    QByteArray frame;
//    frame.append(slaveAddr);
//    frame.append(ReadHoldingRegisters);
//    frame.append((regAddr >> 8) & 0xFF);
//    frame.append(regAddr & 0xFF);
//    frame.append((regNum >> 8) & 0xFF);
//    frame.append(regNum & 0xFF);


//    for(int i=0;i<frame.size();i++)
//    {
//        qDebug() << QString::asprintf("[%d] 0x%02X", i, (quint8)frame.at(i));
//    };


//    // 追加CRC
//    quint16 crc = calcModbusCrc((uint8_t*)frame.constData(), frame.size());
//    frame.append(crc & 0xFF);
//    frame.append((crc >> 8) & 0xFF);

//    // 接收长度 = 从机地址(1)+功能码(1)+字节数(1)+数据(2*N)+CRC(2)
////    int recvLen = 5 + 2 * regNum ;
////    QByteArray recvData;

////    if (!sendModbusFrame(frame, recvData, recvLen) || recvData.size() < recvLen) {
////        qCritical() << "读保持寄存器通信失败";
////        return false;
////    }


////    int recvLen = 5 + 2 * regNum +1;
//    int recvLen = 4 + 5 + 2 * regNum +1;
//    QByteArray recvData;

//    if (!sendModbusFrame(frame, recvData, recvLen) || recvData.size() < recvLen) {
//        qCritical() << "读保持寄存器通信失败";
//        return false;
//    }
////     for(int i=0;i<recvData.size();i++)
////      {
////         qDebug() << QString::asprintf("[%d] 0x%02X", i, (quint8)recvData.at(i));
////      };


//     while ((!recvData.isEmpty())&&(recvData.size() > 1)&&((quint8)recvData.at(0) == 0x00))
//     {
//                recvData = recvData.mid(1);
//     }

//     quint8 buf[recvLen];
//     recvLen = 5 + 2 * regNum;
//     qDebug() << "接收数据 hex:" << recvData.toHex(' ');
//    for(int i=0;i<recvData.size();i++)
//    {
//        buf[i] = (quint8)recvData.at(i);
//    };
//    if (recvData.size() < recvLen)
//    {
//        return false;

//    };
//    // 校验CRC
//    quint16 recvCrc = (recvData.at(recvLen-1) << 8) | recvData.at(recvLen-2);
//    quint16 calcCrc = calcModbusCrc((uint8_t*)recvData.constData(), recvLen-2);
//    if (recvCrc != calcCrc) {
//        qCritical() << "CRC校验错误";
//        return false;
//    }

//    // 解析数据
//    int dataLen = recvData.at(2);
//    for (int i = 0; i < dataLen; i += 2) {
//        quint16 val = (recvData.at(3+i) << 8) | recvData.at(4+i);
//        result.append(val);
//    }

//    return true;
}

// ====================== 读输入寄存器 ======================
bool SpiModbusMaster::readInputRegisters(quint8 slaveAddr, quint16 regAddr, quint16 regNum, QVector<quint16> &result)
{
    result.clear();
    QByteArray frame;
    frame.append(slaveAddr);
    frame.append(ReadInputRegisters);
    frame.append((regAddr >> 8) & 0xFF);
    frame.append(regAddr & 0xFF);
    frame.append((regNum >> 8) & 0xFF);
    frame.append(regNum & 0xFF);

    quint16 crc = calcModbusCrc((uint8_t*)frame.constData(), frame.size());
    frame.append(crc & 0xFF);
    frame.append((crc >> 8) & 0xFF);

    int recvLen = 5 + 2 * regNum;
    QByteArray recvData;

    if (!sendModbusFrame(frame, recvData, recvLen) || recvData.size() < recvLen)
        return false;

    quint16 recvCrc = (recvData.at(recvLen-1) << 8) | recvData.at(recvLen-2);
    quint16 calcCrc = calcModbusCrc((uint8_t*)recvData.constData(), recvLen-2);
    if (recvCrc != calcCrc) return false;

    int dataLen = recvData.at(2);
    for (int i = 0; i < dataLen; i += 2) {
        quint16 val = (recvData.at(3+i) << 8) | recvData.at(4+i);
        result.append(val);
    }
    return true;
}

// ====================== 写单个寄存器 ======================
bool SpiModbusMaster::writeSingleRegister(quint8 slaveAddr, quint16 regAddr, quint16 value)
{
    QByteArray frame;
    frame.append(slaveAddr);
    frame.append(WriteSingleRegister);
    frame.append((regAddr >> 8) & 0xFF);
    frame.append(regAddr & 0xFF);
    frame.append((value >> 8) & 0xFF);
    frame.append(value & 0xFF);

    quint16 crc = calcModbusCrc((uint8_t*)frame.constData(), frame.size());
    frame.append(crc & 0xFF);
    frame.append((crc >> 8) & 0xFF);

    QByteArray recvData;
    if (!sendModbusFrame(frame, recvData, 8) || recvData.size() < 8)
        return false;

    quint16 recvCrc = (recvData.at(7) << 8) | recvData.at(6);
    quint16 calcCrc = calcModbusCrc((uint8_t*)recvData.constData(), 6);
    return recvCrc == calcCrc;
}

// ====================== 写多个寄存器 ======================
bool SpiModbusMaster::writeMultipleRegisters(quint8 slaveAddr, quint16 startAddr, const QVector<quint16> &values)
{
    if (values.isEmpty()) return false;
    int regNum = values.size();

    QByteArray frame;
    frame.append(slaveAddr);
    frame.append(WriteMultipleRegisters);
    frame.append((startAddr >> 8) & 0xFF);
    frame.append(startAddr & 0xFF);
    frame.append((regNum >> 8) & 0xFF);
    frame.append(regNum & 0xFF);
    frame.append(regNum * 2);

    for (quint16 val : values) {
        frame.append((val >> 8) & 0xFF);
        frame.append(val & 0xFF);
    }

    quint16 crc = calcModbusCrc((uint8_t*)frame.constData(), frame.size());
    frame.append(crc & 0xFF);
    frame.append((crc >> 8) & 0xFF);

    QByteArray recvData;
    if (!sendModbusFrame(frame, recvData, 8) || recvData.size() < 8)
        return false;

    quint16 recvCrc = (recvData.at(7) << 8) | recvData.at(6);
    quint16 calcCrc = calcModbusCrc((uint8_t*)recvData.constData(), 6);
    return recvCrc == calcCrc;
}
