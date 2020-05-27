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
#define LASER_MODE_SIGNAL						0x20//������ģʽ
#define LASER_SELECT_CH0						0x01
#define LASER_SELECT_CH1						0x02
#define LASER_SELECT_CH2						0x04
#define LASER_SELECT_CH3						0x08
#define LASER_SELECT_CH4						0x10
#define LASER_SELECT_ALL						0x10
/*****************************************************************************/
#define LASER_CH0_ON				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);						
#define LASER_CH1_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
#define LASER_CH2_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
#define LASER_CH3_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
#define LASER_CH4_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
#define LASER_CH0_OFF				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);			
#define LASER_CH1_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
#define LASER_CH2_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
#define LASER_CH3_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
#define LASER_CH4_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
#define GET_LASER_STATE_CH0			HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_4);	
#define GET_LASER_STATE_CH1			HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_7);
#define GET_LASER_STATE_CH2			HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5);
#define GET_LASER_STATE_CH3			HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6);
#define GET_LASER_STATE_CH4			HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_4);
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
extern volatile int32_t  LaserRelease_TotalTime;//���ⷢ����ʱ��
extern volatile int32_t  LaserRelease_TotalEnergy;//���ⷢ��������
/*****************************************************************************/
void sPlcLaserInit(void);
void laserTimerCallback(void);//�ж� ���ⷢ��
void testBenchLaserTimer(uint8_t st);//LASER���ⷢ�����
void EDLAR(void);//ֹͣ��������
void STLAR(void);//��ʼ��������

#endif

