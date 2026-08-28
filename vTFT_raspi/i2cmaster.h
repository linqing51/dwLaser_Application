#ifndef I2CMASTER_H
#define I2CMASTER_H

#include <QObject>
#include <QFile>
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>

class I2CMaster : public QObject
{
    Q_OBJECT
public:
    // 构造函数：指定I2C设备路径（默认/dev/i2c-1对应GPIO2/3）和从机地址
    explicit I2CMaster(const QString &i2cDevice = "/dev/i2c-1", QObject *parent = nullptr);
    ~I2CMaster();

    // 设置I2C从机地址（必须在读写前调用）
    bool setSlaveAddress(quint8 address);

    // 基础写操作：向从机写入n个字节
    bool writeData(const QByteArray &data);

    // 基础读操作：从从机读取n个字节
    QByteArray readData(quint8 length);

    // 寄存器写操作：向指定寄存器写入1个字节
    bool writeRegister(quint8 regAddr, quint8 value);

    // 寄存器读操作：从指定寄存器读取1个字节
    quint8 readRegister(quint8 regAddr);

    // 检查I2C总线是否打开成功
    bool isOpen() const;

private:
    int m_i2cFd;          // I2C设备文件描述符
    QString m_i2cDevice;  // I2C设备路径
    bool m_isOpen;        // 设备是否打开成功
};

#endif // I2CMASTER_H


