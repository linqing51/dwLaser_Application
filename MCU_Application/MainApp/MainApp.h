#ifndef __MAINAPP_H__
#define __MAINAPP_H__

#include "main.h"
#include "adc.h"
#include "crc.h"
#include "i2c.h"
#include "rng.h"
#include "usart.h"
#include "gpio.h"


#include "stdio.h"
#include "string.h"
#include "dac8568.h"





typedef struct{//����Э������
	uint8_t rcvNum;//�ѽ��ܵ��ֽ���
	uint8_t sendNum;//�跢�͵��ֽ���
	uint8_t rcvBuf[256];
	uint8_t sendBuf[256];
	uint8_t *pRcvReadIndex;   
	uint8_t *pRcvWriteIndex;
	int8_t flagRcvDone;
	int8_t flagRcving;
	int8_t flagSendDone;
	int8_t flagSending;
}cmdQueue_t;

typedef struct{//״̬
	int8_t alarm;//���ϱ���
	float readChipTemper;//�������¶�
	float readLaserTemper;//�������¶�
	uint16_t readLaserPd[2];//������PD
	uint16_t readLaserCur[2];//�ɼ�����������
	uint16_t writeLaserCur[2];//���ü���������
	uint16_t writeLaserPwm[2];//����������ռ�ձ�
	int8_t writeLaserAim[2];//������ָʾ��
	uint32_t writeLaserOnTime;//���ⷢ��ʱ��
	uint32_t timerStart;//�����ʱ����ʼʱ��
	uint32_t timerEnd;//j�����ʱ������ʱ��
}laserConfig_t;

typedef struct{
	uint8_t start;
	uint32_t mate;//ƥ��ֵ
	uint32_t counter;//������
}softTimer_t;


void mainApp(void);
#endif






