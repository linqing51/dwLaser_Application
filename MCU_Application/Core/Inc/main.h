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
#define DA_SYNC_Pin GPIO_PIN_13
#define DA_SYNC_GPIO_Port GPIOC
#define DA_DIN_Pin GPIO_PIN_14
#define DA_DIN_GPIO_Port GPIOC
#define DA_SCLK_Pin GPIO_PIN_15
#define DA_SCLK_GPIO_Port GPIOC
#define LPC_ISMON0_Pin GPIO_PIN_0
#define LPC_ISMON0_GPIO_Port GPIOC
#define LPB_ISMON1_Pin GPIO_PIN_1
#define LPB_ISMON1_GPIO_Port GPIOC
#define LPB_ISMON0_Pin GPIO_PIN_2
#define LPB_ISMON0_GPIO_Port GPIOC
#define LPA_ISMON1_Pin GPIO_PIN_3
#define LPA_ISMON1_GPIO_Port GPIOC
#define LPA_ISMON0_Pin GPIO_PIN_0
#define LPA_ISMON0_GPIO_Port GPIOA
#define NTC_TEMP_Pin GPIO_PIN_1
#define NTC_TEMP_GPIO_Port GPIOA
#define LASER1_PD_Pin GPIO_PIN_2
#define LASER1_PD_GPIO_Port GPIOA
#define LASER2_PD_Pin GPIO_PIN_3
#define LASER2_PD_GPIO_Port GPIOA
#define PM_ALARM_Pin GPIO_PIN_4
#define PM_ALARM_GPIO_Port GPIOA
#define SPK_DAC_Pin GPIO_PIN_5
#define SPK_DAC_GPIO_Port GPIOA
#define SPK_EN_Pin GPIO_PIN_6
#define SPK_EN_GPIO_Port GPIOA
#define LASER_PWM_Pin GPIO_PIN_7
#define LASER_PWM_GPIO_Port GPIOA
#define POWER_KEY_Pin GPIO_PIN_4
#define POWER_KEY_GPIO_Port GPIOC
#define TICK_LED_Pin GPIO_PIN_5
#define TICK_LED_GPIO_Port GPIOC
#define ERR_LED_Pin GPIO_PIN_0
#define ERR_LED_GPIO_Port GPIOB
#define SYSID0_IN_Pin GPIO_PIN_1
#define SYSID0_IN_GPIO_Port GPIOB
#define SYSID1_IN_Pin GPIO_PIN_2
#define SYSID1_IN_GPIO_Port GPIOB
#define SYSID2_IN_Pin GPIO_PIN_10
#define SYSID2_IN_GPIO_Port GPIOB
#define POWER_LED_OUT_Pin GPIO_PIN_14
#define POWER_LED_OUT_GPIO_Port GPIOB
#define LASER1_AIM_Pin GPIO_PIN_15
#define LASER1_AIM_GPIO_Port GPIOB
#define LASER2_AIM_Pin GPIO_PIN_8
#define LASER2_AIM_GPIO_Port GPIOC
#define OTG_FS_PSOC_Pin GPIO_PIN_9
#define OTG_FS_PSOC_GPIO_Port GPIOC
#define OTG_FS_PSON_Pin GPIO_PIN_8
#define OTG_FS_PSON_GPIO_Port GPIOA
#define LASER_TRIG_IN_Pin GPIO_PIN_15
#define LASER_TRIG_IN_GPIO_Port GPIOA
#define LASER_EXT_ENA_Pin GPIO_PIN_10
#define LASER_EXT_ENA_GPIO_Port GPIOC
#define ESTOP_IN_Pin GPIO_PIN_11
#define ESTOP_IN_GPIO_Port GPIOC
#define INTERLOCK_IN_Pin GPIO_PIN_12
#define INTERLOCK_IN_GPIO_Port GPIOC
#define LOCK_LED_Pin GPIO_PIN_2
#define LOCK_LED_GPIO_Port GPIOD
#define TEC_OUT_Pin GPIO_PIN_4
#define TEC_OUT_GPIO_Port GPIOB
#define ALARM_LED_OUT_Pin GPIO_PIN_5
#define ALARM_LED_OUT_GPIO_Port GPIOB
#define LASER1_LED_OUT_Pin GPIO_PIN_6
#define LASER1_LED_OUT_GPIO_Port GPIOB
#define LASER2_LED_OUT_Pin GPIO_PIN_7
#define LASER2_LED_OUT_GPIO_Port GPIOB
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
