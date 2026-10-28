#ifndef __LIBDBG_H__
#define __LIBDBG_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "stm32f4xx_hal.h"
#include "..\config\myConfig.h"
#include "stdio.h"
/*****************************************************************************/
void listEpromTable(void);//输出EPROM分布表
void listNvramTable(void);//输出NVRAM分布表
int fputc(int ch,FILE *f);
int fgetc(FILE *f);
int ferror(FILE *f);
void morseCodeDiag(uint8_t diag);//莫尔斯电码诊断闪烁，循环不返回
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
