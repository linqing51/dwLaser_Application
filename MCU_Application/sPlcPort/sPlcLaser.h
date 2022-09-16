#ifndef __SPLCLASER_H__
#define __SPLCLASER_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
#define LASER_MODE_CW							0x01//����ģʽ
#define LASER_MODE_SP							0x02//������ģʽ
#define LASER_MODE_MP							0x04//������ģʽ
#define LASER_MODE_GP							0x08//Ⱥ����ģʽ
#define LASER_MODE_DERMA						0x10//
#define LASER_MODE_SIGNAL						0x20//
#define LASER_SELECT_CH0						0x01
#define LASER_SELECT_CH1						0x02
#define LASER_SELECT_CH2						0x04
#define LASER_SELECT_CH3						0x08
#define LASER_SELECT_ALL						0x0F
/*****************************************************************************/
extern int8_t LaserTimer_Mode;
extern int8_t LaserTimer_Select;
extern int16_t LaserTimer_TCounter;
extern int16_t LaserTimer_TMate;
extern int16_t LaserTimer_TOvertime;
extern int16_t LaserTimer_PCounter;
extern int16_t LaserTimer_PMate;
extern int16_t LaserTimer_POvertime;
extern int16_t LaserTimer_ReleaseTime;
extern int16_t LaserTimer_ReleaseCounter;
extern int8_t  LaserFlag_Emiting;//���ⷢ���б�־
extern int8_t LaserFlag_Emitover;//���ⷢ����ϱ�־
/*****************************************************************************/
void testBenchLaserTimer(uint8_t st);//LASER���ⷢ�����
#endif





