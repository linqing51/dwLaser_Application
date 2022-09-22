#include "dcHmiApp.h"
/*****************************************************************************/
uint8_t hmiCmdBuffer[CMD_MAX_SIZE];//指令缓存
static uint8_t standbyKeyTouchEnableStatus = 0;
uint16_t hmiCmdSize;//已缓冲的指令数
static uint8_t MsgId = 0xFF;//当前显示的信息ID
static void UpdateUI(void);
extern CRC_HandleTypeDef hcrc;
/*****************************************************************************/
void loadDeviceConfig(void){//从EPROM载入配置文件
	uint32_t crc32_eprom_cfg, crc32_cfg, temp;
	uint8_t i;
	epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//从EPROM载入设备配置
	epromReadDword(CONFIG_EPROM_CFG_CRC, &crc32_eprom_cfg);
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	if(crc32_eprom_cfg != crc32_cfg){//校验码错误使用默认配置
		printf("%s,%d,%s:load device config crc fail!!!\n",__FILE__, __LINE__, __func__);
		printf("%s,%d,%s:using default device config!\n",__FILE__, __LINE__, __func__);
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
void saveDeviceConfig(void){//将配置写入EPROM
	uint32_t crc32_cfg;
	epromWrite(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//写入EPROM	
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	epromWriteDword(CONFIG_EPROM_CFG_CRC, &crc32_cfg);//写入校验值
	printf("%s,%d,%s:save device config to eprom done...(CFG CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_cfg);
}
void optionKeyEnable(uint8_t enable){//选项界面按键锁定
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_TONE, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_ADD, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_DEC, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_LCD_BRG_ADD, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_LCD_BRG_DEC, enable);
	BatchEnd();
	//等待5mS HMI处理器
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
void standbyDebugInfoVisiable(int8_t enable){//Standby调试信息可见
	SetControlVisiable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	//SetControlVisiable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
}
void updateDebugInfo(void){//更新Standby调试信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "TLAS:%05d, TMCU:%05d,FPD:%05d, LPD:%05d", NVRAM0[EM_LASER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[SPREG_ADC_2], NVRAM0[SPREG_ADC_1]);
	switch(NVRAM0[EM_DC_PAGE]){
		case GDDC_PAGE_STANDBY_CW:{
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case GDDC_PAGE_STANDBY_SP:{
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case GDDC_PAGE_STANDBY_MP:{
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case GDDC_PAGE_READY:{
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		default:break;	
	}
}
void updateDiognosisTextBox(void){//更新诊断信息文本框
	uint8_t i;
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	//从NVRAM中更新文本框
	//更新功率校正表
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
void updateDiognosisInfo(void){//更新诊断信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "ADC0:%05d,ADC1:%05d,ADC2:%05d,DAC0:%05d,DAC1:%05d,DAC2:%05d,DAC3:%05d", NVRAM0[SPREG_ADC_0], NVRAM0[SPREG_ADC_1], NVRAM0[SPREG_ADC_2], NVRAM0[SPREG_DAC_0], NVRAM0[SPREG_DAC_1], NVRAM0[SPREG_DAC_2], NVRAM0[SPREG_DAC_3]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO0, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "FS NC:%1d, FS NO:%1d, ES:%d, IL:%1d, FP:%1d", LD(X_FOOTSWITCH_NC),  LD(X_FOOTSWITCH_NO), LD(X_ESTOP_NC), LD(X_INTERLOCK_NC), LD(X_FIBER_PROBE));
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO1, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "TLAS:%05d,TMCU:%05d,FAN:%3d", NVRAM0[EM_LASER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[EM_FAN_SPEED]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO2, (uint8_t*)dispBuf);
}

void updateScheme_0_Display(void){//更新选项界面方案名称
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
void updateScheme_1_Display(void){//更新选项界面方案名称
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
void updateInformationDisplay(void){//更新信息界面显示
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
void returnStandbyDisplay(void){//返回STANDBY界面
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
void clearReleaseTimeEnergy(void){//清除发射时间与能量显示
	LaserRelease_TotalTime0 = 0;
	LaserRelease_TotalTime1 = -1;
	LaserRelease_TotalEnergy0 = 0;
	LaserRelease_TotalEnergy1 = -1;
	LaserAcousticBeepNum = 0;
	updateReleaseTimeEnergy(true);
}
void updateReleaseTimeEnergy(uint8_t refresh){//刷新发射时间能量
	uint8_t minute;
	uint8_t seconds;
	char dispBuf1[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf1, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	//refresh = 1强制更新
	//refresh = 0变化更新
	minute = LaserRelease_TotalTime0 / 60;
	seconds = LaserRelease_TotalTime0 % 60;
	if((LaserRelease_TotalTime0 != LaserRelease_TotalTime1) || refresh){//时间
		sprintf(dispBuf1, "%3d:%02d", minute, seconds);//00:00
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_TREATMENT_TIME, (uint8_t*)dispBuf1);		
		LaserRelease_TotalTime1 =LaserRelease_TotalTime0;
	}
	if((LaserRelease_TotalEnergy0 != LaserRelease_TotalEnergy1) || refresh){//能量
		sprintf(dispBuf1, "%11.1f J", LaserRelease_TotalEnergy0);//00:00
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ENERGEY, (uint8_t*)dispBuf1);
		LaserRelease_TotalEnergy1 = LaserRelease_TotalEnergy0;
	}
}
void updateWarnMsgDisplay(uint8_t id){//更新警号显示框
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
			case MSG_ENVI_LTEMP:{
				pstr = WARN_MSG_ENVI_LTEMP[(NVRAM0[DM_LANGUAGE])];
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
void updateSchemeInfo(int16_t cn){//更新SCHEME 详细参数
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
	sprintf(dispBuf1, "1470nM Power:%3.1fW", ((float)power0 / 10.0F));
	if(cn < 16){
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)dispBuf1);
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, (uint8_t*)dispBuf2);
	}
	else{
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)dispBuf1);
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL2, (uint8_t*)dispBuf2);
	}
}
void unselectSchemeNum(int16_t sel){//反选方案条
	if(sel < 16){
		SetButtonValue(GDDC_PAGE_SCHEME_0, (GDDC_PAGE_SCHEME_KEY_SELECT_0 + sel), 0x0);
	}
	else{
		sel -= 16;
		SetButtonValue(GDDC_PAGE_SCHEME_1, (GDDC_PAGE_SCHEME_KEY_SELECT_0 + sel), 0x0);
	}	
}
void seletcSchemeNum(int16_t sel){//选中方案条
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
void unselectScheme_0_All(void){//反选第一页全部方案条
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
void unselectScheme_1_All(void){//反选第二页全部方案条
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
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_ADD, enable);	
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_DEC, enable);
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_ADD, enable);	
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_DEC, enable);	
}
void readyKeyTouchEnable(int8_t enable){
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);
}
void readyKeyValue(int8_t value){
	SetButtonValue(GDDC_PAGE_READY, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
}
void standbyPageTouchEnable(int8_t enable){//Standby界面触摸
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{//STANDBY CW
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
			break;
		}
		case LASER_MODE_SP:{
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_POWER_ADD, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_POWER_DEC, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);		
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_AIM_BRG_ADD, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_AIM_BRG_DEC, enable);
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, enable);		
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_POSWIDTH_DEC, enable);			
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, enable);	
			break;
		}
		case LASER_MODE_MP:{
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
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, enable);		
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_POSWIDTH_DEC, enable);		
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, enable);		
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_DEC, enable);			
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, enable);	
			SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, enable);	
			break;
		}
		default:break;
	}
}
void standbyKeyTouchEnable(int8_t enable){//Standby key触摸
	if(enable != standbyKeyTouchEnableStatus){
		SetControlEnable(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);	
		SetControlEnable(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);
		SetControlEnable(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);
		standbyKeyTouchEnableStatus = enable;
	}
}
void standbyKeyValue(uint8_t value){//设置Standby键值
	SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
}
void updatePowerDisplay(void){//更新功率显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER, (uint8_t*)dispBuf);
		}
		case LASER_MODE_SP:{
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER, (uint8_t*)dispBuf);
		}
		case LASER_MODE_MP:{
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER, (uint8_t*)dispBuf);
		}
		default:break;
	}
	updateExtralDisplay();
}
void updateReadyPowerDisplay(void){//更新READY功率显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_POWER, (uint8_t*)dispBuf);
}
static void updateExtralDisplay(void){//更新额外显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	float freq, averagePower, dutyCycle;
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);			
			averagePower = (float)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
			sprintf(dispBuf, "%3.1f W", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_AVERAGE_POWER, (uint8_t*)dispBuf);
			break;
		}
		case LASER_MODE_SP:{
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AVERAGE_POWER, (uint8_t*)dispBuf);		
			break;
		}
		case LASER_MODE_MP:{
			freq = 1000.0F / (float)(NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH]);
			sprintf(dispBuf, "%4.1f Hz", freq);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);			
			dutyCycle = (float)NVRAM0[EM_LASER_MP_POSWIDTH] / (float)(NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH]);
			sprintf(dispBuf, "%4.1f %%", dutyCycle * 100.0F);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);
			averagePower = dutyCycle * (float)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
			sprintf(dispBuf, "%3.1f W", averagePower);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AVERAGE_POWER, (uint8_t*)dispBuf);
			break;
		}
		default:break;
	}
}
void updateStandbyDisplay(void){//更新方案显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	NVRAM0[EM_TOTAL_POWER] = NVRAM0[EM_LASER_POWER_CH0];
	if(NVRAM0[EM_LASER_PULSE_MODE] != LASER_MODE_CW && 
		 NVRAM0[EM_LASER_PULSE_MODE] != LASER_MODE_SP &&
	   NVRAM0[EM_LASER_PULSE_MODE] != LASER_MODE_MP){
		 NVRAM0[EM_LASER_PULSE_MODE] = LASER_MODE_CW;
		 }
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_CW:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;//切换待机页面						
			SetScreen(NVRAM0[EM_DC_PAGE]);
			updatePowerDisplay();
			SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x01);
			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_MODE_SP, 0x00);
			SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x00);
			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME]);							
			SetTextInt32(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
			SetProgressValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//更新进度条
			break;			
		}
		case LASER_MODE_SP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_SP;//切换待机页面		
			SetScreen(NVRAM0[EM_DC_PAGE]);
			updatePowerDisplay();
			updatePosWidthDisplay();
			SetProgressValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));		
			SetButtonValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x00);
			SetButtonValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_MODE_SP, 0x01);
			SetButtonValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x00);
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME]);		
			SetTextInt32(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
			SetProgressValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//更新进度条
			updatePosWidthDisplay();
			break;		
		}
		case LASER_MODE_MP:{
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;//切换待机页面
			SetScreen(NVRAM0[EM_DC_PAGE]);
			updatePowerDisplay();
			SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER, ((uint32_t)NVRAM0[EM_LASER_POWER_CH0] * 100 / CONFIG_MAX_LASERPOWER_CH0));
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_MODE_CW, 0x00);
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_MODE_SP, 0x00);
			SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_MODE_MP, 0x01);
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME]);
			SetTextInt32(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_AIM_BRG , NVRAM0[DM_AIM_BRG], 1, 0);
			SetProgressValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//更新进度条
			updatePosWidthDisplay();
			updateNegWidthDisplay();
			break;
		}
		default:{
		}break;
	}
}

void updateOptionDisplay(void){//更新选项显示	
	if(LD(MR_FOOSWITCH_HAND_SWITCH)){
		SetButtonValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON, 0x01);
	}
	else{
		SetButtonValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON, 0x00);
	}
	if(LD(MR_BEEP_TONE)){
		SetButtonValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_TONE, 0x01);
	}
	else{
		SetButtonValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_TONE, 0x00);
	}
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//更新BEEM音量进度条
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);//更新LCD亮度
	BatchEnd();
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME ,NVRAM0[DM_BEEM_VOLUME], 1, 0);
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG ,NVRAM0[DM_LCD_BRG], 1, 0);
}
void updatePosWidthDisplay(void){//更新正脉宽显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
		case LASER_MODE_SP:{	
			if(NVRAM0[EM_LASER_SP_POSWIDTH] < 1000){
				sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_SP_POSWIDTH]);
			}
			else{
				sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_SP_POSWIDTH] / 1000));
			}
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_POSWIDTH, (uint8_t*)dispBuf);
			break;
		}
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

	updateExtralDisplay();
}
void updateNegWidthDisplay(void){//更新负脉宽显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	switch(NVRAM0[EM_LASER_PULSE_MODE]){
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
	updateExtralDisplay();
}

void updateReadyDisplay(void){//更新READY显示
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_NAME, (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME]);
	updateReadyPowerDisplay();
	clearReleaseTimeEnergy();
	updateReleaseTimeEnergy(true);
	updateAcousticDisplay();
}

void updateAcousticDisplay(void){//更新提示音设置
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	float ftmp;
	int16_t cycle = 0;
	if(NVRAM0[EM_LASER_PULSE_MODE] ==LASER_MODE_CW){//CW
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "N/A");
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ACOUSTIC_CYCLE, (uint8_t*)dispBuf);
		
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%d S", NVRAM0[EM_ACOUSTIC_TIME]);
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ACOUSTIC_TIME, (uint8_t*)dispBuf);
	}
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){//MP
		if(LD(R_ACOUSTIC_ENABLE)){
			cycle = NVRAM0[EM_ACOUSTIC_TIME] / NVRAM0[EM_ACOUSTIC_TIME_STEP];
			memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
			sprintf(dispBuf, "%d Cycle", cycle);
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ACOUSTIC_CYCLE, (uint8_t*)dispBuf);
			
			memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
			sprintf(dispBuf, "%d S", NVRAM0[EM_ACOUSTIC_TIME]);
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ACOUSTIC_TIME, (uint8_t*)dispBuf);
		}
		else{
			memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
			sprintf(dispBuf, "");
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ACOUSTIC_CYCLE, (uint8_t*)dispBuf);
			
			memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
			sprintf(dispBuf, "N/A");
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ACOUSTIC_TIME, (uint8_t*)dispBuf);
		}
	}
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	ftmp = ((float)(NVRAM0[EM_ACOUSTIC_ENERGY]));
	if(LD(R_ACOUSTIC_ENABLE)){
		sprintf(dispBuf, "%4.1fJ", ftmp);
	}
	else{
		sprintf(dispBuf, "N/A");
	}
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ACOUSTIC_ENERGEY, (uint8_t*)dispBuf);
	//调试信息
	printf("%s,%d,%s:acoustic time = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME]);
	printf("%s,%d,%s:acoustic energy = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY]);
	printf("%s,%d,%s:acoustic cycle = %d\n", __FILE__, __LINE__, __func__, cycle);	
}
void dcHmiLoopInit(void){//初始化模块
	uint8_t i;
	setAimBrightness(0);
	printf("%s,%d,%s:start hmi uart init......\n",__FILE__, __LINE__, __func__);
	hmiUartInit();
	NVRAM0[DM_LANGUAGE] = MSG_EN;//默认语言英语
	NVRAM0[EM_HMI_OPERA_STEP] = 0;
	//检查MUSIC VOLUME储存值是否合规
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM; i++){
		if(FDRAM[FD_LASER_SELECT + (i * 64)] != LASER_SELECT_CH0){//默认设置为单波长
			FDRAM[FD_LASER_SELECT + (i * 64)] = LASER_SELECT_CH0;
		}
	}
	NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = CONFIG_BEEM_MAX_VOLUME;
	LIMS16(DM_BEEM_VOLUME, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = CONFIG_AIM_MAX_DC;
	LIMS16(DM_AIM_BRG, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = CONFIG_LCD_MIN_DC;
	NVRAM0[TMP_REG_1] = CONFIG_LCD_MAX_DC;
	LIMS16(DM_LCD_BRG, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = 7;
	LIMS16(DM_LANGUAGE, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[EM_FAN_SPEED] = 0;
	SSET(R_RFID_PASS);
	//屏蔽报警
	RRES(R_LASER_TEMP_HIGH);							
	RRES(R_LASER_TEMP_LOW);								
	RRES(R_MCU_TEMP_HIGH);										
	RRES(R_MCU_TEMP_LOW);									
	RRES(R_FAULT);
	//脚踏插入
	SSET(R_FOOTSWITCH_PLUG);
}
static void temperatureLoop(void){//温度轮询轮询
	TNTC(EM_LASER_TEMP, SPREG_ADC_0);//CODE转换为NTC测量温度温度
	TENV(EM_MCU_TEMP, SPREG_ADC_3);//CODE转换为MCU温度
	//判断二极管温度
	if(NVRAM0[EM_LASER_TEMP] >= CONFIG_DIODE_HIGH_TEMP){//激光器过热
		SSET(R_LASER_TEMP_HIGH);
	}
	if(NVRAM0[EM_LASER_TEMP] <= (CONFIG_DIODE_HIGH_TEMP - 50)){//激光器恢复正常温度
		RRES(R_LASER_TEMP_HIGH);
	}
	if(NVRAM0[EM_LASER_TEMP] <= CONFIG_DIODE_LOW_TEMP){//激光器低温保护
		SSET(R_LASER_TEMP_LOW);
	}
	if(NVRAM0[EM_LASER_TEMP] >= CONFIG_DIODE_LOW_TEMP + 50){//激光器恢复正常温度
		RRES(R_LASER_TEMP_LOW);
	}
	//判断环境温度
	if(NVRAM0[EM_MCU_TEMP] >= CONFIG_ENVI_HIGH_TEMP){//环境温度过热
		SSET(R_MCU_TEMP_HIGH);
	}
	if(NVRAM0[EM_MCU_TEMP] >= CONFIG_ENVI_HIGH_TEMP - 50){
		RRES(R_MCU_TEMP_HIGH);
	}
	if(NVRAM0[EM_MCU_TEMP] <= CONFIG_ENVI_LOW_TEMP){
		SSET(R_MCU_TEMP_LOW);
	}
	if(NVRAM0[EM_MCU_TEMP] >= CONFIG_ENVI_LOW_TEMP + 50){
		RRES(R_MCU_TEMP_LOW);
	}
	if(LDP(SPCOIL_PS10MS)){
		if(NVRAM0[EM_LASER_TEMP] >= CONFIG_DIODE_SET_TEMP + 10){
			SSET(Y_TEC);
		}
		if(NVRAM0[EM_LASER_TEMP] <= CONFIG_DIODE_SET_TEMP - 10){
			RRES(Y_TEC);
		}
	}
	//温控执行 激光等待发射及错误状态启动温控	
	if(LDP(SPCOIL_PS1000MS)){//每秒更新风扇速度
		if(LD(R_LASER_TEMP_HIGH) || LD(R_LASER_TEMP_LOW) || LD(R_MCU_TEMP_HIGH) || LD(R_MCU_TEMP_LOW)){//过热状态无条件打开风扇
			NVRAM0[EM_FAN_SPEED] = 100;
		}
		else{
			if(NVRAM0[EM_LASER_TEMP] < 200){//<20.0C
				NVRAM0[EM_FAN_SPEED] = 0;
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 200) && (NVRAM0[EM_LASER_TEMP] < 220)){
				NVRAM0[EM_FAN_SPEED] = 20;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 220) && (NVRAM0[EM_LASER_TEMP] < 240)){
				NVRAM0[EM_FAN_SPEED] = 25;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 240) && (NVRAM0[EM_LASER_TEMP] < 260)){
				NVRAM0[EM_FAN_SPEED] = 30;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 260) && (NVRAM0[EM_LASER_TEMP] < 280)){
				NVRAM0[EM_FAN_SPEED] = 35;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 280) && (NVRAM0[EM_LASER_TEMP] < 300)){
				NVRAM0[EM_FAN_SPEED] = 40;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 300) && (NVRAM0[EM_LASER_TEMP] < 320)){
				NVRAM0[EM_FAN_SPEED] = 45;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 320) && (NVRAM0[EM_LASER_TEMP] < 340)){
				NVRAM0[EM_FAN_SPEED] = 60;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 340) && (NVRAM0[EM_LASER_TEMP] < 360)){
				NVRAM0[EM_FAN_SPEED] = 85;		
			}
			else if((NVRAM0[EM_LASER_TEMP] >= 360)){
				NVRAM0[EM_FAN_SPEED] = 100;
			}
		}
		setFanSpeed(NVRAM0[EM_FAN_SPEED]);
	}
}
static void faultLoop(void){//故障轮询
	uint8_t temp;
	temp = 0;
	if(LD(R_DISABLE_FIBER_PROBE)){//屏蔽光纤探测器
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
	if(LD(R_DISABLE_RFID)){//屏蔽光纤RFID探测
		SSET(R_RFID_PASS);
	}
	if(LD(R_DISABLE_ESTOP)){//屏蔽紧急停止开关
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
	if(LD(R_DISABLE_TEMPERATURE)){//屏蔽高温报警
		RRES(R_LASER_TEMP_HIGH);
		RRES(R_LASER_TEMP_LOW);
		RRES(R_MCU_TEMP_HIGH);
		RRES(R_MCU_TEMP_LOW);
	}
	if(LD(R_DISABLE_FOOTSWITCH)){//屏蔽脚踏插入探测、使能屏幕激光发射控制
		SSET(R_FOOTSWITCH_PLUG);
		if(LD(R_HMI_FOOTSWITCH_PRESS)){
			SSET(R_FOOTSWITCH_PRESS);
		}
		else{
			RRES(R_FOOTSWITCH_PRESS);
		}
	}
	else{
		if(LD(X_FOOTSWITCH_NC)){//常闭
			SSET(R_FOOTSWITCH_PLUG);
		}
		else{
			RRES(R_FOOTSWITCH_PLUG);
		}
		if(LD(X_FOOTSWITCH_NO)){//常开
			SSET(R_FOOTSWITCH_PRESS);
		}
		else{
			RRES(R_FOOTSWITCH_PRESS);
		}
	}
	temp |= LDB(R_ESTOP);//正常1 
	temp |=	LDB(R_INTERLOCK);//正常1
	temp |= LDB(R_FOOTSWITCH_PLUG);//正常1
	temp |= LDB(R_FIBER_PROBE);//正常1
	temp |= LDB(R_RFID_PASS);//正常1
	temp |= LD(R_LASER_TEMP_HIGH);//正常0
	temp |= LD(R_LASER_TEMP_LOW);//正常0
	temp |= LD(R_MCU_TEMP_LOW);//正常0
	if(temp){
		SSET(R_FAULT);
	}
	else{
		RRES(R_FAULT);
	}
	//
	if(LD(R_FAULT)){
		RRES(Y_GREEN_LED);//关闭绿灯
		RRES(Y_YELLOW_LED);//关闭蓝灯
		SSET(Y_RED_LED);//打开红灯
	}
	else if(LaserFlag_Emiting){
		RRES(Y_GREEN_LED);//关闭绿灯
		SSET(Y_YELLOW_LED);//打开蓝灯
		RRES(Y_RED_LED);//关闭红灯
	}
	else{
		SSET(Y_GREEN_LED);//打开绿灯
		RRES(Y_YELLOW_LED);//关闭蓝灯
		RRES(Y_RED_LED);//关闭红灯
	}
}
static void speakerLoop(void){//蜂鸣器轮询
	int8_t laserStatus0, laserStatus1, laserStatus2, laserStatus3;
	double ftmp;
	if(LD(SPCOIL_BEEM_ENABLE)){
		sPlcSpeakerVolume(NVRAM0[SPREG_BEEM_VOLUME]);
		switch(NVRAM0[SPREG_BEEM_MODE]){//模式
			case BEEM_MODE_0:{
				if(LDB(SPCOIL_BEEM_BUSY)){
					sPlcSpeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				break;
			}
			case BEEM_MODE_1:{//模式1 声光同步
				laserStatus0 = GET_LASER_CH0;
				laserStatus1 = GET_LASER_CH1;
				laserStatus2 = GET_LASER_CH2;
				laserStatus3 = GET_LASER_CH3;	
				if(laserStatus0 || laserStatus1 || laserStatus2 || laserStatus3){//LT3763 PWM ON
					if(LDB(SPCOIL_BEEM_BUSY)){//如果PWM无输出-> 有输出
						sPlcSpeakerEnable();//启动音频
						SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
					}
				}
				else{
					if(LD(SPCOIL_BEEM_BUSY)){
						sPlcSpeakerDisable();//启动音频
						RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器	
					}
				}
				NVRAM0[SPREG_BEEM_COUNTER] = -1;
				break;
			}
			case BEEM_MODE_2:{//模式2 长间隔 激光发射音		
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 50){//1
					sPlcSpeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
					sPlcSpeakerDisable();//停止音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100){
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			case BEEM_MODE_3:{//模式3 滴滴两下一停 报警音
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 25){//1
					sPlcSpeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器			
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 25 && NVRAM0[SPREG_BEEM_COUNTER] < 35){//0
					sPlcSpeakerDisable();//关闭音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 35 && NVRAM0[SPREG_BEEM_COUNTER] < 60){//1
					sPlcSpeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 60 && NVRAM0[SPREG_BEEM_COUNTER] < 70){//0
					sPlcSpeakerDisable();//关闭音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 200){//停1秒
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			case BEEM_MODE_4:{//模式4 长间隔+提示音 激光发射音				
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 50){//1
					sPlcSpeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
					sPlcSpeakerDisable();//停止音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100){
					//判断是否启动提示音
					ftmp = LaserAcousticBeepNum * (float)NVRAM0[EM_ACOUSTIC_ENERGY];
					if(LaserRelease_TotalEnergy0 > ftmp){
						//sPlcSpeakerVolume(100);
						NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_ACOUSITC_SPK_FREQ;
						sPlcSpeakerFreq(NVRAM0[SPREG_BEEM_FREQ]);
						LaserAcousticBeepNum ++;
						printf("%s,%d,%s:beep num:%d, energy:%f\n",__FILE__, __LINE__, __func__, LaserAcousticBeepNum, LaserRelease_TotalEnergy0);
					}
					else{
						//sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
						NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_SPK_FREQ;					
						sPlcSpeakerFreq(NVRAM0[SPREG_BEEM_FREQ]);
					}
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}						
				break;
			}
			default:break;
		}
	}
	else{
		sPlcSpeakerDisable();//关闭音频
		RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
		NVRAM0[SPREG_BEEM_COUNTER]  = 0;
	}
}

void dcHmiLoop(void){//HMI轮训程序	
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
	speakerLoop();
	temperatureLoop();//温控程序
	faultLoop();
	if(LD(R_DCHMI_RESET_DONE) && LD(R_DCHMI_RESTORE_DONE)){//HMI复位完成后处理串口指令
		hmiCmdSize = queue_find_cmd(hmiCmdBuffer, CMD_MAX_SIZE);//从缓冲区中获取一条指令         
        if(hmiCmdSize > 0){//接收到指令及判断是否为开机提示                                                            
            ProcessMessage((PCTRL_MSG)hmiCmdBuffer, hmiCmdSize);//指令处理  
        }                                                                             
	}
	//状态机
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_POWERUP){//上电步骤	
		loadScheme();//从掉电存储寄存器中恢复方案参数	
		NVRAM0[EM_DC_DEFAULT_PASSCODE0] = CONFIG_HMI_DEFAULT_PASSWORD0;
		NVRAM0[EM_DC_DEFAULT_PASSCODE1] = CONFIG_HMI_DEFAULT_PASSWORD1;
		NVRAM0[EM_DC_DEFAULT_PASSCODE2] = CONFIG_HMI_DEFAULT_PASSWORD2;
		NVRAM0[EM_DC_DEFAULT_PASSCODE3] = 0;
		NVRAM0[DM_DC_OLD_PASSCODE2] = 0;
		NVRAM0[DM_DC_OLD_PASSCODE3] = 0;
	
		NVRAM0[EM_DC_NEW_PASSCODE2] = 0;
		NVRAM0[EM_DC_NEW_PASSCODE3] = 0;
		//检查储存密码是否合规
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
		queue_reset();//清空HMI指令接收缓冲区	
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RESTORE_HMI;
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_RESTORE_HMI){//等待HMI复位
		T100MS(T100MS_HMI_POWERUP_DELAY, true, CONFIG_WAIT_HMI_DELAY_TIME);
		if(LD(T_100MS_START * 16 + T100MS_HMI_POWERUP_DELAY)){
			printf("%s,%d,%s:hmi delay done......\n",__FILE__, __LINE__, __func__);
			T100MS(T100MS_HMI_POWERUP_DELAY, false, CONFIG_WAIT_HMI_DELAY_TIME);
			RRES(R_DCHMI_RESET_DOING);
			SSET(R_DCHMI_RESET_DONE);	
			//HMI从内置FLASH中恢复设置	
			SSET(R_DCHMI_RESTORE_DOING);
			FlashRestoreControl(FLASH_DATA_VERSION, FLASH_DATA_ADDR);
			RRES(R_DCHMI_RESTORE_DOING);
			SSET(R_DCHMI_RESTORE_DONE);
			//设置HMI页面
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_WAIT_ENTER_PASSCODE;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_POWERUP;//HMI页面
			MsgId = 0xFF;//当前显示的信息ID
		
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

			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏

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
			
			SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			//打开蜂鸣器
			NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_0;
			NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
			SSET(SPCOIL_BEEM_ENABLE);
		}
		else{
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RESTORE_HMI;	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_CHECK_FAIL_DISPLAY){//自检错误显示
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_WAIT_ENTER_PASSCODE){//等待开机密码输入
		T100MS(T100MS_ENTER_PASSCODE_DELAY, true, CONFIG_WAIT_PASSWORD_DELAY_TIME);
		if(LD(T_100MS_START * 16 + T100MS_ENTER_PASSCODE_DELAY)){
			RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
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
	
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_PASSCODE_INPUT){//输入开机密码
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_PASSCODE_NEW0){//等待输入新密码		
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_STANDBY){//待机状态机
		if(LD(R_ENGINEER_MODE)){//工程模式显示调试信息
			if(LDP(SPCOIL_PS1000MS)){		
				updateDebugInfo();
			}
		}
		if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//正脉宽加按键
			T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					if(NVRAM0[EM_LASER_PULSE_MODE]== LASER_MODE_SP){
						NVRAM0[EM_LASER_SP_POSWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_SP_POSWIDTH], CONFIG_MAX_LASER_POSWIDTH);
						if(NVRAM0[EM_LASER_SP_POSWIDTH] >= CONFIG_MAX_LASER_POSWIDTH){//达到最大值后停止自加
							RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
							T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
						}
					}
					else if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
						NVRAM0[EM_LASER_MP_POSWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_MP_POSWIDTH], CONFIG_MAX_LASER_POSWIDTH);
						if(NVRAM0[EM_LASER_MP_POSWIDTH] >= CONFIG_MAX_LASER_POSWIDTH){//达到最大值后停止自加
							RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
							T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
						}
					}
					updatePosWidthDisplay();
				}
			}
		}					
		if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//正脉宽减按键
			T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_MP_POSWIDTH] = keyRuleDec(NVRAM0[EM_LASER_MP_POSWIDTH], CONFIG_MIN_LASER_POSWIDTH);
					if(NVRAM0[EM_LASER_MP_POSWIDTH] <= CONFIG_MIN_LASER_POSWIDTH){//达到最小值后停止自减
						RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					updatePosWidthDisplay();
				}
			}
		}
		if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//负脉宽加按键
			T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_MP_NEGWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_MP_NEGWIDTH], CONFIG_MAX_LASER_NEGWIDTH);
					if(NVRAM0[EM_LASER_MP_NEGWIDTH] >= CONFIG_MAX_LASER_NEGWIDTH){//达到最大值后停止自加
						RRES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					updateNegWidthDisplay();					
				}
			}
		}
		if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//负脉宽减按键
			T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_MP_NEGWIDTH] = keyRuleDec(NVRAM0[EM_LASER_MP_NEGWIDTH], CONFIG_MIN_LASER_NEGWIDTH);
					if(NVRAM0[EM_LASER_MP_NEGWIDTH] <= CONFIG_MIN_LASER_NEGWIDTH){//达到最小值后停止自减
						RRES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					updateNegWidthDisplay();
				}
			}
		}
		if(LDB(R_FAULT)){//无故障显示
			RRES(SPCOIL_BEEM_ENABLE);
			updateWarnMsgDisplay(MSG_NO_ERROR);
			standbyKeyTouchEnable(true);
		}
		if(LD(R_FAULT)){
			if(LD(R_LASER_TEMP_HIGH)){//激光器高温保护
				updateWarnMsgDisplay(MSG_DIODE_HTEMP);
			}
			else if(LD(R_LASER_TEMP_LOW)){//激光器低温NTC开路保护
				updateWarnMsgDisplay(MSG_DIODE_LTEMP);
			}
			else if(LD(R_MCU_TEMP_HIGH)){//环境高温保护
				updateWarnMsgDisplay(MSG_ENVI_HTEMP);
			}
			else if(LD(R_MCU_TEMP_LOW)){//环境低温保护
				updateWarnMsgDisplay(MSG_ENVI_LTEMP);
			}
			else if(LDB(R_ESTOP)){//急停按下
				updateWarnMsgDisplay(MSG_ESTOP_PRESS);		
			}
			else if(LDB(R_INTERLOCK)){//安全连锁拔出
				updateWarnMsgDisplay(MSG_INTERLOCK_UNPLUG);
			}
			else if(LDB(R_FIBER_PROBE)){//光纤拔出
				updateWarnMsgDisplay(MSG_FIBER_UNPLUG);
			}
			else if(LDB(R_FOOTSWITCH_PLUG)){//脚踏拔出
				updateWarnMsgDisplay(MSG_FOOTSWITCH_UNPLUG);
			}
			else if(LDB(R_RFID_PASS)){//光纤ID不匹配
				updateWarnMsgDisplay(MSG_FIBER_MISSMATE);
			}
			standbyKeyTouchEnable(false);//禁止Standby触摸
			NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_3;//设置喇叭声音模式
			NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
			SSET(SPCOIL_BEEM_ENABLE);//启动喇叭
		}
		if(LD(R_STANDBY_KEY_ENTER_OPTION_DOWN)){//点击OPTION
			RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
			if(LD(R_ENGINEER_MODE)){
				SetControlVisiable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER, true);//显示控件
				SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER ,true);//使能控件
			}
			else{
				SetControlVisiable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER, false);//显示控件
				SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER ,false);//使能控件
			}
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_OPTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			updateOptionDisplay();
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_STANDBY_KEY_ENTER_OPTION_DOWN);
		}else 
		if(LD(R_STANDBY_KEY_ENTER_SCHEME_DOWN)){//点击SCHEME 默认显示第一页
			RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
			if(NVRAM0[DM_SCHEME_NUM] < 16){//第一页
				updateScheme_0_Display();//更新方案第一页名称
				seletcSchemeNum(NVRAM0[DM_SCHEME_NUM]);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_0;
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_0;
			}
			else{
				updateScheme_1_Display();//更新方案第二页名称
				seletcSchemeNum(NVRAM0[DM_SCHEME_NUM]);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_1;
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_1;
			}
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_STANDBY_KEY_ENTER_SCHEME_DOWN);
		}else
		if(LD(R_STANDBY_KEY_STNADBY_DOWN)){//点击READY
			LaserTimer_Select = (int8_t)NVRAM0[EM_LASER_SELECT];
			LaserTimer_Mode = (int8_t)NVRAM0[EM_LASER_PULSE_MODE];
			printf("%s,%d,%s:set laser channel=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Select);
			printf("%s,%d,%s:set laser mode=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Mode);
			LaserTimer_TMate 				= NVRAM0[EM_LASER_MP_POSWIDTH];//激光脉冲正脉宽 10mS
			LaserTimer_TOvertime 		= NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH];//激光脉冲周期 25mS	
			printf("%s,%d,%s:set LaserTimer_TMate=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TMate);
			printf("%s,%d,%s:set LaserTimer_TOvertime=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TOvertime);
			//ACOUSTIC 初始化
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
				//能量大于设置功率的两倍
				SSET(R_ACOUSTIC_ENABLE);
				NVRAM0[EM_ACOUSTIC_TIME_STEP] = 1;//CW模式每次加减量1秒
				NVRAM0[EM_ACOUSTIC_ENERGY_STEP] = NVRAM0[EM_LASER_POWER_CH0] / 10;//CW模式每次加减量
				NVRAM0[EM_ACOUSTIC_TIME] = 2;//初始为1秒
				NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_TIME] * NVRAM0[EM_LASER_POWER_CH0] / 10;
				NVRAM0[EM_ACOUSTIC_TIME_MIN] = 2;//最小2秒
				NVRAM0[EM_ACOUSTIC_TIME_MAX] = NVRAM0[EM_ACOUSTIC_TIME_STEP] * 100;//最大100秒
				NVRAM0[EM_ACOUSTIC_ENERGY_MIN] = NVRAM0[EM_ACOUSTIC_TIME_MIN] * NVRAM0[EM_LASER_POWER_CH0] / 10;
				NVRAM0[EM_ACOUSTIC_ENERGY_MAX] = NVRAM0[EM_LASER_POWER_CH0] / 10 * NVRAM0[EM_ACOUSTIC_TIME_MAX];
			}
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
				//脉冲大于1秒启用提示音
				if((NVRAM0[EM_LASER_MP_POSWIDTH] >= 1000) && (NVRAM0[EM_LASER_MP_NEGWIDTH] >= 1000)){//周期大于2000mS
					SSET(R_ACOUSTIC_ENABLE);
					NVRAM0[EM_ACOUSTIC_TIME_STEP] = (NVRAM0[EM_LASER_MP_POSWIDTH] / 1000) + (NVRAM0[EM_LASER_MP_NEGWIDTH] / 1000);
					NVRAM0[EM_ACOUSTIC_TIME] = NVRAM0[EM_ACOUSTIC_TIME_STEP];
					
					NVRAM0[EM_ACOUSTIC_ENERGY_STEP] = (NVRAM0[EM_LASER_MP_POSWIDTH] / 1000) * NVRAM0[EM_LASER_POWER_CH0] / 10;
					NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
					
					NVRAM0[EM_ACOUSTIC_TIME_MIN] = NVRAM0[EM_ACOUSTIC_TIME_STEP];					
					NVRAM0[EM_ACOUSTIC_TIME_MAX] = NVRAM0[EM_ACOUSTIC_TIME_MIN] * 100;//最大100周期
					NVRAM0[EM_ACOUSTIC_ENERGY_MIN] = NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
					NVRAM0[EM_ACOUSTIC_ENERGY_MAX] = NVRAM0[EM_LASER_POWER_CH0] / 10 * NVRAM0[EM_ACOUSTIC_TIME_MAX];
				
				}
				else{
					RRES(R_ACOUSTIC_ENABLE);
				}
			}
			//调试信息
			if(LD(R_ACOUSTIC_ENABLE)){
				printf("%s,%d,%s:acoustic enable!\n", __FILE__, __LINE__, __func__);
			}
			else{
				printf("%s,%d,%s:acoustic disable!\n", __FILE__, __LINE__, __func__);
			}
			//printf("%s,%d,%s:acoustic time = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME]);
			//printf("%s,%d,%s:acoustic energy = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY]);
			//printf("%s,%d,%s:acoustic cycle = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_CYCLE]);
			
			
			printf("%s,%d,%s:acoustic time step = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME_STEP]);
			printf("%s,%d,%s:acoustic time min = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME_MIN]);
			printf("%s,%d,%s:acoustic time max = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME_MAX]);
			
			printf("%s,%d,%s:acoustic energy step = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY_STEP]);
			printf("%s,%d,%s:acoustic energy min = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY_MIN]);
			printf("%s,%d,%s:acoustic energy max = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY_MAX]);
			
			//校正输出功率
			NVRAM0[SPREG_DAC_0] = fitLaserToCode(0, NVRAM0[EM_LASER_POWER_CH0], &deviceConfig);
			NVRAM0[SPREG_DAC_1] = 0x0;
			NVRAM0[SPREG_DAC_2] = 0x0;
			NVRAM0[SPREG_DAC_3] = 0x0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();//更新工作激光
			//打开指示激光
			setAimBrightness(NVRAM0[DM_AIM_BRG]);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;	
			RRES(R_STANDBY_KEY_STNADBY_DOWN);
			//页面切换
			readyPageTouchEnable(false);
			readyKeyValue(true);
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//切换待机页面
			SetScreen(NVRAM0[EM_DC_PAGE]);
			updateReadyDisplay();
			standbyKeyValue(false);
		}
		if(LD(R_STANDBY_KEY_SCHEME_SAVE_DOWN)){//save down	
			//禁止屏幕触摸
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
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_PARA){//等待蜂鸣器
		readyPageTouchEnable(true);
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_DONE;	
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_DONE){//2秒内脚踏无法使用
		T100MS(T100MS_READY_BEEM_DELAY, true, CONFIG_STANDBY_BEEM_DELAY_TIME);//启动计时器延时2000mS 打开计时器		
		if(LD(T_100MS_START * 16 + T100MS_READY_BEEM_DELAY) && LDB(R_FOOTSWITCH_PRESS)){
			RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
			T100MS(T100MS_READY_BEEM_DELAY, false, 3);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
		}
		else{
			if(LD(R_STANDBY_KEY_STNADBY_UP)){//REDAY 弹起
				RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
				T100MS(T100MS_READY_BEEM_DELAY, false, 3);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
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
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_DONE;
			}
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_WAIT_TRIGGER){//等待触发激光	
		if(LD(R_ENGINEER_MODE)){//工程模式显示调试信息	
			if(LDP(SPCOIL_PS1000MS)){		
				updateDebugInfo();
			}
		}
		if(LD(R_READY_KEY_ACOUSTIC_ENERGY_ADD_DOWN)){
			T10MS(T10MS_ACOUSTIC_ENERGY_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_ACOUSTIC_ENERGY_ADD_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){			
					addAcousticEnergy();
					if(NVRAM0[EM_ACOUSTIC_ENERGY] >= NVRAM0[EM_ACOUSTIC_ENERGY_MAX]){//达到最大值后停止自加
						NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_ENERGY_MAX];
						RRES(R_READY_KEY_ACOUSTIC_ENERGY_ADD_DOWN);
						T10MS(T10MS_ACOUSTIC_ENERGY_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					updateAcousticDisplay();
				}
			}
		}
		if(LD(R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN)){
			T10MS(T10MS_ACOUSTIC_ENERGY_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_ACOUSTIC_ENERGY_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					decAcousticEnergy();
					if(NVRAM0[EM_ACOUSTIC_ENERGY] <= NVRAM0[EM_ACOUSTIC_ENERGY_MIN]){//达到最大值后停止自加
						NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_ENERGY_MIN];
						RRES(R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN);
						T10MS(T10MS_ACOUSTIC_ENERGY_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					updateAcousticDisplay();
				}
			}
		}		
		if(LD(R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN)){
			T10MS(T10MS_ACOUSTIC_TIME_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_ACOUSTIC_TIME_ADD_KEYDOWN_DELAY)){
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					addAcousticTime();
					if(NVRAM0[EM_ACOUSTIC_TIME] >= NVRAM0[EM_ACOUSTIC_TIME_MAX]){//达到最大值后停止自加
						NVRAM0[EM_ACOUSTIC_TIME] = NVRAM0[EM_ACOUSTIC_TIME_MAX];
						RRES(R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN);
						T10MS(T10MS_ACOUSTIC_TIME_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					updateAcousticDisplay();
				}
			}
		}		
		if(LD(R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN)){
			T10MS(T10MS_ACOUSTIC_TIME_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_ACOUSTIC_TIME_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					decAcousticTime();
					if(NVRAM0[EM_ACOUSTIC_TIME] <= NVRAM0[EM_ACOUSTIC_TIME_MIN]){//达到最大值后停止自加
						NVRAM0[EM_ACOUSTIC_TIME] = NVRAM0[EM_ACOUSTIC_TIME_MIN];
						RRES(R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN);
						T10MS(T10MS_ACOUSTIC_TIME_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					updateAcousticDisplay();
				}
			}
		}		
		if(LD(R_STANDBY_KEY_STNADBY_UP) || LD(R_FAULT)){//回到等待状态
			EDLAR();//停止发射
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();
			T100MS(T100MS_READY_BEEM_DELAY, false, 3);//停止2秒计时器
			setAimBrightness(0);
			switch(NVRAM0[EM_LASER_PULSE_MODE]){
				case LASER_MODE_CW:{
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;//切换待机页面 CW
					break;
				}
				case LASER_MODE_SP:{
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_SP;//切换待机页面 CW
					break;
				}
				case LASER_MODE_MP:{
					NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;//切换待机页面 CW
					break;
				}
				default:break;
			}
			SetScreen(NVRAM0[EM_DC_PAGE]);//切换待机页面
			updateStandbyDisplay();
			standbyKeyValue(false);
			if(LD(R_STANDBY_KEY_STNADBY_UP)){
				RRES(R_STANDBY_KEY_STNADBY_UP);
			}
			updateWarnMsgDisplay(MSG_NO_ERROR);//显示警告信息
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			return;
		}
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//上升沿触发
			if(LDP(R_FOOTSWITCH_PRESS)){//发射激光
				readyPageTouchEnable(false);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				SSET(SPCOIL_BEEM_ENABLE);//启动喇叭
			}
		}
		else{//电平触发
			if(LD(R_FOOTSWITCH_PRESS)){//发射激光	
				readyPageTouchEnable(false);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				SSET(SPCOIL_BEEM_ENABLE);//启动喇叭
			}	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_EMITING){//发激光中READY页面
		if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){//每隔1S刷新累计时间和能量
			LaserRelease_TotalEnergy0 = (float)(LaserRelease_TotalTime0 * (float)(NVRAM0[EM_TOTAL_POWER]) / 10.0F);//计算发射能量
			if(LaserRelease_TotalEnergy0 >= 99999999){
				LaserRelease_TotalEnergy0 = 99999999;
			}
			updateReleaseTimeEnergy(false);//更新累计发射时间和能量
		}
		if(LD(R_ENGINEER_MODE)){//工程模式显示调试信息	
			if(LDP(SPCOIL_PS1000MS)){		
				updateDebugInfo();
			}
		}		
		if(LD(R_STANDBY_KEY_STNADBY_UP) || LD(R_FAULT)){//回到等待状态
			EDLAR();//停止发射
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();
			setAimBrightness(0);
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;//切换待机页面 CW 
			}
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;//切换待机页面 MP
			}
			SetScreen(NVRAM0[EM_DC_PAGE]);//切换待机页面
			updateStandbyDisplay();
			standbyKeyValue(false);
			if(LD(R_STANDBY_KEY_STNADBY_UP)){
				RRES(R_STANDBY_KEY_STNADBY_UP);
			}
			updateWarnMsgDisplay(MSG_NO_ERROR);//显示警告信息
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			return;
		}
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//上升沿触发
			if(LDP(R_FOOTSWITCH_PRESS)){//关闭激光
				EDLAR();
				RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				readyPageTouchEnable(true);
				printf("%s,%d,%s:hand switch mode,footswitch press,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		else{
			if(LDB(R_FOOTSWITCH_PRESS)){//关闭激光
				EDLAR(); 
				RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				readyPageTouchEnable(true);
				printf("%s,%d,%s:foot switch mode,footswitch unpress,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_ERROR){//Ready检测到脚踏踩下
		if(LDB(R_FOOTSWITCH_PRESS)){//检测到脚踏状态恢复正常
			RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
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
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_OPTION){//选项界面
		if(LD(R_OPTION_KEY_ENTER_INFORMATION_DOWN)){		
			updateInformationDisplay();		
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_INFORMATION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_INFORMATION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_OPTION_KEY_ENTER_INFORMATION_DOWN);
		}
		if(LD(R_OPTION_KEY_ENTER_OK_DOWN)){//确定
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			updateStandbyDisplay();
			RRES(R_OPTION_KEY_ENTER_OK_DOWN);
		}
		if(LD(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN)){//进入诊断状态
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_DIAGNOSIS;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			updateDiognosisTextBox();//更新文本输入值
			RRES(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_INFORMATION){//信息界面
		if(LD(R_INFORMATION_KEY_OK_DOWN)){
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_OPTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_INFORMATION_KEY_OK_DOWN);	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_SCHEME_0){//方案界面第一页
		if(LD(R_SCHEME_KEY_OK_DOWN)){//确定
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];//选定方案生效
			loadScheme();
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_OK_DOWN);
		}
		else if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//取消
			loadScheme();//FD->EM
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		else if(LD(R_SCHEME_KEY_RENAME_DOWN)){//改名
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//将EM_SCHEME_NUM_TMP指向的名称更新RENAME输入框
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_RENAME_DOWN);
		}
		else if(LD(R_SCHEME_KEY_NEXT_SCHEME)){//第一页->第二页
			updateScheme_1_Display();//更新第二页
			seletcSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);//更新选中条
			updateSchemeInfo(NVRAM0[EM_SCHEME_NUM_TMP]);//更新选中详细信息
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_1;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_1;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_NEXT_SCHEME);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_SCHEME_1){//方案界面第二页
		if(LD(R_SCHEME_KEY_OK_DOWN)){//确定
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];
			loadScheme();
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_OK_DOWN);
		}
		else if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//取消
			sPlcFdramLoad();//NVRAM->FD
			loadScheme();//FD->EM
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		else if(LD(R_SCHEME_KEY_RENAME_DOWN)){//改名
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//将EM_SCHEME_NUM_TMP指向的名称更新RENAME输入框
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_RENAME_DOWN);
		}
		else if(LD(R_SCHEME_KEY_LAST_SCHEME)){//第二页->第一页
			updateScheme_0_Display();//更新第一页
			seletcSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);//更新选中条
			updateSchemeInfo(NVRAM0[EM_SCHEME_NUM_TMP]);//更新选中详细信息
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME_0;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_0;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_LAST_SCHEME);
		}		
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_RENAME){//方案改名
		if(LD(R_RENAME_TEXTDISPLAY_READ_DONE)){//更名完毕				
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
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_DIAGNOSIS){//诊断界面
		if(LD(R_DIAGNOSIS_OK_DOWN)){//返回Option
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_OPTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_DIAGNOSIS_OK_DOWN);
		}
		else if(LD(R_CLEAR_EPROM)){//
			__set_PRIMASK(0);//关闭中断
			sPlcNvramClear();//清空NVRAM
			sPlcFdramClear();//清空FDRAM
			resetGddcHmi();
			delayMs(4000);//等待4秒
			REBOOT();	
		}
		else if(LD(R_SAVE_EPROM)){//储存配制到EPROM
			__set_PRIMASK(0);//关闭中断
			sPlcNvramSave();//更新NVRAM
			sPlcFdramSave();//更新FDRAM
			saveDeviceConfig();//更新配制
			resetGddcHmi();
			delayMs(4000);//等待4秒
			REBOOT();	
		}
		else if(LDP(SPCOIL_PS1000MS)){
			updateDiognosisInfo();
		}
		return;
	}
/*****************************************************************************/
}

//消息处理流程
//msg 待处理消息
//size 消息长度
static void ProcessMessage( PCTRL_MSG msg, uint16_t size ){
	uint8_t cmd_type = msg->cmd_type;                                                     //指令类型
    uint8_t ctrl_msg = msg->ctrl_msg;                                                     //消息的类型
    uint8_t control_type = msg->control_type;                                             //控件类型
    uint16_t screen_id = PTR2U16(&msg->screen_id);                                        //画面ID
    uint16_t control_id = PTR2U16(&msg->control_id);                                      //控件ID
    uint32_t value = PTR2U32(msg->param);                                                 //数值
    switch(cmd_type){  
		case NOTIFY_TOUCH_PRESS:{//触摸屏按下
			break;
		}
		case NOTIFY_TOUCH_RELEASE:{//触摸屏松开
			NotifyTouchXY(hmiCmdBuffer[1],PTR2U16(hmiCmdBuffer + 2),PTR2U16(hmiCmdBuffer + 4)); 
			break;
		}			
		case NOTIFY_WRITE_FLASH_OK:{//写FLASH成功
			NotifyWriteFlash(1);                                                      
			break;              
		}			
		case NOTIFY_WRITE_FLASH_FAILD:{//写FLASH失败
			NotifyWriteFlash(0);                        	                              
			break;            
		}			
		case NOTIFY_READ_FLASH_OK:{//读取FLASH成功
			NotifyReadFlash(1, hmiCmdBuffer + 2, size - 6);//去除帧头帧尾
			break;                                  
		}			
		case NOTIFY_READ_FLASH_FAILD:{//读取FLASH失败
			NotifyReadFlash(0,0,0);                                                   
			break;  
		}			
		case NOTIFY_READ_RTC:{//读取RTC时间
			NotifyReadRTC(hmiCmdBuffer[2], hmiCmdBuffer[3], hmiCmdBuffer[4], hmiCmdBuffer[5], hmiCmdBuffer[6], hmiCmdBuffer[7], hmiCmdBuffer[8]);
			break;
		}
		case NOTIFY_CONTROL:{
			if(ctrl_msg==MSG_GET_CURRENT_SCREEN){//画面ID变化通知
                NotifyScreen(screen_id);//画面切换调动的函数
            }
            else{
				switch(control_type){
					case kCtrlButton:{//按钮控件
						NotifyButton(screen_id,control_id,msg->param[1]);                  
						break;  
					}
					case kCtrlText:{//文本控件
						NotifyText(screen_id,control_id,msg->param);                       
						break;
					}						
					case kCtrlProgress:{//进度条控件
						NotifyProgress(screen_id,control_id,value);                        
						break;
					}						
					case kCtrlSlider:{//滑动条控件
						NotifySlider(screen_id,control_id,value);                          
						break;
					}						
					case kCtrlMeter:{//仪表控件
						NotifyMeter(screen_id,control_id,value);                           
						break;
					}
					case kCtrlMenu:{//菜单控件
						NotifyMenu(screen_id,control_id,msg->param[0],msg->param[1]);      
						break;
					}
					case kCtrlSelector:{//选择控件
						NotifySelector(screen_id,control_id,msg->param[0]);                
						break;
					}						
					case kCtrlRTC:{//倒计时控件
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
    //TODO: 添加用户代码

}

//触摸坐标事件响应
//press 1按下触摸屏，3松开触摸屏;x x坐标;y y坐标
static void NotifyTouchXY(uint8_t press,uint16_t x,uint16_t y){
    //TODO: 添加用户代码
}


/*! 
*  \brief  更新数据
*/ 
static void UpdateUI(void){
	uint8_t err;
	err = err;
}


                                                                          
/*!                                                                              
*  \brief  滑动条控件通知                                                       
*  \details  当滑动条改变(或调用GetControlValue)时，执行此函数                  
*  \param screen_id 画面ID                                                      
*  \param control_id 控件ID                                                     
*  \param value 值                                                              
*/                                                                              
static void NotifySlider(uint16_t screen_id, uint16_t control_id, uint32_t value){                                                                                                                                  

}

/*! 
*  \brief  仪表控件通知
*  \details  调用GetControlValue时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param value 值
*/
static void NotifyMeter(uint16_t screen_id, uint16_t control_id, uint32_t value){
    //TODO: 添加用户代码
}

/*! 
*  \brief  菜单控件通知
*  \details  当菜单项按下或松开时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param item 菜单项索引
*  \param state 按钮状态：0松开，1按下
*/
static void NotifyMenu(uint16_t screen_id, uint16_t control_id, uint8_t item, uint8_t state){

}

/*! 
*  \brief  选择控件通知
*  \details  当选择控件变化时，执行此函数
*  \param screen_id 画面ID
*  \param control_id 控件ID
*  \param item 当前选项
*/
static void NotifySelector(uint16_t screen_id, uint16_t control_id, uint8_t  item){


}

/*! 
*  \brief  定时器超时通知处理
*  \param screen_id 画面ID
*  \param control_id 控件ID
*/
static void NotifyTimer(uint16_t screen_id, uint16_t control_id){
}

/*! 
*  \brief  读取用户FLASH状态返回
*  \param status 0失败，1成功
*  \param _data 返回数据
*  \param length 数据长度
*/
static void NotifyReadFlash(uint8_t status,uint8_t *_data,uint16_t length){
    //TODO: 添加用户代码
}

/*! 
*  \brief  写用户FLASH状态返回
*  \param status 0失败，1成功
*/
static void NotifyWriteFlash(uint8_t status){
    //TODO: 添加用户代码
}


/*! 
*  \brief  string 转 int
*  \param char *str  数字字符串
*/
int str2int(const char *str){
    int temp = 0;
    const char *ptr = str;                                                            //记录字符串

    if(*str == '-' || *str == '+')                                                    //判断第一个字符是否是正负
    {                                                                            
        str++;                                                                        //偏移一位
    }                                                                            
    while(*str != 0)                                                             
    {                                                                            
        if ((*str < '0') || (*str > '9'))                                             //检测是否为数字字符 
        {                                                                        
            break;                                                               
        }                                                                        
        temp = temp * 10 + (*str - '0');                                              //转换
        str++;                                                                        //偏移一位
    }                                                                            
    if (*ptr == '-')                                                                  //如果为负数就取反
    {
        temp = -temp;
    }

    return temp;   
}




