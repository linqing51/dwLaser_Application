/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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
#include "gpio.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, LAS_PWM1_Pin|EDAC1_SDI_Pin|EDAC1_SCK_Pin|EDAC1_CS_Pin
                          |LAS_PWM0_Pin|EDAC0_SDI_Pin|EDAC0_SCK_Pin|EDAC0_CS_Pin
                          |ERR_LED_Pin|LAS_PWM3_Pin|EDAC3_SDI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, NFC_RST_Pin|LAS_TEC_Pin|SPK_EN_Pin|EDAC3_CS_Pin
                          |LAS_PWM2_Pin|EDAC2_SDI_Pin|EDAC2_SCK_Pin|EDAC2_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(OTG_FS_PSON_GPIO_Port, OTG_FS_PSON_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EDAC3_SCK_GPIO_Port, EDAC3_SCK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LAS_PWM1_Pin EDAC1_SDI_Pin EDAC1_SCK_Pin LAS_PWM0_Pin
                           EDAC0_SDI_Pin EDAC0_SCK_Pin ERR_LED_Pin LAS_PWM3_Pin
                           EDAC3_SDI_Pin */
  GPIO_InitStruct.Pin = LAS_PWM1_Pin|EDAC1_SDI_Pin|EDAC1_SCK_Pin|LAS_PWM0_Pin
                          |EDAC0_SDI_Pin|EDAC0_SCK_Pin|ERR_LED_Pin|LAS_PWM3_Pin
                          |EDAC3_SDI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : EDAC1_CS_Pin */
  GPIO_InitStruct.Pin = EDAC1_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EDAC1_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EDAC0_CS_Pin */
  GPIO_InitStruct.Pin = EDAC0_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EDAC0_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : FS_NC_Pin OTG_FS_PSOC_Pin */
  GPIO_InitStruct.Pin = FS_NC_Pin|OTG_FS_PSOC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : FS_NO_Pin NFC_STA_Pin ESTOP_NC_Pin */
  GPIO_InitStruct.Pin = FS_NO_Pin|NFC_STA_Pin|ESTOP_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : INTERLOCK_NC_Pin */
  GPIO_InitStruct.Pin = INTERLOCK_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INTERLOCK_NC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : NFC_RST_Pin TICK_LED_Pin EDAC2_CS_Pin */
  GPIO_InitStruct.Pin = NFC_RST_Pin|TICK_LED_Pin|EDAC2_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LAS_TEC_Pin */
  GPIO_InitStruct.Pin = LAS_TEC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LAS_TEC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : SPK_EN_Pin EDAC3_CS_Pin LAS_PWM2_Pin EDAC2_SDI_Pin
                           EDAC2_SCK_Pin */
  GPIO_InitStruct.Pin = SPK_EN_Pin|EDAC3_CS_Pin|LAS_PWM2_Pin|EDAC2_SDI_Pin
                          |EDAC2_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : OTG_FS_PSON_Pin */
  GPIO_InitStruct.Pin = OTG_FS_PSON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(OTG_FS_PSON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EDAC3_SCK_Pin */
  GPIO_InitStruct.Pin = EDAC3_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(EDAC3_SCK_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
