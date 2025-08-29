#ifndef __HMILIB_H__
#define __HMILIB_H__
/*****************************************************************************/
#include "sPlc.h"
#include "hmiCmdQueue.h"
#include "hmiDriver.h"
#include "hmiCmdProcess.h"
#include "boardConfig.h"
#include "appConfig.h"
/*****************************************************************************/
extern void hmiUartSendChar(uint8_t t);
extern void hmiUartInit(void);
extern void hmiUartErrorReset(void);
#endif





