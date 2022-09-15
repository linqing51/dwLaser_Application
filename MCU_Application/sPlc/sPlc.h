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
#define LASER_MODE_CW											0x01//连续模式
#define LASER_MODE_SP											0x02//单脉冲模式
#define LASER_MODE_MP											0x04//多脉冲模式
#define LASER_MODE_GP											0x08//群脉冲模式
#define LASER_MODE_DERMA									0x10//
#define LASER_MODE_SIGNAL									0x20//
#define LASER_SELECT_CH0									0x01
#define LASER_SELECT_CH1									0x02
#define LASER_SELECT_CH2									0x04
#define LASER_SELECT_CH3									0x08
#define LASER_SELECT_ALL									0x0F
/*****************************************************************************/
extern UART_HandleTypeDef huart1;//调试
extern CRC_HandleTypeDef hcrc;
extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;//FAN PWM
extern TIM_HandleTypeDef htim3;//LED PWM
extern TIM_HandleTypeDef htim7;//DAC DMA 计时器
extern TIM_HandleTypeDef htim10;//Laser Timer
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim14;//sPlc Timer
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
extern int8_t  LaserFlag_Emiting;//激光发射中标志
extern int8_t LaserFlag_Emitover;//激光发射完毕标志
extern int32_t LaserRelease_TotalTime0;//激光发射总时间
extern double LaserRelease_TotalEnergy0;//激光发射总能量
extern int32_t LaserRelease_TotalTime1;//激光发射总时间
extern double LaserRelease_TotalEnergy1;//激光发射总能量
extern uint32_t LaserAcousticBeepNum;//提示音发射次数
/*****************************************************************************/
extern void sPlcInit(void);//软逻辑初始化
extern void sPlcProcessStart(void);//sPLC轮询起始
extern void sPlcProcessEnd(void);//sPLC轮询结束
extern void sPlcPortProcess(void);//sPLC平台程序
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
extern void sPlcNvramUpdate(void);//更新NVRAM->EPROM	
extern void sPlcNvramLoad(void);
extern void sPlcNvramSave(void);
extern void sPlcNvramClear(void);//清除NVRAM数据
extern void sPlcFdramLoad(void);
extern void sPlcFdramSave(void);
extern void sPlcFdramClear(void);
extern void sPlcDeviceConfigClear(void);
extern void sPlcDeviceLogClear(void);
extern void delayMs(uint32_t delayMs);//SPLC 阻塞延时
extern void mucReboot(void);//软件复位
/*****************************************************************************/
extern void sPlcInit(void);
/*****************************************************************************/
extern void sPlcTimerInit(void);//硬件sTimer计时器初始化
extern void sPlcTimerIsr(void);//硬件sTimer计时器中断 1mS
extern void sPlcTimerDisalbe(void);//SPLC关闭计时器
extern void sPlcTimerEnable(void);//SPLC打开计时器
extern void sPlcDacInit(void);//DAC初始化
extern void sPlcDacRefresh(void);//刷新DAC
extern void sPlcAdcInit(void);
extern void sPlcAdcProcess(void);
extern void sPlcSpeakerFreq(int16_t freq);//设置喇叭频率
extern void sPlcSpeakerVolume(int16_t volume);//设置喇叭音量
extern void sPlcSpeakerEnable(void);//打开喇叭数据流
extern void sPlcSpeakerDisable(void);//关闭喇叭数据流
extern void sPlcSpeakerInit(void);//喇叭初始化
extern void sPlcLaserInit(void);
extern void sPlcLaserTimerIsr(void);//中断 激光发射
extern void sPlcLaserTimerTestBench(uint8_t st);//LASER激光发射测试
/*****************************************************************************/
extern void REBOOT(void) ;//复位
//位指令
extern void SSET(uint16_t A);//线圈置位
extern void RRES(uint16_t A);//线圈复位
extern void FLIP(uint16_t A) ;//翻转
extern uint8_t LD(uint16_t A) ;//载入
extern uint8_t LDB(uint16_t A) ;//方向载入
extern uint8_t LDP(uint16_t A) ;//脉冲上升沿
extern uint8_t LDN(uint16_t A) ;//脉冲下降沿
//计时器指令
extern void T10MS(uint8_t A, uint8_t start, uint16_t value) ;//10mS计时器启动
extern void T100MS(uint8_t A, uint8_t start, uint16_t value) ;//100mS计时器启动
//运算指令
extern void CLR(uint16_t A) ;//寄存器清零
extern void CLRD(uint16_t A) ;//32位寄存器清零
extern void MOV(uint16_t dist, uint16_t src) ;//16位寄存器传输
extern void MOVD(uint16_t dist, uint16_t src) ;//32位寄存器传输
extern void SWAP(uint16_t dist, uint16_t src) ;//交换A的高低字节
extern void ABS16(uint16_t dist, uint16_t src) ;//16位数球绝对值
extern void ABS32(uint16_t dist, uint16_t src) ;//32位数求绝对值
extern void SMIN16(uint16_t index, uint16_t length, uint16_t min) ;//16位有符号数组找最小值
extern void SMAX16(uint16_t index, uint16_t length, uint16_t max) ;//16位有符号数组找最大值
extern void UMIN16(uint16_t index, uint16_t length, uint16_t min) ;//16位无符号数组找最小值
extern void UMAX16(uint16_t index, uint16_t length, uint16_t max) ;//16位无符号数组找最大值
extern void SUM16(uint16_t index, uint16_t length, uint16_t sum) ;//16BIT数求和->32BIT
extern void MULT32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->32非饱和乘法 D = Sa * Sb
extern void MULTS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->16饱和乘法 D = Sa * Sb
extern void MULT16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->16非饱和乘法 D = Sa * Sb
extern void SUB32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32位非饱和减法 D = Sa - Sb
extern void SUBS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16位饱和减法 D = Sa - Sb
extern void SUB16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16位非饱和减法 D = Sa - Sb
extern void ADD32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32位非饱加法 D = Sa + Sb
extern void ADDS32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32位饱和加法 D = Sa + Sb
extern void ADDS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16位饱和加法 D = Sa + Sb
extern void ADD16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16位非饱和加法 D = Sa + Sb
extern void ADD1(uint16_t Sa) ;//16位非饱和自加
extern void ADDS1(uint16_t Sa) ;//16位饱和自加
extern void DEC1(uint16_t Sa) ;//16位非饱和自减
extern void DECS1(uint16_t Sa) ;//16位饱和自减
extern void ADL1(uint16_t Sa) ;//32位非饱和自加
extern void ADLS1(uint16_t Sa) ;//32位饱和自加
extern void DEL1(uint16_t Sa) ;//32位非饱和自减
extern void DELS1(uint16_t Sa) ;//32位饱和自减
extern void TNTC(uint16_t dist, uint16_t src);//CODE转换为环境温度
extern void TENV(uint16_t dist, uint16_t src);//CODE转换为NTC测量温度温度
extern void BCPY(uint16_t dist, uint16_t src, uint16_t length);//块复制
extern void LIMS16(uint16_t src, uint16_t min, uint16_t max);//有符号16位数限制幅度指令
extern void UPDAC0(void);//立即更新DAC0
extern void UPDAC1(void);//立即更新DAC1
extern void UPDAC2(void);
extern void UPDAC3(void);
extern void CLDAC(void);//立即清空DAC0和DAC1
extern void IMDIO(void) ;//立即更新IO点状态含输入输出
extern void NVSAVE(void);//强制立即更新NVRAM
extern void NVFSAVE(void);//NVRAM全部写入EPROM
extern void NVLOAD(void);
extern void FDSAV(void);
extern void FDLAD(void);
extern void FDSAV_ONE(int16_t cn);
extern void FDLAD_ONE(int16_t cn);
extern void PRTM(uint16_t adr, uint8_t len);
extern void LINKS(void);//从机接收
extern void LINKM(void);//主机发送
extern void EDLAR(void);//停止发射脉冲
extern void STLAR(void);//开始发射脉冲
/*****************************************************************************/
#endif
