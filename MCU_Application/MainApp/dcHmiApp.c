#include "dcHmiApp.h"
/*****************************************************************************/
uint8_t hmiCmdBuffer[CMD_MAX_SIZE];//指令缓存
static int8_t standbyKeyTouchEnableStatus = -1;
uint16_t hmiCmdSize;//已缓冲的指令数
static uint8_t MsgId = 0xFF;//当前显示的信息ID
uint8_t CcmRamBuf[0xFFFF] __attribute__ ((at(CCMDATARAM_BASE)));//文件读写缓冲
uint32_t newBootloadCrc32;
// 创建风扇控制器实例
FanController FanTec;
/*****************************************************************************/
FRESULT retUsbH;
FATFS	USBH_fatfs;
FIL BootLoadFile;//FATFS File Object 记录信息
extern ApplicationTypeDef Appli_state;
static uint16_t legalUsbDev[5] = {0x16C0, 0, 0, 0, 0};
static uint16_t legalUsbPid[5] = {0x05E2, 0, 0, 0, 0};
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
#if defined(LDR2P1_G5_A1_20250731_DUAL) || defined(LDR2P1_G5_A1_20250731_TRIP)
	SET_USB_FS_SEL_LEGACY_ON;
	SET_USB_FS_PSON_LEGACY_ON;
	SET_USB_HS_PSON_LEGACY_OFF;
#endif
#if defined (LDR2P1_G5_A1_20250910_DUAL) || defined(LDR2P1_G5_A1_20250910_TRIP)
	SET_USBA0_SEL_OFF;
	SET_USBA1_SEL_ON;//切换为外部USB
	SET_USBA0_PSON_ON;
	SET_USBA1_PSON_OFF;
#endif
	printf("Bootloader:switch ext usb,power off int usb power\n");
	vTaskDelay(2000);
	//挂载USB DISK FAT文件系统
	retUsbH = f_mount(&USBH_fatfs, (const TCHAR*)FATFS_ROOT, 1);
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
	HAL_FLASH_Unlock();//解锁FLASH锁定
	softDelayMs(3000);
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGSERR | FLASH_FLAG_WRPERR);
	if (FLASH_If_EraseBootload() != 0x00){//擦除BOOTLOAD 失败
		printf("BootLoader:Erase bootload fail, GameOver!!!!!\n");
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Erase bootload fail,Game Over!"));
		return;
	}
	softDelayMs(1000);
	if(checkBlank(BOOTLOADER_FLASH_START_ADDRESS, BOOTLOADER_FLASH_SIZE)){//FLASH 查空
		printf("Bootloader:Check mcu booload blank sucess.\n");
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Erase bootload sucessful..."));
	}
	else{
		printf("Bootloader:Check mcu booload blank not empty!\n");
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Erase bootload fail,Game Over!"));
		return;
	}
	softDelayMs(2000);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Start update new bootload..."));
	for(i = 0; i < BOOTLOADER_FLASH_SIZE; i += 4){
		if(FLASH_lf_WriteBootload((BOOTLOADER_FLASH_START_ADDRESS + i), *(uint32_t *) (CcmRamBuf + i)) != 0x00){
			softDelayMs(100);
			printf("BootLoader:Write mcu bootload fail,GameOver!!!!!\n");//写入FLASH错误
		}
	}
	HAL_FLASH_Lock();
	printf("BootLoader:Update new bootload done...\n");
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)"Update new bootload done...");
	softDelayMs(1000);
	//检查已写入的Bootload是否正确
	printf("BootLoader:Start checksum new bootload...\n");
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Start checksum new bootload..."));
	BootloadCrc = getOriginBootloadCrc();
	softDelayMs(1000);
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
	softDelayMs(100);
	REBOOT();
	while(1);
}

void exitBootloadUpdate(void){//退出Bootload更新
	f_close(&BootLoadFile);
	f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
	vTaskDelay(300);
	//切换回内部USB
#if defined(LDR2P1_G5_A1_20250731_DUAL) || defined(LDR2P1_G5_A1_20250731_TRIP)
	SET_USB_FS_SEL_LEGACY_OFF;
	SET_USB_FS_PSON_LEGACY_ON;
	SET_USB_HS_PSON_LEGACY_OFF;
#endif
	
#if defined (LDR2P1_G5_A1_20250910_DUAL) || defined(LDR2P1_G5_A1_20250910_TRIP)
	SET_USBA0_SEL_OFF;
	SET_USBA1_SEL_ON;//切换为内部USB
	SET_USBA0_PSON_ON;//打开内部USB供电
#endif
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)(""));
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);
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

void updateDiagnosisCaliInfo(void){//更新功率校准动态信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%4.1fC", (NVRAM0[EM_LASER_A_DIODE_TEMP] / 10.0F));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_DIODE_TEMP, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%4.1fC", (NVRAM0[EM_HWATER_TEMP] / 10.0F));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_HWATER_TEMP, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%4.1fC", (NVRAM0[EM_CWATER_TEMP] / 10.0F));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CWATER_TEMP, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1f%%", NVRAM0[EM_TPID0_OUT] * 100.0F / CONFIG_DAC_MAXBIT_CH8);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_PID0, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1f%%", NVRAM0[EM_TPID1_OUT] * 100.0F / CONFIG_DAC_MAXBIT_CH9);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_PID1, (uint8_t*)dispBuf);
		
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH0_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CDISP_CH0, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH1_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CDISP_CH1, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH2_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CDISP_CH2, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH3_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CDISP_CH3, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH4_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CDISP_CH4, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH5_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CDISP_CH5, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH6_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CDISP_CH6, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH7_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CDISP_CH7, (uint8_t*)dispBuf);

}

void updateDebugInfo(void){//更新Standby调试信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1) ||\
		defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
	sprintf(dispBuf, "LT:%05d,HT:%05d,MT:%05d,FPD:%05d,LPD:%05d,TC:%05d", \
	NVRAM0[EM_LASER_A_DIODE_TEMP], NVRAM0[EM_HT0_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[SPREG_ADC_9], NVRAM0[SPREG_ADC_10], NVRAM0[SPREG_DAC_7]);
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
#endif
#if defined(LYPE_MCU_1V0_20260106)
	sprintf(dispBuf, "LT:%05d,WHT:%05d,WCT%05d,AT%05d,MT:%05d,FPD:%05d,LPD:%05d,PID:%05d", \
	NVRAM0[EM_LASER_A_DIODE_TEMP], NVRAM0[EM_HWATER_TEMP], NVRAM0[EM_CWATER_TEMP], NVRAM0[EM_HDC1080_TEMP], NVRAM0[EM_MCU_TEMP], \
	NVRAM0[EM_LASER_FPD], NVRAM0[EM_LASER_LPD], NVRAM0[EM_TPID0_OUT]);
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
#endif
}
void updateDiagnosisCali(void){//跟新诊断-校准页面静态信息
	uint8_t i;
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	//更新功率校正表
	for(i = 0;i < 20; i++){//CH0
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr0[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_0P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH1
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr1[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_1P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH2
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr2[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_2P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH3
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr3[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_3P5 + i), (uint8_t*)dispBuf);
	}	
	for(i = 0;i < 20; i++){//CH4
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr4[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_4P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH5
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr5[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_5P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH6
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr6[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_6P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH7
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr7[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DISGNOSIS_CALI_TEXTDISPLAY_7P5 + i), (uint8_t*)dispBuf);
	}
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CSET_CH0, (uint8_t*)dispBuf);
	
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CSET_CH1, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CSET_CH2, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CSET_CH3, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CSET_CH4, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CSET_CH5, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CSET_CH6, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXTDISPLAY_CSET_CH7, (uint8_t*)dispBuf);
}



void updateDiagnosis(void){//更新诊断信信息
	//uint8_t i;
	//char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	//从NVRAM中更新文本框	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_YEAR , deviceConfig.mfg_year, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_MONTH , deviceConfig.mfg_month, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_DAY , deviceConfig.mfg_day, 1, 0);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_SN, (uint8_t*)deviceConfig.serialNumber);
	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_RED_LED_DC , deviceConfig.redLedDc, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_GREEN_LED_DC , deviceConfig.greenLedDc, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_BLUE_LED_DC , deviceConfig.blueLedDc, 1, 0);
	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_SET_AIM_GAIN, deviceConfig.redAimGain, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIBER_DETECT, deviceConfig.fiberDetect, 1, 0);
	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_DIODE_A_TEMP, deviceConfig.laserDiodeA_Temp, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_DIODE_B_TEMP, deviceConfig.laserDiodeB_Temp, 1, 0);
	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);	
	SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);	
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);

	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, false);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)"");
	
	if(deviceConfig.normalOpenInterLock == 0){
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_OPEN_ILOCK, true);
	}
	else{
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_OPEN_ILOCK, false);
	}
	
}
void updateDiagnosisInfoRaw(void){//更新诊断信息-RAW值
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "A00-A15:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_ADC_0], NVRAM0[SPREG_ADC_1], NVRAM0[SPREG_ADC_2], NVRAM0[SPREG_ADC_3], \
	NVRAM0[SPREG_ADC_4], NVRAM0[SPREG_ADC_5], NVRAM0[SPREG_ADC_6], NVRAM0[SPREG_ADC_7], \
	NVRAM0[SPREG_ADC_8], NVRAM0[SPREG_ADC_9], NVRAM0[SPREG_ADC_10], NVRAM0[SPREG_ADC_11], \
	NVRAM0[SPREG_ADC_12], NVRAM0[SPREG_ADC_13], NVRAM0[SPREG_ADC_14], NVRAM0[SPREG_ADC_15]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO0, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "A16-A31:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_ADC_16], NVRAM0[SPREG_ADC_17], NVRAM0[SPREG_ADC_18], NVRAM0[SPREG_ADC_19], \
	NVRAM0[SPREG_ADC_20], NVRAM0[SPREG_ADC_21], NVRAM0[SPREG_ADC_22], NVRAM0[SPREG_ADC_23], \
	NVRAM0[SPREG_ADC_24], NVRAM0[SPREG_ADC_25], NVRAM0[SPREG_ADC_26], NVRAM0[SPREG_ADC_27], \
	NVRAM0[SPREG_ADC_28], NVRAM0[SPREG_ADC_29], NVRAM0[SPREG_ADC_30], NVRAM0[SPREG_ADC_31]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO1, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "A32-A47:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_ADC_32], NVRAM0[SPREG_ADC_33], NVRAM0[SPREG_ADC_34], NVRAM0[SPREG_ADC_35], \
	NVRAM0[SPREG_ADC_36], NVRAM0[SPREG_ADC_37], NVRAM0[SPREG_ADC_38], NVRAM0[SPREG_ADC_39], \
	NVRAM0[SPREG_ADC_40], NVRAM0[SPREG_ADC_41], NVRAM0[SPREG_ADC_42], NVRAM0[SPREG_ADC_43], \
	NVRAM0[SPREG_ADC_44], NVRAM0[SPREG_ADC_45], NVRAM0[SPREG_ADC_46], NVRAM0[SPREG_ADC_47]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO2, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "A48-A55:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_ADC_48], NVRAM0[SPREG_ADC_49], NVRAM0[SPREG_ADC_50], NVRAM0[SPREG_ADC_51], \
	NVRAM0[SPREG_ADC_52], NVRAM0[SPREG_ADC_53], NVRAM0[SPREG_ADC_54], NVRAM0[SPREG_ADC_55]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO3, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "A56-A63:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_ADC_56], NVRAM0[SPREG_ADC_57], NVRAM0[SPREG_ADC_58], NVRAM0[SPREG_ADC_59], \
	NVRAM0[SPREG_ADC_60], 0, 0, 0);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO4, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "D0-17:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_DAC_0], NVRAM0[SPREG_DAC_1], NVRAM0[SPREG_DAC_2], NVRAM0[SPREG_DAC_3], \
	NVRAM0[SPREG_DAC_4], NVRAM0[SPREG_DAC_5], NVRAM0[SPREG_DAC_6], NVRAM0[SPREG_DAC_7], \
	NVRAM0[SPREG_DAC_8], NVRAM0[SPREG_DAC_9], NVRAM0[SPREG_DAC_10], NVRAM0[SPREG_DAC_11], \
	NVRAM0[SPREG_DAC_12], NVRAM0[SPREG_DAC_13], NVRAM0[SPREG_DAC_14], NVRAM0[SPREG_DAC_15], \
	NVRAM0[SPREG_DAC_16], NVRAM0[SPREG_DAC_17]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO5, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "X0-31:%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d", \
	LD(X_START * 16 +  0), LD(X_START * 16 +  1), LD(X_START * 16 +  2) ,LD(X_START * 16 +  3), \
	LD(X_START * 16 +  4), LD(X_START * 16 +  5), LD(X_START * 16 +  6) ,LD(X_START * 16 +  7), \
	LD(X_START * 16 +  8), LD(X_START * 16 +  9), LD(X_START * 16 + 10) ,LD(X_START * 16 + 11), \
	LD(X_START * 16 + 12), LD(X_START * 16 + 13), LD(X_START * 16 + 14) ,LD(X_START * 16 + 15), \
	LD(X_START * 16 + 16), LD(X_START * 16 + 17), LD(X_START * 16 + 18) ,LD(X_START * 16 + 19), \
	LD(X_START * 16 + 20), LD(X_START * 16 + 21), LD(X_START * 16 + 22) ,LD(X_START * 16 + 23), \
	LD(X_START * 16 + 24), LD(X_START * 16 + 25), LD(X_START * 16 + 26) ,LD(X_START * 16 + 27), \
	LD(X_START * 16 + 28), LD(X_START * 16 + 29), LD(X_START * 16 + 30) ,LD(X_START * 16 + 31));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO6, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "Y0-31:%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d,%1d", \
	LD(Y_START * 16 +  0), LD(Y_START * 16 +  1), LD(Y_START * 16 +  2) ,LD(Y_START * 16 +  3), \
	LD(Y_START * 16 +  4), LD(Y_START * 16 +  5), LD(Y_START * 16 +  6) ,LD(Y_START * 16 +  7), \
	LD(Y_START * 16 +  8), LD(Y_START * 16 +  9), LD(Y_START * 16 + 10) ,LD(Y_START * 16 + 11), \
	LD(Y_START * 16 + 12), LD(Y_START * 16 + 13), LD(Y_START * 16 + 14) ,LD(Y_START * 16 + 15), \
	LD(Y_START * 16 + 16), LD(Y_START * 16 + 17), LD(Y_START * 16 + 18) ,LD(Y_START * 16 + 19), \
	LD(Y_START * 16 + 20), LD(Y_START * 16 + 21), LD(Y_START * 16 + 22) ,LD(Y_START * 16 + 23), \
	LD(Y_START * 16 + 24), LD(Y_START * 16 + 25), LD(Y_START * 16 + 26) ,LD(Y_START * 16 + 27), \
	LD(Y_START * 16 + 28), LD(Y_START * 16 + 29), LD(Y_START * 16 + 30) ,LD(Y_START * 16 + 31));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO7, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "DIODE-AT:%05d,COUPLE-AT:%05d,CRYSTAL-AT0:%05d,CRYSTAL-AT01:%05d", \
	NVRAM0[EM_LASER_A_DIODE_TEMP], NVRAM0[EM_LASER_A_COUPLER_TEMP], NVRAM0[EM_LASER_A_CRYST0_TEMP], NVRAM0[EM_LASER_A_CRYST1_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO8, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "DIODE-BT:%05d,COUPLE-BT:%05d,CRYSTAL-BT0:%05d,CRYSTAL-BT01:%05d", \
	NVRAM0[EM_LASER_B_DIODE_TEMP], NVRAM0[EM_LASER_B_COUPLER_TEMP], NVRAM0[EM_LASER_B_CRYST0_TEMP], NVRAM0[EM_LASER_B_CRYST1_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO9, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "HT1:%05d,HT2:%05d,HT3:%05d,WHT:%05d,WCT:%05d", \
	NVRAM0[EM_HT1_TEMP], NVRAM0[EM_HT2_TEMP], NVRAM0[EM_HT3_TEMP], NVRAM0[EM_HWATER_TEMP], NVRAM0[EM_CWATER_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO10, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "AT0:%05d,AT1:%05d,MT:%05d,BT:%05d", \
	NVRAM0[EM_AMBIENT0_TEMP], NVRAM0[EM_AMBIENT1_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[EM_MBAT_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO11, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "FAN0-3 GET:%05d,%05d,%05d,%05d,FAN0-3 SET:%05d,%05d,%05d,%05d", \
	NVRAM0[EM_FAN0_GET_SPEED], NVRAM0[EM_FAN1_GET_SPEED], NVRAM0[EM_FAN2_GET_SPEED], NVRAM0[EM_FAN3_GET_SPEED], \
	NVRAM0[EM_FAN0_SET_SPEED], NVRAM0[EM_FAN1_SET_SPEED], NVRAM0[EM_FAN2_SET_SPEED], NVRAM0[EM_FAN3_SET_SPEED]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXTDISPLAY_INFO12, (uint8_t*)dispBuf);
}

void updateDiagnosisInfo(void){//更新诊断信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "FSNC:%1d,FSNO:%1d,ESTOP:%d,ILOCK:%1d,FB:%1d,FPD:%05d,LPD:%05d", \
	LD(X_FOOTSWITCH_NC), LD(X_FOOTSWITCH_NO), LD(X_ESTOP_NC), LD(X_INTERLOCK_NC), LD(X_FIBER_PROBE),NVRAM0[SPREG_ADC_47],NVRAM0[SPREG_ADC_48]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO0, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "LDT:%05d,COT:%05d,CRYT0:%05d,CRYT1:%05d,HT0:%05d,HT1:%05d,HT2:%05d,HT3:%05d", \
	NVRAM0[EM_LASER_A_DIODE_TEMP], NVRAM0[EM_LASER_A_COUPLER_TEMP], NVRAM0[EM_LASER_A_CRYST0_TEMP], NVRAM0[EM_LASER_A_CRYST1_TEMP], \
	NVRAM0[EM_HT0_TEMP], NVRAM0[EM_HT1_TEMP], NVRAM0[EM_HT2_TEMP], NVRAM0[EM_HT3_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO1, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "WHOTT:%05d,WCOLT:%05d,MCUT:%05d,BATT:%05d", \
	NVRAM0[EM_HWATER_TEMP], NVRAM0[EM_CWATER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[EM_MBAT_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO2, (uint8_t*)dispBuf);
		
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "FAN:%05d,WFSW NC:%1d,WFSW NO:%1d", \
	NVRAM0[EM_FAN0_SET_SPEED], LD(SPCOIL_WFSWITCH_PLUG), LD(SPCOIL_WFSWITCH_NO));
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO3, (uint8_t*)dispBuf);
}

void updateSchemeDetail(int16_t classify, int16_t index){//更新选项界面方案名称
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	//uint8_t index;
	//index = NVRAM0[EM_SCHEME_NUM_TMP];
	switch(classify){
#if defined(APP_CONFIG_WAVE_1470_650) || defined(APP_CONFIG_WAVE_1470_980_650)
		case SCHEME_PHLEBOLOGY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- Phlebology");
			if(strlen((char*)sPhlebology[0].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sPhlebology[0].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sPhlebology[1].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sPhlebology[1].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sPhlebology[2].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sPhlebology[2].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
			}
			//方案3-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
			BatchEnd();

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);//禁止修改名称
			break;			
		}
		case SCHEME_PROCTOLOGY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- Proctology");
			if(strlen((char*)sProctology[0].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[0].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[1].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[1].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[2].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[2].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[3].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[3].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[4].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[4].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[5].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[5].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
			}	
			//方案6-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
			BatchEnd();

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);	

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);
			break;
		}
		case SCHEME_GYNECOLOGY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- Gynecology");
			if(index < 16){//方案0-15
				if(strlen((char*)sGynecology[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[8].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[8].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[9].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[9].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[10].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[10].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[11].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[11].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[12].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[12].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[13].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[13].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[14].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[14].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[15].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[15].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, (uint8_t*)dispBuf);
				}			
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, true);
				BatchEnd();
				
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, true);
				BatchEnd();
				
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
				
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,true);					
			}
			else{
				if(strlen((char*)sGynecology[16].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[16].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[17].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[17].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
				}				
				if(strlen((char*)sGynecology[18].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[18].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[19].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[19].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[20].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[20].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[21].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[21].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[22].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[22].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
				}
				
				//方案5-15禁止选择
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
				BatchEnd();
				
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
				BatchEnd();

				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,true);
					
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);
			}
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);
			break;				
		}
		case SCHEME_ENT:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- ENT");
			if(strlen((char*)sENT[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[8].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[8].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[9].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[9].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[10].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[10].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[11].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[11].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[12].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[12].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[13].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[13].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[14].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[15].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[15].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[15].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, (uint8_t*)dispBuf);
			}	
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, true);
			BatchEnd();
					
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, true);
			BatchEnd();
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
					
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);		
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);
			break;
		}
#endif
		case SCHEME_NEUROSURGERY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- Neurosurgery");
#if defined(APP_CONFIG_WAVE_1470_980_650)
			if(strlen((char*)sNeurosurgery[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
			}
			//方案4-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
			BatchEnd();
#endif
#if defined(APP_CONFIG_WAVE_1470_650)
			if(strlen((char*)sNeurosurgery[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
			}
			//方案4-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, false);		
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
			BatchEnd();
#endif
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);	

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);
			break;
		}
		case SCHEME_DERMATOLOGY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- Dermatology");
			if(strlen((char*)sDermatology[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sDermatology[8].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[8].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
			}	
			//方案8-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);			
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
			BatchEnd();

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);		

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);
			break;
		}
		case SCHEME_LIPOSUCTION:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- Liposuction");
			if(strlen((char*)sLiposuction[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
			}				
			if(strlen((char*)sLiposuction[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
			}		
			//方案7-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, true);	
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);			
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
			BatchEnd();

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);	
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);
			break;
		}
		case SCHEME_DENTISTRY:{	
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- Dentistry");
			if(index < 16){//方案0-15
				if(strlen((char*)sDentistry[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[8].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[8].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[9].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[9].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[10].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[10].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[11].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[11].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[12].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[12].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[13].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[13].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[14].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[14].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[15].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[15].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, (uint8_t*)dispBuf);
				}	
				//方案0-15禁止选择
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, true);				
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, true);
				BatchEnd();
			
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);		
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);			
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, true);			
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, true);
				BatchEnd();

				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
					
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,true);	

				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);				
			}
			else{
				if(strlen((char*)sDentistry[16].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[16].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
				}	
				if(strlen((char*)sDentistry[17].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[17].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[18].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[18].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[19].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[19].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[20].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[20].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[21].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[21].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[22].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[22].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
				}
				//方案0-15禁止选择
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, true);				
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
				BatchEnd();
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);		
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);			
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, true);			
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
				BatchEnd();			
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,true);
					
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);	

				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);
			}
			break;
		}
		case SCHMEM_THERAPY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- Therapy");
#if defined(APP_CONFIG_WAVE_1470_980_650)
			if(strlen((char*)sTherapy[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sTherapy[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
			}		
			//方案8-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
			BatchEnd();
#endif
#if defined(APP_CONFIG_WAVE_1470_650)
			if(strlen((char*)sTherapy[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sTherapy[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
			}	
			//方案8-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, false);		
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, false);
			BatchEnd();
#endif
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);	

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, false);
			break;
		}
		case SCHEME_CUSTIOM:{
#if defined(APP_CONFIG_WAVE_1470_980_650)
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "- Custom");
#endif
			
#if defined(APP_CONFIG_WAVE_1470_650)
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_CLASSIFY, "");
#endif
			
			if(index < 16){
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_0])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_0], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_1])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_1], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_2])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_2], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_3])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_3], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_4])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_4], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_5])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_5], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_6])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_6], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_7])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_7], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_8])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_8], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_9])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_9], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_10])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_10], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_11])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_11], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_12])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_12], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_13])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_13], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_14])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_14], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_15])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_15], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, (uint8_t*)dispBuf);
				}
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,false);
				
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,true);	
			}
			else{
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_16])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_16], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_17])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_17], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_18])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_18], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_19])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_19], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_20])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_20], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_21])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_21], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_22])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_22], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_23])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_23], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_24])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_24], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_25])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_25], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_26])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_26], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_27])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_27], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_28])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_28], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_29])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_29], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_30])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_30], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_31])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_31], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, (uint8_t*)dispBuf);
				}
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_LAST_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_LAST_PAGE,true);
				
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_NEXT_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_KEY_NEXT_PAGE,false);	
			}		
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_6, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_7, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_8, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_9, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_10, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_11, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_12, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_13, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_14, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_KEY_SELECT_15, true);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_7, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_8, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_9, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_10, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_11, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_12, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_13, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_14, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_TEXTDISPLAY_SCHEME_15, true);
			BatchEnd();
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_KEY_RENAME, true);
			break;
		}
		default:{break;}
	}
	unselectSchemeAll();
	SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)"");
	SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)"");
}

void updateInformationDisplay(void){//更新信息界面显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	char *pMain, *pMonir;
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_TPYE, (uint8_t*)INFO_MSG_TYPE);	
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_TPYE, (uint8_t*)INFO_MSG_TYPE);	

	memset(dispBuf, 0x0,sizeof(dispBuf));
	sprintf(dispBuf, "SN: %s", (uint8_t*)deviceConfig.serialNumber);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_SN, (uint8_t*)dispBuf);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_LASER_WAVELENGTH, (uint8_t*)INFO_MSG_WAVELENGTH);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_MAX_LASER_POWER, (uint8_t*)INFO_MSG_LASER_POWER);
	
	memset(dispBuf, 0x0,sizeof(dispBuf));
	sprintf(dispBuf, "%s", (char*)INFO_MSG_HW_VERSION);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_HARDWAR_VERSIONE, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0,sizeof(dispBuf));
	pMain = (char*)(BOOTLOAD_MAIN_ADDRESS);
	pMonir = (char*)(BOOTLAOD_MINOR_ADDRESS);
	if((*pMain >='0' && *pMain <= '9') && (*pMonir >= '0' && *pMonir <= '9')){
		sprintf(dispBuf, "%s-%s:%s  Bootload Ver: %c.%c", (char*)INFO_MSG_SW_VERSION, __DATE__, __TIME__, *pMain, *pMonir);
		SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_SOFTWARE_VERSION, (uint8_t*)dispBuf);
	}
	else{
		sprintf(dispBuf, "%s; Bootload Ver: 1.0", (char*)INFO_MSG_SW_VERSION);
		SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_SOFTWARE_VERSION, (uint8_t*)dispBuf);
	}
	
	memset(dispBuf, 0x0,sizeof(dispBuf));
	sprintf(dispBuf, "MANUFACTURE DATE: %4d-%2d-%2d", deviceConfig.mfg_year, deviceConfig.mfg_month, deviceConfig.mfg_day);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_MANUFACTURE_DATE, (uint8_t*)dispBuf);			
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "UUID: %08X%08X%08X", UniqueId[0], UniqueId[1], UniqueId[2]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFO_TEXTDISPLAY_UUID, (uint8_t*)dispBuf);	
}
void returnStandbyDisplay(void){//返回STANDBY界面
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
			
			case MSG_HUMIDITY_ABNORMAL:{
				pstr = WARM_MSG_HUMIDITY_ABNORMAL;
				break;
			}	
			case MSG_HWATER_ABNORMAL:{
				pstr = WARM_MSG_HWATER_ABNORMAL;
				break;
			}
			case MSG_CWATER_ABNORMAL:{
				pstr = WARM_MSG_CWATER_ABNORMAL;
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

void updateSchemeInfo(int16_t classify, int16_t index){//更新SCHEME 详细参数
	char dispBuf1[CONFIG_DCHMI_DISKBUF_SIZE], dispBuf2[CONFIG_DCHMI_DISKBUF_SIZE];
	int16_t mode, select;
	int16_t	power_ch0, power_ch1, power_red, posWidth, negWidth;
	power_ch0 &= power_ch0;
	power_ch1 &= power_ch1;
	memset(dispBuf1, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);	
	memset(dispBuf2, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(classify){
#if defined(APP_CONFIG_WAVE_1470_650) || defined(APP_CONFIG_WAVE_1470_980_650)
		case SCHEME_PHLEBOLOGY:{
			if(index > (CONFIG_PHLEBOLOGY_SIZE - 1)){
				index = (CONFIG_PHLEBOLOGY_SIZE - 1);
			}
			select = sPhlebology[index].channel;
			power_ch0 = sPhlebology[index].power_ch0;
			power_ch1 = sPhlebology[index].power_ch1;
			power_red = sPhlebology[index].power_red;
			posWidth = sPhlebology[index].poswidth;
			negWidth = sPhlebology[index].negwidth;
			mode = sPhlebology[index].pulse_mode;				
			break;
		}
		case SCHEME_PROCTOLOGY:{
			if(index > (CONFIG_PROCTOLOGY_SIZE - 1)){
				index = (CONFIG_PROCTOLOGY_SIZE - 1);
			}
			select = sProctology[index].channel;
			power_ch0 = sProctology[index].power_ch0;
			power_ch1 = sProctology[index].power_ch1;
			power_red = sProctology[index].power_red;
			posWidth = sProctology[index].poswidth;
			negWidth = sProctology[index].negwidth;
			mode = sProctology[index].pulse_mode;	
			break;
		}
		case SCHEME_GYNECOLOGY:{
			if(index > (CONFIG_GYNECOLOGY_SIZE - 1)){
				index = (CONFIG_GYNECOLOGY_SIZE - 1);
			}
			select = sGynecology[index].channel;
			power_ch0 = sGynecology[index].power_ch0;
			power_ch1 = sGynecology[index].power_ch1;
			power_red = sGynecology[index].power_red;
			posWidth = sGynecology[index].poswidth;
			negWidth = sGynecology[index].negwidth;
			mode = sGynecology[index].pulse_mode;		
			break;
		}
		case SCHEME_ENT:{
			if(index > (CONFIG_ENT_SIZE - 1)){
				index = (CONFIG_ENT_SIZE - 1);
			}
			select = sENT[index].channel;
			power_ch0 = sENT[index].power_ch0;
			power_ch1 = sENT[index].power_ch1;
			power_red = sENT[index].power_red;
			posWidth = sENT[index].poswidth;
			negWidth = sENT[index].negwidth;
			mode = sENT[index].pulse_mode;	
			break;
		}
		case SCHEME_NEUROSURGERY:{
			if(index > (CONFIG_NEUROSURGERY_SIZE - 1)){
				index = (CONFIG_NEUROSURGERY_SIZE - 1);
			}
			select = sNeurosurgery[index].channel;
			power_ch0 = sNeurosurgery[index].power_ch0;
			power_ch1 = sNeurosurgery[index].power_ch1;
			power_red = sNeurosurgery[index].power_red;
			posWidth = sNeurosurgery[index].poswidth;
			negWidth = sNeurosurgery[index].negwidth;
			mode = sNeurosurgery[index].pulse_mode;
			break;
		}
		case SCHEME_DERMATOLOGY:{
			if(index > (CONFIG_DERMATOLOGY_SIZE - 1)){
				index = (CONFIG_DERMATOLOGY_SIZE - 1);
			}
			select = sDermatology[index].channel;
			power_ch0 = sDermatology[index].power_ch0;
			power_ch1 = sDermatology[index].power_ch1;
			power_red = sDermatology[index].power_red;
			posWidth = sDermatology[index].poswidth;
			negWidth = sDermatology[index].negwidth;
			mode = sDermatology[index].pulse_mode;
			break;
		}
		case SCHEME_LIPOSUCTION:{
			if(index > (CONFIG_LIPOSUCTION_SIZE - 1)){
				index = (CONFIG_LIPOSUCTION_SIZE - 1);
			}
			select = sLiposuction[index].channel;
			power_ch0 = sLiposuction[index].power_ch0;
			power_ch1 = sLiposuction[index].power_ch1;
			power_red = sLiposuction[index].power_red;
			posWidth = sLiposuction[index].poswidth;
			negWidth = sLiposuction[index].negwidth;
			mode = sLiposuction[index].pulse_mode;
			break;		
		}
		case SCHEME_DENTISTRY:{
			if(index > (CONFIG_DENTISRTY_SIZE - 1)){
				index = (CONFIG_DENTISRTY_SIZE - 1);
			}
			select = sDentistry[index].channel;
			power_ch0 = sDentistry[index].power_ch0;
			power_ch1 = sDentistry[index].power_ch1;
			power_red = sDentistry[index].power_red;
			posWidth = sDentistry[index].poswidth;
			negWidth = sDentistry[index].negwidth;
			mode = sDentistry[index].pulse_mode;
			break;			
		}
		case SCHMEM_THERAPY:{
			if(index > (CONFIG_THERAPY_SIZE - 1)){
				index = (CONFIG_THERAPY_SIZE - 1);
			}
			select = sTherapy[index].channel;
			power_ch0 = sTherapy[index].power_ch0;
			power_ch1 = sTherapy[index].power_ch1;
			power_red = sTherapy[index].power_red;
			posWidth = sTherapy[index].poswidth;
			negWidth = sTherapy[index].negwidth;
			mode = sTherapy[index].pulse_mode;
			break;				
		}
#endif
		case SCHEME_CUSTIOM:{
			if(index < 0)
				index = 0;
			if(index > CONFIG_HMI_SCHEME_NUM)
				index = CONFIG_HMI_SCHEME_NUM;		
			select = FDRAM1[index * 64 + FD_LASER_CHANNEL_SELECT];	
			power_ch0 = FDRAM1[index * 64 + FD_LASER_POWER_CH0];
			power_ch1 = FDRAM1[index * 64 + FD_LASER_POWER_CH1];
			power_red = FDRAM1[index * 64 + FD_LASER_POWER_RED];
			posWidth = FDRAM1[index * 64 + FD_LASER_POSWIDTH];
			negWidth = FDRAM1[index * 64 + FD_LASER_NEGWIDTH];
			mode = FDRAM1[index * 64 + FD_LASER_PULSE_MODE];
			break;
		}
		default:break;
	}
	switch(select){
		case LASER_CHANNEL_CH0:{
#if defined(APP_CONFIG_WAVE_1470_650) || defined(APP_CONFIG_WAVE_1470_980_650)
			sprintf(dispBuf1, "1470nm: %3.1fW", ((float)power_ch0 / 10.0F));
#endif

#if defined(APP_CONFIG_WAVE_1940_650)
			sprintf(dispBuf1, "1940nm: %3.1fW", ((float)power_ch0 / 10.0F));
#endif	

#if defined(APP_CONFIG_WAVE_450_980)
			sprintf(dispBuf1, "450nm: %3.1fW", ((float)power_ch0 / 10.0F));
#endif			
			
			if(mode == LASER_MODE_CW){
				sprintf(dispBuf2, "Mode: CW");
			}
			if(mode == LASER_MODE_MP){
				sprintf(dispBuf2, "Mode: Pulse, On: %dmS, Off: %dmS", posWidth, negWidth);
			}
			break;
		}
		case LASER_CHANNEL_CH1:{
			sprintf(dispBuf1, "980nm: %3.1fW", ((float)power_ch1 / 10.0F));
			if(mode == LASER_MODE_CW){
				sprintf(dispBuf2, "Mode: CW");
			}
			if(mode == LASER_MODE_MP){
				sprintf(dispBuf2, "Mode: Pulse, On: %dmS, Off: %dmS", posWidth, negWidth);
			}						
			break;
		}
		case    LASER_CHANNEL_RAIM:{
			sprintf(dispBuf1, "635nm: %3.1fW", ((float)power_red / 10.0F));
			if(mode == LASER_MODE_CW){
				sprintf(dispBuf2, "Mode: CW");
			}
			if(mode == LASER_MODE_MP){
				sprintf(dispBuf2, "Mode: Pulse, On: %dmS, Off: %dmS", posWidth, negWidth);
			}						
			break;
		}
		default:break;
	}
	SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL0, (uint8_t*)dispBuf1);
	SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_TEXTDISPLAY_DETAIL1, (uint8_t*)dispBuf2);
}

void unselectSchemeNum(int16_t index){//反选方案条
	if(index >= 16){
		index = index - 16;
	}
	SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, (GDDC_PAGE_SCHEME_KEY_SELECT_0 + index), 0x0);
}
void seletcSchemeNum(int16_t classify, int16_t index){//选中方案条
	if(index >= 16){
		SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, (GDDC_PAGE_SCHEME_KEY_SELECT_0 + index - 16), 0x1);
	}
	else{
		SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, (GDDC_PAGE_SCHEME_KEY_SELECT_0 + index), 0x1);
	}
	updateSchemeInfo(classify, index);
}
void unselectSchemeAll(void){//反选第一页全部方案条
	BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
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
		sprintf(dispBuf, "%5.2f Hz", freq);
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);		

		dutyCycle = (float)NVRAM0[EM_LASER_POSWIDTH] / (float)(NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH]);
		sprintf(dispBuf, "%4.1f %%", dutyCycle * 100.0F);			
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);		
		averagePower = dutyCycle * (float)(NVRAM0[EM_LASER_POWER_TOTAL]) / 10.0F;
	}
	//平均功率显示
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(NVRAM0[EM_LASER_CHANNEL_SELECT]){
		case LASER_CHANNEL_CH0:{
			averagePower = dutyCycle * (float)(NVRAM0[EM_LASER_POWER_CH0]) / 10.0F;
			break;
		}
		case LASER_CHANNEL_CH1:{
			averagePower = dutyCycle * (float)(NVRAM0[EM_LASER_POWER_CH1]) / 10.0F;
			break;
		}
		default:{
			averagePower = dutyCycle * ((float)(NVRAM0[EM_LASER_POWER_CH0]) + (float)NVRAM0[EM_LASER_POWER_CH1] + (float)NVRAM0[EM_LASER_POWER_635]) / 10.0F;
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
	float barValue;
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(NVRAM0[EM_LASER_CHANNEL_SELECT]){
		case LASER_CHANNEL_CH0:{
			NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH0];
			break;
		}
		case LASER_CHANNEL_CH1:{
			NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH1];
			break;
		}
		case LASER_CHANNEL_RAIM:{
			NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_635];
			break;
		}
		default:break;
	}
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_MODE_CW, true);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_MODE_MP, false);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, false);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_POSWIDTH, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_NEGWIDTH, false);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_ICON_MPKEY, false);
		
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, false);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, false);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, false);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, false);	
		
		sprintf(dispBuf, "N/A");
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_FREQUENCY, (uint8_t*)dispBuf);			
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DUTYCYCLE, (uint8_t*)dispBuf);
	}
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_MODE_CW, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_MODE_MP, true);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, true);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_POSWIDTH, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_NEGWIDTH, true);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_ICON_MPKEY, true);
		
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, true);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, true);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, true);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, true);
		updatePosWidthDisplay();
		updateNegWidthDisplay();
	}

#if defined(APP_CONFIG_WAVE_1470_980_650)
		barValue = NVRAM0[EM_LASER_POWER_CH0] * 100.0F / CONFIG_LOGIC_MAX_LASER_POWER_CH0;
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_CH0, (uint32_t)barValue);
		barValue = NVRAM0[EM_LASER_POWER_CH1] * 100.0F / CONFIG_LOGIC_MAX_LASER_POWER_CH1;
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_CH1, (uint32_t)barValue);
		barValue = NVRAM0[EM_LASER_POWER_635] * 100.0F / CONFIG_MAX_LASER_POWER_RED;
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_RED, (uint32_t)barValue);
#endif
	SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_AIM, NVRAM0[DM_RAIM_BRG]);
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){//1470
		sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_SEL, (uint8_t*)dispBuf);		
		barValue = NVRAM0[EM_LASER_POWER_CH0] * 100.0F / CONFIG_LOGIC_MAX_LASER_POWER_CH0;
		if(barValue <= 2){
			barValue = 2;
		}
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL, (uint32_t)barValue);
		
#if defined(APP_CONFIG_WAVE_1470_980_650)
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, true);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, true);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, true);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, true);
		
				SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, false);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, 0);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, true);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, true);
		
#endif
#if defined(APP_CONFIG_WAVE_1470_650)
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, true);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, true);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, false);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, false);
#endif
#if defined(APP_CONFIG_WAVE_1940_650)
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, true);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, true);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, false);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, false);
#endif

#if defined(APP_CONFIG_WAVE_450_980)
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);

		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, true);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, true);

		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, false);
#endif

	}
	if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){//980
		sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_SEL, (uint8_t*)dispBuf);
		barValue = NVRAM0[EM_LASER_POWER_CH1] * 100.0F / CONFIG_LOGIC_MAX_LASER_POWER_CH1;
		if(barValue <= 2){
			barValue = 2;
		}
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL, (uint32_t)barValue);
#if defined(APP_CONFIG_WAVE_1470_650) || defined(APP_CONFIG_WAVE_1470_980_650)
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, 0);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, 1);
#endif
#if defined(APP_CONFIG_WAVE_1940_650)
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, 0);
#endif
#if defined(APP_CONFIG_WAVE_450_980)
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, 0);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, 1);		
#endif
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, 0);
	}
	if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_RAIM){//635
		sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_635]) / 10));
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_SEL, (uint8_t*)dispBuf);
		barValue = NVRAM0[EM_LASER_POWER_635] * 100.0F / CONFIG_MAX_LASER_POWER_RED;
		if(barValue <= 2){
			barValue = 2;
		}
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL, (uint32_t)barValue);

#if defined(APP_CONFIG_WAVE_1470_650) || defined(APP_CONFIG_WAVE_1470_980_650)
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, true);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, true);
		//SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		//SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		//SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);	
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, true);
#endif
#if defined(APP_CONFIG_WAVE_1940_650)
		//SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		//SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		//SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0A, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, true);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0B, true);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, true);
#endif 
		
#if defined(APP_CONFIG_WAVE_450_980)
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, true);
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0C, true);

		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1A, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1B, false);
		
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_RED, false);
#endif
	}
#if defined(APP_CONFIG_WAVE_1470_980_650)
	//memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	//sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
	//SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_CH0, (uint8_t*)dispBuf);
	//memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	//sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
	//SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_CH1, (uint8_t*)dispBuf);	
	//memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	//sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_635]) / 10));	
	//SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_RED, (uint8_t*)dispBuf);		
#endif
		
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%d%%\n", NVRAM0[DM_RAIM_BRG] * 10);
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_SET_POWER_AIM, (uint8_t*)dispBuf);
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
	switch(NVRAM0[EM_LASER_CHANNEL_SELECT]){
		case LASER_CHANNEL_CH0:{
			displayPower = (float)NVRAM0[EM_LASER_POWER_CH0] / 10.0F;
#if defined(APP_CONFIG_WAVE_1470_650)	|| defined(APP_CONFIG_WAVE_1470_980_650)
			sprintf(dispBuf, "1470nm");
#endif
#if defined(APP_CONFIG_WAVE_1940_650)
			sprintf(dispBuf, "1940nm");
#endif
#if defined(APP_CONFIG_WAVE_450_980)
			sprintf(dispBuf, "450nm");
#endif
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_SHOW_WAVE, (uint8_t*)dispBuf);
			break;
		}
		case LASER_CHANNEL_CH1:{
			displayPower = (float)NVRAM0[EM_LASER_POWER_CH1] / 10.0F;
			sprintf(dispBuf, "980nm");
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_SHOW_WAVE, (uint8_t*)dispBuf);
			break;
		}
		case LASER_CHANNEL_RAIM:{
			displayPower = (float)NVRAM0[EM_LASER_POWER_635] / 10.0F;
			sprintf(dispBuf, "635nm");
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_SHOW_WAVE, (uint8_t*)dispBuf);
			break;
		}			
		default:{
			sprintf(dispBuf, "1470+980nm");
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_SHOW_WAVE, (uint8_t*)dispBuf);
			displayPower = ((float)NVRAM0[EM_LASER_POWER_CH0] + (float)NVRAM0[EM_LASER_POWER_CH1] + (float)NVRAM0[EM_LASER_POWER_635])/ 10.0F;
			break;
		}
	}
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
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
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	ftmp = ((float)(NVRAM0[EM_ACOUSTIC_ENERGY])) / 10.0F;
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
	loadDeviceConfig();//载入硬件配置
	if(deviceConfig.greenLedDc <= 0 || (deviceConfig.greenLedDc > CONFIG_GREEN_LED_MAX_DC)){
		SET_GREEN_LED_DC(10);
	}
	else{
		SET_GREEN_LED_DC(deviceConfig.greenLedDc);
	}
	if(deviceConfig.redLedDc <= 0 || (deviceConfig.redLedDc > CONFIG_RED_LED_MAX_DC)){
		SET_RED_LED_DC(10);
	}
	else{
		SET_RED_LED_DC(deviceConfig.redLedDc);
	}
	if(deviceConfig.blueLedDc <= 0 || (deviceConfig.blueLedDc > CONFIG_BLUE_LED_MAX_DC)){
		SET_BLUE_LED_DC(10);
	}
	else{
		SET_BLUE_LED_DC(deviceConfig.blueLedDc);
	}
	tempControlInit();
	standbyKeyTouchEnableStatus = -1;
	setRedLaserPwm(0);
	hmiUartInit();
	schemeInit(0);//不恢复自定义方案
	loadSelectScheme(NVRAM0[DM_SCHEME_CLASSIFY], NVRAM0[DM_SCHEME_INDEX]);
	//NVRAM0[EM_HMI_OPERA_STEP] = 0;
	NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_HIBERNATE;
	//检查VOLUME储存值是否合规
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = CONFIG_BEEM_MAX_VOLUME;
	LIMS16(DM_BEEM_VOLUME, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = CONFIG_MAX_LASER_POWER_RAIM;
	LIMS16(DM_RAIM_BRG, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[TMP_REG_0] = CONFIG_LCD_MIN_DC;
	NVRAM0[TMP_REG_1] = CONFIG_LCD_MAX_DC;
	LIMS16(DM_LCD_BRG, TMP_REG_0, TMP_REG_1);
	
	NVRAM0[EM_FAN0_SET_SPEED] = 0;
	NVRAM0[EM_FAN0_GET_SPEED] = 0;
	SSET(R_RFID_PASS);
	//屏蔽报警	
	RRES(R_LASER_A_DIODE_TEMP_HIGH);
	RRES(R_LASER_A_DIODE_TEMP_LOW);
	RRES(R_LASER_B_DIODE_TEMP_HIGH);
	RRES(R_LASER_B_DIODE_TEMP_LOW);

	RRES(R_LASER_A_COUPLER_TEMP_HIGH);
	RRES(R_LASER_A_COUPLER_TEMP_LOW);
	RRES(R_LASER_B_COUPLER_TEMP_HIGH);
	RRES(R_LASER_B_COUPLER_TEMP_LOW);

	RRES(R_LASER_A_CRYST0_TEMP_HIGH);
	RRES(R_LASER_A_CRYST0_TEMP_LOW);
	RRES(R_LASER_A_CRYST1_TEMP_HIGH);
	RRES(R_LASER_A_CRYST1_TEMP_LOW);

	RRES(R_LASER_B_CRYST0_TEMP_HIGH);
	RRES(R_LASER_B_CRYST0_TEMP_LOW);
	RRES(R_LASER_B_CRYST1_TEMP_HIGH);
	RRES(R_LASER_B_CRYST1_TEMP_LOW);

	RRES(R_HT0_TEMP_HIGH);
	RRES(R_HT1_TEMP_HIGH);
	RRES(R_HT2_TEMP_HIGH);
	RRES(R_HT3_TEMP_HIGH);

	RRES(R_HWATER_TEMP_HIGH);
	RRES(R_HWATER_TEMP_LOW);
	RRES(R_CWATER_TEMP_HIGH);
	RRES(R_CWATER_TEMP_LOW);
	RRES(R_AMBIENT0_TEMP_HIGH);
	RRES(R_AMBIENT0_TEMP_LOW);
	RRES(R_AMBIENT1_TEMP_HIGH);
	RRES(R_AMBIENT1_TEMP_LOW);
	RRES(R_AMBIENT2_TEMP_HIGH);
	RRES(R_AMBIENT2_TEMP_LOW);
	RRES(R_AMBIENT3_TEMP_HIGH);
	RRES(R_AMBIENT3_TEMP_LOW);
	RRES(R_HDC1080_TEMP_HIGH);
	RRES(R_HDC1080_TEMP_LOW);
	RRES(R_HDC1080_HUMIDITY_HIGH);
	RRES(R_HDC1080_HUMIDITY_LOW);
	RRES(R_DHT11_TEMP_HIGH);			
	RRES(R_DHT11_TEMP_LOW);
	RRES(R_DHT11_HUMIDITY_HIGH);
	RRES(R_DHT11_HUMIDITY_LOW);
	RRES(R_MCU_TEMP_HIGH);		
	RRES(R_MCU_TEMP_LOW);		
	RRES(R_MBAT_TEMP_HIGH);	
	RRES(R_MBAT_TEMP_LOW);		
	RRES(R_HWATER_FLOW_LOW);
	RRES(R_CWATER_FLOW_LOW);
									
	RRES(R_FAULT);
	//脚踏插入
	//SSET(R_FOOTSWITCH_PLUG);
	RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
	SET_SPK_TIM_ON;
	SET_BEEM_LED_OFF;
#if defined(LDR2P1_G5_A1_20250731_DUAL) || defined(LDR2P1_G5_A1_20250731_TRIP)	
	SET_USB_FS_SEL_LEGACY_OFF;//切换为MCU USB
	SET_USB_FS_PSON_LEGACY_ON;//切换为内部USB
	SET_USB_HS_PSON_LEGACY_OFF;//打开内部USB供电
#endif
#if defined (LDR2P1_G5_A1_20250910_DUAL) || defined(LDR2P1_G5_A1_20250910_TRIP)
	SET_USBA0_SEL_OFF;
	SET_USBA1_SEL_ON;
	SET_USBA0_PSON_ON;
#endif
}

static void faultLoop(void){//故障轮询
	uint8_t flag = 0;		
	flag |= LDB(R_ESTOP);//
	if(LDB(R_DISABLE_TEMPERATURE_CHECK)){//屏蔽温度报警
		flag |= LD(R_TEMP_FAULT);//正常0
	}
	else{
		RRES(R_TEMP_FAULT);
	}
	
	if(LDB(R_DISABLE_HUMIDITY_CHECK)){//屏蔽湿度报警
		flag |= LD(R_HUMIDITY_FALUT);//正常0
	}
	else{
		RRES(R_HUMIDITY_FALUT);
	}
	
	if(LDB(R_DISABLE_FLOW_CHECK)){//屏蔽流量报警
		flag |= LD(R_FLOW_FAULT);
	}
	else{
		RRES(R_FLOW_FAULT);
	}
	
	flag |= LDB(R_ESTOP);//
	flag |=	LDB(R_INTERLOCK);//正常1
	flag |= LDB(R_FOOTSWITCH_PLUG);//正常1
	flag |= LDB(R_FIBER_PROBE);//正常1
	flag |= LDB(R_RFID_PASS);//正常1
	flag |= LD(R_TEMP_FAULT);
	flag |= LD(R_HUMIDITY_FALUT);
	flag |= LD(R_FLOW_FAULT);
	
	if(flag){
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
		SSET(Y_GREEN_LED);//打开绿灯
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
				laserStatus = (GET_LASER_CH0 || GET_LASER_CH1);
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
						NVRAM0[SPREG_BEEM_FREQ] = CONFIG_ACOUSITC_SPK_FREQ;			
						sPlcSpeakerFreq(NVRAM0[SPREG_BEEM_FREQ]);
					}
					else{
						sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
						NVRAM0[SPREG_BEEM_FREQ] = CONFIG_DEFAULT_SPK_FREQ;					
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

uint8_t isLegalUsbDev(USBH_HandleTypeDef *phost){//判断是否是允许的无线脚踏适配器
	uint8_t i;
	for(i = 0;i < 5;i ++){
		if((phost->device.DevDesc.idVendor == legalUsbDev[i]) && phost->device.DevDesc.idProduct == legalUsbPid[i]){
			return true;
		}
	}
	return false;
}

void wfswLoop(USBH_HandleTypeDef *phost){//无线脚踏轮询
	HID_KEYBD_Info_TypeDef *k_pinfo;
  char c;
	if(Appli_state == APPLICATION_READY){//判断适配器是否插入
		if(isLegalUsbDev(phost)){		
			if(LDB(SPCOIL_WFSWITCH_PLUG)){
				printf("%s,%d,%s:wireless footswich plug......\n",__FILE__, __LINE__, __func__);
				SSET(SPCOIL_WFSWITCH_PLUG);
			}
			k_pinfo = USBH_HID_GetKeybdInfo(phost); 	
			if(k_pinfo != NULL){
				c = USBH_HID_GetASCIICode(k_pinfo);
				if(c == '1'){//凯昆脚踏默认为数字1
					printf("%s,%d,%s:wireless footswich press......\n",__FILE__, __LINE__, __func__);
					SSET(SPCOIL_WFSWITCH_NO);
				}
				if(c == 0x0){
					printf("%s,%d,%s:wireless footswich release......\n",__FILE__, __LINE__, __func__);		
					RRES(SPCOIL_WFSWITCH_NO);
				}		
			}
		}
		else{
#if CONFIG_DEBUG_WSW == 1
			printf("%s,%d,%s:inlega footswitch usb device......!\n",__FILE__, __LINE__, __func__);
#endif
		}
	}
	else{
		if(LD(SPCOIL_WFSWITCH_PLUG)){
			RRES(SPCOIL_WFSWITCH_PLUG);
			RRES(SPCOIL_WFSWITCH_NO);
			printf("%s,%d,%s:wireless footswich unplug......\n",__FILE__, __LINE__, __func__);
		}	
	}
}

static void gddcHmiLoop(void){//大彩触摸屏轮询程序
	if(LD(R_DCHMI_RESET_DONE) && LD(R_DCHMI_RESTORE_DONE)){//HMI复位完成后处理串口指令
		hmiCmdSize = queue_find_cmd(hmiCmdBuffer, CMD_MAX_SIZE);//从缓冲区中获取一条指令         
				if(hmiCmdSize > 0){//接收到指令及判断是否为开机提示                                                            
						ProcessMessage((PCTRL_MSG)hmiCmdBuffer, hmiCmdSize);//指令处理  
				}                                                                             
	}
}
static void powerManagementLoop(void){//电源管理轮询程序
	if(NVRAM0[EM_HMI_OPERA_STEP] != FSMSTEP_HIBERNATE){	
#if defined(CONFIG_PMU_STM32)
		if(LDB(X_PWR_KEY)){//STM32软关机按键
			PmuPowerDown();
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_HIBERNATE;
		}		
#endif
#if defined(CONFIG_PMU_LTC2955)
		if(LDN(X_PWR_INT)){//PMU单元软关机信号
			//关闭激光器
			EDLAR();//停止发射
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			NVRAM0[SPREG_DAC_4] = 0;NVRAM0[SPREG_DAC_5] = 0;NVRAM0[SPREG_DAC_6] = 0;NVRAM0[SPREG_DAC_7] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();UPDAC4();UPDAC5();UPDAC6();UPDAC7();
			NVRAM0[SPREG_DAC_16] = 0;NVRAM0[SPREG_DAC_17] = 0;
			UPDAC16();UPDAC17();
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_POWEROFF_CONFIRM;//进入关机确认状态
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_POWEROFF_CONFIRM;	
			SetScreen(NVRAM0[EM_DC_PAGE]);
		}
#endif
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_HIBERNATE){
		if(LD(X_PWR_KEY)){
			PmuPowerUp();
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_IDLE;
		}
	}
}

void dcHmiLoop(void){//HMI轮训程序
	uint8_t tmp8;
	powerManagementLoop();
	wfswLoop(&APP_CONFIG_WFSW_PORT);
	speakerLoop();
	statusLoop();
	faultLoop();
	gddcHmiLoop();
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_HIBERNATE){//休眠软关机
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_IDLE){//待机
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_POWERUP;
		return;
	}
	//状态机
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_POWERUP){//上电步骤	
		RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
		sPlcSpeakerEnable();
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
			MsgId = 0xFF;//当前显示的信息ID
		
			SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, false);			
			SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			
			SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);					
			SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);

			SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//清空警报信息栏
			
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_RFID, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FIBER_PROBE, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_AUTO_FAN, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_CLEAR_EPROM, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FOOTSWITCH, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_TEMPERATURE, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_ESTOP, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_INTERLOCK, false);		
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_FLOW, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_DISABLE_HUMIDITY, false);	
			
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
#if defined(APP_CONFIG_WAVE_1470_650)
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_POWERUP_1470;												
#endif
#if defined(APP_CONFIG_WAVE_1470_980_650)
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_POWERUP_TRI;								
#endif
#if defined(APP_CONFIG_WAVE_1940_650)
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_POWERUP_1940;	
#endif

#if defined(APP_CONFIG_WAVE_450_980)
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_POWERUP_450;	
#endif
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			//打开蜂鸣器
			NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_0;
			NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
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
		SET_LASER_CH7_OFF;
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
				if(LD(R_TEMP_FAULT)){
					if(LD(R_LASER_A_DIODE_TEMP_HIGH) || LD(R_LASER_B_DIODE_TEMP_HIGH)){//激光器高温保护
						updateWarnMsgDisplay(MSG_DIODE_HTEMP);
					}
					else if(LD(R_LASER_A_DIODE_TEMP_LOW) || LD(R_LASER_B_DIODE_TEMP_LOW)){//激光器低温NTC开路保护
						updateWarnMsgDisplay(MSG_DIODE_LTEMP);
					}
					else if(LD(R_MCU_TEMP_HIGH)){//环境高温保护
						updateWarnMsgDisplay(MSG_ENVI_HTEMP);
					}
					else if(LD(R_MCU_TEMP_LOW)){//环境低温保护
						updateWarnMsgDisplay(MSG_ENVI_LTEMP);
					}
					else if(LD(R_HWATER_TEMP_HIGH) || LD(R_HWATER_TEMP_LOW)){//热水温度异常
						updateWarnMsgDisplay(MSG_HWATER_ABNORMAL);
					}
					else if(LD(R_CWATER_TEMP_HIGH) || LD(R_CWATER_TEMP_LOW)){//冷水温度异常
						updateWarnMsgDisplay(MSG_CWATER_ABNORMAL);
					}
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
				else if(LD(R_FLOW_FAULT)){//流量报警
					updateWarnMsgDisplay(MSG_FLOW_ABNORMAL);
				}
				else if(LD(R_HUMIDITY_FALUT)){//湿度报警
					updateWarnMsgDisplay(MSG_HUMIDITY_ABNORMAL);
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
		if(LD(R_STANDBY_KEY_STNADBY_DOWN)){//点击READY
			SET_LASER_CH7_ON;	
			CLRD(EM_LASER_RELEASE_TIME);
			CLRD(EM_LASER_TRIG_TIME);
			LaserTimer_Mode = (int8_t)NVRAM0[EM_LASER_PULSE_MODE];
			printf("%s,%d,%s:set laser mode=%d\n",__FILE__, __LINE__, __func__, LaserTimer_Mode);
			LaserTimer_TMate 				= NVRAM0[EM_LASER_POSWIDTH];
			LaserTimer_TOvertime 		= NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH];	
			printf("%s,%d,%s:set LaserTimer_TMate=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TMate);
			printf("%s,%d,%s:set LaserTimer_TOvertime=%d\n", __FILE__, __LINE__, __func__, LaserTimer_TOvertime);
			//ACOUSTIC 初始化
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
				//能量大于设置功率的两倍	
				if(NVRAM0[DM_SCHEME_CLASSIFY] == SCHEME_PROCTOLOGY){
					if((NVRAM0[DM_SCHEME_INDEX] == 0) || 
						 (NVRAM0[DM_SCHEME_INDEX] == 1) ||
						 (NVRAM0[DM_SCHEME_INDEX] == 2)){
						RRES(R_ACOUSTIC_ENABLE);
					}
					else{
						SSET(R_ACOUSTIC_ENABLE);
					}
				}
				else{
					SSET(R_ACOUSTIC_ENABLE);
				}							   
				NVRAM0[EM_ACOUSTIC_TIME_STEP] = 1;//CW模式每次加减量1秒
				//NVRAM0[EM_ACOUSTIC_ENERGY_STEP] = NVRAM0[EM_LASER_POWER_TOTAL] / 10;//CW模式每次加减量
				NVRAM0[EM_ACOUSTIC_ENERGY_STEP] = NVRAM0[EM_LASER_POWER_TOTAL];//CW模式每次加减量
				NVRAM0[EM_ACOUSTIC_TIME] = 1;//初始为1秒
				NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_TIME] * NVRAM0[EM_LASER_POWER_TOTAL];
				NVRAM0[EM_ACOUSTIC_TIME_MIN] = 1;//最小1秒
				NVRAM0[EM_ACOUSTIC_TIME_MAX] = NVRAM0[EM_ACOUSTIC_TIME_STEP] * 50;//最大100秒
				NVRAM0[EM_ACOUSTIC_ENERGY_MIN] = NVRAM0[EM_ACOUSTIC_TIME_MIN] * NVRAM0[EM_LASER_POWER_TOTAL];
				NVRAM0[EM_ACOUSTIC_ENERGY_MAX] = NVRAM0[EM_LASER_POWER_TOTAL] * NVRAM0[EM_ACOUSTIC_TIME_MAX];
			}	
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
				//脉冲大于1秒启用提示音
				if((NVRAM0[EM_LASER_POSWIDTH] >= 1000) && (NVRAM0[EM_LASER_NEGWIDTH] >= 1000)){//周期大于2000mS
					SSET(R_ACOUSTIC_ENABLE);
					NVRAM0[EM_ACOUSTIC_TIME_STEP] = (NVRAM0[EM_LASER_POSWIDTH] / 1000) + (NVRAM0[EM_LASER_NEGWIDTH] / 1000);
					NVRAM0[EM_ACOUSTIC_TIME] = NVRAM0[EM_ACOUSTIC_TIME_STEP];
					
					NVRAM0[EM_ACOUSTIC_ENERGY_STEP] = (NVRAM0[EM_LASER_POSWIDTH] /1000) * NVRAM0[EM_LASER_POWER_TOTAL];
					NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
					
					NVRAM0[EM_ACOUSTIC_TIME_MIN] = NVRAM0[EM_ACOUSTIC_TIME_STEP];					
					NVRAM0[EM_ACOUSTIC_TIME_MAX] = NVRAM0[EM_ACOUSTIC_TIME_MIN] * 10;//最大100周期
					NVRAM0[EM_ACOUSTIC_ENERGY_MIN] = NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
					NVRAM0[EM_ACOUSTIC_ENERGY_MAX] = NVRAM0[EM_LASER_POWER_TOTAL] * NVRAM0[EM_ACOUSTIC_TIME_MAX];
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
#if defined(LYPE_MCU_1V0_20260106)
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){//->450nm  0-3CH 
				NVRAM0[SPREG_DAC_0] = fitLaserToCode(LASER_DAC_CHANNEL_CH0, (int16_t)((float)(NVRAM0[EM_LASER_POWER_CH0] / 4.0F)), &deviceConfig, true);
				NVRAM0[SPREG_DAC_1] = fitLaserToCode(LASER_DAC_CHANNEL_CH1, (int16_t)((float)(NVRAM0[EM_LASER_POWER_CH0] / 4.0F)), &deviceConfig, true);
				NVRAM0[SPREG_DAC_2] = fitLaserToCode(LASER_DAC_CHANNEL_CH2, (int16_t)((float)(NVRAM0[EM_LASER_POWER_CH0] / 4.0F)), &deviceConfig, true);
				NVRAM0[SPREG_DAC_3] = fitLaserToCode(LASER_DAC_CHANNEL_CH3, (int16_t)((float)(NVRAM0[EM_LASER_POWER_CH0] / 4.0F)), &deviceConfig, true);
				UPDAC0();UPDAC1();UPDAC2();UPDAC3();
			}
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){//->980nm 4CH
				NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
				UPDAC0();UPDAC1();UPDAC2();UPDAC3();
				NVRAM0[SPREG_DAC_4] = fitLaserToCode(LASER_DAC_CHANNEL_CH4, NVRAM0[EM_LASER_POWER_CH1], &deviceConfig, true);
				UPDAC4();
			}
			NVRAM0[SPREG_DAC_17] = (NVRAM0[DM_GAIM_BRG] * deviceConfig.greenAimGain) + CONFIG_LASER_GAIM_OFFSET;
			UPDAC17();//打开绿光
#endif
			
#if defined(MODEL_PVGLS_7W_1940_A0) ||\
		defined(MODEL_PVGLS_10W_1940_A1) ||\
		defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1) ||\
		defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_RASPI_G9_A1_20260322)
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){
				NVRAM0[SPREG_DAC_0] = fitLaserToCode(LASER_CHANNEL_CH0, NVRAM0[EM_LASER_POWER_CH0], &deviceConfig, true);
				UPDAC0();
				NVRAM0[SPREG_DAC_1] = 0;
				UPDAC1();
			}
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){
				NVRAM0[SPREG_DAC_0] = 0;
				UPDAC0();
				NVRAM0[SPREG_DAC_1] = fitLaserToCode(LASER_CHANNEL_CH1, NVRAM0[EM_LASER_POWER_CH1], &deviceConfig, true);
				UPDAC1();
			}
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_RAIM){
				NVRAM0[SPREG_DAC_0] = 0;UPDAC0();
				NVRAM0[SPREG_DAC_1] = 0;UPDAC1();
				//打开指示激光
				NVRAM0[SPREG_DAC_16] = (NVRAM0[DM_RAIM_BRG] * deviceConfig.redAimGain) + CONFIG_LASER_RAIM_OFFSET;
				UPDAC16();//打开红光
			}
#endif

#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){
				NVRAM0[SPREG_DAC_0] = fitLaserToCode(LASER_CHANNEL_CH0, (int16_t)((float)NVRAM0[EM_LASER_POWER_CH0] / 2.0F), &deviceConfig, true);
				NVRAM0[SPREG_DAC_1] = fitLaserToCode(LASER_CHANNEL_CH1, (int16_t)((float)NVRAM0[EM_LASER_POWER_CH0] / 2.0F), &deviceConfig, true);
				UPDAC0();UPDAC1();
			}
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){
				NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;
				UPDAC0();
				UPDAC1();
				NVRAM0[SPREG_DAC_2] = fitLaserToCode(LASER_CHANNEL_CH1, NVRAM0[EM_LASER_POWER_CH1], &deviceConfig, true);
				UPDAC2();
			}
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_RAIM){
				NVRAM0[SPREG_DAC_0] = 0;UPDAC0();
				NVRAM0[SPREG_DAC_1] = 0;UPDAC1();
				NVRAM0[SPREG_DAC_2] = 0;UPDAC2();
				//打开指示激光
				NVRAM0[SPREG_DAC_16] = (NVRAM0[DM_RAIM_BRG] * deviceConfig.redAimGain) + CONFIG_LASER_RAIM_OFFSET;
				UPDAC16();//打开红光
			}
#endif

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
			goNextScheme();
			loadSelectScheme(NVRAM0[DM_SCHEME_CLASSIFY], NVRAM0[DM_SCHEME_INDEX]);//切换方案				
			updateStandbyDisplay();
			RRES(R_STANDBY_KEY_SCHEME_NEXT_DOWN);
		}
		if(LD(R_STANDBY_KEY_SCHEME_LAST_DOWN)){
			goLastScheme();
			loadSelectScheme(NVRAM0[DM_SCHEME_CLASSIFY], NVRAM0[DM_SCHEME_INDEX]);
			updateStandbyDisplay();	
			RRES(R_STANDBY_KEY_SCHEME_LAST_DOWN);
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
			if(LD(R_ACOUSTIC_ENABLE)){
				SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_ADD, true);
				SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_INC, true);
				SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_ADD, true);
				SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_INC, true);
			}
			else{
				SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_ADD, false);
				SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_ENERGY_INC, false);
				SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_ADD, false);
				SetControlEnable(GDDC_PAGE_READY, GDDC_PAGE_READY_KEY_ACOUSTIC_TIME_INC, false);
			}
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
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			NVRAM0[SPREG_DAC_4] = 0;NVRAM0[SPREG_DAC_5] = 0;NVRAM0[SPREG_DAC_6] = 0;NVRAM0[SPREG_DAC_7] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();
			UPDAC4();UPDAC5();UPDAC6();UPDAC7();
			NVRAM0[SPREG_DAC_16] = 0;UPDAC16();//关闭红激光
			NVRAM0[SPREG_DAC_17] = 0;UPDAC17();//关闭绿激光
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
				NVRAM0[SPREG_BEEM_FREQ] = CONFIG_DEFAULT_SPK_FREQ;					
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
				NVRAM0[SPREG_BEEM_FREQ] = CONFIG_DEFAULT_SPK_FREQ;					
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
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			NVRAM0[SPREG_DAC_4] = 0;NVRAM0[SPREG_DAC_5] = 0;NVRAM0[SPREG_DAC_6] = 0;NVRAM0[SPREG_DAC_7] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();UPDAC4();UPDAC5();UPDAC6();UPDAC7();
			NVRAM0[SPREG_DAC_16] = 0;NVRAM0[SPREG_DAC_17] = 0;
			UPDAC16();UPDAC17();
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
		if(LD(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN)){//进入诊断状态
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_DIAGNOSIS;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS;
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			updateDiagnosis();//更新文本输入值
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
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_SCHEME){//方案界面第一页
		RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_0_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 0 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 0;
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 16 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 16;				
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_0_DOWN);		
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_1_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 1 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 1;			
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 17 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 17;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_1_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_2_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 2 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 2;		
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 18 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 18;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_2_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_3_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 3 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 3;
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 19 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 19;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_3_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_4_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 4 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 4;
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 20 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 20;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_4_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_5_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 5 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 5;
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 21 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 21;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_5_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_6_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 6 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 6;			
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 22 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 22;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_6_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_7_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 7 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 7;
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 23 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 23;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_7_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_8_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 8 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 8;	
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 24 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 24;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_8_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_9_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 9 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 9;	
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 25 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 25;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_9_DOWN);
		}
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_10_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 10 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 10;
				
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 26 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 26;
			}	
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_10_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_11_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 11  && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 11;
			}		
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 27 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 27;
			}	
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_11_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_12_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 12 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 12;
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 28 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 28;
			}	
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_12_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_13_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 13 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 13;
			}	
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 29 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 29;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_13_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_14_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 14 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 14;
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 30 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 30;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);
			RRES(R_SCHEME_KEY_SCHEME_SELECT_14_DOWN);
		}
		
		if(LD(R_SCHEME_KEY_SCHEME_SELECT_15_DOWN)){
			unselectSchemeNum(NVRAM0[EM_SCHEME_NUM_TMP]);
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 15 && NVRAM0[EM_SCHEME_NUM_TMP] < 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 15;
			}
			if(NVRAM0[EM_SCHEME_NUM_TMP] != 31 && NVRAM0[EM_SCHEME_NUM_TMP] >= 16){
				NVRAM0[EM_SCHEME_NUM_TMP] = 31;
			}
			updateSchemeInfo(NVRAM0[EM_SCHEME_CLASSIFY_TMP], NVRAM0[EM_SCHEME_NUM_TMP]);	
			RRES(R_SCHEME_KEY_SCHEME_SELECT_15_DOWN);
		}
		if(LD(R_SCHEME_KEY_RENAME_DOWN)){//改名
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//将EM_SCHEME_NUM_TMP指向的名称更新RENAME输入框
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM1 + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_RENAME_DOWN);
		}
		return;
	}	
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_RENAME){//方案改名
		if(LD(R_RENAME_TEXTDISPLAY_READ_DONE)){//更名完毕					
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_RENAME_TEXTDISPLAY_READ_DONE);	
		}
		else if(LD(R_RENAME_KEY_EXIT_DOWN)){	
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_SCHEME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_SCHEME_DETAIL;
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
		if(LD(R_DIAGNOSIS_GOTO_RAW_DOWN)){//进入RAW数据显示
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_DIAGNOSIS_RAW;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS_RAW;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_DIAGNOSIS_GOTO_RAW_DOWN);
		}
		else if(LD(R_CLEAR_EPROM)){//
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			__set_PRIMASK(0);//关闭中断
			sPlcNvramClear();//清空NVRAM
			sPlcFdramClear();//清空FDRAM
			sPlcDeviceConfigClear();//清空config
			resetGddcHmi();
			softDelayMs(40);//等待4秒
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
		else if(LDP(R_DIAGNOSIS_GOTO_CORRECTION_DOWN)){//进入校正页面
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_CORRECTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS_CALI;
			NVRAM0[EM_CALI_CUR_SET_CH0] = 0;NVRAM0[EM_CALI_CUR_SET_CH1] = 0;NVRAM0[EM_CALI_CUR_SET_CH2] = 0;NVRAM0[EM_CALI_CUR_SET_CH3] = 0;
			NVRAM0[EM_CALI_CUR_SET_CH4] = 0;NVRAM0[EM_CALI_CUR_SET_CH5] = 0;NVRAM0[EM_CALI_CUR_SET_CH6] = 0;NVRAM0[EM_CALI_CUR_SET_CH7] = 0;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			updateDiagnosisCali();
			//刷新页面数据
			RRES(R_DIAGNOSIS_GOTO_CORRECTION_DOWN);
		
		}
		else if(LDP(SPCOIL_PS200MS)){
			updateDiagnosisInfo();
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_DIAGNOSIS_RAW){//进入原始参数显示页面
		if(LD(R_DIAGNOSIS_RAW_RETURN_DOWN)){//返回DIAGNOSIS页面
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_DIAGNOSIS;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS;
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			RRES(R_DIAGNOSIS_RAW_RETURN_DOWN);
		}
		else if(LDP(SPCOIL_PS200MS)){
			updateDiagnosisInfoRaw();
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_CORRECTION){//8通道功率校准	
		if(LD(R_DIAGNOSIS_CORRECTION_RETURN_DOWN)){//返回DIAGNOSIS页面
			SET_LASER_CH0_OFF;SET_LASER_CH1_OFF;SET_LASER_CH2_OFF;SET_LASER_CH3_OFF;
			SET_LASER_CH4_OFF;SET_LASER_CH5_OFF;SET_LASER_CH6_OFF;SET_LASER_CH7_OFF;
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;//关闭激光
			NVRAM0[SPREG_DAC_4] = 0;NVRAM0[SPREG_DAC_5] = 0;NVRAM0[SPREG_DAC_6] = 0;NVRAM0[SPREG_DAC_7] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();UPDAC4();
			UPDAC4();UPDAC5();UPDAC6();UPDAC6();UPDAC7();
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH0, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH1, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH2, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH3, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH4, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH5, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH6, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH7, false);
			LaserFlag_Emiting = 0;
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_DIAGNOSIS;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS;
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			RRES(R_DIAGNOSIS_CORRECTION_RETURN_DOWN);
			return;
		}
		if(GET_LASER_CH0 || GET_LASER_CH1 || GET_LASER_CH2 || GET_LASER_CH3 || GET_LASER_CH4 || GET_LASER_CH5 || GET_LASER_CH6 || GET_LASER_CH7){
			LaserFlag_Emiting = 1;
		}
		else{
			LaserFlag_Emiting = 0;
		}
		if(LD(R_TEMP_FAULT) || LD(R_HUMIDITY_FALUT) || LD(R_FLOW_FAULT)){
			SET_LASER_CH0_OFF;
			SET_LASER_CH1_OFF;
			SET_LASER_CH2_OFF;
			SET_LASER_CH3_OFF;
			SET_LASER_CH4_OFF;
			SET_LASER_CH5_OFF;
			SET_LASER_CH6_OFF;
			SET_LASER_CH7_OFF;
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH0, false);	
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH1, false);	
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH2, false);	
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH3, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH4, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH5, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH6, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_BUTTON_LAS_PWM_CH7, false);	
		}
		if(LDP(SPCOIL_PS200MS)){
			updateDiagnosisCaliInfo();
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_POWEROFF_CONFIRM){//关机确认
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



