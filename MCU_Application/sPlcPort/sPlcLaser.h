#ifndef __SPLCLASER_H__
#define __SPLCLASER_H__
/*****************************************************************************/
#include "sPlc.h"
#include "hmiLib.h"
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
#define LASER_SELECT_CH4						0x10
#define LASER_SELECT_ALL						0x10
/*****************************************************************************/
#define SET_LASER_PWM(b)						HAL_GPIO_WritePin(LP_PWM_GPIO_Port, LP_PWM_Pin, (GPIO_PinState)b)						
#define GET_LASER_PWM()							HAL_GPIO_ReadPin(LP_PWM_GPIO_Port, LP_PWM_Pin)	

/*****************************************************************************/
extern volatile int8_t  LaserTimer_Mode;
extern volatile int8_t  LaserTimer_Select;
extern volatile int16_t  LaserTimer_TCounter;
extern volatile int16_t  LaserTimer_TMate;
extern volatile int16_t  LaserTimer_TOvertime;
extern volatile int16_t  LaserTimer_PCounter;
extern volatile int16_t  LaserTimer_PMate;
extern volatile int16_t  LaserTimer_POvertime;
extern volatile int16_t  LaserTimer_ReleaseTime;
extern volatile int16_t  LaserTimer_ReleaseCounter;
extern volatile int16_t  LaserTimer_BeemSwitchCounter;
extern volatile int16_t  LaserTimer_BeemSwtichLength;
extern volatile int8_t   LaserFlag_Emiting;//���ⷢ���б�־
extern volatile int8_t   LaserFlag_Emitover;//���ⷢ����ϱ�־
extern volatile int32_t  LaserRelease_TotalTime0;//���ⷢ����ʱ��
extern volatile int32_t  LaserRelease_TotalEnergy0;//���ⷢ��������
extern int32_t LaserRelease_TotalTime1;//���ⷢ����ʱ��
extern int32_t LaserRelease_TotalEnergy1;//���ⷢ��������
/*****************************************************************************/
void sPlcLaserInit(void);
void laserTimerIsr(void);//�ж� ���ⷢ��
void testBenchLaserTimer(uint8_t st);//LASER���ⷢ�����
void EDLAR(void);//ֹͣ��������
void STLAR(void);//��ʼ��������

#endif





