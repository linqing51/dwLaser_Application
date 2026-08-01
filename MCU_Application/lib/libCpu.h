#ifndef __LIBCPU_H__
#define __LIBCPU_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "stdio.h"
#include "stm32f4xx_hal.h"
#include "myConfig.h"
#include "flash_if.h"
#include "libcrc.h"
/*****************************************************************************/
extern uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
extern uint16_t cpuGetFlashSize(void);
extern void readStm32UniqueID(void);
extern void softDelayMs(uint32_t ms);//软件延时
extern void softDelayUs(uint32_t us);//软件延时
extern void tickCheckTask(void);//TICK 检测程序
extern void morseCodeDiag(uint8_t diag);//蜂鸣器诊断声音 摩尔斯电码
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif



