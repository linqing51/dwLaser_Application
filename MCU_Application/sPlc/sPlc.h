#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
//#include "arm_math.h"
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
#include "sPlcConfig.h"
#include "sPlcMisc.h"
#include "sPlcMcu.h"
#include "sPlcFun.h"
#include "sPlcTimer.h"
#include "sPlcLaser.h"
#if CONFIG_SPLC_USING_EPROM == 1
#include "sPlcEprom.h"
#endif
#if CONFIG_SPLC_USING_ADC == 1
#include "sPlcAdc.h"
#endif
#if CONFIG_SPLC_USING_DAC == 1
#include "sPlcDac.h"
#endif
#if CONFIG_USING_DCHMI_APP == 1
#include "dcHmiApp.h"
#endif
/*****************************************************************************/
#include "main.h"
//#include "sPlcPort.h"
//#include "debugLed.h"
#if CONFIG_SPLC_FUN_EPID == 1
#include "splcFunEPID.h"
#endif
#if CONFIG_SPLC_FUNTEST == 1
#include "sPlcTest.h"
#endif
/*****************************************************************************/
typedef float						fp32_t;
typedef double						fp64_t;
/*****************************************************************************/
extern int16_t NVRAM0_MR[];//��Ȧ ����
extern int16_t NVRAM1_MR[];//��Ȧ ����
/*****************************************************************************/
extern int16_t NVRAM0_DM[];//���ݼĴ���
extern int16_t NVRAM1_DM[];//���ݼĴ���
/*****************************************************************************/
extern int16_t NVRAM0_R[];//��Ȧ�Ǳ���
extern int16_t NVRAM1_R[];//��Ȧ�Ǳ���
/*****************************************************************************/
extern int16_t NVRAM0_EM[];//���ݼĴ����Ǳ���
/*****************************************************************************/
extern int16_t NVRAM0_T_1MS[];//��ʱ��Ȧ1MS
extern int16_t NVRAM1_T_1MS[];//��ʱ��Ȧ1MS
extern int16_t NVRAM0_T_10MS[];//��ʱ��Ȧ10MS
extern int16_t NVRAM1_T_10MS[];//��ʱ��Ȧ10MS
extern int16_t NVRAM0_T_100MS[];//��ʱ��Ȧ100MS
extern int16_t NVRAM1_T_100MS[];//��ʱ��Ȧ100MS
/*****************************************************************************/
extern int16_t NVRAM0_T_1MS_ENA[];//��ʱ��ʹ��1MS
extern int16_t NVRAM1_T_1MS_ENA[];//��ʱ��ʹ��1MS
extern int16_t NVRAM0_T_10MS_ENA[];//��ʱ��ʹ��10MS
extern int16_t NVRAM1_T_10MS_ENA[];//��ʱ��ʹ��10MS
extern int16_t NVRAM0_T_100MS_ENA[];//��ʱ��ʹ��100MS
extern int16_t NVRAM1_T_100MS_ENA[];//��ʱ��ʹ��100MS
/*****************************************************************************/
extern int16_t NVRAM0_TD_1MS[];//��ʱ��ʱ��1MS
extern int16_t NVRAM0_TD_10MS[];//��ʱ��ʱ��10MS
extern int16_t NVRAM0_TD_100MS[];//��ʱ��ʱ��100MS
/*****************************************************************************/
extern int16_t NVRAM0_X[];//����λ�Ĵ���
extern int16_t NVRAM1_X[];//����λ�Ĵ���
/*****************************************************************************/
extern int16_t NVRAM0_Y[];//���λ�Ĵ���
extern int16_t NVRAM1_Y[];//���λ�Ĵ���
/*****************************************************************************/
extern int16_t NVRAM0_SPREG[];//����Ĵ���
/*****************************************************************************/
extern int16_t NVRAM0_SPCOIL[];//������Ȧ
extern int16_t NVRAM1_SPCOIL[];//������Ȧ
/*****************************************************************************/
extern int16_t NVRAM0_TMP[];//��ʱ�Ĵ���
/*****************************************************************************/
extern int16_t FDRAM0[];//�浵�Ĵ���
/*****************************************************************************/
extern uint8_t TimerCounter_1mS;
extern uint8_t TimerCounter_10mS;
extern uint8_t TimerCounter_100mS;
extern uint8_t TD_10MS_SP;
extern uint8_t TD_100MS_SP;
extern uint8_t TD_1000MS_SP;
/*****************************************************************************/
void sPlcInit(void);//���߼���ʼ��
void sPlcProcessStart(void);//sPLC��ѯ��ʼ
void sPlcProcessEnd(void);//sPLC��ѯ����
void sPlcPortProcess(void);//sPLCƽ̨����
/*****************************************************************************/
void assertAddress(uint8_t type, uint16_t adr);//����ַ
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
__weak void inputInit(void);
__weak void inputRefresh(void);
__weak void outputInit(void);
__weak void outputRefresh(void);
__weak void loadDefault(void);
__weak void enterSplcIsr(void);
__weak void exitSplcIsr(void);
__weak void disableSplcIsr(void);
__weak void enableSplcIsr(void);
__weak void updateNvram(void);//����NVRAM->EPROM
__weak void clearNvram(void);//���NVRAM����	
__weak void loadNvram(void);
__weak void saveNvram(void);
__weak void loadFdram(void);
__weak void saveFdram(void);
__weak void mucReboot(void);//�����λ
__weak void setLed(uint8_t color, uint8_t state);//����LED��
/*****************************************************************************/
void sPlcInit(void);
/*****************************************************************************/
#endif
