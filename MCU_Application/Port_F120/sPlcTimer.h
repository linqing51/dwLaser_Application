#ifndef __SPLCTIMER_H__
#define __SPLCTIMER_H__
/*****************************************************************************/
#include "sPlcPort.h"
void initSplcTimer(void);//Ӳ��sTimer��ʱ����ʼ��
extern void sPlcTimerIsr(void);//Ӳ��sTimer��ʱ���ж� 1mS
#endif