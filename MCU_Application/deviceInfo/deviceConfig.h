#ifndef __DEVICECONFIG_H__
#define __DEVICECONFIG_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
//#include "arm_math.h"
/*****************************************************************************/
typedef struct{
	uint16_t calibrationPwr0[10];//通道0功率校正表
	uint16_t calibrationPwr1[10];//通道1功率校正表
	uint16_t calibrationPwr2[10];//通道2功率校正表
	uint16_t calibrationPwr3[10];//通道3功率校正表
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



