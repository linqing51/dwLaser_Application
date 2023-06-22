#include "dcHmiNotifyProgress.h"
/*****************************************************************************/
void NotifyProgress(uint16_t screen_id, uint16_t control_id, uint32_t value){
	float fpwr;
	switch(screen_id){
		case GDDC_PAGE_STANDBY:{
			switch(control_id){
				case GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL:{
					if(value > 100){
						value = 100;
					}
					if(value <= 0){
						value = 1;
					}
					if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_1470){//1470
						fpwr = (float)value / 100 * CONFIG_MAX_LASER_POWER_1470;
						if(fpwr < CONFIG_MIN_LASER_POWER_1470){
							fpwr = CONFIG_MIN_LASER_POWER_1470;
						}
						NVRAM0[EM_LASER_POWER_1470] = (int16_t)fpwr;
					}
					if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_980){//980
						fpwr = (float)value / 100 * CONFIG_MAX_LASER_POWER_980;
						if(fpwr < CONFIG_MIN_LASER_POWER_980){
							fpwr = CONFIG_MIN_LASER_POWER_980;
						}
						NVRAM0[EM_LASER_POWER_980] = (int16_t)fpwr;
					}
					if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_635){//635
						fpwr = (float)value / 100 * CONFIG_MAX_LASER_POWER_635;
						if(fpwr < CONFIG_MIN_LASER_POWER_635){
							fpwr = CONFIG_MIN_LASER_POWER_635;
						}
						NVRAM0[EM_LASER_POWER_635] = (int16_t)fpwr;
					}
					NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_1470] + NVRAM0[EM_LASER_POWER_980] + NVRAM0[EM_LASER_POWER_635];
					updateStandbyDisplay();
					break;
				}
				case GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_1470:{
					if(value > 100){
						value = 100;
					}
					if(value <= 0){
						value = 1;
					}
					fpwr = (float)value / 100 * CONFIG_MAX_LASER_POWER_1470 * 10.0F;
					NVRAM0[EM_LASER_AVERAGE_POWER_1470] = (int16_t)fpwr;
					NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_1470] + NVRAM0[EM_LASER_POWER_980] + NVRAM0[EM_LASER_POWER_635];
					updateStandbyDisplay();					
					break;
				}
				case GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_980:{
					if(value > 100){
						value = 100;
					}
					if(value <= 0){
						value = 1;
					}
					fpwr = (float)value / 100 * CONFIG_MAX_LASER_POWER_980 * 10.0F;
					NVRAM0[EM_LASER_AVERAGE_POWER_980] = (int16_t)fpwr;
					NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_1470] + NVRAM0[EM_LASER_POWER_980] + NVRAM0[EM_LASER_POWER_635];
					updateStandbyDisplay();
					break;
				}
				case GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_635:{
					if(value > 100){
						value = 100;
					}
					fpwr = (float)value / 100 * CONFIG_MAX_LASER_POWER_635 * 10.0F;
					NVRAM0[EM_LASER_AVERAGE_POWER_635] = (int16_t)fpwr;
					NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_1470] + NVRAM0[EM_LASER_POWER_980] + NVRAM0[EM_LASER_POWER_635];
					updateStandbyDisplay();
					break;
				}
				case GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_650:{
					if(value > CONFIG_MAX_LASER_POWER_650){
						value = CONFIG_MAX_LASER_POWER_650;
					}
					NVRAM0[DM_AIM_BRG] = (int16_t)value;
					updateStandbyDisplay();
					break;
				}				
				default:break;
			}
			break;
		}
		case GDDC_PAGE_OPTION:{
			switch(control_id){
				case GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME:{
					if(value > CONFIG_BEEM_MAX_VOLUME){
						value = CONFIG_BEEM_MAX_VOLUME;
					}
					NVRAM0[DM_BEEM_VOLUME] = (int16_t)value;
					NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
					SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
					break;
				}
				case GDDC_PAGE_OPTION_PROGRESS_LCD_BRG:{
					if(value < CONFIG_LCD_MIN_DC){
						value = CONFIG_LCD_MIN_DC;
					}
					if(value > CONFIG_LCD_MAX_DC){
						value = CONFIG_LCD_MAX_DC;
					}
					NVRAM0[DM_LCD_BRG] = (int16_t)value;
					SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG , NVRAM0[DM_LCD_BRG], 1, 0);
					SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
					break;
				}					
				default:break;
			}
			break;
		}
	}
} 




