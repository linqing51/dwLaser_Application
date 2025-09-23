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
  __HAL_RCC_GPIOE_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, NFC_RESET_Pin|LAS_PWM1_Pin|DEV_GPIO8_Pin|DEV_GPIO7_Pin
                          |DEV_GPIO6_Pin|DEV_GPIO5_Pin|DEV_GPIO4_Pin|DEV_GPIO3_Pin
                          |DEV_GPIO2_Pin|DEV_GPIO1_Pin|DEV_GPIO0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LAS_PWM0_GPIO_Port, LAS_PWM0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, TEC_PWM_Pin|EDAC7_SCK_Pin|EDAC7_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, EDAC7_SDI_Pin|MPU_USB1_PSON_Pin|USB_INT_PSON_Pin|USB_FS_SEL2_Pin
                          |ERR_LED_Pin|TICK_LED_Pin|BEEM_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, DEV_GPIO9_Pin|VN5016_CSDIS_Pin|VN5016_INPUT_Pin|SPK_EN_Pin
                          |MCP41010_CS_Pin|MCP41010_SCK_Pin|MCP41010_SDI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, PWR_LED_Pin|USB_FS_SEL_Pin|AHT_SDA_Pin|AHT_SCL_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USB_FS_PSON_GPIO_Port, USB_FS_PSON_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : NFC_RESET_Pin */
  GPIO_InitStruct.Pin = NFC_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(NFC_RESET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : NFC_INT_Pin */
  GPIO_InitStruct.Pin = NFC_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(NFC_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : FS_NC_Pin FS_NO_Pin */
  GPIO_InitStruct.Pin = FS_NC_Pin|FS_NO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : LAS_PWM1_Pin DEV_GPIO8_Pin DEV_GPIO7_Pin DEV_GPIO6_Pin
                           DEV_GPIO5_Pin DEV_GPIO4_Pin DEV_GPIO3_Pin DEV_GPIO2_Pin
                           DEV_GPIO1_Pin DEV_GPIO0_Pin */
  GPIO_InitStruct.Pin = LAS_PWM1_Pin|DEV_GPIO8_Pin|DEV_GPIO7_Pin|DEV_GPIO6_Pin
                          |DEV_GPIO5_Pin|DEV_GPIO4_Pin|DEV_GPIO3_Pin|DEV_GPIO2_Pin
                          |DEV_GPIO1_Pin|DEV_GPIO0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : LAS_PWM0_Pin */
  GPIO_InitStruct.Pin = LAS_PWM0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LAS_PWM0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : TEC_PWM_Pin */
  GPIO_InitStruct.Pin = TEC_PWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TEC_PWM_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EDAC7_SDI_Pin */
  GPIO_InitStruct.Pin = EDAC7_SDI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(EDAC7_SDI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EDAC7_SCK_Pin */
  GPIO_InitStruct.Pin = EDAC7_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(EDAC7_SCK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EDAC7_CS_Pin */
  GPIO_InitStruct.Pin = EDAC7_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(EDAC7_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : DEV_GPIO9_Pin */
  GPIO_InitStruct.Pin = DEV_GPIO9_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DEV_GPIO9_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MPU_USB1_PSON_Pin ERR_LED_Pin TICK_LED_Pin BEEM_LED_Pin */
  GPIO_InitStruct.Pin = MPU_USB1_PSON_Pin|ERR_LED_Pin|TICK_LED_Pin|BEEM_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : USB_INT_PSON_Pin USB_FS_SEL2_Pin */
  GPIO_InitStruct.Pin = USB_INT_PSON_Pin|USB_FS_SEL2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : BT_LED_Pin PWR_KEY_Pin ESTOP_NC_Pin */
  GPIO_InitStruct.Pin = BT_LED_Pin|PWR_KEY_Pin|ESTOP_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : PWR_LED_Pin USB_FS_SEL_Pin */
  GPIO_InitStruct.Pin = PWR_LED_Pin|USB_FS_SEL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : VN5016_CSDIS_Pin VN5016_INPUT_Pin SPK_EN_Pin */
  GPIO_InitStruct.Pin = VN5016_CSDIS_Pin|VN5016_INPUT_Pin|SPK_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : INTERLOCK_NC_Pin */
  GPIO_InitStruct.Pin = INTERLOCK_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(INTERLOCK_NC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MCP41010_CS_Pin */
  GPIO_InitStruct.Pin = MCP41010_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(MCP41010_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MCP41010_SCK_Pin MCP41010_SDI_Pin */
  GPIO_InitStruct.Pin = MCP41010_SCK_Pin|MCP41010_SDI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : USB_FS_PSON_Pin */
  GPIO_InitStruct.Pin = USB_FS_PSON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(USB_FS_PSON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : AHT_SDA_Pin AHT_SCL_Pin */
  GPIO_InitStruct.Pin = AHT_SDA_Pin|AHT_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
