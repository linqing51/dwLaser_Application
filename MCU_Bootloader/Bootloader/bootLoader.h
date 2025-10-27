#ifndef __DWLASER_BOOTLOADER_H__
#define __DWLASER_BOOTLOADER_H__
/*****************************************************************************/
#include "main.h"
#include "stdbool.h"
#include "stm32f4xx_hal.h"
#include "libcrc.h"
#include "stdio.h"
#include "string.h"
#include "stddef.h"
/*****************************************************************************/
#include "cmsis_armcc.h"
/*****************************************************************************/
#include "usbh_platform.h"
#include "usbh_core.h"
#include "usbh_msc.h"
#include "ff.h"
#include "ff_gen_drv.h"
#include "flash_if.h"
//#include "usart.h"
/*****************************************************************************/
#include "..\..\MCU_Application\sPlcPort\sPlcEprom.h"
#include "..\..\MCU_Application\lib\libcpu.h"
#include "..\..\MCU_Application\lib\libdbg.h"
#include "..\..\MCU_Application\sPlc\sPlcConfig.h"
#include "..\..\MCU_Application\sPlc\BoardConfig.h"
#include "..\..\MCU_Application\MainApp\AppConfig.h"
/*****************************************************************************/
void resetInit(void);
void bootLoadInit(void);
void bootLoadProcess(void);
#endif




