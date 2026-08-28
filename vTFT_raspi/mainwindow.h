#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "customimagebutton.h"
#include "menu1.h"
#include "menu2.h"
#include "menu3.h"
#include "menu4.h"
#include "menu5.h"
#include "spimaster.h"
#include <QMainWindow>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <unistd.h>
#include <cstring>
#include <pigpio.h> // 引入pigpio头文件
#include <gpiod.h>
#include "gpiocontrol.h"
#include "gpioqueryinput.h"
#include "gpiointerrupt.h"
#include "serialportmanager.h"
#include "i2cmaster.h"
#include "spimodbusmaster.h"
#include <QTimer>
#include "modbusuart4master.h"
#include <QThread>






// 定义要控制的IO口（树莓派CM5的BCM编号，不是物理引脚号）
#define CONTROL_PIN 18 // 示例：控制BCM 18号引脚

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QWidget *centralWidget;  // 中心窗口
    CustomImageButton *customBtn_PROTOCOLS;
    CustomImageButton *customBtn_OPERATION;
    CustomImageButton *customBtn_PATIENT_RECORD;
    CustomImageButton *customBtn_RESOURCES;
    CustomImageButton *customBtn_SETUP;
    menu1 *m1;
    menu2 *m2;
    menu3 *m3;
    menu4 *m4;
    menu5 *m5;

    SpiMaster master;
    SpiModbusMaster modbusMaster;
    GpioControl gpio;
    GpioQueryInput gpio1;
    SerialPortManager* serialMgr;
    GpioInterrupt gpioInterrupt;
    I2CMaster i2c;
    ModbusUart4Master modbus;

    QTimer *timer;
    QVector<quint16> regData;
//    SpiMaster *spi;

    // 初始化pigpio和IO口
    bool initPigpio();
    // 释放pigpio资源
    void releasePigpio();



// 定义切换信号
signals:
    void switchTomenu1();
    void switchTomenu2();
    void switchTomenu3();
    void switchTomenu4();
    void switchTomenu5();
private slots:
    void CustomBtnPROTOCOLSTomenu1Clicked();
    void CustomBtnOPERATIONTomenu1Clicked();
    void CustomBtnPATIENTRECORDTomenu1Clicked();
    void CustomBtnRESOURCESTomenu1Clicked();
    void CustomBtnSETUPTomenu1Clicked();
    void showmenu();
};

#endif // MAINWINDOW_H
