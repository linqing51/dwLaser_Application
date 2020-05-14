#ifndef __BACKGROUNDAPP_H__
#define __BACKGROUNDAPP_H__
/*****************************************************************************/
#include "sPlc.h"
#include "appConfig.h"
#include "appSplcAdr.h"
/*****************************************************************************/
/*****************************************************************************/
uint8_t getBeemDuty(int16_t volume);
uint8_t getLcdDuty(int16_t LcdBrg);//��Ļ����ֵת��Ϊռ�ձ�
uint8_t getAimDuty(int16_t AimBrg);//ָʾ������ֵת��Ϊռ�ձ�
int16_t pulseWidthAdd(int16_t ps);
int16_t pulseWidthDec(int16_t ps);
void loadScheme(void);//DM->EM
void updateSchemeName(void);//TMP->FD
void saveScheme(void);//EM->DM
int8_t checkScheme(int8_t cn);//�������
void defaultScheme(void);//�ָ�Ĭ������
void loadDefault(void);
int16_t fitLaserToCode(uint8_t ch, int16_t power);
/*****************************************************************************/
#endif