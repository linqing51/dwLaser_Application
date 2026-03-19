#ifndef __HDC1080_H
#define __HDC1080_H

#include "stm32f4xx_hal.h"

/************************模拟I2C引脚定义************************/
// 请根据你的硬件连接修改以下引脚定义
#define HDC1080_I2C_SCL_GPIO_PORT    GPIOG
#define HDC1080_I2C_SCL_PIN         GPIO_PIN_14
#define HDC1080_I2C_SDA_GPIO_PORT    GPIOG
#define HDC1080_I2C_SDA_PIN         GPIO_PIN_13

/************************HDC1080设备地址************************/
#define HDC1080_ADDR                0x40 << 1  // I2C地址左移一位（HAL库格式）

/************************HDC1080寄存器地址************************/
#define HDC1080_TEMP_REG            0x00        // 温度寄存器
#define HDC1080_HUMI_REG            0x01        // 湿度寄存器
#define HDC1080_CONFIG_REG          0x02        // 配置寄存器


typedef struct
{
   float temp; 
   float humi; 
} hdc1080_TypeDef;

extern  hdc1080_TypeDef hdc1080_buf;



/************************函数声明************************/
// 模拟I2C底层操作函数
void HDC1080_I2C_Init(void);                  // 初始化模拟I2C引脚
void HDC1080_I2C_Start(void);                 // I2C起始信号
void HDC1080_I2C_Stop(void);                  // I2C停止信号
void HDC1080_I2C_SendAck(uint8_t ack);        // 发送应答信号
uint8_t HDC1080_I2C_WaitAck(void);            // 等待应答信号
void HDC1080_I2C_SendByte(uint8_t data);      // 发送一个字节
uint8_t HDC1080_I2C_ReadByte(uint8_t ack);    // 读取一个字节

// HDC1080核心驱动函数
uint8_t HDC1080_Init(void);                   // 初始化HDC1080
void HDC1080_Read_Temp_Humi(float *temp, float *humi); // 读取温湿度

// 引脚操作宏定义
#define HDC1080_SCL_HIGH()  HAL_GPIO_WritePin(HDC1080_I2C_SCL_GPIO_PORT, HDC1080_I2C_SCL_PIN, GPIO_PIN_SET)
#define HDC1080_SCL_LOW()   HAL_GPIO_WritePin(HDC1080_I2C_SCL_GPIO_PORT, HDC1080_I2C_SCL_PIN, GPIO_PIN_RESET)
#define HDC1080_SDA_HIGH()  HAL_GPIO_WritePin(HDC1080_I2C_SDA_GPIO_PORT, HDC1080_I2C_SDA_PIN, GPIO_PIN_SET)
#define HDC1080_SDA_LOW()   HAL_GPIO_WritePin(HDC1080_I2C_SDA_GPIO_PORT, HDC1080_I2C_SDA_PIN, GPIO_PIN_RESET)
#define HDC1080_SDA_READ()  HAL_GPIO_ReadPin(HDC1080_I2C_SDA_GPIO_PORT, HDC1080_I2C_SDA_PIN)

#endif
