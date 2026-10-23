#include "sPlc.h"
#include "sPlcEprom.h"
/*****************************************************************************/
void listEpromTable(void){//输出EPROM分布表
	int32_t tmp;
	uint8_t eprom_id[4];
	epromReadDeviceId(eprom_id);
  
//  //配置EPROM数据地址
//#define CONFIG_EPROM_MR_START									(0x0L)//
//#define CONFIG_EPROM_MR_END										(CONFIG_EPROM_MR_START + MR_END - MR_START)
//#define CONFIG_EPROM_DM_START									(CONFIG_EPROM_MR_END + 1)//NVRAM中DM在EPROM储存地址
//#define CONFIG_EPROM_DM_END										(CONFIG_EPROM_DM_START + DM_END - DM_START)

//#define CONFIG_EPROM_FD_SCHEME_SIZE						((FD_SCHEME_END_0 - FD_SCHEME_START_0 + 1) * 2)//单个方案占用的EPROM空间
//#define CONFIG_EPROM_FD_START									(CONFIG_EPROM_DM_END + 1)
//#define CONFIG_EPROM_FD_END										(CONFIG_EPROM_FD_START + FD_END - FD_START)

//#define CONFIG_EPROM_MR_CRC										(CONFIG_EPROM_DM_CRC - 4L + 1L)//4B MR NVRAM CRC32 硬件计算
//#define CONFIG_EPROM_DM_CRC										(CONFIG_EPROM_FD_CRC - 4L + 1L)//4B DM NVRAM CRC32 硬件计算
//#define CONFIG_EPROM_FD_CRC										(CONFIG_EPROM_MCU_FW_CRC - 4L + 1L)//4B FD NVRAM CRC32 硬件计算
//#define CONFIG_EPROM_MCU_FW_CRC								(CONFIG_EPROM_LCD_FW_CRC - 4L + 1L)//4B MCU固件CRC32值 软件计算
//#define CONFIG_EPROM_LCD_FW_CRC								(CONFIF_EPROM_TREATMENT_CRC - 4L + 1L)//4B LCD固件CRC32值 软件计算
//#define CONFIF_EPROM_TREATMENT_CRC						(CONFIG_EPROM_CFG_CRC - 4L + 1L)//4B treatment CRC32值 硬件计算
//#define CONFIG_EPROM_CFG_CRC									(CONFIG_EPROM_LOG_CRC - 4L + 1L)//4B deviceConfig CRC32值 硬件计算
//#define CONFIG_EPROM_LOG_CRC									(CONFIG_EPROM_TREATMENT_START - 4L + 1L)//4B logInfo CRC32值 硬件计算

//#define CONFIG_EPROM_TREATMENT_START					(CONFIG_EPROM_TREATMENT_END - (32L * 1024L) + 1L)
//#define CONFIG_EPROM_TREATMENT_END						(CONFIG_EPROM_CONFIG_START - 1L)

//#define CONFIG_EPROM_CONFIG_START							(CONFIG_EPROM_CONFIG_END - 1024L + 1L)//1024B 配置信息区
//#define CONFIG_EPROM_CONFIG_END								(CONFIG_EPROM_LOGINFO_START - 1L)
//#define CONFIG_EPROM_LOGINFO_START						(CONFIG_EPROM_LOGINFO_END - 256L + 1L)//256B 记录信息区 
//#define CONFIG_EPROM_LOGINFO_END							(CONFIG_EPROM_SIZE - 1L)

	printf("************************EPROM MAP****************************\n\n");
	printf("EPROM ID:%02X%02X%02X%02X\n", eprom_id[0], eprom_id[1], eprom_id[2], eprom_id[3]);
	printf("MR EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MR_START, (uint32_t)CONFIG_EPROM_MR_END, (uint16_t)CONFIG_MRRAM_SIZE);
	printf("DM EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_DM_START, (uint32_t)CONFIG_EPROM_DM_END, (uint16_t)CONFIG_DMRAM_SIZE);
	printf("FD EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_FD_START, (uint32_t)CONFIG_EPROM_FD_END, (uint16_t)CONFIG_FDRAM_SIZE);
	printf("MR CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MR_CRC, (uint32_t)(CONFIG_EPROM_MR_CRC + 3), 4);
	printf("DM CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_DM_CRC, (uint32_t)(CONFIG_EPROM_DM_CRC + 3), 4);
	printf("FD CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_FD_CRC, (uint32_t)(CONFIG_EPROM_FD_CRC + 3), 4);	
  printf("MCU FW CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MCU_FW_CRC, (uint32_t)(CONFIG_EPROM_MCU_FW_CRC + 3), 4);
	printf("LCD FW CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_LCD_FW_CRC, (uint32_t)(CONFIG_EPROM_LCD_FW_CRC + 3), 4);
	printf("TREATMEN_CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIF_EPROM_TREATMENT_CRC, (uint32_t)(CONFIF_EPROM_TREATMENT_CRC + 3), 4);
  
  printf("CFG CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_CFG_CRC, (uint32_t)(CONFIG_EPROM_CFG_CRC + 3), 4);
	printf("LOG CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_LOG_CRC, (uint32_t)(CONFIG_EPROM_LOG_CRC + 3), 4);	
  
  printf("TREAMENT EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_TREATMENT_START, (uint32_t)CONFIG_EPROM_TREATMENT_END, (uint16_t)(CONFIG_EPROM_TREATMENT_END - CONFIG_EPROM_TREATMENT_START + 1));
  
  printf("CONFIG EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_CONFIG_START, (uint32_t)CONFIG_EPROM_CONFIG_END, (uint16_t)(CONFIG_EPROM_CONFIG_END - CONFIG_EPROM_CONFIG_START + 1));
	printf("LOGINFO EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_LOGINFO_START,(uint32_t)CONFIG_EPROM_LOGINFO_END, (uint16_t)(CONFIG_EPROM_LOGINFO_END - CONFIG_EPROM_LOGINFO_START + 1));
		
	printf("deviceConfig size:%d byte\n", sizeof(deviceConfig));
	printf("deviceLogInfo size:%d byte\n", sizeof(deviceLogInfo));
	
	tmp = CONFIG_EPROM_CONFIG_END - CONFIG_EPROM_CONFIG_START + 1;
	if(sizeof(deviceConfig) > tmp){
		printf("WARNING:struce deviceConfig size overflow!!!\n");
	}
	tmp = CONFIG_EPROM_LOGINFO_END - CONFIG_EPROM_LOGINFO_START + 1;
	if(sizeof(deviceLogInfo) > tmp){
		printf("WARNING:struce devideInfo size overflow!!!\n");
	}
}

void clearEprom(clarmEpromCmd_t cmd){//清除EPROM内容
	uint8_t var = 0;
	uint32_t i;	
	switch(cmd){
		case CLEAR_EPROM_ALL:{
			for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_NVRAM:{
			for(i = CONFIG_EPROM_MR_START; i <= CONFIG_EPROM_MR_END;i ++){
				epromWriteByte(i, &var);
			}
			for(i = CONFIG_EPROM_DM_START; i <= CONFIG_EPROM_DM_END;i ++){
				epromWriteByte(i, &var);
			}
			
			for(i = CONFIG_EPROM_MR_CRC; i <= (CONFIG_EPROM_MR_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			
			for(i = CONFIG_EPROM_DM_CRC; i <= (CONFIG_EPROM_DM_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_FDRAM:{
			for(i = CONFIG_EPROM_FD_START; i <= CONFIG_EPROM_FD_END;i ++){
				epromWriteByte(i, &var);
			}			
			for(i = CONFIG_EPROM_FD_CRC; i <= (CONFIG_EPROM_FD_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_MCU_FIRMWARE_CRC:{
			for(i = CONFIG_EPROM_MCU_FW_CRC;i <= (CONFIG_EPROM_MCU_FW_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_LCD_FIRMWARE_CRC:{
			for(i = CONFIG_EPROM_LCD_FW_CRC;i <= (CONFIG_EPROM_LCD_FW_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_DEVICE_CONFIG:{
			for(i = CONFIG_EPROM_CONFIG_START;i <= CONFIG_EPROM_CONFIG_END;i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
		case CLEAR_EPROM_LOG_INFO:{
			for(i = CONFIG_EPROM_LOGINFO_START;i <= CONFIG_EPROM_LOGINFO_END;i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
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







