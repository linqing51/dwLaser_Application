/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dac.c
  * @brief   This file provides code for the configuration
  *          of the DAC instances.
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
/* Includes ------------------------------------------------------------------*/
#include "dac.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

DAC_HandleTypeDef hdac;

/* DAC init function */
void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT1 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

void HAL_DAC_MspInit(DAC_HandleTypeDef* dacHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(dacHandle->Instance==DAC)
  {
  /* USER CODE BEGIN DAC_MspInit 0 */

  /* USER CODE END DAC_MspInit 0 */
    /* DAC clock enable */
    __HAL_RCC_DAC_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    PA5     ------> DAC_OUT2
    */
    GPIO_InitStruct.Pin = TEC0_SET_Pin|TEC1_SET_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN DAC_MspInit 1 */

  /* USER CODE END DAC_MspInit 1 */
  }
}

void HAL_DAC_MspDeInit(DAC_HandleTypeDef* dacHandle)
{

  if(dacHandle->Instance==DAC)
  {
  /* USER CODE BEGIN DAC_MspDeInit 0 */

  /* USER CODE END DAC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DAC_CLK_DISABLE();

    /**DAC GPIO Configuration
    PA4     ------> DAC_OUT1
    PA5     ------> DAC_OUT2
    */
    HAL_GPIO_DeInit(GPIOA, TEC0_SET_Pin|TEC1_SET_Pin);

  /* USER CODE BEGIN DAC_MspDeInit 1 */

  /* USER CODE END DAC_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
 ** @brief  输出DAC通道1电压
 ** @param  voltage: 要输出的电压值(0 ~ 3.3V)
 ** @retval HAL状态码
 */
HAL_StatusTypeDef DAC_TEC_SetChannel1Voltage(float voltage)
{
  /// 输入电压限幅到0~3.3V范围
  if(voltage < 0.0f) voltage = 0.0f;
  if(voltage > DAC_REF_VOLTAGE) voltage = DAC_REF_VOLTAGE;

  /// 电压转换为12位DAC数值
  uint32_t dac_value = (uint32_t)(voltage * DAC_MAX_VALUE / DAC_REF_VOLTAGE);

  /// 写入DAC通道1输出
  return HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, dac_value);
}

/**
 ** @brief  输出DAC通道2电压
 ** @param  voltage: 要输出的电压值(0 ~ 3.3V)
 ** @retval HAL状态码
 */
HAL_StatusTypeDef DAC_TEC_SetChannel2Voltage(float voltage)
{
  /// 输入电压限幅
  if(voltage < 0.0f) voltage = 0.0f;
  if(voltage > DAC_REF_VOLTAGE) voltage = DAC_REF_VOLTAGE;
  /// 电压转换为DAC数值
  uint32_t dac_value = (uint32_t)(voltage * DAC_MAX_VALUE / DAC_REF_VOLTAGE);
  /// 写入DAC通道2输出
  return HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, dac_value);
}

/**
 ** @brief  同时输出DAC通道1和通道2电压
 ** @param  ch1_voltage: 通道1电压
 ** @param  ch2_voltage: 通道2电压
 ** @retval HAL状态码
 */
HAL_StatusTypeDef DAC_TEC_SetDualChannelVoltage(float ch1_voltage, float ch2_voltage)
{
  HAL_StatusTypeDef ret = HAL_OK;

  /// 设置通道1电压
  ret = DAC_TEC_SetChannel1Voltage(ch1_voltage);
  if(ret != HAL_OK) return ret;

  /// 设置通道2电压
  ret = DAC_TEC_SetChannel2Voltage(ch2_voltage);
  return ret;
}

/* USER CODE END 1 */

