#include "dcHmiNotifyText.h"
/*! 
*  \brief  �ı��ؼ�֪ͨ
*  \details  ���ı�ͨ�����̸���(�����GetControlValue)ʱ��ִ�д˺���
*  \details  �ı��ؼ����������ַ�����ʽ�·���MCU������ı��ؼ������Ǹ���ֵ��
*  \details  ����Ҫ�ڴ˺����н��·��ַ�������ת�ظ���ֵ��
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param str �ı��ؼ�����
*/
void NotifyText(uint16_t screen_id, uint16_t control_id, uint8_t *str){
   //TODO: ����û�
	uint16_t tmp;int32_t sValue;fp32_t fValue;
	switch(screen_id){
		case GDDC_PAGE_RENAME:{
			switch(control_id){
				case GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME:{
					tmp = NVRAM0[EM_SCHEME_NUM_TMP];
					if(strlen((const char*)str) <= CONFIG_SCHEME_NAME_SIZE){
						strcpy((char*)(FDRAM + (tmp * 64)), (const char*)str);
						if(tmp < 16){
							SetTextValue(GDDC_PAGE_SCHEME_0, (GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0 + tmp), str);
						}
						else{
							SetTextValue(GDDC_PAGE_SCHEME_1, (GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0 + tmp - 16), str);
						}
					}
					SSET(R_RENAME_TEXTDISPLAY_READ_DONE);
					break;
				}
				default:break;
			}
			break;
		}
		case GDDC_PAGE_DIAGNOSIS:{
			switch(control_id){
				//ͨ��0 ����У����
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
				//ͨ��1 ����У����
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
				//ͨ��2 ����У����
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P1:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[0] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P2:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P3:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P4:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[4] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P6:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[5] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P7:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[6] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P8:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[7] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P9:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[8] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_1P0:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr2[9] = (uint16_t)(fValue * 10.0F);
					break;
				}
				//ͨ��3 ����У����
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P1:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[0] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P2:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[1] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P3:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[2] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P4:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[3] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P5:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[4] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P6:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[5] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P7:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[6] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P8:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[7] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P9:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[8] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_1P0:{
					sscanf((const char*)str, "%f", &fValue);
					deviceConfig.calibrationPwr3[9] = (uint16_t)(fValue * 10.0F);
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_AIM_MAX:{
					sscanf((const char*)str, "%d", &sValue);
					deviceConfig.aimMaxCfg = (uint8_t)sValue;
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_RLED_BRG:{
					sscanf((const char*)str, "%d", &sValue);
					deviceConfig.redLedBrg = (uint8_t)sValue;
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_GLED_BRG:{
					sscanf((const char*)str, "%d", &sValue);
					deviceConfig.greenLedBrg = (uint8_t)sValue;
					break;
				}
				case GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_YLED_BRG:{
					sscanf((const char*)str, "%d", &sValue);
					deviceConfig.yellowLedBrg = (uint8_t)sValue;
					break;
				}
				default:break;
			}
			break;
		}
		default:break;
	}
}   






