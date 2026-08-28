//#include "spimaster.h"
//#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <linux/spi/spidev.h>
//#include <unistd.h>
//#include <QDebug>


//SpiMaster::SpiMaster(QObject *parent) : QObject(parent)
//{
//    spiFd = -1;
//    spiMode = SPI_MODE_0;
//    bitsPerWord = 8;
//    maxSpeed = 1000000;
//}

//SpiMaster::~SpiMaster()
//{
//    closeSpi();
//}

//bool SpiMaster::openSpi(const char *device, uint32_t speed)
//{
//    // 关闭已打开的SPI
//    if (spiFd >= 0) {
//        closeSpi();
//    }

//    // 打开SPI设备文件（O_RDWR：读写模式）
//    spiFd = open(device, O_RDWR);
//    if (spiFd < 0) {
//        qDebug() << "打开SPI失败：权限不足或设备不存在" << strerror(errno);
//        return false;
//    }

//    // 设置SPI模式
//    if (ioctl(spiFd, SPI_IOC_WR_MODE, &spiMode) < 0) {
//        qDebug() << "设置SPI模式失败：" << strerror(errno);
//        closeSpi();
//        return false;
//    }

//    // 设置数据位
//    if (ioctl(spiFd, SPI_IOC_WR_BITS_PER_WORD, &bitsPerWord) < 0) {
//        qDebug() << "设置数据位失败：" << strerror(errno);
//        closeSpi();
//        return false;
//    }

//    // 设置波特率
//    maxSpeed = speed;
//    if (ioctl(spiFd, SPI_IOC_WR_MAX_SPEED_HZ, &maxSpeed) < 0) {
//        qDebug() << "设置波特率失败：" << strerror(errno);
//        closeSpi();
//        return false;
//    }

//    qDebug() << "SPI设备打开成功：" << device << "波特率：" << maxSpeed;
//    return true;
//}

//QByteArray SpiMaster::transfer(const QByteArray &sendData)
//{
//    if (spiFd < 0 || sendData.isEmpty()) {
//        return QByteArray();
//    }

//    int len = sendData.length();
//    uint8_t *txBuf = new uint8_t[len];
//    uint8_t *rxBuf = new uint8_t[len];
//    memset(rxBuf, 0, len);
//    memcpy(txBuf, sendData.data(), len);

//    // SPI传输结构体
//    struct spi_ioc_transfer tr = {
//        .tx_buf = (unsigned long)txBuf,
//        .rx_buf = (unsigned long)rxBuf,
//        .len = len,
//        .speed_hz = maxSpeed,
//        .delay_usecs = 0,
//        .bits_per_word = bitsPerWord,
//        .cs_change = 0,
//        .tx_nbits = 0,
//        .rx_nbits = 0,
//        .word_delay_usecs = 0,
//        .pad = 0,

//    };

//    // 执行SPI传输
//    int ret = ioctl(spiFd, SPI_IOC_MESSAGE(1), &tr);
//    QByteArray recvData;
//    if (ret >= 0) {
//        recvData = QByteArray((char *)rxBuf, len);
//    } else {
//        qDebug() << "SPI传输失败：" << strerror(errno);
//    }

//    // 释放内存
//    delete[] txBuf;
//    delete[] rxBuf;
//    return recvData;
//}

//void SpiMaster::closeSpi()
//{
//    if (spiFd >= 0) {
//        close(spiFd);
//        spiFd = -1;
//    }
//}


#include "spimaster.h"

SpiMaster:: SpiMaster(QObject *parent) : QObject(parent)
  ,spiFd(-1)
{

}

bool SpiMaster::init() {
    // 打开SPI设备
    spiFd = open(SPI_DEVICE, O_RDWR);
    if (spiFd < 0) {
        qCritical() << "打开SPI设备失败：" << strerror(errno);
        return false;
    }

    // 设置SPI模式
    uint8_t mode = SPI_MODE;
    if (ioctl(spiFd, SPI_IOC_WR_MODE, &mode) < 0) {
        qCritical() << "设置SPI模式失败：" << strerror(errno);
        close(spiFd);
        return false;
    }

    // 设置每字位数
    uint8_t bits = SPI_BITS_PER_WORD;
    if (ioctl(spiFd, SPI_IOC_WR_BITS_PER_WORD, &bits) < 0) {
        qCritical() << "设置位宽失败：" << strerror(errno);
        close(spiFd);
        return false;
    }

    // 设置时钟频率
    uint32_t speed = SPI_SPEED;
    if (ioctl(spiFd, SPI_IOC_WR_MAX_SPEED_HZ, &speed) < 0) {
        qCritical() << "设置速度失败：" << strerror(errno);
        close(spiFd);
        return false;
    }

    qInfo() << "SPI初始化成功，速度：" << speed << "Hz";
    return true;
}

// SPI读写（全双工，发送len字节同时接收len字节）
bool SpiMaster::transfer(uint8_t *txBuf, uint8_t *rxBuf, int len) {
    struct spi_ioc_transfer tr = {
        .tx_buf = (unsigned long)txBuf,
        .rx_buf = (unsigned long)rxBuf,
        .len = len,
        .speed_hz = SPI_SPEED,
        .delay_usecs = 0,
        .bits_per_word = SPI_BITS_PER_WORD,
        .cs_change = 0,  // 保持片选有效（主从一对一）
        .tx_nbits = 0,
        .rx_nbits = 0,
        .word_delay_usecs = 0,
        .pad = 0,
    };


    if (ioctl(spiFd, SPI_IOC_MESSAGE(1), &tr) < 0) {
        qCritical() << "SPI传输失败：" << strerror(errno);
        return false;
    }
    return true;
}

// 发送指令并接收响应
bool SpiMaster::sendCmdAndRecv(uint8_t cmd, uint8_t *recvData, int recvLen) {
    uint8_t txBuf[2048] = {0};
    uint8_t rxBuf[2048] = {0};
    txBuf[0] = cmd;  // 第一个字节为指令
    txBuf[1] = 0x02;
    txBuf[2] = 0x03;
    txBuf[3] = 0x04;
   // 全双工传输（发送指令+占位，同时接收响应）
    if (!transfer(txBuf, rxBuf, recvLen)) {
        return false;
    }

    // 拷贝响应数据
    memcpy(recvData, rxBuf, recvLen);
    qInfo() << "发送指令：0x" << QString::number(cmd, 16)
            << "，接收响应：" << QByteArray((char*)rxBuf, recvLen).toHex();
    return true;
}

SpiMaster::~SpiMaster() {
    if (spiFd >= 0) {
        close(spiFd);
    }
}
