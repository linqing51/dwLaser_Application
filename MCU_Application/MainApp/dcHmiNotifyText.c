#include "dcHmiNotifyText.h"
/*! 
*  \brief  文本控件通知
*  \details  当文本通过键盘更新(或调用GetControlValue)时，执行此函数
*  \details  文本控件的内容以字符串形式下发到MCU，如果文本控件内容是浮点值，
*  \details  则需要在此函数中将下发字符串重新转回浮点值。
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param str 文本控件内容
*/
void NotifyText(uint16_t screen_id, uint16_t control_id, uint8_t *str){
   //TODO: 添加用户
	uint16_t tmp;int32_t sValue;float fValue;
	switch(screen_id){
		case GDDC_PAGE_RENAME:{
			switch(control_id){
				case GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME:{
					tmp = NVRAM0[EM_SCHEME_NUM_TMP];
					if(strlen((const char*)str) <= CONFIG_SCHEME_NAME_SIZE){
						strcpy((char*)&FDRAM1[tmp * 64 + FD_LASER_SCHEME_NAME], (char*)str);
						SetTextValue(GDDC_PAGE_SCHEME_DETAIL, (GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0 + tmp), str);
						SSET(R_RENAME_TEXTDISPLAY_READ_DONE);
					}
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_DIAGNOSIS:{
			switch(control_id){
				//通道0 功率校正表
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P1:{	                                                          
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[0] = (uint16_t)(fValue * 10.0F);            					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P2:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P3:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P4:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[4] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P6:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[5] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P7:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[6] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P8:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[7] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P9:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[8] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_1P0:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[9] = (uint16_t)(fValue * 10.0F);
					break;
				}
				//通道1 功率校正表
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P1:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[0] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P2:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P3:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P4:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[4] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P6:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[5] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P7:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[6] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P8:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[7] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P9:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[8] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_1P0:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[9] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_SN:{
					strncpy(deviceConfig.serialNumber, (const char*)str, sizeof(deviceConfig.serialNumber));
					break;
				}
				case GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_YEAR:{				
					sscanf((const char*)str, "%d", &sValue);
					if(sValue < 2022){
						sValue = 2022;
					}
					if(sValue > 2099){
						sValue = 2099;
					}
					deviceConfig.mfg_year = sValue;
					break;
				}
				case GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_MONTH:{
					sscanf((const char*)str, "%d", &sValue);
					if(sValue > 12){
						sValue = 12;
					}
					if(sValue < 1){
						sValue = 1;
					}
					deviceConfig.mfg_month = sValue;
					break;
				}
				case GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_DAY:{
				sscanf((const char*)str, "%d", &sValue);
					if(sValue > 31){
						sValue = 31;
					}
					if(sValue < 1){
						sValue = 1;
					}
					deviceConfig.mfg_day = sValue;
					break;	
				}
				case GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_RED_LED_DC:{
					sscanf((const char*)str, "%d", &sValue);
					if(sValue > 100){
						sValue = 100;
					}
					if(sValue < 1){
						sValue = 1;
					}
					deviceConfig.redLedDc = sValue;
					break;
				}
				case GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_GREEN_LED_DC:{
					sscanf((const char*)str, "%d", &sValue);
					if(sValue > 100){
						sValue = 100;
					}
					if(sValue < 1){
						sValue = 1;
					}
					deviceConfig.greenLedDc = sValue;
					break;
				}
				case GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_BLUE_LED_DC:{
					sscanf((const char*)str, "%d", &sValue);
					if(sValue > 100){
						sValue = 100;
					}
					if(sValue < 1){
						sValue = 1;
					}
					deviceConfig.blueLedDc = sValue;	
					break;
				}
				case GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_SET_AIM_GAIN:{
					sscanf((const char*)str, "%d", &sValue);
					if(sValue > 100){
						sValue = 100;
					}
					if(sValue < 1){
						sValue = 1;
					}
					deviceConfig.aimGain = sValue;	
					break;
				}
				default:break;
			}
			break;
		}
		default:break;
	}
}   






