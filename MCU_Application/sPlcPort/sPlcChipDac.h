#ifndef __SPLCCHIPDAC_H__
#define __SPLCCHIPDAC_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
void initChipDac(void);//DAC��ʼ��
void refreshChipDac(void);//ˢ��DAC
void UPDAC0(void);//��������DAC0
void UPDAC1(void);//��������DAC1
void UPDAC2(void);
void UPDAC3(void);
void CLDAC(void);//�������DAC0��DAC1
#endif


