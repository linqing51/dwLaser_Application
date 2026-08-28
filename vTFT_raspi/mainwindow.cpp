#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QLabel>
#include <QMessageBox>
#include "QDebug"
#include <QThread>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),gpio("gpiochip0", 8,this),gpio1("gpiochip0", 27,this)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground, false);
    m1 = new menu1();
    m1->hide();
    m2 = new menu2();
    m2->hide();
    m3 = new menu3();
    m3->hide();
    m4 = new menu4();
    m4->hide();
    m5 = new menu5();
    m5->hide();

//    spi = new SpiMaster(this);
//    if (spi->openSpi("/dev/spidev0.0", 10000000)) {
//        QByteArray recv = spi->transfer(QByteArray::fromHex("010203"));
//        qDebug() << "receive:" << recv.toHex(' ');
//    };
//    spi->closeSpi();
//    qDebug() << "spi close";

//    if (!master.init()) {
//        qDebug() << "spi error";
//    }

//    // 测试：发送读取数据指令，接收1024字节响应
//    uint8_t recvData[2048] = {0};
//    if (master.sendCmdAndRecv(CMD_READ_DATA, recvData, 2048)) {
//        qInfo() << "接收数据：" << (int)recvData[0] << (int)recvData[1]
//                << (int)recvData[2] << (int)recvData[3];
//    }


    // CM5默认gpiochip0，控制BCM 18号GPIO

    // 初始化为输出模式
    if (!gpio.initOutput()) {
       qCritical() << "GPIO未初始化，无法读取电平";
    }


//    if (!modbusMaster.initSpi("/dev/spidev0.0", 5000000, SPI_MODE_0, 8)) {
//           qDebug() << "spi error";
//    }

    if (!modbusMaster.initSpi("/dev/spidev0.0", 2000000, SPI_MODE_0, 8)) {
           qDebug() << "spi error";
    }


     timer = new QTimer(this);
     QObject::connect(timer, &QTimer::timeout, [&]() {
         // 从站地址1，读取寄存器地址0，长度2
         if (modbusMaster.readHoldingRegisters(1, 0, 240, regData)) {
//             qDebug() << "读保持寄存器成功:" ;
             qDebug() << "读保持寄存器成功:" << regData;
         }
//         usleep(1000);
//         if (modbusMaster.readHoldingRegisters(1, 5, 100, regData)) {
////             qDebug() << "读保持寄存器成功:" ;
//             qDebug() << "读保持寄存器成功:" << regData;
//         }

         // 写单个寄存器：从站1，地址10，值1234
//         modbusMaster.writeSingleRegister(1, 10, 1234);

         // 写多个寄存器
//         modbusMaster.writeMultipleRegisters(1, 20, {111,222,333});

     });
     timer->start(100);







     // 创建自定义按钮
     customBtn_PROTOCOLS = new CustomImageButton(ui->centralWidget,340, 433);
     customBtn_PROTOCOLS->setLeaveImageRect(QRect(2000, 2500, 340, 433));
     customBtn_PROTOCOLS->setEnterImageRect(QRect(2000, 2500, 340, 433));
     customBtn_PROTOCOLS->setPressImageRect(QRect(0, 2500, 340, 433));
     customBtn_PROTOCOLS->setReleaseImageRect(QRect(2000, 2500, 340, 433));
     connect(customBtn_PROTOCOLS, &QPushButton::clicked, []() {
         qDebug() << "自定义按钮customBtn_PROTOCOLS被点击";
     });
     customBtn_PROTOCOLS->move(69,469);

     customBtn_OPERATION = new CustomImageButton(ui->centralWidget,340, 433);
     customBtn_OPERATION->setLeaveImageRect(QRect(2000, 2500, 340, 433));
     customBtn_OPERATION->setEnterImageRect(QRect(2000, 2500, 340, 433));
     customBtn_OPERATION->setPressImageRect(QRect(400, 2500, 340, 433));
     customBtn_OPERATION->setReleaseImageRect(QRect(2000, 2500, 340, 433));
     connect(customBtn_OPERATION, &QPushButton::clicked, []() {
         qDebug() << "自定义按钮customBtn_OPERATION被点击";
     });
     customBtn_OPERATION->move(429,469);

     customBtn_PATIENT_RECORD = new CustomImageButton(ui->centralWidget,340, 433);
     customBtn_PATIENT_RECORD->setLeaveImageRect(QRect(2000, 2500, 340, 433));
     customBtn_PATIENT_RECORD->setEnterImageRect(QRect(2000, 2500, 340, 433));
     customBtn_PATIENT_RECORD->setPressImageRect(QRect(800, 2500, 340, 433));
     customBtn_PATIENT_RECORD->setReleaseImageRect(QRect(2000, 2500, 340, 433));
     connect(customBtn_PATIENT_RECORD, &QPushButton::clicked, []() {
         qDebug() << "自定义按钮customBtn_PATIENT_RECORD被点击";
     });
     customBtn_PATIENT_RECORD->move(790,469);

     customBtn_RESOURCES = new CustomImageButton(ui->centralWidget,340, 433);
     customBtn_RESOURCES->setLeaveImageRect(QRect(2000, 2500, 340, 433));
     customBtn_RESOURCES->setEnterImageRect(QRect(2000, 2500, 340, 433));
     customBtn_RESOURCES->setPressImageRect(QRect(1200, 2500, 340, 433));
     customBtn_RESOURCES->setReleaseImageRect(QRect(2000, 2500, 340, 433));
     connect(customBtn_RESOURCES, &QPushButton::clicked, []() {
         qDebug() << "自定义按钮customBtn_RESOURCES被点击";
     });
     customBtn_RESOURCES->move(1151,469);

     CustomImageButton *customBtn_SETUP = new CustomImageButton(ui->centralWidget,340, 433);
     customBtn_SETUP->setLeaveImageRect(QRect(2000, 2500, 340, 433));
     customBtn_SETUP->setEnterImageRect(QRect(2000, 2500, 340, 433));
     customBtn_SETUP->setPressImageRect(QRect(1600, 2500, 340, 433));
     customBtn_SETUP->setReleaseImageRect(QRect(2000, 2500, 340, 433));
     connect(customBtn_SETUP, &QPushButton::clicked, []() {
         qDebug() << "自定义按钮customBtn_SETUP被点击";
     });
     customBtn_SETUP->move(1512,469);

     connect(m1, &menu1::switchToMain, this, &MainWindow::showmenu);
     connect(this, &MainWindow::switchTomenu1, m1, &menu1::showmenu);
     connect(m2, &menu2::switchToMain, this, &MainWindow::showmenu);
     connect(this, &MainWindow::switchTomenu2, m2, &menu2::showmenu);
     connect(m3, &menu3::switchToMain, this, &MainWindow::showmenu);
     connect(this, &MainWindow::switchTomenu3, m3, &menu3::showmenu);
     connect(m4, &menu4::switchToMain, this, &MainWindow::showmenu);
     connect(this, &MainWindow::switchTomenu4, m4, &menu4::showmenu);
     connect(m5, &menu5::switchToMain, this, &MainWindow::showmenu);
     connect(this, &MainWindow::switchTomenu5, m5, &menu5::showmenu);

     connect(customBtn_PROTOCOLS, &QPushButton::clicked, this, &MainWindow::CustomBtnPROTOCOLSTomenu1Clicked);
     connect(customBtn_OPERATION, &QPushButton::clicked, this, &MainWindow::CustomBtnOPERATIONTomenu1Clicked);
     connect(customBtn_PATIENT_RECORD, &QPushButton::clicked, this, &MainWindow::CustomBtnPATIENTRECORDTomenu1Clicked);
     connect(customBtn_RESOURCES, &QPushButton::clicked, this, &MainWindow::CustomBtnRESOURCESTomenu1Clicked);
     connect(customBtn_SETUP, &QPushButton::clicked, this, &MainWindow::CustomBtnSETUPTomenu1Clicked);



//     // CM5默认gpiochip0，控制BCM 18号GPIO

//     // 初始化为输出模式
//     if (!gpio.initOutput()) {
//        qCritical() << "GPIO未初始化，无法读取电平";
//     }

//     // 循环控制高低电平（间隔1秒）
//     for (int i = 0; i < 1; ++i) {
//         gpio.setValue(true);  // 高电平
//         QThread::msleep(10);

//         gpio.setValue(false); // 低电平
//         QThread::msleep(10);
//     }


     if (!gpio1.initInput()) {
        qCritical() << "GPIO未初始化，无法读取电平";
     }

//     // 自动查询：1秒刷新一次
//     QTimer *timer = new QTimer(this);
//     QObject::connect(timer, &QTimer::timeout, [&]() {
//         bool level = gpio1.getGpioLevel();
//         qCritical() << QString("当前GPIO电平：%1（%2）")
//                                       .arg(level ? "高电平" : "低电平")
//                                       .arg(level ? "1" : "0");
//     });
//     timer->start(1000);




//     // 获取串口管理实例
//     serialMgr = SerialPortManager::getInstance();

//     // 初始化串口（115200波特率，8N1）
//     if (!serialMgr->initSerialPort()) {
//         qCritical() << "串口0初始化失败，程序退出";
//     };

//     // 绑定数据接收信号（处理接收到的数据）
//     QObject::connect(serialMgr, &SerialPortManager::dataReceived, [](const QByteArray& data) {
//         qInfo() << "外部处理接收数据：" << data;
//         // 访问静态共享数据
//         QMutexLocker locker(&SerialPortManager::sharedDataMutex);
//         qInfo() << "静态共享数据：" << SerialPortManager::sharedSerialData;
//     });

//     // 测试：每隔1秒发送一次数据
//     QTimer *sendTimer0 = new QTimer(this);
//     QObject::connect(sendTimer0, &QTimer::timeout, [&]() {
//         SerialPortManager::getInstance()->sendData("Hello CM5 UART!\r\n");
////         qInfo() << "每隔1秒发送一次数据";
//     });
//     sendTimer0->start(1000);






//     // 连接信号（接收数据、状态、错误）
//     QObject::connect(&modbus, &ModbusUart4Master::readDataReady,
//                      [=](int slave, int addr, const QList<quint16> &vals) {
//         qDebug() << "从站" << slave << "地址" << addr << "数据:" << vals;
//     });

//     QObject::connect(&modbus, &ModbusUart4Master::modbusError,
//                      [=](const QString &err) {
//         qDebug() << "错误:" << err;
//     });

//     QObject::connect(&modbus, &ModbusUart4Master::connectStateChanged,
//                      [=](bool ok) {
//         qDebug() << "UART4连接状态:" << ok;
//     });

//     // 1. 连接UART4
//     if (modbus.connectUart4()) {
//         qDebug() << "UART4 打开成功";

//         // 2. 读取从站1，地址0，长度10
//         modbus.readHoldingRegisters(1, 0, 10);

//         // 3. 写入从站1，地址5，值0x1234
//          modbus.writeSingleRegister(1, 5, 0x1234);
//     } else {
//         qDebug() << "UART4 打开失败！";
//     }

//    QTimer *sendTimer = new QTimer(this);
//    QObject::connect(sendTimer, &QTimer::timeout, [&]() {
//        // 2. 读取从站1，地址0，长度10
//        modbus.readHoldingRegisters(1, 0, 10);

//    });
//    sendTimer->start(500);




     // 连接信号
     QObject::connect(&gpioInterrupt, &GpioInterrupt::interruptTriggered, [](int level) {
         qInfo() << "【中断触发】GPIO电平：" << level;
     });
     QObject::connect(&gpioInterrupt, &GpioInterrupt::errorOccurred, [](const QString& error) {
         qCritical() << "【错误】" << error;
     });

     bool initOk = gpioInterrupt.initialize("gpiochip0", 17, GpioEdge::BothEdges, "qt-gpio-interrupt");
     if (!initOk) {
         qCritical() << "GPIO中断初始化失败，程序退出";
     }





//     // 2. 检查设备是否打开成功
//     if (!i2c.isOpen()) {
//         qCritical() << "I2C初始化失败，程序退出";
//     }

//     // 3. 设置从机地址（示例：0x50，需替换为实际从机地址）
//     if (!i2c.setSlaveAddress(0x50)) {
//         qCritical() << "I2C设置从机地址失败，程序退出";
//     }

//     // 4. 示例1：向从机写入原始数据（如写入0x01 0x02）
//     QByteArray writeData;
//     writeData.append(0x01);
//     writeData.append(0x02);
//     i2c.writeData(writeData);

//     // 5. 示例2：向寄存器0x10写入值0x55
//     i2c.writeRegister(0x10, 0x55);

//     // 6. 示例3：从寄存器0x10读取值
//     quint8 regValue = i2c.readRegister(0x10);
//     qInfo() << "寄存器0x10读取值：0x" << QString::number(regValue, 16);

//     // 7. 示例4：从从机读取3个字节原始数据
//     QByteArray readData = i2c.readData(3);
//     if (!readData.isEmpty()) {
//         qInfo() << "读取原始数据：" << readData.toHex(' ').toUpper();
//     }




}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showmenu()
{
    this->show();
}

void MainWindow::CustomBtnPROTOCOLSTomenu1Clicked()
{
//    this->hide();
    emit switchTomenu1();
}

void MainWindow::CustomBtnOPERATIONTomenu1Clicked()
{
//    this->hide();
    emit switchTomenu2();
}

void MainWindow::CustomBtnPATIENTRECORDTomenu1Clicked()
{
//    this->hide();
    emit switchTomenu3();
}

void MainWindow::CustomBtnRESOURCESTomenu1Clicked()
{
//    this->hide();
    emit switchTomenu4();
}

void MainWindow::CustomBtnSETUPTomenu1Clicked()
{
//    this->hide();
    emit switchTomenu5();
}




