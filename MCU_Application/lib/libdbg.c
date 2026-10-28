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
#ifndef CONFIG_MORSECODE_DOT_MS
	#define CONFIG_MORSECODE_DOT_MS     					200
#endif
#ifndef CONFIG_MORSECODE_DASH_MS
	#define CONFIG_MORSECODE_DASH_MS   						600
#endif
#ifndef CONFIG_MORSECODE_GAP_MS
	#define CONFIG_MORSECODE_GAP_MS     					200
#endif
#ifndef CONFIG_MORSECODE_REPEAT_MS
	#define CONFIG_MORSECODE_REPEAT_MS  					2000
#endif
/*****************************************************************************/
extern UART_HandleTypeDef CONFIG_DEBUG_UART;
/*****************************************************************************/
#pragma import(__use_no_semihosting_swi)

/*
 * 莫尔斯电码表：位打包压缩存储。
 * 每个字符 1 个 uint16：
 *   高字节 = 码长（1~7 个点划符号）
 *   低字节 = 码型位图，从 bit0 起依次存放"划=0、点=1"（即点划序列反向存储，
 *            播放时从低到高逐位取出，与原顺序一致）。
 * 索引覆盖 ASCII 0x20~0x7E（含 0-9、A-Z、a-z、常用标点），无效/未定义字符
 * 码长为 0，morseCodeDiag 自动回退到 '0'。
 * 相比原"36 项字符串指针表"（36×4B 指针 + 约 6B/项字符串 ≈ 300B），
 * 全 ASCII 字符集仅 95×2B ≈ 190B，且无 RAM 指针表开销。
 */
static const uint16_t morseTable[0x5F] = {
  /* 0x20 ' ' */ 0x0000,/* 0x21 '!' */ 0x0612,/* 0x22 '"' */ 0x062D,/* 0x23 '#' */ 0x0000,
  /* 0x24 '$' */ 0x0737,/* 0x25 '%' */ 0x0000,/* 0x26 '&' */ 0x051D,/* 0x27 ''' */ 0x0621,
  /* 0x28 '(' */ 0x0512,/* 0x29 ')' */ 0x0612,/* 0x2A '*' */ 0x0000,/* 0x2B '+' */ 0x0515,
  /* 0x2C ',' */ 0x060C,/* 0x2D '-' */ 0x061E,/* 0x2E '.' */ 0x062A,/* 0x2F '/' */ 0x0516,
  /* 0x30 '0' */ 0x0500,/* 0x31 '1' */ 0x0501,/* 0x32 '2' */ 0x0503,/* 0x33 '3' */ 0x0507,
  /* 0x34 '4' */ 0x050F,/* 0x35 '5' */ 0x051F,/* 0x36 '6' */ 0x051E,/* 0x37 '7' */ 0x051C,
  /* 0x38 '8' */ 0x0518,/* 0x39 '9' */ 0x0510,/* 0x3A ':' */ 0x060E,/* 0x3B ';' */ 0x062A,
  /* 0x3C '<' */ 0x0000,/* 0x3D '=' */ 0x050E,/* 0x3E '>' */ 0x0000,/* 0x3F '?' */ 0x0633,
  /* 0x40 '@' */ 0x0629,/* 0x41 'A' */ 0x0201,/* 0x42 'B' */ 0x0407,/* 0x43 'C' */ 0x0405,
  /* 0x44 'D' */ 0x0303,/* 0x45 'E' */ 0x0101,/* 0x46 'F' */ 0x040B,/* 0x47 'G' */ 0x0304,
  /* 0x48 'H' */ 0x040F,/* 0x49 'I' */ 0x0203,/* 0x4A 'J' */ 0x0401,/* 0x4B 'K' */ 0x0302,
  /* 0x4C 'L' */ 0x040D,/* 0x4D 'M' */ 0x0200,/* 0x4E 'N' */ 0x0202,/* 0x4F 'O' */ 0x0300,
  /* 0x50 'P' */ 0x0409,/* 0x51 'Q' */ 0x0404,/* 0x52 'R' */ 0x0305,/* 0x53 'S' */ 0x0307,
  /* 0x54 'T' */ 0x0100,/* 0x55 'U' */ 0x0306,/* 0x56 'V' */ 0x0407,/* 0x57 'W' */ 0x0304,
  /* 0x58 'X' */ 0x0406,/* 0x59 'Y' */ 0x0402,/* 0x5A 'Z' */ 0x040C,/* 0x5B '[' */ 0x0000,
  /* 0x5C '\' */ 0x0000,/* 0x5D ']' */ 0x0000,/* 0x5E '^' */ 0x0000,/* 0x5F '_' */ 0x0613,
  /* 0x60 '`' */ 0x0000,/* 0x61 'a' */ 0x0201,/* 0x62 'b' */ 0x0407,/* 0x63 'c' */ 0x0405,
  /* 0x64 'd' */ 0x0303,/* 0x65 'e' */ 0x0101,/* 0x66 'f' */ 0x040B,/* 0x67 'g' */ 0x0304,
  /* 0x68 'h' */ 0x040F,/* 0x69 'i' */ 0x0203,/* 0x6A 'j' */ 0x0401,/* 0x6B 'k' */ 0x0302,
  /* 0x6C 'l' */ 0x040D,/* 0x6D 'm' */ 0x0200,/* 0x6E 'n' */ 0x0202,/* 0x6F 'o' */ 0x0300,
  /* 0x70 'p' */ 0x0409,/* 0x71 'q' */ 0x0404,/* 0x72 'r' */ 0x0305,/* 0x73 's' */ 0x0307,
  /* 0x74 't' */ 0x0100,/* 0x75 'u' */ 0x0306,/* 0x76 'v' */ 0x0407,/* 0x77 'w' */ 0x0304,
  /* 0x78 'x' */ 0x0406,/* 0x79 'y' */ 0x0402,/* 0x7A 'z' */ 0x040C,/* 0x7B '{' */ 0x0000,
  /* 0x7C '|' */ 0x0000,/* 0x7D '}' */ 0x0000,/* 0x7E '~' */ 0x0000
};

struct __FILE { int handle; /* Add whatever you need here */ };
FILE __stdout;
FILE __stdin;
/*****************************************************************************/

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
	printf("T_10MS_ENA:%d---%d(size:%d byte)\n",T_10MS_ENA_START, T_10MS_ENA_END, CONFIG_T_10MS_ENA_SIZE);	
	printf("T_100MS_ENA:%d---%d(size:%d byte)\n",T_100MS_ENA_START, T_100MS_ENA_END, CONFIG_T_100MS_ENA_SIZE);	
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

void morseCodeDiag(uint8_t diag){//莫尔斯电码诊断闪烁，循环不返回
  uint16_t code;
  uint8_t len;
  uint8_t i;
  uint8_t sym;
  if(diag < 0x20 || diag > 0x7E){//超出表范围回退到 '0'
    diag = '0';
  }
  code = morseTable[diag - 0x20];
  len = (uint8_t)(code >> 8);
  if(len == 0){//未定义字符回退到 '0'
    code = morseTable['0' - 0x20];
    len = (uint8_t)(code >> 8);
  }
  while(1){
    for(i = 0; i < len; i++){
      sym = (uint8_t)((code >> i) & 0x01);
      SET_RED_LED_ON;
      if(sym){//bit=1 为点
        HAL_Delay(CONFIG_MORSECODE_DOT_MS);
      }else{//bit=0 为划
        HAL_Delay(CONFIG_MORSECODE_DASH_MS);
      }
      SET_RED_LED_OFF;
      HAL_Delay(CONFIG_MORSECODE_GAP_MS);
    }
    HAL_Delay(CONFIG_MORSECODE_REPEAT_MS);
  }
}

