#ifndef __CRC16_H__
#define __CRC16_H__
/*****************************************************************************/
#include "lib.h"
/*****************************************************************************/
uint16_t crc16Calculate(uint8_t *buf, uint32_t len);//CRC16 ��������
uint16_t crc16CalculateAdd(uint8_t dat);//CRC16 ���������ֽ�
void crc16Clear(void);//��վ�CRC16���
void crc16SetCrcOld(uint16_t old);
/*****************************************************************************/
#endif