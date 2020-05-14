#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
#include "cmsis_os.h"
#include "stm32f4xx_hal.h"
#include "sPlcConfig.h"
#include "sPlcFun.h"
//#include "sPlcPort.h"
//#include "debugLed.h"
#if CONFIG_SPLC_FUN_EPID == 1
#include "splcFunEPID.h"
#endif
#if CONFIG_SPLC_FUNTEST == 1
#include "sPlcTest.h"
#endif
/*****************************************************************************/
#define SPLC_FP32					*(fp32_t*)//ָ��ȡ�����ȸ���
#define SPLC_FP64					*(fp64_t*)//ָ��ȡ˫���ȸ���
#define SPLC_INT32					*(int32_t*)//ָ��ȡ������
/*****************************************************************************/
extern volatile int16_t NVRAM0[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��ǰ �����浵�Ĵ���
extern volatile int16_t NVRAM1[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��һ��
extern volatile uint8_t TimerCounter_5mS;
extern volatile uint8_t TimerCounter_10mS;
extern volatile uint8_t TimerCounter_100mS;
extern volatile uint8_t TD_10MS_SP;
extern volatile uint8_t TD_100MS_SP;
extern volatile uint8_t TD_1000MS_SP;
/*****************************************************************************/
void sPlcInit(void);//���߼���ʼ��
void sPlcProcessStart(void);//sPLC��ѯ��ʼ
void sPlcProcessEnd(void);//sPLC��ѯ����
extern void sPlcPortProcess(void);//sPLCƽ̨����
extern void initWatchDog(void);//���Ź���ʼ��
extern void feedWatchDog(void);//ι��
extern void enableWatchDog(void);//ʹ�ܿ��Ź�
extern void disableWatchDog(void);//�رտ��Ź�(δ����)
extern void checkWatchDog(void);//��鿴�Ź�״̬
extern void mucReboot(void);//�����λ
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
void enterSplcIsr(void);
void exitSplcIsr(void);
void disableSplcIsr(void);
void enableSplcIsr(void);
/*****************************************************************************/
void sPlcInit(void);
void updateNvram(void);//����NVRAM->EPROM
void clearNvram(void);//���NVRAM����	
void loadNvram(void);
void loadFdram(void);
void saveFdram(void);
void saveNvram(void);
/*****************************************************************************/
#endif
