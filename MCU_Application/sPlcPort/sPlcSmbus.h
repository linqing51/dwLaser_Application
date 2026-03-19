#ifndef __SPLCSMBUS_H__ 
#define __SPLCSMBUS_H__

#include "stm32f4xx_hal.h"

/* ************************ 硬件配置 ************************ */
// I2C3 句柄（需在主函数或i2c.c中初始化）
extern I2C_HandleTypeDef hi2c3;

// PCA9546 I2C 设备地址（A0/A1/A2接地，7位地址0x70，HAL库左移1位）
#define PCA9546_DEV_ADDR    0x70 << 1  // 最终通信地址：0xE0

// PCA9546 复位引脚定义（PH13）
#define PCA9546_RESET_PORT  GPIOH
#define PCA9546_RESET_PIN   GPIO_PIN_13
#define PCA9546_RESET_LOW()  HAL_GPIO_WritePin(PCA9546_RESET_PORT, PCA9546_RESET_PIN, GPIO_PIN_RESET)
#define PCA9546_RESET_HIGH() HAL_GPIO_WritePin(PCA9546_RESET_PORT, PCA9546_RESET_PIN, GPIO_PIN_SET)

// PCA9546 通道定义
#define PCA9546_CHANNEL_0   0x01  // 选择通道0
#define PCA9546_CHANNEL_1   0x02  // 选择通道1
#define PCA9546_CHANNEL_2   0x04  // 选择通道2
#define PCA9546_CHANNEL_3   0x08  // 选择通道3
#define PCA9546_CHANNEL_ALL 0x0F  // 选择所有通道
#define PCA9546_CHANNEL_NONE 0x00 // 关闭所有通道

/* ************************ 函数声明 ************************ */
HAL_StatusTypeDef PCA9546_Init(void);                  // 整体初始化（含复位）
void PCA9546_Reset_GPIO_Init(void);                    // 复位引脚初始化
HAL_StatusTypeDef PCA9546_HardwareReset(void);         // 硬件复位
HAL_StatusTypeDef PCA9546_SelectChannel(uint8_t channel); // 选择通道
HAL_StatusTypeDef PCA9546_ReadChannel(uint8_t *pChannel);  // 读取通道状态
uint8_t PCA9546_Test(void);
#endif /* __PCA9546_H */



