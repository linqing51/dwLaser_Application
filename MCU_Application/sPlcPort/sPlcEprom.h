#ifndef __SPLCEPROM_H__
#define __SPLCEPROM_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
uint8_t epromReadByte(uint16_t ReadAddr);//��AT24CXXָ����ַ����һ������
uint16_t epromReadHword(uint16_t ReadAddr);//��AT24CXX�����ָ����ַ��ʼ����16λ��
uint32_t epromReadDword(int16_t ReadAddr);////��AT24CXX�����ָ����ַ��ʼ����32λ��
void epromWriteByte(uint16_t WriteAddr, uint8_t *DataToWrite);//��AT24CXXָ����ַд��һ������
void epromWriteHword(uint16_t WriteAddr, uint16_t *DataToWrite);//��AT24CXX�����ָ����ַ��ʼд��16λ��
void epromWriteDword(uint16_t WriteAddr, uint32_t *DataToWrite);//��AT24CXX�����ָ����ַ��ʼд��32λ��
uint8_t epromTest(void);
#endif
