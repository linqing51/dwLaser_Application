#ifndef __LIBCPU_H__
#define __LIBCPU_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
#include "boardConfig.h"
/*****************************************************************************/
extern uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
extern uint16_t cpuGetFlashSize(void);
extern void readStm32UniqueID(void);
#endif



