/**
  ******************************************************************************
  * @file    USB_Host/FWupgrade_Standalone/Inc/flash_if.h
  * @author  MCD Application Team
  * @brief   Header file for flash_if.c
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2017 STMicroelectronics International N.V.
  * All rights reserved.</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FLASH_IF_H
#define __FLASH_IF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);

#define BOOTLOADER_FLASH_START_ADDRESS    		ADDR_FLASH_SECTOR_0//引导程序起始地址
#define BOOTLOADER_FLASH_END_ADDRESS			(ADDR_FLASH_SECTOR_4 - 1)//引导程序起始地址
#define BOOTLOADER_FLASH_SIZE					(BOOTLOADER_FLASH_END_ADDRESS - BOOTLOADER_FLASH_START_ADDRESS + 1)//引导程序区容量
#ifdef STM32F413xx
#define APPLICATION_FLASH_START_ADDRESS        	ADDR_FLASH_SECTOR_5//应用程序起始地址
#define APPLICATION_FLASH_END_ADDRESS  			(ADDR_FLASH_SECTOR_15 + 131072 - 1)//应用程序结束地址
#define APPLICATION_FLASH_SIZE   				(APPLICATION_FLASH_END_ADDRESS - APPLICATION_FLASH_START_ADDRESS + 1)//应用程序区容量
#endif
#ifdef STM32F405xx
#define APPLICATION_FLASH_START_ADDRESS        	ADDR_FLASH_SECTOR_4//应用程序起始地址
#define APPLICATION_FLASH_END_ADDRESS  			(ADDR_FLASH_SECTOR_11 + 131072 - 1)//应用程序结束地址
#define APPLICATION_FLASH_SIZE   				(APPLICATION_FLASH_END_ADDRESS - APPLICATION_FLASH_START_ADDRESS + 1)//应用程序区容量

#endif
/* Base address of the Flash sectors Bank 1 */
#ifdef STM32F413xx
#define ADDR_FLASH_SECTOR_0     				((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     				((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     				((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     				((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     				((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     				((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     				((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     				((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     				((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     				((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    				((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    				((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */
#define ADDR_FLASH_SECTOR_12     				((uint32_t)0x08100000) /* Base @ of Sector 12, 128 Kbytes */
#define ADDR_FLASH_SECTOR_13     				((uint32_t)0x08120000) /* Base @ of Sector 13, 128 Kbytes */
#define ADDR_FLASH_SECTOR_14     				((uint32_t)0x08140000) /* Base @ of Sector 14, 128 Kbytes */
#define ADDR_FLASH_SECTOR_15     				((uint32_t)0x08160000) /* Base @ of Sector 15, 128 Kbytes */
#endif
#ifdef STM32F405xx
#define ADDR_FLASH_SECTOR_0     				((uint32_t)0x08000000) /* Base @ of Sector 0, 16 Kbytes */
#define ADDR_FLASH_SECTOR_1     				((uint32_t)0x08004000) /* Base @ of Sector 1, 16 Kbytes */
#define ADDR_FLASH_SECTOR_2     				((uint32_t)0x08008000) /* Base @ of Sector 2, 16 Kbytes */
#define ADDR_FLASH_SECTOR_3     				((uint32_t)0x0800C000) /* Base @ of Sector 3, 16 Kbytes */
#define ADDR_FLASH_SECTOR_4     				((uint32_t)0x08010000) /* Base @ of Sector 4, 64 Kbytes */
#define ADDR_FLASH_SECTOR_5     				((uint32_t)0x08020000) /* Base @ of Sector 5, 128 Kbytes */
#define ADDR_FLASH_SECTOR_6     				((uint32_t)0x08040000) /* Base @ of Sector 6, 128 Kbytes */
#define ADDR_FLASH_SECTOR_7     				((uint32_t)0x08060000) /* Base @ of Sector 7, 128 Kbytes */
#define ADDR_FLASH_SECTOR_8     				((uint32_t)0x08080000) /* Base @ of Sector 8, 128 Kbytes */
#define ADDR_FLASH_SECTOR_9     				((uint32_t)0x080A0000) /* Base @ of Sector 9, 128 Kbytes */
#define ADDR_FLASH_SECTOR_10    				((uint32_t)0x080C0000) /* Base @ of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    				((uint32_t)0x080E0000) /* Base @ of Sector 11, 128 Kbytes */
#endif
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void FLASH_If_FlashUnlock(void);
FlagStatus FLASH_If_ReadOutProtectionStatus(void);
uint32_t FLASH_If_WriteApplication(uint32_t Address, uint32_t Data);
uint32_t FLASH_lf_WriteBootload(uint32_t Address, uint32_t Data);
uint32_t FLASH_If_EraseBootload(void);//擦除BOOTLOAD
uint32_t FLASH_If_EraseApplication(void);//擦除APPLICATION
#ifdef __cplusplus
}
#endif

#endif  /* __FLASH_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
