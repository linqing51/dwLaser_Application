#include "dcHmiApp.h"
/*****************************************************************************/
uint8_t hmiCmdBuffer[CMD_MAX_SIZE];//指令缓存
static int8_t standbyKeyTouchEnableStatus = -1;
uint16_t hmiCmdSize;//已缓冲的指令数
static uint8_t MsgId = 0xFF;//当前显示的信息ID
static void UpdateUI(void);
uint8_t CcmRamBuf[0xFFFF] __attribute__ ((at(CCMDATARAM_BASE)));//文件读写缓冲
uint32_t newBootloadCrc32;
IncPid_t LaserTecIncPids;
IncPid_t LaserFanIncPids;
int16_t LaserTecOut;
int16_t LaserFanOut;
int16_t LaserTecOutCounter;
int16_t LaserFanOutCounter;
/*****************************************************************************/
FRESULT retUsbH;
FATFS	USBH_fatfs;
FIL BootLoadFile;//FATFS File Object 记录信息
/*****************************************************************************/
void saveConfigToDisk(void){//将配置储存到U盘

}
void loadConfigFromDisk(void){//从U盘载入配置

}
void saveSchemeToDisk(void){//将方案储存到U盘
	
}
void loadSchemeFromDisk(void){//从U盘载入方案

}
uint8_t updateBootloadReq(void){//更新BOOTLOAD请求 1:可以更新  0：不能更新
	uint32_t TmpReadSize = 0x00;
	uint32_t LastPGAddress;
	uint8_t readflag = TRUE;
	uint32_t bytesread;//实际文件读取字节数
	uint32_t i;
	//警告信息
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Please Standby,Do Not Power Off!!"));
	vTaskDelay(800);
	//挂载USB DISK FAT文件系统
	retUsbH = f_mount(&USBH_fatfs, (const TCHAR*)FATFS_ROOT, 0);
	if(retUsbH != FR_OK){//挂载U盘失败
		printf("Bootloader:Mount Fatfs errror:%d!\n", retUsbH);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Mount usb disk errror,exit update!"));
		return false;
	}
	vTaskDelay(6000);
	//打开文件
	retUsbH = f_open(&BootLoadFile, (const TCHAR*)(BOOTLOAD_FILENAME), FA_OPEN_EXISTING | FA_READ);//
	if(retUsbH != FR_OK){//读取失败跳过固件更新直接运行程序
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		printf("BootLoader:Open %s fail,unmount usb disk,ECODE=0x%02XH\n", BOOTLOAD_FILENAME, retUsbH);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Open file errror,exit update!"));
		return false;
	}
	//检查文件大小
	f_lseek(&BootLoadFile, 0);//读取指针移动到开头
	if(f_size(&BootLoadFile) > BOOTLOADER_FLASH_SIZE){//MCU固件大于FLSAH容量
		f_close(&BootLoadFile);
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		printf("BootLoader:File %s is over length, close file and unmount disk!\n", BOOTLOAD_FILENAME);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("File is over length,exit update!"));
		return false;
	}
	vTaskDelay(800);
	//计算新固件CRC值
	newBootloadCrc32 = 0;
	crc32Clear();
	LastPGAddress = BOOTLOADER_FLASH_START_ADDRESS;
	memset(CcmRamBuf, 0xFF, sizeof(CcmRamBuf));
	while(readflag){
		/* Read maximum 512 Kbyte from the selected file */
		f_read(&BootLoadFile, CcmRamBuf, sizeof(CcmRamBuf), (void*)&bytesread);
		newBootloadCrc32 = crc32Calculate(CcmRamBuf, bytesread);//CRC32 计算数组
		/* Temp variable */
		TmpReadSize = bytesread;
		/* The read data < "BUFFER_SIZE" Kbyte */
		if(TmpReadSize < BUFFER_SIZE){
			readflag = FALSE;
		}
		LastPGAddress += TmpReadSize;
	}
	f_close(&BootLoadFile);
	f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
	for(i = LastPGAddress;i < BOOTLOADER_FLASH_END_ADDRESS;i ++){//补完剩余CRC
		newBootloadCrc32 = crc32CalculateAdd(0xFF);
	}
	//与已有的固件进行对比并给出提示
	if(BootloadCrc == newBootloadCrc32){
		printf("BootLoader:old crc%08X: and new crc:%08X is same,skip update!\n", BootloadCrc , newBootloadCrc32);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)"File is same,skip update...");
		vTaskDelay(800);
		return false;
	}
	else{
		printf("BootLoader:old crc%08X: and new crc:%08X is not same,need confirm update!\n", BootloadCrc , newBootloadCrc32);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)"Confirm update...YES OR NO!!!");
		
		SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, true);
		SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, true);
		
		SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, true);	
		SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, true);	
		
		vTaskDelay(800);
		return true;
	}
}
void confirmBootloadUpdate(void){//执行Bootload更新
	uint32_t i;
	vTaskSuspendAll();//禁用任务切换
	__disable_irq();//关闭中断
	SysTick->CTRL = 0;//关键代码
	HAL_FLASH_Unlock();//解说FLASH锁定
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGSERR | FLASH_FLAG_WRPERR);
	if (FLASH_If_EraseBootload() != 0x00){//擦除BOOTLOAD 失败
		printf("BootLoader:Erase bootload fail, GameOver!!!!!\n");
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Erase bootload fail,Game Over!"));
		return;
	}
	softDelayMs(800);
	if(checkBlank(BOOTLOADER_FLASH_START_ADDRESS, BOOTLOADER_FLASH_SIZE)){//FLASH 查空
		printf("Bootloader:Erase mcu booload sucess.\n");
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Erase bootload sucessful..."));
	}
	else{
		printf("Bootloader:Erase mcu booload fail.\n");
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Erase bootload fail,Game Over!"));
		return;
	}
	softDelayMs(800);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Start update new bootload..."));
	for(i = 0; i < BOOTLOADER_FLASH_SIZE; i += 4){
		if(FLASH_lf_WriteBootload((BOOTLOADER_FLASH_START_ADDRESS + i), *(uint32_t *) (CcmRamBuf + i)) != 0x00){
			printf("BootLoader:write mcu bootload fail,GameOver!!!!!\n");//写入FLASH错误
		}
	}
	HAL_FLASH_Lock();
	printf("BootLoader:Update new bootload done...\n");
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)"Update new bootload done...");
	softDelayMs(800);
	//检查已写入的Bootload是否正确
	printf("BootLoader:Start checksum new bootload...\n");
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Start checksum new bootload..."));
	BootloadCrc = getOriginBootloadCrc();
	softDelayMs(800);
	if(BootloadCrc == newBootloadCrc32){
		printf("BootLoader:Checksum bootload pass,flash crc:%08X, file crc:%08X\n", BootloadCrc , newBootloadCrc32);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Checksum bootload pass,power cycle the system"));
	}
	else{
		printf("BootLoader:Checksum bootload fail,flash crc:%08X, file crc:%08X\n,Game Over!!!\n", BootloadCrc , newBootloadCrc32);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Checksum bootload fail,Game Over!!!"));
		f_close(&BootLoadFile);
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
	}
	while(1);
}

void exitBootloadUpdate(void){//退出Bootload更新
	f_close(&BootLoadFile);
	f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
	vTaskDelay(300);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)(""));
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
		
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);

	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);
	
}
	
void loadDeviceConfig(void){//从EPROM载入配置文件
	uint32_t crc32_eprom_cfg, crc32_cfg;
	epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//从EPROM载入设备配置
	epromReadDword(CONFIG_EPROM_CFG_CRC, &crc32_eprom_cfg);
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	if(crc32_eprom_cfg != crc32_cfg){//校验码错误使用默认配置
		printf("%s,%d,%s:load device config crc fail!!!\n",__FILE__, __LINE__, __func__);
		printf("%s,%d,%s:using default device config!\n",__FILE__, __LINE__, __func__);
		//大族模块默认功率表 1470
		deviceConfig.calibrationPwr0[0] = 9;
		deviceConfig.calibrationPwr0[1] = 28;
		deviceConfig.calibrationPwr0[2] = 48;
		deviceConfig.calibrationPwr0[3] = 68;
		deviceConfig.calibrationPwr0[4] = 87;
		deviceConfig.calibrationPwr0[5] = 105;
		deviceConfig.calibrationPwr0[6] = 120;
		deviceConfig.calibrationPwr0[7] = 133;
		deviceConfig.calibrationPwr0[8] = 144;
		deviceConfig.calibrationPwr0[9] = 153;
		//大族模块默认功率表 980
		deviceConfig.calibrationPwr1[0] = 9;
		deviceConfig.calibrationPwr1[1] = 28;
		deviceConfig.calibrationPwr1[2] = 48;
		deviceConfig.calibrationPwr1[3] = 68;
		deviceConfig.calibrationPwr1[4] = 87;
		deviceConfig.calibrationPwr1[5] = 105;
		deviceConfig.calibrationPwr1[6] = 120;
		deviceConfig.calibrationPwr1[7] = 133;
		deviceConfig.calibrationPwr1[8] = 144;
		deviceConfig.calibrationPwr1[9] = 153;
		
		deviceConfig.mfg_year = 2023;
		deviceConfig.mfg_month = 4;
		deviceConfig.mfg_day = 15;
		
		sprintf(deviceConfig.serialNumber, "XXXX-XXX");
		deviceConfig.greenLedDc = CONFIG_GREEN_LED_DEFAULT_DC;
		deviceConfig.redLedDc = CONFIG_RED_LED_DEFAULT_DC;
		deviceConfig.blueLedDc = CONFIG_BLUE_LED_DEFAULT_DC;
		deviceConfig.aimGain = CONFIG_AIM_DEFAULT_GAIN;
		deviceConfig.normalOpenInterLock = 1;//默认常开脚踏 
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
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_ADD, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_BEEM_VOLUME_INC, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_LCD_BRG_ADD, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_LCD_BRG_INC, enable);		
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_OK, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_INFORMATION, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_HAND_SWITCH_ON, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_ENTER_ENGINEER, enable);	
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_RESTORE, enable);
}
void standbyDebugInfoVisiable(int8_t enable){//Standby调试信息可见
	SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_READY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
}
void updateDebugInfo(void){//更新Standby调试信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "TLAS:%05d, TMCU:%05d,FPD:%05d, LPD:%05d", NVRAM0[EM_LASER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[SPREG_ADC_2], NVRAM0[SPREG_ADC_1]);
	switch(NVRAM0[EM_DC_PAGE]){
		case GDDC_PAGE_STANDBY:{
			SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, (uint8_t*)dispBuf);
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
	//
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_YEAR , deviceConfig.mfg_year, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_MONTH , deviceConfig.mfg_month, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_DAY , deviceConfig.mfg_day, 1, 0);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_SN, (uint8_t*)deviceConfig.serialNumber);
	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_RED_LED_DC , deviceConfig.redLedDc, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_GREEN_LED_DC , deviceConfig.greenLedDc, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_BLUE_LED_DC , deviceConfig.blueLedDc, 1, 0);
	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_SET_AIM_GAIN, deviceConfig.aimGain, 1, 0);
	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);	
	SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);	
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
	
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, false);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)"");
	
}
void updateDiognosisInfo(void){//更新诊断信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "ADC0:%05d,ADC1:%05d,ADC2:%05d,DAC0:%05d,DAC1:%05d", NVRAM0[SPREG_ADC_0], NVRAM0[SPREG_ADC_1], NVRAM0[SPREG_ADC_2], NVRAM0[SPREG_DAC_0], NVRAM0[SPREG_DAC_1]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO0, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "FS NC:%1d, FS NO:%1d, ES:%d, IL:%1d, FP:%1d", LD(X_FOOTSWITCH_NC),  LD(X_FOOTSWITCH_NO), LD(X_ESTOP_NC), LD(X_INTERLOCK_NC), LD(X_FIBER_PROBE));
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO1, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "TLAS:%05d,TMCU:%05d,FANs:%3d,FANg:%3d", NVRAM0[EM_LASER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[EM_FAN_SET_SPEED], NVRAM0[EM_FAN_GET_SPEED]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO2, (uint8_t*)dispBuf);
}

void updateScheme_0_Display(void){//更新选项界面方案名称
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_0])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_0]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_1])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_1]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_2])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_2]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_3])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_3]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_4])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_4]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_5])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_5]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_6])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_6]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_7])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_7]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_8])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_8]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_9])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_9]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_10])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_10]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_11])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_11]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_12])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_12]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_13])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_13]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_14])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_14]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_15])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_15]));
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, (uint8_t*)dispBuf);	
	}
	unselectScheme_0_All();
	SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"");
	SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)"");
}
void updateScheme_1_Display(void){//更新选项界面方案名称
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_16])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_16]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_17])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_17]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_18])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_18]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_19])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_19]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_20])) <= CONFIG_SCHEME_NAME_SIZE){	
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_20]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_21])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_21]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_22])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_22]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_23])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_23]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_24])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_24]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_25])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_25]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_26])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_26]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_27])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_27]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_28])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_28]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_29])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_29]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_30])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_30]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, (uint8_t*)dispBuf);
	}
	if(strlen((char*)(&FDRAM0[FD_SCHEME_START_31])) <= CONFIG_SCHEME_NAME_SIZE){
		strcpy(dispBuf, (char*)(&FDRAM0[FD_SCHEME_START_31]));
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, (uint8_t*)dispBuf);	
	}
	unselectScheme_1_All();
	SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"");
	SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)"");
}
void updateInformationDisplay(void){//更新信息界面显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	char *pMain, *pMonir;
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_TPYE, (uint8_t*)INFO_MSG_TYPE);	
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_TPYE, (uint8_t*)INFO_MSG_TYPE);	

	memset(dispBuf, 0x0,sizeof(dispBuf));
	sprintf(dispBuf, "SN:%s", (uint8_t*)deviceConfig.serialNumber);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_SN, (uint8_t*)dispBuf);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_LASER_WAVELENGTH, (uint8_t*)INFO_MSG_WAVELENGTH);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_MAX_LASER_POWER, (uint8_t*)INFO_MSG_LASER_POWER);

	memset(dispBuf, 0x0,sizeof(dispBuf));
	pMain = (char*)(BOOTLOAD_MAIN_ADDRESS);
	pMonir = (char*)(BOOTLAOD_MINOR_ADDRESS);
	if((*pMain >='0' && *pMain <= '9') && (*pMonir >= '0' && *pMonir <= '9')){
		sprintf(dispBuf, "%s;Bootload Ver: %c.%c", (char*)INFO_MSG_VERSION, *pMain, *pMonir);
		SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_VERSION, (uint8_t*)dispBuf);
	}
	else{
		sprintf(dispBuf, "%s;Bootload Ver: 1.0", (char*)INFO_MSG_VERSION);
		SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_VERSION, (uint8_t*)dispBuf);
	}
	memset(dispBuf, 0x0,sizeof(dispBuf));
	sprintf(dispBuf, "MANUFACTURE DATE:%4d-%2d-%2d", deviceConfig.mfg_year, deviceConfig.mfg_month, deviceConfig.mfg_day);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_MANUFACTURE_DATE, (uint8_t*)dispBuf);			
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "UUID:%08X%08X%08X", UniqueId[0], UniqueId[1], UniqueId[2]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_UUID, (uint8_t*)dispBuf);	
}
void returnStandbyDisplay(void){//返回STANDBY界面
	switch(NVRAM0[EM_LASER_PULSE_MODE]){	
		case LASER_MODE_CW:{
			//NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;
			break;
		}
		case LASER_MODE_MP:{
			//NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_MP;
			break;
		}
		default:{
			//NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY_CW;
			break;
		}
	}
	NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;	
	SetScreen(NVRAM0[EM_DC_PAGE]);
}
void clearReleaseTimeEnergy(void){//清除发射时间与能量显示
	CLRD(EM_LASER_RELEASE_TIME);
	CLRD(EM_LASER_TRIG_TIME);
	CLRD(EM_LASER_RELEASE_ENERGY);
	updateReleaseTimeEnergy();
}
void updateReleaseTimeEnergy(void){//刷新发射时间能量
	uint8_t minute;
	uint8_t seconds;
	int32_t temp0, temp1, temp2, temp3, temp4, temp5;
	char dispBuf1[CONFIG_DCHMI_DISKBUF_SIZE];
	int32_t *p;
	memset(dispBuf1, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	temp0 = *((int32_t*)&NVRAM0[EM_LASER_TRIG_TIME]);//激光打开时间秒
	temp0 = temp0 / 50;
	minute = temp0 / 60;
	seconds = temp0 % 60;
	sprintf(dispBuf1, "%3d:%02d", minute, seconds);//00:00
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_TREATMENT_TIME, (uint8_t*)dispBuf1);		
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){//连续模式能量计算
		temp2 = temp0 * NVRAM0[EM_LASER_POWER_TOTAL];//计算发射能量
	}
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){//脉冲模式能量计算
		if(NVRAM0[EM_LASER_POSWIDTH] < 1000 || NVRAM0[EM_LASER_NEGWIDTH] < 1000){//采用计算法
			temp3 = NVRAM0[EM_LASER_POSWIDTH];
			temp4 = NVRAM0[EM_LASER_NEGWIDTH];
			temp2 = temp0 * NVRAM0[EM_LASER_POWER_TOTAL] * temp3 / (temp3 + temp4);
		}
		else{//只计算正脉宽能量
			temp3 = NVRAM0[EM_LASER_POSWIDTH];temp3 = temp3 / 1000;
			temp4 = NVRAM0[EM_LASER_NEGWIDTH];temp4 = temp4 / 1000;
			
			temp1 = temp0 / (temp3 + temp4);
			temp5 = temp0 % (temp3 + temp4);
			temp2 = temp1 * NVRAM0[EM_LASER_POWER_TOTAL] * temp3;
			if(temp5 <= temp3){
				temp2 += temp5 * NVRAM0[EM_LASER_POWER_TOTAL];
			}
			else{
				temp2 += temp3 * NVRAM0[EM_LASER_POWER_TOTAL];
			}	
		}
	}
	if(temp2 < 0){
		temp2 = 0;
	}
	if(temp2 >= INT32_MAX){
		temp2 = INT32_MAX;
	}
	p = (int32_t*)(&NVRAM0[EM_LASER_RELEASE_ENERGY]);
	*p = temp2;
	sprintf(dispBuf1, "%11.1f J", ((float)temp2 / 10));//00:00
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_ENERGEY, (uint8_t*)dispBuf1);
}
void updateWarnMsgDisplay(uint8_t id){//更新警号显示框
	const char *pstr;
	if((MsgId != id) || (NVRAM0[EM_DC_PAGE] != NVRAM1[EM_DC_PAGE])){
		switch(id){
			case MSG_NO_ERROR:{
				pstr = WARN_MSG_NO_ERROR;
				break;
			}
			case MSG_INTERLOCK_UNPLUG:{
				pstr = WARN_MSG_INTERLOCK_UNPLUG;
				break;
			}
			case MSG_FOOTSWITCH_UNPLUG:{
				pstr = WARN_MSG_FOOTSWITCH_UNPLUG;
				break;
			}
			case MSG_ESTOP_PRESS:{
				pstr = WARN_MSG_ESTOP_PRESS;
				break;
			}
			case MSG_FIBER_UNPLUG:{
				pstr = WARN_MSG_FIBER_UNPLUG;
				break;
			}
			case MSG_OUT_ENERGY:{
				pstr = WARN_MSG_OUT_ENERGY;
				break;
			}
			case MSG_DIODE_HTEMP:{
				pstr = WARN_MSG_DIODE_HTEMP;
				break;
			}
			case MSG_DIODE_LTEMP:{
				pstr = WARN_MSG_DIODE_LTEMP;
				break;
			}
			case MSG_DIODE0_OVERCURRENT:{
				pstr = WARN_MSG_DIODE0_OVERCURRENT;
				break;
			}
			case MSG_DIODE1_OVERCURRENT:{
				pstr = WARN_MSG_DIODE1_OVERCURRENT;
				break;
			}
			case MSG_NTC_ERROR:{
				pstr = WARN_MSG_NTC_ERROR;
				break;
			}
			case MSG_ENVI_HTEMP:{
				pstr = WARN_MSG_ENVI_HTEMP;
				break;
			}
			case MSG_ENVI_LTEMP:{
				pstr = WARN_MSG_ENVI_LTEMP;
				break;
			}
			case MSG_FOOT_DEPRESSED:{
				pstr = WARN_MSG_FOOT_DEPRESSED;
				break;
			}
			case MSG_LASER_EMIT:{
				pstr = WARN_MSG_LASER_EMIT;
				break;
			}
			case MSG_WAIT_TRIGGER:{
				pstr = WARN_MSG_WAIT_TRIGGER;
				break;
			}
			case MSG_FIBER_MISSMATE:{
				pstr = WARN_MSG_FIBER_MISSMATE;
				break;
			}
			default:{
				pstr = WARN_MSG_NO_ERROR;
				break;
			}
		}
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, (uint8_t*)pstr);
		MsgId = id;
	}
}
void updateSchemeInfo(int16_t cn){//更新SCHEME 详细参数
	char dispBuf1[CONFIG_DCHMI_DISKBUF_SIZE], dispBuf2[CONFIG_DCHMI_DISKBUF_SIZE];
	int16_t mode;
	int16_t	power_1470;
	int16_t posWidth;
	int16_t negWidth;
	power_1470 =0;
	if(cn < 0)
		cn = 0;
	if(cn > CONFIG_HMI_SCHEME_NUM)
		cn = CONFIG_HMI_SCHEME_NUM;
	mode = FDRAM0[cn * 64 + FD_LASER_PULSE_MODE]; 
	power_1470 = FDRAM0[cn * 64 + FD_LASER_POWER_1470];
	memset(dispBuf1, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);	
	memset(dispBuf2, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf1, "1470nM Power: %3.1fW", ((float)power_1470 / 10.0F));
	if(cn < 16){
		SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)dispBuf1);
	}
	else{
		SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)dispBuf1);
	}	
	switch(mode){
		case LASER_MODE_CW:{
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)"Mode: CW");
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)"Mode: CW");
			}
			break;
		}
		case LASER_MODE_MP:{
			posWidth = FDRAM0[cn * 64 + FD_LASER_MP_POSWIDTH];
			negWidth = FDRAM0[cn * 64 + FD_LASER_MP_NEGWIDTH];
			sprintf(dispBuf2, "Mode: Pulsed,OnTime:%dmS, OffTime:%dmS", posWidth, negWidth );
			if(cn < 16){
				SetTextValue(GDDC_PAGE_SCHEME_0, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)dispBuf2);
			}
			else{
				SetTextValue(GDDC_PAGE_SCHEME_1, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)dispBuf2);
			}
			break;
		}
		default:break;
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
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_INC, enable);
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_ADD, enable);	
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_INC, enable);	
}
void readyKeyTouchEnable(int8_t enable){
	SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);
}
void readyKeyValue(int8_t value){
	SetButtonValue(GDDC_PAGE_READY, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
}
void standbyPageTouchEnable(int8_t enable){//Standby界面触摸
//改为批量修改	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POWER_ADD, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POWER_INC, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_MODE_CW, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_MODE_MP, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_ENTER_OPTION, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_ENTER_SCHEME, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_NEXT, enable);		
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_LAST, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_AIM_BRG_ADD, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_AIM_BRG_INC, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, enable);		
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, enable);		
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, enable);		
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, enable);			
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_1470, enable);
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_1470, enable);
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_1470, enable);
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_1470, enable);	
//		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGC_STANDBY_PROGRESS_AIM_BRG, enable);	
}
void standbyKeyTouchEnable(int8_t enable){//Standby key触摸
	if(enable != standbyKeyTouchEnableStatus){
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);	
		standbyKeyTouchEnableStatus = enable;
	}
}
void standbyKeyValue(uint8_t value){//设置Standby键值
	SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
}
void updateExtralDisplay(void){//更新额外显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	float freq, averagePower, dutyCycle, totalPower;
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
		dutyCycle = 1;
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "N/A");
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);			
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);	
		averagePower = (float)(NVRAM0[EM_LASER_POWER_TOTAL]) / 10.0F;		
	}
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		freq = 1000.0F / (float)(NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH]);
		sprintf(dispBuf, "%4.1f Hz", freq);
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);			
		
		dutyCycle = (float)NVRAM0[EM_LASER_POSWIDTH] / (float)(NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH]);
		sprintf(dispBuf, "%4.1f %%", dutyCycle * 100.0F);
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);
		averagePower = dutyCycle * (float)(NVRAM0[EM_LASER_POWER_TOTAL]) / 10.0F;
	}
	//平均功率显示
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(NVRAM0[EM_LASER_SELECT]){
		case LASER_CHANNEL_1470:{
			averagePower = dutyCycle * (float)(NVRAM0[EM_LASER_POWER_1470]) / 10.0F;
			break;
		}
		case LASER_CHANNEL_980:{
			averagePower = dutyCycle * (float)(NVRAM0[EM_LASER_POWER_980]) / 10.0F;
			break;
		}
		case LASER_CHANNEL_635:{
			averagePower = dutyCycle * (float)(NVRAM0[EM_LASER_POWER_635]) / 10.0F;
			break;
		}
		case LASER_CHANNEL_1470_980:{
			averagePower = dutyCycle * ((float)(NVRAM0[EM_LASER_POWER_1470]) + (float)NVRAM0[EM_LASER_POWER_980]) / 10.0F;
			break;
		}
		case LASER_CHANNEL_1470_635:{
			averagePower = dutyCycle * ((float)(NVRAM0[EM_LASER_POWER_1470]) + (float)NVRAM0[EM_LASER_POWER_635]) / 10.0F;
			break;
		}
		case LASER_CHANNEL_980_635:{
			averagePower = dutyCycle * ((float)(NVRAM0[EM_LASER_POWER_980]) + (float)NVRAM0[EM_LASER_POWER_635]) / 10.0F;
			break;
		}
		case LASER_CHANNEL_1470_980_635:{
			averagePower = dutyCycle * ((float)(NVRAM0[EM_LASER_POWER_1470]) + (float)NVRAM0[EM_LASER_POWER_980] + (float)NVRAM0[EM_LASER_POWER_635]) / 10.0F;
			break;
		}
		default:{
			averagePower = dutyCycle * ((float)(NVRAM0[EM_LASER_POWER_1470]) + (float)NVRAM0[EM_LASER_POWER_980] + (float)NVRAM0[EM_LASER_POWER_635]) / 10.0F;
			break;
		}
	}
	sprintf(dispBuf, "%3.1f W", averagePower);
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_AVERAGE_POWER, (uint8_t*)dispBuf);		
	//总功率显示
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	totalPower = (float)NVRAM0[EM_LASER_POWER_TOTAL] / 10.0F;
	sprintf(dispBuf, "%3.1f W", totalPower);
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
}

void updatePosWidthDisplay(void){//更新正脉宽显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	if(NVRAM0[EM_LASER_POSWIDTH] < 1000){
		sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_POSWIDTH]);
	}
	else{
		sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_POSWIDTH] / 1000));
	}
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_POSWIDTH, (uint8_t*)dispBuf);		
}
void updateNegWidthDisplay(void){//更新负脉宽显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	if(NVRAM0[EM_LASER_NEGWIDTH] < 1000){
		sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_NEGWIDTH]);
	}
	else{
		sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_NEGWIDTH] / 1000));
	}
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_NEGWIDTH, (uint8_t*)dispBuf);
}

void updateStandbyDisplay(void){//更新方案显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	float freq, dutyCycle, barValue;
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_1470] + NVRAM0[EM_LASER_POWER_980] +NVRAM0[EM_LASER_POWER_635];
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
		SetButtonValue(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_MODE_CW, true);
		SetButtonValue(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_MODE_MP, false);
		
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, false);
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, false);
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, false);
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, false);
		
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_TEXTDISPLAY_POSWIDTH, false);
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_TEXTDISPLAY_NEGWIDTH, false);
		
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_ICON_MPKEY, false);
		
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, false);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, false);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, false);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, false);	
		
		sprintf(dispBuf, "N/A");
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);			
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);		
	}
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
		SetButtonValue(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_MODE_CW, false);
		SetButtonValue(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_MODE_MP, true);
		
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, true);
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, true);
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, true);
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, true);
		
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_TEXTDISPLAY_POSWIDTH, true);
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_TEXTDISPLAY_NEGWIDTH, true);
		
		SetControlVisiable(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_ICON_MPKEY, true);
		
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, true);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, true);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, true);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, true);

		
		updatePosWidthDisplay();
		updateNegWidthDisplay();
		
		freq = 1000.0F / (float)(NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH]);
		sprintf(dispBuf, "%4.1f Hz", freq);
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);			
		
		dutyCycle = (float)NVRAM0[EM_LASER_POSWIDTH] / (float)(NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH]);
		sprintf(dispBuf, "%4.1f %%", dutyCycle * 100.0F);
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);			
	}
  barValue = NVRAM0[EM_LASER_POWER_1470] * 100.0F / CONFIG_MAX_LASER_POWER_1470;
	SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_1470, (uint32_t)barValue);
	barValue = NVRAM0[EM_LASER_POWER_980] * 100.0F / CONFIG_MAX_LASER_POWER_980;
	SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_980, (uint32_t)barValue);
	barValue = NVRAM0[EM_LASER_POWER_635] * 100.0F / CONFIG_MAX_LASER_POWER_635;
	SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_635, (uint32_t)barValue);
	SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_650, NVRAM0[DM_AIM_BRG]);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	if(NVRAM0[EM_LASER_SELECT] == LASER_CHANNEL_1470){//1470
		sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_1470]) / 10));
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_SEL, (uint8_t*)dispBuf);
		barValue = NVRAM0[EM_LASER_POWER_1470] * 100.0F / CONFIG_MAX_LASER_POWER_1470;
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL, (uint32_t)barValue);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_1470, 1);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_980, 0);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_635, 0);
	}
	if(NVRAM0[EM_LASER_SELECT] == LASER_CHANNEL_980){//980
		sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_980]) / 10));
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_SEL, (uint8_t*)dispBuf);
		barValue = NVRAM0[EM_LASER_POWER_980] * 100.0F / CONFIG_MAX_LASER_POWER_980;
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL, (uint32_t)barValue);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_1470, 0);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_980, 1);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_635, 0);
	}
	if(NVRAM0[EM_LASER_SELECT] == LASER_CHANNEL_635){//635
		sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_635]) / 10));
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_SEL, (uint8_t*)dispBuf);
		barValue = NVRAM0[EM_LASER_POWER_635] * 100.0F / CONFIG_MAX_LASER_POWER_635;
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL, (uint32_t)barValue);
		SetButtonValue(GDDC_PAGE_STANDBY,GDDC_PAGE_STANDBY_KEY_SELECT_1470, 0);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_980, 0);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_635, 1);
	}
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_1470]) / 10));
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_1470, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_980]) / 10));
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_980, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_635]) / 10));	
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_635, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%d%%\n", NVRAM0[DM_AIM_BRG] * deviceConfig.aimGain);
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_650, (uint8_t*)dispBuf);

	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_NAME, (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME]);
	updateExtralDisplay();
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

void updateReadyDisplay(void){//更新READY显示
	float displayPower;
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(NVRAM0[EM_LASER_SELECT]){
		case LASER_CHANNEL_1470:{
			displayPower = (float)NVRAM0[EM_LASER_POWER_1470] / 10.0F;
			break;
		}
		case LASER_CHANNEL_980:{
			displayPower = (float)NVRAM0[EM_LASER_POWER_980] / 10.0F;
			break;
		}
		case LASER_CHANNEL_635:{
			displayPower = (float)NVRAM0[EM_LASER_POWER_635] / 10.0F;
			break;
		}
		case LASER_CHANNEL_1470_980:{
			displayPower = ((float)NVRAM0[EM_LASER_POWER_1470] + (float)NVRAM0[EM_LASER_POWER_980])/ 10.0F;
			break;
		}			
		case LASER_CHANNEL_1470_635:{
			displayPower = ((float)NVRAM0[EM_LASER_POWER_1470] + (float)NVRAM0[EM_LASER_POWER_635])/ 10.0F;
			break;
		}			
		case LASER_CHANNEL_980_635:{
			displayPower = ((float)NVRAM0[EM_LASER_POWER_980] + (float)NVRAM0[EM_LASER_POWER_635])/ 10.0F;
			break;
		}			
		case LASER_CHANNEL_1470_980_635:{
			displayPower = ((float)NVRAM0[EM_LASER_POWER_1470] + (float)NVRAM0[EM_LASER_POWER_980] + (float)NVRAM0[EM_LASER_POWER_635])/ 10.0F;
			break;
		}			
		default:{
			displayPower = ((float)NVRAM0[EM_LASER_POWER_1470] + (float)NVRAM0[EM_LASER_POWER_980] + (float)NVRAM0[EM_LASER_POWER_635])/ 10.0F;
			break;
		}
	}
	sprintf(dispBuf, "%3.1f W\n", displayPower);
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_POWER_TOTAL, (uint8_t*)dispBuf);
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_NAME, (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME]);
	clearReleaseTimeEnergy();
	updateReleaseTimeEnergy();
	updateAcousticDisplay();
}

void updateAcousticDisplay(void){//更新提示音设置
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	float ftmp;
	int16_t cycle = 0;
	if(NVRAM0[EM_LASER_PULSE_MODE] ==LASER_MODE_CW){//CW
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "");
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
		//PID参数初始化

	LaserTecIncPids.kp = 0.08;
	LaserTecIncPids.ki = 0.005;
	LaserTecIncPids.kd = 0.15;

	standbyKeyTouchEnableStatus = -1;
	setRedLaserPwm(0);
	hmiUartInit();
	NVRAM0[EM_HMI_OPERA_STEP] = 0;
	//检查VOLUME储存值是否合规
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = CONFIG_BEEM_MAX_VOLUME;
	LIMS16(DM_BEEM_VOLUME, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = CONFIG_MAX_LASER_POWER_650;
	LIMS16(DM_AIM_BRG, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = CONFIG_LCD_MIN_DC;
	NVRAM0[TMP_REG_1] = CONFIG_LCD_MAX_DC;
	LIMS16(DM_LCD_BRG, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = 7;
	LIMS16(DM_LANGUAGE, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[EM_FAN_SET_SPEED] = 0;
	NVRAM0[EM_FAN_GET_SPEED] = 0;
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
//	if(LDP(SPCOIL_PS10MS)){
//		if(NVRAM0[EM_LASER_TEMP] >= CONFIG_DIODE_SET_TEMP + 15){
//			SSET(Y_TEC);
//		}
//		if(NVRAM0[EM_LASER_TEMP] <= CONFIG_DIODE_SET_TEMP - 15){
//			RRES(Y_TEC);
//		}
//	}
	//温控执行 激光等待发射及错误状态启动温控
	if(LDP(SPCOIL_PS1000MS)){//2秒间隔
		//运行温控PID程序
		LaserTecOut += IncPidCalc(&LaserTecIncPids, CONFIG_DIODE_SET_TEMP, NVRAM0[EM_LASER_TEMP]); 	
		if(LaserTecOut >= 100){
			LaserTecOut = 100;
		}
		if(LaserTecOut < 0){
			LaserTecOut = 0;
		}
		printf("%s,%d,%s:laser tec out:%d\n",__FILE__, __LINE__, __func__, LaserTecOut);
		LaserTecOutCounter = 0;
		if(LaserTecOut > 0){
			SSET(Y_TEC);
		}
	}
	if(LDP(SPCOIL_PS10MS)){
		if(LaserTecOutCounter >= LaserTecOut){
			RRES(Y_TEC);
		}
		LaserTecOutCounter ++;
	}

	//运行风扇PID程序
	if(LDP(SPCOIL_PS1000MS)){
		if(LD(R_LASER_TEMP_HIGH) || LD(R_LASER_TEMP_LOW) || LD(R_MCU_TEMP_HIGH) || LD(R_MCU_TEMP_LOW)){//过热状态无条件打开风扇
			NVRAM0[EM_FAN_SET_SPEED] = 100;
		}
		else{	
			if(LaserTecOut < 10){//功率小于5W
				NVRAM0[EM_FAN_SET_SPEED] = 20;
			}
			else if(LaserTecOut >= 10 && LaserTecOut < 20){
				NVRAM0[EM_FAN_SET_SPEED] = 25;
			}
			else if(LaserTecOut >= 20 && LaserTecOut < 30){
				NVRAM0[EM_FAN_SET_SPEED] = 30;
			}
			else if(LaserTecOut >= 30 && LaserTecOut < 40){
				NVRAM0[EM_FAN_SET_SPEED] = 40;
			}
			else if(LaserTecOut >= 40 && LaserTecOut < 50){
				NVRAM0[EM_FAN_SET_SPEED] = 50;
			}
			else if(LaserTecOut >= 50 && LaserTecOut < 60){
				NVRAM0[EM_FAN_SET_SPEED] = 60;
			}
			else if(LaserTecOut >= 60 && LaserTecOut < 70){
				NVRAM0[EM_FAN_SET_SPEED] = 70;
			}
			else if(LaserTecOut >= 70 && LaserTecOut < 80){
				NVRAM0[EM_FAN_SET_SPEED] = 80;
			}
			else if(LaserTecOut >= 80 && LaserTecOut < 90){
				NVRAM0[EM_FAN_SET_SPEED] = 90;
			}
			else if(LaserTecOut >= 90 && LaserTecOut <= 100){
				NVRAM0[EM_FAN_SET_SPEED] = 100;
			}
		}
	setFanSpeed(NVRAM0[EM_FAN_SET_SPEED]);
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
		if(deviceConfig.normalOpenInterLock == 1){//常开连锁
			if(LD(X_INTERLOCK_NC)){
				RRES(R_INTERLOCK);
			}
			else{
				SSET(R_INTERLOCK);
			}
		}
		else{//常闭连锁
			if(LD(X_INTERLOCK_NC)){
				SSET(R_INTERLOCK);
			}
			else{
				RRES(R_INTERLOCK);
			}
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
		RRES(Y_YELLOW_LED);//关闭黄灯
		SSET(Y_RED_LED);//打开红灯
	}
	else if(LaserFlag_Emiting){
		SSET(Y_GREEN_LED);//关闭绿灯
		RRES(Y_YELLOW_LED);//打开黄灯
		SSET(Y_RED_LED);//关闭红灯
	}
	else{
		RRES(Y_GREEN_LED);//打开绿灯
		RRES(Y_YELLOW_LED);//关闭黄灯
		RRES(Y_RED_LED);//关闭红灯
	}
}
static void speakerLoop(void){//蜂鸣器轮询
	int8_t laserStatus;
	int32_t temp0;
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
				laserStatus = GET_LASER_1470;
				if(laserStatus){//LT3763 PWM ON
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
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 15){//1
					sPlcSpeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器			
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 15 && NVRAM0[SPREG_BEEM_COUNTER] < 30){//0
					sPlcSpeakerDisable();//关闭音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 30 && NVRAM0[SPREG_BEEM_COUNTER] < 45){//1
					sPlcSpeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 45 && NVRAM0[SPREG_BEEM_COUNTER] < 60){//0
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
					temp0 = (*((int32_t*)&NVRAM0[EM_LASER_TRIG_TIME]) + 25) / 50;
					//temp0 = temp0 / 60;
					if((temp0 % NVRAM0[EM_ACOUSTIC_TIME]) == 0){
						sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME] + 30);		
						NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_ACOUSITC_SPK_FREQ;			
						sPlcSpeakerFreq(NVRAM0[SPREG_BEEM_FREQ]);
					}
					else{
						sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
						NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_SPK_FREQ;					
						sPlcSpeakerFreq(NVRAM0[SPREG_BEEM_FREQ]);
					}
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}						
				break;
			}
			case BEEM_MODE_5:{
				if(NVRAM0[EM_LASER_RELEASE_ENERGY] < 2500){//<250J
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
				}
				else if(NVRAM0[EM_LASER_RELEASE_ENERGY] >= 2500 && NVRAM0[EM_LASER_RELEASE_ENERGY] < 5000){//250-500J	
					if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 15){//1
						sPlcSpeakerEnable();//启动音频
						SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器			
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 15 && NVRAM0[SPREG_BEEM_COUNTER] < 25){//0
						sPlcSpeakerDisable();//关闭音频
						RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 25 && NVRAM0[SPREG_BEEM_COUNTER] < 50){//1
						sPlcSpeakerEnable();//启动音频
						SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
						sPlcSpeakerDisable();//关闭音频
						RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100){
						NVRAM0[SPREG_BEEM_COUNTER] = -1;
					}					
				}
				else if(NVRAM0[EM_LASER_RELEASE_ENERGY] > 5000){
					if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 14){//1
						sPlcSpeakerEnable();//启动音频
						SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器			
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 14 && NVRAM0[SPREG_BEEM_COUNTER] < 26){//0
						sPlcSpeakerDisable();//关闭音频
						RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 26 && NVRAM0[SPREG_BEEM_COUNTER] < 40){//1
						sPlcSpeakerEnable();//启动音频
						SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 40 && NVRAM0[SPREG_BEEM_COUNTER] < 52){//0
						sPlcSpeakerDisable();//关闭音频
						RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 52 && NVRAM0[SPREG_BEEM_COUNTER] < 66){//1
						sPlcSpeakerEnable();//启动音频
						SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 66 && NVRAM0[SPREG_BEEM_COUNTER] < 160){//0
						sPlcSpeakerDisable();//关闭音频
						RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 160){//停1秒
						NVRAM0[SPREG_BEEM_COUNTER] = -1;
					}	
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
	uint8_t tmp8;
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
		NVRAM0[DM_DC_OLD_PASSCODE2] = 0;
		NVRAM0[DM_DC_OLD_PASSCODE3] = 0;
	
		NVRAM0[EM_DC_NEW_PASSCODE2] = 0;
		NVRAM0[EM_DC_NEW_PASSCODE3] = 0;
		//检查储存密码是否合规
		NVRAM0[TMP_REG_0 + 0] = NVRAM0[DM_DC_OLD_PASSCODE0] & 0x00FF;
		NVRAM0[TMP_REG_1 + 1] = (NVRAM0[DM_DC_OLD_PASSCODE0] >> 8) & 0x00FF;
		NVRAM0[TMP_REG_2 + 2] = NVRAM0[DM_DC_OLD_PASSCODE1] & 0x00FF;
		NVRAM0[TMP_REG_3 + 3] = (NVRAM0[DM_DC_OLD_PASSCODE1] >> 8) & 0x00FF;
		if((NVRAM0[TMP_REG_0 + 0] < '0') || (NVRAM0[TMP_REG_0 + 0] > '9') ||
		   (NVRAM0[TMP_REG_1 + 1] < '0') || (NVRAM0[TMP_REG_1 + 1] > '9') ||
		   (NVRAM0[TMP_REG_2 + 2] < '0') || (NVRAM0[TMP_REG_2 + 2] > '9') ||
		   (NVRAM0[TMP_REG_3 + 3] < '0') || (NVRAM0[TMP_REG_3 + 3] > '9')){
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
		
			SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, false);			
			SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			
			SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);					
			SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			
			SetTextValue(GDDC_PAGE_PASSCODE, GDDC_PAGE_PASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
			SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));

			SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏
			
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_RFID, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FIBER_PROBE, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FAN_CONTRAL, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_CLEAR_EPROM, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FOOTSWITCH, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_TEMPERATURE, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_ESTOP, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_INTERLOCK, false);		
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_CALIBRATION_MODE, false);
			
			SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)(""));
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, false);
			
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, true);
			
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			
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
		if(LDP(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){
			NVRAM0[EM_LASER_POSWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_POSWIDTH], CONFIG_MAX_LASER_POSWIDTH);
			updatePosWidthDisplay();
		}
		if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//正脉宽加按键
			T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_POSWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_POSWIDTH], CONFIG_MAX_LASER_POSWIDTH);
					updatePosWidthDisplay();
					if(NVRAM0[EM_LASER_POSWIDTH] >= CONFIG_MAX_LASER_POSWIDTH){//达到最大值后停止自加
						RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
						T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
				}
			}
		}	
		if(LD(R_STANDBY_KEY_POSWIDTH_ADD_UP)){
			RRES(R_STANDBY_KEY_POSWIDTH_ADD_DOWN);
			T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
			updateExtralDisplay();
			RRES(R_STANDBY_KEY_POSWIDTH_ADD_UP);
		}
		if(LDP(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){
			NVRAM0[EM_LASER_POSWIDTH] = keyRuleDec(NVRAM0[EM_LASER_POSWIDTH], CONFIG_MIN_LASER_POSWIDTH);
			updatePosWidthDisplay();
		}
		if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//正脉宽减按键
			T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_POSWIDTH] = keyRuleDec(NVRAM0[EM_LASER_POSWIDTH], CONFIG_MIN_LASER_POSWIDTH);
					updatePosWidthDisplay();
					if(NVRAM0[EM_LASER_POSWIDTH] <= CONFIG_MIN_LASER_POSWIDTH){//达到最小值后停止自减
						RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);
						T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
				}
			}
		}
		if(LD(R_STANDBY_KEY_POSWIDTH_DEC_UP)){
			RRES(R_STANDBY_KEY_POSWIDTH_DEC_DOWN);	
			T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
			updateExtralDisplay();
			RRES(R_STANDBY_KEY_POSWIDTH_DEC_UP);
		}
		if(LDP(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){
			NVRAM0[EM_LASER_NEGWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_NEGWIDTH], CONFIG_MAX_LASER_NEGWIDTH);
			updateNegWidthDisplay();
		}
		if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//负脉宽加按键
			T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_NEGWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_NEGWIDTH], CONFIG_MAX_LASER_NEGWIDTH);
					updateNegWidthDisplay();
					if(NVRAM0[EM_LASER_NEGWIDTH] >= CONFIG_MAX_LASER_NEGWIDTH){//达到最大值后停止自加
						RRES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
						T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}					
				}
			}
		}
		if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_UP)){
			RRES(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN);
			T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
			updateExtralDisplay();
			RRES(R_STANDBY_KEY_NEGWIDTH_ADD_UP);
		}
		if(LDP(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){
			NVRAM0[EM_LASER_NEGWIDTH] = keyRuleDec(NVRAM0[EM_LASER_NEGWIDTH], CONFIG_MIN_LASER_NEGWIDTH);
			updateNegWidthDisplay();
		}
		if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//负脉宽减按键
			T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_NEGWIDTH] = keyRuleDec(NVRAM0[EM_LASER_NEGWIDTH], CONFIG_MIN_LASER_NEGWIDTH);
					updateNegWidthDisplay();
					if(NVRAM0[EM_LASER_NEGWIDTH] <= CONFIG_MIN_LASER_NEGWIDTH){//达到最小值后停止自减
						RRES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
						T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
					}
					updateNegWidthDisplay();
				}
			}
		}
		if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_UP)){
			RRES(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN);
			T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
			updateExtralDisplay();
			RRES(R_STANDBY_KEY_NEGWIDTH_DEC_UP);
		}
		
		if(LDP(SPCOIL_PS200MS)){
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
			else{//无故障显示
				RRES(SPCOIL_BEEM_ENABLE);
				updateWarnMsgDisplay(MSG_NO_ERROR);
				standbyKeyTouchEnable(true);
			}
		}
		if(LDB(R_FAULT) && LDP(SPCOIL_PS100MS)){//无故障显示
			RRES(SPCOIL_BEEM_ENABLE);
			updateWarnMsgDisplay(MSG_NO_ERROR);
			standbyKeyTouchEnable(true);
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
			updateOptionDisplay();
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_STANDBY_KEY_ENTER_OPTION_DOWN);
		}else 
		if(LD(R_STANDBY_KEY_ENTER_SCHEME_DOWN)){//点击SCHEME 默认显示第一页
			//备份FDRAM0->FDRAM1
			memcpy((uint8_t*)FDRAM1, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
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
			CLRD(EM_LASER_RELEASE_TIME);
			CLRD(EM_LASER_TRIG_TIME);
			LaserTimer_Mode = (int8_t)NVRAM0[EM_LASER_PULSE_MODE];
			printf("%s,%d,%s:set laser mode=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Mode);
			if(NVRAM0[EM_LASER_SELECT] == LASER_CHANNEL_635){
				if(NVRAM0[EM_LASER_POSWIDTH] <= 100){
					LaserTimer_TMate				= 100;
				}
				else{
					LaserTimer_TMate 				= NVRAM0[EM_LASER_POSWIDTH];
				}
				if(NVRAM0[EM_LASER_NEGWIDTH] <= 100){
					LaserTimer_TOvertime 		= LaserTimer_TMate + 100;
				}
				else{
					LaserTimer_TOvertime 		= NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH];
				}
			}
			else{
				LaserTimer_TMate 				= NVRAM0[EM_LASER_POSWIDTH];
				LaserTimer_TOvertime 		= NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH];	
			}
			printf("%s,%d,%s:set LaserTimer_TMate=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TMate);
			printf("%s,%d,%s:set LaserTimer_TOvertime=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TOvertime);
			//ACOUSTIC 初始化
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
				//能量大于设置功率的两倍
				SSET(R_ACOUSTIC_ENABLE);
				NVRAM0[EM_ACOUSTIC_TIME_STEP] = 1;//CW模式每次加减量1秒
				NVRAM0[EM_ACOUSTIC_ENERGY_STEP] = NVRAM0[EM_LASER_POWER_TOTAL] / 10;//CW模式每次加减量
				NVRAM0[EM_ACOUSTIC_TIME] = 1;//初始为1秒
				NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_TIME] * NVRAM0[EM_LASER_POWER_TOTAL] / 10;
				NVRAM0[EM_ACOUSTIC_TIME_MIN] = 1;//最小1秒
				NVRAM0[EM_ACOUSTIC_TIME_MAX] = NVRAM0[EM_ACOUSTIC_TIME_STEP] * 100;//最大100秒
				NVRAM0[EM_ACOUSTIC_ENERGY_MIN] = NVRAM0[EM_ACOUSTIC_TIME_MIN] * NVRAM0[EM_LASER_POWER_TOTAL] / 10;
				NVRAM0[EM_ACOUSTIC_ENERGY_MAX] = NVRAM0[EM_LASER_POWER_TOTAL] / 10 * NVRAM0[EM_ACOUSTIC_TIME_MAX];
			}	
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
				//脉冲大于1秒启用提示音
				if((NVRAM0[EM_LASER_POSWIDTH] >= 1000) && (NVRAM0[EM_LASER_NEGWIDTH] >= 1000)){//周期大于2000mS
					SSET(R_ACOUSTIC_ENABLE);
					NVRAM0[EM_ACOUSTIC_TIME_STEP] = (NVRAM0[EM_LASER_POSWIDTH] / 1000) + (NVRAM0[EM_LASER_NEGWIDTH] / 1000);
					NVRAM0[EM_ACOUSTIC_TIME] = NVRAM0[EM_ACOUSTIC_TIME_STEP];
					
					NVRAM0[EM_ACOUSTIC_ENERGY_STEP] = (NVRAM0[EM_LASER_POSWIDTH] / 1000) * NVRAM0[EM_LASER_POWER_TOTAL] / 10;
					NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
					
					NVRAM0[EM_ACOUSTIC_TIME_MIN] = NVRAM0[EM_ACOUSTIC_TIME_STEP];					
					NVRAM0[EM_ACOUSTIC_TIME_MAX] = NVRAM0[EM_ACOUSTIC_TIME_MIN] * 100;//最大100周期
					NVRAM0[EM_ACOUSTIC_ENERGY_MIN] = NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
					NVRAM0[EM_ACOUSTIC_ENERGY_MAX] = NVRAM0[EM_LASER_POWER_TOTAL] / 10 * NVRAM0[EM_ACOUSTIC_TIME_MAX];
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
			printf("%s,%d,%s:acoustic time step = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME_STEP]);
			printf("%s,%d,%s:acoustic time min = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME_MIN]);
			printf("%s,%d,%s:acoustic time max = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME_MAX]);
			
			printf("%s,%d,%s:acoustic energy step = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY_STEP]);
			printf("%s,%d,%s:acoustic energy min = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY_MIN]);
			printf("%s,%d,%s:acoustic energy max = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY_MAX]);
			
			//校正输出功率
			if(NVRAM0[EM_LASER_SELECT] == LASER_CHANNEL_1470){
				NVRAM0[SPREG_DAC_0] = fitLaserToCode(LASER_CHANNEL_1470, NVRAM0[EM_LASER_POWER_1470], &deviceConfig);
				UPDAC0();
			}
			else{
				NVRAM0[SPREG_DAC_1] = 0;
				UPDAC1();
			}
			if(NVRAM0[EM_LASER_SELECT] == LASER_CHANNEL_980){
				NVRAM0[SPREG_DAC_1] = fitLaserToCode(LASER_CHANNEL_980, NVRAM0[EM_LASER_POWER_980], &deviceConfig);
				UPDAC1();
			}
			else{
				NVRAM0[SPREG_DAC_0] = 0;
				UPDAC0();
			}
			
			//打开指示激光
			setRedLaserPwm(NVRAM0[DM_AIM_BRG] * deviceConfig.aimGain);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;	
			RRES(R_STANDBY_KEY_STNADBY_DOWN);
			standbyKeyValue(0);
			//页面切换
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//切换待机页面
			SetScreen(NVRAM0[EM_DC_PAGE]);
			readyPageTouchEnable(0);
			readyKeyValue(1);
			updateReadyDisplay();
		}
		if(LD(R_STANDBY_KEY_SCHEME_NEXT_DOWN)){
			if(NVRAM0[DM_SCHEME_NUM] < (CONFIG_HMI_SCHEME_NUM - 1)){
				ADDS1(DM_SCHEME_NUM);//+1
				loadScheme();//DM->EM
				updateStandbyDisplay();
			}
			vTaskDelay(100);
			RRES(R_STANDBY_KEY_SCHEME_NEXT_DOWN);
		}
		if(LD(R_STANDBY_KEY_SCHEME_LAST_DOWN)){
			if(NVRAM0[DM_SCHEME_NUM] > 0){
				DECS1(DM_SCHEME_NUM);//-1
				loadScheme();//DM->EM
				updateStandbyDisplay();	
			}
			vTaskDelay(100);
			RRES(R_STANDBY_KEY_SCHEME_LAST_DOWN);
		}
		if(LD(R_STANDBY_KEY_SCHEME_SAVE_DOWN)){//save down	
			saveScheme();//EM->FD
			FDSAV_ONE(NVRAM0[DM_SCHEME_NUM]);//FDRAM->EPROM
			vTaskDelay(100);
			RRES(R_STANDBY_KEY_SCHEME_SAVE_DOWN);			
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_PARA){//等待蜂鸣器
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_DONE;	
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_DONE){//2秒内脚踏无法使用
		T100MS(T100MS_READY_BEEM_DELAY, true, CONFIG_STANDBY_BEEM_DELAY_TIME);//启动计时器延时2000mS 打开计时器		
		if(LD(T_100MS_START * 16 + T100MS_READY_BEEM_DELAY) && LDB(R_FOOTSWITCH_PRESS)){
			T100MS(T100MS_READY_BEEM_DELAY, false, 3);
			readyPageTouchEnable(1);
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//切换待机页面
			SetScreen(NVRAM0[EM_DC_PAGE]);
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
					if(NVRAM0[EM_DC_PAGE] != GDDC_PAGE_WEAR_SAFETY){
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_WEAR_SAFETY;//切换待机页面
						SetScreen(NVRAM0[EM_DC_PAGE]);
					}
				}
				if(LDN(R_FOOTSWITCH_PRESS)){
					RRES(SPCOIL_BEEM_ENABLE);
					if(NVRAM0[EM_DC_PAGE] != GDDC_PAGE_READY){
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//切换待机页面
						SetScreen(NVRAM0[EM_DC_PAGE]);
					}
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
		if(LDP(R_READY_KEY_ACOUSTIC_ENERGY_ADD_DOWN)){
			addAcousticEnergy();
			updateAcousticDisplay();
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
		if(LD(R_READY_KEY_ACOUSTIC_ENERGY_ADD_UP)){
			RRES(R_READY_KEY_ACOUSTIC_ENERGY_ADD_DOWN);
			T10MS(T10MS_ACOUSTIC_ENERGY_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
			RRES(R_READY_KEY_ACOUSTIC_ENERGY_ADD_UP);
		}
		if(LDP(R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN)){
			decAcousticEnergy();
			updateAcousticDisplay();		
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
		if(LD(R_READY_KEY_ACOUSTIC_ENERGY_DEC_UP)){
			RRES(R_READY_KEY_ACOUSTIC_ENERGY_DEC_DOWN);
			T10MS(T10MS_ACOUSTIC_ENERGY_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
			RRES(R_READY_KEY_ACOUSTIC_ENERGY_DEC_UP);
		}
		if(LDP(R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN)){
			addAcousticTime();
			updateAcousticDisplay();
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
		if(LD(R_READY_KEY_ACOUSTIC_TIME_ADD_UP)){
			RRES(R_READY_KEY_ACOUSTIC_TIME_ADD_DOWN);
			T10MS(T10MS_ACOUSTIC_TIME_ADD_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
			RRES(R_READY_KEY_ACOUSTIC_TIME_ADD_UP);
		}
		if(LDP(R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN)){
			decAcousticTime();
			updateAcousticDisplay();
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
		if(LD(R_READY_KEY_ACOUSTIC_TIME_DEC_UP)){
			RRES(R_READY_KEY_ACOUSTIC_TIME_DEC_DOWN);
			T10MS(T10MS_ACOUSTIC_TIME_DEC_KEYDOWN_DELAY, false, CONFIG_KEY_REPEAT_DELAY_TIME);
			RRES(R_READY_KEY_ACOUSTIC_TIME_DEC_UP);
		}
		if(LD(R_STANDBY_KEY_STNADBY_UP) || LD(R_FAULT)){//回到等待状态
			EDLAR();//停止发射
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;
			UPDAC0();UPDAC1();
			//光比红激光
			setRedLaserPwm(0);
			T100MS(T100MS_READY_BEEM_DELAY, false, 3);//停止2秒计时器
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//切换待机页面
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
		if(LD(MR_FOOSWITCH_HAND_SWITCH)){//上升沿触发
			if(LDP(R_FOOTSWITCH_PRESS)){//发射激光
				sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
				NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_SPK_FREQ;					
				sPlcSpeakerFreq(NVRAM0[SPREG_BEEM_FREQ]);
				readyPageTouchEnable(0);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				SSET(SPCOIL_BEEM_ENABLE);//启动喇叭
			}
		}
		else{//电平触发
			if(LD(R_FOOTSWITCH_PRESS)){//发射激光	
				sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
				NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_SPK_FREQ;					
				sPlcSpeakerFreq(NVRAM0[SPREG_BEEM_FREQ]);
				readyPageTouchEnable(0);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				SSET(SPCOIL_BEEM_ENABLE);//启动喇叭
			}	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_EMITING){//发激光中READY页面
		if(LDP(SPCOIL_PS10MS)){
			ADLS1(EM_LASER_TRIG_TIME);
		}
		if(LDP(SPCOIL_PS10MS) && LaserFlag_Emiting){
			ADLS1(EM_LASER_RELEASE_TIME);
		}
		if(LDP(SPCOIL_PS100MS)){//每隔1S刷新累计时间和能量
			updateReleaseTimeEnergy();//更新累计发射时间和能量
		}
		if(LD(R_ENGINEER_MODE)){//工程模式显示调试信息	
			if(LDP(SPCOIL_PS1000MS)){		
				updateDebugInfo();
			}
		}		
		if(LD(R_STANDBY_KEY_STNADBY_UP) || LD(R_FAULT)){//回到等待状态
			EDLAR();//停止发射
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;
			UPDAC0();UPDAC1();
			setRedLaserPwm(0);
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//切换待机页面
			SetScreen(NVRAM0[EM_DC_PAGE]);//切换待机页面
			updateStandbyDisplay();
			standbyKeyValue(0);
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
				readyPageTouchEnable(1);
				printf("%s,%d,%s:hand switch mode,footswitch press,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		else{
			if(LDB(R_FOOTSWITCH_PRESS)){//关闭激光
				EDLAR(); 
				RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				readyPageTouchEnable(1);
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
		if(LD(R_OPTION_KEY_BEEM_VOLUME_ADD_DOWN)){
			if(NVRAM0[DM_BEEM_VOLUME] < CONFIG_BEEM_MAX_VOLUME){
				NVRAM0[DM_BEEM_VOLUME] += 1;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
				SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//更新进度条
			}
			RRES(R_OPTION_KEY_BEEM_VOLUME_ADD_DOWN);
		}
		if(LD(R_OPTION_KEY_BEEM_VOLUME_DEC_DOWN)){
			if(NVRAM0[DM_BEEM_VOLUME] > 0){
				NVRAM0[DM_BEEM_VOLUME] -= 1;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
				SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//更新进度条
			}
			RRES(R_OPTION_KEY_BEEM_VOLUME_DEC_DOWN);
		}
		if(LD(R_OPTION_KEY_LCD_BRG_ADD_DOWN)){					
			if(NVRAM0[DM_LCD_BRG] < CONFIG_LCD_MAX_DC){
				NVRAM0[DM_LCD_BRG] += 1;
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG , NVRAM0[DM_LCD_BRG], 1, 0);
				SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);
				SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
			}
			RRES(R_OPTION_KEY_LCD_BRG_ADD_DOWN);
		}
		if(LD(R_OPTION_KEY_LCD_BRG_DEC_DOWN)){					
			if(NVRAM0[DM_LCD_BRG] > CONFIG_LCD_MIN_DC){
				NVRAM0[DM_LCD_BRG] -= 1;
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG , NVRAM0[DM_LCD_BRG], 1, 0);
				SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);
				SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
			}
			RRES(R_OPTION_KEY_LCD_BRG_DEC_DOWN);
		}
		if(LD(R_OPTION_KEY_ENTER_INFORMATION_DOWN)){		
			updateInformationDisplay();		
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_INFORMATION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_INFORMATION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_OPTION_KEY_ENTER_INFORMATION_DOWN);
		}
		if(LD(R_OPTION_KEY_RESTORE_DOWN)){//恢复默认值
				//optionKeyEnable(false);//锁定按键
				loadDefault();
				lockPreScheme();
				NVFSAVE();//强制更新NVRAM
				updateOptionDisplay();//更新Option显示
				SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));//更新背光亮度
				//optionKeyEnable(true);//解锁按键
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
				SetScreen(NVRAM0[EM_DC_PAGE]);
				RRES(R_OPTION_KEY_RESTORE_DOWN);
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
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_0_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 0){
				NVRAM0[EM_SCHEME_NUM_TMP] = 0;
				updateSchemeInfo(0);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_0_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_1_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 1){
				NVRAM0[EM_SCHEME_NUM_TMP] = 1;
				updateSchemeInfo(1);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_1_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_2_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 2){
				NVRAM0[EM_SCHEME_NUM_TMP] = 2;
				updateSchemeInfo(2);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_2_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_3_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 3){
				NVRAM0[EM_SCHEME_NUM_TMP] = 3;
				updateSchemeInfo(3);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_3_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_4_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 4){
				NVRAM0[EM_SCHEME_NUM_TMP] = 4;
				updateSchemeInfo(4);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_4_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_5_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 5){
				NVRAM0[EM_SCHEME_NUM_TMP] = 5;
				updateSchemeInfo(5);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_5_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_6_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 6){
				NVRAM0[EM_SCHEME_NUM_TMP] = 6;
				updateSchemeInfo(6);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_6_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_7_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 7){
				NVRAM0[EM_SCHEME_NUM_TMP] = 7;
				updateSchemeInfo(7);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_7_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_8_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 8){
				NVRAM0[EM_SCHEME_NUM_TMP] = 8;
				updateSchemeInfo(8);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_8_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_9_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 9){
				NVRAM0[EM_SCHEME_NUM_TMP] = 9;
				updateSchemeInfo(9);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_9_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_10_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 10){
				NVRAM0[EM_SCHEME_NUM_TMP] = 10;
				updateSchemeInfo(10);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_10_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_11_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 11){
				NVRAM0[EM_SCHEME_NUM_TMP] = 11;
				updateSchemeInfo(11);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_11_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_12_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 12){
				NVRAM0[EM_SCHEME_NUM_TMP] = 12;
				updateSchemeInfo(12);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_12_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_13_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 13){
				NVRAM0[EM_SCHEME_NUM_TMP] = 13;
				updateSchemeInfo(13);
			}			
			RRES(R_SCHEME_KEY_SCHEME_SELECT_13_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_14_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 14){
				NVRAM0[EM_SCHEME_NUM_TMP] = 14;
				updateSchemeInfo(14);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_14_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_15_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 15){
				NVRAM0[EM_SCHEME_NUM_TMP] = 15;
				updateSchemeInfo(15);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_15_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_OK_DOWN)){//确定
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];//选定方案生效
			loadScheme();
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//切换待机页面						
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_OK_DOWN);
		}
		if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//取消
			//从FDRAM1中恢复FDRAM0
			memcpy((uint8_t*)FDRAM0, (uint8_t*)FDRAM1, (CONFIG_FDRAM_SIZE*2));
			loadScheme();//FD->EM
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//切换待机页面						
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		if(LD(R_SCHEME_KEY_RENAME_DOWN)){//改名
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//将EM_SCHEME_NUM_TMP指向的名称更新RENAME输入框
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM0 + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_RENAME_DOWN);
		}
		if(LD(R_SCHEME_KEY_NEXT_SCHEME)){//第一页->第二页
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
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_16_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 16;
				updateSchemeInfo(16);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_16_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_17_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 17){
				NVRAM0[EM_SCHEME_NUM_TMP] = 17;
				updateSchemeInfo(17);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_17_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_18_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 18){
				NVRAM0[EM_SCHEME_NUM_TMP] = 18;
				updateSchemeInfo(18);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_18_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_19_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 19){
				NVRAM0[EM_SCHEME_NUM_TMP] = 19;
				updateSchemeInfo(19);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_19_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_20_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 20){
				NVRAM0[EM_SCHEME_NUM_TMP] = 20;
				updateSchemeInfo(20);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_20_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_21_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 21){
				NVRAM0[EM_SCHEME_NUM_TMP] = 21;
				updateSchemeInfo(21);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_21_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_22_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 22){
				NVRAM0[EM_SCHEME_NUM_TMP] = 22;
				updateSchemeInfo(22);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_22_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_23_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 23){
				NVRAM0[EM_SCHEME_NUM_TMP] = 23;
				updateSchemeInfo(23);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_23_DOWN);
		}

		if(LD(R_SCHEME_KEY_SCHEME_SELECT_24_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 24){
				NVRAM0[EM_SCHEME_NUM_TMP] = 24;
				updateSchemeInfo(24);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_24_DOWN);
		}		
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_25_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 25){
				NVRAM0[EM_SCHEME_NUM_TMP] = 25;
				updateSchemeInfo(25);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_25_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_26_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 26){
				NVRAM0[EM_SCHEME_NUM_TMP] = 26;
				updateSchemeInfo(26);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_26_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_27_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 27){
				NVRAM0[EM_SCHEME_NUM_TMP] = 27;
				updateSchemeInfo(27);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_27_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_28_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 28){
				NVRAM0[EM_SCHEME_NUM_TMP] = 28;
				updateSchemeInfo(28);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_28_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_29_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 29){
				NVRAM0[EM_SCHEME_NUM_TMP] = 29;
				updateSchemeInfo(29);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_29_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_30_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 30){
				NVRAM0[EM_SCHEME_NUM_TMP] = 30;
				updateSchemeInfo(30);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_30_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_31_DOWN)){
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 31){
				NVRAM0[EM_SCHEME_NUM_TMP] = 31;
				updateSchemeInfo(31);
			}
			RRES(R_SCHEME_KEY_SCHEME_SELECT_31_DOWN);
		}
			
		if(LD(R_SCHEME_KEY_OK_DOWN)){//确定
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];
			loadScheme();
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//切换待机页面						
			SetScreen(NVRAM0[EM_DC_PAGE]);				
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_OK_DOWN);
		}
		if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//取消
			//从FDRAM1中恢复FDRAM0
			memcpy((uint8_t*)FDRAM0, (uint8_t*)FDRAM1, (CONFIG_FDRAM_SIZE*2));
			loadScheme();//FD->EM
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//切换待机页面						
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		if(LD(R_SCHEME_KEY_RENAME_DOWN)){//改名
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//将EM_SCHEME_NUM_TMP指向的名称更新RENAME输入框
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM0 + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_RENAME_DOWN);
		}
		if(LD(R_SCHEME_KEY_LAST_SCHEME)){//第二页->第一页
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
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			__set_PRIMASK(0);//关闭中断
			sPlcNvramClear();//清空NVRAM
			sPlcFdramClear();//清空FDRAM
			sPlcDeviceConfigClear();//清空config
			resetGddcHmi();
			softDelayMs(4000);//等待4秒
			REBOOT();	
		}
		else if(LD(R_SAVE_EPROM)){//储存配制到EPROM
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			__set_PRIMASK(0);//关闭中断
			sPlcNvramSave();//更新NVRAM
			sPlcFdramSave();//更新FDRAM
			saveDeviceConfig();//更新配制
			resetGddcHmi();
			softDelayMs(4000);//等待4秒
			REBOOT();	
		}
		else if(LD(R_CLEAR_CRC)){//清除固件CRC
			tmp8 = 0;
			__set_PRIMASK(0);//关闭中断
			epromWriteByte((CONFIG_EPROM_LCD_FW_CRC + 0), &tmp8);
			epromWriteByte((CONFIG_EPROM_LCD_FW_CRC + 1), &tmp8);
			epromWriteByte((CONFIG_EPROM_LCD_FW_CRC + 2), &tmp8);
			epromWriteByte((CONFIG_EPROM_LCD_FW_CRC + 3), &tmp8);
			
			epromWriteByte((CONFIG_EPROM_MCU_FW_CRC + 0), &tmp8);
			epromWriteByte((CONFIG_EPROM_MCU_FW_CRC + 1), &tmp8);
			epromWriteByte((CONFIG_EPROM_MCU_FW_CRC + 2), &tmp8);
			epromWriteByte((CONFIG_EPROM_MCU_FW_CRC + 3), &tmp8);
			resetGddcHmi();
			softDelayMs(4000);//等待4秒
			REBOOT();	
		}
		else if(LD(R_UPDATE_BOOTLOAD_REQ)){//更新Boot load请求
			SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, true);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
			if(updateBootloadReq()){
				SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, true);
				SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, true);
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, true);	
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, true);	
			}
			else{
				SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
				SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);	
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);	
				
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, true);
				
				SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);
			}
			RRES(R_UPDATE_BOOTLOAD_REQ);
		}
		else if(LD(R_UPDATE_BOOTLOAD_YES)){//执行Bootload更新	
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			confirmBootloadUpdate();
		}
		else if(LD(R_UPDATE_BOOTLOAD_NO)){//错误Bootload更新序列
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			
			exitBootloadUpdate();
			
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);
			
			SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, true);
			RRES(R_UPDATE_BOOTLOAD_NO);
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




