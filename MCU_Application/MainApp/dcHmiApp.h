#ifndef __DCHMIAPP_H__
#define __DCHMIAPP_H__
/*****************************************************************************/
#include "sPlc.h"
#include "boardConfig.h"
#include "appConfig.h"
/*****************************************************************************/
#include "dcHmiApp.h"
#include "preScheme.h"
#include "dcHmiLanguage.h"
#include "dcHmiNotifyButton.h"
#include "dcHmiNotifyProgress.h"
#include "dcHmiNotifyReadRTC.h"
#include "dcHmiNotifyText.h"
#include "tempCtrLoop.h"
/*****************************************************************************/
#include "hmiLib.h"
#include "dcHmiRes.h"
#include "MainAppLib.h"
//#include "fan_controller.h"
//#
/*****************************************************************************/
#define FSMSTEP_HIBERNATE														0//休眠->软关机
#define FSMSTEP_IDLE																1//待机
#define FSMSTEP_POWERUP															10//上电
//HMI初始操作	
#define FSMSTEP_RESTORE_HMI													100//HMI 恢复储存数据
#define FSMSTEP_CHECK_FAIL_DISPLAY									200//失败自检
//密码输入状态
#define FSMSTEP_WAIT_ENTER_PASSCODE									300
#define FSMSTEP_PASSCODE_INPUT											301//密码输入状态
#define FSMSTEP_PASSCODE_NEW0												302//密码更改状态第一次输入
#define FSMSTEP_PASSCODE_NEW1												303//密码更改状态第二次输入
//STNADBY状态
#define FSMSTEP_STANDBY															400//等待状态
#define FSMSTEP_READY_LOAD_PARA											401//载入参数
#define FSMSTEP_READY_LOAD_DONE											402//载入参数完毕
#define FSMSTEP_LASER_WAIT_TRIGGER									403//激光触发
#define FSMSTEP_LASER_EMITING												404//激光发射中
#define FSMSTEP_READY_ERROR													405//脚踏踩下错误
//选项状态
#define FSMSTEP_OPTION															500//选项菜单
#define FSMSTEP_INFORMATION													600
#define FSMSTEP_SCHEME															700//方案菜单第页

#define FSMSTEP_DIAGNOSIS  													800//诊断菜单
#define FSMSTEP_DIAGNOSIS_RAW												801//诊断菜单-RAW数据
#define FSMSTEP_RENAME															900
//关机状态
#define FSMSTEP_POWEROFF_CONFIRM										1000
//功率校准状态
#define FSMSTEP_CORRECTION													1100//功率校正
/*****************************************************************************/
#define FLASH_DATA_VERSION  												0XAABB0000
#define FLASH_DATA_ADDR     												0X00000000
/*****************************************************************************/
#define MSG_ID_NO_ERROR															0
#define MSG_ID_INTERLOCK_UNPLUG											1
#define	MSG_ID_FOOTSWITCH_UNPLUG										2
#define	MSG_ID_ESTOP_PRESS													3
#define	MSG_ID_FIBER_UNPLUG													4
#define	MSG_ID_OUT_ENERGY														5
#define	MSG_ID_LASER_EMIT														6
#define	MSG_ID_WAIT_TRIGGER													7
#define	MSG_ID_FIBER_MISSMATE												8
#define	MSG_ID_LASEER_DIODE_A_HTEMP									9
#define	MSG_ID_LASEER_DIODE_B_HTEMP									10
#define	MSG_ID_LASEER_DIODE_A_LTEMP									11
#define	MSG_ID_LASEER_DIODE_B_LTEMP									12
#define MSG_ID_LASEER_COUPLER_A_HTEMP               13
#define MSG_ID_LASEER_COUPLER_B_HTEMP               14
#define MSG_ID_LASEER_CRYST0_A_HTEMP								15
#define MSG_ID_LASEER_CRYST1_A_HTEMP								16
#define MSG_ID_LASEER_CRYST0_B_HTEMP								17
#define MSG_ID_LASEER_CRYST1_B_HTEMP								18
#define MSG_ID_LASEER_CRYST0_A_LTEMP                19
#define MSG_ID_LASEER_CRYST0_B_LTEMP                20
#define MSG_ID_LASEER_CRYST1_A_LTEMP                21
#define MSG_ID_LASEER_CRYST1_B_LTEMP                22
#define MSG_ID_HT0_TEMP_HIGH												23
#define MSG_ID_HT1_TEMP_HIGH												24
#define MSG_ID_HT2_TEMP_HIGH												25
#define MSG_ID_HT3_TEMP_HIGH												26
#define MSG_ID_HWATER_TEMP_HIGH											27
#define MSG_ID_HWATER_TEMP_LOW											28
#define MSG_ID_CWATER_TEMP_HIGH											29
#define MSG_ID_CWATER_TEMP_LOW											30
#define MSG_ID_AMBIENT0_TEMP_HIGH										31
#define MSG_ID_AMBIENT0_TEMP_LOW										32	
#define MSG_ID_AMBIENT1_TEMP_HIGH										33
#define MSG_ID_AMBIENT1_TEMP_LOW				            34
#define MSG_ID_AMBIENT2_TEMP_HIGH			              35
#define MSG_ID_AMBIENT2_TEMP_LOW										36
#define MSG_ID_AMBIENT3_TEMP_HIGH			              37
#define MSG_ID_AMBIENT3_TEMP_LOW				            38
#define MSG_ID_HDC1080_TEMP_HIGH										39			
#define MSG_ID_HDC1080_TEMP_LOW											40
#define MSG_ID_HDC1080_HUMIDITY_HIGH								41	
#define MSG_ID_HDC1080_HUMIDITY_LOW									42
#define MSG_ID_DHT11_TEMP_HIGH											43
#define MSG_ID_DHT11_TEMP_LOW												44	
#define MSG_ID_DHT11_HUMIDITY_HIGH									45	
#define MSG_ID_DHT11_HUMIDITY_LOW										46	
#define MSG_ID_MCU_TEMP_HIGH												47	
#define MSG_ID_MCU_TEMP_LOW													48	
#define MSG_ID_MBAT_TEMP_HIGH												49	
#define MSG_ID_MBAT_TEMP_LOW												50	
#define	MSG_ID_DIODE_A_OVERCURRENT									51	
#define	MSG_ID_DIODE_B_OVERCURRENT									52
#define MSG_ID_FLOW_ABNORMAL												53									
#define MSG_ID_HUMIDITY_ABNORMAL										53	
/*****************************************************************************/
void dcHmiLoop(void);//HMI轮训程序
void dcHmiLoopInit(void);
void statusLoop(void);
void tempControlLoop(void);//温度风扇控制循环
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
uint8_t isLegalUsbDev(USBH_HandleTypeDef *phost);
void wfswLoop(USBH_HandleTypeDef *phost);
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
void standbyKeyValue(uint8_t value);//设置Standby键值
void standbyKeyTouchEnable(int8_t enable);//Standby key触摸
/*****************************************************************************/
void updateExtralDisplay(void);//更新额外显示
void standbyDebugInfoVisiable(int8_t enable);
void optionKeyEnable(uint8_t enable);
/*****************************************************************************/
extern void PmuPowerUp(void);//开机函数
extern void PmuPowerDown(void);//关机函数
#endif






