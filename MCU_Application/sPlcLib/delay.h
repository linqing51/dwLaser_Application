#ifndef __DELAY_H__
#define __DELAY_H__
/*****************************************************************************/
#include "lib.h"
#include "sPlc.h"
/*****************************************************************************/
void delayMs(uint16_t ms) reentrant;
void delayUs(uint16_t us) reentrant;
/*****************************************************************************/
#endif
