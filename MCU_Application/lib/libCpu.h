#ifndef __LIBCPU_H__
#define __LIBCPU_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "stdio.h"
/* 按具体型号宏探测系列(工程编译选项定义); 若HAL未定义系列宏则在此补齐 */
#if defined(STM32F100xB)  || defined(STM32F100xE)  || defined(STM32F101x6) || \
    defined(STM32F101xB)  || defined(STM32F101xE)  || defined(STM32F101xG) || \
    defined(STM32F102x6)  || defined(STM32F102xB)  || defined(STM32F103x6) || \
    defined(STM32F103xB)  || defined(STM32F103xE)  || defined(STM32F103xG) || \
    defined(STM32F105xC)  || defined(STM32F107xC)
  #include "stm32f1xx_hal.h"
  #ifndef STM32F1xx
    #define STM32F1xx
  #endif
#elif defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
      defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
      defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || \
      defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) || \
      defined(STM32F479xx) || defined(STM32F412Cx) || defined(STM32F412Zx) || defined(STM32F412Rx) || \
      defined(STM32F412Vx) || defined(STM32F413xx) || defined(STM32F423xx)
  #include "stm32f4xx_hal.h"
  #ifndef STM32F4xx
    #define STM32F4xx
  #endif
#endif
#include "..\config\myConfig.h"
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



