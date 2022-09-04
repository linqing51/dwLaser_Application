#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
//#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
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
#if CONFIG_SPLC_USING_ADC == 1
#include "sPlcAdc.h"
#endif
#include "sPlcDac.h"
#if CONFIG_USING_DCHMI_APP == 1
#include "dcHmiApp.h"
#endif
#include "preScheme.h"
/*****************************************************************************/
#include "main.h"
//#include "sPlcPort.h"
//#include "debugLed.h"
#if CONFIG_SPLC_FUNTEST == 1
#include "sPlcTest.h"
#endif
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
void sPlcInit(void);//���߼���ʼ��
void sPlcProcessStart(void);//sPLC��ѯ��ʼ
void sPlcProcessEnd(void);//sPLC��ѯ����
void sPlcPortProcess(void);//sPLCƽ̨����
/*****************************************************************************/
void assertCoilAddress(uint16_t adr);
void assertRegisterAddress(uint16_t adr);
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
extern void inputInit(void);
extern void inputRefresh(void);
extern void outputInit(void);
extern void outputRefresh(void);
extern void loadDefault(void);
extern void enterSplcIsr(void);
extern void exitSplcIsr(void);
extern void disableSplcIsr(void);
extern void enableSplcIsr(void);
extern void updateNvram(void);//����NVRAM->EPROM	
extern void loadNvram(void);
extern void saveNvram(void);
extern void clearNvram(void);//���NVRAM����
extern void loadFdram(void);
extern void saveFdram(void);
extern void clearFdram(void);
extern void clearDeviceConfig(void);
extern void clearDeviceLog(void);
extern void delayMs(uint32_t delayMs);//SPLC ������ʱ
extern void mucReboot(void);//�����λ
/*****************************************************************************/
void sPlcInit(void);
/*****************************************************************************/
extern void LINKS(void);//�ӻ�����
extern void LINKM(void);//��������
/*****************************************************************************/
#endif
