#ifndef __SPLC_SMBUS_H__
#define __SPLC_SMBUS_H__
/****************************************************************************/
#include "stm32f4xx_hal.h"
#include "stdbool.h"
#include "libcpu.h"
#include "sPlcConfig.h"
#include "boardConfig.h"
#include "AppConfig.h"
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
typedef enum{// DAC5578 通道枚举（8路通道 A~H）
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

typedef enum{// DAC5578 掉电模式枚举
	DAC5578_PWR_ON          = 0U,    // 正常工作
	DAC5578_PWR_DOWN_1K     = 1U,    // 掉电，输出接1kΩ到GND
	DAC5578_PWR_DOWN_100K   = 2U,    // 掉电，输出接100kΩ到GND
	DAC5578_PWR_DOWN_HIZ    = 3U     // 掉电，输出高阻
} DAC5578_PowerModeTypeDef;

typedef enum{// 函数状态返回值
	DAC5578_OK      = 0U,
	DAC5578_ERROR   = 1U,
	DAC5578_TIMEOUT = 2U
} DAC5578_StatusTypeDef;

/*****************************************************************************/
DAC5578_StatusTypeDef DAC5578_Init(void);//DAC5578 硬件初始化（I2C自检+软件复位）
DAC5578_StatusTypeDef DAC5578_SetChannel(DAC5578_ChannelTypeDef ch, uint8_t data);//设置单通道DAC输出值（8位数据 0~255）
DAC5578_StatusTypeDef DAC5578_SetMultiChannel(DAC5578_ChannelTypeDef ch, uint8_t *pData, uint8_t len);//批量设置多路DAC通道
DAC5578_StatusTypeDef DAC5578_SetPowerMode(DAC5578_ChannelTypeDef ch, DAC5578_PowerModeTypeDef mode);// 设置指定通道掉电/正常模式
DAC5578_StatusTypeDef DAC5578_SoftReset(void);//DAC5578 软件复位（恢复上电默认状态）
DAC5578_StatusTypeDef DAC5578_ReadChannel(DAC5578_ChannelTypeDef ch, uint8_t *pData);//读取指定通道DAC寄存器数值
/*****************************************************************************/
HAL_StatusTypeDef PCA9546_HardwareReset(void);//PCA9546硬件复位（低电平复位，延时后释放）
HAL_StatusTypeDef PCA9546_Init(void);//PCA9546整体初始化（先复位引脚初始化→硬件复位→通道复位）
HAL_StatusTypeDef PCA9546_SelectChannel(uint8_t channel);//选择PCA9546的指定通道
HAL_StatusTypeDef PCA9546_ReadChannel(uint8_t *pChannel);//读取PCA9546当前选中的通道
/******************************************************************************/	
	
#ifdef __cplusplus
}
#endif

#endif





