#ifndef __DEVICECONFIG_H__
#define __DEVICECONFIG_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
/*****************************************************************************/
typedef struct{
	uint16_t calibrationPwr0[10];//ͨ��0����У����
	uint16_t calibrationPwr1[10];//ͨ��1����У����
	char serialNumber[16];//���к�
	int16_t mfg_year;//������
	int16_t mfg_month;//������
	int16_t mfg_day;//������
	int8_t redLedDc;//�������
	int8_t greenLedDc;//�̵�����
	int8_t blueLedDc;//��������
}deviceConfig_t;

typedef struct{
	uint32_t powerUpCycle;//��������
	uint32_t runTime;//�����ۼ�ʱ�� ��λ����
	int16_t laserMaxPhotoDiode;//�����������
	int16_t mucMaxTemper;//����������¶�
}deviceLogInfo_t;
/*****************************************************************************/
extern deviceConfig_t deviceConfig;
extern deviceLogInfo_t deviceLogInfo;
extern uint32_t	UniqueId[3];//���������к� 
/*****************************************************************************/
extern uint16_t cpuGetFlashSize(void);
extern void readStm32UniqueID(void);
#endif



