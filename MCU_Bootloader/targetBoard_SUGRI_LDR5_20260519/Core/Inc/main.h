/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPIO_X0_Pin GPIO_PIN_2
#define GPIO_X0_GPIO_Port GPIOE
#define GPIO_X1_Pin GPIO_PIN_3
#define GPIO_X1_GPIO_Port GPIOE
#define DAC7568_SYNC_Pin GPIO_PIN_13
#define DAC7568_SYNC_GPIO_Port GPIOC
#define DAC7568_DIN_Pin GPIO_PIN_14
#define DAC7568_DIN_GPIO_Port GPIOC
#define DAC7568_SCLK_Pin GPIO_PIN_15
#define DAC7568_SCLK_GPIO_Port GPIOC
#define TEC_CUR1_Pin GPIO_PIN_0
#define TEC_CUR1_GPIO_Port GPIOC
#define LAS_CUR0_Pin GPIO_PIN_1
#define LAS_CUR0_GPIO_Port GPIOC
#define LAS_CUR1_Pin GPIO_PIN_2
#define LAS_CUR1_GPIO_Port GPIOC
#define LAS_CUR2_Pin GPIO_PIN_3
#define LAS_CUR2_GPIO_Port GPIOC
#define TEC_CUR0_Pin GPIO_PIN_0
#define TEC_CUR0_GPIO_Port GPIOA
#define LAS_NTC1_Pin GPIO_PIN_1
#define LAS_NTC1_GPIO_Port GPIOA
#define LAS_LPD1_Pin GPIO_PIN_2
#define LAS_LPD1_GPIO_Port GPIOA
#define LAS_FPD1_Pin GPIO_PIN_3
#define LAS_FPD1_GPIO_Port GPIOA
#define LAS_FPD0_Pin GPIO_PIN_6
#define LAS_FPD0_GPIO_Port GPIOA
#define TEC0_PWM_Pin GPIO_PIN_7
#define TEC0_PWM_GPIO_Port GPIOA
#define LAS_LPD0_Pin GPIO_PIN_4
#define LAS_LPD0_GPIO_Port GPIOC
#define LAS_NTC0_Pin GPIO_PIN_5
#define LAS_NTC0_GPIO_Port GPIOC
#define GPIO_Y0_Pin GPIO_PIN_0
#define GPIO_Y0_GPIO_Port GPIOB
#define GPIO_Y1_Pin GPIO_PIN_1
#define GPIO_Y1_GPIO_Port GPIOB
#define GPIO_Y2_Pin GPIO_PIN_7
#define GPIO_Y2_GPIO_Port GPIOE
#define GPIO_Y3_Pin GPIO_PIN_8
#define GPIO_Y3_GPIO_Port GPIOE
#define GPIO_Y4_Pin GPIO_PIN_9
#define GPIO_Y4_GPIO_Port GPIOE
#define GPIO_Y5_Pin GPIO_PIN_10
#define GPIO_Y5_GPIO_Port GPIOE
#define GPIO_Y6_Pin GPIO_PIN_11
#define GPIO_Y6_GPIO_Port GPIOE
#define GPIO_Y7_Pin GPIO_PIN_12
#define GPIO_Y7_GPIO_Port GPIOE
#define GPIO_X7_Pin GPIO_PIN_14
#define GPIO_X7_GPIO_Port GPIOE
#define GPIO_X6_Pin GPIO_PIN_15
#define GPIO_X6_GPIO_Port GPIOE
#define GPIO_X5_Pin GPIO_PIN_10
#define GPIO_X5_GPIO_Port GPIOB
#define GPIO_X4_Pin GPIO_PIN_11
#define GPIO_X4_GPIO_Port GPIOB
#define EPROM_NSS_Pin GPIO_PIN_12
#define EPROM_NSS_GPIO_Port GPIOB
#define EPROM_SCK_Pin GPIO_PIN_13
#define EPROM_SCK_GPIO_Port GPIOB
#define EPROM_MISO_Pin GPIO_PIN_14
#define EPROM_MISO_GPIO_Port GPIOB
#define EPROM_MOSI_Pin GPIO_PIN_15
#define EPROM_MOSI_GPIO_Port GPIOB
#define GPIO_X3_Pin GPIO_PIN_12
#define GPIO_X3_GPIO_Port GPIOD
#define GPIO_X2_Pin GPIO_PIN_13
#define GPIO_X2_GPIO_Port GPIOD
#define LAS1_AIM_Pin GPIO_PIN_14
#define LAS1_AIM_GPIO_Port GPIOD
#define COMM_TX_Pin GPIO_PIN_6
#define COMM_TX_GPIO_Port GPIOC
#define COMM_RX_Pin GPIO_PIN_7
#define COMM_RX_GPIO_Port GPIOC
#define TEC1_PWM_Pin GPIO_PIN_8
#define TEC1_PWM_GPIO_Port GPIOC
#define LAS0_PWM_Pin GPIO_PIN_9
#define LAS0_PWM_GPIO_Port GPIOC
#define USB_OTG_FS_PSON_Pin GPIO_PIN_8
#define USB_OTG_FS_PSON_GPIO_Port GPIOA
#define DBG_TX_Pin GPIO_PIN_9
#define DBG_TX_GPIO_Port GPIOA
#define DBG_RX_Pin GPIO_PIN_10
#define DBG_RX_GPIO_Port GPIOA
#define USB_OTG_FS_DM_Pin GPIO_PIN_11
#define USB_OTG_FS_DM_GPIO_Port GPIOA
#define USB_OTG_FS_DP_Pin GPIO_PIN_12
#define USB_OTG_FS_DP_GPIO_Port GPIOA
#define LAS0_AIM_Pin GPIO_PIN_15
#define LAS0_AIM_GPIO_Port GPIOA
#define LCD_TX_Pin GPIO_PIN_5
#define LCD_TX_GPIO_Port GPIOD
#define LCD_RX_Pin GPIO_PIN_6
#define LCD_RX_GPIO_Port GPIOD
#define LAS1_PWM_Pin GPIO_PIN_6
#define LAS1_PWM_GPIO_Port GPIOB
#define LAS2_PWM_Pin GPIO_PIN_7
#define LAS2_PWM_GPIO_Port GPIOB
#define TICK_LED_Pin GPIO_PIN_9
#define TICK_LED_GPIO_Port GPIOB
#define ERR_LED_Pin GPIO_PIN_0
#define ERR_LED_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
