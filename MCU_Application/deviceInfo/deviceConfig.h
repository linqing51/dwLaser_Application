#ifndef __DEVICECONFIG_H__
#define __DEVICECONFIG_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
typedef float						fp32_t;
typedef double						fp64_t;
/*****************************************************************************/
typedef struct{
	char serialNumber[32];//���к�
	char dateOfManufacture[32];//��������
	//����3�ζ���ʽ���Y = A*X^3 + B*X^2 + C*X + D
	fp32_t laserNotesIntercept[5];//D
	fp32_t laserNotesB1[5];//C
	fp32_t laserNotesB2[5];//B
	fp32_t laserNotesB3[5];//A
	uint16_t crc;
}deviceConfig_t;

typedef struct{
	uint32_t bootLoaderCrc;//��������У����
	uint32_t mucAppCrc;//Ӧ�ó���У����
	uint32_t lcdAppCrc;//����������У����
}firmwareInfo_t;//�̼���Ϣ

typedef struct{
	uint32_t powerUpCycle;//��������
	uint32_t runTime;//�����ۼ�ʱ�� ��λ����
	uint32_t laserOnTime[5];//���ⷢ���ۼ�ʱ�� ��λ��
	int16_t laserMaxTemper;//����������¶�
	int16_t laserMinTemper;//����������¶�
	int16_t laserMaxCurrent[5];//������������
	int16_t laserMaxPhotoDiode;//�����������
	int16_t mucMaxTemper;//����������¶�
	int16_t mucMinTemper;//����������¶�
}deviceLogInfo_t;
/*****************************************************************************/
extern deviceConfig_t deviceConfig;
extern firmwareInfo_t firmwareInfo;//�̼���Ϣ
extern deviceLogInfo_t deviceLogInfo;
extern uint32_t	UniqueId[3];//���������к� 
/*****************************************************************************/
extern uint16_t cpuGetFlashSize(void);
extern void readStm32UniqueID(void);
#endif



