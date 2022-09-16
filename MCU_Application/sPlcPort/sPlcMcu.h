#ifndef __SPLCMCU_H__
#define __SPLCMCU_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
/*****************************************************************************/
void initWatchDog(void);
void enableWatchDog(void);
void disableWatchDog(void);
void feedWatchDog(void);
void mucReboot(void);
#endif



