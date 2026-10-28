#include "sPlc.h"
#include "sPlcEprom.h"
/*****************************************************************************/
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
#ifdef CONFIG_EPROM_BK_START
		case CLEAR_EPROM_BKRAM:{
			for(i = CONFIG_EPROM_BK_START; i <= CONFIG_EPROM_BK_END;i ++){
				epromWriteByte(i, &var);
			}			
			for(i = CONFIG_EPROM_BK_CRC; i <= (CONFIG_EPROM_BK_CRC + 3);i ++){
				epromWriteByte(i, &var);
			}
			break;
		}
#endif
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







