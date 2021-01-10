/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
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
#define LASER_NTC_Pin GPIO_PIN_1
#define LASER_NTC_GPIO_Port GPIOA
#define LASER_PD_Pin GPIO_PIN_2
#define LASER_PD_GPIO_Port GPIOA
#define LASER_FIBER_Pin GPIO_PIN_3
#define LASER_FIBER_GPIO_Port GPIOA
#define PM_ALARM_Pin GPIO_PIN_4
#define PM_ALARM_GPIO_Port GPIOA
#define SPK_VOL_Pin GPIO_PIN_5
#define SPK_VOL_GPIO_Port GPIOA
#define SPK_SD_Pin GPIO_PIN_6
#define SPK_SD_GPIO_Port GPIOA
#define LP_PWM_Pin GPIO_PIN_7
#define LP_PWM_GPIO_Port GPIOA
#define FSWITCH_NC_Pin GPIO_PIN_4
#define FSWITCH_NC_GPIO_Port GPIOC
#define SYS_LED_ERR_Pin GPIO_PIN_5
#define SYS_LED_ERR_GPIO_Port GPIOC
#define SYS_LED_RUN_Pin GPIO_PIN_0
#define SYS_LED_RUN_GPIO_Port GPIOB
#define SYS_ID0_Pin GPIO_PIN_1
#define SYS_ID0_GPIO_Port GPIOB
#define SYS_ID1_Pin GPIO_PIN_2
#define SYS_ID1_GPIO_Port GPIOB
#define SYS_ID2_Pin GPIO_PIN_10
#define SYS_ID2_GPIO_Port GPIOB
#define LCD_RX_Pin GPIO_PIN_12
#define LCD_RX_GPIO_Port GPIOB
#define LCD_TX_Pin GPIO_PIN_13
#define LCD_TX_GPIO_Port GPIOB
#define LCD_PWR_Pin GPIO_PIN_14
#define LCD_PWR_GPIO_Port GPIOB
#define HEN_OUT0_Pin GPIO_PIN_15
#define HEN_OUT0_GPIO_Port GPIOB
#define NFC_TX_Pin GPIO_PIN_6
#define NFC_TX_GPIO_Port GPIOC
#define NFC_RX_Pin GPIO_PIN_7
#define NFC_RX_GPIO_Port GPIOC
#define HEN_OUT1_Pin GPIO_PIN_8
#define HEN_OUT1_GPIO_Port GPIOC
#define OTG_FS_PSOC_Pin GPIO_PIN_9
#define OTG_FS_PSOC_GPIO_Port GPIOC
#define OTG_FS_PSON_Pin GPIO_PIN_8
#define OTG_FS_PSON_GPIO_Port GPIOA
#define DBG_TX_Pin GPIO_PIN_9
#define DBG_TX_GPIO_Port GPIOA
#define DBG_RX_Pin GPIO_PIN_10
#define DBG_RX_GPIO_Port GPIOA
#define USB_OTG_FS_DM_Pin GPIO_PIN_11
#define USB_OTG_FS_DM_GPIO_Port GPIOA
#define USB_OTG_FS_DP_Pin GPIO_PIN_12
#define USB_OTG_FS_DP_GPIO_Port GPIOA
#define FSWITCH_NO_km_Pin GPIO_PIN_15
#define FSWITCH_NO_km_GPIO_Port GPIOA
#define FSWITCH_NO_Pin GPIO_PIN_10
#define FSWITCH_NO_GPIO_Port GPIOC
#define ESTOP_IN_Pin GPIO_PIN_11
#define ESTOP_IN_GPIO_Port GPIOC
#define INTLOCK_IN_Pin GPIO_PIN_12
#define INTLOCK_IN_GPIO_Port GPIOC
#define FAN5V_OUT_Pin GPIO_PIN_2
#define FAN5V_OUT_GPIO_Port GPIOD
#define LED_AIM_PWM_Pin GPIO_PIN_4
#define LED_AIM_PWM_GPIO_Port GPIOB
#define LED_RED_PWM_Pin GPIO_PIN_5
#define LED_RED_PWM_GPIO_Port GPIOB
#define LED_GREEN_Pin GPIO_PIN_6
#define LED_GREEN_GPIO_Port GPIOB
#define LED_BLUDE_PWM_Pin GPIO_PIN_7
#define LED_BLUDE_PWM_GPIO_Port GPIOB
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
