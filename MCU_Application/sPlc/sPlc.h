#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
#include "cmsis_os.h"
#include "main.h"
#include "arm_math.h"
#include "usbh_core.h"
/*****************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <LIMITS.H>
#include "stdbool.h"
#include "stdint.h"
/*****************************************************************************/
#include "libcrc.h"
#include "deviceConfig.h"
#include "sPlcConfig.h"
#include "sPlcFun.h"
#include "dcHmiApp.h"
#include "preScheme.h"
/*****************************************************************************/
#if CONFIG_SPLC_FUNTEST == 1
#include "sPlcTest.h"
#endif
/*****************************************************************************/
#define BEEM_MODE_0														0x10//连续模式
#define BEEM_MODE_1														0x11//声光同步
#define BEEM_MODE_2														0x12//激光发射固定间隔
#define BEEM_MODE_3														0x13//异常报警
#define BEEM_MODE_4														0x14//激光发射固定间隔+提示音
/*****************************************************************************/
#define LASER_CHANNEL_0												0x00//通道0
#define LASER_CHANNEL_1												0x01//通道1
#define LASER_CHANNEL_2												0x02//通道2
#define LASER_CHANNEL_3												0x03//通道3
/*****************************************************************************/
#define LASER_MODE_CW													0x01//连续模式
#define LASER_MODE_SP													0x02//单脉冲模式
#define LASER_MODE_MP													0x04//多脉冲模式
#define LASER_MODE_GP													0x08//群脉冲模式
#define LASER_MODE_DERMA											0x10//
#define LASER_MODE_SIGNAL											0x20//
#define LASER_SELECT_CH0											0x01
#define LASER_SELECT_CH1											0x02
#define LASER_SELECT_CH2											0x04
#define LASER_SELECT_CH3											0x08
#define LASER_SELECT_ALL											0x0F
/*****************************************************************************/
#define MCP4821_NSHDN_MASK										(1 << 12)
#define MCP4821_NGA_MASK											(1 << 13)
/*****************************************************************************/
#define SET_EDAC0_CS(b)												HAL_GPIO_WritePin(EDAC0_CS_GPIO_Port, EDAC0_CS_Pin, b)
#define SET_EDAC1_CS(b)												HAL_GPIO_WritePin(EDAC1_CS_GPIO_Port, EDAC1_CS_Pin, b)
#define SET_EDAC2_CS(b)												HAL_GPIO_WritePin(EDAC2_CS_GPIO_Port, EDAC2_CS_Pin, b)
#define SET_EDAC3_CS(b)												HAL_GPIO_WritePin(EDAC3_CS_GPIO_Port, EDAC3_CS_Pin, b)
#define SET_EDAC0_SCK(b)											HAL_GPIO_WritePin(EDAC0_SCK_GPIO_Port, EDAC0_SCK_Pin, b)
#define SET_EDAC1_SCK(b)											HAL_GPIO_WritePin(EDAC1_SCK_GPIO_Port, EDAC1_SCK_Pin, b)
#define SET_EDAC2_SCK(b)											HAL_GPIO_WritePin(EDAC2_SCK_GPIO_Port, EDAC2_SCK_Pin, b)
#define SET_EDAC3_SCK(b)											HAL_GPIO_WritePin(EDAC3_SCK_GPIO_Port, EDAC3_SCK_Pin, b)
#define SET_EDAC0_SDI(b)											HAL_GPIO_WritePin(EDAC0_SDI_GPIO_Port, EDAC0_SDI_Pin, b)
#define SET_EDAC1_SDI(b)											HAL_GPIO_WritePin(EDAC1_SDI_GPIO_Port, EDAC1_SDI_Pin, b)
#define SET_EDAC2_SDI(b)											HAL_GPIO_WritePin(EDAC2_SDI_GPIO_Port, EDAC2_SDI_Pin, b)
#define SET_EDAC3_SDI(b)											HAL_GPIO_WritePin(EDAC3_SDI_GPIO_Port, EDAC3_SDI_Pin, b)
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_RED_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2)
#define SET_RED_LED_OFF												HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2)
#define SET_GREEN_LED_ON											HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1)
#define SET_GREEN_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1)
#define SET_BLUE_LED_ON												HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3)
#define SET_BLUE_LED_OFF											HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_3)

#define SET_BLUE_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b);
#define SET_RED_LED_DC(b)											__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, b);
#define SET_GREEN_LED_DC(b)										__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, b);

#define SET_ERR_LED_ON												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET)
#define SET_ERR_LED_OFF												HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET)
#define GET_ERR_LED														HAL_GPIO_ReadPin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define FLIP_ERR_LED													HAL_GPIO_TogglePin(ERR_LED_GPIO_Port, ERR_LED_Pin)
#define SET_TICK_LED_ON												HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET)
#define SET_TICK_LED_OFF											HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET)
#define GET_TICK_LED													HAL_GPIO_ReadPin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define FLIP_TICK_LED													HAL_GPIO_TogglePin(TICK_LED_GPIO_Port, TICK_LED_Pin)
#define SET_LASER_CH0_ON											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_SET)
#define SET_LASER_CH0_OFF											HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_RESET)
#define SET_LASER_CH1_ON											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_SET)
#define SET_LASER_CH1_OFF											HAL_GPIO_WritePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin, GPIO_PIN_RESET)
#define SET_LASER_CH2_ON											HAL_GPIO_WritePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin, GPIO_PIN_SET)
#define SET_LASER_CH2_OFF											HAL_GPIO_WritePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin, GPIO_PIN_RESET)
#define SET_LASER_CH3_ON											HAL_GPIO_WritePin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin, GPIO_PIN_SET)
#define SET_LASER_CH3_OFF											HAL_GPIO_WritePin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin, GPIO_PIN_RESET)
#define FLIP_LASER_CH0												HAL_GPIO_TogglePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define FLIP_LASER_CH1												HAL_GPIO_TogglePin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)
#define FLIP_LASER_CH2												HAL_GPIO_TogglePin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin)
#define FLIP_LASER_CH3												HAL_GPIO_TogglePin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin)
#define GET_LASER_CH0													HAL_GPIO_ReadPin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin)
#define GET_LASER_CH1													HAL_GPIO_ReadPin(LAS_PWM1_GPIO_Port, LAS_PWM1_Pin)
#define GET_LASER_CH2													HAL_GPIO_ReadPin(LAS_PWM2_GPIO_Port, LAS_PWM2_Pin)
#define GET_LASER_CH3													HAL_GPIO_ReadPin(LAS_PWM3_GPIO_Port, LAS_PWM3_Pin)
#define SET_SPEAKER_ON												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_RESET)
#define SET_SPEAKER_OFF												HAL_GPIO_WritePin(SPK_EN_GPIO_Port, SPK_EN_Pin, GPIO_PIN_SET)
#define SET_AIM_ON										   			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1)
#define SET_AIM_OFF														HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1)
#define SET_FAN_ON														HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2)
#define SET_FAN_OFF														HAL_TIM_PWM_Stop(&htim12, TIM_CHANNEL_2)
#define SET_TEC_ON														HAL_GPIO_WritePin(LAS_TEC_GPIO_Port, LAS_TEC_Pin, GPIO_PIN_SET)
#define SET_TEC_OFF														HAL_GPIO_WritePin(LAS_TEC_GPIO_Port, LAS_TEC_Pin, GPIO_PIN_RESET)
/*****************************************************************************/
typedef enum {
	CLEAR_EPROM_ALL 														= 0x01,
	CLEAR_EPROM_NVRAM														= 0x02,
	CLEAR_EPROM_FDRAM														= 0x03,
	CLEAR_EPROM_FIRMWARE_CRC										= 0x04,
	CLEAR_EPROM_DEVICE_CONFIG										= 0x05,
	CLEAR_EPROM_LOG_INFO												= 0x06
}clarmEpromCmd_t;
/*****************************************************************************/
extern I2C_HandleTypeDef hi2c1;
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart4;
extern USBH_HandleTypeDef hUsbHostFS;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern CRC_HandleTypeDef hcrc;
extern DAC_HandleTypeDef hdac;
extern TIM_HandleTypeDef htim2;//AIM PWM
extern TIM_HandleTypeDef htim3;//LED PWM
extern TIM_HandleTypeDef htim7;//DAC DMA 计时器
extern TIM_HandleTypeDef htim10;//Laser Timer
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim14;//sPlc Timer
extern RNG_HandleTypeDef hrng;
/*****************************************************************************/
extern int16_t NVRAM0[CONFIG_NVRAM_SIZE];//掉电保持寄存器 当前 包含存档寄存器
extern int16_t NVRAM1[CONFIG_NVRAM_SIZE];//掉电保持寄存器 上一次
extern int16_t FDRAM0[CONFIG_FDRAM_SIZE];//存档寄存器
extern int16_t FDRAM1[CONFIG_FDRAM_SIZE];//存档寄存器
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
extern void sPlcloadDefault(void);
extern void sPlcIsrDisable(void);
extern void sPlcIsrEnable(void);
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
extern void resetInit(void);
extern void SystemClock_Reset(void);//复位系统时钟
extern void UsbGpioReset(void);
extern void setAimBrightness(int8_t brg);//设置瞄准光亮度
extern void setFanSpeed(int16_t speed);//设置风扇转速
extern void morseCodeDiag(uint8_t diag);//诊断码
extern HAL_StatusTypeDef epromReadByte(uint16_t ReadAddr, uint8_t *rdat);//在AT24CXX指定地址读出一个数据
extern HAL_StatusTypeDef epromReadHword(uint16_t ReadAddr, uint16_t *rdat);//在AT24CXX里面的指定地址开始读出16位数
extern HAL_StatusTypeDef epromReadDword(uint16_t ReadAddr, uint32_t *rdat);////在AT24CXX里面的指定地址开始读出32位数
extern HAL_StatusTypeDef epromWriteByte(uint16_t WriteAddr, uint8_t *wdat);//在AT24CXX指定地址写入8位数据
extern HAL_StatusTypeDef epromWriteHword(uint16_t WriteAddr, uint16_t *wdat);//在AT24CXX里面的指定地址开始写入16位数
extern HAL_StatusTypeDef epromWriteDword(uint16_t WriteAddr, uint32_t *wdat);//在AT24CXX里面的指定地址开始写入32位数
extern HAL_StatusTypeDef epromRead(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);
extern HAL_StatusTypeDef epromWrite(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);
extern uint8_t sPlcEpromTest(void);
extern uint8_t checkBlank(uint32_t adr, uint32_t size);//MCU Flash 查空
void clearEprom(clarmEpromCmd_t cmd);//清除EPROM内容
void listEpromTable(void);
void softDelayMs(uint16_t ms);//软件延时
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
