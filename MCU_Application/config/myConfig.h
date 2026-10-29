/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#ifndef __CONFIG_H__
#define __CONFIG_H__
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#define SW_VERSION																		"4.0a1b1"
/*****************************************************************************/
#if defined(CORE_6M3S_JL_FC_1940_1470_635)
#include ".\6M3S_JL_FC\AppConfig.h"
#include ".\6M3S_JL_FC\BoardConfig.h"
#include ".\6M3S_JL_FC\sPlcConfig.h"
#endif

#if defined(LYPE_2V0_20260703_M450)
#include ".\LYPE_2V0_M450\AppConfig.h"
#include ".\LYPE_2V0_M450\BoardConfig.h"
#include ".\LYPE_2V0_M450\sPlcConfig.h"
#endif

#if defined(G5_TRI_A1_20260915)
#include ".\G5_TRI_A1_20260915\AppConfig.h"
#include ".\G5_TRI_A1_20260915\BoardConfig.h"
#include ".\G5_TRI_A1_20260915\sPlcConfig.h"
#endif
/*****************************************************************************/
//定义分类方案个数
#define CONFIG_PHLEBOLOGY_SIZE												3
#define CONFIG_PROCTOLOGY_SIZE												6
#define CONFIG_GYNECOLOGY_SIZE												23
#define CONFIG_ENT_SIZE																16
#define CONFIG_ENDOLIFT_SIZE													11

#if defined(APP_CONFIG_WAVE_1470_980_635)
#define CONFIG_NEUROSURGERY_SIZE											5
#endif

#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
#define CONFIG_NEUROSURGERY_SIZE											3
#endif

#define CONFIG_DERMATOLOGY_SIZE												9
#define CONFIG_LIPOSUCTION_SIZE												7
#define CONFIG_DENTISRTY_SIZE													23

#if defined(APP_CONFIG_WAVE_1470_980_635)
#define CONFIG_THERAPY_SIZE														8
#endif

#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
#define CONFIG_THERAPY_SIZE														3
#endif
/*****************************************************************************/
#ifdef __cplusplus
}
#endif

#endif










