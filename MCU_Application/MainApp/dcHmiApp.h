#ifndef __DCHMIAPP_H__
#define __DCHMIAPP_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
#define FSMSTEP_POWERUP															0//�ϵ�
//HMI��ʼ����	
#define FSMSTEP_RESTORE_HMI													100//HMI �ָ���������
#define FSMSTEP_CHECK_FAIL_DISPLAY									200//ʧ���Լ�
//��������״̬
#define FSMSTEP_WAIT_ENTER_PASSCODE									300
#define FSMSTEP_PASSCODE_INPUT											301//��������״̬
#define FSMSTEP_PASSCODE_NEW0												302//�������״̬��һ������
#define FSMSTEP_PASSCODE_NEW1												303//�������״̬�ڶ�������
//STNADBY״̬
#define FSMSTEP_STANDBY															400//�ȴ�״̬
#define FSMSTEP_READY_LOAD_PARA											401//�������
#define FSMSTEP_READY_LOAD_DONE											402//����������
#define FSMSTEP_LASER_WAIT_TRIGGER									403//���ⴥ��
#define FSMSTEP_LASER_EMITING												404//���ⷢ����
#define FSMSTEP_READY_ERROR													405//��̤���´���
//ѡ��״̬
#define FSMSTEP_OPTION															500//ѡ��˵�
#define FSMSTEP_INFORMATION													600
#define FSMSTEP_SCHEME															700//�����˵���ҳ

#define FSMSTEP_DIAGNOSIS  													800//��ϲ˵�
#define FSMSTEP_RENAME															900
#define FSMSTEP_CORRECTION													1000//����У��
/*****************************************************************************/
#define FLASH_DATA_VERSION  												0XAABB0000
#define FLASH_DATA_ADDR     												0X00000000
/*****************************************************************************/
#define MSG_NO_ERROR																0
#define MSG_INTERLOCK_UNPLUG												1
#define	MSG_FOOTSWITCH_UNPLUG												2
#define	MSG_ESTOP_PRESS															3
#define	MSG_FIBER_UNPLUG														4
#define	MSG_OUT_ENERGY															5
#define	MSG_DIODE_HTEMP															6
#define	MSG_DIODE_LTEMP															7
#define	MSG_DIODE0_OVERCURRENT											8
#define	MSG_DIODE1_OVERCURRENT											9
#define	MSG_NTC_ERROR																10
#define	MSG_ENVI_HTEMP															11
#define MSG_ENVI_LTEMP															12
#define	MSG_FOOT_DEPRESSED													13
#define	MSG_LASER_EMIT															14
#define	MSG_WAIT_TRIGGER														15
#define	MSG_FIBER_MISSMATE													16
/*****************************************************************************/
void dcHmiLoop(void);//HMI��ѵ����
void dcHmiLoopInit(void);
void updateStandbyDisplay(void);
void standbyTouchEnable(int8_t enable);
void updatePowerDisplay(void);
void updatePosWidthDisplay(void);
void updateNegWidthDisplay(void );
void updateTimesDisplay(void);
void updateGroupOffDisplay(void);
void updateOptionDisplay(void);
void updateInformationDisplay(void);
void updateAcousticDisplay(void);
/*****************************************************************************/
void loadSelectScheme(int16_t classify, int16_t index);
void updateSchemeDetail(int16_t classify, int16_t index);
void unselectSchemeAll(void);
void seletcSchemeNum(int16_t classify, int16_t index);
void unselectSchemeNum(int16_t index);
/*****************************************************************************/
void clearReleaseTimeEnergy(void);
void updateReleaseTimeEnergy(void);
void updateSchemeInfo(int16_t classify, int16_t cn);
void updateWarnMsgDisplay(uint8_t id);
void returnStandbyDisplay(void);
void standbyKeyValue(uint8_t value);//����Standby��ֵ
void standbyKeyTouchEnable(int8_t enable);//Standby key����
/*****************************************************************************/
void updateExtralDisplay(void);//���¶�����ʾ
void standbyDebugInfoVisiable(int8_t enable);
void optionKeyEnable(uint8_t enable);
/*****************************************************************************/
void loadDeviceConfig(void);
void saveDeviceConfig(void);
/*****************************************************************************/
#endif






