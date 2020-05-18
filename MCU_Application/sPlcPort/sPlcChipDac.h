#ifndef __SPLCCHIPDAC_H__
#define __SPLCCHIPDAC_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
void initChipDac(void);//DAC初始化
void refreshChipDac(void);//刷新DAC
void UPDAC0(void);//立即更新DAC0
void UPDAC1(void);//立即更新DAC1
void UPDAC2(void);
void UPDAC3(void);
void CLDAC(void);//立即清空DAC0和DAC1
#endif


