#ifndef __FIRMWAREUPDATE_H__
#define __FIRMWAREUPDATE_H__
/*****************************************************************************/
#include "sPlcPort.h"
#include "sPlc.h"
/*****************************************************************************/
typedef struct{
	uint8_t UREQ;//�̼���������
	uint8_t HW_CODE;//Ӳ���ͺ�
	uint8_t HW_VER;//Ӳ���汾
	uint8_t FW_VER;//�����¹̼��汾
	uint16_t FW_CRC16;//�����¹̼�CRC8ֵ
	uint16_t FW_SIZE;//�����¹̼�����
}fwConfig_t;
/*****************************************************************************/
void upDateFirmwareInit(void);//�̼����ó�ʼ��
void upDateFirmware(void);//����MCU 2nd �̼�
void upDateHmi(void);//����HMI�̼�
/*****************************************************************************/
#endif

