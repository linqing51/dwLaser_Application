#ifndef __DEVICECONFIG_H__
#define __DEVICECONFIG_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
//#include "arm_math.h"
/*****************************************************************************/
typedef struct{
	uint16_t calibrationPwr0[10];//ͨ��0����У����
	uint16_t calibrationPwr1[10];//ͨ��1����У����
	uint16_t calibrationPwr2[10];//ͨ��2����У����
	uint16_t calibrationPwr3[10];//ͨ��3����У����
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



