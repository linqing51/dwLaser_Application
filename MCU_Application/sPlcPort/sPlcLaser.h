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
#define LASER_SELECT_ALL						0x0F
/*****************************************************************************/
#define SET_LAS_PWM0(b)								HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, b)
#define FLIP_LAS_PWM0()								HAL_GPIO_TogglePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)

#define SET_LAS_PWM1(b)								HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, b)
#define FLIP_LAS_PWM1()								HAL_GPIO_TogglePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)

#define SET_LAS_PWM2(b)								HAL_GPIO_WritePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin, b)
#define FLIP_PWM2()										HAL_GPIO_TogglePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin)

#define SET_LAS_PWM3(b)								HAL_GPIO_WritePin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin, b)
#define FLIP_LASPWM3()								HAL_GPIO_TogglePin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin)

#define GET_LASER_PWM0								HAL_GPIO_ReadPin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin) 	
#define GET_LASER_PWM1								HAL_GPIO_ReadPin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)
#define GET_LASER_PWM2								HAL_GPIO_ReadPin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin)
#define GET_LASER_PWM3								HAL_GPIO_ReadPin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin)
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





