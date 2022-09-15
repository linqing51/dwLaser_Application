#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
#include "cmsis_os.h"
#include "main.h"
#include "arm_math.h"
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <LIMITS.H>
#include <math.h>
#include "stdbool.h"
#include "stdint.h"
/*****************************************************************************/
#include "libcrc.h"
#include "deviceConfig.h"
#include "sPlcConfig.h"
#include "sPlcMisc.h"
#include "sPlcSpeaker.h"
#include "sPlcMcu.h"
#include "sPlcFun.h"
#include "sPlcTimer.h"
#include "sPlcLaser.h"

#include "sPlcEprom.h"
#include "sPlcAdc.h"
#include "sPlcDac.h"
#include "dcHmiApp.h"
#include "preScheme.h"
/*****************************************************************************/
#include "main.h"
#if CONFIG_SPLC_FUNTEST == 1
#include "sPlcTest.h"
#endif
/*****************************************************************************/
#define LASER_MODE_CW											0x01//����ģʽ
#define LASER_MODE_SP											0x02//������ģʽ
#define LASER_MODE_MP											0x04//������ģʽ
#define LASER_MODE_GP											0x08//Ⱥ����ģʽ
#define LASER_MODE_DERMA									0x10//
#define LASER_MODE_SIGNAL									0x20//
#define LASER_SELECT_CH0									0x01
#define LASER_SELECT_CH1									0x02
#define LASER_SELECT_CH2									0x04
#define LASER_SELECT_CH3									0x08
#define LASER_SELECT_ALL									0x0F
/*****************************************************************************/
extern UART_HandleTypeDef huart1;//����
extern CRC_HandleTypeDef hcrc;
extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;//FAN PWM
extern TIM_HandleTypeDef htim3;//LED PWM
extern TIM_HandleTypeDef htim7;//DAC DMA ��ʱ��
extern TIM_HandleTypeDef htim10;//Laser Timer
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim14;//sPlc Timer
/*****************************************************************************/
extern int16_t NVRAM0[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��ǰ �����浵�Ĵ���
extern int16_t NVRAM1[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��һ��
extern int16_t FDRAM[CONFIG_FDRAM_SIZE];//�浵�Ĵ���
extern uint8_t LKSRAM[CONFIG_LKSRAM_SIZE];//ͨ�ŷ��ͻ�����
extern uint8_t LKRRAM[CONFIG_LKRRAM_SIZE];//ͨ�Ž��ջ�����
extern uint16_t TimerCounter_10mS;//10����
extern uint16_t TimerCounter_100mS;//100����
extern uint16_t TimerCounter_200mS;//200����
extern uint16_t TimerCounter_500mS;//500����
extern uint16_t TimerCounter_1000mS;//1��
extern uint16_t TimerCounter_60000mS;//1����
extern uint8_t TD_10MS_SP;
extern uint8_t TD_100MS_SP;
extern uint8_t TD_200MS_SP;
extern uint8_t TD_500MS_SP;
extern uint8_t TD_1000MS_SP;
extern uint8_t TD_60000MS_SP;
extern uint32_t sPlcTick;
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
extern int32_t LaserRelease_TotalTime0;//���ⷢ����ʱ��
extern double LaserRelease_TotalEnergy0;//���ⷢ��������
extern int32_t LaserRelease_TotalTime1;//���ⷢ����ʱ��
extern double LaserRelease_TotalEnergy1;//���ⷢ��������
extern uint32_t LaserAcousticBeepNum;//��ʾ���������
/*****************************************************************************/
extern void sPlcInit(void);//���߼���ʼ��
extern void sPlcProcessStart(void);//sPLC��ѯ��ʼ
extern void sPlcProcessEnd(void);//sPLC��ѯ����
extern void sPlcPortProcess(void);//sPLCƽ̨����
/*****************************************************************************/
extern void sPlcAssertCoilAddress(uint16_t adr);
extern void sPlcAssertRegisterAddress(uint16_t adr);
/*****************************************************************************/
void clearX(void);
void clearY(void);
void clearDM(void);
void clearEM(void);
void clearR(void);
void clearT(void);
void clearTD(void);
void clearSPCOIL(void);
void clearSPREG(void);
/*****************************************************************************/
extern void sPlcInputInit(void);
extern void sPlcInputRefresh(void);
extern void sPlcOutputInit(void);
extern void sPlcOutputRefresh(void);
extern void sPlcloadDefault(void);
extern void sPlcIsrDisable(void);
extern void sPlcIsrEnable(void);
extern void sPlcNvramUpdate(void);//����NVRAM->EPROM	
extern void sPlcNvramLoad(void);
extern void sPlcNvramSave(void);
extern void sPlcNvramClear(void);//���NVRAM����
extern void sPlcFdramLoad(void);
extern void sPlcFdramSave(void);
extern void sPlcFdramClear(void);
extern void sPlcDeviceConfigClear(void);
extern void sPlcDeviceLogClear(void);
extern void delayMs(uint32_t delayMs);//SPLC ������ʱ
extern void mucReboot(void);//�����λ
/*****************************************************************************/
extern void sPlcInit(void);
/*****************************************************************************/
extern void sPlcTimerInit(void);//Ӳ��sTimer��ʱ����ʼ��
extern void sPlcTimerIsr(void);//Ӳ��sTimer��ʱ���ж� 1mS
extern void sPlcTimerDisalbe(void);//SPLC�رռ�ʱ��
extern void sPlcTimerEnable(void);//SPLC�򿪼�ʱ��
extern void sPlcDacInit(void);//DAC��ʼ��
extern void sPlcDacRefresh(void);//ˢ��DAC
extern void sPlcAdcInit(void);
extern void sPlcAdcProcess(void);
extern void sPlcSpeakerFreq(int16_t freq);//��������Ƶ��
extern void sPlcSpeakerVolume(int16_t volume);//������������
extern void sPlcSpeakerEnable(void);//������������
extern void sPlcSpeakerDisable(void);//�ر�����������
extern void sPlcSpeakerInit(void);//���ȳ�ʼ��
extern void sPlcLaserInit(void);
extern void sPlcLaserTimerIsr(void);//�ж� ���ⷢ��
extern void sPlcLaserTimerTestBench(uint8_t st);//LASER���ⷢ�����
/*****************************************************************************/
extern void REBOOT(void) ;//��λ
//λָ��
extern void SSET(uint16_t A);//��Ȧ��λ
extern void RRES(uint16_t A);//��Ȧ��λ
extern void FLIP(uint16_t A) ;//��ת
extern uint8_t LD(uint16_t A) ;//����
extern uint8_t LDB(uint16_t A) ;//��������
extern uint8_t LDP(uint16_t A) ;//����������
extern uint8_t LDN(uint16_t A) ;//�����½���
//��ʱ��ָ��
extern void T10MS(uint8_t A, uint8_t start, uint16_t value) ;//10mS��ʱ������
extern void T100MS(uint8_t A, uint8_t start, uint16_t value) ;//100mS��ʱ������
//����ָ��
extern void CLR(uint16_t A) ;//�Ĵ�������
extern void CLRD(uint16_t A) ;//32λ�Ĵ�������
extern void MOV(uint16_t dist, uint16_t src) ;//16λ�Ĵ�������
extern void MOVD(uint16_t dist, uint16_t src) ;//32λ�Ĵ�������
extern void SWAP(uint16_t dist, uint16_t src) ;//����A�ĸߵ��ֽ�
extern void ABS16(uint16_t dist, uint16_t src) ;//16λ�������ֵ
extern void ABS32(uint16_t dist, uint16_t src) ;//32λ�������ֵ
extern void SMIN16(uint16_t index, uint16_t length, uint16_t min) ;//16λ�з�����������Сֵ
extern void SMAX16(uint16_t index, uint16_t length, uint16_t max) ;//16λ�з������������ֵ
extern void UMIN16(uint16_t index, uint16_t length, uint16_t min) ;//16λ�޷�����������Сֵ
extern void UMAX16(uint16_t index, uint16_t length, uint16_t max) ;//16λ�޷������������ֵ
extern void SUM16(uint16_t index, uint16_t length, uint16_t sum) ;//16BIT�����->32BIT
extern void MULT32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->32�Ǳ��ͳ˷� D = Sa * Sb
extern void MULTS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->16���ͳ˷� D = Sa * Sb
extern void MULT16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->16�Ǳ��ͳ˷� D = Sa * Sb
extern void SUB32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32λ�Ǳ��ͼ��� D = Sa - Sb
extern void SUBS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16λ���ͼ��� D = Sa - Sb
extern void SUB16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16λ�Ǳ��ͼ��� D = Sa - Sb
extern void ADD32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32λ�Ǳ��ӷ� D = Sa + Sb
extern void ADDS32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32λ���ͼӷ� D = Sa + Sb
extern void ADDS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16λ���ͼӷ� D = Sa + Sb
extern void ADD16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16λ�Ǳ��ͼӷ� D = Sa + Sb
extern void ADD1(uint16_t Sa) ;//16λ�Ǳ����Լ�
extern void ADDS1(uint16_t Sa) ;//16λ�����Լ�
extern void DEC1(uint16_t Sa) ;//16λ�Ǳ����Լ�
extern void DECS1(uint16_t Sa) ;//16λ�����Լ�
extern void ADL1(uint16_t Sa) ;//32λ�Ǳ����Լ�
extern void ADLS1(uint16_t Sa) ;//32λ�����Լ�
extern void DEL1(uint16_t Sa) ;//32λ�Ǳ����Լ�
extern void DELS1(uint16_t Sa) ;//32λ�����Լ�
extern void TNTC(uint16_t dist, uint16_t src);//CODEת��Ϊ�����¶�
extern void TENV(uint16_t dist, uint16_t src);//CODEת��ΪNTC�����¶��¶�
extern void BCPY(uint16_t dist, uint16_t src, uint16_t length);//�鸴��
extern void LIMS16(uint16_t src, uint16_t min, uint16_t max);//�з���16λ�����Ʒ���ָ��
extern void UPDAC0(void);//��������DAC0
extern void UPDAC1(void);//��������DAC1
extern void UPDAC2(void);
extern void UPDAC3(void);
extern void CLDAC(void);//�������DAC0��DAC1
extern void IMDIO(void) ;//��������IO��״̬���������
extern void NVSAVE(void);//ǿ����������NVRAM
extern void NVFSAVE(void);//NVRAMȫ��д��EPROM
extern void NVLOAD(void);
extern void FDSAV(void);
extern void FDLAD(void);
extern void FDSAV_ONE(int16_t cn);
extern void FDLAD_ONE(int16_t cn);
extern void PRTM(uint16_t adr, uint8_t len);
extern void LINKS(void);//�ӻ�����
extern void LINKM(void);//��������
extern void EDLAR(void);//ֹͣ��������
extern void STLAR(void);//��ʼ��������
/*****************************************************************************/
#endif
