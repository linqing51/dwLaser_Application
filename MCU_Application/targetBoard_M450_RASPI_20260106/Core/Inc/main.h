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
#define LTC2955_INT_Pin GPIO_PIN_2
#define LTC2955_INT_GPIO_Port GPIOE
#define PWR_DCOK_Pin GPIO_PIN_3
#define PWR_DCOK_GPIO_Port GPIOE
#define STA0_LED_Pin GPIO_PIN_4
#define STA0_LED_GPIO_Port GPIOE
#define STA1_LED_Pin GPIO_PIN_5
#define STA1_LED_GPIO_Port GPIOE
#define SPK_PWM_Pin GPIO_PIN_6
#define SPK_PWM_GPIO_Port GPIOE
#define STA2_LED_Pin GPIO_PIN_8
#define STA2_LED_GPIO_Port GPIOI
#define STA3_LED_Pin GPIO_PIN_13
#define STA3_LED_GPIO_Port GPIOC
#define SPK_EN_Pin GPIO_PIN_14
#define SPK_EN_GPIO_Port GPIOC
#define MCP41010_SDI_Pin GPIO_PIN_15
#define MCP41010_SDI_GPIO_Port GPIOC
#define MCP41010_SCK_Pin GPIO_PIN_9
#define MCP41010_SCK_GPIO_Port GPIOI
#define MCP41010_CS_Pin GPIO_PIN_10
#define MCP41010_CS_GPIO_Port GPIOI
#define RED_LED_Pin GPIO_PIN_11
#define RED_LED_GPIO_Port GPIOI
#define BLUE_LED_Pin GPIO_PIN_0
#define BLUE_LED_GPIO_Port GPIOF
#define SGATE_NC_Pin GPIO_PIN_1
#define SGATE_NC_GPIO_Port GPIOF
#define SGATE_EN_Pin GPIO_PIN_2
#define SGATE_EN_GPIO_Port GPIOF
#define INTRUSION_NC_Pin GPIO_PIN_3
#define INTRUSION_NC_GPIO_Port GPIOF
#define AMB_NTC_Pin GPIO_PIN_6
#define AMB_NTC_GPIO_Port GPIOF
#define HWATER_NTC_Pin GPIO_PIN_7
#define HWATER_NTC_GPIO_Port GPIOF
#define CWATER_NTC_Pin GPIO_PIN_8
#define CWATER_NTC_GPIO_Port GPIOF
#define DHT11_SEN_Pin GPIO_PIN_9
#define DHT11_SEN_GPIO_Port GPIOF
#define LAS_NTC_Pin GPIO_PIN_0
#define LAS_NTC_GPIO_Port GPIOC
#define LAS_LPD_Pin GPIO_PIN_2
#define LAS_LPD_GPIO_Port GPIOC
#define LAS_FPD_Pin GPIO_PIN_3
#define LAS_FPD_GPIO_Port GPIOC
#define TEC0_SET_Pin GPIO_PIN_4
#define TEC0_SET_GPIO_Port GPIOA
#define TEC1_SET_Pin GPIO_PIN_5
#define TEC1_SET_GPIO_Port GPIOA
#define DAC8568_LDAC_Pin GPIO_PIN_12
#define DAC8568_LDAC_GPIO_Port GPIOF
#define DAC8568_NSS_Pin GPIO_PIN_13
#define DAC8568_NSS_GPIO_Port GPIOF
#define DAC8568_SCK_Pin GPIO_PIN_14
#define DAC8568_SCK_GPIO_Port GPIOF
#define DAC8568_DOUT_Pin GPIO_PIN_15
#define DAC8568_DOUT_GPIO_Port GPIOF
#define DAC8568_CLEAR_Pin GPIO_PIN_0
#define DAC8568_CLEAR_GPIO_Port GPIOG
#define LAS_BREAK_Pin GPIO_PIN_1
#define LAS_BREAK_GPIO_Port GPIOG
#define LAS7_PWM_Pin GPIO_PIN_7
#define LAS7_PWM_GPIO_Port GPIOE
#define LAS6_PWM_Pin GPIO_PIN_8
#define LAS6_PWM_GPIO_Port GPIOE
#define LAS5_PWM_Pin GPIO_PIN_9
#define LAS5_PWM_GPIO_Port GPIOE
#define LAS4_PWM_Pin GPIO_PIN_10
#define LAS4_PWM_GPIO_Port GPIOE
#define LAS3_PWM_Pin GPIO_PIN_11
#define LAS3_PWM_GPIO_Port GPIOE
#define LAS2_PWM_Pin GPIO_PIN_12
#define LAS2_PWM_GPIO_Port GPIOE
#define LAS1_PWM_Pin GPIO_PIN_13
#define LAS1_PWM_GPIO_Port GPIOE
#define LAS0_PWM_Pin GPIO_PIN_14
#define LAS0_PWM_GPIO_Port GPIOE
#define TEC_BREAK_Pin GPIO_PIN_15
#define TEC_BREAK_GPIO_Port GPIOE
#define TEC1_PWM_Pin GPIO_PIN_10
#define TEC1_PWM_GPIO_Port GPIOB
#define TEC0_PWM_Pin GPIO_PIN_11
#define TEC0_PWM_GPIO_Port GPIOB
#define TEC3_PWM_Pin GPIO_PIN_6
#define TEC3_PWM_GPIO_Port GPIOH
#define TEC2_PWM_Pin GPIO_PIN_7
#define TEC2_PWM_GPIO_Port GPIOH
#define TEC5_PWM_Pin GPIO_PIN_8
#define TEC5_PWM_GPIO_Port GPIOH
#define TEC4_PWM_Pin GPIO_PIN_9
#define TEC4_PWM_GPIO_Port GPIOH
#define TEC7_PWN_Pin GPIO_PIN_10
#define TEC7_PWN_GPIO_Port GPIOH
#define TEC6_PWM_Pin GPIO_PIN_11
#define TEC6_PWM_GPIO_Port GPIOH
#define GAIM_PWM_Pin GPIO_PIN_12
#define GAIM_PWM_GPIO_Port GPIOH
#define ICAN_RX_Pin GPIO_PIN_12
#define ICAN_RX_GPIO_Port GPIOB
#define ICAN_TX_Pin GPIO_PIN_13
#define ICAN_TX_GPIO_Port GPIOB
#define RAIM_PWM_Pin GPIO_PIN_14
#define RAIM_PWM_GPIO_Port GPIOB
#define IBUS_INT0_Pin GPIO_PIN_15
#define IBUS_INT0_GPIO_Port GPIOB
#define GDDC_UART_TX_Pin GPIO_PIN_8
#define GDDC_UART_TX_GPIO_Port GPIOD
#define GDDC_UART_RX_Pin GPIO_PIN_9
#define GDDC_UART_RX_GPIO_Port GPIOD
#define IBUS_INT1_Pin GPIO_PIN_10
#define IBUS_INT1_GPIO_Port GPIOD
#define IBUS_INT2_Pin GPIO_PIN_11
#define IBUS_INT2_GPIO_Port GPIOD
#define IBUS_INT3_Pin GPIO_PIN_12
#define IBUS_INT3_GPIO_Port GPIOD
#define MPU_EN_Pin GPIO_PIN_2
#define MPU_EN_GPIO_Port GPIOG
#define MPU_INT0_Pin GPIO_PIN_3
#define MPU_INT0_GPIO_Port GPIOG
#define MPU_INT1_Pin GPIO_PIN_4
#define MPU_INT1_GPIO_Port GPIOG
#define FS_NO_Pin GPIO_PIN_5
#define FS_NO_GPIO_Port GPIOG
#define FS_NC_Pin GPIO_PIN_6
#define FS_NC_GPIO_Port GPIOG
#define SKEY_NO_Pin GPIO_PIN_7
#define SKEY_NO_GPIO_Port GPIOG
#define YOUT1_Pin GPIO_PIN_8
#define YOUT1_GPIO_Port GPIOG
#define MHI_UART_TX_Pin GPIO_PIN_6
#define MHI_UART_TX_GPIO_Port GPIOC
#define HMI_UART_RX_Pin GPIO_PIN_7
#define HMI_UART_RX_GPIO_Port GPIOC
#define YOUT0_Pin GPIO_PIN_8
#define YOUT0_GPIO_Port GPIOC
#define IBUS_SDA_Pin GPIO_PIN_9
#define IBUS_SDA_GPIO_Port GPIOC
#define IBUS_SCL_Pin GPIO_PIN_8
#define IBUS_SCL_GPIO_Port GPIOA
#define MPU_UART_TX_Pin GPIO_PIN_9
#define MPU_UART_TX_GPIO_Port GPIOA
#define MPU_UART_RX_Pin GPIO_PIN_10
#define MPU_UART_RX_GPIO_Port GPIOA
#define USB_OTG_FS_DM_Pin GPIO_PIN_11
#define USB_OTG_FS_DM_GPIO_Port GPIOA
#define USB_OTG_FS_DP_Pin GPIO_PIN_12
#define USB_OTG_FS_DP_GPIO_Port GPIOA
#define SWDIO_Pin GPIO_PIN_13
#define SWDIO_GPIO_Port GPIOA
#define IBUS_RESET_Pin GPIO_PIN_13
#define IBUS_RESET_GPIO_Port GPIOH
#define INTERLOCK_RESET_Pin GPIO_PIN_14
#define INTERLOCK_RESET_GPIO_Port GPIOH
#define INTERLOCK_NC_Pin GPIO_PIN_15
#define INTERLOCK_NC_GPIO_Port GPIOH
#define MPU_SPI_NSS_Pin GPIO_PIN_0
#define MPU_SPI_NSS_GPIO_Port GPIOI
#define MPU_SPI_SCK_Pin GPIO_PIN_1
#define MPU_SPI_SCK_GPIO_Port GPIOI
#define MPU_SPI_MISO_Pin GPIO_PIN_2
#define MPU_SPI_MISO_GPIO_Port GPIOI
#define MPU_SPI_MOSI_Pin GPIO_PIN_3
#define MPU_SPI_MOSI_GPIO_Port GPIOI
#define SWCLK_Pin GPIO_PIN_14
#define SWCLK_GPIO_Port GPIOA
#define EPROM_NSS_Pin GPIO_PIN_15
#define EPROM_NSS_GPIO_Port GPIOA
#define EPROM_SCK_Pin GPIO_PIN_10
#define EPROM_SCK_GPIO_Port GPIOC
#define EPROM_MISO_Pin GPIO_PIN_11
#define EPROM_MISO_GPIO_Port GPIOC
#define DBG_TX_Pin GPIO_PIN_12
#define DBG_TX_GPIO_Port GPIOC
#define ESTOP_NC_Pin GPIO_PIN_0
#define ESTOP_NC_GPIO_Port GPIOD
#define ESTOP_RESET_Pin GPIO_PIN_1
#define ESTOP_RESET_GPIO_Port GPIOD
#define DBG_RX_Pin GPIO_PIN_2
#define DBG_RX_GPIO_Port GPIOD
#define HDC1080_SDA_Pin GPIO_PIN_13
#define HDC1080_SDA_GPIO_Port GPIOG
#define HDC1080_SCL_Pin GPIO_PIN_14
#define HDC1080_SCL_GPIO_Port GPIOG
#define PUMP0_PWM_Pin GPIO_PIN_15
#define PUMP0_PWM_GPIO_Port GPIOG
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB
#define EPROM_MOSI_Pin GPIO_PIN_5
#define EPROM_MOSI_GPIO_Port GPIOB
#define ECAN_RX_Pin GPIO_PIN_8
#define ECAN_RX_GPIO_Port GPIOB
#define ECAN_TX_Pin GPIO_PIN_9
#define ECAN_TX_GPIO_Port GPIOB
#define PUMP1_PWM_Pin GPIO_PIN_0
#define PUMP1_PWM_GPIO_Port GPIOE
#define LTC2955_KILL_Pin GPIO_PIN_1
#define LTC2955_KILL_GPIO_Port GPIOE
#define VBUS_FS_EN_Pin GPIO_PIN_4
#define VBUS_FS_EN_GPIO_Port GPIOI
#define FAN2_PWM_Pin GPIO_PIN_5
#define FAN2_PWM_GPIO_Port GPIOI
#define FAN1_PWM_Pin GPIO_PIN_6
#define FAN1_PWM_GPIO_Port GPIOI
#define FAN0_PWM_Pin GPIO_PIN_7
#define FAN0_PWM_GPIO_Port GPIOI

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
