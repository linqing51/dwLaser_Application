#ifndef __DEVICECONFIG_H__
#define __DEVICECONFIG_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
typedef float						fp32_t;
typedef double						fp64_t;
/*****************************************************************************/
typedef struct{
	uint8_t serialNumber[16];//���к�
	uint32_t bootLoaderVer;//��������汾
	uint32_t bootLoaderCrc;//��������У����
	uint32_t mucAppVer;//Ӧ�ó���汾
	uint32_t mucAppCrc;//Ӧ�ó���У����
	uint32_t lcdAppVer;//����������汾
	uint32_t lcdAppCrc;//����������У����
	//����3�ζ���ʽ���Y = A*X^3 + B*X^2 + C*X + D
	fp32_t laserNotesIntercept[8];//D
	fp32_t laserNotesB1[8];//C
	fp32_t laserNotesB2[8];//B
	fp32_t laserNotesB3[8];//A
	int16_t laserLimitPower[8];//��������
	uint16_t checkSum;//�����ļ�У����
}deviceConfig_t;
/*****************************************************************************/
extern deviceConfig_t myDeviceConfig;
extern deviceConfig_t defaultDeviceConfig;//Ĭ�����ò���
/*****************************************************************************/
#endif



