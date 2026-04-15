/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    gpio.c
  * @brief   This file provides code for the configuration
  *          of all used GPIO pins.
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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, MPU_PWR_Pin|TEC_GATE_Pin|SPK_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, BEEM_LED_Pin|MPU_INT1_Pin|MPU_INT0_Pin|TEC_PWM_Pin
                          |LD1_PWM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, USBH_EXT_PSON_Pin|PWR_KILL_Pin|PWR_LED_Pin|MCP41010_SDI_Pin
                          |MCP41010_SCK_Pin|ERR_LED_Pin|TICK_LED_Pin|MCP41010_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, EPROM_NSS_Pin|TEC_OUT_Pin|TEC_SCK_Pin|TEC_SYNC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : FS_NO_Pin FS_NC_Pin BT_LED_Pin MPU_SAT2_Pin
                           MPU_SAT1_Pin MPU_SAT0_Pin */
  GPIO_InitStruct.Pin = FS_NO_Pin|FS_NC_Pin|BT_LED_Pin|MPU_SAT2_Pin
                          |MPU_SAT1_Pin|MPU_SAT0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : ESTOP_NC_Pin */
  GPIO_InitStruct.Pin = ESTOP_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(ESTOP_NC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MPU_PWR_Pin TEC_GATE_Pin SPK_EN_Pin */
  GPIO_InitStruct.Pin = MPU_PWR_Pin|TEC_GATE_Pin|SPK_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : BEEM_LED_Pin MPU_INT1_Pin MPU_INT0_Pin TEC_PWM_Pin
                           LD1_PWM_Pin */
  GPIO_InitStruct.Pin = BEEM_LED_Pin|MPU_INT1_Pin|MPU_INT0_Pin|TEC_PWM_Pin
                          |LD1_PWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : USBH_EXT_PSON_Pin PWR_KILL_Pin PWR_LED_Pin MCP41010_SDI_Pin
                           MCP41010_SCK_Pin ERR_LED_Pin TICK_LED_Pin MCP41010_CS_Pin */
  GPIO_InitStruct.Pin = USBH_EXT_PSON_Pin|PWR_KILL_Pin|PWR_LED_Pin|MCP41010_SDI_Pin
                          |MCP41010_SCK_Pin|ERR_LED_Pin|TICK_LED_Pin|MCP41010_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : INTERLOCK_NC_Pin */
  GPIO_InitStruct.Pin = INTERLOCK_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INTERLOCK_NC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.Pin = GPIO_PIN_8;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : EPROM_NSS_Pin TEC_OUT_Pin TEC_SCK_Pin TEC_SYNC_Pin */
  GPIO_InitStruct.Pin = EPROM_NSS_Pin|TEC_OUT_Pin|TEC_SCK_Pin|TEC_SYNC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
