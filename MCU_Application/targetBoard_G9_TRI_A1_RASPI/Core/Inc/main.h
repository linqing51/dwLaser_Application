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
#define FS_NO_Pin GPIO_PIN_4
#define FS_NO_GPIO_Port GPIOE
#define FS_NC_Pin GPIO_PIN_5
#define FS_NC_GPIO_Port GPIOE
#define AIM_PWM_Pin GPIO_PIN_6
#define AIM_PWM_GPIO_Port GPIOE
#define ESTOP_NC_Pin GPIO_PIN_13
#define ESTOP_NC_GPIO_Port GPIOC
#define LAS1_CUR_Pin GPIO_PIN_0
#define LAS1_CUR_GPIO_Port GPIOC
#define LAS0_CUR_Pin GPIO_PIN_1
#define LAS0_CUR_GPIO_Port GPIOC
#define TEC0_CUR_Pin GPIO_PIN_2
#define TEC0_CUR_GPIO_Port GPIOC
#define LAS0_NTC_Pin GPIO_PIN_3
#define LAS0_NTC_GPIO_Port GPIOC
#define LAS0_LPD_Pin GPIO_PIN_0
#define LAS0_LPD_GPIO_Port GPIOA
#define LAS0_FPD_Pin GPIO_PIN_1
#define LAS0_FPD_GPIO_Port GPIOA
#define HT1_NTC_Pin GPIO_PIN_2
#define HT1_NTC_GPIO_Port GPIOA
#define HT2_NTC_Pin GPIO_PIN_3
#define HT2_NTC_GPIO_Port GPIOA
#define LAS0_SET_Pin GPIO_PIN_4
#define LAS0_SET_GPIO_Port GPIOA
#define LAS1_SET_Pin GPIO_PIN_5
#define LAS1_SET_GPIO_Port GPIOA
#define LAS0_PWM_Pin GPIO_PIN_6
#define LAS0_PWM_GPIO_Port GPIOA
#define IVIN_IS_Pin GPIO_PIN_7
#define IVIN_IS_GPIO_Port GPIOA
#define MPU_PWR_Pin GPIO_PIN_4
#define MPU_PWR_GPIO_Port GPIOC
#define TEC_GATE_Pin GPIO_PIN_5
#define TEC_GATE_GPIO_Port GPIOC
#define BT_LED_Pin GPIO_PIN_8
#define BT_LED_GPIO_Port GPIOE
#define BEEM_LED_Pin GPIO_PIN_10
#define BEEM_LED_GPIO_Port GPIOE
#define MPU_SAT2_Pin GPIO_PIN_11
#define MPU_SAT2_GPIO_Port GPIOE
#define MPU_SAT1_Pin GPIO_PIN_12
#define MPU_SAT1_GPIO_Port GPIOE
#define MPU_SAT0_Pin GPIO_PIN_13
#define MPU_SAT0_GPIO_Port GPIOE
#define MPU_INT1_Pin GPIO_PIN_14
#define MPU_INT1_GPIO_Port GPIOE
#define MPU_INT0_Pin GPIO_PIN_15
#define MPU_INT0_GPIO_Port GPIOE
#define MPU_SCL_Pin GPIO_PIN_10
#define MPU_SCL_GPIO_Port GPIOB
#define MPU_SDA_Pin GPIO_PIN_11
#define MPU_SDA_GPIO_Port GPIOB
#define MPU_NSS_Pin GPIO_PIN_12
#define MPU_NSS_GPIO_Port GPIOB
#define MPU_SCK_Pin GPIO_PIN_13
#define MPU_SCK_GPIO_Port GPIOB
#define MPU_MISO_Pin GPIO_PIN_14
#define MPU_MISO_GPIO_Port GPIOB
#define MPU_MOSI_Pin GPIO_PIN_15
#define MPU_MOSI_GPIO_Port GPIOB
#define BT_TX_Pin GPIO_PIN_8
#define BT_TX_GPIO_Port GPIOD
#define BT_RX_Pin GPIO_PIN_9
#define BT_RX_GPIO_Port GPIOD
#define USBH_EXT_PSON_Pin GPIO_PIN_10
#define USBH_EXT_PSON_GPIO_Port GPIOD
#define INTERLOCK_NC_Pin GPIO_PIN_11
#define INTERLOCK_NC_GPIO_Port GPIOD
#define GREEN_LED_Pin GPIO_PIN_12
#define GREEN_LED_GPIO_Port GPIOD
#define RED_LED_Pin GPIO_PIN_13
#define RED_LED_GPIO_Port GPIOD
#define BLUE_LED_Pin GPIO_PIN_14
#define BLUE_LED_GPIO_Port GPIOD
#define POWER_KILL_Pin GPIO_PIN_15
#define POWER_KILL_GPIO_Port GPIOD
#define DBG_TX_Pin GPIO_PIN_6
#define DBG_TX_GPIO_Port GPIOC
#define DBG_RX_Pin GPIO_PIN_7
#define DBG_RX_GPIO_Port GPIOC
#define FAN_FG_Pin GPIO_PIN_8
#define FAN_FG_GPIO_Port GPIOC
#define FAN0_PWM_Pin GPIO_PIN_9
#define FAN0_PWM_GPIO_Port GPIOC
#define POWER_INT_Pin GPIO_PIN_8
#define POWER_INT_GPIO_Port GPIOA
#define MPU_UART1_TX_Pin GPIO_PIN_9
#define MPU_UART1_TX_GPIO_Port GPIOA
#define MPU_UART1_RX_Pin GPIO_PIN_10
#define MPU_UART1_RX_GPIO_Port GPIOA
#define USB_OTG_FS_DM_Pin GPIO_PIN_11
#define USB_OTG_FS_DM_GPIO_Port GPIOA
#define USB_OTG_FS_DP_Pin GPIO_PIN_12
#define USB_OTG_FS_DP_GPIO_Port GPIOA
#define SPK_PWM_Pin GPIO_PIN_15
#define SPK_PWM_GPIO_Port GPIOA
#define GDDC_TX_Pin GPIO_PIN_10
#define GDDC_TX_GPIO_Port GPIOC
#define GDDC_RX_Pin GPIO_PIN_11
#define GDDC_RX_GPIO_Port GPIOC
#define SPK_EN_Pin GPIO_PIN_12
#define SPK_EN_GPIO_Port GPIOC
#define CAN_RX_Pin GPIO_PIN_0
#define CAN_RX_GPIO_Port GPIOD
#define CAN_TX_Pin GPIO_PIN_1
#define CAN_TX_GPIO_Port GPIOD
#define PWR_LED_Pin GPIO_PIN_2
#define PWR_LED_GPIO_Port GPIOD
#define MCP41010_SDI_Pin GPIO_PIN_3
#define MCP41010_SDI_GPIO_Port GPIOD
#define MCP41010_SCK_Pin GPIO_PIN_4
#define MCP41010_SCK_GPIO_Port GPIOD
#define ERR_LED_Pin GPIO_PIN_5
#define ERR_LED_GPIO_Port GPIOD
#define TICK_LED_Pin GPIO_PIN_6
#define TICK_LED_GPIO_Port GPIOD
#define MCP41010_CS_Pin GPIO_PIN_7
#define MCP41010_CS_GPIO_Port GPIOD
#define EPROM_SCK_Pin GPIO_PIN_3
#define EPROM_SCK_GPIO_Port GPIOB
#define EPROM_MISO_Pin GPIO_PIN_4
#define EPROM_MISO_GPIO_Port GPIOB
#define EPROM_MOSI_Pin GPIO_PIN_5
#define EPROM_MOSI_GPIO_Port GPIOB
#define EPROM_NSS_Pin GPIO_PIN_6
#define EPROM_NSS_GPIO_Port GPIOB
#define DAC7311_SDI_Pin GPIO_PIN_7
#define DAC7311_SDI_GPIO_Port GPIOB
#define DAC7311_SCK_Pin GPIO_PIN_8
#define DAC7311_SCK_GPIO_Port GPIOB
#define DAC7311_CS_Pin GPIO_PIN_9
#define DAC7311_CS_GPIO_Port GPIOB
#define TEC0_PWM_Pin GPIO_PIN_0
#define TEC0_PWM_GPIO_Port GPIOE
#define LAS1_PWM_Pin GPIO_PIN_1
#define LAS1_PWM_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
