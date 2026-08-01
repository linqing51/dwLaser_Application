#ifndef __HMILIB_H__
#define __HMILIB_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "sPlc.h"
#include "hmiCmdQueue.h"
#include "hmiDriver.h"
#include "hmiCmdProcess.h"
/*****************************************************************************/
extern void hmiUartSendChar(uint8_t t);
extern void hmiUartInit(void);
extern void hmiUartErrorReset(void);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif





