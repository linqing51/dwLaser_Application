#ifndef __SPLCCHIPDAC_H__
#define __SPLCCHIPDAC_H__
/*****************************************************************************/
#include "sPlcPort.h"
/*****************************************************************************/
void initChipDac(void);//DAC��ʼ��
void refreshChipDac(void);//ˢ��DAC
void UPDAC0(void) reentrant;//��������DAC0
void UPDAC1(void) reentrant;//��������DAC1
void UPDAC2(void) reentrant;
void UPDAC3(void) reentrant;
void CLDAC(void) reentrant;//�������DAC0��DAC1
#endif


