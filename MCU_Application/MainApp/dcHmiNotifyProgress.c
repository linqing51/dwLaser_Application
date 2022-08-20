#include "dcHmiNotifyProgress.h"
/*****************************************************************************/
void NotifyProgress(uint16_t screen_id, uint16_t control_id, uint32_t value){ 
	int16_t tmp16;
	switch(screen_id){
		case GDDC_PAGE_STANDBY_CW:{
			switch(control_id){
				case GDDC_PAGE_STANDBY_PROGRESS_SET_POWER:{
					if(value > 100){
						value = 100;
					}
					NVRAM0[EM_LASER_POWER_CH0] = (int16_t)(value * CONFIG_MAX_LASERPOWER_CH0 / 100);
					NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
					updatePowerDisplay();					
					break;
				}
				case GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG:{
					tmp16 = (int16_t)value;
					if(tmp16 < CONFIG_AIM_MIN_DC){
						tmp16 = CONFIG_AIM_MIN_DC;
					}
					if(tmp16 > CONFIG_AIM_MAX_DC){
						tmp16 = CONFIG_AIM_MAX_DC;
					}
					NVRAM0[DM_AIM_BRG] = (int16_t)tmp16;	
					SetTextInt32(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
					break;
				}
				default:break;
			}
			break;
		}
	
		case GDDC_PAGE_STANDBY_MP:{
			switch(control_id){
				case GDDC_PAGE_STANDBY_PROGRESS_SET_POWER:{
					if(value > 100){
						value = 100;
					}
					NVRAM0[EM_LASER_POWER_CH0] = (int16_t)(value * CONFIG_MAX_LASERPOWER_CH0 / 100);
					NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
					updatePowerDisplay();
					break;
				}
				case GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG:{
					if(value < CONFIG_AIM_MIN_DC){
						value = CONFIG_AIM_MIN_DC;
					}
					if(value > CONFIG_AIM_MAX_DC){
						value = CONFIG_AIM_MAX_DC;
					}
					NVRAM0[DM_AIM_BRG] = (int16_t)value;	
					SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
					break;
				}				
				default:break;
			}
			break;
		}
		case GDDC_PAGE_OPTION:{
			switch(control_id){
				case GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME:{
					if(value < CONFIG_BEEM_MIN_VOLUME){
						value = CONFIG_BEEM_MIN_VOLUME;
					}
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




