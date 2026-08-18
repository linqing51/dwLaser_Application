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
#define BID0_Pin GPIO_PIN_2
#define BID0_GPIO_Port GPIOE
#define BID1_Pin GPIO_PIN_3
#define BID1_GPIO_Port GPIOE
#define BID2_Pin GPIO_PIN_4
#define BID2_GPIO_Port GPIOE
#define BID3_Pin GPIO_PIN_5
#define BID3_GPIO_Port GPIOE
#define RAIM_PWM_Pin GPIO_PIN_6
#define RAIM_PWM_GPIO_Port GPIOE
#define SLD1_PWM_Pin GPIO_PIN_13
#define SLD1_PWM_GPIO_Port GPIOC
#define BEEM_LED_Pin GPIO_PIN_3
#define BEEM_LED_GPIO_Port GPIOF
#define ERR_LED_Pin GPIO_PIN_4
#define ERR_LED_GPIO_Port GPIOF
#define TICK_LED_Pin GPIO_PIN_5
#define TICK_LED_GPIO_Port GPIOF
#define EPROM_NSS_Pin GPIO_PIN_6
#define EPROM_NSS_GPIO_Port GPIOF
#define EPROM_SCK_Pin GPIO_PIN_7
#define EPROM_SCK_GPIO_Port GPIOF
#define EPROM_MISO_Pin GPIO_PIN_8
#define EPROM_MISO_GPIO_Port GPIOF
#define EPROM_MOSI_Pin GPIO_PIN_9
#define EPROM_MOSI_GPIO_Port GPIOF
#define EPROM_WP_Pin GPIO_PIN_10
#define EPROM_WP_GPIO_Port GPIOF
#define LAS_LPD_Pin GPIO_PIN_0
#define LAS_LPD_GPIO_Port GPIOC
#define LAS_FPD_Pin GPIO_PIN_1
#define LAS_FPD_GPIO_Port GPIOC
#define LAS_NTC_Pin GPIO_PIN_2
#define LAS_NTC_GPIO_Port GPIOC
#define BUS_VIN_Pin GPIO_PIN_3
#define BUS_VIN_GPIO_Port GPIOC
#define SLD1_CUR_Pin GPIO_PIN_0
#define SLD1_CUR_GPIO_Port GPIOA
#define MPR0_CUR_Pin GPIO_PIN_1
#define MPR0_CUR_GPIO_Port GPIOA
#define MPR1_CUR_Pin GPIO_PIN_2
#define MPR1_CUR_GPIO_Port GPIOA
#define MPR2_CUR_Pin GPIO_PIN_3
#define MPR2_CUR_GPIO_Port GPIOA
#define MPR1_SET_Pin GPIO_PIN_4
#define MPR1_SET_GPIO_Port GPIOA
#define MPR2_SET_Pin GPIO_PIN_5
#define MPR2_SET_GPIO_Port GPIOA
#define MPR3_CUR_Pin GPIO_PIN_6
#define MPR3_CUR_GPIO_Port GPIOA
#define MPR4_CUR_Pin GPIO_PIN_7
#define MPR4_CUR_GPIO_Port GPIOA
#define HT2_NTC_Pin GPIO_PIN_4
#define HT2_NTC_GPIO_Port GPIOC
#define HT1_NTC_Pin GPIO_PIN_5
#define HT1_NTC_GPIO_Port GPIOC
#define MPR5_CUR_Pin GPIO_PIN_0
#define MPR5_CUR_GPIO_Port GPIOB
#define SLD0_CUR_Pin GPIO_PIN_1
#define SLD0_CUR_GPIO_Port GPIOB
#define MPR5_PWM_Pin GPIO_PIN_11
#define MPR5_PWM_GPIO_Port GPIOF
#define SLD0_PWM_Pin GPIO_PIN_12
#define SLD0_PWM_GPIO_Port GPIOF
#define DAC8568_DOUT_Pin GPIO_PIN_13
#define DAC8568_DOUT_GPIO_Port GPIOF
#define DAC8568_SCK_Pin GPIO_PIN_14
#define DAC8568_SCK_GPIO_Port GPIOF
#define DAC8568_SYNC_Pin GPIO_PIN_15
#define DAC8568_SYNC_GPIO_Port GPIOF
#define MPR3_PWM_Pin GPIO_PIN_0
#define MPR3_PWM_GPIO_Port GPIOG
#define MPR4_PWM_Pin GPIO_PIN_1
#define MPR4_PWM_GPIO_Port GPIOG
#define MPR0_PWM_Pin GPIO_PIN_7
#define MPR0_PWM_GPIO_Port GPIOE
#define MPR1_PWM_Pin GPIO_PIN_8
#define MPR1_PWM_GPIO_Port GPIOE
#define MPR2_PWM_Pin GPIO_PIN_9
#define MPR2_PWM_GPIO_Port GPIOE
#define MPU_STA2_Pin GPIO_PIN_10
#define MPU_STA2_GPIO_Port GPIOE
#define MPU_STA1_Pin GPIO_PIN_11
#define MPU_STA1_GPIO_Port GPIOE
#define MPU_STA0_Pin GPIO_PIN_12
#define MPU_STA0_GPIO_Port GPIOE
#define MPU_INT2_Pin GPIO_PIN_13
#define MPU_INT2_GPIO_Port GPIOE
#define MPU_INT1_Pin GPIO_PIN_14
#define MPU_INT1_GPIO_Port GPIOE
#define MPU_INT0_Pin GPIO_PIN_15
#define MPU_INT0_GPIO_Port GPIOE
#define DBG_TX_Pin GPIO_PIN_10
#define DBG_TX_GPIO_Port GPIOB
#define DBG_RX_Pin GPIO_PIN_11
#define DBG_RX_GPIO_Port GPIOB
#define ESTOP_NC_Pin GPIO_PIN_12
#define ESTOP_NC_GPIO_Port GPIOB
#define USB_HS_PSON_Pin GPIO_PIN_13
#define USB_HS_PSON_GPIO_Port GPIOB
#define USB_OTG_HS_DM_Pin GPIO_PIN_14
#define USB_OTG_HS_DM_GPIO_Port GPIOB
#define USB_OTG_HS_DP_Pin GPIO_PIN_15
#define USB_OTG_HS_DP_GPIO_Port GPIOB
#define SPK_ENA_Pin GPIO_PIN_8
#define SPK_ENA_GPIO_Port GPIOD
#define MCP41010_CS_Pin GPIO_PIN_9
#define MCP41010_CS_GPIO_Port GPIOD
#define MCP41010_SCK_Pin GPIO_PIN_10
#define MCP41010_SCK_GPIO_Port GPIOD
#define MCP41010_SDI_Pin GPIO_PIN_11
#define MCP41010_SDI_GPIO_Port GPIOD
#define PWR_LED_Pin GPIO_PIN_13
#define PWR_LED_GPIO_Port GPIOD
#define PWR_INT_Pin GPIO_PIN_14
#define PWR_INT_GPIO_Port GPIOD
#define PWR_KILL_Pin GPIO_PIN_15
#define PWR_KILL_GPIO_Port GPIOD
#define USB_FS_PSON_Pin GPIO_PIN_3
#define USB_FS_PSON_GPIO_Port GPIOG
#define GDDC_TX_Pin GPIO_PIN_6
#define GDDC_TX_GPIO_Port GPIOC
#define GDDC_RX_Pin GPIO_PIN_7
#define GDDC_RX_GPIO_Port GPIOC
#define UPLINK_TX_Pin GPIO_PIN_9
#define UPLINK_TX_GPIO_Port GPIOA
#define UPLINK_RX_Pin GPIO_PIN_10
#define UPLINK_RX_GPIO_Port GPIOA
#define USB_OTG_FS_DM_Pin GPIO_PIN_11
#define USB_OTG_FS_DM_GPIO_Port GPIOA
#define USB_OTG_FS_DP_Pin GPIO_PIN_12
#define USB_OTG_FS_DP_GPIO_Port GPIOA
#define UPLINK_NSS_Pin GPIO_PIN_15
#define UPLINK_NSS_GPIO_Port GPIOA
#define UPLINK_SCK_Pin GPIO_PIN_10
#define UPLINK_SCK_GPIO_Port GPIOC
#define UPLINK_MISO_Pin GPIO_PIN_11
#define UPLINK_MISO_GPIO_Port GPIOC
#define UPLINK_MOSI_Pin GPIO_PIN_12
#define UPLINK_MOSI_GPIO_Port GPIOC
#define ECAN_RX_Pin GPIO_PIN_0
#define ECAN_RX_GPIO_Port GPIOD
#define ECAN_TX_Pin GPIO_PIN_1
#define ECAN_TX_GPIO_Port GPIOD
#define FS_NO_Pin GPIO_PIN_15
#define FS_NO_GPIO_Port GPIOG
#define FAN_PWM_Pin GPIO_PIN_4
#define FAN_PWM_GPIO_Port GPIOB
#define FAN_FG_Pin GPIO_PIN_5
#define FAN_FG_GPIO_Port GPIOB
#define GLED_PWM_Pin GPIO_PIN_6
#define GLED_PWM_GPIO_Port GPIOB
#define RLED_PWM_Pin GPIO_PIN_7
#define RLED_PWM_GPIO_Port GPIOB
#define BLED_PWM_Pin GPIO_PIN_8
#define BLED_PWM_GPIO_Port GPIOB
#define SPK_PWM_Pin GPIO_PIN_9
#define SPK_PWM_GPIO_Port GPIOB
#define FS_NC_Pin GPIO_PIN_0
#define FS_NC_GPIO_Port GPIOE
#define ILOCK_NC_Pin GPIO_PIN_1
#define ILOCK_NC_GPIO_Port GPIOE

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
