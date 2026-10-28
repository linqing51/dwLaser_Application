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
#define FS_NC_Pin GPIO_PIN_13
#define FS_NC_GPIO_Port GPIOC
#define FS_NO_Pin GPIO_PIN_0
#define FS_NO_GPIO_Port GPIOC
#define LD1_PWM_Pin GPIO_PIN_1
#define LD1_PWM_GPIO_Port GPIOC
#define LD1_CUR_Pin GPIO_PIN_2
#define LD1_CUR_GPIO_Port GPIOC
#define LD0_PWM_Pin GPIO_PIN_3
#define LD0_PWM_GPIO_Port GPIOC
#define AIM_PWM_Pin GPIO_PIN_0
#define AIM_PWM_GPIO_Port GPIOA
#define LD0_CUR_Pin GPIO_PIN_1
#define LD0_CUR_GPIO_Port GPIOA
#define TEC_PWM_Pin GPIO_PIN_2
#define TEC_PWM_GPIO_Port GPIOA
#define TEC_DAC_Pin GPIO_PIN_3
#define TEC_DAC_GPIO_Port GPIOA
#define LD0_SET_Pin GPIO_PIN_4
#define LD0_SET_GPIO_Port GPIOA
#define LD1_SET_Pin GPIO_PIN_5
#define LD1_SET_GPIO_Port GPIOA
#define TEC_CUR_Pin GPIO_PIN_6
#define TEC_CUR_GPIO_Port GPIOA
#define LAS_NTC_Pin GPIO_PIN_7
#define LAS_NTC_GPIO_Port GPIOA
#define LAS_LPD_Pin GPIO_PIN_4
#define LAS_LPD_GPIO_Port GPIOC
#define LAS_FPD_Pin GPIO_PIN_5
#define LAS_FPD_GPIO_Port GPIOC
#define HT1_NTC_Pin GPIO_PIN_0
#define HT1_NTC_GPIO_Port GPIOB
#define ESTOP_NC_Pin GPIO_PIN_1
#define ESTOP_NC_GPIO_Port GPIOB
#define USB_HS_PSON_Pin GPIO_PIN_2
#define USB_HS_PSON_GPIO_Port GPIOB
#define DBG_TX_Pin GPIO_PIN_10
#define DBG_TX_GPIO_Port GPIOB
#define DBG_RX_Pin GPIO_PIN_11
#define DBG_RX_GPIO_Port GPIOB
#define SPK_PWM_Pin GPIO_PIN_6
#define SPK_PWM_GPIO_Port GPIOC
#define SPK_EN_Pin GPIO_PIN_7
#define SPK_EN_GPIO_Port GPIOC
#define MCP41010_CS_Pin GPIO_PIN_8
#define MCP41010_CS_GPIO_Port GPIOC
#define MCP41010_SCK_Pin GPIO_PIN_9
#define MCP41010_SCK_GPIO_Port GPIOC
#define MCP41010_SDI_Pin GPIO_PIN_8
#define MCP41010_SDI_GPIO_Port GPIOA
#define GDDC_TX_Pin GPIO_PIN_9
#define GDDC_TX_GPIO_Port GPIOA
#define GDDC_RX_Pin GPIO_PIN_10
#define GDDC_RX_GPIO_Port GPIOA
#define EPROM_NSS_Pin GPIO_PIN_15
#define EPROM_NSS_GPIO_Port GPIOA
#define EPROM_SCK_Pin GPIO_PIN_10
#define EPROM_SCK_GPIO_Port GPIOC
#define EPROM_MISIO_Pin GPIO_PIN_11
#define EPROM_MISIO_GPIO_Port GPIOC
#define EPROM_MOSI_Pin GPIO_PIN_12
#define EPROM_MOSI_GPIO_Port GPIOC
#define INTERLOCK_NC_Pin GPIO_PIN_2
#define INTERLOCK_NC_GPIO_Port GPIOD
#define FAN_FG_Pin GPIO_PIN_4
#define FAN_FG_GPIO_Port GPIOB
#define FAN_PWM_Pin GPIO_PIN_5
#define FAN_PWM_GPIO_Port GPIOB
#define BLUE_LED_Pin GPIO_PIN_6
#define BLUE_LED_GPIO_Port GPIOB
#define RED_LED_Pin GPIO_PIN_7
#define RED_LED_GPIO_Port GPIOB
#define GREEN_LED_Pin GPIO_PIN_8
#define GREEN_LED_GPIO_Port GPIOB
#define USB_FS_PSON_Pin GPIO_PIN_9
#define USB_FS_PSON_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
