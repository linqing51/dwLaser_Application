#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
//stm32
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h" 
#include "arm_math.h"
/*****************************************************************************/
//cdev
#include "math.h"
#include <stdio.h>
#include <stddef.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <LIMITS.H>
#include "stdbool.h"
#include "stdint.h"
#include "string.h"
/*****************************************************************************/
//lib
#include "sPlcConfig.h"
#include "sPlcEprom.h"
#include "sPlcFun.h"
#include "libcrc.h"
#include "libdbg.h"
#include "libcpu.h"
#include "flash_if.h"
#include "pid_temp_control.h"
#include "fuzzy_pid.h"
#if defined(LYPE_MCU_1V0_20260106)
#include "sPlcI2C_HDC1080.h"
#endif
/*****************************************************************************/
//usb
#include "usbh_msc.h"
#include "usb_host.h"
#include "usbh_core.h"
/*****************************************************************************/
//fatfs
#include "ff.h"
#include "ff_gen_drv.h"
#include "flash_if.h"
/*****************************************************************************/
#if CONFIG_SPLC_USING_FUNTEST == 1
#include "sPlcTest.h"
#endif
/*****************************************************************************/
#define BEEM_MODE_0														0x10//连续模式
#define BEEM_MODE_1														0x11//声光同步
#define BEEM_MODE_2														0x12//激光发射固定间隔
#define BEEM_MODE_3														0x13//异常报警
#define BEEM_MODE_4														0x14//激光发射固定间隔+提示音
#define BEEM_MODE_5														0x15
/*****************************************************************************/
#define LASER_MODE_CW													0x01//连续模式
#define LASER_MODE_MP													0x02//多脉冲模式
/*****************************************************************************/
typedef struct{
	uint16_t calibrationPwr0[20];//通道0功率校正表
	uint16_t calibrationPwr1[20];//通道1功率校正表
	uint16_t calibrationPwr2[20];//通道2功率校正表
	uint16_t calibrationPwr3[20];//通道3功率校正表
	uint16_t calibrationPwr4[20];//通道4功率校正表
	uint16_t calibrationPwr5[20];//通道5功率校正表
	uint16_t calibrationPwr6[20];//通道6功率校正表
	uint16_t calibrationPwr7[20];//通道7功率校正表
	char serialNumber[16];//序列号
	int16_t mfg_year;//生产年
	int16_t mfg_month;//生产月
	int16_t mfg_day;//生产日
	int8_t redLedDc;//红灯亮度
	int8_t greenLedDc;//绿灯亮度
	int8_t blueLedDc;//蓝灯亮度
	int8_t redAimGain;//红指示光增益
	int8_t greenAimGain;//绿指示光增益
	int16_t fiberDetect;//光纤探测阈值
	int16_t laserDiodeA_Temp;//激光器A设置温度
	int16_t laserDiodeB_Temp;//激光器B设置温度
	char normalOpenInterLock;
}deviceConfig_t;
typedef struct{
	uint32_t powerUpCycle;//开机次数
	uint32_t runTime;//运行累计时间 单位分钟
	int16_t laserMaxPhotoDiode;//激光器最大功率
	int16_t mucMaxTemper;//处理器最高温度
}deviceLogInfo_t;
/*****************************************************************************/
// 封装一个简化调用的宏
#define OFFSET(type, member)  ((uint32_t)&(((type *)0)->member))

/*****************************************************************************/
extern deviceConfig_t deviceConfig;
extern deviceLogInfo_t deviceLogInfo;
extern uint32_t	UniqueId[3];//处理器序列号 
/*****************************************************************************/
extern int16_t NVRAM0[CONFIG_NVRAM_SIZE];//掉电保持寄存器 当前 包含存档寄存器
extern int16_t NVRAM1[CONFIG_NVRAM_SIZE];//掉电保持寄存器 上一次
extern int16_t FDRAM0[CONFIG_FDRAM_SIZE], FDRAM1[CONFIG_FDRAM_SIZE];//存档寄存器
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
extern uint32_t BootloadCrc, ApplicationCrc;
/*****************************************************************************/
extern int8_t LaserTimer_Mode;
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
/*****************************************************************************/
extern void sPlcInit(void);//软逻辑初始化
extern void sPlcProcessStart(void);//sPLC轮询起始
extern void sPlcProcessEnd(void);//sPLC轮询结束
extern void sPlcPortProcess(void);//sPLC平台程序
extern void sPlcAssertCoilAddress(uint16_t adr);
extern void sPlcAssertRegisterAddress(uint16_t adr);
/*****************************************************************************/
extern void sPlcInputInit(void);
extern void sPlcInputRefresh(void);
extern void sPlcOutputInit(void);
extern void sPlcOutputRefresh(void);
extern void sPlcIsrDisable(void);
extern void sPlcIsrEnable(void);
extern void sPlcTimerInit(void);//硬件sTimer计时器初始化
extern void sPlcTimerIsr(void);//硬件sTimer计时器中断 1mS
extern void sPlcTimerDisalbe(void);//SPLC关闭计时器
extern void sPlcTimerEnable(void);//SPLC打开计时器
extern void sPlcDacInit(void);//DAC初始化
extern void sPlcDacRefresh(void);//刷新DAC
extern void sPlcAdcInit(void);
extern void sPlcAdcProcessBufferA(void);
extern void sPlcAdcProcessBufferB(void);
extern void sPlcSpeakerFreq(int16_t freq);//设置喇叭频率
extern void sPlcSpeakerVolume(int16_t volume);//设置喇叭音量
extern void sPlcSpeakerEnable(void);//打开喇叭数据流
extern void sPlcSpeakerDisable(void);//关闭喇叭数据流
extern void sPlcSpeakerInit(void);//喇叭初始化
extern void sPlcLaserInit(void);
extern void sPlcLaserTimerIsr(void);//中断 激光发射
extern void sPlcLaserTimerTestBench(uint8_t st);//LASER激光发射测试
extern void sPlcNvramUpdate(void);//更新NVRAM->EPROM	
extern void sPlcNvramLoad(void);
extern void sPlcNvramSave(void);
extern void sPlcNvramClear(void);//清除NVRAM数据
extern void sPlcFdramLoad(void);
extern void sPlcFdramSave(void);
extern void sPlcFdramClear(void);
extern void sPlcDeviceConfigClear(void);
extern void sPlcDeviceLogClear(void);
extern void mucReboot(void);//软件复位
extern void resetInit(void);
extern void SystemClock_Reset(void);//复位系统时钟
extern void UsbGpioReset(void);
extern void setRedLaserPwm(int16_t pwm);//设置红激光占空比
extern void setGreenLaserPwm(int16_t pwm);//设置绿激光占空比
extern void setPower_635(int16_t pwr);//设置红激光功率
extern void setFanSpeed(int16_t speed);//设置风扇转速
extern void morseCodeDiag(uint8_t diag);//诊断码
extern void saveDeviceConfig(void);//将配置写入EPROM
extern void loadDeviceConfig(void);//从EPROM载入配置文件
extern void saveCalibrationTable(uint8_t channel);//储存选定通道的功率校准表
extern HAL_StatusTypeDef epromWriteEnable(bool en);//ERPOM写保护
extern HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat);//指定地址读出一个数据
extern HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat);//指定地址开始读出16位数
extern HAL_StatusTypeDef epromReadDword(uint16_t ReadAddr, uint32_t *rdat);//指定地址开始读出32位数
extern HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t *wdat);//在AT24CXX指定地址写入8位数据
extern HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t *wdat);//在AT24CXX里面的指定地址开始写入16位数
extern HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t *wdat);//在AT24CXX里面的指定地址开始写入32位数
extern HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);
extern HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);
extern uint8_t sPlcEpromTest(void);

extern uint32_t getOriginBootloadCrc(void);//计算MCU Bootload CRC32
extern uint32_t getOriginAppCrc(void);//计算MCU App CRC32
extern uint8_t updateBootloadReq(void);//更新BOOTLOAD请求
extern void confirmBootloadUpdate(void);//执行Bootload更新
extern void exitBootloadUpdate(void);//退出Bootload更新
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
extern void TNTLC(uint16_t dist, uint16_t src, float ntc_rs, float ntc_b);//CODE转换为环境温度 下电阻
extern void TNTUC(uint16_t dist, uint16_t src, float ntc_rs, float ntc_b);//CODE转换为环境温度 上电阻
extern void TENV(uint16_t dist, uint16_t src);//CODE转换为NTC测量温度温度
extern void BCPY(uint16_t dist, uint16_t src, uint16_t length);//块复制
extern void LIMS16(uint16_t src, uint16_t min, uint16_t max);//有符号16位数限制幅度指令
extern void UPDAC0(void);//立即更新LASER DAC0
extern void UPDAC1(void);//立即更新LASER DAC1
extern void UPDAC2(void);//立即更新LASER DAC2
extern void UPDAC3(void);//立即更新LASER DAC3
extern void UPDAC4(void);//立即更新LASER DAC4
extern void UPDAC5(void);//立即更新LASER DAC5
extern void UPDAC6(void);//立即更新LASER DAC6
extern void UPDAC7(void);//立即更新LASER DAC7
extern void UPDAC8(void);//立即更新TEC DAC8
extern void UPDAC9(void);//立即更新TEC DAC9
extern void UPDAC10(void);//立即更新TEC DAC10
extern void UPDAC11(void);//立即更新TEC DAC11
extern void UPDAC12(void);//立即更新TEC DAC12
extern void UPDAC13(void);//立即更新TEC DAC13
extern void UPDAC14(void);//立即更新TEC DAC14
extern void UPDAC15(void);//立即更新TEC DAC15
extern void UPDAC16(void);//立即更新650 DAC16
extern void UPDAC17(void);//立即更行532 DAC17
extern void CLDAC(void);//立即清空全部DAC
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
