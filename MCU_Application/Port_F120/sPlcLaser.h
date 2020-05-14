#ifndef __SPLCLASER_H__
#define __SPLCLASER_H__
/*****************************************************************************/
#include "sPlc.h"
#include "appSplcAdr.h"
#include "backgroundApp.h"
#include "dcHmiApp.h"
/*****************************************************************************/
#define LASER_MODE_CW							0x01//����ģʽ
#define LASER_MODE_SP							0x02//������ģʽ
#define LASER_MODE_MP							0x04//������ģʽ
#define LASER_MODE_GP							0x08//Ⱥ����ģʽ
#define LASER_MODE_DERMA						0x10//
#define LASER_MODE_SIGNAL						0x20//������ģʽ
#define LASER_SELECT_CH0						0x01
#define LASER_SELECT_CH1						0x02
#define LASER_SELECT_CH2						0x04
#define LASER_SELECT_CH3						0x08
#define LASER_SELECT_ALL						0x10
/*****************************************************************************/
extern volatile int8_t data LaserTimer_Mode;
extern volatile int8_t data LaserTimer_Select;
extern volatile int16_t data LaserTimer_TCounter;
extern volatile int16_t data LaserTimer_TMate;
extern volatile int16_t data LaserTimer_TOvertime;
extern volatile int16_t data LaserTimer_PCounter;
extern volatile int16_t data LaserTimer_PMate;
extern volatile int16_t data LaserTimer_POvertime;
extern volatile int16_t data LaserTimer_ReleaseTime;
extern volatile int16_t data LaserTimer_ReleaseCounter;
extern volatile int16_t data LaserTimer_BeemSwitchCounter;
extern volatile int16_t data LaserTimer_BeemSwtichLength;
extern volatile int8_t data  LaserFlag_Emiting;//���ⷢ���б�־
extern volatile int8_t data  LaserFlag_Emitover;//���ⷢ����ϱ�־
extern volatile int32_t data LaserRelease_TotalTime;//���ⷢ����ʱ��
extern volatile int32_t data LaserRelease_TotalEnergy;//���ⷢ��������
/*****************************************************************************/
void sPlcLaserInit(void);
void laserTimerIsr(void);//TIMER4 �ж� ���ⷢ��
void testBenchLaserTimer(uint8_t st);//LASER���ⷢ�����
void EDLAR(void)reentrant;//ֹͣ��������
void STLAR(void);//��ʼ��������
#endif