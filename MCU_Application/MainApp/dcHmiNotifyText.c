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
						updateSchemeDetail(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
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
					deviceConfig.redAimGain = sValue;	
					break;
				}
				case GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIBER_DETECT:{
					sscanf((const char*)str, "%d", &sValue);
					if(sValue > 4095){
						sValue = 4095;
					}
					if(sValue < 1){
						sValue = 1;
					}
					deviceConfig.fiberDetect = sValue;
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_DIAGNOSIS_CALI:{
			switch(control_id){
				//CH0 校准数据输入
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[0] = (uint16_t)(fValue * 10.0F); 		
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P10:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P15:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P20:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P25:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[4] = (uint16_t)(fValue * 10.0F);	
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P30:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[5] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P35:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[6] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P40:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[7] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P45:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[8] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P50:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[9] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P55:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[10] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P60:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[11] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P65:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[12] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P70:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[13] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P75:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[14] = (uint16_t)(fValue * 10.0F);				
					break;
				}
				
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P80:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[15] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P85:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[16] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P90:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[17] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P95:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[18] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P100:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr0[19] = (uint16_t)(fValue * 10.0F);
					break;
				}
				//CH1 校准数据输入
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[0] = (uint16_t)(fValue * 10.0F); 		
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P10:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P15:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P20:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P25:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[4] = (uint16_t)(fValue * 10.0F);	
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P30:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[5] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P35:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[6] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P40:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[7] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P45:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[8] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P50:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[9] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P55:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[10] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P60:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[11] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P65:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[12] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P70:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[13] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P75:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[14] = (uint16_t)(fValue * 10.0F);				
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P80:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[15] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P85:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[16] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P90:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[17] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P95:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[18] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P100:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr1[19] = (uint16_t)(fValue * 10.0F);
					break;
				}
				//CH2 校准数据
					case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[0] = (uint16_t)(fValue * 10.0F); 		
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P10:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P15:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P20:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P25:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[4] = (uint16_t)(fValue * 10.0F);	
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P30:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[5] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P35:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[6] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P40:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[7] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P45:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[8] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P50:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[9] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P55:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[10] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P60:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[11] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P65:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[12] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P70:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[13] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P75:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[14] = (uint16_t)(fValue * 10.0F);				
					break;
				}				
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P80:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[15] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P85:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[16] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P90:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[17] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P95:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[18] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P100:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[19] = (uint16_t)(fValue * 10.0F);
					break;
				}
				//CH3 校准数据
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[0] = (uint16_t)(fValue * 10.0F); 		
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P10:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P15:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P20:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P25:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[4] = (uint16_t)(fValue * 10.0F);	
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P30:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[5] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P35:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[6] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P40:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[7] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P45:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[8] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P50:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[9] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P55:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[10] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P60:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[11] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P65:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[12] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P70:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[13] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P75:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[14] = (uint16_t)(fValue * 10.0F);				
					break;
				}				
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P80:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[15] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P85:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[16] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P90:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[17] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P95:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[18] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P100:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[19] = (uint16_t)(fValue * 10.0F);
					break;
				}
				//CH4 校准数据
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[0] = (uint16_t)(fValue * 10.0F); 		
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P10:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P15:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P20:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P25:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[4] = (uint16_t)(fValue * 10.0F);	
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P30:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[5] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P35:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[6] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P40:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[7] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P45:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[8] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P50:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[9] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P55:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[10] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P60:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[11] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P65:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[12] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P70:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[13] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P75:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[14] = (uint16_t)(fValue * 10.0F);				
					break;
				}				
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P80:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[15] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P85:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[16] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P90:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[17] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P95:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[18] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P100:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr4[19] = (uint16_t)(fValue * 10.0F);
					break;
				}
				//CH5 校准数据
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[0] = (uint16_t)(fValue * 10.0F); 		
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P10:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P15:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P20:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P25:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[4] = (uint16_t)(fValue * 10.0F);	
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P30:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[5] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P35:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[6] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P40:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[7] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P45:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[8] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P50:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[9] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P55:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[10] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P60:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[11] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P65:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[12] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P70:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[13] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P75:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[14] = (uint16_t)(fValue * 10.0F);				
					break;
				}				
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P80:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[15] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P85:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[16] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P90:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[17] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P95:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[18] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P100:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr5[19] = (uint16_t)(fValue * 10.0F);
					break;
				}
				//CH6 校准数据
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[0] = (uint16_t)(fValue * 10.0F); 		
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P10:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P15:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P20:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P25:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[4] = (uint16_t)(fValue * 10.0F);	
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P30:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[5] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P35:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[6] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P40:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[7] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P45:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[8] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P50:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[9] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P55:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[10] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P60:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[11] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P65:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[12] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P70:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[13] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P75:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[14] = (uint16_t)(fValue * 10.0F);				
					break;
				}				
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P80:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[15] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P85:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[16] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P90:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[17] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P95:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[18] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P100:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr6[19] = (uint16_t)(fValue * 10.0F);
					break;
				}
				//CH7 校准数据
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[0] = (uint16_t)(fValue * 10.0F); 		
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P10:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P15:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P20:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P25:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[4] = (uint16_t)(fValue * 10.0F);	
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P30:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[5] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P35:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[6] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P40:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[7] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P45:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[8] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P50:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[9] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P55:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[10] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P60:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[11] = (uint16_t)(fValue * 10.0F);					
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P65:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[12] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P70:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[13] = (uint16_t)(fValue * 10.0F);					
				break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P75:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[14] = (uint16_t)(fValue * 10.0F);				
					break;
				}				
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P80:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[15] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P85:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[16] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P90:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[17] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P95:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[18] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P100:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr7[19] = (uint16_t)(fValue * 10.0F);
					break;
				}
				
				default:break;
			}
			break;
		}
		default:break;
	}
}   






