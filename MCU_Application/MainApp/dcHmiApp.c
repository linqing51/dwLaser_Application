#include "dcHmiApp.h"
/*****************************************************************************/
uint8_t hmiCmdBuffer[CMD_MAX_SIZE];//指令缓存
uint16_t hmiCmdSize;//已缓冲的指令数
static uint8_t MsgId = 0xFF;//当前显示的信息ID
static uint8_t StandbyKeyEnable = 0xFF;//待机模式
static void UpdateUI(void);
/*****************************************************************************/
void loadDeviceLogInfo(void){//从EPROM载入记录文件
	uint16_t crc1, crc2;
	HAL_StatusTypeDef ret1, ret2;
	ret1 = epromRead(CONFIG_EPROM_LOGINFO_START, (uint8_t*)&deviceLogInfo, sizeof(deviceLogInfo));//从EPROM载入设备配置
	crc16Clear();
	crc1 = crc16Calculate((uint8_t*)&deviceLogInfo, sizeof(deviceLogInfo));//CRC16 计算数组
	ret2 = epromRead((CONFIG_EPROM_LOGINFO_START + 512 - 2), (uint8_t*)&crc2, 2);//从EPROM载入LOG CRC
	if(ret1 != HAL_OK || ret2 != HAL_OK || crc1 != crc2){//校验码不同使用默认配置
		printf("dcHmiApp->loadDeviceLogInfo:Load device log fail!!!\n");
		printf("dcHmiApp->loadDeviceLogInfo:Reset device log!\n");
		memset((uint8_t*)&deviceLogInfo, 0x0, sizeof(deviceLogInfo));
		saveDeviceLogInfo();
	}
	else{
		printf("dcHmiApp->loadDeviceLogInfo:Load device log ok!\n");
	}
}
void loadDeviceConfig(void){//从EPROM载入配置文件
	uint16_t crc1, crc2;
	uint16_t configSize;
	HAL_StatusTypeDef ret1, ret2;
	configSize = sizeof(deviceConfig);
	ret1 = epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, configSize);//从EPROM载入设备配置
	crc16Clear();
	crc1 = crc16Calculate((uint8_t*)&deviceConfig, configSize);//CRC16 计算数组
	ret2 = epromRead((CONFIG_EPROM_CONFIG_START + 512 - 2), (uint8_t*)&crc2, 2);//从EPROM载入设备配置
	if(ret1 != HAL_OK || ret2 != HAL_OK || crc1 != crc2){//校验码不同使用默认配置
#if CONFIG_DEBUG_APP == 1
		printf("dcHmiApp->loadDeviceConfig:Load device config fail!!!\n");
		printf("dcHmiApp->loadDeviceConfig:Using default device config!\n");
#endif		
		//进行3次多项式拟合Y = A*X^3 + B*X^2 + C*X + D
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
void saveDeviceConfig(void){//将配置写入EPROM
	uint16_t crc;
	HAL_StatusTypeDef ret;
	ret = epromWrite(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//写入EPROM
	if(ret != HAL_OK){
		printf("dcHmiApp->saveDeviceConfig:Save device config to eprom fail!!!\n");
	}
	else{
		printf("dcHmiApp->saveDeviceConfig:Save device config to eprom ok!\n");
	}
	crc16Clear();
	crc = crc16Calculate((uint8_t*)&deviceConfig, sizeof(deviceConfig));//CRC16 计算数组
	ret = epromWrite((CONFIG_EPROM_CONFIG_START + 512 - 2), (uint8_t*)&crc, 2);//写入校验值
	if(ret != HAL_OK){
		printf("dcHmiApp->saveDeviceConfig:Save device config crc to eprom fail!!!\n");
	}
	else{
		printf("dcHmiApp->saveDeviceConfig:Save device config crc to eprom ok!\n");
	}
}
void saveDeviceLogInfo(void){//将记录写入EPROM
	uint16_t crc;
	HAL_StatusTypeDef ret;
	ret = epromWrite(CONFIG_EPROM_LOGINFO_START, (uint8_t*)&deviceLogInfo, sizeof(deviceLogInfo));//写入EPROM
	if(ret != HAL_OK){
		printf("dcHmiApp->saveDeviceLogInfo:Save device log to eprom fail!!!\n");
	}
	crc16Clear();
	crc = crc16Calculate((uint8_t*)&deviceLogInfo, sizeof(deviceLogInfo));//CRC16 计算数组
	ret = epromWrite((CONFIG_EPROM_LOGINFO_START + 512 - 2), (uint8_t*)&crc, 2);//写入校验值
	if(ret != HAL_OK){
		printf("dcHmiApp->saveDeviceLogInfo:Save device log crc to eprom fail!!!\n");
	}
}
void deviceLogInfoLoop(void){//检查记录
	uint8_t upReq;
	upReq = 0;
	if(NVRAM0[EM_LASER_TEMP] > deviceLogInfo.laserMaxTemper){//记录激光器最高温度
		deviceLogInfo.laserMaxTemper = NVRAM0[EM_LASER_TEMP];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_TEMP] < deviceLogInfo.laserMinTemper){//记录激光器最低温度
		deviceLogInfo.laserMinTemper = NVRAM0[EM_LASER_TEMP];
		upReq |= 1;
	}
	if(NVRAM0[EM_MCU_TEMP] > deviceLogInfo.mucMaxTemper){//记录处理器最高温度
		deviceLogInfo.mucMaxTemper = NVRAM0[EM_MCU_TEMP];
		upReq |= 1;
	}
	if(NVRAM0[EM_MCU_TEMP] < deviceLogInfo.mucMinTemper){//记录处理器最低温度
		deviceLogInfo.mucMinTemper = NVRAM0[EM_MCU_TEMP];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH0] > deviceLogInfo.laserMaxCurrent[0]){//记录最大电流 通道0
		deviceLogInfo.laserMaxCurrent[0] = NVRAM0[EM_LASER_CURRENT_CH0];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH1] > deviceLogInfo.laserMaxCurrent[1]){//记录最大电流 通道1
		deviceLogInfo.laserMaxCurrent[1] = NVRAM0[EM_LASER_CURRENT_CH1];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH2] > deviceLogInfo.laserMaxCurrent[2]){//记录最大电流 通道2
		deviceLogInfo.laserMaxCurrent[2] = NVRAM0[EM_LASER_CURRENT_CH2];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH3] > deviceLogInfo.laserMaxCurrent[3]){//记录最大电流 通道3
		deviceLogInfo.laserMaxCurrent[3] = NVRAM0[EM_LASER_CURRENT_CH3];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH4] > deviceLogInfo.laserMaxCurrent[4]){//记录最大电流 通道4
		deviceLogInfo.laserMaxCurrent[4] = NVRAM0[EM_LASER_CURRENT_CH4];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_PHOTODIODE] > deviceLogInfo.laserMaxPhotoDiode){//记录最大功率
		deviceLogInfo.laserMaxPhotoDiode = NVRAM0[EM_LASER_PHOTODIODE];
		upReq |= 1;
	}
	if(NVRAM0[EM_LASER_CURRENT_CH0] > CONFIG_LASER_THRESHOLD_CH0){//通道0电流大于阈值激光发射
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[0] ++;
		}
	}
	if(NVRAM0[EM_LASER_CURRENT_CH1] > CONFIG_LASER_THRESHOLD_CH1){//通道1电流大于阈值激光发射
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[1] ++;
		}
	}
	if(NVRAM0[EM_LASER_CURRENT_CH2] > CONFIG_LASER_THRESHOLD_CH2){//通道2电流大于阈值激光发射
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[2] ++;
		}
	}
	if(NVRAM0[EM_LASER_CURRENT_CH3] > CONFIG_LASER_THRESHOLD_CH3){//通道3电流大于阈值激光发射
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[3] ++;
		}
	}
	if(NVRAM0[EM_LASER_CURRENT_CH4] > CONFIG_LASER_THRESHOLD_CH4){//通道4电流大于阈值激光发射
		if(LDP(SPCOIL_PS1000MS)){
			deviceLogInfo.laserOnTime[4] ++;
		}
	}
	if(LDP(SPCOIL_PS1MINS)){//每分钟记录Log
		deviceLogInfo.runTime ++;
	}
	if(upReq){
		saveDeviceLogInfo();
		upReq = 0;
	}
}
void optionKeyEnable(uint8_t enable){//选项界面按键锁定
	BatchBegin(GDDC_PAGE_OPTION);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_TONE, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_AIM_BRG_ADD, enable);
	BatchSetEnable(GDDC_PAGE_OPTION_KEY_AIM_BRG_DEC, enable);
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
void standbyDebugInfoVisiable(int8_t enable){//Standby调试信息可见
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
void updateStandbyDebugInfo(void){//更新Standby调试信息
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
void updateDiognosisInfo(void){//更新诊断信息
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
void updateEnergyDensity(void){//更新能量密度显示
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
void returnStandbyDisplay(void){//返回STANDBY界面
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
void clearReleaseTimeEnergy(void){//清除发射时间与能量显示
	LaserRelease_TotalTime0 = 0;
	LaserRelease_TotalTime1 = -1;
	LaserRelease_TotalEnergy0 = 0;
	LaserRelease_TotalEnergy1 = -1;
	updateReleaseTimeEnergy();
}
void updateReleaseTimeEnergy(void){//刷新发射时间能量
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
void updateWarnMsgDisplay(uint8_t id){//更新警号显示框
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
void standbyTouchEnable(int8_t enable){//使能STANDBY界面触摸
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
void updatePowerDisplay(int16_t ch, int16_t mode){//更新功率显示
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
void updateExtralDisplay(int16_t mode){//更新额外显示
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
void updateStandbyDisplay(void){//更新方案显示
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
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;//切换待机页面						
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
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_SP;//切换待机页面		
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
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;//切换待机页面
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
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_GP;//切换待机页面
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
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_DERMA;//切换待机页面
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
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_SIGNAL;//切换待机页面
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

void updateOptionDisplay(void){//更新选项显示	
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
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//更新BEEM音量进度条
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_AIM_BRG, NVRAM0[DM_AIM_BRG]);//更新AIM亮度进度条
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);//更新LCD亮度
	BatchEnd();
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME ,NVRAM0[DM_BEEM_VOLUME], 1, 0);
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG ,NVRAM0[DM_LCD_BRG], 1, 0);
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_AIM_BRG ,NVRAM0[DM_AIM_BRG], 1, 0);
}

void updatePosWidthDisplay(int16_t mode){//更新正脉宽显示
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
void updateNegWidthDisplay(int16_t mode){//更新负脉宽显示
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
void updateTimesDisplay(void){//更新Times显示
	SetTextInt32(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_GP_TEXTDISPLAY_TIMES ,NVRAM0[EM_LASER_GP_TIMES], 1, 0);
	updateExtralDisplay(LASER_MODE_GP);
}
void updateGroupOffDisplay(void){//更新GroupOff显示
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
void standbyKeyEnableSet(uint8_t ena){//设置Standby使能
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
void standbyKeyValue(uint8_t value){//设置Standby键值
	SetButtonValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
	SetButtonValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
}
void dcHmiLoopInit(void){//初始化模块
	uint8_t i;
#if CONFIG_USING_DCHMI_APP == 1
	loadDeviceConfig();//载入deviceConfig
	loadDeviceLogInfo();
	deviceLogInfo.powerUpCycle ++;
	saveDeviceLogInfo();
	printf("%s,%d,%s:start hmi uart init......\n",__FILE__, __LINE__, __func__);
	hmiUartInit();
#endif
	NVRAM0[EM_HMI_OPERA_STEP] = 0;
	//检查MUSIC VOLUME储存值是否合规
#if CONFIG_USING_SINGLE_WAVE == 1
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM; i++){
		if(FDRAM[FD_LASER_SELECT + (i * 64)] != LASER_SELECT_CH0){//默认设置为单波长
			FDRAM[FD_LASER_SELECT + (i * 64)] = LASER_SELECT_CH0;
		}
	}
	if(NVRAM0[EM_LASER_SELECT] != LASER_SELECT_CH0){
		NVRAM0[EM_LASER_SELECT] = LASER_SELECT_CH0;
	}
#endif
	
#if CONFIG_USING_DUAL_WAVE == 1
	for(i = 0;i < CONFIG_HMI_SCHEME_NUM; i++){
		if(FDRAM[FD_LASER_SELECT + (i * 30)] != (LASER_SELECT_CH0 | LASER_SELECT_CH1)){//默认设置为单波长
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
	//屏蔽报警
	RRES(R_LASER_TEMP_HIGH);							
	RRES(R_LASER_TEMP_LOW);								
	RRES(R_MCU_TEMP_HIGH);										
	RRES(R_MCU_TEMP_LOW);									
	RRES(R_FAULT);
	//脚踏插入
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
static void temperatureLoop(void){//温度轮询轮询
	int16_t temp;
	TNTC(EM_LASER_TEMP, SPREG_ADC_1);//CODE转换为NTC测量温度温度
	TENV(EM_MCU_TEMP, SPREG_ADC_8);//CODE转换为NTC测量温度温度
	//判断二极管0是否过热
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
	//判断环境是否过热
	if(NVRAM0[EM_MCU_TEMP] > CONFIG_APP_ENVI_HIGH_TEMP){
		SSET(R_MCU_TEMP_HIGH);
	}
	else{
		RRES(R_MCU_TEMP_HIGH);
	}
	//温控执行 激光等待发射及错误状态启动温控	
	if(LD(R_LASER_TEMP_HIGH) || LD(R_MCU_TEMP_HIGH)){//过热状态无条件打开风扇
		SSET(Y_FAN_LD);
	}
	else{ 
		if((NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_WAIT_TRIGGER) ||
		   (NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_EMITING) ||
		   (NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_ERROR) ||
		   (NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_DIAGNOSIS) ||
		   (NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_CORRECTION)){//激光工作或异常状态风扇开
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
	
	if(LD(R_DISABLE_TEMPERATURE)){//屏蔽高温报警
		RRES(R_LASER_TEMP_HIGH);
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
	temp |= LD(R_MCU_TEMP_LOW);//正常0
	if(temp){
		SSET(R_FAULT);
	}
	else{
		RRES(R_FAULT);
	}
	//
	if(LD(R_FAULT)){
		RRES(Y_GLED);//关闭绿灯
		RRES(Y_BLED);//关闭蓝灯
		SSET(Y_RLED);//打开红灯
	}
	else if(LaserFlag_Emiting){
		RRES(Y_GLED);//关闭绿灯
		SSET(Y_BLED);//打开蓝灯
		RRES(Y_RLED);//关闭红灯
	}
	else{
		SSET(Y_GLED);//打开绿灯
		RRES(Y_BLED);//关闭蓝灯
		RRES(Y_RLED);//关闭红灯
	}
}
static void laserStateLoop(void){//激光状态轮询
	fp32_t cur, power;
	//计算激光电流 CH0
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_0]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//计算电压值
	cur = cur / 100.0F / 20.0F / 0.003F;//计算电流值
	NVRAM0[EM_LASER_CURRENT_CH0] = cur;
	//计算激光电流 CH1
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_7]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//计算电压值
	cur = cur / 100.0F / 20.0F / 0.003F;//计算电流值
	NVRAM0[EM_LASER_CURRENT_CH1] = cur;
	//计算激光电流 CH2
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_6]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//计算电压值
	cur = cur / 100.0F / 20.0F / 0.003F;//计算电流值
	NVRAM0[EM_LASER_CURRENT_CH2] = cur;
	//计算激光电流 CH3
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_5]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//计算电压值
	cur = cur / 100.0F / 20.0F / 0.003F;//计算电流值
	NVRAM0[EM_LASER_CURRENT_CH3] = cur;
	//激光激光电流 CH4
	cur = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_4]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//计算电压值
	cur = cur / 100.0F / 20.0F / 0.003F;//计算电流值
	NVRAM0[EM_LASER_CURRENT_CH4] = cur;
	//计算激光功率
	power = (3300.0F * CONFIG_VREF_CAL * NVRAM0[SPREG_ADC_2]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//计算电压值
	if(power > 3.3F){
		power = 3.3;
	}
	if(power < 0){
		power = 0;
	}
	NVRAM0[EM_LASER_PHOTODIODE] = power * 1000;
}
void dcHmiLoop(void){//HMI轮训程序	
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
	if(LD(R_DCHMI_RESET_DONE) && LD(R_DCHMI_RESTORE_DONE)){//HMI复位完成后处理串口指令
		hmiCmdSize = queue_find_cmd(hmiCmdBuffer, CMD_MAX_SIZE);//从缓冲区中获取一条指令         
        if(hmiCmdSize > 0){//接收到指令及判断是否为开机提示                                                            
            ProcessMessage((PCTRL_MSG)hmiCmdBuffer, hmiCmdSize);//指令处理  
        }                                                                             
	}
	//状态机
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_POWERUP){//上电步骤	
		loadScheme();//从掉电存储寄存器中恢复方案参数
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

			SetTextValue(GDDC_PAGE_STANDBY_CW, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏
			SetTextValue(GDDC_PAGE_STANDBY_SP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏
			SetTextValue(GDDC_PAGE_STANDBY_MP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏
			SetTextValue(GDDC_PAGE_STANDBY_GP, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏
			SetTextValue(GDDC_PAGE_STANDBY_DERMA, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏
			SetTextValue(GDDC_PAGE_STANDBY_SIGNAL, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏
					
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
				updateStandbyDebugInfo();
			}
		}
		switch(NVRAM0[EM_LASER_PULSE_MODE]){//脉宽自动加减
			case LASER_MODE_SP:{
				if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//正脉宽加按键
					T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_SP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_SP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_SP);
							if(NVRAM0[EM_LASER_SP_POSWIDTH] >= 10000){//达到最大值后停止自加
								RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
								T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}		
				if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//正脉宽减按键
					T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_SP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_SP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_SP);
							if(NVRAM0[EM_LASER_SP_POSWIDTH] <= 1){//达到最小值后停止自减
								RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
								T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}
				break;
			}
			case LASER_MODE_MP:{
				if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//正脉宽加按键
					T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_MP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_MP_POSWIDTH]);
							updatePosWidthDisplay(LASER_MODE_MP);
							if(NVRAM0[EM_LASER_MP_POSWIDTH] >= 10000){//达到最大值后停止自加
								RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
								T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}				
				if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//正脉宽减按键
					T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_MP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_MP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_MP);
							if(NVRAM0[EM_LASER_MP_POSWIDTH] <= 1){//达到最小值后停止自减
								RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
								T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//负脉宽加按键
					T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_MP_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_MP_NEGWIDTH]);
							updateNegWidthDisplay(LASER_MODE_MP);
							if(NVRAM0[EM_LASER_MP_NEGWIDTH] >= 10000){//达到最大值后停止自加
								RRES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
								T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}							
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//负脉宽减按键
					T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_MP_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_MP_NEGWIDTH]);
							updateNegWidthDisplay(LASER_MODE_MP);
							if(NVRAM0[EM_LASER_MP_NEGWIDTH] <= 1){//达到最小值后停止自减
								RRES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
								T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}
				break;
			}
			case LASER_MODE_GP:{
				if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//正脉宽加按键
					T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_GP_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_GP);
							if(NVRAM0[EM_LASER_GP_POSWIDTH] >= 10000){//达到最大值后停止自加
								RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
								T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}						
						}
					}
				}				
				if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//正脉宽减按键
					T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_GP_POSWIDTH]);		
							updatePosWidthDisplay(LASER_MODE_GP);
							if(NVRAM0[EM_LASER_GP_POSWIDTH] <= 1){//达到最小值后停止自减
								RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
								T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//负脉宽加按键
					T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_GP_NEGWIDTH]);		
							updateNegWidthDisplay(LASER_MODE_GP);
							if(NVRAM0[EM_LASER_GP_NEGWIDTH] >= 10000){//达到最大值后停止自加
								RRES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
								T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//负脉宽减按键
					T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_GP_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_GP_NEGWIDTH]);	
							updateNegWidthDisplay(LASER_MODE_GP);
							if(NVRAM0[EM_LASER_GP_NEGWIDTH] <= 1){//达到最小值后停止自减
								RRES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
								T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}						
						}
					}
				}
				if(LD(R_STANDBY_KEY_TIMES_ADD_DOWN)){//脉冲数加按键
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
				if(LD(R_STANDBY_KEY_TIMES_DEC_DOWN)){//脉冲数减按键
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
				if(LD(R_STANDBY_KEY_GROUP_OFF_ADD_DOWN)){//脉冲间隔加按键
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
				if(LD(R_STANDBY_KEY_GROUP_OFF_DEC_DOWN)){//脉冲间隔减按键
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
				if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//正脉宽加按键
					T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_DERMA_POSWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_DERMA_POSWIDTH]);		
							updatePosWidthDisplay(LASER_MODE_DERMA);
							if(NVRAM0[EM_LASER_DERMA_POSWIDTH] >= 10000){//达到最大值后停止自加
								RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
								T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}						
						}
					}
				}				
				if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//正脉宽减按键
					T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_DERMA_POSWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_DERMA_POSWIDTH]);	
							updatePosWidthDisplay(LASER_MODE_DERMA);
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//负脉宽加按键
					T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_DERMA_NEGWIDTH] = pulseWidthAdd(NVRAM0[EM_LASER_DERMA_NEGWIDTH]);	
							updateNegWidthDisplay(LASER_MODE_DERMA);
							if(NVRAM0[EM_LASER_DERMA_NEGWIDTH] >= 10000){//达到最小值后停止自减
								RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
								T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
							}
						}
					}
				}
				if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//负脉宽减按键
					T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
					if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
						if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
							NVRAM0[EM_LASER_DERMA_NEGWIDTH] = pulseWidthDec(NVRAM0[EM_LASER_DERMA_NEGWIDTH]);
							updateNegWidthDisplay(LASER_MODE_DERMA);
							if(NVRAM0[EM_LASER_DERMA_NEGWIDTH] <= 1){//达到最小值后停止自减
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
		if(LDB(R_FAULT)){//无故障显示
			RRES(SPCOIL_BEEM_ENABLE);
			updateWarnMsgDisplay(MSG_NO_ERROR);
			standbyKeyEnableSet(true);
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
			standbyKeyEnableSet(false);//禁止Standby触摸
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
		}else if(LD(R_STANDBY_KEY_ENTER_SCHEME_DOWN)){//点击SCHEME 默认显示第一页
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
		}else if(LD(R_STANDBY_KEY_STNADBY_DOWN)){//点击READY
			standbyTouchEnable(false);//禁用屏幕按键
			standbyKeyEnableSet(false);//禁用待机准备按键
			if(LD(R_FOOTSWITCH_PRESS)){//检测脚踏踩下
				//打开蜂鸣器
				NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_3;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SSET(SPCOIL_BEEM_ENABLE);
				updateWarnMsgDisplay(MSG_FOOT_DEPRESSED);//显示错误信息
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_ERROR;	
			}
			else if(LDB(R_FAULT)){//无故障进入Standby->Ready启动过程
				LaserTimer_Select = (int8_t)NVRAM0[EM_LASER_SELECT];
				LaserTimer_Mode = (int8_t)NVRAM0[EM_LASER_PULSE_MODE];
#if CONFIG_DEBUG_APP == 1
				printf("%s,%d,%s:set laser channel=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Select);
				printf("%s,%d,%s:set laser mode=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Mode);
#endif
				switch(LaserTimer_Mode){
					case LASER_MODE_SP:{
						LaserTimer_TMate 			= NVRAM0[EM_LASER_SP_POSWIDTH];//激光脉冲正脉宽 10mS
						break;
					}
					case LASER_MODE_MP:{
						LaserTimer_TMate 			= NVRAM0[EM_LASER_MP_POSWIDTH];//激光脉冲正脉宽 10mS
						LaserTimer_TOvertime 		= NVRAM0[EM_LASER_MP_POSWIDTH] + NVRAM0[EM_LASER_MP_NEGWIDTH];//激光脉冲周期 25mS
						break;
					}
					case LASER_MODE_GP:{
						LaserTimer_TMate 			= NVRAM0[EM_LASER_GP_POSWIDTH];//激光脉冲正脉宽 10mS
						LaserTimer_TOvertime 		= NVRAM0[EM_LASER_GP_POSWIDTH] + NVRAM0[EM_LASER_GP_NEGWIDTH];//激光脉冲周期 25mS
						LaserTimer_PMate 			= NVRAM0[EM_LASER_GP_TIMES];//10个脉冲
						LaserTimer_POvertime 		= NVRAM0[EM_LASER_GP_GROUP_OFF];//间隔33mS
						break;
					}
					case LASER_MODE_DERMA:{
						LaserTimer_TMate 			= NVRAM0[EM_LASER_DERMA_POSWIDTH];//激光脉冲正脉宽 10mS
						LaserTimer_TOvertime 		= NVRAM0[EM_LASER_DERMA_POSWIDTH] + NVRAM0[EM_LASER_DERMA_NEGWIDTH];//激光脉冲周期 25mS
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
				//校正输出功率
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
#if CONFIG_USING_DUAL_WAVE == 1//双波长
				UPDAC1();
#endif
#if CONFIG_USING_TRIPE_WAVE == 1//三波长
				UPDAC2();
#endif
#if CONFIG_USING_QUAD_WAVE == 1//四波长
				UPDAC3();
#endif
#if CONFIG_USING_FIVE_WAVE == 1//五波长
				UPDAC4();
#endif				
				//打开蜂鸣器
				NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_0;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SSET(SPCOIL_BEEM_ENABLE);
#if CONFIG_DEBUG_APP == 1
				printf("%s,%d,%s:set Beem mode:%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_BEEM_MODE]);
				printf("%s,%d,%s:set Beem freq:%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_BEEM_FREQ]);
				printf("%s,%d,%s:set Beem on\n", __FILE__, __LINE__, __func__);
#endif
				//打开指示激光
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
			//禁止屏幕触摸
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
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_PARA){//等待蜂鸣器
		T100MS(T100MS_READY_BEEM_DELAY, true, CONFIG_STANDBY_BEEM_DELAY_TIME);//启动计时器延时2000mS//打开计时器
		//清空计时器
		if(LD(T_100MS_START * 16 + T100MS_READY_BEEM_DELAY)){
			T100MS(T100MS_READY_BEEM_DELAY, false, 3);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_DONE;
		}
		else{
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_DONE){//参数载入完毕并停止蜂鸣器
		RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
		standbyKeyEnableSet(true);
		RRES(R_STANDBY_KEY_STNADBY_DOWN);
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;	
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_WAIT_TRIGGER){//等待触发激光	
		updateWarnMsgDisplay(MSG_WAIT_TRIGGER);//显示警告信息
		if(LD(R_ENGINEER_MODE)){//工程模式显示调试信息	
			if(LDP(SPCOIL_PS1000MS)){		
				updateStandbyDebugInfo();
			}
		}
		if(LD(R_FAULT)){//Ready状态检测到故障
			EDLAR();//停止发射
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
		else if(LD(R_STANDBY_KEY_STNADBY_UP)){//回到等待状态
			EDLAR();//停止发射
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
			updateWarnMsgDisplay(MSG_NO_ERROR);//显示警告信息
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
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//上升沿触发
			if(LDP(R_FOOTSWITCH_PRESS)){//发射激光
				//禁止Standby触摸
				standbyKeyEnableSet(false);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				updateWarnMsgDisplay(MSG_LASER_EMIT);
				SSET(SPCOIL_BEEM_ENABLE);//启动喇叭
			}
		}
		else{//电平触发
			if(LD(R_FOOTSWITCH_PRESS)){//发射激光	
				standbyKeyEnableSet(false);
				HAL_Delay(10);				
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				updateWarnMsgDisplay(MSG_LASER_EMIT);
				SSET(SPCOIL_BEEM_ENABLE);//启动喇叭
			}	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_EMITING){//发激光中
		if(LDP(SPCOIL_PS100MS)){//每隔1S刷新累计时间和能量
			LaserRelease_TotalEnergy0 = (fp32_t)(LaserRelease_TotalTime0 * (fp32_t)(NVRAM0[EM_TOTAL_POWER]) / 10.0F);//计算发射能量
			if(LaserRelease_TotalEnergy0 > 99999){
				LaserRelease_TotalEnergy0 = 99999;
			}
			updateReleaseTimeEnergy();//更新累计发射时间和能量
		}
		if(LD(R_ENGINEER_MODE)){//工程模式显示调试信息	
			if(LDP(SPCOIL_PS1000MS)){		
				updateStandbyDebugInfo();
			}
		}		
		if(LD(R_FAULT)){//发现故障
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
			RRES(SPCOIL_AIM_ENABEL);//关闭指示光
			RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器		
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
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//上升沿触发
			if(LDP(R_FOOTSWITCH_PRESS)){//关闭激光
				EDLAR();
				updateWarnMsgDisplay(MSG_NO_ERROR);
				RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				standbyKeyEnableSet(true);
				printf("%s,%d,%s:hand switch mode,footswitch press,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		else{
			if(LDB(R_FOOTSWITCH_PRESS)){//关闭激光
				EDLAR(); 
				updateWarnMsgDisplay(MSG_NO_ERROR);
				RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				standbyKeyEnableSet(true);
				printf("%s,%d,%s:foot switch mode,footswitch unpress,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_ERROR){//Ready检测到脚踏踩下
		if(LDB(R_FOOTSWITCH_PRESS)){//检测到脚踏状态恢复正常
			RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
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
			loadFdram();//NVRAM->FD
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
			resetGddcHmi();
			clearNvram();
			clearFdram();
			clearDeviceConfig();
			clearDeviceLog();
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




