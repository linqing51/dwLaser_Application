#ifndef __DEVICECONFIG_H__
#define __DEVICECONFIG_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
typedef float						fp32_t;
typedef double						fp64_t;
/*****************************************************************************/
typedef struct{
	uint8_t serialNumber[16];//序列号
	uint32_t bootLoaderVer;//引导程序版本
	uint32_t bootLoaderCrc;//引导程序校验码
	uint32_t mucAppVer;//应用程序版本
	uint32_t mucAppCrc;//应用程序校验码
	uint32_t lcdAppVer;//触摸屏程序版本
	uint32_t lcdAppCrc;//触摸屏程序校验码
	//进行3次多项式拟合Y = A*X^3 + B*X^2 + C*X + D
	fp32_t laserNotesIntercept[8];//D
	fp32_t laserNotesB1[8];//C
	fp32_t laserNotesB2[8];//B
	fp32_t laserNotesB3[8];//A
	int16_t laserLimitPower[8];//功率限制
	uint16_t checkSum;//配置文件校正码
}deviceConfig_t;
/*****************************************************************************/
extern deviceConfig_t myDeviceConfig;
extern deviceConfig_t defaultDeviceConfig;//默认配置参数
/*****************************************************************************/
#endif



