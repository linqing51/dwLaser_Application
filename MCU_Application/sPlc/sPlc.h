#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "arm_math.h"
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <LIMITS.H>
#include <math.h>
#include "stdbool.h"
#include "stdint.h"
/*****************************************************************************/
#include "sPlcConfig.h"
#include "sPlcMisc.h"
#include "sPlcMcu.h"
#include "sPlcFun.h"
#include "sPlcTimer.h"
#include "sPlcLaser.h"
#if CONFIG_SPLC_USING_EPROM == 1
#include "sPlcEprom.h"
#endif
#if CONFIG_SPLC_USING_ADC == 1
#include "sPlcAdc.h"
#endif
#if CONFIG_SPLC_USING_DAC == 1
#include "sPlcDac.h"
#endif
#if CONFIG_USING_DCHMI_APP == 1
#include "dcHmiApp.h"
#endif
/*****************************************************************************/
#include "main.h"
//#include "sPlcPort.h"
//#include "debugLed.h"
#if CONFIG_SPLC_FUN_EPID == 1
#include "splcFunEPID.h"
#endif
#if CONFIG_SPLC_FUNTEST == 1
#include "sPlcTest.h"
#endif
/*****************************************************************************/
typedef float						fp32_t;
typedef double						fp64_t;
/*****************************************************************************/
extern int16_t NVRAM0[CONFIG_NVRAM_SIZE];//掉电保持寄存器 当前 包含存档寄存器
extern int16_t NVRAM1[CONFIG_NVRAM_SIZE];//掉电保持寄存器 上一次
extern int16_t FDRAM[CONFIG_FDRAM_SIZE];//存档寄存器
extern uint8_t TimerCounter_1mS;
extern uint8_t TimerCounter_10mS;
extern uint8_t TimerCounter_100mS;
extern uint8_t TD_10MS_SP;
extern uint8_t TD_100MS_SP;
extern uint8_t TD_1000MS_SP;
/*****************************************************************************/
void sPlcInit(void);//软逻辑初始化
void sPlcProcessStart(void);//sPLC轮询起始
void sPlcProcessEnd(void);//sPLC轮询结束
void sPlcPortProcess(void);//sPLC平台程序
/*****************************************************************************/
void assertCoilAddress(uint16_t adr);
void assertRegisterAddress(uint16_t adr);
/*****************************************************************************/
void clearX(void);
void clearY(void);
void clearDM(void);
void clearEM(void);
void clearR(void);
void clearT(void);
void clearTD(void);
void clearSPCOIL(void);
void clearSPREG(void);
/*****************************************************************************/
__weak void inputInit(void);
__weak void inputRefresh(void);
__weak void outputInit(void);
__weak void outputRefresh(void);
__weak void loadDefault(void);
__weak void enterSplcIsr(void);
__weak void exitSplcIsr(void);
__weak void disableSplcIsr(void);
__weak void enableSplcIsr(void);
__weak void updateNvram(void);//更新NVRAM->EPROM
__weak void clearNvram(void);//清除NVRAM数据	
__weak void loadNvram(void);
__weak void saveNvram(void);
__weak void loadFdram(void);
__weak void saveFdram(void);
__weak void mucReboot(void);//软件复位
__weak void setLed(uint8_t color, uint8_t state);//设置LED灯
/*****************************************************************************/
void sPlcInit(void);
/*****************************************************************************/
#endif
