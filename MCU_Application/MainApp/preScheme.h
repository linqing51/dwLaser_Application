/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#ifndef __PRESCHEME_H__
#define __PRESCHEME_H__
/*****************************************************************************/
#include "sPlc.h"
#include "dcHmiApp.h"
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
/*===========================================================================
 * [分支范围说明] 分支: run_treatment
 * 本分支只进行: ① 病历相关功能; ② 节省 RAM / EPROM 用量优化。
 * 优化要点: 预设治疗方案 sXxx[32] 运行期永不修改、只在预设基础上临时调整且
 *   不回存(重启即丢弃), 故全部由 .bss(RAM) 改为 const 初始化器固化在 Flash,
 *   restoreScheme 不再硬编码填充预设, 仅保留 FDRAM 自定义方案逻辑与 FDSAV()。
 * 握手 5 秒超时问题本分支暂不修复(见 hmiCmdQueue.c / dcHmiApp.c 内注解)。
 *===========================================================================*/
typedef struct{
	char *name;//治疗名字
	int16_t channel;//激光通道选择
	int16_t pulse_mode;//模式
	int16_t power_ch0;
	int16_t power_ch1;
	int16_t power_ch2;
  int16_t power_ch3;
  int16_t power_ch4;
  int16_t power_ch5;
  int16_t power_ch6;
  int16_t power_ch7;
	int16_t poswidth;
	int16_t negwidth;
}myScheme_t;
/*****************************************************************************/
extern const myScheme_t sPhlebology[32];//0
extern const myScheme_t sProctology[32];//1
extern const myScheme_t sGynecology[32];//2
extern const myScheme_t sENT[32];//3
extern const myScheme_t sNeurosurgery[32];//4
extern const myScheme_t sDermatology[32];//5
extern const myScheme_t sLiposuction[32];//6
extern const myScheme_t sDentistry[32];//7
extern const myScheme_t sTherapy[32];//8
extern const myScheme_t sEndolift[32];//11
/*****************************************************************************/
void restoreScheme(uint8_t reDef);//治疗方案初始化
void goNextScheme(void);//切换下一个方案
void goLastScheme(void);//切换上一个方案
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif


