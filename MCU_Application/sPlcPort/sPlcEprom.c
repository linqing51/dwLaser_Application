#include "sPlc.h"
#include "sPlcEprom.h"
/*****************************************************************************/
void listEpromTable(void){//输出EPROM分布表
	int32_t tmp;
	uint8_t eprom_id[4];
	epromReadDeviceId(eprom_id);
	printf("************************EPROM MAP****************************\n\n");
	printf("EPROM ID:%02X%02X%02X%02X\n", eprom_id[0], eprom_id[1], eprom_id[2], eprom_id[3]);
	printf("MR EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MR_START, (uint32_t)CONFIG_EPROM_MR_END, (uint16_t)CONFIG_MRRAM_SIZE);
	printf("DM EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_DM_START, (uint32_t)CONFIG_EPROM_DM_END, (uint16_t)CONFIG_DMRAM_SIZE);
	printf("FD EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_FD_START, (uint32_t)CONFIG_EPROM_FD_END, (uint16_t)CONFIG_FDRAM_SIZE);
	
	printf("MEDICAL CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MEDICAL_CRC, (uint32_t)(CONFIG_EPROM_MEDICAL_CRC + 3), 4);
	printf("MR CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MR_CRC, (uint32_t)(CONFIG_EPROM_MR_CRC + 3), 4);
	printf("DM CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_DM_CRC, (uint32_t)(CONFIG_EPROM_DM_CRC + 3), 4);
	printf("FD CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_FD_CRC, (uint32_t)(CONFIG_EPROM_FD_CRC + 3), 4);	
	printf("MCU FW CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_MCU_FW_CRC, (uint32_t)(CONFIG_EPROM_MCU_FW_CRC + 3), 4);
	printf("LCD FW CRC EPROM:0x%04X---0x%04X(size:%d byte)\n", (uint32_t)CONFIG_EPROM_LCD_FW_CRC, (uint32_t)(CONFIG_EPROM_LCD_FW_CRC + 3), 4);
	
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







