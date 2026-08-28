#ifndef GPIOQUERYINPUT_H
#define GPIOQUERYINPUT_H

#include <QObject>
#include <gpiod.h>
#include <QString>

// 类名修改为GpioQueryInput
class GpioQueryInput : public QObject
{
    Q_OBJECT
public:
    // 构造函数：chipName=GPIO芯片名（如"gpiochip0"），lineOffset=GPIO偏移量（如27）
    explicit GpioQueryInput(const char *chipName = "gpiochip0", int lineOffset = 27, QObject *parent = nullptr);
    ~GpioQueryInput();

    bool initInput();
    // 查询GPIO输入电平：返回true=高电平，false=低电平，失败返回false
    bool getGpioLevel();

    // 检查GPIO初始化是否成功
    bool isInitSuccess() const { return m_initSuccess; }
    bool m_initSuccess = false;            // 初始化状态

private:
    struct gpiod_chip *m_chip;   // GPIO芯片句柄
    struct gpiod_line *m_line;   // GPIO线路句柄
    const char *m_chipName;       // 芯片名称
    int m_lineNum;                // BCM编号
    bool m_isInit;                // 是否已初始化

};

#endif // GPIOQUERYINPUT_H

