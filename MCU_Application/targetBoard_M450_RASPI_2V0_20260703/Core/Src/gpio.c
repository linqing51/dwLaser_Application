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
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOG_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, STA0_LED_Pin|STA1_LED_Pin|STA2_LED_Pin|STA3_LED_Pin
                          |TEC_BREAK_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, SGATE_EN_Pin|SAFE_RESET_Pin|SPK_EN_Pin|MCP41010_SDI_Pin
                          |MCP41010_SCK_Pin|RED_LED_Pin|BLUE_LED_Pin|POWER_LED_Pin
                          |LAS1_PWM_Pin|LAS3_PWM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOF, MCP41010_CS_Pin|AIM0_ENABLE_Pin|AIM1_ENABLE_Pin|DAC8568_CLEAR_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOH, DAC8568_SCK_Pin|DAC8568_DOUT_Pin|DAC8568_NSS_Pin|MCU_BREAK_OUT_Pin
                          |TEC1_PWM_Pin|TEC3_PWM_Pin|TEC5_PWM_Pin|TEC7_PWM_Pin
                          |MPU_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LAS0_PWM_Pin|LAS2_PWM_Pin|LCM3000_I2C_EN_Pin|TPL0501_SPI3_MOSI_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOE, LAS5_PWM_Pin|LAS7_PWM_Pin|LAS4_PWM_Pin|LAS6_PWM_Pin
                          |TEC0_PWM_Pin|TEC2_PWM_Pin|TEC4_PWM_Pin|TEC6_PWM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOH, YOUT0_Pin|GAIM_SHDN_Pin|MPU_RST_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(YOUT1_GPIO_Port, YOUT1_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, PCA9546_RESET_Pin|TPL0501_SPI3_NSS_Pin|TPL0501_SPI3_SCK_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(POWER_KILL_GPIO_Port, POWER_KILL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(EPROM_NSS_GPIO_Port, EPROM_NSS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(HDMI_VCC_EA_GPIO_Port, HDMI_VCC_EA_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOG, LCM3000_EEPROM_PROTECT_Pin|HDC1080_SDA_Pin|HDC1080_SCL_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, PUMP1_PWM_Pin|PUMP0_PWM_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(VBUS_FS_EN_GPIO_Port, VBUS_FS_EN_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : STA0_LED_Pin STA1_LED_Pin STA2_LED_Pin STA3_LED_Pin */
  GPIO_InitStruct.Pin = STA0_LED_Pin|STA1_LED_Pin|STA2_LED_Pin|STA3_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pins : HT_TRAFFIC_Pin HUMIDITY_SENSOR_Pin */
  GPIO_InitStruct.Pin = HT_TRAFFIC_Pin|HUMIDITY_SENSOR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

  /*Configure GPIO pins : SGATE_EN_Pin SAFE_RESET_Pin SPK_EN_Pin MCP41010_SDI_Pin
                           MCP41010_SCK_Pin MCP41010_CS_Pin RED_LED_Pin BLUE_LED_Pin
                           POWER_LED_Pin LAS1_PWM_Pin LAS3_PWM_Pin */
  GPIO_InitStruct.Pin = SGATE_EN_Pin|SAFE_RESET_Pin|SPK_EN_Pin|MCP41010_SDI_Pin
                          |MCP41010_SCK_Pin|MCP41010_CS_Pin|RED_LED_Pin|BLUE_LED_Pin
                          |POWER_LED_Pin|LAS1_PWM_Pin|LAS3_PWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : INTRUSION_NC_Pin SGATE_NC_Pin */
  GPIO_InitStruct.Pin = INTRUSION_NC_Pin|SGATE_NC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : DAC8568_SCK_Pin DAC8568_DOUT_Pin MCU_BREAK_OUT_Pin TEC1_PWM_Pin
                           TEC3_PWM_Pin TEC5_PWM_Pin TEC7_PWM_Pin MPU_EN_Pin */
  GPIO_InitStruct.Pin = DAC8568_SCK_Pin|DAC8568_DOUT_Pin|MCU_BREAK_OUT_Pin|TEC1_PWM_Pin
                          |TEC3_PWM_Pin|TEC5_PWM_Pin|TEC7_PWM_Pin|MPU_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : DAC8568_NSS_Pin */
  GPIO_InitStruct.Pin = DAC8568_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DAC8568_NSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : AIM0_ENABLE_Pin AIM1_ENABLE_Pin DAC8568_CLEAR_Pin */
  GPIO_InitStruct.Pin = AIM0_ENABLE_Pin|AIM1_ENABLE_Pin|DAC8568_CLEAR_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  /*Configure GPIO pins : LAS0_PWM_Pin LCM3000_EEPROM_PROTECT_Pin */
  GPIO_InitStruct.Pin = LAS0_PWM_Pin|LCM3000_EEPROM_PROTECT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : LAS2_PWM_Pin LCM3000_I2C_EN_Pin */
  GPIO_InitStruct.Pin = LAS2_PWM_Pin|LCM3000_I2C_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : LAS5_PWM_Pin LAS7_PWM_Pin LAS4_PWM_Pin LAS6_PWM_Pin
                           TEC0_PWM_Pin TEC2_PWM_Pin TEC4_PWM_Pin TEC6_PWM_Pin */
  GPIO_InitStruct.Pin = LAS5_PWM_Pin|LAS7_PWM_Pin|LAS4_PWM_Pin|LAS6_PWM_Pin
                          |TEC0_PWM_Pin|TEC2_PWM_Pin|TEC4_PWM_Pin|TEC6_PWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  /*Configure GPIO pin : TEC_BREAK_Pin */
  GPIO_InitStruct.Pin = TEC_BREAK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(TEC_BREAK_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : YOUT0_Pin GAIM_SHDN_Pin */
  GPIO_InitStruct.Pin = YOUT0_Pin|GAIM_SHDN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : YOUT1_Pin */
  GPIO_InitStruct.Pin = YOUT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(YOUT1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LAS_TRAFFIC_Pin */
  GPIO_InitStruct.Pin = LAS_TRAFFIC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(LAS_TRAFFIC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : IBUS_INT0_Pin IBUS_INT3_Pin IBUS_INT2_Pin */
  GPIO_InitStruct.Pin = IBUS_INT0_Pin|IBUS_INT3_Pin|IBUS_INT2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : PCA9546_RESET_Pin */
  GPIO_InitStruct.Pin = PCA9546_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PCA9546_RESET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : IBUS_INT4_Pin IBUS_INT5_Pin MPU_INT0_Pin MPU_INT1_Pin
                           MPU_INT2_Pin MPU_INT3_Pin */
  GPIO_InitStruct.Pin = IBUS_INT4_Pin|IBUS_INT5_Pin|MPU_INT0_Pin|MPU_INT1_Pin
                          |MPU_INT2_Pin|MPU_INT3_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pins : IBUS_INT6_Pin ESTOP_NC_Pin G_DCOK_Pin IBUS_INT1_Pin */
  GPIO_InitStruct.Pin = IBUS_INT6_Pin|ESTOP_NC_Pin|G_DCOK_Pin|IBUS_INT1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pins : INTERLOCK_NC_Pin SKEY_NO_Pin FS_NC_Pin FS_NO_Pin */
  GPIO_InitStruct.Pin = INTERLOCK_NC_Pin|SKEY_NO_Pin|FS_NC_Pin|FS_NO_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  /*Configure GPIO pin : POWER_KILL_Pin */
  GPIO_InitStruct.Pin = POWER_KILL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(POWER_KILL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : MPU_RST_Pin */
  GPIO_InitStruct.Pin = MPU_RST_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MPU_RST_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : POWER_INT_Pin */
  GPIO_InitStruct.Pin = POWER_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(POWER_INT_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : EPROM_NSS_Pin */
  GPIO_InitStruct.Pin = EPROM_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(EPROM_NSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : HDMI_VCC_EA_Pin */
  GPIO_InitStruct.Pin = HDMI_VCC_EA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HDMI_VCC_EA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : TPL0501_SPI3_NSS_Pin TPL0501_SPI3_SCK_Pin */
  GPIO_InitStruct.Pin = TPL0501_SPI3_NSS_Pin|TPL0501_SPI3_SCK_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /*Configure GPIO pin : TPL0501_SPI3_MOSI_Pin */
  GPIO_InitStruct.Pin = TPL0501_SPI3_MOSI_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(TPL0501_SPI3_MOSI_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : HDC1080_SDA_Pin */
  GPIO_InitStruct.Pin = HDC1080_SDA_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(HDC1080_SDA_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : HDC1080_SCL_Pin */
  GPIO_InitStruct.Pin = HDC1080_SCL_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(HDC1080_SCL_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PUMP1_PWM_Pin PUMP0_PWM_Pin */
  GPIO_InitStruct.Pin = PUMP1_PWM_Pin|PUMP0_PWM_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : VBUS_FS_EN_Pin */
  GPIO_InitStruct.Pin = VBUS_FS_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(VBUS_FS_EN_GPIO_Port, &GPIO_InitStruct);


//======================================================
  GPIO_InitStruct.Pin = GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, GPIO_PIN_RESET);




}

/* USER CODE BEGIN 2 */

/* USER CODE END 2 */
