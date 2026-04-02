/******************************************************************************

                  版权所有 (C), 2013-2023, 深圳博思高科技有限公司

 ******************************************************************************
  文 件 名   : drv_usart2.h
  版 本 号   : 初稿
  作    者   : 张舵
  生成日期   : 2019年5月22日
  最近修改   :
  功能描述   : 串口2 指令接收
  函数列表   :
  修改历史   :
  1.日    期   : 2019年5月22日
    作    者   : 张舵
    修改内容   : 创建文件

******************************************************************************/

#ifndef __DRV_USART5_H
#define __DRV_USART5_H

#include "stdio.h"	
#include "string.h"
#include "stm32f4xx_hal.h"



#define USART5MAXBUFFSIZE 1024

void drv_Usart5_Init (uint32_t BaudRate);
void drv_Usart5SendString (const uint8_t *Buff);
void drv_Usart5SendData (const uint8_t *Buff, uint16_t SendSize);
void drv_Usart5RecvReset (void);
uint8_t drv_Usart5RecvOne (uint8_t *Str);
uint16_t drv_Usart5RecvAtTime (uint8_t *Buff, uint16_t RecvSize, uint32_t timeout_MilliSeconds);
uint8_t drv_Usart5Read(uint8_t *buf, uint16_t len);

uint8_t drv_Usart5_GetByte(void);
    
#endif


