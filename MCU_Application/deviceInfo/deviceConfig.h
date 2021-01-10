#ifndef __DEVICECONFIG_H__
#define __DEVICECONFIG_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
#include "arm_math.h"
/*****************************************************************************/
typedef struct{
	char serialNumber[32];//序列号
	char dateOfManufacture[32];//生产日期
	//进行3次多项式拟合Y = A*X^3 + B*X^2 + C*X + D
	float32_t laserNotesIntercept[5];//D
	float32_t laserNotesB1[5];//C
	float32_t laserNotesB2[5];//B
	float32_t laserNotesB3[5];//A
	uint16_t crc;
}deviceConfig_t;

typedef struct{
	uint32_t bootLoaderCrc;//引导程序校验码
	uint32_t mucAppCrc;//应用程序校验码
	uint32_t lcdAppCrc;//触摸屏程序校验码
}firmwareInfo_t;//固件信息

typedef struct{
	uint32_t powerUpCycle;//开机次数
	uint32_t runTime;//运行累计时间 单位分钟
	uint32_t laserOnTime[5];//激光发射累计时间 单位秒
	int16_t laserMaxTemper;//激光器最大温度
	int16_t laserMinTemper;//激光器最低温度
	int16_t laserMaxCurrent[5];//激光器最大电流
	int16_t laserMaxPhotoDiode;//激光器最大功率
	int16_t mucMaxTemper;//处理器最高温度
	int16_t mucMinTemper;//处理器最低温度
}deviceLogInfo_t;
/*****************************************************************************/
extern deviceConfig_t deviceConfig;
extern firmwareInfo_t firmwareInfo;//固件信息
extern deviceLogInfo_t deviceLogInfo;
extern uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
extern uint16_t cpuGetFlashSize(void);
extern void readStm32UniqueID(void);
#endif



