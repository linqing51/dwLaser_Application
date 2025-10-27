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
#define NFC_RESET_Pin GPIO_PIN_2
#define NFC_RESET_GPIO_Port GPIOE
#define NFC_INT_Pin GPIO_PIN_3
#define NFC_INT_GPIO_Port GPIOE
#define FS_NC_Pin GPIO_PIN_4
#define FS_NC_GPIO_Port GPIOE
#define FS_NO_Pin GPIO_PIN_5
#define FS_NO_GPIO_Port GPIOE
#define LAS_PWM1_Pin GPIO_PIN_6
#define LAS_PWM1_GPIO_Port GPIOE
#define LAS_PWM0_Pin GPIO_PIN_13
#define LAS_PWM0_GPIO_Port GPIOC
#define TEC_PWM_Pin GPIO_PIN_0
#define TEC_PWM_GPIO_Port GPIOF
#define AIM_PWM_Pin GPIO_PIN_6
#define AIM_PWM_GPIO_Port GPIOF
#define VN5016_CUR_Pin GPIO_PIN_0
#define VN5016_CUR_GPIO_Port GPIOC
#define LD1_CUR_Pin GPIO_PIN_1
#define LD1_CUR_GPIO_Port GPIOC
#define LD0_CUR_Pin GPIO_PIN_2
#define LD0_CUR_GPIO_Port GPIOC
#define TEC_CUR_Pin GPIO_PIN_3
#define TEC_CUR_GPIO_Port GPIOC
#define LD1_SET_Pin GPIO_PIN_4
#define LD1_SET_GPIO_Port GPIOA
#define LD0_SET_Pin GPIO_PIN_5
#define LD0_SET_GPIO_Port GPIOA
#define IVIN_IS_Pin GPIO_PIN_6
#define IVIN_IS_GPIO_Port GPIOA
#define LAS_NTC_Pin GPIO_PIN_7
#define LAS_NTC_GPIO_Port GPIOA
#define LAS_LPD_Pin GPIO_PIN_4
#define LAS_LPD_GPIO_Port GPIOC
#define LAS_FPD_Pin GPIO_PIN_5
#define LAS_FPD_GPIO_Port GPIOC
#define HT2_NTC_Pin GPIO_PIN_0
#define HT2_NTC_GPIO_Port GPIOB
#define HT1_NTC_Pin GPIO_PIN_1
#define HT1_NTC_GPIO_Port GPIOB
#define EDAC7_SDI_Pin GPIO_PIN_2
#define EDAC7_SDI_GPIO_Port GPIOB
#define EDAC7_SCK_Pin GPIO_PIN_11
#define EDAC7_SCK_GPIO_Port GPIOF
#define EDAC7_CS_Pin GPIO_PIN_12
#define EDAC7_CS_GPIO_Port GPIOF
#define MPU_POLL_Pin GPIO_PIN_13
#define MPU_POLL_GPIO_Port GPIOF
#define DEV_SPI_INT0_Pin GPIO_PIN_14
#define DEV_SPI_INT0_GPIO_Port GPIOF
#define DEV_SPI_INT1_Pin GPIO_PIN_15
#define DEV_SPI_INT1_GPIO_Port GPIOF
#define DEV_SPI_INT2_Pin GPIO_PIN_0
#define DEV_SPI_INT2_GPIO_Port GPIOG
#define MPU_RESET_Pin GPIO_PIN_1
#define MPU_RESET_GPIO_Port GPIOG
#define DEV_SPI_STA_Pin GPIO_PIN_7
#define DEV_SPI_STA_GPIO_Port GPIOE
#define MPU_REFLASH_Pin GPIO_PIN_12
#define MPU_REFLASH_GPIO_Port GPIOE
#define MPU_USB_OTG_PSON_Pin GPIO_PIN_14
#define MPU_USB_OTG_PSON_GPIO_Port GPIOE
#define MPU_USB_OTG_ID_Pin GPIO_PIN_15
#define MPU_USB_OTG_ID_GPIO_Port GPIOE
#define DEV_I2C2_SCL_Pin GPIO_PIN_10
#define DEV_I2C2_SCL_GPIO_Port GPIOB
#define DEV_I2C2_SDA_Pin GPIO_PIN_11
#define DEV_I2C2_SDA_GPIO_Port GPIOB
#define MPU_USB1_PSON_LEGACY_Pin GPIO_PIN_12
#define MPU_USB1_PSON_LEGACY_GPIO_Port GPIOB
#define USB_HS_PSON_LEGACY_Pin GPIO_PIN_13
#define USB_HS_PSON_LEGACY_GPIO_Port GPIOB
#define USBA1_PSON_Pin GPIO_PIN_14
#define USBA1_PSON_GPIO_Port GPIOB
#define USBA1_SEL_Pin GPIO_PIN_15
#define USBA1_SEL_GPIO_Port GPIOB
#define MPU_BT_TXD_Pin GPIO_PIN_8
#define MPU_BT_TXD_GPIO_Port GPIOD
#define MPU_BT_RXD_Pin GPIO_PIN_9
#define MPU_BT_RXD_GPIO_Port GPIOD
#define BT_LED_Pin GPIO_PIN_10
#define BT_LED_GPIO_Port GPIOD
#define PWR_KEY_Pin GPIO_PIN_11
#define PWR_KEY_GPIO_Port GPIOD
#define FAN_FG_Pin GPIO_PIN_12
#define FAN_FG_GPIO_Port GPIOD
#define FAN_PWM_Pin GPIO_PIN_13
#define FAN_PWM_GPIO_Port GPIOD
#define PWR_LED_Pin GPIO_PIN_14
#define PWR_LED_GPIO_Port GPIOD
#define USBA0_SEL_Pin GPIO_PIN_15
#define USBA0_SEL_GPIO_Port GPIOD
#define VN5016_CSDIS_Pin GPIO_PIN_2
#define VN5016_CSDIS_GPIO_Port GPIOG
#define VN5016_INPUT_Pin GPIO_PIN_3
#define VN5016_INPUT_GPIO_Port GPIOG
#define INTERLOCK_NC_Pin GPIO_PIN_4
#define INTERLOCK_NC_GPIO_Port GPIOG
#define SPK_EN_Pin GPIO_PIN_5
#define SPK_EN_GPIO_Port GPIOG
#define MCP41010_CS_Pin GPIO_PIN_6
#define MCP41010_CS_GPIO_Port GPIOG
#define MCP41010_SCK_Pin GPIO_PIN_7
#define MCP41010_SCK_GPIO_Port GPIOG
#define MCP41010_SDI_Pin GPIO_PIN_8
#define MCP41010_SDI_GPIO_Port GPIOG
#define SPK_PWM_Pin GPIO_PIN_6
#define SPK_PWM_GPIO_Port GPIOC
#define BLUE_LED_Pin GPIO_PIN_7
#define BLUE_LED_GPIO_Port GPIOC
#define RED_LED_Pin GPIO_PIN_8
#define RED_LED_GPIO_Port GPIOC
#define GREEN_LED_Pin GPIO_PIN_9
#define GREEN_LED_GPIO_Port GPIOC
#define USB_FS_PSON_LEGACY_Pin GPIO_PIN_8
#define USB_FS_PSON_LEGACY_GPIO_Port GPIOA
#define DBG_TX_Pin GPIO_PIN_9
#define DBG_TX_GPIO_Port GPIOA
#define DBG_RX_Pin GPIO_PIN_10
#define DBG_RX_GPIO_Port GPIOA
#define USB_OTG_FS_DM_Pin GPIO_PIN_11
#define USB_OTG_FS_DM_GPIO_Port GPIOA
#define USB_OTG_FS_DP_Pin GPIO_PIN_12
#define USB_OTG_FS_DP_GPIO_Port GPIOA
#define DEV_NSS_Pin GPIO_PIN_15
#define DEV_NSS_GPIO_Port GPIOA
#define DEV_SCK_Pin GPIO_PIN_10
#define DEV_SCK_GPIO_Port GPIOC
#define DEV_MISO_Pin GPIO_PIN_11
#define DEV_MISO_GPIO_Port GPIOC
#define DEV_MOSI_Pin GPIO_PIN_12
#define DEV_MOSI_GPIO_Port GPIOC
#define ESTOP_NC_Pin GPIO_PIN_0
#define ESTOP_NC_GPIO_Port GPIOD
#define AHT_SDA_Pin GPIO_PIN_1
#define AHT_SDA_GPIO_Port GPIOD
#define AHT_SCL_Pin GPIO_PIN_2
#define AHT_SCL_GPIO_Port GPIOD
#define USBA0_PSON_Pin GPIO_PIN_3
#define USBA0_PSON_GPIO_Port GPIOD
#define USBD0_PSON_Pin GPIO_PIN_4
#define USBD0_PSON_GPIO_Port GPIOD
#define GDDC_TX_Pin GPIO_PIN_5
#define GDDC_TX_GPIO_Port GPIOD
#define GDDC_RX_Pin GPIO_PIN_6
#define GDDC_RX_GPIO_Port GPIOD
#define USBD0_ID_Pin GPIO_PIN_7
#define USBD0_ID_GPIO_Port GPIOD
#define NFC_RX_Pin GPIO_PIN_9
#define NFC_RX_GPIO_Port GPIOG
#define MPU_3V3_EN_Pin GPIO_PIN_11
#define MPU_3V3_EN_GPIO_Port GPIOG
#define MPU_1V8_EN_Pin GPIO_PIN_12
#define MPU_1V8_EN_GPIO_Port GPIOG
#define MPU_1V2_EN_Pin GPIO_PIN_13
#define MPU_1V2_EN_GPIO_Port GPIOG
#define NFC_TX_Pin GPIO_PIN_14
#define NFC_TX_GPIO_Port GPIOG
#define ERR_LED_Pin GPIO_PIN_5
#define ERR_LED_GPIO_Port GPIOB
#define TICK_LED_Pin GPIO_PIN_6
#define TICK_LED_GPIO_Port GPIOB
#define BEEM_LED_Pin GPIO_PIN_7
#define BEEM_LED_GPIO_Port GPIOB
#define EPROM_SCL_Pin GPIO_PIN_8
#define EPROM_SCL_GPIO_Port GPIOB
#define EPROM_SDA_Pin GPIO_PIN_9
#define EPROM_SDA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
