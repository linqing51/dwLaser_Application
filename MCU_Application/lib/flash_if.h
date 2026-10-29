/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
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
#ifndef __FLASH_IF_H__
#define __FLASH_IF_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* 按具体型号宏探测系列(工程编译选项定义, 如STM32F405xx/STM32F103xB等);
 * 若HAL版本未定义系列宏(老版本CubeF1/F4), 在此补齐供库内条件编译使用 */
#if defined(STM32F100xB)  || defined(STM32F100xE)  || defined(STM32F101x6) || \
    defined(STM32F101xB)  || defined(STM32F101xE)  || defined(STM32F101xG) || \
    defined(STM32F102x6)  || defined(STM32F102xB)  || defined(STM32F103x6) || \
    defined(STM32F103xB)  || defined(STM32F103xE)  || defined(STM32F103xG) || \
    defined(STM32F105xC)  || defined(STM32F107xC)
  #include "stm32f1xx_hal.h"
  #ifndef STM32F1xx
    #define STM32F1xx
  #endif
#elif defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx) || \
      defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx) || \
      defined(STM32F401xC) || defined(STM32F401xE) || defined(STM32F410Tx) || defined(STM32F410Cx) || \
      defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F469xx) || \
      defined(STM32F479xx) || defined(STM32F412Cx) || defined(STM32F412Zx) || defined(STM32F412Rx) || \
      defined(STM32F412Vx) || defined(STM32F413xx) || defined(STM32F423xx)
  #include "stm32f4xx_hal.h"
  #ifndef STM32F4xx
    #define STM32F4xx
  #endif
#else
  #error "flash_if.h: only supports STM32F1xx / STM32F4xx!"
#endif

/* Exported types ------------------------------------------------------------*/
typedef  void (*pFunction)(void);

#if defined(STM32F1xx)
/* F1默认与F4相同布局: 64KB Bootloader(0x08000000~0x0800FFFF) + Application从0x08010000起
 * 小容量F1(64K/128K等)请按实际芯片调整两个END地址; 运行时擦除/写入上限由
 * FLASH_If_GetFlashEndAddr()(基于cpuGetFlashSize())动态截断, 不会越界 */
#define BOOTLOADER_FLASH_START_ADDRESS    0x08000000U//引导程序起始地址
#define BOOTLOADER_FLASH_END_ADDRESS      0x0800FFFFU//引导程序结束地址
#define BOOTLOADER_FLASH_SIZE             (BOOTLOADER_FLASH_END_ADDRESS - BOOTLOADER_FLASH_START_ADDRESS + 1U)//引导程序区容量

#define APPLICATION_FLASH_START_ADDRESS   0x08010000U//应用程序起始地址
#define APPLICATION_FLASH_END_ADDRESS     0x080FFFFFU//应用程序结束地址(默认按1MB芯片; 按实际调整)
#define APPLICATION_FLASH_SIZE            (APPLICATION_FLASH_END_ADDRESS - APPLICATION_FLASH_START_ADDRESS + 1U)//应用程序区容量

#else/* STM32F4xx */
#define BOOTLOADER_FLASH_START_ADDRESS    		ADDR_FLASH_SECTOR_0//引导程序起始地址
#define BOOTLOADER_FLASH_END_ADDRESS					(ADDR_FLASH_SECTOR_4 - 1)//引导程序起始地址
#define BOOTLOADER_FLASH_SIZE									(BOOTLOADER_FLASH_END_ADDRESS - BOOTLOADER_FLASH_START_ADDRESS + 1)//引导程序区容量

#define APPLICATION_FLASH_START_ADDRESS     	ADDR_FLASH_SECTOR_4//应用程序起始地址
#define APPLICATION_FLASH_END_ADDRESS  				(ADDR_FLASH_SECTOR_11 + 131072 - 1)//应用程序结束地址
#define APPLICATION_FLASH_SIZE   							(APPLICATION_FLASH_END_ADDRESS - APPLICATION_FLASH_START_ADDRESS + 1)//应用程序区容量

//1 Mbyte Flash memory single bank vs dual bank organization
/* Base address of the Flash sectors Bank 1 */
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
#endif/* STM32F1xx / STM32F4xx */

/* Exported macros -----------------------------------------------------------*/
/* 全部可清除的FLASH错误/状态标志(供擦写前清陈旧标志, 调试中断后必用):
 * F1: EOP/WRPERR/PGERR/OPTVERR (无OPERR/PGSERR)
 * F4: EOP/OPERR/WRPERR/PGAERR/PGPERR/PGSERR
 * BSY只读, 不可写清除 */
#if defined(STM32F1xx)
#define FLASH_IF_ALL_CLEAR_FLAGS  (FLASH_FLAG_EOP    | FLASH_FLAG_WRPERR | \
                                   FLASH_FLAG_PGERR  | FLASH_FLAG_OPTVERR)
#else
#define FLASH_IF_ALL_CLEAR_FLAGS  (FLASH_FLAG_EOP   | FLASH_FLAG_OPERR | \
                                   FLASH_FLAG_WRPERR| FLASH_FLAG_PGAERR| \
                                   FLASH_FLAG_PGPERR| FLASH_FLAG_PGSERR)
#endif

/* Exported functions ------------------------------------------------------- */
void FLASH_If_FlashUnlock(void);
FlagStatus FLASH_If_ReadOutProtectionStatus(void);
uint32_t FLASH_If_Read(uint32_t Address);//读Flash(32位, F1/F4全系列)
uint32_t FLASH_If_Write(uint32_t Address, uint32_t Data);
uint32_t FLASH_If_EraseBootload(void);//擦除BOOTLOADER
uint32_t FLASH_If_EraseApplication(void);//擦除APPLICATION
uint32_t FLASH_If_WriteApplication(uint32_t Address, uint32_t Data);
uint32_t FLASH_lf_WriteBootload(uint32_t Address, uint32_t Data);
#ifdef __cplusplus
}
#endif

#endif  /* __FLASH_IF_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
