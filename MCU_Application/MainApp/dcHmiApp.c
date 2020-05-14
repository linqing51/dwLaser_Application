#include "dcHmiApp.h"
/*****************************************************************************/
code char *LANG_WARN_MSG_NO_ERROR = "";
code char *LANG_WARN_MSG_INTERLOCK_UNPLUG = "Door interlock disconnected";//��ȫ����û��
code char *LANG_WARN_MSG_FOOTSWITCH_UNPLUG = "Footswitch not connected";//��̤û��
code char *LANG_WARN_MSG_ESTOP_PRESS = "ESTOP Press";
code char *LANG_WARN_MSG_FIBER_UNPLUG = "No fiber connected ";//����û�����RFID��ʶ��
code char *LANG_WARN_MSG_OUT_ENERGY = "Energy out of tolerance";//����ƫ�20%��Ԥ�����ܣ������Ժ�ʵ��
code char *LANG_WARN_MSG_DIODE_HTEMP = "Laser overheating";//�¶ȹ���
code char *LANG_WARN_MSG_DIODE_LTEMP = "Laser NTC Open";//�¶ȹ���
code char *LANG_WARN_MSG_DIODE0_OVERCURRENT = "Laser current exceeds set value";//���������޶�ֵ������������
code char *LANG_WARN_MSG_DIODE1_OVERCURRENT = "Laser current exceeds set value";//���������޶�ֵ������������
code char *LANG_WARN_MSG_NTC_ERROR = "Thermistor Error";//�����������
code char *LANG_WARN_MSG_ENVI_HTEMP = "Envi High Temperature";//�����¶ȹ���
code char *LANG_WARN_MSG_FOOT_DEPRESSED = "Foot/finger switch is depressed";//��̤����ȥû������
code char *LANG_WARN_MSG_LASER_EMIT = "Laser is firing";//�������ڷ���
code char *LANG_WARN_MSG_WAIT_TRIGGER = "Wait Laser Trigger";//�ȴ����ⴥ��
code char *LANG_WARN_MSG_FIBER_MISSMATE = "Fiber not mate";
/*****************************************************************************/
code char *LANG_INFO_MSG_TYPE = "TYPE: Dual Git Engineering Sample";
code char *LANG_INFO_MSG_SN = "SN: 0000-00-00";
code char *LANG_INFO_MSG_WAVELENGTH = "WAVE LENGTH: 980nM";
code char *LANG_INFO_MSG_LASER_POWER = "LASER_POWER: 30W";
code char *LANG_INFO_MSG_VERSION = "VERSION: 0.99";
code char *LANG_INFO_MSG_MANUFACTURE_DATE = "MANUFACTURE DATE:1970-01-01";
/*****************************************************************************/
uint8_t hmiCmdBuffer[CMD_MAX_SIZE];//ָ���
uint16_t data hmiCmdSize;//�ѻ����ָ����
static data uint8_t MsgId;//��ǰ��ʾ����ϢID
void UpdateUI(void);
static void updateReleaseTimeEnergy(void);
/*****************************************************************************/
#if CONFIG_USING_DCHMI_APP == 1
void optionKeyEnable(uint8_t enable){//ѡ����水������
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_TONE, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_AIM_BRG_ADD, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_AIM_BRG_DEC, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_ADD, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_DEC, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_LCD_BRG_ADD, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_LCD_BRG_DEC, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_ENTER_OK, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_ENTER_INFORMATION, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_ENTER_CORRECTION, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_PROGRESS_AIM_BRG, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_RESTORE, enable);
	BatchEnd();
}
void standbyDebugInfoVisiable(int8_t enable){//Standby������Ϣ�ɼ�
	SetControlVisiable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
}
void updateStandbyDebugInfo(void){//����Standby������Ϣ
	char dispBuf[128];
	sprintf(dispBuf, "Diode Temper:%d, Chip Temper:%d", NVRAM0[EM_DIODE_TEMP0], NVRAM0[EM_ENVI_TEMP]);
	SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, dispBuf);
	SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, dispBuf);
	SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, dispBuf);
	SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, dispBuf);
	SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, dispBuf);
	SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, dispBuf);
}
void updateDiognosisInfo(void){//���������Ϣ
	char dispBuf[256];
	
	sprintf(dispBuf, "ADC0:0x%4X,ADC1:0x%4X,ADC2:0x%4X,ADC3:0x%4X", NVRAM0[SPREG_ADC_0], NVRAM0[SPREG_ADC_1], NVRAM0[SPREG_ADC_2], NVRAM0[SPREG_ADC_3]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO0, dispBuf);
	
	sprintf(dispBuf, "ADC4:0x%4X,ADC5:0x%4X,ADC6:0x%4X,ADC7:0x%4X", NVRAM0[SPREG_ADC_4], NVRAM0[SPREG_ADC_5], NVRAM0[SPREG_ADC_6], NVRAM0[SPREG_ADC_7]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO1, dispBuf);
	
	sprintf(dispBuf, "DAC0:0x%4X,DAC1:0x%4X,DAC2:0x%4X,DAC3:0x%4X", NVRAM0[SPREG_DAC_0], NVRAM0[SPREG_DAC_1], NVRAM0[SPREG_DAC_2], NVRAM0[SPREG_DAC_3]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO2, dispBuf);
	
	sprintf(dispBuf, "NFC VER:0x%4X, PLATFORM VER:0x%4X", NVRAM0[SPREG_DK25L_VER], NVRAM0[SPREG_IDENTITY]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO3, dispBuf);
	
	sprintf(dispBuf, "FS NC:%d, FS NO:%d, ES:%d, IL:%d, FP:%d", LD(X_FOOTSWITCH_NC),  LD(X_FOOTSWITCH_NO), LD(X_ESTOP), LD(X_INTERLOCK), NVRAM0[X_FIBER_PROBE]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO4, dispBuf);
	
	sprintf(dispBuf, "FAN:%d, TEC:%d", LD(Y_FAN0),  LD(Y_TEC0));
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO5, dispBuf);
}
void updateEnergyDensity(void){//���������ܶ���ʾ
	char dispBuf[32];
	fp32_t ftemp;
	ftemp = (fp32_t)NVRAM0[EM_TOTAL_POWER];
	switch(NVRAM0[EM_LASER_DERMA_SPOT_SIZE]){	
		case DERMA_SPOT_SIZE_0MM5:{
			sprintf(dispBuf, "%dj/cm", (int16_t)(ftemp / 0.019625F));
			break;
		}
		case DERMA_SPOT_SIZE_1MM0:{
			sprintf(dispBuf, "%dj/cm", (int16_t)(ftemp / 0.0785F));
			break;
		}
		case DERMA_SPOT_SIZE_2MM0:{
			sprintf(dispBuf, "%dj/cm", (int16_t)(ftemp / 0.314926F));
			break;
		}
		case DERMA_SPOT_SIZE_3MM0:{
			sprintf(dispBuf, "%dj/cm", (int16_t)(ftemp / 0.706853));
			break;
		}
		default:{
			sprintf(dispBuf, "HHHHj/cm");
			break;
		}
	}
	SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_TEXTDISPLAY_ENERGY_DENSITY, dispBuf);
}
void updateScheme_0_Display(void){//����ѡ����淽������
	char dispBuf[32];
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_0])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_0]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_1])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_1]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_2])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_2]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_3])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_3]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_4])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_4]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_5])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_5]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_6])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_6]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_7])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_7]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_8])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_8]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_9])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_9]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_10])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_10]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_11])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_11]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_12])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_12]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_13])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_13]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_14])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_14]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_15])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_15]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, dispBuf);	
	}
	unselectScheme_0_All();
	SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "");
	SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, "");
	SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, "");
}
void updateScheme_1_Display(void){//����ѡ����淽������
	char dispBuf[26];
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_16])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_16]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_17])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_17]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_18])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_18]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_19])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_19]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_20])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_20]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_21])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_21]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_22])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_22]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_23])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_23]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_24])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_24]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_25])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_25]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_26])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_26]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_27])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_27]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_28])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_28]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_29])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_29]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_30])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_30]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_31])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_31]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, dispBuf);	
	}
	unselectScheme_1_All();
	SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "");
	SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, "");
	SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, "");
}
void returnStandbyDisplay(void){//����STANDBY����
	switch(NVRAM0[EM_LASER_PULSE_MODE]){	
		case LASER_MODE_CW:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;
			break;
		}
		case LASER_MODE_SP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_SP;
			break;
		}
		case LASER_MODE_MP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;
			break;
		}
		case LASER_MODE_GP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_GP;
			break;
		}
		case LASER_MODE_SIGNAL:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_SIGNAL;
			break;
		}
		case LASER_MODE_DERMA:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_DERMA;
			break;
		}
		default:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;
			break;
		}
	}
	NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;	
	SetScreen(NVRAM0[EM_DC_PAGE]);
}
void updateReleaseTimeEnergy(void){//ˢ�·���ʱ������
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			SetTextInt32(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime, 1, 0);
			SetTextInt32(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy, 1, 0);
			break;
		}
		case LASER_MODE_SP:{
			SetTextInt32(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime, 1, 0);
			SetTextInt32(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy, 1, 0);
			break;
		}
		case LASER_MODE_MP:{			
			SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime, 1, 0);
			SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy, 1, 0);
			break;
		}
		case LASER_MODE_GP:{			
			SetTextInt32(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime, 1, 0);
			SetTextInt32(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy, 1, 0);
			break;
		}
		case LASER_MODE_SIGNAL:{
			SetTextInt32(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime, 1, 0);
			SetTextInt32(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy, 1, 0);
			break;
		}
		case LASER_MODE_DERMA:{
			SetTextInt32(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime, 1, 0);
			SetTextInt32(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy, 1, 0);
			break;
		}
		default:break;
	}
}
void updateWarnMsgDisplay(uint8_t id){//���¾�����ʾ��
	char *pstr;
	if(MsgId != id){
		switch(id){
			case MSG_NO_ERROR:{
				pstr = LANG_WARN_MSG_NO_ERROR;
				break;
			}
			case MSG_INTERLOCK_UNPLUG:{
				pstr = LANG_WARN_MSG_INTERLOCK_UNPLUG;
				break;
			}
			case MSG_FOOTSWITCH_UNPLUG:{
				pstr = LANG_WARN_MSG_FOOTSWITCH_UNPLUG;
				break;
			}
			case MSG_ESTOP_PRESS:{
				pstr = LANG_WARN_MSG_ESTOP_PRESS;
				break;
			}
			case MSG_FIBER_UNPLUG:{
				pstr = LANG_WARN_MSG_FIBER_UNPLUG;
				break;
			}
			case MSG_OUT_ENERGY:{
				pstr = LANG_WARN_MSG_OUT_ENERGY;
				break;
			}
			case MSG_DIODE_HTEMP:{
				pstr = LANG_WARN_MSG_DIODE_HTEMP;
				break;
			}
			case MSG_DIODE_LTEMP:{
				pstr = LANG_WARN_MSG_DIODE_LTEMP;
				break;
			}
			case MSG_DIODE0_OVERCURRENT:{
				pstr = LANG_WARN_MSG_DIODE0_OVERCURRENT;
				break;
			}
			case MSG_DIODE1_OVERCURRENT:{
				pstr = LANG_WARN_MSG_DIODE1_OVERCURRENT;
				break;
			}
			case MSG_NTC_ERROR:{
				pstr = LANG_WARN_MSG_NTC_ERROR;
				break;
			}
			case MSG_ENVI_HTEMP:{
				pstr = LANG_WARN_MSG_ENVI_HTEMP;
				break;
			}
			case MSG_FOOT_DEPRESSED:{
				pstr = LANG_WARN_MSG_FOOT_DEPRESSED;
				break;
			}
			case MSG_LASER_EMIT:{
				pstr = LANG_WARN_MSG_LASER_EMIT;
				break;
			}
			case MSG_WAIT_TRIGGER:{
				pstr = LANG_WARN_MSG_WAIT_TRIGGER;
				break;
			}
			case MSG_FIBER_MISSMATE:{
				pstr = LANG_WARN_MSG_FIBER_MISSMATE;
				break;
			}
			default:{
				pstr = LANG_WARN_MSG_NO_ERROR;
				break;
			}
		}
		SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, pstr);
		SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, pstr);
		SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, pstr);
		SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, pstr);
		SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, pstr);
		SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, pstr);
		MsgId = id;
	}
}
void updateSchemeInfo(int16_t cn){//����SCHEME ��ϸ����
	char dispBuf1[64], dispBuf2[64];
	int16_t mode;
	int16_t	power0;
	int16_t power1;
	int16_t posWidth;
	int16_t negWidth;
	int16_t times;
	int16_t	groupOff;
	int16_t energyInterval;
	if(cn < 0)
		cn = 0;
	if(cn > CONFIG_HMI_SCHEME_NUM)
		cn = CONFIG_HMI_SCHEME_NUM;
	mode = FDRAM[cn * 30 + FD_LASER_PULSE_MODE]; 
	power0 = FDRAM[cn * 30 + FD_LASER_POWER_CH0];
	power1 = FDRAM[cn * 30 + FD_LASER_POWER_CH1];
	
	memset(dispBuf1, 0x0, 32);	
	memset(dispBuf2, 0x0, 32);
	switch(mode){
		case LASER_MODE_CW:{
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:CW");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:CW");
			}
			sprintf(dispBuf2, "");
			break;
		}
		case LASER_MODE_SP:{
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:Single");			
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:Single");
			}
			posWidth = FDRAM[cn * 30 + FD_LASER_SP_POSWIDTH];
			sprintf(dispBuf2, "OnTime:%dms", posWidth);
			break;
		}
		case LASER_MODE_MP:{
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:Pulsed");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:Pulsed");
			}
			posWidth = FDRAM[cn * 30 + FD_LASER_MP_POSWIDTH];
			negWidth = FDRAM[cn * 30 + FD_LASER_MP_NEGWIDTH];
			sprintf(dispBuf2, "OnTime:%dms,OffTime:%dms", posWidth, negWidth);
			break;
		}
		case LASER_MODE_GP:{
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:Group");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:Group");
			}
			posWidth = FDRAM[cn * 30 + FD_LASER_GP_POSWIDTH];
			negWidth = FDRAM[cn * 30 + FD_LASER_GP_NEGWIDTH];
			times = FDRAM[cn * 30 + FD_LASER_GP_TIMES];
			groupOff = FDRAM[cn * 30 + FD_LASER_GP_GROUP_OFF];
			sprintf(dispBuf2, "OnTime:%dms,OffTime:%dmS,Times:%d,GroupOff:%dms", posWidth, negWidth, times, groupOff);
			break;
		}
		case LASER_MODE_DERMA:{
			posWidth = FDRAM[cn * 30 + FD_LASER_DERMA_POSWIDTH];
			negWidth = FDRAM[cn * 30 + FD_LASER_DERMA_NEGWIDTH];
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:DERAM");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:DERAM");
			}
			sprintf(dispBuf2, "OnTime:%dms,OffTime:%dmS,Times:%d,Group Off:%dms", posWidth, negWidth);
			break;
		}
		case LASER_MODE_SIGNAL:{
			energyInterval = FDRAM[cn * 30 + FD_LASER_SIGNAL_ENERGY_INTERVAL];
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:SIGNAL");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, "Mode:SIGNAL");
			}
			sprintf(dispBuf2, "Energy Interval:%dJ", energyInterval);
			break;
		}
		default:break;
	}
#if CONFIG_USING_SINGLE_WAVE == 1
	sprintf(dispBuf1, "980nM Power:%4.1fW", ((fp32_t)power0 / 10.0F));
#endif
#if CONFIG_USING_DUAL_WAVE == 1
	sprintf(dispBuf1, "1470nM Power:%4.1fW;980nM Power:%4.1fW", ((fp32_t)power0 / 10.0F), ((fp32_t)power1 / 10.0F));
#endif
	if(cn < 16){
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, dispBuf1);
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, dispBuf2);
	}
	else{
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, dispBuf1);
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, dispBuf2);
	}
}
void unselectSchemeNum(int16_t sel){//��ѡ������
	if(sel < 16){
		SetButtonValue(GDDC_PAGE_SCHEME_0, (GDDC_PAGE_SCHEME_KEY_SELECT_0 + sel), 0x0);
	}
	else{
		sel -= 16;
		SetButtonValue(GDDC_PAGE_SCHEME_1, (GDDC_PAGE_SCHEME_KEY_SELECT_0 + sel), 0x0);
	}	
}
void seletcSchemeNum(int16_t sel){//ѡ�з�����
	NVRAM0[EM_SCHEME_NUM_TMP] = sel;
	if(sel < 16){
		SetButtonValue(GDDC_PAGE_SCHEME_0, (GDDC_PAGE_SCHEME_KEY_SELECT_0 + sel), 0x1);
	}
	else{
		sel -= 16;
		SetButtonValue(GDDC_PAGE_SCHEME_1, (GDDC_PAGE_SCHEME_KEY_SELECT_0 + sel), 0x1);
	}
	updateSchemeInfo(NVRAM0[EM_SCHEME_NUM_TMP]);
}
void unselectScheme_0_All(void){//��ѡ��һҳȫ��������
	BatchBegin(GDDC_PAGE_SCHEME_0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_0, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_1, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_2, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_3, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_4, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_5, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_6, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_7, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_8, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_9, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_10, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_11, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_12, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_13, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_14, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_15, 0x0);
	BatchEnd();
}
void unselectScheme_1_All(void){//��ѡ�ڶ�ҳȫ��������
	BatchBegin(GDDC_PAGE_SCHEME_1);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_0, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_1, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_2, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_3, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_4, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_5, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_6, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_7, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_8, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_9, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_10, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_11, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_12, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_13, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_14, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_KEY_SELECT_15, 0x0);
	BatchEnd();
}
void standbyTouchEnable(int8_t enable){//ʹ��STANDBY���津��
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			BatchBegin(GDDC_PAGE_STANDBY_CW);
			
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_GP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH0, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH1, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_RESET, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH0, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH1, enable);
#endif				
			BatchEnd();
			break;
		}
		case LASER_MODE_SP:{
			BatchBegin(GDDC_PAGE_STANDBY_SP);
			
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_GP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH0, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH1, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_RESET, enable);
			
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH0, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH1, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_SP_KEY_POSWIDTH_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_SP_KEY_POSWIDTH_DEC, enable);
			
			BatchEnd();
			break;
		}
		case LASER_MODE_MP:{
			BatchBegin(GDDC_PAGE_STANDBY_MP);
			
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_GP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, enable);		
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);
#if CONFIG_USING_DUAL_WAVE == 1				
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH0, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH1, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_RESET, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH0, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH1, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_MP_KEY_POSWIDTH_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_MP_KEY_POSWIDTH_DEC, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_MP_KEY_NEGWIDTH_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_MP_KEY_NEGWIDTH_DEC, enable);
			
			BatchEnd();
			break;
		}
		case LASER_MODE_GP:{
			BatchBegin(GDDC_PAGE_STANDBY_GP);
			
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_GP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH0, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH1, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_RESET, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH0, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH1, enable);
#endif				
			BatchSetEnable(GDDC_PAGE_STANDBY_GP_KEY_POSWIDTH_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_GP_KEY_POSWIDTH_DEC, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_GP_KEY_NEGWIDTH_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_GP_KEY_NEGWIDTH_DEC, enable);

			BatchSetEnable(GDDC_PAGE_STANDBY_GP_KEY_TIMES_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_GP_KEY_TIMES_DEC, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_GP_KEY_GROUP_OFF_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_GP_KEY_GROUP_OFF_DEC, enable);
			
			BatchEnd();
			break;
		}
		case LASER_MODE_DERMA:{
			BatchBegin(GDDC_PAGE_STANDBY_DERMA);
			
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_GP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);
#if CONFIG_USING_DUAL_WAVE == 1				
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH0, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH1, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_RESET, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH0, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH1, enable);
#endif				
			BatchSetEnable(GDDC_PAGE_STANDBY_DERMA_KEY_POSWIDTH_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_DERMA_KEY_POSWIDTH_DEC, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_DERMA_KEY_NEGWIDTH_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_DERMA_KEY_NEGWIDTH_DEC, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_0MM5, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_1MM0, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_2MM0, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_3MM0, enable);	
			
			BatchEnd();
			break;
		}
		case LASER_MODE_SIGNAL:{
			BatchBegin(GDDC_PAGE_STANDBY_SIGNAL);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_GP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SP, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);
#if CONFIG_USING_DUAL_WAVE == 1
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH0, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_CH1, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, enable);
#endif
			BatchSetEnable(GDDC_PAGE_STANDBY_KEY_RESET, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH0, enable);
#if CONFIG_USING_DUAL_WAVE == 1				
			BatchSetEnable(GDDC_PAGE_STANDBY_PROGRESS_CH1, enable);
#endif				
			BatchSetEnable(GDDC_PAGE_STANDBY_SIGNAL_KEY_ENERGY_INTERVAL_ADD, enable);
			BatchSetEnable(GDDC_PAGE_STANDBY_SIGNAL_KEY_ENERGY_INTERVAL_DEC, enable);
		
			BatchEnd();
			break;
		}
		default:break;
	}
}
void updatePowerDisplay(int16_t ch, int16_t mode){//���¹�����ʾ
	uint8_t dispBuf[16];
	switch(mode){
		case LASER_MODE_CW:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1					
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif					
					break;
				}
				default:break;
			}
		}
		case LASER_MODE_SP:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif
					break;
				}
				default:break;
			}					
			break;
		}
		case LASER_MODE_MP:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1					
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif
					break;
				}
				default:break;
			}					
			break;
		}
		case LASER_MODE_GP:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif					
					break;
				}
				default:break;
			}
			break;
		}
		
		case LASER_MODE_DERMA:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1					
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif					
					break;
				}
				default:break;
			}
			updateEnergyDensity();
			break;		
		}
		case LASER_MODE_SIGNAL:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%4.1f W", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, dispBuf);
					sprintf(dispBuf, "%4.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, dispBuf);
#endif					
					break;
				}
				default:break;
			}
			break;
		}
		default:break;
	}
	updateExtralDisplay(mode);
}
void updateExtralDisplay(int16_t mode){//���¶�����ʾ
	uint8_t dispBuf[16];
	fp32_t freq, averagePower, dutyCycle;
	switch(mode){
		case LASER_MODE_CW:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_DUTYCYCLE, dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_FREQUENCY, dispBuf);			
			averagePower = (fp32_t)(NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F;
			sprintf(dispBuf, "%4.2f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_AVERAGE_POWER, dispBuf);
			break;
		}
		case LASER_MODE_SP:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_DUTYCYCLE, dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_FREQUENCY, dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_AVERAGE_POWER, dispBuf);
			break;
		}
		case LASER_MODE_MP:{
			freq =1000.0F / (fp32_t)(NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH]);
			sprintf(dispBuf, "%4.2f", freq);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_FREQUENCY, dispBuf);
						
			dutyCycle = (fp32_t)NVRAM0[EM_LASER_MP_POSWIDTH] / (fp32_t)(NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH]);
			sprintf(dispBuf, "%4.2f", dutyCycle * 100.0F);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_DUTYCYCLE, dispBuf);
			
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F;
			sprintf(dispBuf, "%4.2f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_AVERAGE_POWER, dispBuf);
			break;
		}
		case LASER_MODE_GP:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_FREQUENCY, dispBuf);
			
			dutyCycle = ((fp32_t)NVRAM0[EM_LASER_GP_POSWIDTH] * NVRAM0[EM_LASER_GP_TIMES]) / ((fp32_t)(NVRAM0[EM_LASER_GP_POSWIDTH] + NVRAM0[EM_LASER_GP_NEGWIDTH]) * NVRAM0[EM_LASER_GP_TIMES] + NVRAM0[EM_LASER_GP_GROUP_OFF]);
			sprintf(dispBuf, "%4.2f", dutyCycle * 100.0F);
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_DUTYCYCLE, dispBuf);
			
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F;
			sprintf(dispBuf, "%4.2f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_AVERAGE_POWER, dispBuf);		
			
			break;
		}
		case LASER_MODE_DERMA:{
			freq = 1000.0F / (fp32_t)(NVRAM0[EM_LASER_DERMA_POSWIDTH] + NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
			sprintf(dispBuf, "%4.2f", freq);
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_FREQUENCY, dispBuf);
			
			dutyCycle = (fp32_t)NVRAM0[EM_LASER_DERMA_POSWIDTH] / (fp32_t)(NVRAM0[EM_LASER_DERMA_POSWIDTH] + NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
			sprintf(dispBuf, "%4.2f", dutyCycle * 100.0F);
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DUTYCYCLE, dispBuf);
			
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F;
			sprintf(dispBuf, "%4.2f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_AVERAGE_POWER, dispBuf);
			break;
		}
		case LASER_MODE_SIGNAL:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_DUTYCYCLE, dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_FREQUENCY, dispBuf);
			averagePower = (fp32_t)((NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F);
			sprintf(dispBuf, "%4.2f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_AVERAGE_POWER, dispBuf);
			break;
		}		
		default:break;
	}
}
void updateStandbyDisplay(void){//���·�����ʾ
	uint8_t dispBuf[16];
	NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
	updateReleaseTimeEnergy();
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;//�л�����ҳ��						
			updatePowerDisplay(LASER_SELECT_ALL, LASER_MODE_CW);
			SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
#if CONFIG_USING_DUAL_WAVE == 1
			SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
#endif		
			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x01);
			BatchBegin(GDDC_PAGE_STANDBY_CW);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_GP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, 0x0);
			BatchEnd();			
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (char*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
			break;			
		}
		case LASER_MODE_SP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_SP;//�л�����ҳ��		
			updatePowerDisplay(LASER_SELECT_ALL, LASER_MODE_SP);	
			SetProgressValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
#if CONFIG_USING_DUAL_WAVE == 1			
			SetProgressValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
#endif			
			SetButtonValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_MODE_SP, 0x01);
			BatchBegin(GDDC_PAGE_STANDBY_SP);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_GP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, 0x0);
			BatchEnd();
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (char*)(&NVRAM0[EM_LASER_SCHEME_NAME]));		
			updatePosWidthDisplay(LASER_MODE_SP);
			break;		
		}
		case LASER_MODE_MP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;//�л�����ҳ��
			updatePowerDisplay(LASER_SELECT_ALL, LASER_MODE_MP);
			SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
#if CONFIG_USING_DUAL_WAVE == 1		
			SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
#endif	
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x01);
			BatchBegin(GDDC_PAGE_STANDBY_MP);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_GP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, 0x0);
			BatchEnd();		
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (char*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
			updatePosWidthDisplay(LASER_MODE_MP);
			updateNegWidthDisplay(LASER_MODE_MP);
			break;
		}
		case LASER_MODE_GP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_GP;//�л�����ҳ��
			updatePowerDisplay(LASER_SELECT_ALL, LASER_MODE_GP);
			SetProgressValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
#if CONFIG_USING_DUAL_WAVE == 1
			SetProgressValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
#endif		
			SetButtonValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_MODE_GP, 0x01);
			BatchBegin(GDDC_PAGE_STANDBY_GP);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, 0x0);
			BatchEnd();
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (char*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
			updatePosWidthDisplay(LASER_MODE_GP);
			updateNegWidthDisplay(LASER_MODE_GP);
			sprintf(dispBuf, "%d", NVRAM0[EM_LASER_GP_TIMES]);
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_TIMES, dispBuf);			
			updateGroupOffDisplay();
			break;
		}
		case LASER_MODE_DERMA:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_DERMA;//�л�����ҳ��
			updatePowerDisplay(LASER_SELECT_ALL, LASER_MODE_DERMA);
			SetProgressValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
#if CONFIG_USING_DUAL_WAVE == 1
			SetProgressValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
#endif
			SetButtonValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_MODE_DERMA, 0x01);
			BatchBegin(GDDC_PAGE_STANDBY_DERMA);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_GP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, 0x0);
			BatchEnd();
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (char*)(&NVRAM0[EM_LASER_SCHEME_NAME]));					
			updatePosWidthDisplay(LASER_MODE_DERMA);
			updateNegWidthDisplay(LASER_MODE_DERMA);
			updateEnergyDensity();
			switch(NVRAM0[EM_LASER_DERMA_SPOT_SIZE]){
				case DERMA_SPOT_SIZE_0MM5:{
					BatchBegin(GDDC_PAGE_STANDBY_DERMA);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_1MM0, 0x0);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_2MM0, 0x0);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_3MM0, 0x0);
					BatchEnd();
					SetButtonValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_0MM5, 0x01);
					break;
				}
				case DERMA_SPOT_SIZE_1MM0:{
					BatchBegin(GDDC_PAGE_STANDBY_DERMA);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_0MM5, 0x0);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_2MM0, 0x0);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_3MM0, 0x0);
					BatchEnd();
					SetButtonValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_1MM0, 0x01);
					break;
				}
				case DERMA_SPOT_SIZE_2MM0:{
					BatchBegin(GDDC_PAGE_STANDBY_DERMA);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_0MM5, 0x0);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_1MM0, 0x0);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_3MM0, 0x0);
					BatchEnd();
					SetButtonValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_2MM0, 0x01);
					break;
				}
				case DERMA_SPOT_SIZE_3MM0:{
					BatchBegin(GDDC_PAGE_STANDBY_DERMA);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_0MM5, 0x0);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_1MM0, 0x0);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_2MM0, 0x0);
					BatchEnd();
					SetButtonValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_3MM0, 0x01);
					break;
				}
				default:break;
			}
			switch(NVRAM0[EM_LASER_SELECT]){
				case LASER_SELECT_CH0:{
#if CONFIG_USING_DUAL_WAVE == 1
					BatchBegin(GDDC_PAGE_STANDBY_DERMA);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_SELECT_CH0, 0x01);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_SELECT_CH1, 0x00);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, 0x00);
					BatchEnd();
#endif
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					BatchBegin(GDDC_PAGE_STANDBY_DERMA);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_SELECT_CH0, 0x00);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_SELECT_CH1, 0x01);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, 0x00);
					BatchEnd();
#endif
					break;
				}
				case LASER_SELECT_ALL:{
#if CONFIG_USING_DUAL_WAVE == 1
					BatchBegin(GDDC_PAGE_STANDBY_DERMA);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_SELECT_CH0, 0x00);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_SELECT_CH1, 0x00);
					BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, 0x01);
					BatchEnd();
#endif
					break;
				}
				default:break;
			}
			break;
		}
		case LASER_MODE_SIGNAL:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_SIGNAL;//�л�����ҳ��
			updatePowerDisplay(LASER_SELECT_ALL, LASER_MODE_SIGNAL);
			SetProgressValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_PROGRESS_CH0, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
#if CONFIG_USING_DUAL_WAVE == 1
			SetProgressValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_PROGRESS_CH1, ((uint32_t)NVRAM0[EM_LASER_POWER_CH1] * 100 / CONFIG_MAX_LASERPOWER_CH1));
#endif
			SetButtonValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, 0x01);
			BatchBegin(GDDC_PAGE_STANDBY_SIGNAL);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_SP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_GP, 0x0);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_DERMA, 0x0);
			BatchEnd();
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (char*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
			SetTextInt32(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_SIGNAL_TEXTDISPLAY_ENERGY_INTERVAL ,NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL], 1, 0);	
			break;
		}
		default:break;
	}
	SetScreen(NVRAM0[EM_DC_PAGE]);
}

void updateOptionDisplay(void){//����ѡ����ʾ	
	if(LD(MR_FOOSWITCH_HAND_SWITCH)){
		SetButtonValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON, 0x01);
	}
	else{
		SetButtonValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON, 0x00);
	}
	if(LD(MR_BEEM_TONE)){
		SetButtonValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_TONE, 0x01);
	}
	else{
		SetButtonValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_TONE, 0x00);
	}
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//����BEEM����������
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//����AIM���Ƚ�����
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);//����LCD����
	BatchEnd();
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME ,NVRAM0[DM_BEEM_VOLUME], 1, 0);
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG ,NVRAM0[DM_LCD_BRG], 1, 0);
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_AIM_BRG ,NVRAM0[DM_AIM_BRG], 1, 0);
}

void updatePosWidthDisplay(int16_t mode){//������������ʾ
	uint8_t dispBuf[16];
	switch(mode){
		case LASER_MODE_SP:{
			if(NVRAM0[EM_LASER_SP_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_SP_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_SP_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_SP_TEXTDISPLAY_POSWIDTH, dispBuf);
			break;
		}
		case LASER_MODE_MP:{
			if(NVRAM0[EM_LASER_MP_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_MP_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_MP_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_MP_TEXTDISPLAY_POSWIDTH, dispBuf);
			break;
		}			
		case LASER_MODE_GP:{
			if(NVRAM0[EM_LASER_GP_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_GP_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_GP_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_POSWIDTH, dispBuf);
			break;
		}
		case LASER_MODE_DERMA:{
			if(NVRAM0[EM_LASER_DERMA_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_DERMA_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_DERMA_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_TEXTDISPLAY_POSWIDTH, dispBuf);
			break;		
		}
		default:break;
	}
	updateExtralDisplay(mode);
}
void updateNegWidthDisplay(int16_t mode){//���¸�������ʾ
	uint8_t dispBuf[16];
	switch(mode){
		case LASER_MODE_MP:{
			if(NVRAM0[EM_LASER_MP_NEGWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_MP_NEGWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_MP_NEGWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_MP_TEXTDISPLAY_NEGWIDTH, dispBuf);
			break;
		}
		case LASER_MODE_GP:{
			if(NVRAM0[EM_LASER_GP_NEGWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_GP_NEGWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_GP_NEGWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_NEGWIDTH, dispBuf);
			break;
		
		
		}
		case LASER_MODE_DERMA:{
			if(NVRAM0[EM_LASER_DERMA_NEGWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_DERMA_NEGWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_TEXTDISPLAY_NEGWIDTH, dispBuf);
			break;
		}
		default:break;
	}
	updateExtralDisplay(mode);
}
void updateTimesDisplay(void){//����Times��ʾ
	SetTextInt32(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_TIMES ,NVRAM0[EM_LASER_GP_TIMES], 1, 0);
	updateExtralDisplay(LASER_MODE_GP);
}
void updateGroupOffDisplay(void){//����GroupOff��ʾ
	uint8_t dispBuf[16];
	if(NVRAM0[EM_LASER_GP_GROUP_OFF] < 1000){
		sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_GP_GROUP_OFF]);
	}
	else{
		sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_GP_GROUP_OFF] / 1000));
	}
	SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_GROUP_OFF, dispBuf);
	updateExtralDisplay(LASER_MODE_GP);
}
void standbyKeyEnable(uint8_t ena){//����Standbyʹ��
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
	SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
	SetControlEnable(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
	SetControlEnable(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
	SetControlEnable(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
}
void standbyKeyValue(uint8_t value){//����Standby��ֵ	
	SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
}
void dcHmiLoopInit(void){//��ʼ��ģ��
	uint8_t i;
	NVRAM0[EM_HMI_OPERA_STEP] = 0;
	//���BEEM VOLUME����ֵ�Ƿ�Ϲ�
#if CONFIG_USING_SINGLE_WAVE == 1
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM; i++){
		FDRAM[FD_LASER_SELECT + (i * 30)] = LASER_SELECT_CH0;//Ĭ������Ϊ������
	}
	NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
#endif
	if(NVRAM0[DM_BEEM_VOLUME] > CONFIG_MAX_BEEM_VOLUME){
		NVRAM0[DM_BEEM_VOLUME] = CONFIG_MAX_BEEM_VOLUME;
	}
	if(NVRAM0[DM_BEEM_VOLUME] < CONFIG_MIN_BEEM_VOLUME){
		NVRAM0[DM_BEEM_VOLUME] = CONFIG_MIN_BEEM_VOLUME;
	}
	NVRAM0[EM_COOL_SET_TEMP] = CONFIG_COOL_SET_TEMP;
	NVRAM0[EM_COOL_DIFF_TEMP] = CONFIG_COOL_DIFF_TEMP;
	RES(Y_TEC0);
	SET(Y_FAN0);
	SET(Y_FAN1);
	SET(R_RFID_PASS);
	RES(R_DRIVE_TEMP_HIGH);//�������������ȱ���
#if CONFIG_USING_DUAL_WAVE == 0
	NVRAM0[EM_LASER_POWER_CH1] = 0;
	NVRAM0[EM_LASER_POWER_CH2] = 0;
	NVRAM0[EM_LASER_POWER_CH3] = 0;
#endif
}
static void temperatureLoop(void){//�¶���ѯ˳��
	int16_t temp;
	temp = NVRAM0[SPREG_ADC_2];
	TNTC(EM_DIODE_TEMP0, SPREG_ADC_2);//CODEת��ΪNTC�����¶��¶�
	temp = NVRAM0[EM_DIODE_TEMP0];
	temp = NVRAM0[SPREG_ADC_3];
	TNTC(EM_DIODE_TEMP1, SPREG_ADC_3);//CODEת��ΪNTC�����¶��¶�
	temp = NVRAM0[EM_DIODE_TEMP1];
	temp = NVRAM0[SPREG_ADC_8];
	TENV(EM_ENVI_TEMP, SPREG_ADC_8);//CODEת��Ϊ�����¶�
	temp = NVRAM0[EM_ENVI_TEMP];
	//�ж϶�����0�Ƿ����
	if(NVRAM0[EM_DIODE_TEMP0] > CONFIG_APP_DIODE_HIGH_TEMP){
		SET(R_DIODE_TEMP_HIGH);
	}
	else{
		RES(R_DIODE_TEMP_HIGH);
	}
	if(NVRAM0[EM_DIODE_TEMP0] < CONFIG_APP_DIODE_LOW_TEMP){
		SET(R_DIODE_TEMP_LOW);
	}
	else{
		RES(R_DIODE_TEMP_LOW);
	}
	//�жϻ����Ƿ����
	if(NVRAM0[EM_ENVI_TEMP] > CONFIG_APP_ENVI_HIGH_TEMP){
		SET(R_ENVI_TEMP_HIGH);
	}
	else{
		RES(R_ENVI_TEMP_HIGH);
	}
	//�¿�ִ�� ����ȴ����估����״̬�����¿�	
	if(LD(R_FAN_ENABLE) || LD(R_DIODE_TEMP_HIGH) || LD(R_ENVI_TEMP_HIGH)){
		SET(Y_FAN1);
		if(NVRAM0[EM_DIODE_TEMP0] >= (CONFIG_COOL_SET_TEMP + CONFIG_COOL_DIFF_TEMP)){
			SET(Y_TEC0);
		}
		if(NVRAM0[EM_DIODE_TEMP0] <= (CONFIG_COOL_SET_TEMP + CONFIG_COOL_DIFF_TEMP)){
			RES(Y_TEC0);
		}   
	}
	else{
		RES(Y_TEC0);
		RES(Y_FAN1);
	}
}
static void faultLoop(void){//������ѯ
	uint8_t temp;
	temp = 0;
	if(LD(R_DISABLE_FIBER_PROBE)){//���ι���̽����
		SET(R_FIBER_PROBE);
		SET(R_RFID_PASS);
	}
	else{
		if(LD(X_FIBER_PROBE)){
			SET(R_FIBER_PROBE);
		}
		else{
			RES(R_FIBER_PROBE);
		}
//		if(LD(R_DISABLE_RFID)){
//			SET(R_RFID_PASS);
//		}
//		else{
//			if(LDP(X_FIBER_PROBE)){
//				RES(R_RFID_PASS);//����RFID��ȡ
//			}
//			SET(R_RFID_PASS);
//		}
	}
	temp |= LDB(X_ESTOP);//����1 
	temp |=	LDB(X_INTERLOCK);//����1
	temp |= LDB(X_FOOTSWITCH_NC);//����1
	temp |= LDB(R_FIBER_PROBE);//����1
	temp |= LDB(R_RFID_PASS);//����1
	temp |= LD(R_DIODE_TEMP_HIGH);//����0
	temp |= LD(R_DIODE_TEMP_LOW);//����0
	temp |= LD(R_ENVI_TEMP_HIGH);//����0
	if(temp){
		SET(R_FAULT);
		SET(Y_LED_ALARM);
	}
	else{
		RES(R_FAULT);
		RES(Y_LED_ALARM);
	}
}
void dcHmiLoop(void){//HMI��ѵ����
	if(LDP(SPCOIL_PS100MS)){//ÿ100mS����һ���¶�
		temperatureLoop();
		faultLoop();
	}
	if(LaserFlag_Emiting){
		SET(Y_LED_EMIT);
	}
	else{
		RES(Y_LED_EMIT);
	}
	if(LD(R_DCHMI_RESET_DONE) && LD(R_DCHMI_RESTORE_DONE)){//HMI��λ��ɺ�����ָ��
		hmiCmdSize = queue_find_cmd(hmiCmdBuffer, CMD_MAX_SIZE);//�ӻ������л�ȡһ��ָ��         
        if(hmiCmdSize > 0){//���յ�ָ��ж��Ƿ�Ϊ������ʾ                                                            
            ProcessMessage((PCTRL_MSG)hmiCmdBuffer, hmiCmdSize);//ָ���  
        }                                                                             
	}
	//״̬��
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_POWERUP){//�ϵ粽��	
		SET(R_FAN_ENABLE);
		SET(Y_LED_POWERON);//��Դ�Ƴ���
#if CONFIG_USING_BACKGROUND_APP == 1
		loadScheme();//�ӵ���洢�Ĵ����лָ���������
#endif
#if CONFIG_USING_DUAL_WAVE == 0
	NVRAM0[EM_LASER_POWER_CH1] = 0;
	NVRAM0[EM_LASER_POWER_CH2] = 0;
	NVRAM0[EM_LASER_POWER_CH3] = 0;
#endif		
		NVRAM0[EM_DC_DEFAULT_PASSCODE0] = CONFIG_HMI_DEFAULT_PASSSWORD0;
		NVRAM0[EM_DC_DEFAULT_PASSCODE1] = CONFIG_HMI_DEFAULT_PASSSWORD1;
		NVRAM0[EM_DC_DEFAULT_PASSCODE2] = 0;
		NVRAM0[EM_DC_DEFAULT_PASSCODE3] = 0;
		NVRAM0[DM_DC_OLD_PASSCODE2] = 0;
		NVRAM0[DM_DC_OLD_PASSCODE3] = 0;
	
		NVRAM0[EM_DC_NEW_PASSCODE2] = 0;
		NVRAM0[EM_DC_NEW_PASSCODE3] = 0;
		//��鴢�������Ƿ�Ϲ�
		NVRAM0[TM_START + 0] = NVRAM0[DM_DC_OLD_PASSCODE0] & 0x00FF;
		NVRAM0[TM_START + 1] = (NVRAM0[DM_DC_OLD_PASSCODE0] >> 8) & 0x00FF;
		NVRAM0[TM_START + 2] = NVRAM0[DM_DC_OLD_PASSCODE1] & 0x00FF;
		NVRAM0[TM_START + 3] = (NVRAM0[DM_DC_OLD_PASSCODE1] >> 8) & 0x00FF;
		if((NVRAM0[TM_START + 0] < 0x30) || (NVRAM0[TM_START + 0] > 0x39) ||
		   (NVRAM0[TM_START + 1] < 0x30) || (NVRAM0[TM_START + 1] > 0x39) ||
		   (NVRAM0[TM_START + 2] < 0x30) || (NVRAM0[TM_START + 2] > 0x39) ||
		   (NVRAM0[TM_START + 3] < 0x30) || (NVRAM0[TM_START + 3] > 0x39)){
			NVRAM0[DM_DC_OLD_PASSCODE0] = CONFIG_HMI_DEFAULT_PASSSWORD0;
			NVRAM0[DM_DC_OLD_PASSCODE1] = CONFIG_HMI_DEFAULT_PASSSWORD1;  
		}	
		SET(R_DCHMI_RESET_DOING);
		hmiCmdSize = 0;
		queue_reset();//���HMIָ����ջ�����	
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RESTORE_HMI;
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_RESTORE_HMI){//�ȴ�HMI��λ
		SET(R_FAN_ENABLE);
		T100MS(T100MS_HMI_POWERUP_DELAY, true, CONFIG_CHECK_DELAY_TIME);
		if(LD(T_100MS_START * 16 + T100MS_HMI_POWERUP_DELAY)){
			T100MS(T100MS_HMI_POWERUP_DELAY, false, CONFIG_CHECK_DELAY_TIME);
			RES(R_DCHMI_RESET_DOING);
			SET(R_DCHMI_RESET_DONE);	
			//HMI������FLASH�лָ�����	
			SET(R_DCHMI_RESTORE_DOING);
			FlashRestoreControl(FLASH_DATA_VERSION, FLASH_DATA_ADDR);
			RES(R_DCHMI_RESTORE_DOING);
			SET(R_DCHMI_RESTORE_DONE);
			//����HMIҳ��
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_WAIT_ENTER_PASSCODE;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_POWERUP;//HMIҳ��
			MsgId = 0xFF;//��ǰ��ʾ����ϢID
		
			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, false);
			SetButtonValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_STANDBY, false);
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, false);
			SetButtonValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_STANDBY, false);
			SetButtonValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_STANDBY, false);
			SetButtonValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_STANDBY, false);
			
			SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			SetControlEnable(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			SetControlEnable(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			SetControlEnable(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			
			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);
			SetButtonValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);
			SetButtonValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);
			SetButtonValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);
			SetButtonValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);
			
			SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);

			SetTextValue(GDDC_PAGE_PASSCODE, GDDC_PAGE_PASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
			SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));	
			SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
			SetScreen(NVRAM0[EM_DC_PAGE]);	
		}
		else{
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RESTORE_HMI;	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_CHECK_FAIL_DISPLAY){//�Լ������ʾ
		SET(R_FAN_ENABLE);
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_WAIT_ENTER_PASSCODE){//�ȴ�������������
		RES(R_FAN_ENABLE);
		T100MS(T100MS_ENTER_PASSCODE_DELAY, true, CONFIG_CHECK_DELAY_TIME);
		if(LD(T_100MS_START * 16 + T100MS_ENTER_PASSCODE_DELAY)){
			T100MS(T100MS_ENTER_PASSCODE_DELAY, false, CONFIG_CHECK_DELAY_TIME);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_PASSCODE_INPUT;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_PASSCODE;
			SetScreen(NVRAM0[EM_DC_PAGE]);
		}
		else{
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_WAIT_ENTER_PASSCODE;
		}
		return;
	}
	
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_PASSCODE_INPUT){//���뿪������
		RES(R_FAN_ENABLE);
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_PASSCODE_NEW0){//�ȴ�����������
		RES(R_FAN_ENABLE);
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_STANDBY){//����״̬��
#if	CONFIG_APP_DEBUG == 1
		if(LDP(SPCOIL_PS1000MS)){		
			updateStandbyDebugInfo();
		}
#endif
		switch(NVRAM0[EM_LASER_PULSE_MODE]){//�����Զ��Ӽ�
			case LASER_MODE_SP:{
				if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//������Ӱ���
					T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_SP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_SP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_SP);
						}
					}
				}		
				if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//�����������
					T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_SP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_SP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_SP);
						}
					}
				}
				break;
			}
			case LASER_MODE_MP:{
				if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//������Ӱ���
					T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_MP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_MP_POSWIDTH]);
							updatePosWidthDisplay(LASER_MODE_MP);
						}
					}
				}				
				if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//�����������
					T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_MP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_MP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_MP);
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//������Ӱ���
					T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_MP_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_MP_NEGWIDTH]);
							updateNegWidthDisplay(LASER_MODE_MP);
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//�����������
					T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_MP_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_MP_NEGWIDTH]);
							updateNegWidthDisplay(LASER_MODE_MP);
						}
					}
				}
				break;
			}
			case LASER_MODE_GP:{
				if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//������Ӱ���
					T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_GP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_GP);
						}
					}
				}				
				if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//�����������
					T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_GP_POSWIDTH]);		
							updatePosWidthDisplay(LASER_MODE_GP);
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//������Ӱ���
					T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_GP_NEGWIDTH]);		
							updateNegWidthDisplay(LASER_MODE_GP);
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//�����������
					T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_GP_NEGWIDTH]);	
							updateNegWidthDisplay(LASER_MODE_GP);
						}
					}
				}
				if(LD(R_STANDBY_KEY_TIMES_ADD_DOWN)){//�������Ӱ���
					T10MS(T10MS_TIMES_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_TIMES_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							if(NVRAM0[EM_LASER_GP_TIMES] < CONFIG_MAX_LASER_TIMES){
								NVRAM0[EM_LASER_GP_TIMES] += 1;
								updateTimesDisplay();	
							}
						}
					}
				}
				if(LD(R_STANDBY_KEY_TIMES_DEC_DOWN)){//������������
					T10MS(T10MS_TIMES_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_TIMES_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							if(NVRAM0[EM_LASER_GP_TIMES] > CONFIG_MIN_LASER_TIMES){
								NVRAM0[EM_LASER_GP_TIMES] -= 1;
								updateTimesDisplay();	
							}
						}
					}
				}			
				if(LD(R_STANDBY_KEY_GROUP_OFF_ADD_DOWN)){//�������Ӱ���
					T10MS(T10MS_GROUP_OFF_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_GROUP_OFF_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_GROUP_OFF] =	pulseWidthAdd(NVRAM0[EM_LASER_GP_GROUP_OFF]);	
							updateGroupOffDisplay();			
						}								
					}
				}
				if(LD(R_STANDBY_KEY_GROUP_OFF_DEC_DOWN)){//������������
					T10MS(T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_GROUP_OFF] =	pulseWidthDec(NVRAM0[EM_LASER_GP_GROUP_OFF]);	
							updateGroupOffDisplay();	
						}
					}
				}
				break;
			}
			case LASER_MODE_DERMA:{
				if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//������Ӱ���
					T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_DERMA_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_DERMA_POSWIDTH]);		
							updatePosWidthDisplay(LASER_MODE_DERMA);
						}
					}
				}				
				if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//�����������
					T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_DERMA_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_DERMA_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_DERMA);
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//������Ӱ���
					T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_DERMA_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_DERMA_NEGWIDTH]);	
							updateNegWidthDisplay(LASER_MODE_DERMA);
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//�����������
					T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_DERMA_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
							updateNegWidthDisplay(LASER_MODE_DERMA);
						}
					}
				}					
				break;
			}
			default:break;
		}
		if(LD(R_FAULT)){//�й�����ʾ
			if(LD(R_DIODE_TEMP_HIGH)){//���������±���
				updateWarnMsgDisplay(MSG_DIODE_HTEMP);
			}
			else if(LD(R_DIODE_TEMP_LOW)){//����������NTC��·����
				updateWarnMsgDisplay(MSG_DIODE_LTEMP);
			}
			else if(LD(R_ENVI_TEMP_HIGH)){//�������±���
				updateWarnMsgDisplay(MSG_ENVI_HTEMP);
			}
			else if(LDB(X_ESTOP)){//��ͣ����
				updateWarnMsgDisplay(MSG_ESTOP_PRESS);		
			}
			else if(LDB(X_INTERLOCK)){//��ȫ�����γ�
				updateWarnMsgDisplay(MSG_INTERLOCK_UNPLUG);
			}
			else if(LDB(R_FIBER_PROBE)){//���˰γ�
				updateWarnMsgDisplay(MSG_FIBER_UNPLUG);
			}
			else if(LDB(X_FOOTSWITCH_NC)){//��̤�γ�
				updateWarnMsgDisplay(MSG_FOOTSWITCH_UNPLUG);
			}
			else if(LDB(R_RFID_PASS)){//����ID��ƥ��
				updateWarnMsgDisplay(MSG_FIBER_MISSMATE);
			}
			BeemMode = BEEM_MODE_3;
			BeemDuty = getBeemDuty(NVRAM0[DM_BEEM_VOLUME]);
			BeemFreq = BEEM_FREQ_0;
			BeemEnable = true;
		}
		else{//�޹�����ʾ
			BeemEnable = false;
			updateWarnMsgDisplay(MSG_NO_ERROR);
		}
		if(LDP(R_FAULT)){
			standbyKeyEnable(false);//��ֹStandby����
		}
		if(LDN(R_FAULT)){
			standbyKeyEnable(true);
		}

		if(LD(R_STANDBY_KEY_ENTER_OPTION_DOWN)){//���OPTION
			BeemEnable = false;//�رշ�����
			if(LD(R_ENGINEER_MODE)){
				SetControlVisiable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER, true);//��ʾ�ؼ�
				SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER ,true);//ʹ�ܿؼ�
			}
			else{
				SetControlVisiable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER, false);//��ʾ�ؼ�
				SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER ,false);//ʹ�ܿؼ�
			}
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_OPTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			updateOptionDisplay();
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_STANDBY_KEY_ENTER_OPTION_DOWN);
		}else if(LD(R_STANDBY_KEY_ENTER_SCHEME_DOWN)){//���SCHEME Ĭ����ʾ��һҳ
			BeemEnable = false;//�رշ�����
			if(NVRAM0[DM_SCHEME_NUM] < 16){//��һҳ
				updateScheme_0_Display();//���·�����һҳ����
				seletcSchemeNum(NVRAM0[DM_SCHEME_NUM]);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_0;
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_0;
			}
			else{
				updateScheme_1_Display();//���·����ڶ�ҳ����
				seletcSchemeNum(NVRAM0[DM_SCHEME_NUM]);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_1;
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_1;
			}
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
		}else if(LD(R_STANDBY_KEY_STNADBY_DOWN)){//���READY
			standbyTouchEnable(false);			
			if(LD(X_FOOTSWITCH_NO)){//����̤����
				//�򿪷�����
				BeemMode = BEEM_MODE_3;
				BeemDuty = getBeemDuty(NVRAM0[DM_BEEM_VOLUME]);
				BeemCounter = 0;
				BeemFreq = BEEM_FREQ_0;
				BeemEnable = true;
				updateWarnMsgDisplay(MSG_FOOT_DEPRESSED);//��ʾ������Ϣ
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_ERROR;	
			}
			else if(LDB(R_FAULT)){//�޹��Ͻ���Standby->Ready��������
				LaserTimer_Select = (int8_t)NVRAM0[EM_LASER_SELECT];
				LaserTimer_Mode = (int8_t)NVRAM0[EM_LASER_PULSE_MODE];
				switch(LaserTimer_Mode){
					case LASER_MODE_SP:{
						LaserTimer_TMate 			= NVRAM0[EM_LASER_SP_POSWIDTH];//�������������� 10mS
						break;
					}
					case LASER_MODE_MP:{
						LaserTimer_TMate 			= NVRAM0[EM_LASER_MP_POSWIDTH];//�������������� 10mS
						LaserTimer_TOvertime 		= NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH];//������������ 25mS
						break;
					}
					case LASER_MODE_GP:{
						LaserTimer_TMate 			= NVRAM0[EM_LASER_GP_POSWIDTH];//�������������� 10mS
						LaserTimer_TOvertime 		= NVRAM0[EM_LASER_GP_POSWIDTH] + NVRAM0[EM_LASER_GP_NEGWIDTH];//������������ 25mS
						LaserTimer_PMate 			= NVRAM0[EM_LASER_GP_TIMES];//10������
						LaserTimer_POvertime 		= NVRAM0[EM_LASER_GP_GROUP_OFF];//���33mS
						break;
					}
					case LASER_MODE_DERMA:{
						LaserTimer_TMate 			= NVRAM0[EM_LASER_DERMA_POSWIDTH];//�������������� 10mS
						LaserTimer_TOvertime 		= NVRAM0[EM_LASER_DERMA_POSWIDTH] + NVRAM0[EM_LASER_DERMA_NEGWIDTH];//������������ 25mS
						break;
					}
					default:break;
				}
#if CONFIG_USING_BACKGROUND_APP == 1
				NVRAM0[SPREG_DAC_0] = fitLaserToCode(LASER_SELECT_CH0, NVRAM0[EM_LASER_POWER_CH0]);
				UPDAC0();
#if CONFIG_USING_DUAL_WAVE == 1		
				NVRAM0[SPREG_DAC_1] = fitLaserToCode(LASER_SELECT_CH1, NVRAM0[EM_LASER_POWER_CH1]);
				UPDAC1();
#else
				NVRAM0[SPREG_DAC_2] = 0;UPDAC2();
				NVRAM0[SPREG_DAC_3] = 0;UPDAC3();
#endif
#endif
				//�򿪷�����
				BeemMode = BEEM_MODE_0;
				BeemDuty = getBeemDuty(NVRAM0[DM_BEEM_VOLUME]);
				BeemCounter = 0;
				BeemFreq = BEEM_FREQ_0;
				BeemEnable = true;
				//��ָʾ����
				AimDuty0 = getAimDuty(NVRAM0[DM_AIM_BRG]);
				AimEnable0 = true;	
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;	
			}
			else{
				standbyKeyValue(false);
				standbyTouchEnable(true);
			}
			RES(R_STANDBY_KEY_STNADBY_DOWN);
		}
		else if(LD(R_STANDBY_KEY_SCHEME_SAVE_DOWN)){	
			//��ֹ��Ļ����
			standbyTouchEnable(false);
			saveScheme();//EM->FD
			FDSAV_ONE(NVRAM0[DM_SCHEME_NUM]);//FDRAM->EPROM
			standbyTouchEnable(true);
			RES(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_PARA){//�ȴ�������
		SET(R_FAN_ENABLE);
		T100MS(T100MS_READY_BEEM_DELAY, true, CONFIG_STANDBY_BEEM_DELAY_TIME);//������ʱ����ʱ2000mS//�򿪼�ʱ��
		//��ռ�ʱ��
		if(LD(T_100MS_START * 16 + T100MS_READY_BEEM_DELAY)){
			T100MS(T100MS_READY_BEEM_DELAY, false, 3);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_DONE;
		}
		else{
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_DONE){//����������ϲ�ֹͣ������
		BeemEnable = false;//�رշ�����
		SET(R_FAN_ENABLE);
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
		standbyKeyEnable(true);
		standbyKeyValue(true);
		RES(R_STANDBY_KEY_STNADBY_DOWN);
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_WAIT_TRIGGER){//�ȴ���������	
		updateWarnMsgDisplay(MSG_WAIT_TRIGGER);
		if(LD(R_FAULT)){//Ready״̬��⵽����
			EDLAR();//ֹͣ����
			NVRAM0[SPREG_DAC_0] = 0;UPDAC0();
			NVRAM0[SPREG_DAC_1] = 0;UPDAC1();
			NVRAM0[SPREG_DAC_2] = 0;UPDAC2();
			NVRAM0[SPREG_DAC_3] = 0;UPDAC3();	
			AimEnable0 = false;	
			standbyTouchEnable(true);
			standbyKeyValue(false);
			standbyKeyEnable(false);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
		}
		else if(LD(R_STANDBY_KEY_STNADBY_UP)){//�ص��ȴ�״̬
			EDLAR();//ֹͣ����
			NVRAM0[SPREG_DAC_0] = 0;UPDAC0();
			NVRAM0[SPREG_DAC_1] = 0;UPDAC1();
			NVRAM0[SPREG_DAC_2] = 0;UPDAC2();
			NVRAM0[SPREG_DAC_3] = 0;UPDAC3();
			AimEnable0 = false;	
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			standbyTouchEnable(true);
			standbyKeyValue(false);
			standbyKeyEnable(true);
			RES(R_STANDBY_KEY_STNADBY_UP);
		}
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//�����ش���
			if(LDP(X_FOOTSWITCH_NO)){//���伤��
				//��ֹStandby����
				standbyKeyEnable(false);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				updateWarnMsgDisplay(MSG_LASER_EMIT);
			}
		}
		else{//��ƽ����
			if(LD(X_FOOTSWITCH_NO)){//���伤��	
				standbyKeyEnable(false);
				delayMs(10);				
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				updateWarnMsgDisplay(MSG_LASER_EMIT);
			}	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_EMITING){//��������
		if(LDP(SPCOIL_PS100MS)){//ÿ��1Sˢ���ۼ�ʱ�������
			NVRAM0[TM_START] = (int16_t)((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10);
			LaserRelease_TotalEnergy = LaserRelease_TotalTime * NVRAM0[TM_START];//���㷢������
			if(LaserRelease_TotalEnergy > 99999){
				LaserRelease_TotalEnergy = 99999;
			}
			updateReleaseTimeEnergy();//�����ۼƷ���ʱ�������
		}
#if	CONFIG_APP_DEBUG == 1		
		if(LDP(SPCOIL_PS1000MS)){		
			updateStandbyDebugInfo();
		}
#endif
		if(LaserFlag_Emiting){
			BeemEnable = true;
		}
		else{
			BeemEnable = false;
		}		
		if(LD(R_FAULT)){//���ֹ���
			EDLAR();
			NVRAM0[SPREG_DAC_0] = 0;UPDAC0();
			NVRAM0[SPREG_DAC_1] = 0;UPDAC1();
			NVRAM0[SPREG_DAC_2] = 0;UPDAC2();
			NVRAM0[SPREG_DAC_3] = 0;UPDAC3();
			AimEnable0 = false;//�ر�ָʾ��	
			BeemEnable = false;//�رշ�����			
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			standbyKeyValue(false);
			standbyKeyEnable(false);
			standbyTouchEnable(true);
			updateWarnMsgDisplay(MSG_NO_ERROR);
		}
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//�����ش���
			if(LDP(X_FOOTSWITCH_NO)){//�رռ���
				EDLAR();
				updateWarnMsgDisplay(MSG_NO_ERROR);
				BeemEnable = false;//�رշ�����	
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				standbyKeyEnable(true);
			}
		}
		else{
			if(LDB(X_FOOTSWITCH_NO)){//�رռ���
				EDLAR(); 
				updateWarnMsgDisplay(MSG_NO_ERROR);
				BeemEnable = false;//�رշ�����	
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				standbyKeyEnable(true);
			}
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_ERROR){//Ready��⵽��̤����
		if(LDB(X_FOOTSWITCH_NO)){//��⵽��̤״̬�ָ�����
			BeemEnable = false;
			standbyKeyValue(false);
			standbyKeyEnable(true);
			standbyTouchEnable(true);
			updateWarnMsgDisplay(MSG_NO_ERROR);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
		}
		else{
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_ERROR;
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_OPTION){//ѡ�����
		RES(R_FAN_ENABLE);
		if(LD(R_OPTION_KEY_ENTER_INFORMATION_DOWN)){
			SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_TPYE, LANG_INFO_MSG_TYPE);	
			SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_SN, LANG_INFO_MSG_SN);
			SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_LASER_WAVELENGTH, LANG_INFO_MSG_WAVELENGTH);
			SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_MAX_LASER_POWER, LANG_INFO_MSG_LASER_POWER);
			SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_VERSION, LANG_INFO_MSG_VERSION);
			SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_MANUFACTURE_DATE, LANG_INFO_MSG_MANUFACTURE_DATE);			
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_INFORMATION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_INFORMATION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_OPTION_KEY_ENTER_INFORMATION_DOWN);
		}
		if(LD(R_OPTION_KEY_ENTER_OK_DOWN)){//ȷ��
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			updateStandbyDisplay();
			RES(R_OPTION_KEY_ENTER_OK_DOWN);
		}
		if(LD(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN)){//�������״̬
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_DIAGNOSIS;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_INFORMATION){//��Ϣ����
		RES(R_FAN_ENABLE);
		if(LD(R_INFORMATION_KEY_OK_DOWN)){
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_OPTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_INFORMATION_KEY_OK_DOWN);	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_SCHEME_0){//���������һҳ
		RES(R_FAN_ENABLE);
		if(LD(R_SCHEME_KEY_OK_DOWN)){//ȷ��
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];//ѡ��������Ч
			loadScheme();
			updateStandbyDisplay();
			returnStandbyDisplay();
			RES(R_SCHEME_KEY_OK_DOWN);
		}
		else if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//ȡ��
			loadScheme();//FD->EM
			updateStandbyDisplay();
			returnStandbyDisplay();
			RES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		else if(LD(R_SCHEME_KEY_RENAME_DOWN)){//����
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//��EM_SCHEME_NUM_TMPָ������Ƹ���RENAME�����
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM + (NVRAM0[EM_SCHEME_NUM_TMP] * 30)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_SCHEME_KEY_RENAME_DOWN);
		}
		else if(LD(R_SCHEME_KEY_NEXT_SCHEME)){//��һҳ->�ڶ�ҳ
			updateScheme_1_Display();//���µڶ�ҳ
			seletcSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);//����ѡ����
			updateSchemeInfo(NVRAM0[EM_SCHEME_NUM_TMP]);//����ѡ����ϸ��Ϣ
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_1;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_1;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_SCHEME_KEY_NEXT_SCHEME);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_SCHEME_1){//��������ڶ�ҳ
		RES(R_FAN_ENABLE);
		if(LD(R_SCHEME_KEY_OK_DOWN)){//ȷ��
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];
			loadScheme();
			updateStandbyDisplay();
			returnStandbyDisplay();
			RES(R_SCHEME_KEY_OK_DOWN);
		}
		else if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//ȡ��
			loadFdram();//NVRAM->FD
			loadScheme();//FD->EM
			updateStandbyDisplay();
			returnStandbyDisplay();
			RES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		else if(LD(R_SCHEME_KEY_RENAME_DOWN)){//����
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//��EM_SCHEME_NUM_TMPָ������Ƹ���RENAME�����
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM + (NVRAM0[EM_SCHEME_NUM_TMP] * 30)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_SCHEME_KEY_RENAME_DOWN);
		}
		else if(LD(R_SCHEME_KEY_LAST_SCHEME)){//�ڶ�ҳ->��һҳ
			updateScheme_0_Display();//���µ�һҳ
			seletcSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);//����ѡ����
			updateSchemeInfo(NVRAM0[EM_SCHEME_NUM_TMP]);//����ѡ����ϸ��Ϣ
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_0;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_0;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_SCHEME_KEY_LAST_SCHEME);
		}		
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_RENAME){//��������
		RES(R_FAN_ENABLE);
		if(LD(R_RENAME_TEXTDISPLAY_READ_DONE)){//�������				
			if(NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_0;
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_0;
			}
			else{
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_1;
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_1;
			}
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_RENAME_TEXTDISPLAY_READ_DONE);	
		}
		else if(LD(R_RENAME_KEY_EXIT_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_0;
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_0;
			}
			else{
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_1;
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_1;
			}
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_RENAME_KEY_EXIT_DOWN);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_DIAGNOSIS){//��Ͻ���
		SET(R_FAN_ENABLE);
		if(LD(R_DIAGNOSIS_OK_DOWN)){//����Option
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_OPTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RES(R_DIAGNOSIS_OK_DOWN);
		}
		else if(LD(R_CLEAR_EPROM)){//
			disableWatchDog();//���ο��Ź�
			clearNvram();
			REBOOT();
			
		}
		else if(LDP(SPCOIL_PS1000MS)){
			updateDiognosisInfo();
		}
		return;
	}
}

//��Ϣ��������
//msg ��������Ϣ
//size ��Ϣ����
void ProcessMessage( PCTRL_MSG msg, uint16_t size ){
	uint8_t cmd_type = msg->cmd_type;                                                     //ָ������
    uint8_t ctrl_msg = msg->ctrl_msg;                                                     //��Ϣ������
    uint8_t control_type = msg->control_type;                                             //�ؼ�����
    uint16_t screen_id = PTR2U16(&msg->screen_id);                                        //����ID
    uint16_t control_id = PTR2U16(&msg->control_id);                                      //�ؼ�ID
    uint32_t value = PTR2U32(msg->param);                                                 //��ֵ
    switch(cmd_type){  
		case NOTIFY_TOUCH_PRESS:{//����������
			break;
		}
		case NOTIFY_TOUCH_RELEASE:{//�������ɿ�
			NotifyTouchXY(hmiCmdBuffer[1],PTR2U16(hmiCmdBuffer + 2),PTR2U16(hmiCmdBuffer + 4)); 
			break;
		}			
		case NOTIFY_WRITE_FLASH_OK:{//дFLASH�ɹ�
			NotifyWriteFlash(1);                                                      
			break;              
		}			
		case NOTIFY_WRITE_FLASH_FAILD:{//дFLASHʧ��
			NotifyWriteFlash(0);                        	                              
			break;            
		}			
		case NOTIFY_READ_FLASH_OK:{//��ȡFLASH�ɹ�
			NotifyReadFlash(1, hmiCmdBuffer + 2, size - 6);//ȥ��֡ͷ֡β
			break;                                  
		}			
		case NOTIFY_READ_FLASH_FAILD:{//��ȡFLASHʧ��
			NotifyReadFlash(0,0,0);                                                   
			break;  
		}			
		case NOTIFY_READ_RTC:{//��ȡRTCʱ��
			NotifyReadRTC(hmiCmdBuffer[2], hmiCmdBuffer[3], hmiCmdBuffer[4], hmiCmdBuffer[5], hmiCmdBuffer[6], hmiCmdBuffer[7], hmiCmdBuffer[8]);
			break;
		}
		case NOTIFY_CONTROL:{
			if(ctrl_msg==MSG_GET_CURRENT_SCREEN){//����ID�仯֪ͨ
                NotifyScreen(screen_id);//�����л������ĺ���
            }
            else{
				switch(control_type){
					case kCtrlButton:{//��ť�ؼ�
						NotifyButton(screen_id,control_id,msg->param[1]);                  
						break;  
					}
					case kCtrlText:{//�ı��ؼ�
						NotifyText(screen_id,control_id,msg->param);                       
						break;
					}						
					case kCtrlProgress:{//�������ؼ�
						NotifyProgress(screen_id,control_id,value);                        
						break;
					}						
					case kCtrlSlider:{//�������ؼ�
						NotifySlider(screen_id,control_id,value);                          
						break;
					}						
					case kCtrlMeter:{//�Ǳ�ؼ�
						NotifyMeter(screen_id,control_id,value);                           
						break;
					}
					case kCtrlMenu:{//�˵��ؼ�
						NotifyMenu(screen_id,control_id,msg->param[0],msg->param[1]);      
						break;
					}
					case kCtrlSelector:{//ѡ��ؼ�
						NotifySelector(screen_id,control_id,msg->param[0]);                
						break;
					}						
					case kCtrlRTC:{//����ʱ�ؼ�
						NotifyTimer(screen_id,control_id);
						break;
					}
					default:{
						break;
					}
				}
            } 
            break;  
        } 
    case NOTIFY_HandShake:
        //NOTIFYHandShake();
        break;
    default:
        break;
    }
}


void NotifyScreen(uint16_t screen_id){
    //TODO: ����û�����

}

//���������¼���Ӧ
//press 1���´�������3�ɿ�������;x x����;y y����
void NotifyTouchXY(uint8_t press,uint16_t x,uint16_t y){
    //TODO: ����û�����
}


/*! 
*  \brief  ��������
*/ 
void UpdateUI(void){

}


                                                                          
/*!                                                                              
*  \brief  �������ؼ�֪ͨ                                                       
*  \details  ���������ı�(�����GetControlValue)ʱ��ִ�д˺���                  
*  \param screen_id ����ID                                                      
*  \param control_id �ؼ�ID                                                     
*  \param value ֵ                                                              
*/                                                                              
void NotifySlider(uint16_t screen_id, uint16_t control_id, uint32_t value){                                                                                                                                  

}

/*! 
*  \brief  �Ǳ�ؼ�֪ͨ
*  \details  ����GetControlValueʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param value ֵ
*/
void NotifyMeter(uint16_t screen_id, uint16_t control_id, uint32_t value){
    //TODO: ����û�����
}

/*! 
*  \brief  �˵��ؼ�֪ͨ
*  \details  ���˵���»��ɿ�ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param item �˵�������
*  \param state ��ť״̬��0�ɿ���1����
*/
void NotifyMenu(uint16_t screen_id, uint16_t control_id, uint8_t item, uint8_t state){

}

/*! 
*  \brief  ѡ��ؼ�֪ͨ
*  \details  ��ѡ��ؼ��仯ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param item ��ǰѡ��
*/
void NotifySelector(uint16_t screen_id, uint16_t control_id, uint8_t  item){


}

/*! 
*  \brief  ��ʱ����ʱ֪ͨ����
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*/
void NotifyTimer(uint16_t screen_id, uint16_t control_id){
}

/*! 
*  \brief  ��ȡ�û�FLASH״̬����
*  \param status 0ʧ�ܣ�1�ɹ�
*  \param _data ��������
*  \param length ���ݳ���
*/
void NotifyReadFlash(uint8_t status,uint8_t *_data,uint16_t length){
    //TODO: ����û�����
}

/*! 
*  \brief  д�û�FLASH״̬����
*  \param status 0ʧ�ܣ�1�ɹ�
*/
void NotifyWriteFlash(uint8_t status){
    //TODO: ����û�����
}


/*! 
*  \brief  string ת int
*  \param char *str  �����ַ���
*/
int str2int(const char *str){
    int temp = 0;
    const char *ptr = str;                                                            //��¼�ַ���

    if(*str == '-' || *str == '+')                                                    //�жϵ�һ���ַ��Ƿ�������
    {                                                                            
        str++;                                                                        //ƫ��һλ
    }                                                                            
    while(*str != 0)                                                             
    {                                                                            
        if ((*str < '0') || (*str > '9'))                                             //����Ƿ�Ϊ�����ַ� 
        {                                                                        
            break;                                                               
        }                                                                        
        temp = temp * 10 + (*str - '0');                                              //ת��
        str++;                                                                        //ƫ��һλ
    }                                                                            
    if (*ptr == '-')                                                                  //���Ϊ������ȡ��
    {
        temp = -temp;
    }

    return temp;   
}

#endif