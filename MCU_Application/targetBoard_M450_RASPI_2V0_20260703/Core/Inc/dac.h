/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dac.h
  * @brief   This file contains all the function prototypes for
  *          the dac.c file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DAC_H__
#define __DAC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern DAC_HandleTypeDef hdac;

/* USER CODE BEGIN Private defines */
/* ???? */
/// DAC输出电压计算(单位:V)，STM32F407 DAC参考电压VREF+为3.3V
#define DAC_REF_VOLTAGE    3.3f
/// DAC分辨率(12位)最大输出值4095
#define DAC_MAX_VALUE      4095U


/* USER CODE END Private defines */

void MX_DAC_Init(void);

/* USER CODE BEGIN Prototypes */
/* ???????? */
/// DAC输出引脚: 通道1为PA4/DAC1_OUT1, 通道2为PA5/DAC1_OUT2
HAL_StatusTypeDef DAC_TEC_Init(void);

/// 设置DAC通道1(PA4)输出电压
/// voltage: 要输出的电压值(0 ~ DAC_REF_VOLTAGE)
HAL_StatusTypeDef DAC_TEC_SetChannel1Voltage(float voltage);

/// 设置DAC通道2(PA5)输出电压
/// voltage: 要输出的电压值(0 ~ DAC_REF_VOLTAGE)
HAL_StatusTypeDef DAC_TEC_SetChannel2Voltage(float voltage);

/// 同时设置DAC通道1和通道2输出电压
HAL_StatusTypeDef DAC_TEC_SetDualChannelVoltage(float ch1_voltage, float ch2_voltage);


/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __DAC_H__ */

