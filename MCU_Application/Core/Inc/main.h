/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#define LAS_PWM1_Pin GPIO_PIN_13
#define LAS_PWM1_GPIO_Port GPIOC
#define EDAC1_SDI_Pin GPIO_PIN_14
#define EDAC1_SDI_GPIO_Port GPIOC
#define EDAC1_SCK_Pin GPIO_PIN_15
#define EDAC1_SCK_GPIO_Port GPIOC
#define EDAC1_CS_Pin GPIO_PIN_0
#define EDAC1_CS_GPIO_Port GPIOC
#define LAS_PWM0_Pin GPIO_PIN_1
#define LAS_PWM0_GPIO_Port GPIOC
#define EDAC0_SDI_Pin GPIO_PIN_2
#define EDAC0_SDI_GPIO_Port GPIOC
#define EDAC0_SCK_Pin GPIO_PIN_3
#define EDAC0_SCK_GPIO_Port GPIOC
#define SPK_DAC_Pin GPIO_PIN_4
#define SPK_DAC_GPIO_Port GPIOA
#define ADC_LAS_NTC_Pin GPIO_PIN_5
#define ADC_LAS_NTC_GPIO_Port GPIOA
#define ADC_LAS_PD_Pin GPIO_PIN_6
#define ADC_LAS_PD_GPIO_Port GPIOA
#define ADC_LAS_FBPD_Pin GPIO_PIN_7
#define ADC_LAS_FBPD_GPIO_Port GPIOA
#define FS_NC_Pin GPIO_PIN_4
#define FS_NC_GPIO_Port GPIOC
#define FS_NO_Pin GPIO_PIN_5
#define FS_NO_GPIO_Port GPIOC
#define INTERLOCK_NC_Pin GPIO_PIN_0
#define INTERLOCK_NC_GPIO_Port GPIOB
#define LAS_TEC_Pin GPIO_PIN_1
#define LAS_TEC_GPIO_Port GPIOB
#define NFC_RST_Pin GPIO_PIN_2
#define NFC_RST_GPIO_Port GPIOB
#define NFC_STA_Pin GPIO_PIN_10
#define NFC_STA_GPIO_Port GPIOB
#define EDAC0_CS_Pin GPIO_PIN_11
#define EDAC0_CS_GPIO_Port GPIOB
#define LAS_FAN_Pin GPIO_PIN_12
#define LAS_FAN_GPIO_Port GPIOB
#define TICK_LED_Pin GPIO_PIN_13
#define TICK_LED_GPIO_Port GPIOB
#define SPK_EN_Pin GPIO_PIN_14
#define SPK_EN_GPIO_Port GPIOB
#define ESTOP_NC_Pin GPIO_PIN_15
#define ESTOP_NC_GPIO_Port GPIOB
#define YELLOW_LED_Pin GPIO_PIN_6
#define YELLOW_LED_GPIO_Port GPIOC
#define RED_LED_Pin GPIO_PIN_7
#define RED_LED_GPIO_Port GPIOC
#define GREEN_LED_Pin GPIO_PIN_8
#define GREEN_LED_GPIO_Port GPIOC
#define OTG_FS_PSOC_Pin GPIO_PIN_9
#define OTG_FS_PSOC_GPIO_Port GPIOC
#define OTG_FS_PSON_Pin GPIO_PIN_8
#define OTG_FS_PSON_GPIO_Port GPIOA
#define LAS_AIM_Pin GPIO_PIN_15
#define LAS_AIM_GPIO_Port GPIOA
#define LAS_PWM3_Pin GPIO_PIN_10
#define LAS_PWM3_GPIO_Port GPIOC
#define EDAC3_SDI_Pin GPIO_PIN_11
#define EDAC3_SDI_GPIO_Port GPIOC
#define EDAC3_SCK_Pin GPIO_PIN_12
#define EDAC3_SCK_GPIO_Port GPIOC
#define EDAC3_CS_Pin GPIO_PIN_2
#define EDAC3_CS_GPIO_Port GPIOD
#define ERR_LED_Pin GPIO_PIN_3
#define ERR_LED_GPIO_Port GPIOB
#define LAS_PWM2_Pin GPIO_PIN_4
#define LAS_PWM2_GPIO_Port GPIOB
#define EDAC2_SDI_Pin GPIO_PIN_5
#define EDAC2_SDI_GPIO_Port GPIOB
#define EDAC2_SCK_Pin GPIO_PIN_6
#define EDAC2_SCK_GPIO_Port GPIOB
#define EDAC2_CS_Pin GPIO_PIN_7
#define EDAC2_CS_GPIO_Port GPIOB
#define I2C1_SCL_Pin GPIO_PIN_8
#define I2C1_SCL_GPIO_Port GPIOB
#define I2C1_SDA_Pin GPIO_PIN_9
#define I2C1_SDA_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
