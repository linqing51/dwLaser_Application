#include "dcHmiApp.h"
/*****************************************************************************/
uint8_t hmiCmdBuffer[CMD_MAX_SIZE];//ָ���
static uint8_t standbyKeyTouchEnableStatus = 0;
uint16_t hmiCmdSize;//�ѻ����ָ����
static uint8_t MsgId = 0xFF;//��ǰ��ʾ����ϢID
static void UpdateUI(void);
extern CRC_HandleTypeDef hcrc;
PID fuzzyPid;
/*****************************************************************************/
void loadDeviceConfig(void){//��EPROM���������ļ�
	uint32_t crc32_eprom_cfg, crc32_cfg, temp;
	uint8_t i;
	epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//��EPROM�����豸����
	epromReadDword(CONFIG_EPROM_CFG_CRC, &crc32_eprom_cfg);
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	if(crc32_eprom_cfg != crc32_cfg){//У�������ʹ��Ĭ������
		printf("%s,%d,%s:load device config crc fail!!!\n",__FILE__, __LINE__, __func__);
		printf("%s,%d,%s:using default device config!\n",__FILE__, __LINE__, __func__);
		//Ĭ��ֵ50%ռ�ձ�
		deviceConfig.aimMaxCfg = CONFIG_SPLC_DEFAULT_AIM_DC;
		deviceConfig.redLedBrg = CONFIG_SPLC_DEFAULT_RLED_DC;
		deviceConfig.greenLedBrg = CONFIG_SPLC_DEFAULT_GLED_DC;
		deviceConfig.yellowLedBrg =CONFIG_SPLC_DEFAULT_YLED_DC;
		for (i = 0;i < 10; i++){
			temp = i * 455;
			deviceConfig.calibrationPwr0[i] = (uint16_t)temp;
		}
		for (i = 0;i < 10; i++){
			temp = i * 455;
			deviceConfig.calibrationPwr1[i] = (uint16_t)temp;
		}
		for (i = 0;i < 10; i++){
			temp = i * 455;
			deviceConfig.calibrationPwr2[i] = (uint16_t)temp;
		}
		for (i = 0;i < 10; i++){
			temp = i * 455;
			deviceConfig.calibrationPwr3[i] = (uint16_t)temp;
		}
		saveDeviceConfig();
	}
	else{
		printf("%s,%d,%s:load device config done...\n",__FILE__, __LINE__, __func__);
	}
}
void saveDeviceConfig(void){//������д��EPROM
	uint32_t crc32_cfg;
	epromWrite(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//д��EPROM	
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	epromWriteDword(CONFIG_EPROM_CFG_CRC, &crc32_cfg);//д��У��ֵ
	printf("%s,%d,%s:save device config to eprom done...(CFG CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_cfg);
}
void optionKeyEnable(uint8_t enable){//ѡ����水������
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_TONE, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_ADD, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_DEC, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_LCD_BRG_ADD, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_LCD_BRG_DEC, enable);
	BatchEnd();
	//�ȴ�5mS HMI������
	delayMs(5);
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_ENTER_OK, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_ENTER_INFORMATION, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER, enable);
	BatchEnd();
	delayMs(5);
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetEnable(GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, enable);
	BatchEnd();
	delayMs(5);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_RESTORE, enable);
}
void standbyDebugInfoVisiable(int8_t enable){//Standby������Ϣ�ɼ�
	SetControlVisiable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	
	SetControlVisiable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, enable);	
}
void updateStandbyDebugInfo(void){//����Standby������Ϣ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "TLAS:%05d, TMCU:%05d,FPD:%05d, PD:%05d", NVRAM0[EM_LASER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[EM_LASER_PHOTODIODE], NVRAM0[EM_LASER_PHOTODIODE]);
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_MP:{
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		default:{
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
	}
}
void updateDiognosisTextBox(void){//���������Ϣ�ı���
	uint8_t i;
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	//��NVRAM�и����ı���
	//���¹���У����
	for(i = 0;i < 10; i++){
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr0[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, (GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR0_0P1 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 10; i++){
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr1[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, (GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR1_0P1 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 10; i++){
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr2[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, (GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR2_0P1 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 10; i++){
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr3[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, (GDDC_PAGE_DISGNOSIS_TEXTDISPLAY_PWR3_0P1 + i), (uint8_t*)dispBuf);
	}
}
void updateDiognosisInfo(void){//���������Ϣ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "ADC0:%05d,ADC1:%05d,ADC2:%05d,DAC0:%05d,DAC1:%05d,DAC2:%05d,DAC3:%05d", NVRAM0[SPREG_ADC_0], NVRAM0[SPREG_ADC_1], NVRAM0[SPREG_ADC_2], NVRAM0[SPREG_DAC_0], NVRAM0[SPREG_DAC_1], NVRAM0[SPREG_DAC_2], NVRAM0[SPREG_DAC_3]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO0, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "FS NC:%1d, FS NO:%1d, ES:%d, IL:%1d, FP:%1d", LD(X_FOOTSWITCH_NC),  LD(X_FOOTSWITCH_NO), LD(X_ESTOP_NC), LD(X_INTERLOCK_NC), LD(X_FIBER_PROBE));
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO1, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "TLAS:%05d,TMCU:%05d,TEC:%3d,FAN:%3d", NVRAM0[EM_LASER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[SPREG_LAS_TEC_DC], NVRAM0[SPREG_LAS_FAN_SPEED]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO2, (uint8_t*)dispBuf);
}

void updateScheme_0_Display(void){//����ѡ����淽������
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_0])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_0]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_1])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_1]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_2])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_2]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_3])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_3]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_4])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_4]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_5])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_5]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_6])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_6]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_7])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_7]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_8])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_8]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_9])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_9]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_10])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_10]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_11])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_11]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_12])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_12]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_13])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_13]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_14])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_14]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_15])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_15]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, (uint8_t*)dispBuf);	
	}
	unselectScheme_0_All();
	SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"");
	SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)"");
	SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, (uint8_t*)"");
}
void updateScheme_1_Display(void){//����ѡ����淽������
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_16])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_16]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_17])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_17]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_18])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_18]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_19])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_19]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_20])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_20]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_21])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_21]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_22])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_22]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_23])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_23]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_24])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_24]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_25])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_25]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_26])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_26]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_27])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_27]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_28])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_28]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_29])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_29]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_30])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_30]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM[FD_SCHEME_START_31])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM[FD_SCHEME_START_31]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, (uint8_t*)dispBuf);	
	}
	unselectScheme_1_All();
	SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"");
	SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)"");
	SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, (uint8_t*)"");
}
void updateInformationDisplay(void){//������Ϣ������ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_TPYE, (uint8_t*)INFO_MSG_TYPE[NVRAM0[DM_LANGUAGE]]);	
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_SN, (uint8_t*)INFO_MSG_SN[NVRAM0[DM_LANGUAGE]]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_LASER_WAVELENGTH, (uint8_t*)INFO_MSG_WAVELENGTH[NVRAM0[DM_LANGUAGE]]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_MAX_LASER_POWER, (uint8_t*)INFO_MSG_LASER_POWER[NVRAM0[DM_LANGUAGE]]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_VERSION, (uint8_t*)INFO_MSG_VERSION[NVRAM0[DM_LANGUAGE]]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_MANUFACTURE_DATE, (uint8_t*)INFO_MSG_MANUFACTURE_DATE[NVRAM0[DM_LANGUAGE]]);			
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "UUID:%08X%08X%08X", UniqueId[0], UniqueId[1], UniqueId[2]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_UUID, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "BuildTime:%s:%s\n", __DATE__, __TIME__);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_BUILDTIME, (uint8_t*)dispBuf);	
}
void returnStandbyDisplay(void){//����STANDBY����
	switch(NVRAM0[EM_LASER_PULSE_MODE]){	
		case LASER_MODE_CW:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;
			break;
		}
		case LASER_MODE_MP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;
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
void clearReleaseTimeEnergy(void){//�������ʱ����������ʾ
	LaserRelease_TotalTime0 = 0;
	LaserRelease_TotalTime1 = -1;
	LaserRelease_TotalEnergy0 = 0;
	LaserRelease_TotalEnergy1 = -1;
	updateReleaseTimeEnergy(true);
}
void updateReleaseTimeEnergy(uint8_t refresh){//ˢ�·���ʱ������
	uint8_t minute;
	uint8_t seconds;
	char dispBuf1[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf1, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	//refresh = 1ǿ�Ƹ���
	//refresh = 0�仯����
	minute = LaserRelease_TotalTime0 / 60;
	seconds = LaserRelease_TotalTime0 % 60;
	if((LaserRelease_TotalTime0 != LaserRelease_TotalTime1) || refresh){//ʱ��
		sprintf(dispBuf1, "%3d:%02d", minute, seconds);//00:00
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_TREATMENT_TIME, (uint8_t*)dispBuf1);		
		LaserRelease_TotalTime1 =LaserRelease_TotalTime0;
	}
	if((LaserRelease_TotalEnergy0 != LaserRelease_TotalEnergy1) || refresh){//����
		sprintf(dispBuf1, "%8.1f J", LaserRelease_TotalEnergy0);//00:00
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ENERGEY, (uint8_t*)dispBuf1);
		LaserRelease_TotalEnergy1 = LaserRelease_TotalEnergy0;
	}
}
void updateWarnMsgDisplay(uint8_t id){//���¾�����ʾ��
	const char *pstr;
	if((MsgId != id) || (NVRAM0[EM_DC_PAGE] != NVRAM1[EM_DC_PAGE])){
		switch(id){
			case MSG_NO_ERROR:{
				pstr = WARN_MSG_NO_ERROR[NVRAM0[DM_LANGUAGE]];
				break;
			}
			case MSG_INTERLOCK_UNPLUG:{
				pstr = WARN_MSG_INTERLOCK_UNPLUG[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_FOOTSWITCH_UNPLUG:{
				pstr = WARN_MSG_FOOTSWITCH_UNPLUG[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_ESTOP_PRESS:{
				pstr = WARN_MSG_ESTOP_PRESS[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_FIBER_UNPLUG:{
				pstr = WARN_MSG_FIBER_UNPLUG[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_OUT_ENERGY:{
				pstr = WARN_MSG_OUT_ENERGY[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_DIODE_HTEMP:{
				pstr = WARN_MSG_DIODE_HTEMP[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_DIODE_LTEMP:{
				pstr = WARN_MSG_DIODE_LTEMP[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_DIODE0_OVERCURRENT:{
				pstr = WARN_MSG_DIODE0_OVERCURRENT[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_DIODE1_OVERCURRENT:{
				pstr = WARN_MSG_DIODE1_OVERCURRENT[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_NTC_ERROR:{
				pstr = WARN_MSG_NTC_ERROR[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_ENVI_HTEMP:{
				pstr = WARN_MSG_ENVI_HTEMP[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_FOOT_DEPRESSED:{
				pstr = WARN_MSG_FOOT_DEPRESSED[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_LASER_EMIT:{
				pstr = WARN_MSG_LASER_EMIT[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_WAIT_TRIGGER:{
				pstr = WARN_MSG_WAIT_TRIGGER[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			case MSG_FIBER_MISSMATE:{
				pstr = WARN_MSG_FIBER_MISSMATE[(NVRAM0[DM_LANGUAGE])];
				break;
			}
			default:{
				pstr = WARN_MSG_NO_ERROR[(NVRAM0[DM_LANGUAGE])];
				break;
			}
		}
		switch(NVRAM0[EM_DC_PAGE]){
			case GDDC_PAGE_STANDBY_CW:{SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, (uint8_t*)pstr);break;}
			case GDDC_PAGE_STANDBY_MP:{SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, (uint8_t*)pstr);break;}
			default:break;
		}
		MsgId = id;
	}
}
void updateSchemeInfo(int16_t cn){//����SCHEME ��ϸ����
	char dispBuf1[CONFIG_DCHMI_DISKBUF_SIZE], dispBuf2[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf1, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	memset(dispBuf2, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	int16_t mode;
	int16_t	power0;
	int16_t power1;
	int16_t posWidth;
	int16_t negWidth;
	int16_t times;
	int16_t	groupOff;
	int16_t energyInterval;
	power0 ^= power0;
	power1 ^= power1;
	if(cn < 0)
		cn = 0;
	if(cn > CONFIG_HMI_SCHEME_NUM)
		cn = CONFIG_HMI_SCHEME_NUM;
	mode = FDRAM[cn * 64 + FD_LASER_PULSE_MODE]; 
	power0 = FDRAM[cn * 64 + FD_LASER_POWER_CH0];
	power1 = FDRAM[cn * 64 + FD_LASER_POWER_CH1];
	
	memset(dispBuf1, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);	
	memset(dispBuf2, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(mode){
		case LASER_MODE_CW:{
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:CW");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:CW");
			}
			sprintf(dispBuf2, "");
			break;
		}
		case LASER_MODE_SP:{
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:Single");			
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:Single");
			}
			posWidth = FDRAM[cn * 64 + FD_LASER_SP_POSWIDTH];
			if((cn == 13) || (cn == 14) || (cn == 17)){
				sprintf(dispBuf2, "OnTime:%dmS, 4 passes", posWidth);
			}
			else{
				sprintf(dispBuf2, "OnTime:%dmS", posWidth);
			}
			break;
		}
		case LASER_MODE_MP:{
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:Pulsed");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:Pulsed");
			}
			posWidth = FDRAM[cn * 64 + FD_LASER_MP_POSWIDTH];
			negWidth = FDRAM[cn * 64 + FD_LASER_MP_NEGWIDTH];
			sprintf(dispBuf2, "OnTime:%dmS, OffTime:%dmS", posWidth, negWidth);
			break;
		}
		case LASER_MODE_GP:{
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:Group");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:Group");
			}
			posWidth = FDRAM[cn * 64 + FD_LASER_GP_POSWIDTH];
			negWidth = FDRAM[cn * 64 + FD_LASER_GP_NEGWIDTH];
			times = FDRAM[cn * 64 + FD_LASER_GP_TIMES];
			groupOff = FDRAM[cn * 64 + FD_LASER_GP_GROUP_OFF];
			sprintf(dispBuf2, "OnTime:%dmS, OffTime:%dmS, Times:%d, GroupOff:%dmS", posWidth, negWidth, times, groupOff);
			break;
		}
		case LASER_MODE_DERMA:{
			posWidth = FDRAM[cn * 64 + FD_LASER_DERMA_POSWIDTH];
			negWidth = FDRAM[cn * 64 + FD_LASER_DERMA_NEGWIDTH];
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:DERAM");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:DERAM");
			}
			sprintf(dispBuf2, "OnTime:%dmS, OffTime:%dmS", posWidth, negWidth);
			break;
		}
		case LASER_MODE_SIGNAL:{
			energyInterval = FDRAM[cn * 64 + FD_LASER_SIGNAL_ENERGY_INTERVAL];
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:SIGNAL");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"Mode:SIGNAL");
			}
			sprintf(dispBuf2, "Energy Interval:%dJ/cm", energyInterval);
			break;
		}
		default:break;
	}
	sprintf(dispBuf1, "1470nM Power:%3.1fW", ((fp32_t)power0 / 10.0F));
	if(cn < 16){
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)dispBuf1);
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, (uint8_t*)dispBuf2);
	}
	else{
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)dispBuf1);
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, (uint8_t*)dispBuf2);
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
void readyPageTouchEnable(int8_t enable){//Ready page->adjust key touch
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGEY_ADD, enable);	
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGEY_DEC, enable);
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_ADD, enable);	
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_DEC, enable);	
}
void readyKeyTouchEnable(int8_t enable){
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);
}
void readyKeyValue(int8_t value){
	SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
}
void standbyPageTouchEnable(int8_t enable){//Standby���津��
	//STANDBY CW
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_POWER_ADD, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_POWER_DEC, enable);		
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);		
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_AIM_BRG_ADD, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_AIM_BRG_DEC, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, enable);	
	//STANDBY MP
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_POWER_ADD, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_POWER_DEC, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);		
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_AIM_BRG_ADD, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_AIM_BRG_DEC, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, enable);	
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, enable);		
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_POSWIDTH_DEC, enable);		
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, enable);		
	SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_DEC, enable);			
}
void standbyKeyTouchEnable(int8_t enable){//Standby key����
	if(enable != standbyKeyTouchEnableStatus){
		SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);	
		SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);	
		standbyKeyTouchEnableStatus = enable;
	}
}
void standbyKeyValue(uint8_t value){//����Standby��ֵ
	SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
}
void updatePowerDisplay(int16_t ch, int16_t mode){//���¹�����ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(mode){
		case LASER_MODE_CW:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER, (uint8_t*)dispBuf);
					break;
				}
				default:break;
			}
		}
		case LASER_MODE_MP:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER, (uint8_t*)dispBuf);
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
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	fp32_t freq, averagePower, dutyCycle;
	switch(mode){
		case LASER_MODE_CW:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);			
			averagePower = (fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
			sprintf(dispBuf, "%3.1f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_AVERAGE_POWER, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_MP:{
			freq =1000.0F / (fp32_t)(NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH]);
			sprintf(dispBuf, "%4.1f", freq);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);
						
			dutyCycle = (fp32_t)NVRAM0[EM_LASER_MP_POSWIDTH] / (fp32_t)(NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH]);
			sprintf(dispBuf, "%4.1f", dutyCycle * 100.0F);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
			sprintf(dispBuf, "%3.1f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AVERAGE_POWER, (uint8_t*)dispBuf);
			break;
		}
		default:break;
	}
}
void updateStandbyDisplay(void){//���·�����ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;//�л�����ҳ��						
			updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_CW);
			SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x01);
			BatchBegin(GDDC_PAGE_STANDBY_CW);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x0);
			BatchEnd();			
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
			break;			
		}
		case LASER_MODE_MP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;//�л�����ҳ��
			updatePowerDisplay(LASER_SELECT_CH0, LASER_MODE_MP);
			SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x01);
			BatchBegin(GDDC_PAGE_STANDBY_MP);
			BatchSetButtonValue(GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x0);
			BatchEnd();		
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
			updatePosWidthDisplay(LASER_MODE_MP);
			updateNegWidthDisplay(LASER_MODE_MP);
			break;
		}
		default:break;
	}
	SetScreen(NVRAM0[EM_DC_PAGE]);
	updateReleaseTimeEnergy(true);
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
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);//����LCD����
	BatchEnd();
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME ,NVRAM0[DM_BEEM_VOLUME], 1, 0);
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG ,NVRAM0[DM_LCD_BRG], 1, 0);
}

void updatePosWidthDisplay(int16_t mode){//������������ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	switch(mode){
		case LASER_MODE_MP:{
			if(NVRAM0[EM_LASER_MP_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_MP_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_MP_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POSWIDTH, (uint8_t*)dispBuf);
			break;
		}			

		default:break;
	}
	updateExtralDisplay(mode);
}
void updateNegWidthDisplay(int16_t mode){//���¸�������ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	switch(mode){
		case LASER_MODE_MP:{
			if(NVRAM0[EM_LASER_MP_NEGWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_MP_NEGWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_MP_NEGWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NEGWIDTH, (uint8_t*)dispBuf);
			break;
		}
		default:break;
	}
	updateExtralDisplay(mode);
}
void updateAcousticTime(int16_t time){
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[DM_ACOUSTIC_TIME]) / 10));
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ACOUSTIC_TIME, (uint8_t*)dispBuf);
}
void updateAcousticEnergy(int16_t energy){
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[DM_ACOUSTIC_ENERGY]) / 10));
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ACOUSTIC_ENERGEY, (uint8_t*)dispBuf);
}

void dcHmiLoopInit(void){//��ʼ��ģ��
	uint8_t i;
#if CONFIG_USING_DCHMI_APP == 1
	printf("%s,%d,%s:start hmi uart init......\n",__FILE__, __LINE__, __func__);
	hmiUartInit();
#endif
	NVRAM0[DM_LANGUAGE] = MSG_EN;//Ĭ������Ӣ��
	NVRAM0[EM_HMI_OPERA_STEP] = 0;
	//���MUSIC VOLUME����ֵ�Ƿ�Ϲ�
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM; i++){
		if(FDRAM[FD_LASER_SELECT + (i * 64)] != LASER_SELECT_CH0){//Ĭ������Ϊ������
			FDRAM[FD_LASER_SELECT + (i * 64)] = LASER_SELECT_CH0;
		}
	}
	NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
	NVRAM0[TMP_REG_0] = CONFIG_MIN_BEEM_VOLUME;
	NVRAM0[TMP_REG_1] = CONFIG_MAX_BEEM_VOLUME;
	LIMS16(DM_BEEM_VOLUME, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = CONFIG_MIN_AIM_BRG;
	NVRAM0[TMP_REG_1] = CONFIG_MAX_AIM_BRG;
	LIMS16(DM_AIM_BRG, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = CONFIG_MIN_LCD_BRG;
	NVRAM0[TMP_REG_1] = CONFIG_MAX_LCD_BRG;
	LIMS16(DM_LCD_BRG, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = 7;
	LIMS16(DM_LANGUAGE, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[SPREG_LAS_TEC_DC] = 0;
	NVRAM0[SPREG_LAS_FAN_SPEED] = 0;
	SSET(R_RFID_PASS);
	//���α���
	RRES(R_LASER_TEMP_HIGH);							
	RRES(R_LASER_TEMP_LOW);								
	RRES(R_MCU_TEMP_HIGH);										
	RRES(R_MCU_TEMP_LOW);									
	RRES(R_FAULT);
	//��̤����
	SSET(R_FOOTSWITCH_PLUG);
	//PID ��ʼ��
	PID_Init(&fuzzyPid);
	__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 0);	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//��TIM
}
static void temperatureLoop(void){//�¶���ѯ��ѯ
	uint16_t temp16;
	TNTC(EM_LASER_TEMP, SPREG_ADC_0);//CODEת��ΪNTC�����¶��¶�
	TENV(EM_MCU_TEMP, SPREG_ADC_3);//CODEת��ΪMCU�¶�
	//�ж϶�����0�Ƿ����
	if(NVRAM0[EM_LASER_TEMP] > CONFIG_APP_DIODE_HIGH_TEMP){//����������
		SSET(R_LASER_TEMP_HIGH);
	}
	else{
		RRES(R_LASER_TEMP_HIGH);
	}
	if(NVRAM0[EM_LASER_TEMP] < CONFIG_APP_DIODE_LOW_TEMP){//�������¶ȹ���
		SSET(R_LASER_TEMP_LOW);
	}
	else{
		RRES(R_LASER_TEMP_LOW);
	}
	//�жϻ����Ƿ����
	if(NVRAM0[EM_MCU_TEMP] > CONFIG_APP_ENVI_HIGH_TEMP){//�����¶ȹ���
		SSET(R_MCU_TEMP_HIGH);
	}
	else{
		RRES(R_MCU_TEMP_HIGH);
	}	
	//�¿�ִ�� ����ȴ����估����״̬�����¿�	
	if(LD(R_LASER_TEMP_HIGH) || LD(R_MCU_TEMP_HIGH)){//����״̬�������򿪷���
		NVRAM0[SPREG_LAS_FAN_SPEED] = 255;
	}
	else{//�¶�����
		if(LDP(SPCOIL_PS1000MS)){//ÿ����·����ٶ�
			if(NVRAM0[EM_LASER_TEMP] < 200){//<15.0C
				NVRAM0[SPREG_LAS_FAN_SPEED] = 0;
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 200) && (NVRAM0[EM_LASER_TEMP] < 220)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 80;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 220) && (NVRAM0[EM_LASER_TEMP] < 240)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 95;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 240) && (NVRAM0[EM_LASER_TEMP] < 260)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 110;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 260) && (NVRAM0[EM_LASER_TEMP] < 280)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 125;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 280) && (NVRAM0[EM_LASER_TEMP] < 300)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 140;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 300) && (NVRAM0[EM_LASER_TEMP] < 320)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 155;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 320) && (NVRAM0[EM_LASER_TEMP] < 340)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 170;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 340) && (NVRAM0[EM_LASER_TEMP] < 360)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 185;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 360) && (NVRAM0[EM_LASER_TEMP] < 380)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 210;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 380) && (NVRAM0[EM_LASER_TEMP] < 400)){
				NVRAM0[SPREG_LAS_FAN_SPEED] = 240;		
			}
			else{
				NVRAM0[SPREG_LAS_FAN_SPEED] = 255;
			}
		}
		//TEC PID ����
		PID_realize(&fuzzyPid, CONFIG_APP_DIODE_STT_TEMP, NVRAM0[EM_LASER_TEMP]);
		temp16 = (uint16_t)(fuzzyPid.pwm_out * -1.0F);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, temp16);
	}
}
static void faultLoop(void){//������ѯ
	uint8_t temp;
	temp = 0;
	if(LD(R_DISABLE_FIBER_PROBE)){//���ι���̽����
		SSET(R_FIBER_PROBE);
	}
	else{
		if(LD(X_FIBER_PROBE)){
			SSET(R_FIBER_PROBE);
		}
		else{
			RRES(R_FIBER_PROBE);
		}
	}
	if(LD(R_DISABLE_RFID)){//���ι���RFID̽��
		SSET(R_RFID_PASS);
	}
	if(LD(R_DISABLE_ESTOP)){//���ν���ֹͣ����
		SSET(R_ESTOP);
	}
	else{
		if(LD(X_ESTOP_NC)){
			SSET(R_ESTOP);
		}
		else{
			RRES(R_ESTOP);
		}
	}
	
	if(LD(R_DISABLE_INTERLOCK)){
		SSET(R_INTERLOCK);
	}
	else{
		if(LD(X_INTERLOCK_NC)){
			SSET(R_INTERLOCK);
		}
		else{
			RRES(R_INTERLOCK);
		}
	}
	
	if(LD(R_DISABLE_TEMPERATURE)){//���θ��±���
		RRES(R_LASER_TEMP_HIGH);
		RRES(R_MCU_TEMP_LOW);
	}
	if(LD(R_DISABLE_FOOTSWITCH)){//���ν�̤����̽�⡢ʹ����Ļ���ⷢ�����
		SSET(R_FOOTSWITCH_PLUG);
		if(LD(R_HMI_FOOTSWITCH_PRESS)){
			SSET(R_FOOTSWITCH_PRESS);
		}
		else{
			RRES(R_FOOTSWITCH_PRESS);
		}
	}
	else{
		if(LD(X_FOOTSWITCH_NC)){//����
			SSET(R_FOOTSWITCH_PLUG);
		}
		else{
			RRES(R_FOOTSWITCH_PLUG);
		}
		if(LD(X_FOOTSWITCH_NO)){//����
			SSET(R_FOOTSWITCH_PRESS);
		}
		else{
			RRES(R_FOOTSWITCH_PRESS);
		}
	}
	temp |= LDB(R_ESTOP);//����1 
	temp |=	LDB(R_INTERLOCK);//����1
	temp |= LDB(R_FOOTSWITCH_PLUG);//����1
	temp |= LDB(R_FIBER_PROBE);//����1
	temp |= LDB(R_RFID_PASS);//����1
	temp |= LD(R_LASER_TEMP_HIGH);//����0
	temp |= LD(R_MCU_TEMP_LOW);//����0
	if(temp){
		SSET(R_FAULT);
	}
	else{
		RRES(R_FAULT);
	}
	//
	if(LD(R_FAULT)){
		RRES(Y_GREEN_LED);//�ر��̵�
		RRES(Y_YELLOW_LED);//�ر�����
		SSET(Y_RED_LED);//�򿪺��
	}
	else if(LaserFlag_Emiting){
		RRES(Y_GREEN_LED);//�ر��̵�
		SSET(Y_YELLOW_LED);//������
		RRES(Y_RED_LED);//�رպ��
	}
	else{
		SSET(Y_GREEN_LED);//���̵�
		RRES(Y_YELLOW_LED);//�ر�����
		RRES(Y_RED_LED);//�رպ��
	}
}
static void laserStateLoop(void){//����״̬��ѯ
	fp32_t volt;
	//���㼤�⹦��
	volt = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_1]) / (NVRAM0[SPREG_ADC_4] * 4096.0F);//�����ѹֵ
	if(volt > 3.3F){
		volt = 3.3;
	}
	if(volt < 0){
		volt = 0;
	}
	NVRAM0[EM_LASER_PHOTODIODE] = volt * 1000;
}
void dcHmiLoop(void){//HMI��ѵ����	
	if(LDP(R_FOOTSWITCH_PLUG)){
		printf("%s,%d,%s:Footswitch Plug!\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(R_FOOTSWITCH_PLUG)){
		printf("%s,%d,%s:Footswitch UnPlug!\n",__FILE__, __LINE__, __func__);
	}
	if(LDP(R_FOOTSWITCH_PRESS)){
		printf("%s,%d,%s:Footswitch Pressed!\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(R_FOOTSWITCH_PRESS)){
		printf("%s,%d,%s:Footswitch UnPressed!\n",__FILE__, __LINE__, __func__);
	}
	temperatureLoop();//�¿س���
	faultLoop();
/*****************************************************************************/
	laserStateLoop();
/*****************************************************************************/
	if(LD(R_DCHMI_RESET_DONE) && LD(R_DCHMI_RESTORE_DONE)){//HMI��λ��ɺ�����ָ��
		hmiCmdSize = queue_find_cmd(hmiCmdBuffer, CMD_MAX_SIZE);//�ӻ������л�ȡһ��ָ��         
        if(hmiCmdSize > 0){//���յ�ָ��ж��Ƿ�Ϊ������ʾ                                                            
            ProcessMessage((PCTRL_MSG)hmiCmdBuffer, hmiCmdSize);//ָ���  
        }                                                                             
	}
	//״̬��
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_POWERUP){//�ϵ粽��	
		loadScheme();//�ӵ���洢�Ĵ����лָ���������	
		NVRAM0[EM_DC_DEFAULT_PASSCODE0] = CONFIG_HMI_DEFAULT_PASSWORD0;
		NVRAM0[EM_DC_DEFAULT_PASSCODE1] = CONFIG_HMI_DEFAULT_PASSWORD1;
		NVRAM0[EM_DC_DEFAULT_PASSCODE2] = CONFIG_HMI_DEFAULT_PASSWORD2;
		NVRAM0[EM_DC_DEFAULT_PASSCODE3] = 0;
		NVRAM0[DM_DC_OLD_PASSCODE2] = 0;
		NVRAM0[DM_DC_OLD_PASSCODE3] = 0;
	
		NVRAM0[EM_DC_NEW_PASSCODE2] = 0;
		NVRAM0[EM_DC_NEW_PASSCODE3] = 0;
		//��鴢�������Ƿ�Ϲ�
		NVRAM0[TMP_REG_0 + 0] = NVRAM0[DM_DC_OLD_PASSCODE0] & 0x00FF;
		NVRAM0[TMP_REG_1 + 1] = (NVRAM0[DM_DC_OLD_PASSCODE0] >> 8) & 0x00FF;
		NVRAM0[TMP_REG_2 + 2] = NVRAM0[DM_DC_OLD_PASSCODE1] & 0x00FF;
		NVRAM0[TMP_REG_3 + 3] = (NVRAM0[DM_DC_OLD_PASSCODE1] >> 8) & 0x00FF;
		if((NVRAM0[TMP_REG_0 + 0] < 0x30) || (NVRAM0[TMP_REG_0 + 0] > 0x39) ||
		   (NVRAM0[TMP_REG_1 + 1] < 0x30) || (NVRAM0[TMP_REG_1 + 1] > 0x39) ||
		   (NVRAM0[TMP_REG_2 + 2] < 0x30) || (NVRAM0[TMP_REG_2 + 2] > 0x39) ||
		   (NVRAM0[TMP_REG_3 + 3] < 0x30) || (NVRAM0[TMP_REG_3 + 3] > 0x39)){
			NVRAM0[DM_DC_OLD_PASSCODE0] = CONFIG_HMI_DEFAULT_PASSWORD0;
			NVRAM0[DM_DC_OLD_PASSCODE1] = CONFIG_HMI_DEFAULT_PASSWORD1;
			NVRAM0[DM_DC_OLD_PASSCODE2] = CONFIG_HMI_DEFAULT_PASSWORD2;
			NVRAM0[DM_DC_OLD_PASSCODE3] = CONFIG_HMI_DEFAULT_PASSWORD3;
		}	
		SSET(R_DCHMI_RESET_DOING);
		hmiCmdSize = 0;
		queue_reset();//���HMIָ����ջ�����	
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RESTORE_HMI;
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_RESTORE_HMI){//�ȴ�HMI��λ
		T100MS(T100MS_HMI_POWERUP_DELAY, true, CONFIG_WAIT_HMI_DELAY_TIME);
		if(LD(T_100MS_START * 16 + T100MS_HMI_POWERUP_DELAY)){
			printf("%s,%d,%s:hmi delay done......\n",__FILE__, __LINE__, __func__);
			T100MS(T100MS_HMI_POWERUP_DELAY, false, CONFIG_WAIT_HMI_DELAY_TIME);
			RRES(R_DCHMI_RESET_DOING);
			SSET(R_DCHMI_RESET_DONE);	
			//HMI������FLASH�лָ�����	
			SSET(R_DCHMI_RESTORE_DOING);
			FlashRestoreControl(FLASH_DATA_VERSION, FLASH_DATA_ADDR);
			RRES(R_DCHMI_RESTORE_DOING);
			SSET(R_DCHMI_RESTORE_DONE);
			//����HMIҳ��
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_WAIT_ENTER_PASSCODE;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_POWERUP;//HMIҳ��
			MsgId = 0xFF;//��ǰ��ʾ����ϢID
		
			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, false);
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, false);
			
			SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			
			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);
					
			SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
		
			SetTextValue(GDDC_PAGE_PASSCODE, GDDC_PAGE_PASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
			SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));

			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//��վ�����Ϣ��
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//��վ�����Ϣ��

			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_RFID, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FIBER_PROBE, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FAN_CONTRAL, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_CLEAR_EPROM, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FOOTSWITCH, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_TEMPERATURE, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_ESTOP, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_INTERLOCK, false);		
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_CALIBRATION_MODE, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);

			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, false);
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, false);
			
			SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			//�򿪷�����
			NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_0;
			NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
			SSET(SPCOIL_BEEM_ENABLE);
		}
		else{
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RESTORE_HMI;	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_CHECK_FAIL_DISPLAY){//�Լ������ʾ
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_WAIT_ENTER_PASSCODE){//�ȴ�������������
		T100MS(T100MS_ENTER_PASSCODE_DELAY, true, CONFIG_WAIT_PASSWORD_DELAY_TIME);
		if(LD(T_100MS_START * 16 + T100MS_ENTER_PASSCODE_DELAY)){
			RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
			T100MS(T100MS_ENTER_PASSCODE_DELAY, false, CONFIG_WAIT_PASSWORD_DELAY_TIME);
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
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_PASSCODE_NEW0){//�ȴ�����������		
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_STANDBY){//����״̬��
		if(LD(R_ENGINEER_MODE)){//����ģʽ��ʾ������Ϣ
			if(LDP(SPCOIL_PS1000MS)){		
				updateStandbyDebugInfo();
			}
		}
		if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//������Ӱ���
			T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_MP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_MP_POSWIDTH]);
					updatePosWidthDisplay(LASER_MODE_MP);
					if(NVRAM0[EM_LASER_MP_POSWIDTH] >= CONFIG_MAX_LASER_POSWIDTH){//�ﵽ���ֵ��ֹͣ�Լ�
						RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
				}
			}
		}					
		if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//�����������
			T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_MP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_MP_POSWIDTH]);	
					updatePosWidthDisplay(LASER_MODE_MP);
					if(NVRAM0[EM_LASER_MP_POSWIDTH] <= CONFIG_MIN_LASER_POSWIDTH){//�ﵽ��Сֵ��ֹͣ�Լ�
						RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
				}
			}
		}
		if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//������Ӱ���
			T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_MP_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_MP_NEGWIDTH]);
					updateNegWidthDisplay(LASER_MODE_MP);
					if(NVRAM0[EM_LASER_MP_NEGWIDTH] >= CONFIG_MAX_LASER_NEGWIDTH){//�ﵽ���ֵ��ֹͣ�Լ�
						RRES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}							
				}
			}
		}
		if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//�����������
			T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_MP_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_MP_NEGWIDTH]);
					updateNegWidthDisplay(LASER_MODE_MP);
					if(NVRAM0[EM_LASER_MP_NEGWIDTH] <= CONFIG_MIN_LASER_NEGWIDTH){//�ﵽ��Сֵ��ֹͣ�Լ�
						RRES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
				}
			}
		}
		if(LDB(R_FAULT)){//�޹�����ʾ
			RRES(SPCOIL_BEEM_ENABLE);
			updateWarnMsgDisplay(MSG_NO_ERROR);
			standbyKeyTouchEnable(true);
		}
		if(LD(R_FAULT)){
			if(LD(R_LASER_TEMP_HIGH)){//���������±���
				updateWarnMsgDisplay(MSG_DIODE_HTEMP);
			}
			else if(LD(R_LASER_TEMP_LOW)){//����������NTC��·����
				updateWarnMsgDisplay(MSG_DIODE_LTEMP);
			}
			else if(LD(R_MCU_TEMP_HIGH)){//�������±���
				updateWarnMsgDisplay(MSG_ENVI_HTEMP);
			}
			else if(LDB(R_ESTOP)){//��ͣ����
				updateWarnMsgDisplay(MSG_ESTOP_PRESS);		
			}
			else if(LDB(R_INTERLOCK)){//��ȫ�����γ�
				updateWarnMsgDisplay(MSG_INTERLOCK_UNPLUG);
			}
			else if(LDB(R_FIBER_PROBE)){//���˰γ�
				updateWarnMsgDisplay(MSG_FIBER_UNPLUG);
			}
			else if(LDB(R_FOOTSWITCH_PLUG)){//��̤�γ�
				updateWarnMsgDisplay(MSG_FOOTSWITCH_UNPLUG);
			}
			else if(LDB(R_RFID_PASS)){//����ID��ƥ��
				updateWarnMsgDisplay(MSG_FIBER_MISSMATE);
			}
			standbyKeyTouchEnable(false);//��ֹStandby����
			NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_3;//������������ģʽ
			NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
			SSET(SPCOIL_BEEM_ENABLE);//��������
		}
		if(LD(R_STANDBY_KEY_ENTER_OPTION_DOWN)){//���OPTION
			RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
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
			RRES(R_STANDBY_KEY_ENTER_OPTION_DOWN);
		}else 
		if(LD(R_STANDBY_KEY_ENTER_SCHEME_DOWN)){//���SCHEME Ĭ����ʾ��һҳ
			RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
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
			RRES(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
		}else
		if(LD(R_STANDBY_KEY_STNADBY_DOWN)){//���READY
			LaserTimer_Select = (int8_t)NVRAM0[EM_LASER_SELECT];
			LaserTimer_Mode = (int8_t)NVRAM0[EM_LASER_PULSE_MODE];
			printf("%s,%d,%s:set laser channel=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Select);
			printf("%s,%d,%s:set laser mode=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Mode);
			LaserTimer_TMate 				= NVRAM0[EM_LASER_MP_POSWIDTH];//�������������� 10mS
			LaserTimer_TOvertime 		= NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH];//������������ 25mS	
			printf("%s,%d,%s:set LaserTimer_TMate=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TMate);
			printf("%s,%d,%s:set LaserTimer_TOvertime=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TOvertime);
			//У���������
			NVRAM0[SPREG_DAC_0] = fitLaserToCode(0, NVRAM0[EM_LASER_POWER_CH0], &deviceConfig);
			NVRAM0[SPREG_DAC_1] = 0x0;
			NVRAM0[SPREG_DAC_2] = 0x0;
			NVRAM0[SPREG_DAC_3] = 0x0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();//���¹�������
			//��ָʾ����
			SSET(SPCOIL_AIM_ENABEL);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;	
			RRES(R_STANDBY_KEY_STNADBY_DOWN);
			//ҳ���л�
			readyPageTouchEnable(false);
			readyKeyValue(true);
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//�л�����ҳ��
			SetScreen(NVRAM0[EM_DC_PAGE]);
			standbyKeyValue(false);
		}
		if(LD(R_STANDBY_KEY_SCHEME_SAVE_DOWN)){//save down	
			//��ֹ��Ļ����
			standbyPageTouchEnable(false);
			standbyKeyTouchEnable(false);
			saveScheme();//EM->FD
			FDSAV_ONE(NVRAM0[DM_SCHEME_NUM]);//FDRAM->EPROM
			standbyPageTouchEnable(true);
			standbyKeyTouchEnable(true);
			RRES(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_PARA){//�ȴ�������
		//��ռ�ʱ��
		T100MS(T100MS_READY_BEEM_DELAY, true, CONFIG_STANDBY_BEEM_DELAY_TIME);//������ʱ����ʱ2000mS �򿪼�ʱ��		
		if(LD(T_100MS_START * 16 + T100MS_READY_BEEM_DELAY) && LD(R_FOOTSWITCH_PRESS)){
			RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
			T100MS(T100MS_READY_BEEM_DELAY, false, 3);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_DONE;
		}
		else{
			if(LDP(R_FOOTSWITCH_PRESS)){
				NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_3;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SSET(SPCOIL_BEEM_ENABLE);
				printf("%s,%d,%s:set Beem mode:%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_BEEM_MODE]);
				printf("%s,%d,%s:set Beem freq:%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_BEEM_FREQ]);
				printf("%s,%d,%s:set Beem on\n", __FILE__, __LINE__, __func__);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;
			}
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_DONE){//����������ϲ�ֹͣ������
		printf("%s,%d,%s:set Beem off\n", __FILE__, __LINE__, __func__);
		readyPageTouchEnable(true);
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;	
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_WAIT_TRIGGER){//�ȴ���������	
		if(LD(R_ENGINEER_MODE)){//����ģʽ��ʾ������Ϣ	
			if(LDP(SPCOIL_PS1000MS)){		
				updateStandbyDebugInfo();
			}
		}
		if(LD(R_FAULT)){//Ready״̬��⵽����
			EDLAR();//ֹͣ����
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();
			RRES(SPCOIL_AIM_ENABEL);
			//�л���STANBYҳ��
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;//�л�����ҳ�� CW 
			}
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;//�л�����ҳ�� MP
			}
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			standbyKeyTouchEnable(false);
			standbyKeyValue(false);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			printf("%s,%d,%s:detect fault,goto FSMSTEP_STANDBY!\n", __FILE__, __LINE__, __func__);
			printf("%s,%d,%s:clear all dac!\n", __FILE__, __LINE__, __func__);
		}
		else if(LD(R_STANDBY_KEY_STNADBY_UP)){//�ص��ȴ�״̬
			EDLAR();//ֹͣ����
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();
			RRES(SPCOIL_AIM_ENABEL);
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;//�л�����ҳ�� CW 
			}
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;//�л�����ҳ�� MP
			}
			SetScreen(NVRAM0[EM_DC_PAGE]);//�л�����ҳ��
			standbyKeyValue(false);
			RRES(R_STANDBY_KEY_STNADBY_UP);
			updateWarnMsgDisplay(MSG_NO_ERROR);//��ʾ������Ϣ
			printf("%s,%d,%s:set DAC0 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_0]);
			printf("%s,%d,%s:set DAC1 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_1]);
			printf("%s,%d,%s:set DAC2 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_2]);
			printf("%s,%d,%s:set DAC3 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_3]);
			printf("%s,%d,%s:HMI_OPERA_STEP=%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_HMI_OPERA_STEP]);
			printf("%s,%d,%s:Return Standby!\n", __FILE__, __LINE__, __func__);
		}
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//�����ش���
			if(LDP(R_FOOTSWITCH_PRESS)){//���伤��
				readyPageTouchEnable(false);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				SSET(SPCOIL_BEEM_ENABLE);//��������
			}
		}
		else{//��ƽ����
			if(LD(R_FOOTSWITCH_PRESS)){//���伤��	
				readyPageTouchEnable(false);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				SSET(SPCOIL_BEEM_ENABLE);//��������
			}	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_EMITING){//��������READYҳ��
		if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){//ÿ��1Sˢ���ۼ�ʱ�������
			LaserRelease_TotalEnergy0 = (fp32_t)(LaserRelease_TotalTime0 * (fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10.0F);//���㷢������
			if(LaserRelease_TotalEnergy0 > 99999){
				LaserRelease_TotalEnergy0 = 99999;
			}
			updateReleaseTimeEnergy(false);//�����ۼƷ���ʱ�������
		}
		if(LD(R_ENGINEER_MODE)){//����ģʽ��ʾ������Ϣ	
			if(LDP(SPCOIL_PS1000MS)){		
				updateStandbyDebugInfo();
			}
		}		
		if(LD(R_FAULT)){//���ֹ���
			EDLAR();
			NVRAM0[SPREG_DAC_0] = 0;
			UPDAC0();
			RRES(SPCOIL_AIM_ENABEL);//�ر�ָʾ��
			RRES(SPCOIL_BEEM_ENABLE);//�رշ�����		
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			standbyKeyTouchEnable(false);
			standbyPageTouchEnable(true);
			standbyKeyValue(false);
			updateWarnMsgDisplay(MSG_NO_ERROR);
		}
		else if(LD(R_STANDBY_KEY_STNADBY_UP)){//�ص��ȴ�״̬
			EDLAR();//ֹͣ����
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();
			RRES(SPCOIL_AIM_ENABEL);
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;//�л�����ҳ�� CW 
			}
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;//�л�����ҳ�� MP
			}
			readyPageTouchEnable(true);
			SetScreen(NVRAM0[EM_DC_PAGE]);//�л�����ҳ��
			standbyKeyValue(false);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			RRES(R_STANDBY_KEY_STNADBY_UP);
			updateWarnMsgDisplay(MSG_NO_ERROR);//��ʾ������Ϣ
			printf("%s,%d,%s:set DAC0 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_0]);
			printf("%s,%d,%s:set DAC1 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_1]);
			printf("%s,%d,%s:set DAC2 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_2]);
			printf("%s,%d,%s:set DAC3 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_3]);
			printf("%s,%d,%s:HMI_OPERA_STEP=%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_HMI_OPERA_STEP]);
			printf("%s,%d,%s:Return Standby!\n", __FILE__, __LINE__, __func__);				
		}
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//�����ش���
			if(LDP(R_FOOTSWITCH_PRESS)){//�رռ���
				EDLAR();
				RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				readyPageTouchEnable(true);
				printf("%s,%d,%s:hand switch mode,footswitch press,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		else{
			if(LDB(R_FOOTSWITCH_PRESS)){//�رռ���
				EDLAR(); 
				RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				readyPageTouchEnable(true);
				printf("%s,%d,%s:foot switch mode,footswitch unpress,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_ERROR){//Ready��⵽��̤����
		if(LDB(R_FOOTSWITCH_PRESS)){//��⵽��̤״̬�ָ�����
			RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
			standbyKeyValue(false);
			standbyKeyTouchEnable(true);
			standbyPageTouchEnable(true);
			updateWarnMsgDisplay(MSG_NO_ERROR);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
		}
		else{
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_ERROR;
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_OPTION){//ѡ�����
		if(LD(R_OPTION_KEY_ENTER_INFORMATION_DOWN)){		
			updateInformationDisplay();		
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_INFORMATION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_INFORMATION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_OPTION_KEY_ENTER_INFORMATION_DOWN);
		}
		if(LD(R_OPTION_KEY_ENTER_OK_DOWN)){//ȷ��
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			updateStandbyDisplay();
			RRES(R_OPTION_KEY_ENTER_OK_DOWN);
		}
		if(LD(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN)){//�������״̬
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_DIAGNOSIS;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			updateDiognosisTextBox();//�����ı�����ֵ
			RRES(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_INFORMATION){//��Ϣ����
		if(LD(R_INFORMATION_KEY_OK_DOWN)){
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_OPTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_INFORMATION_KEY_OK_DOWN);	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_SCHEME_0){//���������һҳ
		if(LD(R_SCHEME_KEY_OK_DOWN)){//ȷ��
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];//ѡ��������Ч
			loadScheme();
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_OK_DOWN);
		}
		else if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//ȡ��
			loadScheme();//FD->EM
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		else if(LD(R_SCHEME_KEY_RENAME_DOWN)){//����
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//��EM_SCHEME_NUM_TMPָ������Ƹ���RENAME�����
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_RENAME_DOWN);
		}
		else if(LD(R_SCHEME_KEY_NEXT_SCHEME)){//��һҳ->�ڶ�ҳ
			updateScheme_1_Display();//���µڶ�ҳ
			seletcSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);//����ѡ����
			updateSchemeInfo(NVRAM0[EM_SCHEME_NUM_TMP]);//����ѡ����ϸ��Ϣ
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_1;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_1;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_NEXT_SCHEME);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_SCHEME_1){//��������ڶ�ҳ
		if(LD(R_SCHEME_KEY_OK_DOWN)){//ȷ��
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];
			loadScheme();
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_OK_DOWN);
		}
		else if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//ȡ��
			loadFdram();//NVRAM->FD
			loadScheme();//FD->EM
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		else if(LD(R_SCHEME_KEY_RENAME_DOWN)){//����
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//��EM_SCHEME_NUM_TMPָ������Ƹ���RENAME�����
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_RENAME_DOWN);
		}
		else if(LD(R_SCHEME_KEY_LAST_SCHEME)){//�ڶ�ҳ->��һҳ
			updateScheme_0_Display();//���µ�һҳ
			seletcSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);//����ѡ����
			updateSchemeInfo(NVRAM0[EM_SCHEME_NUM_TMP]);//����ѡ����ϸ��Ϣ
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_0;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_0;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_LAST_SCHEME);
		}		
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_RENAME){//��������
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
			RRES(R_RENAME_TEXTDISPLAY_READ_DONE);	
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
			RRES(R_RENAME_KEY_EXIT_DOWN);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_DIAGNOSIS){//��Ͻ���
		if(LD(R_DIAGNOSIS_OK_DOWN)){//����Option
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_OPTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_DIAGNOSIS_OK_DOWN);
		}
		else if(LD(R_CLEAR_EPROM)){//
			__set_PRIMASK(0);//�ر��ж�
			clearNvram();//���NVRAM
			clearFdram();//���FDRAM
			resetGddcHmi();
			delayMs(4000);//�ȴ�4��
			REBOOT();	
		}
		else if(LD(R_SAVE_EPROM)){//�������Ƶ�EPROM
			__set_PRIMASK(0);//�ر��ж�
			saveNvram();//����NVRAM
			saveFdram();//����FDRAM
			saveDeviceConfig();//��������
			resetGddcHmi();
			delayMs(4000);//�ȴ�4��
			REBOOT();	
		}
		else if(LDP(SPCOIL_PS1000MS)){
			updateDiognosisInfo();
		}
		return;
	}
/*****************************************************************************/
}

//��Ϣ��������
//msg ��������Ϣ
//size ��Ϣ����
static void ProcessMessage( PCTRL_MSG msg, uint16_t size ){
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


static void NotifyScreen(uint16_t screen_id){
    //TODO: ����û�����

}

//���������¼���Ӧ
//press 1���´�������3�ɿ�������;x x����;y y����
static void NotifyTouchXY(uint8_t press,uint16_t x,uint16_t y){
    //TODO: ����û�����
}


/*! 
*  \brief  ��������
*/ 
static void UpdateUI(void){
	uint8_t err;
	err = err;
}


                                                                          
/*!                                                                              
*  \brief  �������ؼ�֪ͨ                                                       
*  \details  ���������ı�(�����GetControlValue)ʱ��ִ�д˺���                  
*  \param screen_id ����ID                                                      
*  \param control_id �ؼ�ID                                                     
*  \param value ֵ                                                              
*/                                                                              
static void NotifySlider(uint16_t screen_id, uint16_t control_id, uint32_t value){                                                                                                                                  

}

/*! 
*  \brief  �Ǳ�ؼ�֪ͨ
*  \details  ����GetControlValueʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param value ֵ
*/
static void NotifyMeter(uint16_t screen_id, uint16_t control_id, uint32_t value){
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
static void NotifyMenu(uint16_t screen_id, uint16_t control_id, uint8_t item, uint8_t state){

}

/*! 
*  \brief  ѡ��ؼ�֪ͨ
*  \details  ��ѡ��ؼ��仯ʱ��ִ�д˺���
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*  \param item ��ǰѡ��
*/
static void NotifySelector(uint16_t screen_id, uint16_t control_id, uint8_t  item){


}

/*! 
*  \brief  ��ʱ����ʱ֪ͨ����
*  \param screen_id ����ID
*  \param control_id �ؼ�ID
*/
static void NotifyTimer(uint16_t screen_id, uint16_t control_id){
}

/*! 
*  \brief  ��ȡ�û�FLASH״̬����
*  \param status 0ʧ�ܣ�1�ɹ�
*  \param _data ��������
*  \param length ���ݳ���
*/
static void NotifyReadFlash(uint8_t status,uint8_t *_data,uint16_t length){
    //TODO: ����û�����
}

/*! 
*  \brief  д�û�FLASH״̬����
*  \param status 0ʧ�ܣ�1�ɹ�
*/
static void NotifyWriteFlash(uint8_t status){
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




