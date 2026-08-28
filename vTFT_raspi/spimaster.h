#ifndef SPIMASTER_H
#define SPIMASTER_H


//#include <QObject>
//#include <QDebug>
//#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <linux/spi/spidev.h>
//#include <unistd.h>
//#include <cstring>
//#include <QTimer>


//class SpiMaster : public QObject
//{
//    Q_OBJECT
//public:
//    explicit SpiMaster(QObject *parent = nullptr);
//    ~SpiMaster();

//     bool openSpi(const char *device = "/dev/spidev0.0", uint32_t speed = 1000000);
//    QByteArray transfer(const QByteArray &sendData);
//    void closeSpi();

//private:
//    int spiFd;
//    uint8_t spiMode;
//    uint8_t bitsPerWord;
//    uint32_t maxSpeed;
//};

#include <QCoreApplication>
#include <QDebug>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <cstring>

// SPI设备节点（根据实际硬件调整）
#define SPI_DEVICE "/dev/spidev0.0"
// SPI配置参数
#define SPI_MODE SPI_MODE_0  // CPOL=0, CPHA=0
#define SPI_BITS_PER_WORD 8
#define SPI_SPEED 10000000    // 10MHz（需与STM32匹配）

// 指令定义（主从约定）
#define CMD_READ_DATA 0x01   // 读取数据指令
#define CMD_WRITE_DATA 0x02  // 写入数据指令
#define CMD_ACK 0x0A         // 应答指令

class SpiMaster : public QObject
{
    Q_OBJECT
public:
    explicit SpiMaster(QObject *parent = nullptr);

    // 初始化SPI
    bool init() ;
    // SPI读写（全双工，发送len字节同时接收len字节）
    bool transfer(uint8_t *txBuf, uint8_t *rxBuf, int len);

    // 发送指令并接收响应
    bool sendCmdAndRecv(uint8_t cmd, uint8_t *recvData, int recvLen);

    ~SpiMaster();

private:
    int spiFd;  // SPI文件描述符
};


#endif // SPIMASTER_H
