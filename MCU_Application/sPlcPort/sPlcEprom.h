#ifndef __SPLCEPROM_H__
#define __SPLCEPROM_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat);//��AT24CXXָ����ַ����һ������
HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat);//��AT24CXX�����ָ����ַ��ʼ����16λ��
HAL_StatusTypeDef epromReadDword(int16_t ReadAddr, uint32_t *rdat);////��AT24CXX�����ָ����ַ��ʼ����32λ��
HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t DataToWrite);//��AT24CXXָ����ַд��8λ����
HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t DataToWrite);//��AT24CXX�����ָ����ַ��ʼд��16λ��
HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t DataToWrite);//��AT24CXX�����ָ����ַ��ʼд��32λ��
HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);
HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);
uint8_t epromTest(void);
#endif
