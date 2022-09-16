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
	uint16_t calibrationPwr0[10];//通道0功率校正表
	uint16_t calibrationPwr1[10];//通道1功率校正表
	uint16_t calibrationPwr2[10];//通道2功率校正表
	uint16_t calibrationPwr3[10];//通道3功率校正表
	uint16_t calibrationPwr4[10];//通道4功率校正表
}deviceConfig_t;
typedef struct{
	uint32_t powerUpCycle;//开机次数
	uint32_t runTime;//运行累计时间 单位分钟
	int16_t laserMaxPhotoDiode;//激光器最大功率
	int16_t mucMaxTemper;//处理器最高温度
}deviceLogInfo_t;

typedef struct{//循环缓冲
 uint16_t head;//头指针
 uint16_t tail;//尾指针
 uint16_t lenght;//长度
 uint8_t buff[CONFIG_RING_BUFFER_SIZE];//缓冲大小
}ringBuff_t;

typedef struct{//自由协议
	uint8_t cmdBufRx[FP_RX_SIZE];
	uint8_t cmdBufTx[FP_TX_SIZE];
	uint8_t rxDone;//接收完成
	uint8_t rxIndex;//接收索引
	uint8_t rxRuning;//接收中
	uint8_t txDone;//发送完成
	uint8_t txIndex;//发送数量
	uint8_t txRuning;//发送中
}freeProtocol_t;
/*****************************************************************************/
extern deviceConfig_t deviceConfig;
extern deviceLogInfo_t deviceLogInfo;
extern uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
extern uint16_t cpuGetFlashSize(void);
extern void readStm32UniqueID(void);
/*****************************************************************************/
extern int16_t NVRAM0[CONFIG_NVRAM_SIZE];//掉电保持寄存器 当前 包含存档寄存器
extern int16_t NVRAM1[CONFIG_NVRAM_SIZE];//掉电保持寄存器 上一次
extern int16_t FDRAM[CONFIG_FDRAM_SIZE];//存档寄存器
extern uint8_t LKSRAM[CONFIG_LKSRAM_SIZE];//通信发送缓冲区
extern uint8_t LKRRAM[CONFIG_LKRRAM_SIZE];//通信接收缓冲区
extern uint16_t TimerCounter_10mS;//10毫秒
extern uint16_t TimerCounter_100mS;//100毫秒
extern uint16_t TimerCounter_200mS;//200毫秒
extern uint16_t TimerCounter_500mS;//500毫秒
extern uint16_t TimerCounter_1000mS;//1秒
extern uint16_t TimerCounter_60000mS;//1分钟
extern uint8_t TD_10MS_SP;
extern uint8_t TD_100MS_SP;
extern uint8_t TD_200MS_SP;
extern uint8_t TD_500MS_SP;
extern uint8_t TD_1000MS_SP;
extern uint8_t TD_60000MS_SP;
/*****************************************************************************/
extern void sPlcInit(void);//软逻辑初始化
extern void sPlcProcessStart(void);//sPLC轮询起始
extern void sPlcProcessEnd(void);//sPLC轮询结束
extern void sPlcPortProcess(void);//sPLC平台程序
/*****************************************************************************/
extern void sPlcChipDacInit(void);//DAC初始化
/*****************************************************************************/
extern void sPlcChipAdcInit(void);//ADC模块初始化
extern void sPlcChipAdcProcess(void);//循环采集ADC
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
extern void sPlcTimerInit(void);//硬件sTimer计时器初始化
extern void sPlcTimerIsr(void);//硬件sTimer计时器中断 1mS
extern void sPlclaserTimerIsr(void);//中断 激光发射
extern void sPlcTimerDisable(void);//SPLC关闭计时器
extern void sPlcTimerEnable(void);//SPLC打开计时器
/*****************************************************************************/
extern void sPlcSpeakerFreq(int16_t freq);//设置喇叭频率
extern void sPlcSpeakerVolume(int16_t volume);//设置喇叭音量
extern void sPlcSpeakerEnable(void);//打开喇叭数据流
extern void sPlcSpeakerDisable(void);//关闭喇叭数据流
extern void sPlcSpeakerInit(void);//喇叭初始化
/*****************************************************************************/
extern void sPlcAssertCoilAddress(uint16_t adr);
extern void sPlcAssertRegisterAddress(uint16_t adr);
/*****************************************************************************/
extern void sPlcErrorHandler(uint16_t errCode);//错误处理
extern void sPlcAssertCoilAddress(uint16_t adr);//检查线圈地址
extern void sPlcAssertRegisterAddress(uint16_t adr);//检查寄存器地址
extern void sPlcEnableIsr(void);//使能SPLC中断
extern void sPlcDisableIsr(void);//关闭SPLC中断
extern void sPlcUpdateNvram(void);//更新NVRAM->EPROM	
extern void sPlcLoadNvram(void);//从EPROM中载入NVRAM MR和DM
extern void sPlcSaveNvram(void);//NVRAM MR和DM写入EPROM
extern void sPlcClearNvram(void);//清除NVRAM数据
extern void sPlcLoadFdram(void);//从EPROM载入FDRAM
extern void sPlcSaveFdram(void);//FDRAM写入EPROM
extern void sPlcClearFdram(void);//清空FDRAM
extern void sPlcClearDeviceConfig(void);
extern void sPlcClearDeviceLog(void);
extern void delayMs(uint32_t delayMs);//SPLC 阻塞延时
extern void mucReboot(void);//软件复位
extern void sPlcSaveConfigUdisk(void);//将配置文件写入U盘
extern void sPlcLoadConfigUdisk(void);//从U盘载入配置文件
extern void sPlcSaveNvramUdisk(void);//将NVRAM写入U盘
extern void sPlcLoadNvramUdisk(void);//从U盘载入NVRAM
extern void sPlcSaveLogUdisk(void);//Log写入U盘
extern void sPlcLoadLogUdisk(void);//从U盘恢复Log
extern void sPlcInit(void);
/*****************************************************************************/
extern uint16_t fitLaserToCode(uint8_t ch, int16_t power, deviceConfig_t *pcfg);//功率分段线性校准
extern void sPlcFreeProtocolInit(void);//自由协议初始化
extern void sPlcFreeProtocolProcess(void);//自由协议命令处理 
/*****************************************************************************/
extern void sPlcRingBuffInit(ringBuff_t *p);//循环缓冲初始化
extern uint8_t sPlcRingBuffPush(ringBuff_t *p, uint8_t data);//循环缓冲压入
extern uint8_t sPlcRingBuffPop(ringBuff_t *p ,uint8_t *rData);//循环缓冲弹出
/*****************************************************************************/
extern void LINKS(void);//从机接收
extern void LINKM(void);//主机发送
/*****************************************************************************/
void EDLAR(void);//停止发射脉冲
void STLAR(void);//开始发射脉冲
void CLDAC(void);//立即清空全部DAC
void UPDAC0(void);//更新DAC0
void UPDAC1(void);//更新DAC1
void UPDAC2(void);//更新DAC2
void UPDAC3(void);//更新DAC3
void UPDAC4(void);//更新DAC4
void UPDAC5(void);//更新DAC5
void UPDAC6(void);//更新DAC6
void UPDAC7(void);//更新DAC7
/*****************************************************************************/
#endif
