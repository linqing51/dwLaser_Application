#ifndef __SPLC_DAC5578_H__
#define __SPLC_DAC5578_H__
/*****************************************************************************/
#include "stm32hal.h"   // 统一引入HAL库头文件，移植根据实际修改
#include "stm32xx_hal_i2c.h"
/************************* 移植区 - 仅修改此处 *************************/
// 1. 硬件I2C句柄（根据实际硬件修改，如 hi2c1 / hi2c2）
#define DAC5578_HI2C        &hi2c1

// 2. DAC5578 I2C 7位从地址（TSSOP-16封装，ADDR0配置）
// ADDR0 = GND  : 0x48 (1001000)
// ADDR0 = VDD  : 0x4A (1001010)
// ADDR0 = 悬空 : 0x4C (1001100)
#define DAC5578_DEV_ADDR    0x48U

// 3. I2C 读写地址转换（HAL库I2C 8位地址规则）
#define DAC5578_WR_ADDR     (DAC5578_DEV_ADDR << 1U)
#define DAC5578_RD_ADDR     ((DAC5578_DEV_ADDR << 1U) | 0x01U)

// 4. I2C 超时（硬件I2C超时，单位ms，无系统延时依赖）
#define DAC5578_I2C_TIMEOUT 100U
/*********************************************************************/

// DAC5578 通道枚举（8路通道 A~H）
typedef enum
{
    DAC5578_CH_A = 0U,
    DAC5578_CH_B,
    DAC5578_CH_C,
    DAC5578_CH_D,
    DAC5578_CH_E,
    DAC5578_CH_F,
    DAC5578_CH_G,
    DAC5578_CH_H,
    DAC5578_CH_ALL  // 全部通道（广播）
} DAC5578_ChannelTypeDef;

// DAC5578 掉电模式枚举
typedef enum
{
    DAC5578_PWR_ON          = 0U,    // 正常工作
    DAC5578_PWR_DOWN_1K     = 1U,    // 掉电，输出接1kΩ到GND
    DAC5578_PWR_DOWN_100K   = 2U,    // 掉电，输出接100kΩ到GND
    DAC5578_PWR_DOWN_HIZ    = 3U     // 掉电，输出高阻
} DAC5578_PowerModeTypeDef;

// 函数状态返回值
typedef enum
{
    DAC5578_OK      = 0U,
    DAC5578_ERROR   = 1U,
    DAC5578_TIMEOUT = 2U
} DAC5578_StatusTypeDef;

/************************* 函数声明 *************************/
/**
 * @brief  DAC5578 硬件初始化（I2C自检+软件复位）
 * @retval 执行状态
 */
DAC5578_StatusTypeDef DAC5578_Init(void);

/**
 * @brief  设置单通道DAC输出值（8位数据 0~255）
 * @param  ch: 通道号
 * @param  data: 输出数值(0~255)
 * @retval 执行状态
 */
DAC5578_StatusTypeDef DAC5578_SetChannel(DAC5578_ChannelTypeDef ch, uint8_t data);

/**
 * @brief  批量设置多路DAC通道
 * @param  ch: 起始通道
 * @param  pData: 数据缓冲区指针
 * @param  len: 通道数量
 * @retval 执行状态
 */
DAC5578_StatusTypeDef DAC5578_SetMultiChannel(DAC5578_ChannelTypeDef ch, uint8_t *pData, uint8_t len);

/**
 * @brief  设置指定通道掉电/正常模式
 * @param  ch: 通道号
 * @param  mode: 电源模式
 * @retval 执行状态
 */
DAC5578_StatusTypeDef DAC5578_SetPowerMode(DAC5578_ChannelTypeDef ch, DAC5578_PowerModeTypeDef mode);

/**
 * @brief  DAC5578 软件复位（恢复上电默认状态）
 * @retval 执行状态
 */
DAC5578_StatusTypeDef DAC5578_SoftReset(void);

/**
 * @brief  读取指定通道DAC寄存器数值
 * @param  ch: 通道号
 * @param  pData: 读取数据缓冲区
 * @retval 执行状态
 */
DAC5578_StatusTypeDef DAC5578_ReadChannel(DAC5578_ChannelTypeDef ch, uint8_t *pData);

#endif