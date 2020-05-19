#ifndef __SPLCBEEM_H__
#define __SPLCBEEM_H__
/*****************************************************************************/
#define BEEM_MODE_0											0x10//����ģʽ
#define BEEM_MODE_1											0x11//����ͬ��
#define BEEM_MODE_2											0x12//���ⷢ��̶����
#define BEEM_MODE_3											0x13//�쳣����
#define BEEM_FREQ_0											0xF2//����Ƶ��
#define BEEM_FREQ_1											0xF1//���
/*****************************************************************************/
#include "sPlcPort.h"
/*****************************************************************************/
void sPlcPcaInit(void);//��ʱ�����г�ʼ��
void sPlcAimInit(void);//��������ʼ��
void sPlcAimLoop(void);
void sPlcBeemInit(void);//��������ʼ��
void sPlcBeemLoop(void);
/*****************************************************************************/
extern uint8_t data BeemFreq;//������Ƶ��
extern uint8_t data BeemMode;//������ģʽ
extern uint8_t data BeemDuty;//������ռ�ձ�
extern uint16_t data BeemCounter;
extern int8_t data BeemEnable;
extern uint8_t data AimDuty0, AimDuty1;
extern int8_t data AimEnable0, AimEnable1;
#endif