#ifndef __DEVICECONFIG_H__
#define __DEVICECONFIG_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
/*****************************************************************************/
typedef struct{
	uint16_t calibrationPwr0[10];//通道0功率校正表
	uint16_t calibrationPwr1[10];//通道1功率校正表
	char serialNumber[16];//序列号
	int16_t mfg_year;//生产年
	int16_t mfg_month;//生产月
	int16_t mfg_day;//生产日
	int8_t redLedDc;//红灯亮度
	int8_t greenLedDc;//绿灯亮度
	int8_t blueLedDc;//蓝灯亮度
}deviceConfig_t;

typedef struct{
	uint32_t powerUpCycle;//开机次数
	uint32_t runTime;//运行累计时间 单位分钟
	int16_t laserMaxPhotoDiode;//激光器最大功率
	int16_t mucMaxTemper;//处理器最高温度
}deviceLogInfo_t;
/*****************************************************************************/
extern deviceConfig_t deviceConfig;
extern deviceLogInfo_t deviceLogInfo;
extern uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
extern uint16_t cpuGetFlashSize(void);
extern void readStm32UniqueID(void);
#endif



