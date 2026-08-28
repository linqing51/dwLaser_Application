#include "i2cmaster.h"

I2CMaster::I2CMaster(const QString &i2cDevice, QObject *parent)
    : QObject(parent), m_i2cDevice(i2cDevice), m_i2cFd(-1), m_isOpen(false)
{
    // 打开I2C设备文件（O_RDWR：读写模式）
    m_i2cFd = open(m_i2cDevice.toUtf8().data(), O_RDWR);
    if (m_i2cFd < 0) {
        qCritical() << "I2C设备打开失败：" << m_i2cDevice
                    << "错误原因：" << strerror(errno);
        m_isOpen = false;
    } else {
        qInfo() << "I2C设备打开成功：" << m_i2cDevice;
        m_isOpen = true;
    }
}

I2CMaster::~I2CMaster()
{
    // 析构时关闭I2C设备
    if (m_i2cFd >= 0) {
        close(m_i2cFd);
        m_isOpen = false;
        qInfo() << "I2C设备已关闭";
    }
}

bool I2CMaster::setSlaveAddress(quint8 address)
{
    if (!m_isOpen) {
        qWarning() << "I2C设备未打开，无法设置从机地址";
        return false;
    }
    // 通过ioctl设置I2C从机地址
    if (ioctl(m_i2cFd, I2C_SLAVE, address) < 0) {
        qCritical() << "设置从机地址失败（地址：0x" << QString::number(address, 16) << "）"
                    << "错误原因：" << strerror(errno);
        return false;
    }
    qInfo() << "I2C从机地址设置成功：0x" << QString::number(address, 16);
    return true;
}

bool I2CMaster::writeData(const QByteArray &data)
{
    if (!m_isOpen || data.isEmpty()) {
        qWarning() << "I2C写操作失败：设备未打开或写入数据为空";
        return false;
    }
    // 向I2C设备写入数据
    ssize_t ret = write(m_i2cFd, data.constData(), data.length());
    if (ret != data.length()) {
        qCritical() << "I2C写数据失败，期望写入" << data.length()
                    << "字节，实际写入" << ret << "字节"
                    << "错误原因：" << strerror(errno);
        return false;
    }
    qDebug() << "I2C写数据成功：" << data.toHex(' ').toUpper();
    return true;
}

QByteArray I2CMaster::readData(quint8 length)
{
    if (!m_isOpen || length == 0) {
        qWarning() << "I2C读操作失败：设备未打开或读取长度为0";
        return QByteArray();
    }
    QByteArray data(length, 0);
    // 从I2C设备读取数据
    ssize_t ret = read(m_i2cFd, data.data(), length);
    if (ret != length) {
        qCritical() << "I2C读数据失败，期望读取" << length
                    << "字节，实际读取" << ret << "字节"
                    << "错误原因：" << strerror(errno);
        return QByteArray();
    }
    qDebug() << "I2C读数据成功：" << data.toHex(' ').toUpper();
    return data;
}

bool I2CMaster::writeRegister(quint8 regAddr, quint8 value)
{
    // 寄存器写：先写寄存器地址，再写值（合并为1个字节数组）
    QByteArray data;
    data.append(regAddr);
    data.append(value);
    return writeData(data);
}

quint8 I2CMaster::readRegister(quint8 regAddr)
{
    // 寄存器读：先写寄存器地址，再读1个字节
    if (!writeData(QByteArray(1, regAddr))) {
        qWarning() << "写入寄存器地址失败，无法读取寄存器：0x" << QString::number(regAddr, 16);
        return 0xff; // 错误返回值
    }
    QByteArray data = readData(1);
    return data.isEmpty() ? 0xff : static_cast<quint8>(data.at(0));
}

bool I2CMaster::isOpen() const
{
    return m_isOpen;
}



