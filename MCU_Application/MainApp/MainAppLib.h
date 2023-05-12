#ifndef __MAINAPPLIB_H__
#define __MAINAPPLIB_H__
/*****************************************************************************/
#include "sPlc.h"
#include "preScheme.h"
/*****************************************************************************/
typedef struct{
	float kp;
	float ki;
	float kd;
	float ek0;//e(k-0)
	float ek1;//e(k-1)
	float ek2;//e(k-2)
}IncPid_t;
/*****************************************************************************/
void addAcousticTime(void);//增加提示时间 +1
void decAcousticTime(void);//减小提示时间 -1
void addAcousticEnergy(void);//增加提示能量 +1
void decAcousticEnergy(void);//减小提示能量 -1		
uint8_t fanSpeedToPwm(uint8_t speed);//风扇输入转换为占空比
uint8_t getLcdDuty(int16_t LcdBrg);//屏幕亮度值转换为占空比
int16_t keyRuleAdd(int16_t ps, int16_t max);
int16_t keyRuleDec(int16_t ps, int16_t min);
void loadScheme(void);//DM->EM
void updateSchemeName(void);//TMP->FD
void updateCustomScheme(uint8_t index);//FD->EM
int8_t checkScheme(int8_t cn);//方案检测
void defaultScheme(void);//恢复默认设置
void restoreDefault(void);
uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg);
uint16_t fitLaserToCodeLine(uint8_t ch, int16_t power);
uint8_t saveSchemeToUdisk(void);//将FDRAM写入USB DISK
uint8_t loadSchemeFromUdisk(void);//从USB DISK载入FDRAM
int16_t IncPidCalc(IncPid_t *t, int16_t ref, int16_t fb);
/*****************************************************************************/
#endif



