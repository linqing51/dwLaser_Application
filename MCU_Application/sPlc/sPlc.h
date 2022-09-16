#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
//#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "arm_math.h"
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
#include "sPlcMisc.h"
/*****************************************************************************/
#include "sPlcModbus.h"
#include "sPlcFreeProtocol.h"
/*****************************************************************************/
#include "main.h"
/*****************************************************************************/
typedef float						fp32_t;
typedef double						fp64_t;
typedef struct{
	uint16_t calibrationPwr0[10];//ͨ��0����У����
	uint16_t calibrationPwr1[10];//ͨ��1����У����
	uint16_t calibrationPwr2[10];//ͨ��2����У����
	uint16_t calibrationPwr3[10];//ͨ��3����У����
	uint16_t calibrationPwr4[10];//ͨ��4����У����
}deviceConfig_t;
typedef struct{
	uint32_t powerUpCycle;//��������
	uint32_t runTime;//�����ۼ�ʱ�� ��λ����
	int16_t laserMaxPhotoDiode;//�����������
	int16_t mucMaxTemper;//����������¶�
}deviceLogInfo_t;

typedef struct{//ѭ������
 uint16_t head;//ͷָ��
 uint16_t tail;//βָ��
 uint16_t lenght;//����
 uint8_t buff[CONFIG_RING_BUFFER_SIZE];//�����С
}ringBuff_t;

typedef struct{//����Э��
	uint8_t cmdBufRx[FP_RX_SIZE];
	uint8_t cmdBufTx[FP_TX_SIZE];
	uint8_t rxDone;//�������
	uint8_t rxIndex;//��������
	uint8_t rxRuning;//������
	uint8_t txDone;//�������
	uint8_t txIndex;//��������
	uint8_t txRuning;//������
}freeProtocol_t;
/*****************************************************************************/
extern deviceConfig_t deviceConfig;
extern deviceLogInfo_t deviceLogInfo;
extern uint32_t	UniqueId[3];//���������к� 
/*****************************************************************************/
extern uint16_t cpuGetFlashSize(void);
extern void readStm32UniqueID(void);
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
/*****************************************************************************/
extern void sPlcInit(void);//���߼���ʼ��
extern void sPlcProcessStart(void);//sPLC��ѯ��ʼ
extern void sPlcProcessEnd(void);//sPLC��ѯ����
extern void sPlcPortProcess(void);//sPLCƽ̨����
/*****************************************************************************/
extern void sPlcChipDacInit(void);//DAC��ʼ��
/*****************************************************************************/
extern void sPlcChipAdcInit(void);//ADCģ���ʼ��
extern void sPlcChipAdcProcess(void);//ѭ���ɼ�ADC
/*****************************************************************************/
extern void sPlcInputInit(void);
extern void sPlcInputRefresh(void);
/*****************************************************************************/
extern void sPlcOutputInit(void);
extern void sPlcOutputRefresh(void);
/*****************************************************************************/
extern void sPlcLaserInit(void);
extern void sPlcLaserTimerIsr(void);
/*****************************************************************************/
extern void sPlcTimerInit(void);//Ӳ��sTimer��ʱ����ʼ��
extern void sPlcTimerIsr(void);//Ӳ��sTimer��ʱ���ж� 1mS
extern void sPlclaserTimerIsr(void);//�ж� ���ⷢ��
extern void sPlcTimerDisable(void);//SPLC�رռ�ʱ��
extern void sPlcTimerEnable(void);//SPLC�򿪼�ʱ��
/*****************************************************************************/
extern void sPlcSpeakerFreq(int16_t freq);//��������Ƶ��
extern void sPlcSpeakerVolume(int16_t volume);//������������
extern void sPlcSpeakerEnable(void);//������������
extern void sPlcSpeakerDisable(void);//�ر�����������
extern void sPlcSpeakerInit(void);//���ȳ�ʼ��
/*****************************************************************************/
extern void sPlcAssertCoilAddress(uint16_t adr);
extern void sPlcAssertRegisterAddress(uint16_t adr);
/*****************************************************************************/
extern void sPlcErrorHandler(uint16_t errCode);//������
extern void sPlcAssertCoilAddress(uint16_t adr);//�����Ȧ��ַ
extern void sPlcAssertRegisterAddress(uint16_t adr);//���Ĵ�����ַ
extern void sPlcEnableIsr(void);//ʹ��SPLC�ж�
extern void sPlcDisableIsr(void);//�ر�SPLC�ж�
extern void sPlcUpdateNvram(void);//����NVRAM->EPROM	
extern void sPlcLoadNvram(void);//��EPROM������NVRAM MR��DM
extern void sPlcSaveNvram(void);//NVRAM MR��DMд��EPROM
extern void sPlcClearNvram(void);//���NVRAM����
extern void sPlcLoadFdram(void);//��EPROM����FDRAM
extern void sPlcSaveFdram(void);//FDRAMд��EPROM
extern void sPlcClearFdram(void);//���FDRAM
extern void sPlcClearDeviceConfig(void);
extern void sPlcClearDeviceLog(void);
extern void delayMs(uint32_t delayMs);//SPLC ������ʱ
extern void mucReboot(void);//�����λ
extern void sPlcSaveConfigUdisk(void);//�������ļ�д��U��
extern void sPlcLoadConfigUdisk(void);//��U�����������ļ�
extern void sPlcSaveNvramUdisk(void);//��NVRAMд��U��
extern void sPlcLoadNvramUdisk(void);//��U������NVRAM
extern void sPlcSaveLogUdisk(void);//Logд��U��
extern void sPlcLoadLogUdisk(void);//��U�ָ̻�Log
extern void sPlcInit(void);
/*****************************************************************************/
extern uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg);//���ʷֶ�����У׼
extern void sPlcFreeProtocolInit(void);//����Э���ʼ��
extern void sPlcFreeProtocolProcess(void);//����Э������� 
/*****************************************************************************/
extern void sPlcRingBuffInit(ringBuff_t *p);//ѭ�������ʼ��
extern uint8_t sPlcRingBuffPush(ringBuff_t *p, uint8_t data);//ѭ������ѹ��
extern uint8_t sPlcRingBuffPop(ringBuff_t *p ,uint8_t *rData);//ѭ�����嵯��
/*****************************************************************************/
extern void LINKS(void);//�ӻ�����
extern void LINKM(void);//��������
/*****************************************************************************/
void EDLAR(void);//ֹͣ��������
void STLAR(void);//��ʼ��������
void CLDAC(void);//�������ȫ��DAC
void UPDAC0(void);//����DAC0
void UPDAC1(void);//����DAC1
void UPDAC2(void);//����DAC2
void UPDAC3(void);//����DAC3
void UPDAC4(void);//����DAC4
void UPDAC5(void);//����DAC5
void UPDAC6(void);//����DAC6
void UPDAC7(void);//����DAC7
/*****************************************************************************/
#endif
