/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "sPlc.h"
#include "sPlcEprom.h"
#include <stdio.h>
/*****************************************************************************/
/* 分块填充 [start,end]: 以固定值逐块写; 写失败经调试串口报警, 返回 0 */
static uint8_t FillRange(uint32_t start, uint32_t end, uint8_t value,
                         const char *tag, const char *stage){
	uint8_t buf[64];
	uint32_t a = start;
	if(end < start){ return 0U; }
	memset(buf, value, sizeof(buf));
	while(a <= end){
		uint32_t remain = end - a + 1UL;
		uint16_t chunk = (remain > sizeof(buf)) ? (uint16_t)sizeof(buf) : (uint16_t)remain;
		if(epromWrite(a, buf, chunk) != HAL_OK){
			printf("\r\n[EPROM ALARM] clearEprom(%s) %s write FAIL @0x%08lX\r\n",
			       tag, stage, (unsigned long)a);
			return 0U;
		}
		a += chunk;
	}
	return 1U;
}

/* 回读校验 [start,end] 全为 0x00; 读失败或任一字节不符即报警, 返回 0 */
static uint8_t VerifyRangeZero(uint32_t start, uint32_t end, const char *tag){
	uint8_t rb[64];
	uint32_t a = start;
	if(end < start){ return 0U; }
	while(a <= end){
		uint32_t remain = end - a + 1UL;
		uint16_t chunk = (remain > sizeof(rb)) ? (uint16_t)sizeof(rb) : (uint16_t)remain;
		if(epromRead(a, rb, chunk) != HAL_OK){
			printf("\r\n[EPROM ALARM] clearEprom(%s) readback FAIL @0x%08lX\r\n",
			       tag, (unsigned long)a);
			return 0U;
		}
		for(uint16_t k = 0U; k < chunk; k++){
			if(rb[k] != 0x00U){
				printf("\r\n[EPROM ALARM] clearEprom(%s) verify FAIL @0x%08lX got=0x%02X\r\n",
				       tag, (unsigned long)(a + k), rb[k]);
				return 0U;
			}
		}
		a += chunk;
	}
	return 1U;
}

/* 验证式清除: 先 0xFF 全填充 -> 再 0x00 全填充 -> 回读确认全 0;
 * 任一环节失败均通过调试串口报警。最终态为 0x00, 与历史清除结果一致。 */
static uint8_t VerifiedClear(uint32_t start, uint32_t end, const char *tag){
	if(end < start){ return 0U; }
	if(FillRange(start, end, 0xFFU, tag, "0xFF") == 0U){ return 0U; }
	if(FillRange(start, end, 0x00U, tag, "0x00") == 0U){ return 0U; }
	return VerifyRangeZero(start, end, tag);
}

void clearEprom(clarmEpromCmd_t cmd){//清除EPROM内容(验证式: 0xFF->0x00->回读, 失败串口报警)
	switch(cmd){
		case CLEAR_EPROM_ALL:{
			(void)VerifiedClear(0UL, (uint32_t)CONFIG_EPROM_SIZE - 1UL, "ALL");
			break;
		}
		case CLEAR_EPROM_NVRAM:{
			(void)VerifiedClear(CONFIG_EPROM_MR_START, CONFIG_EPROM_MR_END, "MR");
			(void)VerifiedClear(CONFIG_EPROM_DM_START, CONFIG_EPROM_DM_END, "DM");
			(void)VerifiedClear(CONFIG_EPROM_MR_CRC, CONFIG_EPROM_MR_CRC + 3UL, "MR_CRC");
			(void)VerifiedClear(CONFIG_EPROM_DM_CRC, CONFIG_EPROM_DM_CRC + 3UL, "DM_CRC");
			break;
		}
		case CLEAR_EPROM_FDRAM:{
			(void)VerifiedClear(CONFIG_EPROM_FD_START, CONFIG_EPROM_FD_END, "FD");
			(void)VerifiedClear(CONFIG_EPROM_FD_CRC, CONFIG_EPROM_FD_CRC + 3UL, "FD_CRC");
			break;
		}
#ifdef CONFIG_EPROM_BK_START
		case CLEAR_EPROM_BKRAM:{
			(void)VerifiedClear(CONFIG_EPROM_BK_START, CONFIG_EPROM_BK_END, "BK");
			(void)VerifiedClear(CONFIG_EPROM_BK_CRC, CONFIG_EPROM_BK_CRC + 3UL, "BK_CRC");
			break;
		}
#endif
		case CLEAR_EPROM_MCU_FIRMWARE_CRC:{
			(void)VerifiedClear(CONFIG_EPROM_MCU_FW_CRC, CONFIG_EPROM_MCU_FW_CRC + 3UL, "MCU_FW_CRC");
			break;
		}
		case CLEAR_EPROM_LCD_FIRMWARE_CRC:{
			(void)VerifiedClear(CONFIG_EPROM_LCD_FW_CRC, CONFIG_EPROM_LCD_FW_CRC + 3UL, "LCD_FW_CRC");
			break;
		}
		case CLEAR_EPROM_DEVICE_CONFIG:{
			(void)VerifiedClear(CONFIG_EPROM_CONFIG_START, CONFIG_EPROM_CONFIG_END, "DEV_CFG");
			break;
		}
		case CLEAR_EPROM_LOG_INFO:{
			(void)VerifiedClear(CONFIG_EPROM_LOGINFO_START, CONFIG_EPROM_LOGINFO_END, "LOG_INFO");
			break;
		}
#ifdef CONFIG_EPROM_TREATMENT_START
		case CLEAR_EPROM_TREATMENT:{//清除病历/治疗记录数据区与CRC
			(void)VerifiedClear(CONFIG_EPROM_TREATMENT_START, CONFIG_EPROM_TREATMENT_END, "TREATMENT");
			(void)VerifiedClear(CONFIG_EPROM_TREATMENT_CRC, CONFIG_EPROM_TREATMENT_CRC + 3UL, "TREATMENT_CRC");
			break;
		}
#endif
		default:break;
	}
}

uint8_t checkBlank(uint32_t adr, uint32_t size){//MCU Flash 查空
	uint8_t val;
	uint32_t i;
	for(i = 0;i < size;i ++){
		val = *(__IO uint8_t*)(adr + i);
		if(val != 0xFF){
			return false;
		}
	}
	return true;
}
