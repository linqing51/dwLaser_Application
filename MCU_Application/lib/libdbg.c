/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2011 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include "libdbg.h"
/*****************************************************************************/
extern UART_HandleTypeDef CONFIG_DEBUG_UART;

#pragma import(__use_no_semihosting_swi)

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;


void listNvramTable(void){//输出NVRAM分布表
	printf("************************NVRAM MAP****************************\n\n");
	printf("MR:%d---%d(size:%d byte)\n", MR_START, MR_END, CONFIG_MR_SIZE);
	printf("DM:%d---%d(size:%d byte)\n", DM_START, DM_END, CONFIG_DM_SIZE);
	printf("R:%d---%d(size:%d byte)\n", R_START, R_END, CONFIG_R_SIZE);
	printf("EM:%d---%d(size:%d byte)\n", EM_START, EM_END, CONFIG_EM_SIZE);
	printf("T_1MS:%d---%d(size:%d byte)\n", T_1MS_START, T_1MS_END, CONFIG_T_1MS_SIZE);
	printf("T_10MS:%d---%d(size:%d byte)\n",T_10MS_START, T_10MS_END, CONFIG_T_10MS_SIZE);	
	printf("T_100MS:%d---%d(size:%d byte)\n",T_100MS_START, T_100MS_END, CONFIG_T_100MS_SIZE);	
	printf("T_1MS_ENA:%d---%d(size:%d byte)\n", T_1MS_ENA_START, T_1MS_ENA_END, CONFIG_T_1MS_ENA_SIZE);
	printf("T_10MS_ENA:%d---%d(size:%d byte)\n",T_10MS_ENA_START, T_10MS_ENA_START, CONFIG_T_10MS_ENA_SIZE);	
	printf("T_100MS_ENA:%d---%d(size:%d byte)\n",T_100MS_ENA_START, T_100MS_ENA_START, CONFIG_T_100MS_ENA_SIZE);	
	printf("TD_1MS:%d---%d(size:%d byte)\n", TD_1MS_START, TD_1MS_END, CONFIG_TD_1MS_SIZE);
	printf("TD_10MS:%d---%d(size:%d byte)\n",TD_10MS_START, TD_10MS_END, CONFIG_TD_10MS_SIZE);	
	printf("TD_100MS:%d---%d(size:%d byte)\n",TD_100MS_START, TD_100MS_END, CONFIG_TD_100MS_SIZE);	
	printf("X:%d---%d(size:%d byte)\n", X_START, X_END, CONFIG_X_SIZE);
	printf("Y:%d---%d(size:%d byte)\n",Y_START, Y_END, CONFIG_Y_SIZE);	
	printf("SPREG:%d---%d(size:%d byte)\n",SPREG_START, SPREG_END, CONFIG_SPREG_SIZE);	
	printf("SPCOIL:%d---%d(size:%d byte)\n",SPCOIL_START, SPCOIL_END, CONFIG_SPCOIL_SIZE);
	printf("TMP:%d---%d(size:%d byte)\n",TMP_START, TMP_END, CONFIG_TMP_SIZE);
	printf("NVRAM size:%d byte\n", CONFIG_NVRAM_SIZE);
	printf("FDRAM size:%d byte\n", CONFIG_FDRAM_SIZE);
	printf("*************************************************************\n\n");
}

void listEpromTable(void){//输出EPROM分布表
	printf("************************EPROM MAP****************************\n\n");
	printf("MR EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MR_START, (uint32_t)CONFIG_EPROM_MR_END, (uint16_t)(CONFIG_EPROM_MR_END - CONFIG_EPROM_MR_START + 1L));
	printf("DM EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_DM_START, (uint32_t)CONFIG_EPROM_DM_END, (uint16_t)(CONFIG_EPROM_DM_END - CONFIG_EPROM_DM_START + 1L));
	printf("FD EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_FD_START, (uint32_t)CONFIG_EPROM_FD_END, ((uint16_t)CONFIG_EPROM_FD_END - CONFIG_EPROM_FD_START + 1L));
#ifdef CONFIG_EPROM_BK_START
	printf("BK EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_BK_START, (uint32_t)CONFIG_EPROM_BK_END, ((uint16_t)CONFIG_EPROM_BK_END - CONFIG_EPROM_BK_START + 1L));
#endif
	printf("MR CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MR_CRC, (uint32_t)(CONFIG_EPROM_MR_CRC + 3), 4);
	printf("DM CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_DM_CRC, (uint32_t)(CONFIG_EPROM_DM_CRC + 3), 4);
	printf("FD CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_FD_CRC, (uint32_t)(CONFIG_EPROM_FD_CRC + 3), 4);	
#ifdef CONFIG_EPROM_BK_CRC
	printf("BK CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_BK_CRC, (uint32_t)(CONFIG_EPROM_BK_CRC + 3), 4);
#endif
  printf("MCU FW CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MCU_FW_CRC, (uint32_t)(CONFIG_EPROM_MCU_FW_CRC + 3), 4);
	printf("LCD FW CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_LCD_FW_CRC, (uint32_t)(CONFIG_EPROM_LCD_FW_CRC + 3), 4);
	printf("TREATMEN_CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIF_EPROM_TREATMENT_CRC, (uint32_t)(CONFIF_EPROM_TREATMENT_CRC + 3), 4);
  printf("CFG CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_CFG_CRC, (uint32_t)(CONFIG_EPROM_CFG_CRC + 3), 4);
	printf("LOG CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_LOG_CRC, (uint32_t)(CONFIG_EPROM_LOG_CRC + 3), 4);	
  printf("TREAMENT EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_TREATMENT_START, (uint32_t)CONFIG_EPROM_TREATMENT_END, (uint16_t)(CONFIG_EPROM_TREATMENT_END - CONFIG_EPROM_TREATMENT_START + 1));
  printf("CONFIG EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_CONFIG_START, (uint32_t)CONFIG_EPROM_CONFIG_END, (uint16_t)(CONFIG_EPROM_CONFIG_END - CONFIG_EPROM_CONFIG_START + 1));
	printf("LOGINFO EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_LOGINFO_START,(uint32_t)CONFIG_EPROM_LOGINFO_END, (uint16_t)(CONFIG_EPROM_LOGINFO_END - CONFIG_EPROM_LOGINFO_START + 1));
	printf("**************************************************************\n\n");
}

int fputc(int ch,FILE *f){
	uint8_t dat;
	dat = (ch & 0xFF);
  while(__HAL_UART_GET_FLAG(&CONFIG_DEBUG_UART, UART_FLAG_TXE) == RESET);//等待 UART5 发送寄存器为空
	HAL_UART_Transmit(&CONFIG_DEBUG_UART, &dat, 1, HAL_MAX_DELAY);
	return ch;
}

int fgetc(FILE *f) {
	uint8_t dat;
	while(__HAL_UART_GET_FLAG(&CONFIG_DEBUG_UART, UART_FLAG_RXNE) == SET);
	HAL_UART_Receive(&CONFIG_DEBUG_UART, &dat, 1, 100);
	return (dat);
}


int ferror(FILE *f) {
//  /* Your implementation of ferror */
	return EOF;
}

//定义_sys_exit()以避免使用半主机模式
void _sys_exit(int x){
	x = x;
}

void _ttywrch(int ch){
	ch = ch;
}
