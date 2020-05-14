#ifndef __MAINAPP_H__
#define __MAINAPP_H__
/*****************************************************************************/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
//#include "sPlc.h"
//#include "sPlcPort.h"
//#include "appSplcAdr.h"
#if CONFIG_USING_BACKGROUND_APP == 1
#include "backgroundApp.h"
#endif
#if CONFIG_USING_DCHMI_APP == 1
#include "dcHmiApp.h"
#endif
#if CONFIG_USING_USB_APP == 1
#include "usbApp.h"
#endif
void mainTask(void *pvParameters);

/*****************************************************************************/
#endif



