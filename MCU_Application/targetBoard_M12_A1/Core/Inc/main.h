/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
#define FS_NO_Pin GPIO_PIN_13
#define FS_NO_GPIO_Port GPIOC
#define MCP41010_SDI_Pin GPIO_PIN_14
#define MCP41010_SDI_GPIO_Port GPIOC
#define MCP41010_SCK_Pin GPIO_PIN_15
#define MCP41010_SCK_GPIO_Port GPIOC
#define MCP41010_CS_Pin GPIO_PIN_0
#define MCP41010_CS_GPIO_Port GPIOC
#define LAS_980_DAC_Pin GPIO_PIN_4
#define LAS_980_DAC_GPIO_Port GPIOA
#define LAS_1940_DAC_Pin GPIO_PIN_5
#define LAS_1940_DAC_GPIO_Port GPIOA
#define SPK_EN_Pin GPIO_PIN_6
#define SPK_EN_GPIO_Port GPIOA
#define BEEM_LED_Pin GPIO_PIN_5
#define BEEM_LED_GPIO_Port GPIOC
#define TICK_LED_Pin GPIO_PIN_0
#define TICK_LED_GPIO_Port GPIOB
#define ERR_LED_Pin GPIO_PIN_1
#define ERR_LED_GPIO_Port GPIOB
#define HGC5615_CS_Pin GPIO_PIN_12
#define HGC5615_CS_GPIO_Port GPIOB
#define HGC5615_SCK_Pin GPIO_PIN_13
#define HGC5615_SCK_GPIO_Port GPIOB
#define HGC5615_SDI_Pin GPIO_PIN_14
#define HGC5615_SDI_GPIO_Port GPIOB
#define LAS_TEC_Pin GPIO_PIN_6
#define LAS_TEC_GPIO_Port GPIOC
#define LAS_PWM_Pin GPIO_PIN_7
#define LAS_PWM_GPIO_Port GPIOC
#define ESTOP_NC_Pin GPIO_PIN_8
#define ESTOP_NC_GPIO_Port GPIOC
#define OTG_FS_PSON_Pin GPIO_PIN_8
#define OTG_FS_PSON_GPIO_Port GPIOA
#define INTERLOCK_NC_Pin GPIO_PIN_15
#define INTERLOCK_NC_GPIO_Port GPIOA
#define FAN_PWM_Pin GPIO_PIN_4
#define FAN_PWM_GPIO_Port GPIOB
#define FAN_FG_Pin GPIO_PIN_5
#define FAN_FG_GPIO_Port GPIOB
#define FS_NC_Pin GPIO_PIN_6
#define FS_NC_GPIO_Port GPIOB
#define BLUE_LED_PWN_Pin GPIO_PIN_7
#define BLUE_LED_PWN_GPIO_Port GPIOB
#define RED_LED_PWM_Pin GPIO_PIN_8
#define RED_LED_PWM_GPIO_Port GPIOB
#define GREEN_LED_PWN_Pin GPIO_PIN_9
#define GREEN_LED_PWN_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
