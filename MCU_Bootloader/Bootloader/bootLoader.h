/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#ifndef __BOOTLOADER_H__
#define __BOOTLOADER_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
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
#include "sPlcEprom.h"
#include "libcpu.h"
#include "libdbg.h"
#include "myConfig.h"
/*****************************************************************************/
extern void resetInit(void);
extern void bootLoadInit(void);
extern void bootLoadProcess(void);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/****************************************************************************/
#endif




