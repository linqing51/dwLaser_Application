#include "dcHmiApp.h"
/*****************************************************************************/
uint8_t hmiCmdBuffer[CMD_MAX_SIZE];//ָ���
uint16_t hmiCmdSize;//�ѻ����ָ����
static uint8_t MsgId = 0xFF;//��ǰ��ʾ����ϢID
static uint8_t StandbyKeyEnable = 0xFF;//����ģʽ
static void UpdateUI(void);
/*****************************************************************************/
void loadDeviceLogInfo(void){//��EPROM�����¼�ļ�
	uint16_t crc1, crc2;
	HAL_StatusTypeDef ret1, ret2;
	ret1 = epromRead(CONFIG_EPROM_LOGINFO_START, (uint8_t*)&deviceLogInfo, sizeof(deviceLogInfo));//��EPROM�����豸����
	crc16Clear();
	crc1 = crc16Calculate((uint8_t*)&deviceLogInfo, sizeof(deviceLogInfo));//CRC16 ��������
	ret2 = epromRead((CONFIG_EPROM_LOGINFO_START + 512 - 2), (uint8_t*)&crc2, 2);//��EPROM����LOG CRC
	if(ret1 != HAL_OK || ret2 != HAL_OK || crc1 != crc2){//У���벻ͬʹ��Ĭ������
		printf("dcHmiApp->loadDeviceLogInfo:Load device log fail!!!\n");
		printf("dcHmiApp->loadDeviceLogInfo:Reset device log!\n");
		memset((uint8_t*)&deviceLogInfo, 0x0, sizeof(deviceLogInfo));
		saveDeviceLogInfo();
	}
	else{
		printf("dcHmiApp->loadDeviceLogInfo:Load device log ok!\n");
	}
}
void loadDeviceConfig(void){//��EPROM���������ļ�
	uint16_t crc1, crc2;
	uint16_t configSize;
	HAL_StatusTypeDef ret1, ret2;
	configSize = sizeof(deviceConfig);
	ret1 = epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, configSize);//��EPROM�����豸����
	crc16Clear();
	crc1 = crc16Calculate((uint8_t*)&deviceConfig, configSize);//CRC16 ��������
	ret2 = epromRead((CONFIG_EPROM_CONFIG_START + 512 - 2), (uint8_t*)&crc2, 2);//��EPROM�����豸����
	if(ret1 != HAL_OK || ret2 != HAL_OK || crc1 != crc2){//У���벻ͬʹ��Ĭ������
#if CONFIG_DEBUG_APP == 1
		printf("dcHmiApp->loadDeviceConfig:Load device config fail!!!\n");
		printf("dcHmiApp->loadDeviceConfig:Using default device config!\n");
#endif		
		//����3�ζ���ʽ���Y = A*X^3 + B*X^2 + C*X + D
		sprintf(deviceConfig.serialNumber,"1234-5678-ABCDEF");
		sprintf(deviceConfig.dateOfManufacture, "1970-01-01");
		
		deviceConfig.laserNotesB1[0] = 198.5266667F;
		deviceConfig.laserNotesB1[1] = 0;
		deviceConfig.laserNotesB1[2] = 0;
		deviceConfig.laserNotesB1[3] = 0;
		deviceConfig.laserNotesB1[4] = 0;
	
		deviceConfig.laserNotesB2[0] = 0;
		deviceConfig.laserNotesB2[1] = 0;
		deviceConfig.laserNotesB2[2] = 0;
		deviceConfig.laserNotesB2[3] = 0;
		
		deviceConfig.laserNotesB2[4] = 0;
		
		deviceConfig.laserNotesB3[0] = 0;
		deviceConfig.laserNotesB3[1] = 0;
		deviceConfig.laserNotesB3[2] = 0;
		deviceConfig.laserNotesB3[3] = 0;
		deviceConfig.laserNotesB3[4] = 0;
		
		deviceConfig.laserNotesIntercept[0] = 5977.308956F;
		deviceConfig.laserNotesIntercept[1] = 0;
		deviceConfig.laserNotesIntercept[2] = 0;
		deviceConfig.laserNotesIntercept[3] = 0;
		deviceConfig.laserNotesIntercept[4] = 0;
		
		saveDeviceConfig();
	}
	else{
		printf("dcHmiApp->loadDeviceConfig:Load device config ok!\n");
	}
}
void saveDeviceConfig(void){//������д��EPROM
	uint16_t crc;
	HAL_StatusTypeDef ret;
	ret = epromWrite(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//д��EPROM
	if(ret != HAL_OK){
		printf("dcHmiApp->saveDeviceConfig:Save device config to eprom fail!!!\n");
	}
	else{
		printf("dcHmiApp->saveDeviceConfig:Save device config to eprom ok!\n");
	}
	crc16Clear();
	crc = crc16Calculate((uint8_t*)&deviceConfig, sizeof(deviceConfig));//CRC16 ��������
	ret = epromWrite((CONFIG_EPROM_CONFIG_START + 512 - 2), (uint8_t*)&crc, 2);//д��У��ֵ
	if(ret != HAL_OK){
		printf("dcHmiApp->saveDeviceConfig:Save device config crc to eprom fail!!!\n");
	}
	else{
		printf("dcHmiApp->saveDeviceConfig:Save device config crc to eprom ok!\n");
	}
}
void saveDeviceLogInfo(void){//����¼д��EPROM
	uint16_t crc;
	HAL_StatusTypeDef ret;
	ret = epromWrite(CONFIG_EPROM_LOGINFO_START, (uint8_t*)&deviceLogInfo, sizeof(deviceLogInfo));//д��EPROM
	if(ret != HAL_OK){
		printf("dcHmiApp->saveDeviceLogInfo:Save device log to eprom fail!!!\n");
	}
	crc16Clear();
	crc = crc16Calculate((uint8_t*)&deviceLogInfo, sizeof(deviceLogInfo));//CRC16 ��������
	ret = epromWrite((CONFIG_EPROM_LOGINFO_START + 512 - 2), (uint8_t*)&crc, 2);//д��У��ֵ
	if(ret != HAL_OK){
		printf("dcHmiApp->saveDeviceLogInfo:Save device log crc to eprom fail!!!\n");
	}
}
void deviceLogInfoLoop(void){//����¼
	uint8_t upReq;
	upReq = 0;
	if(NVRAM0[EM_LASER_TEMP] > deviceLogInfo.laserMaxTemper){//��¼����������¶�
		deviceLogInfo.laserMaxTemper = NVRAM0[EM_LASER_TEMP];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_TEMP] < deviceLogInfo.laserMinTemper){//��¼����������¶�
		deviceLogInfo.laserMinTemper = NVRAM0[EM_LASER_TEMP];
		upReq |= 1;
	}
	if(NVRAM0[EM_MCU_TEMP] > deviceLogInfo.mucMaxTemper){//��¼����������¶�
		deviceLogInfo.mucMaxTemper = NVRAM0[EM_MCU_TEMP];
		upReq |= 1;
	}
	if(NVRAM0[EM_MCU_TEMP] < deviceLogInfo.mucMinTemper){//��¼����������¶�
		deviceLogInfo.mucMinTemper = NVRAM0[EM_MCU_TEMP];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH0] > deviceLogInfo.laserMaxCurrent[0]){//��¼������ ͨ��0
		deviceLogInfo.laserMaxCurrent[0] = NVRAM0[EM_LASER_CURRENT_CH0];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH1] > deviceLogInfo.laserMaxCurrent[1]){//��¼������ ͨ��1
		deviceLogInfo.laserMaxCurrent[1] = NVRAM0[EM_LASER_CURRENT_CH1];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH2] > deviceLogInfo.laserMaxCurrent[2]){//��¼������ ͨ��2
		deviceLogInfo.laserMaxCurrent[2] = NVRAM0[EM_LASER_CURRENT_CH2];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH3] > deviceLogInfo.laserMaxCurrent[3]){//��¼������ ͨ��3
		deviceLogInfo.laserMaxCurrent[3] = NVRAM0[EM_LASER_CURRENT_CH3];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH4] > deviceLogInfo.laserMaxCurrent[4]){//��¼������ ͨ��4
		deviceLogInfo.laserMaxCurrent[4] = NVRAM0[EM_LASER_CURRENT_CH4];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_PHOTODIODE] > deviceLogInfo.laserMaxPhotoDiode){//��¼�����
		deviceLogInfo.laserMaxPhotoDiode = NVRAM0[EM_LASER_PHOTODIODE];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH0] > CONFIG_LASER_THRESHOLD_CH0){//ͨ��0����������ֵ���ⷢ��
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[0] ++;
		}
	}
	if(NVRAM0[EM_LASER_CURRENT_CH1] > CONFIG_LASER_THRESHOLD_CH1){//ͨ��1����������ֵ���ⷢ��
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[1] ++;
		}
	}
	if(NVRAM0[EM_LASER_CURRENT_CH2] > CONFIG_LASER_THRESHOLD_CH2){//ͨ��2����������ֵ���ⷢ��
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[2] ++;
		}
	}
	if(NVRAM0[EM_LASER_CURRENT_CH3] > CONFIG_LASER_THRESHOLD_CH3){//ͨ��3����������ֵ���ⷢ��
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[3] ++;
		}
	}
	if(NVRAM0[EM_LASER_CURRENT_CH4] > CONFIG_LASER_THRESHOLD_CH4){//ͨ��4����������ֵ���ⷢ��
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[4] ++;
		}
	}
	if(LDP(SPCOIL_PS1MINS)){//ÿ���Ӽ�¼Log
		deviceLogInfo.runTime ++;
	}
	if(upReq){
		saveDeviceLogInfo();
		upReq = 0;
	}
}
void optionKeyEnable(uint8_t enable){//ѡ����水������
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_TONE, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_AIM_BRG_ADD, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_AIM_BRG_DEC, enable);
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
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_ENTER_CORRECTION, enable);
	BatchEnd();
	delayMs(5);
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetEnable(GDDC_PAGE_OPTION_PROGRESS_AIM_BRG, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, enable);
	BatchEnd();
	delayMs(5);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_RESTORE, enable);
}
void standbyDebugInfoVisiable(int8_t enable){//Standby������Ϣ�ɼ�
	SetControlVisiable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	
	SetControlVisiable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_HAND_LAUNCH, enable);
	
}
void updateStandbyDebugInfo(void){//����Standby������Ϣ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "TLAS:%05d, TMCU:%05d,LD:%05d, PD:%05d", NVRAM0[EM_LASER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[EM_LASER_CURRENT_CH0], NVRAM0[EM_LASER_PHOTODIODE]);
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_SP:{
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_MP:{
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_GP:{
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_SIGNAL:{
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_DERMA:{
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		default:{
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
	}
}
void updateDiognosisInfo(void){//���������Ϣ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "ADC0:%05d,ADC1:%05d,ADC2:%05d,ADC3:%05d", NVRAM0[SPREG_ADC_0], NVRAM0[SPREG_ADC_1], NVRAM0[SPREG_ADC_2], NVRAM0[SPREG_ADC_3]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO0, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "ADC4:%05d,ADC5:%05d,ADC6:%05d,ADC7:%05d", NVRAM0[SPREG_ADC_4], NVRAM0[SPREG_ADC_5], NVRAM0[SPREG_ADC_6], NVRAM0[SPREG_ADC_7]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO1, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "DAC0:%05d,DAC1:%05d,DAC2:%05d,DAC3:%05d", NVRAM0[SPREG_DAC_0], NVRAM0[SPREG_DAC_1], NVRAM0[SPREG_DAC_2], NVRAM0[SPREG_DAC_3]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO2, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "DAC4:%05d,DAC5:%05d,DAC6:%05d,DAC7:%05d", NVRAM0[SPREG_DAC_4], NVRAM0[SPREG_DAC_5], NVRAM0[SPREG_DAC_6], NVRAM0[SPREG_DAC_7]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO3, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "NFC VER:%05d, PLATFORM VER:%05d", NVRAM0[SPREG_DK25L_VER], NVRAM0[SPREG_IDENTITY]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO4, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "FS NC:%1d, FS NO:%1d, ES:%d, IL:%1d, FP:%1d", LD(X_FOOTSWITCH_NC),  LD(X_FOOTSWITCH_NO), LD(X_ESTOP), LD(X_INTERLOCK), LD(X_FIBER_PROBE));
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO5, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "FAN:%1d,TEC:%1d,TLAS:%05d,TMCU:%05d", LD(Y_FAN_LD),  LD(Y_TEC),NVRAM0[EM_LASER_TEMP], NVRAM0[EM_MCU_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO6, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "PowerUp Cycle:%d,RunTime:%d",deviceLogInfo.powerUpCycle, deviceLogInfo.runTime);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO7, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "Max Laser Temper:%d,Max Mcu Temper:%d", deviceLogInfo.laserMaxTemper, deviceLogInfo.mucMaxTemper);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO8, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "Max Laser Current:%d,Max Laser Power:%d", deviceLogInfo.laserMaxCurrent[0], deviceLogInfo.laserMaxPhotoDiode);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO9, (uint8_t*)dispBuf);
}
void updateEnergyDensity(void){//���������ܶ���ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	fp32_t ftemp;
	ftemp = (fp32_t)NVRAM0[EM_TOTAL_POWER];
	switch(NVRAM0[EM_LASER_DERMA_SPOT_SIZE]){	
		case DERMA_SPOT_SIZE_0MM5:{
			sprintf(dispBuf, "%d J/cM^2", (int16_t)(ftemp / 0.019625F));
			break;
		}
		case DERMA_SPOT_SIZE_1MM0:{
			sprintf(dispBuf, "%d J/cM^2", (int16_t)(ftemp / 0.0785F));
			break;
		}
		case DERMA_SPOT_SIZE_2MM0:{
			sprintf(dispBuf, "%d j/cM^2", (int16_t)(ftemp / 0.314926F));
			break;
		}
		case DERMA_SPOT_SIZE_3MM0:{
			sprintf(dispBuf, "%d j/cM^2", (int16_t)(ftemp / 0.706853F));
			break;
		}
		default:{
			sprintf(dispBuf, "----- J/cM^2");
			break;
		}
	}
	SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_TEXTDISPLAY_ENERGY_DENSITY, (uint8_t*)dispBuf);
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
	
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_TPYE, (uint8_t*)INFO_MSG_TYPE[NVRAM0[DM_LANGUAGE]]);	
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_SN, (uint8_t*)INFO_MSG_SN[NVRAM0[DM_LANGUAGE]]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_LASER_WAVELENGTH, (uint8_t*)INFO_MSG_WAVELENGTH[NVRAM0[DM_LANGUAGE]]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_MAX_LASER_POWER, (uint8_t*)INFO_MSG_LASER_POWER[NVRAM0[DM_LANGUAGE]]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_VERSION, (uint8_t*)INFO_MSG_VERSION[NVRAM0[DM_LANGUAGE]]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_MANUFACTURE_DATE, (uint8_t*)INFO_MSG_MANUFACTURE_DATE[NVRAM0[DM_LANGUAGE]]);			
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "UUID:%08X%08X%08X", UniqueId[0], UniqueId[1], UniqueId[2]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_UUID, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "BuildTime:%s:%s\n", __DATE__, __TIME__);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXTDISPLAY_BUILDTIME, (uint8_t*)dispBuf);	
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
void clearReleaseTimeEnergy(void){//�������ʱ����������ʾ
	LaserRelease_TotalTime0 = 0;
	LaserRelease_TotalTime1 = -1;
	LaserRelease_TotalEnergy0 = 0;
	LaserRelease_TotalEnergy1 = -1;
	updateReleaseTimeEnergy();
}
void updateReleaseTimeEnergy(void){//ˢ�·���ʱ������
	if(LaserRelease_TotalTime0 != LaserRelease_TotalTime1){
		SetTextInt32(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_RELEASE_TIME , LaserRelease_TotalTime0, 1, 0);
		LaserRelease_TotalTime1 =LaserRelease_TotalTime0;
	}
	if(LaserRelease_TotalEnergy0 != LaserRelease_TotalEnergy1){
		SetTextInt32(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy0, 1, 0);
		SetTextInt32(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_ENERGY , LaserRelease_TotalEnergy0, 1, 0);
		LaserRelease_TotalEnergy1 = LaserRelease_TotalEnergy0;
	}
}
void updateWarnMsgDisplay(uint8_t id){//���¾�����ʾ��
	const char *pstr;
	if(MsgId != id){
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
		SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, (uint8_t*)pstr);
		SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, (uint8_t*)pstr);
		SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, (uint8_t*)pstr);
		SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, (uint8_t*)pstr);
		SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, (uint8_t*)pstr);
		SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, (uint8_t*)pstr);
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
			sprintf(dispBuf2, "OnTime:%dmS", posWidth);
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
			sprintf(dispBuf2, "Energy Interval:%dJ", energyInterval);
			break;
		}
		default:break;
	}
#if CONFIG_USING_SINGLE_WAVE == 1
	sprintf(dispBuf1, "980nM Power:%3.1fW", ((fp32_t)power0 / 10.0F));
#endif
#if CONFIG_USING_DUAL_WAVE == 1
	sprintf(dispBuf1, "1470nM Power:%3.1fW;980nM Power:%3.1fW", ((fp32_t)power0 / 10.0F), ((fp32_t)power1 / 10.0F));
#endif
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
void standbyTouchEnable(int8_t enable){//ʹ��STANDBY���津��
	uint16_t screen_id;
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			screen_id = GDDC_PAGE_STANDBY_CW;
			break;
		}
		case LASER_MODE_SP:{
			screen_id = GDDC_PAGE_STANDBY_SP;
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_SP_KEY_POSWIDTH_ADD, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_SP_KEY_POSWIDTH_DEC, enable);		
			break;
		}
		case LASER_MODE_MP:{
			screen_id = GDDC_PAGE_STANDBY_MP;
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_MP_KEY_POSWIDTH_ADD, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_MP_KEY_POSWIDTH_DEC, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_MP_KEY_NEGWIDTH_ADD, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_MP_KEY_NEGWIDTH_DEC, enable);			
			break;
		}
		case LASER_MODE_GP:{
			screen_id = GDDC_PAGE_STANDBY_GP;
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_GP_KEY_POSWIDTH_ADD, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_GP_KEY_POSWIDTH_DEC, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_GP_KEY_NEGWIDTH_ADD, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_GP_KEY_NEGWIDTH_DEC, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_GP_KEY_TIMES_ADD, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_GP_KEY_TIMES_DEC, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_GP_KEY_GROUP_OFF_ADD, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_GP_KEY_GROUP_OFF_DEC, enable);				
			break;
		}
		case LASER_MODE_DERMA:{
			screen_id = GDDC_PAGE_STANDBY_DERMA;
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_DERMA_KEY_POSWIDTH_ADD, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_DERMA_KEY_POSWIDTH_DEC, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_DERMA_KEY_NEGWIDTH_ADD, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_DERMA_KEY_NEGWIDTH_DEC, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_0MM5, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_1MM0, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_2MM0, enable);		
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_DERMA_KEY_SPOT_3MM0, enable);		
			break;
		}
		case LASER_MODE_SIGNAL:{
			screen_id = GDDC_PAGE_STANDBY_SIGNAL;
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_SIGNAL_KEY_ENERGY_INTERVAL_ADD, enable);	
			SetControlEnable(screen_id, GDDC_PAGE_STANDBY_SIGNAL_KEY_ENERGY_INTERVAL_DEC, enable);					
			break;
		}
		default:break;
	}
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_POWER_CH0_ADD, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_POWER_CH0_DEC, enable);
#if CONFIG_USING_DUAL_WAVE == 1
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_POWER_CH1_ADD, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_POWER_CH1_DEC, enable);
#endif
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_MODE_GP, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_MODE_SP, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_MODE_SIGNAL, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_MODE_DERMA, enable);		
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);		
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);	
#if CONFIG_USING_DUAL_WAVE == 1
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_SELECT_CH0, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_SELECT_CH1, enable);
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_SELECT_BOTH, enable);
#endif
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_KEY_RESET, enable);	
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_PROGRESS_CH0, enable);	
#if CONFIG_USING_DUAL_WAVE == 1
	SetControlEnable(screen_id, GDDC_PAGE_STANDBY_PROGRESS_CH1, enable);
#endif				
}
void updatePowerDisplay(int16_t ch, int16_t mode){//���¹�����ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(mode){
		case LASER_MODE_CW:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1					
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif					
					break;
				}
				default:break;
			}
		}
		case LASER_MODE_SP:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
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
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1					
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
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
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
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
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1					
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif					
					break;
				}
				default:break;
			}
			break;		
		}
		case LASER_MODE_SIGNAL:{
			switch(ch){
				case LASER_SELECT_CH0:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_CH1:{
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
#endif					
					break;
				}
				case LASER_SELECT_ALL:{
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH0, (uint8_t*)dispBuf);
#if CONFIG_USING_DUAL_WAVE == 1
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_POWER_CH1, (uint8_t*)dispBuf);
					sprintf(dispBuf, "%3.1f", ((fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10));
					SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
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
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	fp32_t freq, averagePower, dutyCycle;
	switch(mode){
		case LASER_MODE_CW:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_DUTYCYCLE, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_FREQUENCY, (uint8_t*)dispBuf);			
#if CONFIG_USING_SINGLE_WAVE == 1
			averagePower = (fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
#endif
#if CONFIG_USING_DUAL_WAVE == 1
			averagePower = (fp32_t)(NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F;
#endif
			sprintf(dispBuf, "%3.1f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_AVERAGE_POWER, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_SP:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_DUTYCYCLE, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_FREQUENCY, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_AVERAGE_POWER, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_MP:{
			freq =1000.0F / (fp32_t)(NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH]);
			sprintf(dispBuf, "%4.1f", freq);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_FREQUENCY, (uint8_t*)dispBuf);
						
			dutyCycle = (fp32_t)NVRAM0[EM_LASER_MP_POSWIDTH] / (fp32_t)(NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH]);
			sprintf(dispBuf, "%4.1f", dutyCycle * 100.0F);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_DUTYCYCLE, (uint8_t*)dispBuf);
#if CONFIG_USING_SINGLE_WAVE == 1
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
#endif
#if 	CONFIG_USING_DUAL_WAVE == 1		
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F;
#endif
			sprintf(dispBuf, "%3.1f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_AVERAGE_POWER, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_GP:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_FREQUENCY, (uint8_t*)dispBuf);
			
			dutyCycle = ((fp32_t)NVRAM0[EM_LASER_GP_POSWIDTH] * NVRAM0[EM_LASER_GP_TIMES]) / ((fp32_t)(NVRAM0[EM_LASER_GP_POSWIDTH] + NVRAM0[EM_LASER_GP_NEGWIDTH]) * NVRAM0[EM_LASER_GP_TIMES] + NVRAM0[EM_LASER_GP_GROUP_OFF]);
			sprintf(dispBuf, "%4.1f", dutyCycle * 100.0F);
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_DUTYCYCLE, (uint8_t*)dispBuf);
#if CONFIG_USING_SINGLE_WAVE == 1
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
#endif			
#if CONFIG_USING_DUAL_WAVE == 1			
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F;
#endif
			sprintf(dispBuf, "%3.1f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_AVERAGE_POWER, (uint8_t*)dispBuf);		
			
			break;
		}
		case LASER_MODE_DERMA:{
			freq = 1000.0F / (fp32_t)(NVRAM0[EM_LASER_DERMA_POSWIDTH] + NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
			sprintf(dispBuf, "%4.1f", freq);
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_FREQUENCY, (uint8_t*)dispBuf);
			
			dutyCycle = (fp32_t)NVRAM0[EM_LASER_DERMA_POSWIDTH] / (fp32_t)(NVRAM0[EM_LASER_DERMA_POSWIDTH] + NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
			sprintf(dispBuf, "%4.1f", dutyCycle * 100.0F);
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DUTYCYCLE, (uint8_t*)dispBuf);
#if CONFIG_USING_SINGLE_WAVE == 1
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
#endif
#if CONFIG_USING_DUAL_WAVE == 1				
			averagePower = dutyCycle * (fp32_t)(NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F;
#endif
			sprintf(dispBuf, "%3.1f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_AVERAGE_POWER, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_SIGNAL:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_DUTYCYCLE, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_FREQUENCY, (uint8_t*)dispBuf);
#if CONFIG_USING_SINGLE_WAVE == 1			
			averagePower = (fp32_t)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
#endif
#if CONFIG_USING_DUAL_WAVE == 1			
			averagePower = (fp32_t)((NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1]) / 10.0F);
#endif
			sprintf(dispBuf, "%3.1f", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_AVERAGE_POWER, (uint8_t*)dispBuf);
			break;
		}		
		default:break;
	}
}
void updateStandbyDisplay(void){//���·�����ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
#if CONFIG_USING_SINGLE_WAVE == 1	
	NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
#endif
#if CONFIG_USING_DUAL_WAVE == 1		
	NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0] + NVRAM0[EM_LASER_POWER_CH1];
#endif
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
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
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
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)(&NVRAM0[EM_LASER_SCHEME_NAME]));		
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
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
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
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
			updatePosWidthDisplay(LASER_MODE_GP);
			updateNegWidthDisplay(LASER_MODE_GP);
			sprintf(dispBuf, "%d", NVRAM0[EM_LASER_GP_TIMES]);
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_TIMES, (uint8_t*)dispBuf);			
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
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)(&NVRAM0[EM_LASER_SCHEME_NAME]));					
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
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)(&NVRAM0[EM_LASER_SCHEME_NAME]));				
			memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
			sprintf(dispBuf, "%d J/cM", NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL]);
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_SIGNAL_TEXTDISPLAY_ENERGY_INTERVAL, (uint8_t*)dispBuf); 
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
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	switch(mode){
		case LASER_MODE_SP:{
			if(NVRAM0[EM_LASER_SP_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_SP_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_SP_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_SP_TEXTDISPLAY_POSWIDTH, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_MP:{
			if(NVRAM0[EM_LASER_MP_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_MP_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_MP_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_MP_TEXTDISPLAY_POSWIDTH, (uint8_t*)dispBuf);
			break;
		}			
		case LASER_MODE_GP:{
			if(NVRAM0[EM_LASER_GP_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_GP_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_GP_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_POSWIDTH, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_DERMA:{
			if(NVRAM0[EM_LASER_DERMA_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_DERMA_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_DERMA_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_TEXTDISPLAY_POSWIDTH, (uint8_t*)dispBuf);
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
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_MP_TEXTDISPLAY_NEGWIDTH, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_GP:{
			if(NVRAM0[EM_LASER_GP_NEGWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_GP_NEGWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_GP_NEGWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_NEGWIDTH, (uint8_t*)dispBuf);
			break;
		
		
		}
		case LASER_MODE_DERMA:{
			if(NVRAM0[EM_LASER_DERMA_NEGWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_DERMA_NEGWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_DERMA_TEXTDISPLAY_NEGWIDTH, (uint8_t*)dispBuf);
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
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	if(NVRAM0[EM_LASER_GP_GROUP_OFF] < 1000){
		sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_GP_GROUP_OFF]);
	}
	else{
		sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_GP_GROUP_OFF] / 1000));
	}
	SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_GROUP_OFF, (uint8_t*)dispBuf);
	updateExtralDisplay(LASER_MODE_GP);
}
void standbyKeyEnableSet(uint8_t ena){//����Standbyʹ��
	if(StandbyKeyEnable != ena){
		SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
		SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
		SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
		SetControlEnable(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
		SetControlEnable(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);
		SetControlEnable(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_STANDBY, ena);	
		StandbyKeyEnable = ena;
	}
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
#if CONFIG_USING_DCHMI_APP == 1
	loadDeviceConfig();//����deviceConfig
	loadDeviceLogInfo();
	deviceLogInfo.powerUpCycle ++;
	saveDeviceLogInfo();
	printf("%s,%d,%s:start hmi uart init......\n",__FILE__, __LINE__, __func__);
	hmiUartInit();
#endif
	NVRAM0[EM_HMI_OPERA_STEP] = 0;
	//���MUSIC VOLUME����ֵ�Ƿ�Ϲ�
#if CONFIG_USING_SINGLE_WAVE == 1
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM; i++){
		if(FDRAM[FD_LASER_SELECT + (i * 64)] != LASER_SELECT_CH0){//Ĭ������Ϊ������
			FDRAM[FD_LASER_SELECT + (i * 64)] = LASER_SELECT_CH0;
		}
	}
	if(NVRAM0[EM_LASER_SELECT] != LASER_SELECT_CH0){
		NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
	}
#endif
	
#if CONFIG_USING_DUAL_WAVE == 1
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM; i++){
		if(FDRAM[FD_LASER_SELECT + (i * 30)] != (LASER_SELECT_CH0 | LASER_SELECT_CH1)){//Ĭ������Ϊ������
			FDRAM[FD_LASER_SELECT + (i * 30)] = LASER_SELECT_CH0;
		}
	}
	if(NVRAM0[EM_LASER_SELECT] != (LASER_SELECT_CH0 | LASER_SELECT_CH1)){
		NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
	}
#endif	
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
	
	RRES(Y_TEC);
	SSET(Y_FAN_LD);
	SSET(Y_FAN_SP);
	SSET(R_RFID_PASS);
	//���α���
	RRES(R_LASER_TEMP_HIGH);							
	RRES(R_LASER_TEMP_LOW);								
	RRES(R_MCU_TEMP_HIGH);										
	RRES(R_MCU_TEMP_LOW);									
	RRES(R_FAULT);
	//��̤����
	SSET(R_FOOTSWITCH_PLUG);
#if CONFIG_USING_SINGLE_WAVE == 1
	NVRAM0[EM_LASER_POWER_CH1] = 0;
	NVRAM0[EM_LASER_POWER_CH2] = 0;
	NVRAM0[EM_LASER_POWER_CH3] = 0;
	NVRAM0[EM_LASER_POWER_CH4] = 0;
#endif

#if	CONFIG_USING_DUAL_WAVE == 1
	NVRAM0[EM_LASER_POWER_CH2] = 0;
	NVRAM0[EM_LASER_POWER_CH3] = 0;
	NVRAM0[EM_LASER_POWER_CH4] = 0;
#endif
}
static void temperatureLoop(void){//�¶���ѯ��ѯ
	int16_t temp;
	TNTC(EM_LASER_TEMP, SPREG_ADC_1);//CODEת��ΪNTC�����¶��¶�
	TENV(EM_MCU_TEMP, SPREG_ADC_8);//CODEת��ΪNTC�����¶��¶�
	//�ж϶�����0�Ƿ����
	if(NVRAM0[EM_LASER_TEMP] > CONFIG_APP_DIODE_HIGH_TEMP){
		SSET(R_LASER_TEMP_HIGH);
	}
	else{
		RRES(R_LASER_TEMP_HIGH);
	}
	if(NVRAM0[EM_LASER_TEMP] < CONFIG_APP_DIODE_LOW_TEMP){
		SSET(R_LASER_TEMP_LOW);
	}
	else{
		RRES(R_LASER_TEMP_LOW);
	}
	//�жϻ����Ƿ����
	if(NVRAM0[EM_MCU_TEMP] > CONFIG_APP_ENVI_HIGH_TEMP){
		SSET(R_MCU_TEMP_HIGH);
	}
	else{
		RRES(R_MCU_TEMP_HIGH);
	}
	//�¿�ִ�� ����ȴ����估����״̬�����¿�	
	if(LD(R_LASER_TEMP_HIGH) || LD(R_MCU_TEMP_HIGH)){//����״̬�������򿪷���
		SSET(Y_FAN_LD);
	}
	else{ 
		if((NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_WAIT_TRIGGER) ||
		   (NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_EMITING) ||
		   (NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_ERROR) ||
		   (NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_DIAGNOSIS) ||
		   (NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_CORRECTION)){//���⹤�����쳣״̬���ȿ�
			SSET(Y_FAN_LD);
			if(LD(SPCOIL_SPWM_OUT_0)){
				SSET(Y_TEC);
			}
			else{
				RRES(Y_TEC);
			}   
			if(NVRAM0[EM_LASER_TEMP] > (CONFIG_COOL_SET_TEMP + CONFIG_COOL_DIFF_TEMP)){
				SSET(Y_TEC);
			}
			if(NVRAM0[EM_LASER_TEMP] < (CONFIG_COOL_SET_TEMP - CONFIG_COOL_DIFF_TEMP)){
				RRES(Y_TEC);
			}
		}
		else{
			RRES(Y_TEC);
			if(LD(R_DISABLE_FAN_SPEED)){
				SSET(Y_FAN_LD);
			}
			else{
				RRES(Y_FAN_LD);
			}
		}
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
		if(LD(X_ESTOP)){
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
		if(LD(X_INTERLOCK)){
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
		RRES(Y_GLED);//�ر��̵�
		RRES(Y_BLED);//�ر�����
		SSET(Y_RLED);//�򿪺��
	}
	else if(LaserFlag_Emiting){
		RRES(Y_GLED);//�ر��̵�
		SSET(Y_BLED);//������
		RRES(Y_RLED);//�رպ��
	}
	else{
		SSET(Y_GLED);//���̵�
		RRES(Y_BLED);//�ر�����
		RRES(Y_RLED);//�رպ��
	}
}
static void laserStateLoop(void){//����״̬��ѯ
	fp32_t cur, power;
	//���㼤����� CH0
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_0]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹֵ
	cur = cur / 100.0F / 20.0F / 0.003F;//�������ֵ
	NVRAM0[EM_LASER_CURRENT_CH0] = cur;
	//���㼤����� CH1
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_7]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹֵ
	cur = cur / 100.0F / 20.0F / 0.003F;//�������ֵ
	NVRAM0[EM_LASER_CURRENT_CH1] = cur;
	//���㼤����� CH2
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_6]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹֵ
	cur = cur / 100.0F / 20.0F / 0.003F;//�������ֵ
	NVRAM0[EM_LASER_CURRENT_CH2] = cur;
	//���㼤����� CH3
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_5]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹֵ
	cur = cur / 100.0F / 20.0F / 0.003F;//�������ֵ
	NVRAM0[EM_LASER_CURRENT_CH3] = cur;
	//���⼤����� CH4
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_4]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹֵ
	cur = cur / 100.0F / 20.0F / 0.003F;//�������ֵ
	NVRAM0[EM_LASER_CURRENT_CH4] = cur;
	//���㼤�⹦��
	power = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_2]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹֵ
	if(power > 3.3F){
		power = 3.3;
	}
	if(power < 0){
		power = 0;
	}
	NVRAM0[EM_LASER_PHOTODIODE] = power * 1000;
}
void dcHmiLoop(void){//HMI��ѵ����	
#if CONFIG_DEBUG_APP == 1
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
#endif
	temperatureLoop();
	faultLoop();
/*****************************************************************************/
	laserStateLoop();
	deviceLogInfoLoop();
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
#if CONFIG_USING_SINGLE_WAVE == 1
		NVRAM0[EM_LASER_POWER_CH2] = 0;
		NVRAM0[EM_LASER_POWER_CH3] = 0;
		NVRAM0[EM_LASER_POWER_CH4] = 0;
#endif		
#if CONFIG_USING_DUAL_WAVE == 1
		NVRAM0[EM_LASER_POWER_CH3] = 0;
		NVRAM0[EM_LASER_POWER_CH4] = 0;
#endif	
#if CONFIG_USING_TRIPE_WAVE == 1
		NVRAM0[EM_LASER_POWER_CH4] = 0;
#endif		
#if CONFIG_USING_QUAD_WAVE == 1

#endif		
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
			
			SetControlVisiable(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_KEY_SAVE_UDISK, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_KEY_LOAD_UDISK, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_KEY_SAVE_UDISK, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_KEY_LOAD_UDISK, false);
			
			SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			SetControlEnable(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);

			SetTextValue(GDDC_PAGE_PASSCODE, GDDC_PAGE_PASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
			SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));

			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//��վ�����Ϣ��
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//��վ�����Ϣ��
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//��վ�����Ϣ��
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//��վ�����Ϣ��
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//��վ�����Ϣ��
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//��վ�����Ϣ��
					
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_RFID, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FIBER_PROBE, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FAN_CONTRAL, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_CLEAR_EPROM, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FOOTSWITCH, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_TEMPERATURE, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_ESTOP, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_INTERLOCK, false);		
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);

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
		switch(NVRAM0[EM_LASER_PULSE_MODE]){//�����Զ��Ӽ�
			case LASER_MODE_SP:{
				if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//������Ӱ���
					T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_SP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_SP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_SP);
							if(NVRAM0[EM_LASER_SP_POSWIDTH] >= 10000){//�ﵽ���ֵ��ֹͣ�Լ�
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
							NVRAM0[EM_LASER_SP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_SP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_SP);
							if(NVRAM0[EM_LASER_SP_POSWIDTH] <= 1){//�ﵽ��Сֵ��ֹͣ�Լ�
								RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
								T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
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
							if(NVRAM0[EM_LASER_MP_POSWIDTH] >= 10000){//�ﵽ���ֵ��ֹͣ�Լ�
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
							if(NVRAM0[EM_LASER_MP_POSWIDTH] <= 1){//�ﵽ��Сֵ��ֹͣ�Լ�
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
							if(NVRAM0[EM_LASER_MP_NEGWIDTH] >= 10000){//�ﵽ���ֵ��ֹͣ�Լ�
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
							if(NVRAM0[EM_LASER_MP_NEGWIDTH] <= 1){//�ﵽ��Сֵ��ֹͣ�Լ�
								RRES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
								T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
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
							if(NVRAM0[EM_LASER_GP_POSWIDTH] >= 10000){//�ﵽ���ֵ��ֹͣ�Լ�
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
							NVRAM0[EM_LASER_GP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_GP_POSWIDTH]);		
							updatePosWidthDisplay(LASER_MODE_GP);
							if(NVRAM0[EM_LASER_GP_POSWIDTH] <= 1){//�ﵽ��Сֵ��ֹͣ�Լ�
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
							NVRAM0[EM_LASER_GP_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_GP_NEGWIDTH]);		
							updateNegWidthDisplay(LASER_MODE_GP);
							if(NVRAM0[EM_LASER_GP_NEGWIDTH] >= 10000){//�ﵽ���ֵ��ֹͣ�Լ�
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
							NVRAM0[EM_LASER_GP_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_GP_NEGWIDTH]);	
							updateNegWidthDisplay(LASER_MODE_GP);
							if(NVRAM0[EM_LASER_GP_NEGWIDTH] <= 1){//�ﵽ��Сֵ��ֹͣ�Լ�
								RRES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
								T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}						
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
							else{
								RRES(R_STANDBY_KEY_TIMES_ADD_DOWN);
								T10MS(T10MS_TIMES_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
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
							else{
								RRES(R_STANDBY_KEY_TIMES_DEC_DOWN);
								T10MS(T10MS_TIMES_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
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
							if(NVRAM0[EM_LASER_GP_GROUP_OFF] >= 10000){
								RRES(R_STANDBY_KEY_GROUP_OFF_ADD_DOWN);
								T10MS(T10MS_GROUP_OFF_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}
				if(LD(R_STANDBY_KEY_GROUP_OFF_DEC_DOWN)){//������������
					T10MS(T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_GROUP_OFF] =	pulseWidthDec(NVRAM0[EM_LASER_GP_GROUP_OFF]);	
							updateGroupOffDisplay();
							if(NVRAM0[EM_LASER_GP_GROUP_OFF] <= 1){
								RRES(R_STANDBY_KEY_GROUP_OFF_DEC_DOWN);
								T10MS(T10MS_GROUP_OFF_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
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
							if(NVRAM0[EM_LASER_DERMA_POSWIDTH] >= 10000){//�ﵽ���ֵ��ֹͣ�Լ�
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
							if(NVRAM0[EM_LASER_DERMA_NEGWIDTH] >= 10000){//�ﵽ��Сֵ��ֹͣ�Լ�
								RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
								T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//�����������
					T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_DERMA_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
							updateNegWidthDisplay(LASER_MODE_DERMA);
							if(NVRAM0[EM_LASER_DERMA_NEGWIDTH] <= 1){//�ﵽ��Сֵ��ֹͣ�Լ�
								RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
								T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}					
				break;
			}
			default:break;
		}
		if(LDB(R_FAULT)){//�޹�����ʾ
			RRES(SPCOIL_BEEM_ENABLE);
			updateWarnMsgDisplay(MSG_NO_ERROR);
			standbyKeyEnableSet(true);
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
			standbyKeyEnableSet(false);//��ֹStandby����
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
		}else if(LD(R_STANDBY_KEY_ENTER_SCHEME_DOWN)){//���SCHEME Ĭ����ʾ��һҳ
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
		}else if(LD(R_STANDBY_KEY_STNADBY_DOWN)){//���READY
			standbyTouchEnable(false);//������Ļ����
			standbyKeyEnableSet(false);//���ô���׼������
			if(LD(R_FOOTSWITCH_PRESS)){//����̤����
				//�򿪷�����
				NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_3;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SSET(SPCOIL_BEEM_ENABLE);
				updateWarnMsgDisplay(MSG_FOOT_DEPRESSED);//��ʾ������Ϣ
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_ERROR;	
			}
			else if(LDB(R_FAULT)){//�޹��Ͻ���Standby->Ready��������
				LaserTimer_Select = (int8_t)NVRAM0[EM_LASER_SELECT];
				LaserTimer_Mode = (int8_t)NVRAM0[EM_LASER_PULSE_MODE];
#if CONFIG_DEBUG_APP == 1
				printf("%s,%d,%s:set laser channel=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Select);
				printf("%s,%d,%s:set laser mode=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Mode);
#endif
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
#if CONFIG_DEBUG_APP == 1
				printf("%s,%d,%s:set LaserTimer_TMate=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TMate);
				printf("%s,%d,%s:set LaserTimer_TOvertime=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TOvertime);
				printf("%s,%d,%s:set LaserTimer_PMate=%d\n", __FILE__, __LINE__, __func__, LaserTimer_PMate);
				printf("%s,%d,%s:set LaserTimer_PMate=%d\n", __FILE__, __LINE__, __func__, LaserTimer_PMate);
#endif
				//У���������
				NVRAM0[SPREG_DAC_0] = fitLaserToCode(0, NVRAM0[EM_LASER_POWER_CH0], &deviceConfig);
				NVRAM0[SPREG_DAC_1] = fitLaserToCode(1, NVRAM0[EM_LASER_POWER_CH1], &deviceConfig);
				NVRAM0[SPREG_DAC_2] = fitLaserToCode(2, NVRAM0[EM_LASER_POWER_CH2], &deviceConfig);
				NVRAM0[SPREG_DAC_3] = fitLaserToCode(3, NVRAM0[EM_LASER_POWER_CH3], &deviceConfig);
				NVRAM0[SPREG_DAC_4] = fitLaserToCode(4, NVRAM0[EM_LASER_POWER_CH4], &deviceConfig);
#if CONFIG_DEBUG_APP == 1
				printf("%s,%d,%s:set SPEG_DAC_0=%05d\n", __FILE__, __LINE__, __func__, (uint16_t)NVRAM0[SPREG_DAC_0]);
				printf("%s,%d,%s:set SPEG_DAC_1=%05d\n", __FILE__, __LINE__, __func__, (uint16_t)NVRAM0[SPREG_DAC_1]);
				printf("%s,%d,%s:set SPEG_DAC_2=%05d\n", __FILE__, __LINE__, __func__, (uint16_t)NVRAM0[SPREG_DAC_2]);
				printf("%s,%d,%s:set SPEG_DAC_3=%05d\n", __FILE__, __LINE__, __func__, (uint16_t)NVRAM0[SPREG_DAC_3]);
				printf("%s,%d,%s:set SPEG_DAC_4=%05d\n", __FILE__, __LINE__, __func__, (uint16_t)NVRAM0[SPREG_DAC_4]);
				printf("%s,%d,%s:set SPEG_DAC_5=%05d\n", __FILE__, __LINE__, __func__, (uint16_t)NVRAM0[SPREG_DAC_5]);
				printf("%s,%d,%s:set SPEG_DAC_6=%05d\n", __FILE__, __LINE__, __func__, (uint16_t)NVRAM0[SPREG_DAC_6]);
				printf("%s,%d,%s:set SPEG_DAC_7=%05d\n", __FILE__, __LINE__, __func__, (uint16_t)NVRAM0[SPREG_DAC_7]);
#endif
#if CONFIG_USING_SINGLE_WAVE == 1
				UPDAC0();
#endif
#if CONFIG_USING_DUAL_WAVE == 1//˫����
				UPDAC1();
#endif
#if CONFIG_USING_TRIPE_WAVE == 1//������
				UPDAC2();
#endif
#if CONFIG_USING_QUAD_WAVE == 1//�Ĳ���
				UPDAC3();
#endif
#if CONFIG_USING_FIVE_WAVE == 1//�岨��
				UPDAC4();
#endif				
				//�򿪷�����
				NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_0;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SSET(SPCOIL_BEEM_ENABLE);
#if CONFIG_DEBUG_APP == 1
				printf("%s,%d,%s:set Beem mode:%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_BEEM_MODE]);
				printf("%s,%d,%s:set Beem freq:%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_BEEM_FREQ]);
				printf("%s,%d,%s:set Beem on\n", __FILE__, __LINE__, __func__);
#endif
				//��ָʾ����
				SSET(SPCOIL_AIM_ENABEL);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;	
			}
			else{
				standbyKeyValue(false);
				standbyTouchEnable(true);
			}
			RRES(R_STANDBY_KEY_STNADBY_DOWN);
		}
		else if(LD(R_STANDBY_KEY_SCHEME_SAVE_DOWN)){	
			//��ֹ��Ļ����
			standbyTouchEnable(false);
			standbyKeyEnableSet(false);
			saveScheme();//EM->FD
			FDSAV_ONE(NVRAM0[DM_SCHEME_NUM]);//FDRAM->EPROM
			standbyTouchEnable(true);
			standbyKeyEnableSet(true);
			RRES(R_STANDBY_KEY_SCHEME_SAVE_DOWN);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_PARA){//�ȴ�������
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
		RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
		standbyKeyEnableSet(true);
		RRES(R_STANDBY_KEY_STNADBY_DOWN);
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;	
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_WAIT_TRIGGER){//�ȴ���������	
		updateWarnMsgDisplay(MSG_WAIT_TRIGGER);//��ʾ������Ϣ
		if(LD(R_ENGINEER_MODE)){//����ģʽ��ʾ������Ϣ	
			if(LDP(SPCOIL_PS1000MS)){		
				updateStandbyDebugInfo();
			}
		}
		if(LD(R_FAULT)){//Ready״̬��⵽����
			EDLAR();//ֹͣ����
			NVRAM0[SPREG_DAC_0] = 0;
			NVRAM0[SPREG_DAC_1] = 0;
			NVRAM0[SPREG_DAC_2] = 0;
			NVRAM0[SPREG_DAC_3] = 0;
			NVRAM0[SPREG_DAC_4] = 0;
			UPDAC0();
			UPDAC1();
			UPDAC2();
			UPDAC3();	
			UPDAC4();
			RRES(SPCOIL_AIM_ENABEL);
			standbyTouchEnable(true);
			standbyKeyEnableSet(false);
			standbyKeyValue(false);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
#if CONFIG_DEBUG_APP == 1
			printf("%s,%d,%s:detect fault,goto FSMSTEP_STANDBY!\n", __FILE__, __LINE__, __func__);
			printf("%s,%d,%s:clear all dac!\n", __FILE__, __LINE__, __func__);
#endif
		}
		else if(LD(R_STANDBY_KEY_STNADBY_UP)){//�ص��ȴ�״̬
			EDLAR();//ֹͣ����
			NVRAM0[SPREG_DAC_0] = 0;
			NVRAM0[SPREG_DAC_1] = 0;
			NVRAM0[SPREG_DAC_2] = 0;
			NVRAM0[SPREG_DAC_3] = 0;
			NVRAM0[SPREG_DAC_4] = 0;
			UPDAC0();
			UPDAC1();
			UPDAC2();
			UPDAC3();
			UPDAC4();
			RRES(SPCOIL_AIM_ENABEL);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			standbyTouchEnable(true);
			standbyKeyEnableSet(true);
			standbyKeyValue(false);
			RRES(R_STANDBY_KEY_STNADBY_UP);
			updateWarnMsgDisplay(MSG_NO_ERROR);//��ʾ������Ϣ
#if CONFIG_DEBUG_APP == 1
				printf("%s,%d,%s:set DAC0 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_0]);
				printf("%s,%d,%s:set DAC1 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_1]);
				printf("%s,%d,%s:set DAC2 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_2]);
				printf("%s,%d,%s:set DAC3 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_3]);
				printf("%s,%d,%s:set DAC4 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_4]);
				printf("%s,%d,%s:set DAC5 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_5]);
				printf("%s,%d,%s:set DAC6 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_6]);
				printf("%s,%d,%s:set DAC7 = %d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_7]);
				printf("%s,%d,%s:HMI_OPERA_STEP=%d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_HMI_OPERA_STEP]);
				printf("%s,%d,%s:Return Standby!\n", __FILE__, __LINE__, __func__);
#endif					
		}
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//�����ش���
			if(LDP(R_FOOTSWITCH_PRESS)){//���伤��
				//��ֹStandby����
				standbyKeyEnableSet(false);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				updateWarnMsgDisplay(MSG_LASER_EMIT);
				SSET(SPCOIL_BEEM_ENABLE);//��������
			}
		}
		else{//��ƽ����
			if(LD(R_FOOTSWITCH_PRESS)){//���伤��	
				standbyKeyEnableSet(false);
				HAL_Delay(10);				
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				updateWarnMsgDisplay(MSG_LASER_EMIT);
				SSET(SPCOIL_BEEM_ENABLE);//��������
			}	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_EMITING){//��������
		if(LDP(SPCOIL_PS100MS)){//ÿ��1Sˢ���ۼ�ʱ�������
			LaserRelease_TotalEnergy0 = (fp32_t)(LaserRelease_TotalTime0 * (fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10.0F);//���㷢������
			if(LaserRelease_TotalEnergy0 > 99999){
				LaserRelease_TotalEnergy0 = 99999;
			}
			updateReleaseTimeEnergy();//�����ۼƷ���ʱ�������
		}
		if(LD(R_ENGINEER_MODE)){//����ģʽ��ʾ������Ϣ	
			if(LDP(SPCOIL_PS1000MS)){		
				updateStandbyDebugInfo();
			}
		}		
		if(LD(R_FAULT)){//���ֹ���
			EDLAR();
			NVRAM0[SPREG_DAC_0] = 0;
			NVRAM0[SPREG_DAC_1] = 0;
			NVRAM0[SPREG_DAC_2] = 0;
			NVRAM0[SPREG_DAC_3] = 0;
			NVRAM0[SPREG_DAC_4] = 0;
			UPDAC0();
			UPDAC1();
			UPDAC2();
			UPDAC3();
			UPDAC4();
			RRES(SPCOIL_AIM_ENABEL);//�ر�ָʾ��
			RRES(SPCOIL_BEEM_ENABLE);//�رշ�����		
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			standbyKeyEnableSet(false);
			standbyTouchEnable(true);
			standbyKeyValue(false);
			updateWarnMsgDisplay(MSG_NO_ERROR);
#if CONFIG_DEBUG_APP == 1
			printf("\r\r\r\n\n\n");
			printf("%s,%d,%s:fault detect!, stop Laser emit!\n", __FILE__, __LINE__, __func__);
			printf("%s,%d,%s:R_ESTOP=%d\n", __FILE__, __LINE__, __func__, LD(R_ESTOP));
			printf("%s,%d,%s:R_INTERLOCK=%d\n", __FILE__, __LINE__, __func__, LD(R_INTERLOCK));
			printf("%s,%d,%s:R_FOOTSWITCH_PLUG=%d\n", __FILE__, __LINE__, __func__, LD(R_FOOTSWITCH_PLUG));
			printf("%s,%d,%s:R_FIBER_PROBE=%d\n", __FILE__, __LINE__, __func__, LD(R_FIBER_PROBE));
			printf("%s,%d,%s:R_RFID_PASS=%d\n", __FILE__, __LINE__, __func__, LD(R_RFID_PASS));
			printf("%s,%d,%s:R_LASER_TEMP_HIGH=%d\n", __FILE__, __LINE__, __func__, LD(R_LASER_TEMP_HIGH));
			printf("%s,%d,%s:R_MCU_TEMP_LOW=%d\n", __FILE__, __LINE__, __func__, LD(R_MCU_TEMP_LOW));		
			printf("%s,%d,%s:SPREG_ADC_0=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_0]);
			printf("%s,%d,%s:SPREG_ADC_1=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_1]);
			printf("%s,%d,%s:SPREG_ADC_2=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_2]);
			printf("%s,%d,%s:SPREG_ADC_3=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_3]);
			printf("%s,%d,%s:SPREG_ADC_4=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_4]);
			printf("%s,%d,%s:SPREG_ADC_5=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_5]);
			printf("%s,%d,%s:SPREG_ADC_6=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_6]);
			printf("%s,%d,%s:SPREG_ADC_7=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_7]);
			printf("%s,%d,%s:SPREG_ADC_8=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_8]);
			printf("%s,%d,%s:SPREG_ADC_9=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_9]);
#endif
		}
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//�����ش���
			if(LDP(R_FOOTSWITCH_PRESS)){//�رռ���
				EDLAR();
				updateWarnMsgDisplay(MSG_NO_ERROR);
				RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				standbyKeyEnableSet(true);
				printf("%s,%d,%s:hand switch mode,footswitch press,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		else{
			if(LDB(R_FOOTSWITCH_PRESS)){//�رռ���
				EDLAR(); 
				updateWarnMsgDisplay(MSG_NO_ERROR);
				RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				standbyKeyEnableSet(true);
				printf("%s,%d,%s:foot switch mode,footswitch unpress,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_ERROR){//Ready��⵽��̤����
		if(LDB(R_FOOTSWITCH_PRESS)){//��⵽��̤״̬�ָ�����
			RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
			standbyKeyValue(false);
			standbyKeyEnableSet(true);
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
			resetGddcHmi();
			clearNvram();
			clearFdram();
			clearDeviceConfig();
			clearDeviceLog();
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




