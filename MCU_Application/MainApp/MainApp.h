#ifndef __MAINAPP_H__
#define __MAINAPP_H__

#include "main.h"
#include "adc.h"
#include "crc.h"
#include "i2c.h"
#include "rng.h"
#include "usart.h"
#include "gpio.h"


#include "stdio.h"
#include "string.h"
#include "dac8568.h"





typedef struct{//自由协议命令
	uint8_t rcvNum;//已接受的字节数
	uint8_t sendNum;//需发送的字节数
	uint8_t rcvBuf[256];
	uint8_t sendBuf[256];
	uint8_t *pRcvReadIndex;   
	uint8_t *pRcvWriteIndex;
	int8_t flagRcvDone;
	int8_t flagRcving;
	int8_t flagSendDone;
	int8_t flagSending;
}cmdQueue_t;

typedef struct{//状态
	int8_t alarm;//故障报警
	float readChipTemper;//处理器温度
	float readLaserTemper;//激光器温度
	uint16_t readLaserPd[2];//激光器PD
	uint16_t readLaserCur[2];//采集激光器电流
	uint16_t writeLaserCur[2];//设置激光器电流
	uint16_t writeLaserPwm[2];//激光器调制占空比
	int8_t writeLaserAim[2];//激光器指示光
	uint32_t writeLaserOnTime;//激光发射时间
	uint32_t timerStart;//激光计时器开始时间
	uint32_t timerEnd;//j激光计时器结束时间
}laserConfig_t;

typedef struct{
	uint8_t start;
	uint32_t mate;//匹配值
	uint32_t counter;//计数器
}softTimer_t;


void mainApp(void);
#endif






