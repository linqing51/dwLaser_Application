#include "dcHmiApp.h"
/*****************************************************************************/
uint8_t hmiCmdBuffer[CMD_MAX_SIZE];//ָ���
static int8_t standbyKeyTouchEnableStatus = -1;
uint16_t hmiCmdSize;//�ѻ����ָ����
static uint8_t MsgId = 0xFF;//��ǰ��ʾ����ϢID
static void UpdateUI(void);
uint8_t CcmRamBuf[0xFFFF] __attribute__ ((at(CCMDATARAM_BASE)));//�ļ���д����
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
FIL BootLoadFile;//FATFS File Object ��¼��Ϣ
/*****************************************************************************/
void saveConfigToDisk(void){//�����ô��浽U��

}
void loadConfigFromDisk(void){//��U����������

}
void saveSchemeToDisk(void){//���������浽U��
	
}
void loadSchemeFromDisk(void){//��U�����뷽��

}
uint8_t updateBootloadReq(void){//����BOOTLOAD���� 1:���Ը���  0�����ܸ���
	uint32_t TmpReadSize = 0x00;
	uint32_t LastPGAddress;
	uint8_t readflag = TRUE;
	uint32_t bytesread;//ʵ���ļ���ȡ�ֽ���
	uint32_t i;
	//������Ϣ
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Please Standby,Do Not Power Off!!"));
	vTaskDelay(800);
	//����USB DISK FAT�ļ�ϵͳ
	retUsbH = f_mount(&USBH_fatfs, (const TCHAR*)FATFS_ROOT, 0);
	if(retUsbH != FR_OK){//����U��ʧ��
		printf("Bootloader:Mount Fatfs errror:%d!\n", retUsbH);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Mount usb disk errror,exit update!"));
		return false;
	}
	vTaskDelay(6000);
	//���ļ�
	retUsbH = f_open(&BootLoadFile, (const TCHAR*)(BOOTLOAD_FILENAME), FA_OPEN_EXISTING | FA_READ);//
	if(retUsbH != FR_OK){//��ȡʧ�������̼�����ֱ�����г���
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		printf("BootLoader:Open %s fail,unmount usb disk,ECODE=0x%02XH\n", BOOTLOAD_FILENAME, retUsbH);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Open file errror,exit update!"));
		return false;
	}
	//����ļ���С
	f_lseek(&BootLoadFile, 0);//��ȡָ���ƶ�����ͷ
	if(f_size(&BootLoadFile) > BOOTLOADER_FLASH_SIZE){//MCU�̼�����FLSAH����
		f_close(&BootLoadFile);
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		printf("BootLoader:File %s is over length, close file and unmount disk!\n", BOOTLOAD_FILENAME);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("File is over length,exit update!"));
		return false;
	}
	vTaskDelay(800);
	//�����¹̼�CRCֵ
	newBootloadCrc32 = 0;
	crc32Clear();
	LastPGAddress = BOOTLOADER_FLASH_START_ADDRESS;
	memset(CcmRamBuf, 0xFF, sizeof(CcmRamBuf));
	while(readflag){
		/* Read maximum 512 Kbyte from the selected file */
		f_read(&BootLoadFile, CcmRamBuf, sizeof(CcmRamBuf), (void*)&bytesread);
		newBootloadCrc32 = crc32Calculate(CcmRamBuf, bytesread);//CRC32 ��������
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
	for(i = LastPGAddress;i < BOOTLOADER_FLASH_END_ADDRESS;i ++){//����ʣ��CRC
		newBootloadCrc32 = crc32CalculateAdd(0xFF);
	}
	//�����еĹ̼����жԱȲ�������ʾ
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
void confirmBootloadUpdate(void){//ִ��Bootload����
	uint32_t i;
	vTaskSuspendAll();//���������л�
	__disable_irq();//�ر��ж�
	SysTick->CTRL = 0;//�ؼ�����
	HAL_FLASH_Unlock();//��˵FLASH����
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGSERR | FLASH_FLAG_WRPERR);
	if (FLASH_If_EraseBootload() != 0x00){//����BOOTLOAD ʧ��
		printf("BootLoader:Erase bootload fail, GameOver!!!!!\n");
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)("Erase bootload fail,Game Over!"));
		return;
	}
	softDelayMs(800);
	if(checkBlank(BOOTLOADER_FLASH_START_ADDRESS, BOOTLOADER_FLASH_SIZE)){//FLASH ���
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
			printf("BootLoader:write mcu bootload fail,GameOver!!!!!\n");//д��FLASH����
		}
	}
	HAL_FLASH_Lock();
	printf("BootLoader:Update new bootload done...\n");
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_FIRMWARE_INFO, (uint8_t*)"Update new bootload done...");
	softDelayMs(800);
	//�����д���Bootload�Ƿ���ȷ
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

void exitBootloadUpdate(void){//�˳�Bootload����
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
	
void loadDeviceConfig(void){//��EPROM���������ļ�
	uint32_t crc32_eprom_cfg, crc32_cfg;
	epromRead(CONFIG_EPROM_CONFIG_START, (uint8_t*)&deviceConfig, sizeof(deviceConfig));//��EPROM�����豸����
	epromReadDword(CONFIG_EPROM_CFG_CRC, &crc32_eprom_cfg);
	crc32_cfg = HAL_CRC_Calculate(&hcrc,(uint32_t *)&deviceConfig, (sizeof(deviceConfig) / 4));
	if(crc32_eprom_cfg != crc32_cfg){//У�������ʹ��Ĭ������
		printf("%s,%d,%s:load device config crc fail!!!\n",__FILE__, __LINE__, __func__);
		printf("%s,%d,%s:using default device config!\n",__FILE__, __LINE__, __func__);
		//����ģ��Ĭ�Ϲ��ʱ� 1470
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
		//����ģ��Ĭ�Ϲ��ʱ� 980
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
		deviceConfig.normalOpenInterLock = 1;//Ĭ�ϳ�����̤ 
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
void standbyDebugInfoVisiable(int8_t enable){//Standby������Ϣ�ɼ�
	SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_READY, GDDC_PAGE_STANDBY_TEXTDISPLAY_DEBUG, enable);
}
void updateDebugInfo(void){//����Standby������Ϣ
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
void updateDiognosisInfo(void){//���������Ϣ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "ADC0:%05d,ADC1:%05d,ADC2:%05d,DAC0:%05d,DAC1:%05d", NVRAM0[SPREG_ADC_0], NVRAM0[SPREG_ADC_1], NVRAM0[SPREG_ADC_2], NVRAM0[SPREG_DAC_0], NVRAM0[SPREG_DAC_1]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO0, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "FS NC:%1d, FS NO:%1d, ES:%d, IL:%1d, FP:%1d", LD(X_FOOTSWITCH_NC),  LD(X_FOOTSWITCH_NO), LD(X_ESTOP_NC), LD(X_INTERLOCK_NC), LD(X_FIBER_PROBE));
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO1, (uint8_t*)dispBuf);
	
	sprintf(dispBuf, "TLAS:%05d,TMCU:%05d,FANs:%3d,FANg:%3d", NVRAM0[EM_LASER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[EM_FAN_SET_SPEED], NVRAM0[EM_FAN_GET_SPEED]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXTDISPLAY_INFO2, (uint8_t*)dispBuf);
}

void updateScheme_0_Display(void){//����ѡ����淽������
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
void updateScheme_1_Display(void){//����ѡ����淽������
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
void updateInformationDisplay(void){//������Ϣ������ʾ
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
void returnStandbyDisplay(void){//����STANDBY����
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
void clearReleaseTimeEnergy(void){//�������ʱ����������ʾ
	CLRD(EM_LASER_RELEASE_TIME);
	CLRD(EM_LASER_TRIG_TIME);
	CLRD(EM_LASER_RELEASE_ENERGY);
	updateReleaseTimeEnergy();
}
void updateReleaseTimeEnergy(void){//ˢ�·���ʱ������
	uint8_t minute;
	uint8_t seconds;
	int32_t temp0, temp1, temp2, temp3, temp4, temp5;
	char dispBuf1[CONFIG_DCHMI_DISKBUF_SIZE];
	int32_t *p;
	memset(dispBuf1, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	temp0 = *((int32_t*)&NVRAM0[EM_LASER_TRIG_TIME]);//�����ʱ����
	temp0 = temp0 / 50;
	minute = temp0 / 60;
	seconds = temp0 % 60;
	sprintf(dispBuf1, "%3d:%02d", minute, seconds);//00:00
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXTDISPLAY_TREATMENT_TIME, (uint8_t*)dispBuf1);		
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){//����ģʽ��������
		temp2 = temp0 * NVRAM0[EM_LASER_POWER_TOTAL];//���㷢������
	}
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){//����ģʽ��������
		if(NVRAM0[EM_LASER_POSWIDTH] < 1000 || NVRAM0[EM_LASER_NEGWIDTH] < 1000){//���ü��㷨
			temp3 = NVRAM0[EM_LASER_POSWIDTH];
			temp4 = NVRAM0[EM_LASER_NEGWIDTH];
			temp2 = temp0 * NVRAM0[EM_LASER_POWER_TOTAL] * temp3 / (temp3 + temp4);
		}
		else{//ֻ��������������
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
void updateWarnMsgDisplay(uint8_t id){//���¾�����ʾ��
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
void updateSchemeInfo(int16_t cn){//����SCHEME ��ϸ����
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
void standbyPageTouchEnable(int8_t enable){//Standby���津��
//��Ϊ�����޸�	
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
void standbyKeyTouchEnable(int8_t enable){//Standby key����
	if(enable != standbyKeyTouchEnableStatus){
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, enable);	
		standbyKeyTouchEnableStatus = enable;
	}
}
void standbyKeyValue(uint8_t value){//����Standby��ֵ
	SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, value);
}
void updateExtralDisplay(void){//���¶�����ʾ
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
	//ƽ��������ʾ
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
	//�ܹ�����ʾ
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	totalPower = (float)NVRAM0[EM_LASER_POWER_TOTAL] / 10.0F;
	sprintf(dispBuf, "%3.1f W", totalPower);
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_TOTAL_POWER, (uint8_t*)dispBuf);
}

void updatePosWidthDisplay(void){//������������ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	if(NVRAM0[EM_LASER_POSWIDTH] < 1000){
		sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_POSWIDTH]);
	}
	else{
		sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_POSWIDTH] / 1000));
	}
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_POSWIDTH, (uint8_t*)dispBuf);		
}
void updateNegWidthDisplay(void){//���¸�������ʾ
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	if(NVRAM0[EM_LASER_NEGWIDTH] < 1000){
		sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_NEGWIDTH]);
	}
	else{
		sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_NEGWIDTH] / 1000));
	}
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_NEGWIDTH, (uint8_t*)dispBuf);
}

void updateStandbyDisplay(void){//���·�����ʾ
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

void updateOptionDisplay(void){//����ѡ����ʾ	
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
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//����BEEM����������
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);//����LCD����
	BatchEnd();
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME ,NVRAM0[DM_BEEM_VOLUME], 1, 0);
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_LCD_BRG ,NVRAM0[DM_LCD_BRG], 1, 0);
}

void updateReadyDisplay(void){//����READY��ʾ
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

void updateAcousticDisplay(void){//������ʾ������
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
	//������Ϣ
	printf("%s,%d,%s:acoustic time = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME]);
	printf("%s,%d,%s:acoustic energy = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY]);
	printf("%s,%d,%s:acoustic cycle = %d\n", __FILE__, __LINE__, __func__, cycle);	
}
void dcHmiLoopInit(void){//��ʼ��ģ��
		//PID������ʼ��

	LaserTecIncPids.kp = 0.08;
	LaserTecIncPids.ki = 0.005;
	LaserTecIncPids.kd = 0.15;

	standbyKeyTouchEnableStatus = -1;
	setRedLaserPwm(0);
	hmiUartInit();
	NVRAM0[EM_HMI_OPERA_STEP] = 0;
	//���VOLUME����ֵ�Ƿ�Ϲ�
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
	//���α���
	RRES(R_LASER_TEMP_HIGH);							
	RRES(R_LASER_TEMP_LOW);								
	RRES(R_MCU_TEMP_HIGH);										
	RRES(R_MCU_TEMP_LOW);									
	RRES(R_FAULT);
	//��̤����
	SSET(R_FOOTSWITCH_PLUG);
}
static void temperatureLoop(void){//�¶���ѯ��ѯ
	TNTC(EM_LASER_TEMP, SPREG_ADC_0);//CODEת��ΪNTC�����¶��¶�
	TENV(EM_MCU_TEMP, SPREG_ADC_3);//CODEת��ΪMCU�¶�
	//�ж϶������¶�
	if(NVRAM0[EM_LASER_TEMP] >= CONFIG_DIODE_HIGH_TEMP){//����������
		SSET(R_LASER_TEMP_HIGH);
	}
	if(NVRAM0[EM_LASER_TEMP] <= (CONFIG_DIODE_HIGH_TEMP - 50)){//�������ָ������¶�
		RRES(R_LASER_TEMP_HIGH);
	}
	if(NVRAM0[EM_LASER_TEMP] <= CONFIG_DIODE_LOW_TEMP){//���������±���
		SSET(R_LASER_TEMP_LOW);
	}
	if(NVRAM0[EM_LASER_TEMP] >= CONFIG_DIODE_LOW_TEMP + 50){//�������ָ������¶�
		RRES(R_LASER_TEMP_LOW);
	}
	//�жϻ����¶�
	if(NVRAM0[EM_MCU_TEMP] >= CONFIG_ENVI_HIGH_TEMP){//�����¶ȹ���
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
	//�¿�ִ�� ����ȴ����估����״̬�����¿�
	if(LDP(SPCOIL_PS1000MS)){//2����
		//�����¿�PID����
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

	//���з���PID����
	if(LDP(SPCOIL_PS1000MS)){
		if(LD(R_LASER_TEMP_HIGH) || LD(R_LASER_TEMP_LOW) || LD(R_MCU_TEMP_HIGH) || LD(R_MCU_TEMP_LOW)){//����״̬�������򿪷���
			NVRAM0[EM_FAN_SET_SPEED] = 100;
		}
		else{	
			if(LaserTecOut < 10){//����С��5W
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
		if(deviceConfig.normalOpenInterLock == 1){//��������
			if(LD(X_INTERLOCK_NC)){
				RRES(R_INTERLOCK);
			}
			else{
				SSET(R_INTERLOCK);
			}
		}
		else{//��������
			if(LD(X_INTERLOCK_NC)){
				SSET(R_INTERLOCK);
			}
			else{
				RRES(R_INTERLOCK);
			}
		}
	}
	if(LD(R_DISABLE_TEMPERATURE)){//���θ��±���
		RRES(R_LASER_TEMP_HIGH);
		RRES(R_LASER_TEMP_LOW);
		RRES(R_MCU_TEMP_HIGH);
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
	temp |= LD(R_LASER_TEMP_LOW);//����0
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
		RRES(Y_YELLOW_LED);//�رջƵ�
		SSET(Y_RED_LED);//�򿪺��
	}
	else if(LaserFlag_Emiting){
		SSET(Y_GREEN_LED);//�ر��̵�
		RRES(Y_YELLOW_LED);//�򿪻Ƶ�
		SSET(Y_RED_LED);//�رպ��
	}
	else{
		RRES(Y_GREEN_LED);//���̵�
		RRES(Y_YELLOW_LED);//�رջƵ�
		RRES(Y_RED_LED);//�رպ��
	}
}
static void speakerLoop(void){//��������ѯ
	int8_t laserStatus;
	int32_t temp0;
	if(LD(SPCOIL_BEEM_ENABLE)){
		sPlcSpeakerVolume(NVRAM0[SPREG_BEEM_VOLUME]);
		switch(NVRAM0[SPREG_BEEM_MODE]){//ģʽ
			case BEEM_MODE_0:{
				if(LDB(SPCOIL_BEEM_BUSY)){
					sPlcSpeakerEnable();//������Ƶ
					SSET(SPCOIL_BEEM_BUSY);//����������
				}
				break;
			}
			case BEEM_MODE_1:{//ģʽ1 ����ͬ��
				laserStatus = GET_LASER_1470;
				if(laserStatus){//LT3763 PWM ON
					if(LDB(SPCOIL_BEEM_BUSY)){//���PWM�����-> �����
						sPlcSpeakerEnable();//������Ƶ
						SSET(SPCOIL_BEEM_BUSY);//����������
					}
				}
				else{
					if(LD(SPCOIL_BEEM_BUSY)){
						sPlcSpeakerDisable();//������Ƶ
						RRES(SPCOIL_BEEM_BUSY);//�رշ�����	
					}
				}
				NVRAM0[SPREG_BEEM_COUNTER] = -1;
				break;
			}
			case BEEM_MODE_2:{//ģʽ2 ����� ���ⷢ����		
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 50){//1
					sPlcSpeakerEnable();//������Ƶ
					SSET(SPCOIL_BEEM_BUSY);//����������
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
					sPlcSpeakerDisable();//ֹͣ��Ƶ
					RRES(SPCOIL_BEEM_BUSY);//�رշ�����
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100){
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			case BEEM_MODE_3:{//ģʽ3 �ε�����һͣ ������
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 15){//1
					sPlcSpeakerEnable();//������Ƶ
					SSET(SPCOIL_BEEM_BUSY);//����������			
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 15 && NVRAM0[SPREG_BEEM_COUNTER] < 30){//0
					sPlcSpeakerDisable();//�ر���Ƶ
					RRES(SPCOIL_BEEM_BUSY);//�رշ�����
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 30 && NVRAM0[SPREG_BEEM_COUNTER] < 45){//1
					sPlcSpeakerEnable();//������Ƶ
					SSET(SPCOIL_BEEM_BUSY);//����������
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 45 && NVRAM0[SPREG_BEEM_COUNTER] < 60){//0
					sPlcSpeakerDisable();//�ر���Ƶ
					RRES(SPCOIL_BEEM_BUSY);//�رշ�����
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 200){//ͣ1��
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			case BEEM_MODE_4:{//ģʽ4 �����+��ʾ�� ���ⷢ����		
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 50){//1
					sPlcSpeakerEnable();//������Ƶ
					SSET(SPCOIL_BEEM_BUSY);//����������
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
					sPlcSpeakerDisable();//ֹͣ��Ƶ
					RRES(SPCOIL_BEEM_BUSY);//�رշ�����
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100){
					//�ж��Ƿ�������ʾ��
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
						sPlcSpeakerEnable();//������Ƶ
						SSET(SPCOIL_BEEM_BUSY);//����������
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
						sPlcSpeakerDisable();//ֹͣ��Ƶ
						RRES(SPCOIL_BEEM_BUSY);//�رշ�����
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100){
						NVRAM0[SPREG_BEEM_COUNTER] = -1;
					}	
				}
				else if(NVRAM0[EM_LASER_RELEASE_ENERGY] >= 2500 && NVRAM0[EM_LASER_RELEASE_ENERGY] < 5000){//250-500J	
					if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 15){//1
						sPlcSpeakerEnable();//������Ƶ
						SSET(SPCOIL_BEEM_BUSY);//����������			
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 15 && NVRAM0[SPREG_BEEM_COUNTER] < 25){//0
						sPlcSpeakerDisable();//�ر���Ƶ
						RRES(SPCOIL_BEEM_BUSY);//�رշ�����
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 25 && NVRAM0[SPREG_BEEM_COUNTER] < 50){//1
						sPlcSpeakerEnable();//������Ƶ
						SSET(SPCOIL_BEEM_BUSY);//����������
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
						sPlcSpeakerDisable();//�ر���Ƶ
						RRES(SPCOIL_BEEM_BUSY);//�رշ�����
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100){
						NVRAM0[SPREG_BEEM_COUNTER] = -1;
					}					
				}
				else if(NVRAM0[EM_LASER_RELEASE_ENERGY] > 5000){
					if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 14){//1
						sPlcSpeakerEnable();//������Ƶ
						SSET(SPCOIL_BEEM_BUSY);//����������			
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 14 && NVRAM0[SPREG_BEEM_COUNTER] < 26){//0
						sPlcSpeakerDisable();//�ر���Ƶ
						RRES(SPCOIL_BEEM_BUSY);//�رշ�����
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 26 && NVRAM0[SPREG_BEEM_COUNTER] < 40){//1
						sPlcSpeakerEnable();//������Ƶ
						SSET(SPCOIL_BEEM_BUSY);//����������
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 40 && NVRAM0[SPREG_BEEM_COUNTER] < 52){//0
						sPlcSpeakerDisable();//�ر���Ƶ
						RRES(SPCOIL_BEEM_BUSY);//�رշ�����
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 52 && NVRAM0[SPREG_BEEM_COUNTER] < 66){//1
						sPlcSpeakerEnable();//������Ƶ
						SSET(SPCOIL_BEEM_BUSY);//����������
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 66 && NVRAM0[SPREG_BEEM_COUNTER] < 160){//0
						sPlcSpeakerDisable();//�ر���Ƶ
						RRES(SPCOIL_BEEM_BUSY);//�رշ�����
					}
					else if(NVRAM0[SPREG_BEEM_COUNTER] >= 160){//ͣ1��
						NVRAM0[SPREG_BEEM_COUNTER] = -1;
					}	
				}
				break;
			}
			default:break;
		}
	}
	else{
		sPlcSpeakerDisable();//�ر���Ƶ
		RRES(SPCOIL_BEEM_BUSY);//�رշ�����
		NVRAM0[SPREG_BEEM_COUNTER]  = 0;
	}
}

void dcHmiLoop(void){//HMI��ѵ����
	uint8_t tmp8;
	speakerLoop();
	temperatureLoop();//�¿س���
	faultLoop();
	if(LD(R_DCHMI_RESET_DONE) && LD(R_DCHMI_RESTORE_DONE)){//HMI��λ��ɺ�����ָ��
		hmiCmdSize = queue_find_cmd(hmiCmdBuffer, CMD_MAX_SIZE);//�ӻ������л�ȡһ��ָ��         
        if(hmiCmdSize > 0){//���յ�ָ��ж��Ƿ�Ϊ������ʾ                                                            
            ProcessMessage((PCTRL_MSG)hmiCmdBuffer, hmiCmdSize);//ָ���  
        }                                                                             
	}
	//״̬��
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_POWERUP){//�ϵ粽��	
		loadScheme();//�ӵ���洢�Ĵ����лָ���������	
		NVRAM0[DM_DC_OLD_PASSCODE2] = 0;
		NVRAM0[DM_DC_OLD_PASSCODE3] = 0;
	
		NVRAM0[EM_DC_NEW_PASSCODE2] = 0;
		NVRAM0[EM_DC_NEW_PASSCODE3] = 0;
		//��鴢�������Ƿ�Ϲ�
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
		
			SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, false);			
			SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			
			SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);					
			SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);
			
			SetTextValue(GDDC_PAGE_PASSCODE, GDDC_PAGE_PASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));
			SetTextValue(GDDC_PAGE_NEW_PASSCODE, GDDC_PAGE_NEWPASSCODE_TEXTDISPLAY, (uint8_t*)(&(NVRAM0[EM_DC_NEW_PASSCODE0])));

			SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXTDISPLAY_WARN, " ");//��վ�����Ϣ��
			
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
				updateDebugInfo();
			}
		}
		if(LDP(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){
			NVRAM0[EM_LASER_POSWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_POSWIDTH], CONFIG_MAX_LASER_POSWIDTH);
			updatePosWidthDisplay();
		}
		if(LD(R_STANDBY_KEY_POSWIDTH_ADD_DOWN)){//������Ӱ���
			T10MS(T10MS_POSWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_ADD_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_POSWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_POSWIDTH], CONFIG_MAX_LASER_POSWIDTH);
					updatePosWidthDisplay();
					if(NVRAM0[EM_LASER_POSWIDTH] >= CONFIG_MAX_LASER_POSWIDTH){//�ﵽ���ֵ��ֹͣ�Լ�
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
		if(LD(R_STANDBY_KEY_POSWIDTH_DEC_DOWN)){//�����������
			T10MS(T10MS_POSWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_POSWIDTH_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_POSWIDTH] = keyRuleDec(NVRAM0[EM_LASER_POSWIDTH], CONFIG_MIN_LASER_POSWIDTH);
					updatePosWidthDisplay();
					if(NVRAM0[EM_LASER_POSWIDTH] <= CONFIG_MIN_LASER_POSWIDTH){//�ﵽ��Сֵ��ֹͣ�Լ�
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
		if(LD(R_STANDBY_KEY_NEGWIDTH_ADD_DOWN)){//������Ӱ���
			T10MS(T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_ADD_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_NEGWIDTH] = keyRuleAdd(NVRAM0[EM_LASER_NEGWIDTH], CONFIG_MAX_LASER_NEGWIDTH);
					updateNegWidthDisplay();
					if(NVRAM0[EM_LASER_NEGWIDTH] >= CONFIG_MAX_LASER_NEGWIDTH){//�ﵽ���ֵ��ֹͣ�Լ�
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
		if(LD(R_STANDBY_KEY_NEGWIDTH_DEC_DOWN)){//�����������
			T10MS(T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY, true, CONFIG_KEY_REPEAT_DELAY_TIME);
			if(LD(T_10MS_START * 16 + T10MS_NEGWIDTH_DEC_KEYDOWN_DELAY)){	
				if(LDP(SPCOIL_PS100MS) || LDN(SPCOIL_PS100MS)){
					NVRAM0[EM_LASER_NEGWIDTH] = keyRuleDec(NVRAM0[EM_LASER_NEGWIDTH], CONFIG_MIN_LASER_NEGWIDTH);
					updateNegWidthDisplay();
					if(NVRAM0[EM_LASER_NEGWIDTH] <= CONFIG_MIN_LASER_NEGWIDTH){//�ﵽ��Сֵ��ֹͣ�Լ�
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
				if(LD(R_LASER_TEMP_HIGH)){//���������±���
					updateWarnMsgDisplay(MSG_DIODE_HTEMP);
				}
				else if(LD(R_LASER_TEMP_LOW)){//����������NTC��·����
					updateWarnMsgDisplay(MSG_DIODE_LTEMP);
				}
				else if(LD(R_MCU_TEMP_HIGH)){//�������±���
					updateWarnMsgDisplay(MSG_ENVI_HTEMP);
				}
				else if(LD(R_MCU_TEMP_LOW)){//�������±���
					updateWarnMsgDisplay(MSG_ENVI_LTEMP);
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
			else{//�޹�����ʾ
				RRES(SPCOIL_BEEM_ENABLE);
				updateWarnMsgDisplay(MSG_NO_ERROR);
				standbyKeyTouchEnable(true);
			}
		}
		if(LDB(R_FAULT) && LDP(SPCOIL_PS100MS)){//�޹�����ʾ
			RRES(SPCOIL_BEEM_ENABLE);
			updateWarnMsgDisplay(MSG_NO_ERROR);
			standbyKeyTouchEnable(true);
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
			updateOptionDisplay();
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_STANDBY_KEY_ENTER_OPTION_DOWN);
		}else 
		if(LD(R_STANDBY_KEY_ENTER_SCHEME_DOWN)){//���SCHEME Ĭ����ʾ��һҳ
			//����FDRAM0->FDRAM1
			memcpy((uint8_t*)FDRAM1, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
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
			//ACOUSTIC ��ʼ��
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_CW){
				//�����������ù��ʵ�����
				SSET(R_ACOUSTIC_ENABLE);
				NVRAM0[EM_ACOUSTIC_TIME_STEP] = 1;//CWģʽÿ�μӼ���1��
				NVRAM0[EM_ACOUSTIC_ENERGY_STEP] = NVRAM0[EM_LASER_POWER_TOTAL] / 10;//CWģʽÿ�μӼ���
				NVRAM0[EM_ACOUSTIC_TIME] = 1;//��ʼΪ1��
				NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_TIME] * NVRAM0[EM_LASER_POWER_TOTAL] / 10;
				NVRAM0[EM_ACOUSTIC_TIME_MIN] = 1;//��С1��
				NVRAM0[EM_ACOUSTIC_TIME_MAX] = NVRAM0[EM_ACOUSTIC_TIME_STEP] * 100;//���100��
				NVRAM0[EM_ACOUSTIC_ENERGY_MIN] = NVRAM0[EM_ACOUSTIC_TIME_MIN] * NVRAM0[EM_LASER_POWER_TOTAL] / 10;
				NVRAM0[EM_ACOUSTIC_ENERGY_MAX] = NVRAM0[EM_LASER_POWER_TOTAL] / 10 * NVRAM0[EM_ACOUSTIC_TIME_MAX];
			}	
			if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
				//�������1��������ʾ��
				if((NVRAM0[EM_LASER_POSWIDTH] >= 1000) && (NVRAM0[EM_LASER_NEGWIDTH] >= 1000)){//���ڴ���2000mS
					SSET(R_ACOUSTIC_ENABLE);
					NVRAM0[EM_ACOUSTIC_TIME_STEP] = (NVRAM0[EM_LASER_POSWIDTH] / 1000) + (NVRAM0[EM_LASER_NEGWIDTH] / 1000);
					NVRAM0[EM_ACOUSTIC_TIME] = NVRAM0[EM_ACOUSTIC_TIME_STEP];
					
					NVRAM0[EM_ACOUSTIC_ENERGY_STEP] = (NVRAM0[EM_LASER_POSWIDTH] / 1000) * NVRAM0[EM_LASER_POWER_TOTAL] / 10;
					NVRAM0[EM_ACOUSTIC_ENERGY] = NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
					
					NVRAM0[EM_ACOUSTIC_TIME_MIN] = NVRAM0[EM_ACOUSTIC_TIME_STEP];					
					NVRAM0[EM_ACOUSTIC_TIME_MAX] = NVRAM0[EM_ACOUSTIC_TIME_MIN] * 100;//���100����
					NVRAM0[EM_ACOUSTIC_ENERGY_MIN] = NVRAM0[EM_ACOUSTIC_ENERGY_STEP];
					NVRAM0[EM_ACOUSTIC_ENERGY_MAX] = NVRAM0[EM_LASER_POWER_TOTAL] / 10 * NVRAM0[EM_ACOUSTIC_TIME_MAX];
				}
				else{
					RRES(R_ACOUSTIC_ENABLE);
				}
			}
			//������Ϣ
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
			
			//У���������
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
			
			//��ָʾ����
			setRedLaserPwm(NVRAM0[DM_AIM_BRG] * deviceConfig.aimGain);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;	
			RRES(R_STANDBY_KEY_STNADBY_DOWN);
			standbyKeyValue(0);
			//ҳ���л�
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//�л�����ҳ��
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
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_PARA){//�ȴ�������
		NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_DONE;	
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_READY_LOAD_DONE){//2���ڽ�̤�޷�ʹ��
		T100MS(T100MS_READY_BEEM_DELAY, true, CONFIG_STANDBY_BEEM_DELAY_TIME);//������ʱ����ʱ2000mS �򿪼�ʱ��		
		if(LD(T_100MS_START * 16 + T100MS_READY_BEEM_DELAY) && LDB(R_FOOTSWITCH_PRESS)){
			T100MS(T100MS_READY_BEEM_DELAY, false, 3);
			readyPageTouchEnable(1);
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//�л�����ҳ��
			SetScreen(NVRAM0[EM_DC_PAGE]);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
		}
		else{
			if(LD(R_STANDBY_KEY_STNADBY_UP)){//REDAY ����
				RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
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
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_WEAR_SAFETY;//�л�����ҳ��
						SetScreen(NVRAM0[EM_DC_PAGE]);
					}
				}
				if(LDN(R_FOOTSWITCH_PRESS)){
					RRES(SPCOIL_BEEM_ENABLE);
					if(NVRAM0[EM_DC_PAGE] != GDDC_PAGE_READY){
						NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//�л�����ҳ��
						SetScreen(NVRAM0[EM_DC_PAGE]);
					}
				}
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_DONE;
			}
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_WAIT_TRIGGER){//�ȴ���������	
		if(LD(R_ENGINEER_MODE)){//����ģʽ��ʾ������Ϣ	
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
					if(NVRAM0[EM_ACOUSTIC_ENERGY] >= NVRAM0[EM_ACOUSTIC_ENERGY_MAX]){//�ﵽ���ֵ��ֹͣ�Լ�
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
					if(NVRAM0[EM_ACOUSTIC_ENERGY] <= NVRAM0[EM_ACOUSTIC_ENERGY_MIN]){//�ﵽ���ֵ��ֹͣ�Լ�
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
					if(NVRAM0[EM_ACOUSTIC_TIME] >= NVRAM0[EM_ACOUSTIC_TIME_MAX]){//�ﵽ���ֵ��ֹͣ�Լ�
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
					if(NVRAM0[EM_ACOUSTIC_TIME] <= NVRAM0[EM_ACOUSTIC_TIME_MIN]){//�ﵽ���ֵ��ֹͣ�Լ�
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
		if(LD(R_STANDBY_KEY_STNADBY_UP) || LD(R_FAULT)){//�ص��ȴ�״̬
			EDLAR();//ֹͣ����
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;
			UPDAC0();UPDAC1();
			//��Ⱥ켤��
			setRedLaserPwm(0);
			T100MS(T100MS_READY_BEEM_DELAY, false, 3);//ֹͣ2���ʱ��
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//�л�����ҳ��
			SetScreen(NVRAM0[EM_DC_PAGE]);//�л�����ҳ��
			updateStandbyDisplay();
			standbyKeyValue(false);
			if(LD(R_STANDBY_KEY_STNADBY_UP)){
				RRES(R_STANDBY_KEY_STNADBY_UP);
			}
			updateWarnMsgDisplay(MSG_NO_ERROR);//��ʾ������Ϣ
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			return;
		}
		if(LD(MR_FOOSWITCH_HAND_SWITCH)){//�����ش���
			if(LDP(R_FOOTSWITCH_PRESS)){//���伤��
				sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
				NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_SPK_FREQ;					
				sPlcSpeakerFreq(NVRAM0[SPREG_BEEM_FREQ]);
				readyPageTouchEnable(0);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				SSET(SPCOIL_BEEM_ENABLE);//��������
			}
		}
		else{//��ƽ����
			if(LD(R_FOOTSWITCH_PRESS)){//���伤��	
				sPlcSpeakerVolume(NVRAM0[DM_BEEM_VOLUME]);
				NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_SPK_FREQ;					
				sPlcSpeakerFreq(NVRAM0[SPREG_BEEM_FREQ]);
				readyPageTouchEnable(0);
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_EMITING;				
				STLAR();
				SSET(SPCOIL_BEEM_ENABLE);//��������
			}	
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LASER_EMITING){//��������READYҳ��
		if(LDP(SPCOIL_PS10MS)){
			ADLS1(EM_LASER_TRIG_TIME);
		}
		if(LDP(SPCOIL_PS10MS) && LaserFlag_Emiting){
			ADLS1(EM_LASER_RELEASE_TIME);
		}
		if(LDP(SPCOIL_PS100MS)){//ÿ��1Sˢ���ۼ�ʱ�������
			updateReleaseTimeEnergy();//�����ۼƷ���ʱ�������
		}
		if(LD(R_ENGINEER_MODE)){//����ģʽ��ʾ������Ϣ	
			if(LDP(SPCOIL_PS1000MS)){		
				updateDebugInfo();
			}
		}		
		if(LD(R_STANDBY_KEY_STNADBY_UP) || LD(R_FAULT)){//�ص��ȴ�״̬
			EDLAR();//ֹͣ����
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;
			UPDAC0();UPDAC1();
			setRedLaserPwm(0);
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//�л�����ҳ��
			SetScreen(NVRAM0[EM_DC_PAGE]);//�л�����ҳ��
			updateStandbyDisplay();
			standbyKeyValue(0);
			if(LD(R_STANDBY_KEY_STNADBY_UP)){
				RRES(R_STANDBY_KEY_STNADBY_UP);
			}
			updateWarnMsgDisplay(MSG_NO_ERROR);//��ʾ������Ϣ
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
			return;
		}
		else if(LD(MR_FOOSWITCH_HAND_SWITCH)){//�����ش���
			if(LDP(R_FOOTSWITCH_PRESS)){//�رռ���
				EDLAR();
				RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				readyPageTouchEnable(1);
				printf("%s,%d,%s:hand switch mode,footswitch press,stop Laser emit req!!!\n", __FILE__, __LINE__, __func__);
			}
		}
		else{
			if(LDB(R_FOOTSWITCH_PRESS)){//�رռ���
				EDLAR(); 
				RRES(SPCOIL_BEEM_ENABLE);//�رշ�����
				NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LASER_WAIT_TRIGGER;
				readyPageTouchEnable(1);
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
		if(LD(R_OPTION_KEY_BEEM_VOLUME_ADD_DOWN)){
			if(NVRAM0[DM_BEEM_VOLUME] < CONFIG_BEEM_MAX_VOLUME){
				NVRAM0[DM_BEEM_VOLUME] += 1;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
				SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//���½�����
			}
			RRES(R_OPTION_KEY_BEEM_VOLUME_ADD_DOWN);
		}
		if(LD(R_OPTION_KEY_BEEM_VOLUME_DEC_DOWN)){
			if(NVRAM0[DM_BEEM_VOLUME] > 0){
				NVRAM0[DM_BEEM_VOLUME] -= 1;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXTDISPLAY_BEEM_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
				SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEM_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//���½�����
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
		if(LD(R_OPTION_KEY_RESTORE_DOWN)){//�ָ�Ĭ��ֵ
				//optionKeyEnable(false);//��������
				loadDefault();
				lockPreScheme();
				NVFSAVE();//ǿ�Ƹ���NVRAM
				updateOptionDisplay();//����Option��ʾ
				SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));//���±�������
				//optionKeyEnable(true);//��������
				NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
				SetScreen(NVRAM0[EM_DC_PAGE]);
				RRES(R_OPTION_KEY_RESTORE_DOWN);
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
		
		if(LD(R_SCHEME_KEY_OK_DOWN)){//ȷ��
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];//ѡ��������Ч
			loadScheme();
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//�л�����ҳ��						
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_OK_DOWN);
		}
		if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//ȡ��
			//��FDRAM1�лָ�FDRAM0
			memcpy((uint8_t*)FDRAM0, (uint8_t*)FDRAM1, (CONFIG_FDRAM_SIZE*2));
			loadScheme();//FD->EM
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//�л�����ҳ��						
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		if(LD(R_SCHEME_KEY_RENAME_DOWN)){//����
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//��EM_SCHEME_NUM_TMPָ������Ƹ���RENAME�����
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM0 + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_RENAME_DOWN);
		}
		if(LD(R_SCHEME_KEY_NEXT_SCHEME)){//��һҳ->�ڶ�ҳ
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
			
		if(LD(R_SCHEME_KEY_OK_DOWN)){//ȷ��
			NVRAM0[DM_SCHEME_NUM] = NVRAM0[EM_SCHEME_NUM_TMP];
			loadScheme();
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//�л�����ҳ��						
			SetScreen(NVRAM0[EM_DC_PAGE]);				
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_OK_DOWN);
		}
		if(LD(R_SCHEME_KEY_CANCEL_DOWN)){//ȡ��
			//��FDRAM1�лָ�FDRAM0
			memcpy((uint8_t*)FDRAM0, (uint8_t*)FDRAM1, (CONFIG_FDRAM_SIZE*2));
			loadScheme();//FD->EM
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//�л�����ҳ��						
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			updateStandbyDisplay();
			returnStandbyDisplay();
			RRES(R_SCHEME_KEY_CANCEL_DOWN);
		}
		if(LD(R_SCHEME_KEY_RENAME_DOWN)){//����
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_RENAME;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_RENAME;
			//��EM_SCHEME_NUM_TMPָ������Ƹ���RENAME�����
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXTDISPLAY_NEWNAME, (uint8_t*)(FDRAM0 + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_SCHEME_KEY_RENAME_DOWN);
		}
		if(LD(R_SCHEME_KEY_LAST_SCHEME)){//�ڶ�ҳ->��һҳ
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
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			__set_PRIMASK(0);//�ر��ж�
			sPlcNvramClear();//���NVRAM
			sPlcFdramClear();//���FDRAM
			sPlcDeviceConfigClear();//���config
			resetGddcHmi();
			softDelayMs(4000);//�ȴ�4��
			REBOOT();	
		}
		else if(LD(R_SAVE_EPROM)){//�������Ƶ�EPROM
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			__set_PRIMASK(0);//�ر��ж�
			sPlcNvramSave();//����NVRAM
			sPlcFdramSave();//����FDRAM
			saveDeviceConfig();//��������
			resetGddcHmi();
			softDelayMs(4000);//�ȴ�4��
			REBOOT();	
		}
		else if(LD(R_CLEAR_CRC)){//����̼�CRC
			tmp8 = 0;
			__set_PRIMASK(0);//�ر��ж�
			epromWriteByte((CONFIG_EPROM_LCD_FW_CRC + 0), &tmp8);
			epromWriteByte((CONFIG_EPROM_LCD_FW_CRC + 1), &tmp8);
			epromWriteByte((CONFIG_EPROM_LCD_FW_CRC + 2), &tmp8);
			epromWriteByte((CONFIG_EPROM_LCD_FW_CRC + 3), &tmp8);
			
			epromWriteByte((CONFIG_EPROM_MCU_FW_CRC + 0), &tmp8);
			epromWriteByte((CONFIG_EPROM_MCU_FW_CRC + 1), &tmp8);
			epromWriteByte((CONFIG_EPROM_MCU_FW_CRC + 2), &tmp8);
			epromWriteByte((CONFIG_EPROM_MCU_FW_CRC + 3), &tmp8);
			resetGddcHmi();
			softDelayMs(4000);//�ȴ�4��
			REBOOT();	
		}
		else if(LD(R_UPDATE_BOOTLOAD_REQ)){//����Boot load����
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
		else if(LD(R_UPDATE_BOOTLOAD_YES)){//ִ��Bootload����	
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DISGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			confirmBootloadUpdate();
		}
		else if(LD(R_UPDATE_BOOTLOAD_NO)){//����Bootload��������
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




