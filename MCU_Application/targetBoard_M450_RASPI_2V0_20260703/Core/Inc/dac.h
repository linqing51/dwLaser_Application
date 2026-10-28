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
// DAC?��????(??��:V)??STM32F407 DAC??????VREF+??????3.3V
#define DAC_REF_VOLTAGE    3.3f
// DAC?????(12��)???????4095
#define DAC_MAX_VALUE      4095U


/* USER CODE END Private defines */

void MX_DAC_Init(void);

/* USER CODE BEGIN Prototypes */
/* ???????? */
// DAC????????????????PA4/DAC1_OUT1??PA5/DAC1_OUT2??
HAL_StatusTypeDef DAC_TEC_Init(void);

// ????DAC???1(PA4)??????
// voltage: ????????????(0 ~ DAC_REF_VOLTAGE)
HAL_StatusTypeDef DAC_TEC_SetChannel1Voltage(float voltage);

// ????DAC???2(PA5)??????
// voltage: ????????????(0 ~ DAC_REF_VOLTAGE)
HAL_StatusTypeDef DAC_TEC_SetChannel2Voltage(float voltage);

// ??????DAC???1?????2??????
HAL_StatusTypeDef DAC_TEC_SetDualChannelVoltage(float ch1_voltage, float ch2_voltage);


/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __DAC_H__ */

