#ifndef __SPLCMISC_H__
#define __SPLCMISC_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
//*****************************************************************************/
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <LIMITS.H>
#include "stdbool.h"
#include "stdint.h"
///*****************************************************************************/
#include "main.h"
/*****************************************************************************/
#include "sPlcConfig.h"
/*****************************************************************************/
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim2;//FAN PWM
//
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
#define GET_ESTOP_NC													HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin)
#define GET_INTERLOCK_NC											HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin)
#define GET_FSWITCH_NO												HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin)
#define GET_FSWITCH_NC												HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin)

#define SET_RED_LED_ON												HAL_GPIO_WritePin(RED_LED_OUT_GPIO_Port, RED_LED_OUT_Pin, GPIO_PIN_SET)
#define SET_RED_LED_OFF												HAL_GPIO_WritePin(RED_LED_OUT_GPIO_Port, RED_LED_OUT_Pin, GPIO_PIN_RESET)
#define SET_GREEN_LED_ON											HAL_GPIO_WritePin(GREEN_LED_OUT_GPIO_Port, GREEN_LED_OUT_Pin, GPIO_PIN_SET)
#define SET_GREEN_LED_OFF											HAL_GPIO_WritePin(GREEN_LED_OUT_GPIO_Port, GREEN_LED_OUT_Pin, GPIO_PIN_RESET)
#define SET_BLUE_LED_ON												HAL_GPIO_WritePin(BLUE_LED_OUT_GPIO_Port, BLUE_LED_OUT_Pin, GPIO_PIN_SET)
#define SET_BLUE_LED_OFF											HAL_GPIO_WritePin(BLUE_LED_OUT_GPIO_Port, BLUE_LED_OUT_Pin, GPIO_PIN_RESET)

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
void resetInit(void);
void SystemClock_Reset(void);//复位系统时钟
void UsbGpioReset(void);
/*****************************************************************************/
void sPlcLoudspeakerLoop(void);//蜂鸣器轮询
void sPlcAimLoop(void);//瞄准光轮询
void sPlcAutoFanLoop(void);//风扇速轮询程序

void setAimBrightness(int8_t brg);//设置瞄准光亮度
int16_t getAimBrightness(void);//获取瞄准光亮度
void setLaserEnable(int8_t channel, int8_t ena);//设置激光使能
void flipLaserEnable(int8_t channel);//翻转激光使能
int8_t getLaserEnable(int8_t channel);//获取激光使能
void setFanSpeed(int16_t speed);//设置风扇转速
int16_t getFanSpeed(void);//获取风扇转速
void setTecDutyCycle(int16_t dc);//设置TEC导通占空比
int16_t getTecDutyCycle(void);//获取TEC导通占空比
void setErrorLed(int8_t ena);//设置故障指示灯状态
int8_t getErrorLed(void);//获取故障指示灯状态
void flipErrorLed(void);//翻转故障指示灯状态
void setTickLed(int8_t ena);//设置心跳指示灯状态
int8_t getTickLed(void);//获取心跳指示光状态
void flipTickLed(void);//翻转心跳指示灯状态
int8_t getEmergencyStop(void);//获取急停开关状态
int8_t getInterLock(void);//获取连锁开关状态
int8_t getFootSwitchNormalOpen(void);//获取常开脚踏开关状态
int8_t getFootSwitchNormalClose(void);//获取常闭脚踏开关状态
void morseCodeDiag(uint8_t diag);//诊断码
/*****************************************************************************/
#endif







