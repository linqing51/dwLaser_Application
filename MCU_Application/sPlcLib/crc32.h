#ifndef __CRC32_H__
#define __CRC32_H__
/*****************************************************************************/
#include "lib.h"
/*****************************************************************************/
uint32_t crc32Calculate(uint8_t *buf, uint32_t len);//CRC32 ��������
uint32_t crc32CalculateAdd(uint8_t dat);//CRC32 ���������ֽ�
void crc32Clear(void);//��վ�CRC32���
void crc32SetCrcOld(uint32_t old);
/*****************************************************************************/
#endif





