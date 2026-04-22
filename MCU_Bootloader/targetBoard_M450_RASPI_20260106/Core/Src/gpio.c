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
  __HAL_RCC_GPIOI_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, STA0_LED_Pin|STA1_LED_Pin|LAS7_PWM_Pin|LAS6_PWM_Pin
                          |LAS5_PWM_Pin|LAS4_PWM_Pin|LAS3_PWM_Pin|LAS2_PWM_Pin
                          |LAS1_PWM_Pin|LAS0_PWM_Pin|TEC_BREAK_Pin|PUMP1_PWM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOI, STA2_LED_Pin|MCP41010_SCK_Pin|MCP41010_CS_Pin|RED_LED_Pin
                          |VBUS_FS_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, STA3_LED_Pin|SPK_EN_Pin|MCP41010_SDI_Pin|YOUT0_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, BLUE_LED_Pin|SGATE_EN_Pin|DHT11_SEN_Pin|DAC8568_LDAC_Pin
                          |DAC8568_NSS_Pin|DAC8568_SCK_Pin|DAC8568_DOUT_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, DAC8568_CLEAR_Pin|LAS_BREAK_Pin|YOUT1_Pin|PUMP0_PWM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, TEC1_PWM_Pin|TEC0_PWM_Pin|GAIM_SHDN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOH, TEC3_PWM_Pin|TEC2_PWM_Pin|TEC5_PWM_Pin|TEC4_PWM_Pin
                          |TEC7_PWM_Pin|TEC6_PWM_Pin|IBUS_RESET_Pin|SAFE_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, HDC1080_SDA_Pin|HDC1080_SCL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : POWER_INT_Pin PWR_DCOK_Pin */
  GPIO_InitStruct.Pin = POWER_INT_Pin|PWR_DCOK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : STA0_LED_Pin STA1_LED_Pin POWER_KILL_Pin */
  GPIO_InitStruct.Pin = STA0_LED_Pin|STA1_LED_Pin|POWER_KILL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : STA2_LED_Pin */
  GPIO_InitStruct.Pin = STA2_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(STA2_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : STA3_LED_Pin */
  GPIO_InitStruct.Pin = STA3_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(STA3_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SPK_EN_Pin */
  GPIO_InitStruct.Pin = SPK_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(SPK_EN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : MCP41010_SDI_Pin YOUT0_Pin */
  GPIO_InitStruct.Pin = MCP41010_SDI_Pin|YOUT0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : MCP41010_SCK_Pin RED_LED_Pin VBUS_FS_EN_Pin */
  GPIO_InitStruct.Pin = MCP41010_SCK_Pin|RED_LED_Pin|VBUS_FS_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pin : MCP41010_CS_Pin */
  GPIO_InitStruct.Pin = MCP41010_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MCP41010_CS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BLUE_LED_Pin SGATE_EN_Pin DAC8568_SCK_Pin DAC8568_DOUT_Pin */
  GPIO_InitStruct.Pin = BLUE_LED_Pin|SGATE_EN_Pin|DAC8568_SCK_Pin|DAC8568_DOUT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pin : SGATE_NC_Pin */
  GPIO_InitStruct.Pin = SGATE_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(SGATE_NC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : INTRUSION_NC_Pin */
  GPIO_InitStruct.Pin = INTRUSION_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(INTRUSION_NC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : DHT11_SEN_Pin DAC8568_LDAC_Pin DAC8568_NSS_Pin */
  GPIO_InitStruct.Pin = DHT11_SEN_Pin|DAC8568_LDAC_Pin|DAC8568_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : DAC8568_CLEAR_Pin PUMP0_PWM_Pin */
  GPIO_InitStruct.Pin = DAC8568_CLEAR_Pin|PUMP0_PWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : LAS_BREAK_Pin YOUT1_Pin */
  GPIO_InitStruct.Pin = LAS_BREAK_Pin|YOUT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : LAS7_PWM_Pin LAS6_PWM_Pin LAS5_PWM_Pin LAS4_PWM_Pin
                           LAS3_PWM_Pin LAS2_PWM_Pin LAS1_PWM_Pin LAS0_PWM_Pin
                           TEC_BREAK_Pin */
  GPIO_InitStruct.Pin = LAS7_PWM_Pin|LAS6_PWM_Pin|LAS5_PWM_Pin|LAS4_PWM_Pin
                          |LAS3_PWM_Pin|LAS2_PWM_Pin|LAS1_PWM_Pin|LAS0_PWM_Pin
                          |TEC_BREAK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : TEC1_PWM_Pin TEC0_PWM_Pin */
  GPIO_InitStruct.Pin = TEC1_PWM_Pin|TEC0_PWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : TEC3_PWM_Pin TEC2_PWM_Pin TEC5_PWM_Pin TEC4_PWM_Pin
                           TEC7_PWM_Pin TEC6_PWM_Pin */
  GPIO_InitStruct.Pin = TEC3_PWM_Pin|TEC2_PWM_Pin|TEC5_PWM_Pin|TEC4_PWM_Pin
                          |TEC7_PWM_Pin|TEC6_PWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : GAIM_SHDN_Pin */
  GPIO_InitStruct.Pin = GAIM_SHDN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GAIM_SHDN_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : IBUS_INT0_Pin */
  GPIO_InitStruct.Pin = IBUS_INT0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(IBUS_INT0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : IBUS_INT1_Pin IBUS_INT2_Pin IBUS_INT3_Pin ESTOP_NC_Pin */
  GPIO_InitStruct.Pin = IBUS_INT1_Pin|IBUS_INT2_Pin|IBUS_INT3_Pin|ESTOP_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : MPU_EN_Pin MPU_INT0_Pin MPU_INT1_Pin FS_NO_Pin
                           FS_NC_Pin SKEY_NO_Pin */
  GPIO_InitStruct.Pin = MPU_EN_Pin|MPU_INT0_Pin|MPU_INT1_Pin|FS_NO_Pin
                          |FS_NC_Pin|SKEY_NO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : IBUS_RESET_Pin SAFE_RESET_Pin */
  GPIO_InitStruct.Pin = IBUS_RESET_Pin|SAFE_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : INTERLOCK_NC_Pin */
  GPIO_InitStruct.Pin = INTERLOCK_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(INTERLOCK_NC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EPROM_NSS_Pin */
  GPIO_InitStruct.Pin = EPROM_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(EPROM_NSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : HDC1080_SDA_Pin HDC1080_SCL_Pin */
  GPIO_InitStruct.Pin = HDC1080_SDA_Pin|HDC1080_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : PUMP1_PWM_Pin */
  GPIO_InitStruct.Pin = PUMP1_PWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PUMP1_PWM_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
