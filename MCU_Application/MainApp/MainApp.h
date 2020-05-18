#ifndef __MAINAPP_H__
#define __MAINAPP_H__
/*****************************************************************************/
#include "sPlc.h"
#include "hmiLib.h"
#include "appSplcAdr.h"
//#if CONFIG_USING_BACKGROUND_APP == 1
//#include "backgroundApp.h"
//#endif
#if CONFIG_USING_DCHMI_APP == 1
#include "dcHmiApp.h"
#endif
/*****************************************************************************/
void mainAppTask(void *argument);
/*****************************************************************************/
#endif



