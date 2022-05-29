#ifndef __SPLCEPROM_H__
#define __SPLCEPROM_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <LIMITS.H>
#include "stdbool.h"
#include "stdint.h"
/*****************************************************************************/
#include "libcrc.h"
#include "sPlcConfig.h"
/*****************************************************************************/
typedef enum {
	CLEAR_EPROM_ALL 			= 0x01,
	CLEAR_EPROM_NVRAM			= 0x02,
	CLEAR_EPROM_FDRAM			= 0x03,
	CLEAR_EPROM_FIRMWARE_CRC	= 0x04,
	CLEAR_EPROM_DEVICE_CONFIG	= 0x05,
	CLEAR_EPROM_LOG_INFO		= 0x06
}clarmEpromCmd_t;
/*****************************************************************************/
HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat);//��AT24CXXָ����ַ����һ������
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat);//��AT24CXX�����ָ����ַ��ʼ����16λ��
HAL_StatusTypeDef epromReadDword(uint16_t ReadAddr, uint32_t *rdat);////��AT24CXX�����ָ����ַ��ʼ����32λ��
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t *wdat);//��AT24CXXָ����ַд��8λ����
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t *wdat);//��AT24CXX�����ָ����ַ��ʼд��16λ��
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t *wdat);//��AT24CXX�����ָ����ַ��ʼд��32λ��
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);
HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);
uint8_t sPlcEpromTest(void);
uint8_t checkBlank(uint32_t adr, uint32_t size);//MCU Flash ���
void clearEprom(clarmEpromCmd_t cmd);//���EPROM����
void listEpromTable(void);
#endif
