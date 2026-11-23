//----------------------------------------------------------------------------
// 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
// 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
// 请以 UTF-8 编码保存, 并在文件头保留本注释。
//----------------------------------------------------------------------------
#include "dcHmiApp.h"
#include "treatment.h"
#include "minicsvApp.h"//U盘CSV导入导出/U盘在位检测
/*****************************************************************************/
uint8_t hmiCmdBuffer[CMD_MAX_SIZE];//指令缓存
static int8_t standbyKeyTouchEnableStatus = -1;
uint16_t hmiCmdSize;//已缓冲的指令数
static MSG_ID_T MsgId;//当前显示的信息ID
uint8_t CcmRamBuf[BOOTLOAD_BUF_SIZE] SPLC_PLACE_AT(10000000);//Bootload 升级块缓冲 8KB（CCM 头部）CCMDATARAM_BASE=0x10000000
/* CCM RAM(0x10000000) 不支持 DMA 访问。当前 FATFS 底层为 USB Host MSC，usbh_conf.c 中
   dma_enable=DISABLE（CPU 轮询搬运），本缓冲经 f_read 读取安全；若未来启用 USB/SDIO DMA，
   禁止将本缓冲直接用作 DMA 目标，需先经 SRAM 中转。
   CCM 剩余空间(0x10002000 起)当前未由 scatter 文件分配(本分支 .sct 无 RW_CCM 区)，
   如需在 CCM 放置普通变量需先在 MDK 目标选项中补充 RW_CCM 执行区；
   ADC DMA 采样缓冲(adcDmaBuffer0/1)已标注 dma_ram 区强制留在 SRAM。 */
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
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Please Standby,Do Not Power Off!!"));
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
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Mount usb disk errror,exit update!"));
		return false;
	}
	vTaskDelay(6000);
	//打开文件
	retUsbH = f_open(&BootLoadFile, (const TCHAR*)(BOOTLOAD_FILENAME), FA_OPEN_EXISTING | FA_READ);//
	if(retUsbH != FR_OK){//读取失败跳过固件更新直接运行程序
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		printf("BootLoader:Open %s fail,unmount usb disk,ECODE=0x%02XH\n", BOOTLOAD_FILENAME, retUsbH);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Open file errror,exit update!"));
		return false;
	}
	//检查文件大小
	f_lseek(&BootLoadFile, 0);//读取指针移动到开头
	if(f_size(&BootLoadFile) > BOOTLOADER_FLASH_SIZE){//MCU固件大于FLSAH容量
		f_close(&BootLoadFile);
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		printf("BootLoader:File %s is over length, close file and unmount disk!\n", BOOTLOAD_FILENAME);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("File is over length,exit update!"));
		return false;
	}
	vTaskDelay(800);
	//计算新固件CRC值（分块读取+硬件CRC流式累加）
	newBootloadCrc32 = 0;
	crc32Clear();
	LastPGAddress = BOOTLOADER_FLASH_START_ADDRESS;
	while(readflag){
		/* 分块读取固件文件，块大小 BOOTLOAD_BUF_SIZE(8KB)，复用 CCM 缓冲 */
		f_read(&BootLoadFile, CcmRamBuf, BOOTLOAD_BUF_SIZE, (void*)&bytesread);
		if(bytesread == 0){//文件已读完
			break;
		}
		newBootloadCrc32 = crc32Calculate(CcmRamBuf, bytesread);//CRC32 累加（硬件CRC不重置）
		/* Temp variable */
		TmpReadSize = bytesread;
		/* The read data < "BOOTLOAD_BUF_SIZE" 字节 */
		if(TmpReadSize < BOOTLOAD_BUF_SIZE){
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
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)"File is same,skip update...");
		vTaskDelay(800);
		return false;
	}
	else{
		printf("BootLoader:old crc%08X: and new crc:%08X is not same,need confirm update!\n", BootloadCrc , newBootloadCrc32);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)"Confirm update...YES OR NO!!!");
		
		SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, true);
		SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, true);
		
		SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, true);	
		SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, true);	
		
		vTaskDelay(800);
		return true;
	}
}
void confirmBootloadUpdate(void){//执行Bootload更新（分块边读边写：正常上下文读USB块，关中断写Flash块，块缓冲8KB）
	uint32_t i;
	uint32_t tmpWord;
	uint32_t remain;
	uint32_t fileOffset = 0;
	uint32_t bytesread = 0;
	uint8_t  readflag = 1;
	uint8_t  firstBlock = 1;
	FRESULT res;

	/* 重新挂载并打开固件文件（正常上下文，USB 协议栈依赖中断，必须开中断读） */
	f_mount(&USBH_fatfs, (const TCHAR*)FATFS_ROOT, 1);
	res = f_open(&BootLoadFile, (const TCHAR*)(BOOTLOAD_FILENAME), FA_OPEN_EXISTING | FA_READ);
	if(res != FR_OK){//打开失败，保留旧固件
		printf("BootLoader:Open %s fail,exit update!\n", BOOTLOAD_FILENAME);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Open file fail,Game Over!"));
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		return;
	}
	if(f_size(&BootLoadFile) > BOOTLOADER_FLASH_SIZE){//超长防护
		printf("BootLoader:File is over length, exit update!\n");
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("File is over length,exit update!"));
		f_close(&BootLoadFile);
		HAL_FLASH_Lock();//恢复锁定
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		return;
	}
	f_lseek(&BootLoadFile, 0);//读取指针移动到开头
	HAL_FLASH_Unlock();//解锁FLASH锁定（无时序敏感，提前到循环外）
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGSERR | FLASH_FLAG_WRPERR);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Start update new bootload..."));

	while(readflag){
		/* 正常上下文读一块（USB MSC 底层轮询需中断驱动，禁止在关中断段读取） */
		f_read(&BootLoadFile, CcmRamBuf, BOOTLOAD_BUF_SIZE, (void*)&bytesread);
		if(bytesread == 0){//文件已读完
			break;
		}
		if(bytesread < BOOTLOAD_BUF_SIZE){
			readflag = 0;
		}
		/* 关键写段：关调度+关中断+关SysTick，保证 Flash 编程时序 */
		vTaskSuspendAll();//禁用任务切换
		__disable_irq();//关闭中断
		SysTick->CTRL = 0;//关键代码
		if(firstBlock){//第一块写入前：整区擦除+查空（与旧版一次性流程等价，仅执行一次）
			firstBlock = 0;
			if (FLASH_If_EraseBootload() != 0x00){//擦除BOOTLOAD 失败
				SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
				__enable_irq();
				(void)xTaskResumeAll();
				HAL_FLASH_Lock();//恢复锁定
				printf("BootLoader:Erase bootload fail, GameOver!!!!!\n");
				SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Erase bootload fail,Game Over!"));
				f_close(&BootLoadFile);
				f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
				return;
			}
			if(checkBlank(BOOTLOADER_FLASH_START_ADDRESS, BOOTLOADER_FLASH_SIZE)){//FLASH 查空
				printf("Bootloader:Check mcu booload blank sucess.\n");
				SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Erase bootload sucessful..."));
			}
			else{
				SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
				__enable_irq();
				(void)xTaskResumeAll();
				HAL_FLASH_Lock();//恢复锁定
				printf("Bootloader:Check mcu booload blank not empty!\n");
				SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Erase bootload fail,Game Over!"));
				f_close(&BootLoadFile);
				f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
				return;
			}
		}
		/* 写当前块（块内 4 字节对齐；尾部不足 4 字节补 0xFF，与文件 CRC 补全逻辑一致） */
		for(i = 0; i < bytesread; i += 4){
			tmpWord = 0xFFFFFFFFU;
			remain = bytesread - i;
			if(remain > 4){ remain = 4; }
			memcpy(&tmpWord, CcmRamBuf + i, (size_t)remain);//小端：剩余字节填低字节，高位保持0xFF
			if(FLASH_lf_WriteBootload((BOOTLOADER_FLASH_START_ADDRESS + fileOffset + i), tmpWord) != 0x00){
				printf("BootLoader:Write mcu bootload fail,GameOver!!!!!\n");//写入FLASH错误
			}
		}
		fileOffset += bytesread;
		/* 恢复：先恢复SysTick，再开中断，再恢复调度 */
		SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
		__enable_irq();
		(void)xTaskResumeAll();
	}
	HAL_FLASH_Lock();
	printf("BootLoader:Update new bootload done...\n");
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)"Update new bootload done...");
	softDelayMs(1000);
	//检查已写入的Bootload是否正确（全区读回：未写的0xFF填充区与文件CRC的补全逻辑一致）
	printf("BootLoader:Start checksum new bootload...\n");
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Start checksum new bootload..."));
	BootloadCrc = getOriginBootloadCrc();
	softDelayMs(1000);
	if(BootloadCrc == newBootloadCrc32){
		printf("BootLoader:Checksum bootload pass,flash crc:%08X, file crc:%08X\n", BootloadCrc , newBootloadCrc32);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Checksum bootload pass,power cycle the system"));
	}
	else{
		printf("BootLoader:Checksum bootload fail,flash crc:%08X, file crc:%08X\n,Game Over!!!\n", BootloadCrc , newBootloadCrc32);
		SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)("Checksum bootload fail,Game Over!!!"));
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
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)(""));
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);
}

void optionKeyEnable(uint8_t enable){//选项界面按键锁定
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_BEEP_VOLUME_ADD, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_BEEP_VOLUME_INC, enable);
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
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEP_VOLUME, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, enable);
	softDelayMs(1);
	SetControlEnable(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_KEY_RESTORE, enable);
}
void standbyDebugInfoVisiable(int8_t enable){//Standby调试信息可见
	SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_READY, GDDC_PAGE_STANDBY_TEXT_DEBUG, enable);
	SetControlVisiable(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, enable);
	//患者注册/编辑页不再设置调试文本控件, 无需切换可见性
}

void updateDiagnosisCaliInfo(void){//更新功率校准动态信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%4.1fC", (NVRAM0[EM_LASER_A_DIODE_TEMP] / 10.0F));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_DIODE_TEMP, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%4.1fC", (NVRAM0[EM_HWATER_TEMP] / 10.0F));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_HWATER_TEMP, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%4.1fC", (NVRAM0[EM_CWATER_TEMP] / 10.0F));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CWATER_TEMP, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1f%%", ((float)NVRAM0[EM_TPID0_OUT] * 100.0F / CONFIG_DAC_MAXBIT_CH8));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_PID0, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1f%%", ((float)NVRAM0[EM_TPID1_OUT] * 100.0F / CONFIG_DAC_MAXBIT_CH9));
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_PID1, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%04d", NVRAM0[EM_HT0_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_HT0, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%04d", NVRAM0[EM_HT1_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_HT1, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH0_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH0, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH1_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH1, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH2_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH2, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH3_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH3, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH4_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH4, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH5_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH5, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH6_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH6, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%5.1fA", NVRAM0[EM_LD_CH7_CURRENT] / 10.0F);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CDISP_CH7, (uint8_t*)dispBuf);

}

void updateDebugInfo(void){//更新Standby调试信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "LT:%05d,HT:%05d,MT:%05d,FPD:%05d,LPD:%05d,TEC:%05d,TR:%05d", \
	NVRAM0[EM_LASER_A_DIODE_TEMP], NVRAM0[EM_HT0_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[SPREG_ADC_54], NVRAM0[SPREG_ADC_55], NVRAM0[SPREG_DAC_8], NVRAM0[DM_TREATMENT_NUM]);
	switch(NVRAM0[EM_DC_PAGE]){
		case GDDC_PAGE_STANDBY:{
			SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_DEBUG, (uint8_t*)dispBuf);
			break;
		}	
		case GDDC_PAGE_READY:{
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		case GDDC_PAGE_LIST_TREATMENT:{
			SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
			break;
		}
		//患者注册/编辑页无调试文本控件, 不在此更新
		default:break;
	}
#if defined(LYPE_MCU_1V0_20260106)
	sprintf(dispBuf, "LT:%05d,WHT:%05d,WCT%05d,AT%05d,MT:%05d,FPD:%05d,LPD:%05d,PID:%05d", \
	NVRAM0[EM_LASER_A_DIODE_TEMP], NVRAM0[EM_HWATER_TEMP], NVRAM0[EM_CWATER_TEMP], NVRAM0[EM_HDC1080_TEMP], NVRAM0[EM_MCU_TEMP], \
	NVRAM0[EM_LASER_FPD], NVRAM0[EM_LASER_LPD], NVRAM0[EM_TPID0_OUT]);
	switch(NVRAM0[EM_DC_PAGE]){
		case GDDC_PAGE_STANDBY:{
			SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_DEBUG, (uint8_t*)dispBuf);
			break;
		}	
		case GDDC_PAGE_READY:{
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_DEBUG, (uint8_t*)dispBuf);
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
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DIAGNOSIS_CALI_TEXT_0P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH1
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr1[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DIAGNOSIS_CALI_TEXT_1P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH2
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr2[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DIAGNOSIS_CALI_TEXT_2P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH3
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr3[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DIAGNOSIS_CALI_TEXT_3P5 + i), (uint8_t*)dispBuf);
	}	
	for(i = 0;i < 20; i++){//CH4
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr4[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DIAGNOSIS_CALI_TEXT_4P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH5
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr5[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DIAGNOSIS_CALI_TEXT_5P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH6
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr6[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DIAGNOSIS_CALI_TEXT_6P5 + i), (uint8_t*)dispBuf);
	}
	for(i = 0;i < 20; i++){//CH7
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%4.1f", deviceConfig.calibrationPwr7[i] / 10.0F);
		SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, (GDDC_PAGE_DIAGNOSIS_CALI_TEXT_7P5 + i), (uint8_t*)dispBuf);
	}
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH0, (uint8_t*)dispBuf);
	
  memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH1, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH2, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH3, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH4, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH5, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH6, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "000");
	SetTextValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH7, (uint8_t*)dispBuf);
	
	SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH0, false);
	SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH1, false);
	SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH2, false);
	SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH3, false);
	SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH4, false);
	SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH5, false);
	SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH6, false);
	SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_SAVE_CH7, false);
}

void updateDiagnosis(void){//更新诊断信信息
	//uint8_t i;
	//char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	//从NVRAM中更新文本框	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_YEAR , deviceConfig.mfg_year, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_MONTH , deviceConfig.mfg_month, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_DAY , deviceConfig.mfg_day, 1, 0);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_SN, (uint8_t*)deviceConfig.serialNumber);
	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_RED_LED_DC , deviceConfig.redLedDc, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_GREEN_LED_DC , deviceConfig.greenLedDc, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_BLUE_LED_DC , deviceConfig.blueLedDc, 1, 0);
	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_SET_AIM_GAIN, deviceConfig.redAimGain, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIBER_DETECT, deviceConfig.fiberDetect, 1, 0);
	
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_DIODE_A_TEMP, deviceConfig.laserDiodeA_Temp, 1, 0);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_DIODE_B_TEMP, deviceConfig.laserDiodeB_Temp, 1, 0);
	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);	
	SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);	
	SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);	
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);

	SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, false);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)"");
	
	if(deviceConfig.normalOpenInterLock == 0){
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_OPEN_ILOCK, true);
	}
	else{
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_OPEN_ILOCK, false);
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
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO0, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "A16-A31:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_ADC_16], NVRAM0[SPREG_ADC_17], NVRAM0[SPREG_ADC_18], NVRAM0[SPREG_ADC_19], \
	NVRAM0[SPREG_ADC_20], NVRAM0[SPREG_ADC_21], NVRAM0[SPREG_ADC_22], NVRAM0[SPREG_ADC_23], \
	NVRAM0[SPREG_ADC_24], NVRAM0[SPREG_ADC_25], NVRAM0[SPREG_ADC_26], NVRAM0[SPREG_ADC_27], \
	NVRAM0[SPREG_ADC_28], NVRAM0[SPREG_ADC_29], NVRAM0[SPREG_ADC_30], NVRAM0[SPREG_ADC_31]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO1, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "A32-A47:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_ADC_32], NVRAM0[SPREG_ADC_33], NVRAM0[SPREG_ADC_34], NVRAM0[SPREG_ADC_35], \
	NVRAM0[SPREG_ADC_36], NVRAM0[SPREG_ADC_37], NVRAM0[SPREG_ADC_38], NVRAM0[SPREG_ADC_39], \
	NVRAM0[SPREG_ADC_40], NVRAM0[SPREG_ADC_41], NVRAM0[SPREG_ADC_42], NVRAM0[SPREG_ADC_43], \
	NVRAM0[SPREG_ADC_44], NVRAM0[SPREG_ADC_45], NVRAM0[SPREG_ADC_46], NVRAM0[SPREG_ADC_47]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO2, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "A48-A55:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_ADC_48], NVRAM0[SPREG_ADC_49], NVRAM0[SPREG_ADC_50], NVRAM0[SPREG_ADC_51], \
	NVRAM0[SPREG_ADC_52], NVRAM0[SPREG_ADC_53], NVRAM0[SPREG_ADC_54], NVRAM0[SPREG_ADC_55]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO3, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "A56-A63:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_ADC_56], NVRAM0[SPREG_ADC_57], NVRAM0[SPREG_ADC_58], NVRAM0[SPREG_ADC_59], \
	NVRAM0[SPREG_ADC_60], 0, 0, 0);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO4, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "D0-17:%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d,%05d", \
	NVRAM0[SPREG_DAC_0], NVRAM0[SPREG_DAC_1], NVRAM0[SPREG_DAC_2], NVRAM0[SPREG_DAC_3], \
	NVRAM0[SPREG_DAC_4], NVRAM0[SPREG_DAC_5], NVRAM0[SPREG_DAC_6], NVRAM0[SPREG_DAC_7], \
	NVRAM0[SPREG_DAC_8], NVRAM0[SPREG_DAC_9], NVRAM0[SPREG_DAC_10], NVRAM0[SPREG_DAC_11], \
	NVRAM0[SPREG_DAC_12], NVRAM0[SPREG_DAC_13], NVRAM0[SPREG_DAC_14], NVRAM0[SPREG_DAC_15], \
	NVRAM0[SPREG_DAC_16], NVRAM0[SPREG_DAC_17]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO5, (uint8_t*)dispBuf);
	
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
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO6, (uint8_t*)dispBuf);

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
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO7, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "DIODE-AT:%05d,COUPLE-AT:%05d,CRYSTAL-AT0:%05d,CRYSTAL-AT01:%05d", \
	NVRAM0[EM_LASER_A_DIODE_TEMP], NVRAM0[EM_LASER_A_COUPLER_TEMP], NVRAM0[EM_LASER_A_CRYST0_TEMP], NVRAM0[EM_LASER_A_CRYST1_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO8, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "DIODE-BT:%05d,COUPLE-BT:%05d,CRYSTAL-BT0:%05d,CRYSTAL-BT01:%05d", \
	NVRAM0[EM_LASER_B_DIODE_TEMP], NVRAM0[EM_LASER_B_COUPLER_TEMP], NVRAM0[EM_LASER_B_CRYST0_TEMP], NVRAM0[EM_LASER_B_CRYST1_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO9, (uint8_t*)dispBuf);

	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "HT0:%05d,HT1:%05d,HT2:%05d,HT3:%05d,WHT:%05d,WCT:%05d", \
	NVRAM0[EM_HT0_TEMP], NVRAM0[EM_HT1_TEMP], NVRAM0[EM_HT2_TEMP], NVRAM0[EM_HT3_TEMP], NVRAM0[EM_HWATER_TEMP], NVRAM0[EM_CWATER_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO10, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "AT0:%05d,AT1:%05d,TMCU:%05d,VBAT:%05d,SET DIODE-AT:%05d,SET DIODE_BT:%05d,TEC0:%05d,TEC1:%05d", \
	NVRAM0[EM_AMBIENT0_TEMP], NVRAM0[EM_AMBIENT1_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[EM_MBAT_TEMP], deviceConfig.laserDiodeA_Temp, deviceConfig.laserDiodeB_Temp,NVRAM0[EM_TPID0_OUT], NVRAM0[EM_TPID1_OUT]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO11, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "FAN0-3 GET:%05d,%05d,%05d,%05d,FAN0-3 SET:%05d,%05d,%05d,%05d", \
	NVRAM0[EM_FAN0_GET_SPEED], NVRAM0[EM_FAN1_GET_SPEED], NVRAM0[EM_FAN2_GET_SPEED], NVRAM0[EM_FAN3_GET_SPEED], \
	NVRAM0[EM_FAN0_SET_SPEED], NVRAM0[EM_FAN1_SET_SPEED], NVRAM0[EM_FAN2_SET_SPEED], NVRAM0[EM_FAN3_SET_SPEED]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO12, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "FAN4-7 GET:%05d,%05d,%05d,%05d,FAN4-7 SET:%05d,%05d,%05d,%05d", \
	NVRAM0[EM_FAN4_GET_SPEED], NVRAM0[EM_FAN5_GET_SPEED], NVRAM0[EM_FAN6_GET_SPEED], NVRAM0[EM_FAN7_GET_SPEED], \
	NVRAM0[EM_FAN4_SET_SPEED], NVRAM0[EM_FAN5_SET_SPEED], NVRAM0[EM_FAN6_SET_SPEED], NVRAM0[EM_FAN7_SET_SPEED]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO13, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "HDC1080 TEMP:%05d, HDC1080 HUMIDITY:%05d", NVRAM0[EM_HDC1080_TEMP], NVRAM0[EM_HDC1080_HUMIDITY]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS_RAW, GDDC_PAGE_DIAGNOSIS_RAW_TEXT_INFO14, (uint8_t*)dispBuf);
}

void updateDiagnosisInfo(void){//更新诊断信息
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "FSNC:%1d,FSNO:%1d,ESTOP:%d,ILOCK:%1d,FB:%1d,FPD:%05d,LPD:%05d,RESET:%1d", \
	LD(X_FOOTSWITCH_NC), LD(X_FOOTSWITCH_NO), LD(X_ESTOP_NC), LD(X_INTERLOCK_NC), LD(X_FIBER_PROBE),NVRAM0[SPREG_ADC_47],NVRAM0[SPREG_ADC_48],LD(Y_ESTOP_RESET));
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_INFO0, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "LDT:%05d,COT:%05d,CRYT0:%05d,CRYT1:%05d,HT0:%05d,HT1:%05d,HT2:%05d,HT3:%05d", \
	NVRAM0[EM_LASER_A_DIODE_TEMP], NVRAM0[EM_LASER_A_COUPLER_TEMP], NVRAM0[EM_LASER_A_CRYST0_TEMP], NVRAM0[EM_LASER_A_CRYST1_TEMP], \
	NVRAM0[EM_HT0_TEMP], NVRAM0[EM_HT1_TEMP], NVRAM0[EM_HT2_TEMP], NVRAM0[EM_HT3_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_INFO1, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "WHOTT:%05d,WCOLT:%05d,MCUT:%05d,BATT:%05d", \
	NVRAM0[EM_HWATER_TEMP], NVRAM0[EM_CWATER_TEMP], NVRAM0[EM_MCU_TEMP], NVRAM0[EM_MBAT_TEMP]);
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_INFO2, (uint8_t*)dispBuf);
		
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "FAN:%05d,WFSW NC:%1d,WFSW NO:%1d", \
	NVRAM0[EM_FAN0_SET_SPEED], LD(SPCOIL_WFSWITCH_PLUG), LD(SPCOIL_WFSWITCH_NO));
	SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_INFO3, (uint8_t*)dispBuf);
	
	//刷新RTC
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_RTC_YEAR, (NVRAM0[EM_RTC_YEAR] + 2000), 0, 4);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_RTC_MONTH, NVRAM0[EM_RTC_MONTH], 0, 2);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_RTC_DAY, NVRAM0[EM_RTC_DAY], 0, 2);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_RTC_HOURS, NVRAM0[EM_RTC_HOURS], 0, 2);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_RTC_MINUTES, NVRAM0[EM_RTC_MINUTES], 0, 2);
	SetTextInt32(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_RTC_SECONDS, NVRAM0[EM_RTC_SECONDS], 0, 2);
}

void updateSchemeDetail(int16_t classify, int16_t index){//更新选项界面方案名称
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	//uint8_t index;
	//index = NVRAM0[EM_SCHEME_NUM_TMP];
	switch(classify){
#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1470_980_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
		case SCHEME_PHLEBOLOGY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Phlebology");
			if(strlen((char*)sPhlebology[0].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sPhlebology[0].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sPhlebology[1].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sPhlebology[1].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sPhlebology[2].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sPhlebology[2].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}
			//方案3-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
			BatchEnd();

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);//禁止修改名称
			break;			
		}
		case SCHEME_PROCTOLOGY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Proctology");
			if(strlen((char*)sProctology[0].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[0].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[1].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[1].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[2].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[2].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[3].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[3].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[4].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[4].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sProctology[5].name) <= CONFIG_SCHEME_NAME_SIZE){
				strcpy(dispBuf, (char*)(sProctology[5].name));
				SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
			}	
			//方案6-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
			BatchEnd();

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);	

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);
			break;
		}
		case SCHEME_GYNECOLOGY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Gynecology");
			if(index < 16){//方案0-15
				if(strlen((char*)sGynecology[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[8].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[8].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[9].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[9].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[10].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[10].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[11].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[11].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[12].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[12].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[13].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[13].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[14].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[14].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[15].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[15].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, (uint8_t*)dispBuf);
				}			
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, true);
				BatchEnd();
				
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, true);
				BatchEnd();
				
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
				
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,true);					
			}
			else{
				if(strlen((char*)sGynecology[16].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[16].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[17].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[17].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
				}				
				if(strlen((char*)sGynecology[18].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[18].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[19].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[19].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[20].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[20].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[21].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[21].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sGynecology[22].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sGynecology[22].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
				}
				
				//方案5-15禁止选择
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
				BatchEnd();
				
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
				BatchEnd();

				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,true);
					
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);
			}
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);
			break;				
		}
		case SCHEME_ENT:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- ENT");
			if(strlen((char*)sENT[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[8].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[8].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[9].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[9].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[10].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[10].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[11].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[11].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[12].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[12].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[13].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[13].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[14].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[14].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sENT[15].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sENT[15].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, (uint8_t*)dispBuf);
			}	
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, true);
			BatchEnd();
					
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, true);
			BatchEnd();
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
					
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);		
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);
			break;
		}
#endif
		case SCHEME_NEUROSURGERY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Neurosurgery");
#if defined(APP_CONFIG_WAVE_1470_980_635)
			if(strlen((char*)sNeurosurgery[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
			}
			//方案4-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
			BatchEnd();
#endif
#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
			if(strlen((char*)sNeurosurgery[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sNeurosurgery[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sNeurosurgery[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}
			//方案4-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, false);		
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
			BatchEnd();
#endif
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);	

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);
			break;
		}
		case SCHEME_DERMATOLOGY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Dermatology");
			if(strlen((char*)sDermatology[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sDermatology[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sDermatology[8].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDermatology[8].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, (uint8_t*)dispBuf);
			}	
			//方案8-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);			
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
			BatchEnd();

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);		

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);
			break;
		}
		case SCHEME_LIPOSUCTION:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Liposuction");
			if(strlen((char*)sLiposuction[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}				
			if(strlen((char*)sLiposuction[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sLiposuction[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sLiposuction[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
			}		
			//方案7-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);	
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);			
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
			BatchEnd();

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);	
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);
			break;
		}
		case SCHEME_DENTISTRY:{	
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Dentistry");
			if(index < 16){//方案0-15
				if(strlen((char*)sDentistry[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[8].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[8].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[9].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[9].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[10].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[10].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[11].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[11].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[12].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[12].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[13].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[13].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[14].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[14].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[15].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[15].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, (uint8_t*)dispBuf);
				}	
				//方案0-15禁止选择
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);				
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, true);
				BatchEnd();
			
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);		
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);			
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);			
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, true);
				BatchEnd();

				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
					
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,true);	

				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);				
			}
			else{
				if(strlen((char*)sDentistry[16].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[16].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
				}	
				if(strlen((char*)sDentistry[17].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[17].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[18].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[18].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[19].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[19].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[20].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[20].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[21].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[21].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)sDentistry[22].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sDentistry[22].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
				}
				//方案0-15禁止选择
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);				
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
				BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
				BatchEnd();
				BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);		
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);			
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);			
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
				BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
				BatchEnd();			
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,true);
					
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);	

				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);
			}
			break;
		}
		case SCHMEM_THERAPY:{
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Therapy");
#if defined(APP_CONFIG_WAVE_1470_980_635)
			if(strlen((char*)sTherapy[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sTherapy[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, (uint8_t*)dispBuf);
			}		
			//方案8-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
			BatchEnd();
#endif
#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
			if(strlen((char*)sTherapy[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sTherapy[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sTherapy[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sTherapy[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}	
			//方案8-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, false);		
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
			BatchEnd();
#endif
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);	

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);
			break;
		}	
		case SCHEME_ENDOLIFT:{
#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Endolift");
			if(strlen((char*)sEndolift[0].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[0].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sEndolift[1].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[1].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sEndolift[2].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[2].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sEndolift[3].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[3].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sEndolift[4].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[4].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sEndolift[5].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[5].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sEndolift[6].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[6].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
			}
			if(strlen((char*)sEndolift[7].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[7].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sEndolift[8].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[8].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sEndolift[9].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[9].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, (uint8_t*)dispBuf);
			}	
			if(strlen((char*)sEndolift[10].name) <= CONFIG_SCHEME_NAME_SIZE){
					strcpy(dispBuf, (char*)(sEndolift[10].name));
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, (uint8_t*)dispBuf);
			}			
			//方案8-15禁止选择
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, false);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, false);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);			
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, false);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, false);
			BatchEnd();

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
				
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
			SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);		

			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, false);
#endif
			break;

		}
		case SCHEME_CUSTIOM:{
#if defined(APP_CONFIG_WAVE_1470_980_635)
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Custom");
#endif
			
#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
			SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_CLASSIFY, "- Custom");
#endif
			if(index < 16){
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_0])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_0], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_1])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_1], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_2])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_2], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_3])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_3], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_4])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_4], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_5])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_5], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_6])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_6], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_7])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_7], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_8])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_8], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_9])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_9], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_10])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_10], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_11])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_11], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_12])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_12], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_13])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_13], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_14])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_14], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_15])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_15], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, (uint8_t*)dispBuf);
				}
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,false);
				
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,true);	
			}
			else{
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_16])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_16], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_17])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_17], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_18])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_18], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_19])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_19], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_20])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_20], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_21])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_21], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_22])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_22], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_23])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_23], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_24])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_24], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_25])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_25], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_26])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_26], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_27])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_27], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_28])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_28], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_29])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_29], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_30])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_30], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, (uint8_t*)dispBuf);
				}
				if(strlen((char*)(&FDRAM1[FD_SCHEME_START_31])) <= CONFIG_SCHEME_NAME_SIZE){
					memcpy(dispBuf, (char*)&FDRAM1[FD_SCHEME_START_31], CONFIG_SCHEME_NAME_SIZE);
					SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, (uint8_t*)dispBuf);
				}
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE, true);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_LAST_PAGE,true);
				
				SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE, false);
				SetControlVisiable(GDDC_PAGE_SCHEME_DETAIL,GDDC_PAGE_SCHEME_DETAIL_KEY_NEXT_PAGE,false);	
			}		
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, true);
			BatchSetEnable(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, true);
			BatchEnd();
			
			BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_0, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_1, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_2, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_3, true);		
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_4, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_5, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_6, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_7, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_8, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_9, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_10, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_11, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_12, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_13, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_14, true);
			BatchSetVisible(GDDC_PAGE_SCHEME_DETAIL_TEXT_SCHEME_15, true);
			BatchEnd();
			
			SetControlEnable(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_KEY_RENAME, true);
			break;
		}
		default:{break;}
	}
	unselectSchemeAll();
	SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_DETAIL0, (uint8_t*)"");
	SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_DETAIL1, (uint8_t*)"");
}

void updateInformationDisplay(void){//更新信息界面显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	char *pMain, *pMonir;
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXT_TYPE, (uint8_t*)info_msg.TYPE);		

	memset(dispBuf, 0x0,sizeof(dispBuf));
	sprintf(dispBuf, "SN: %s", (uint8_t*)deviceConfig.serialNumber);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXT_SN, (uint8_t*)dispBuf);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXT_LASER_WAVELENGTH, (uint8_t*)info_msg.WAVELENGTH);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXT_MAX_LASER_POWER, (uint8_t*)info_msg.LASER_POWER);
	
	memset(dispBuf, 0x0,sizeof(dispBuf));
	sprintf(dispBuf, "%s", (char*)HW_VERSION);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXT_HARDWARE_VERSION, (uint8_t*)dispBuf);
	
	memset(dispBuf, 0x0,sizeof(dispBuf));
	pMain = (char*)(BOOTLOAD_MAIN_ADDRESS);
	pMonir = (char*)(BOOTLOAD_MINOR_ADDRESS);
	if((*pMain >='0' && *pMain <= '9') && (*pMonir >= '0' && *pMonir <= '9')){
		sprintf(dispBuf, "%s-%s:%s  Bootload Ver: %c.%c", (char*)SW_VERSION, __DATE__, __TIME__, *pMain, *pMonir);
		SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXT_SOFTWARE_VERSION, (uint8_t*)dispBuf);
	}
	else{
		sprintf(dispBuf, "%s-%s:%s; No Bootload!!!", (char*)SW_VERSION,  __DATE__, __TIME__);
		SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXT_SOFTWARE_VERSION, (uint8_t*)dispBuf);
	}
	
	memset(dispBuf, 0x0,sizeof(dispBuf));
	sprintf(dispBuf, "MANUFACTURE DATE: %4d-%2d-%2d", deviceConfig.mfg_year, deviceConfig.mfg_month, deviceConfig.mfg_day);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXT_MANUFACTURE_DATE, (uint8_t*)dispBuf);			
	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "UUID: %08X%08X%08X", UniqueId[0], UniqueId[1], UniqueId[2]);
	SetTextValue(GDDC_PAGE_INFORMATION, GDDC_PAGE_INFORMATION_TEXT_UUID, (uint8_t*)dispBuf);	
}
void returnStandbyDisplay(void){//统一返回STANDBY页面:状态机切回待机并刷新待机页显示
	NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_STANDBY;
	NVRAM0[EM_DC_PAGE] = GDDC_PAGE_STANDBY;//显式指定待机页,不依赖寄存器可能已被覆盖的旧值
	updateStandbyDisplay();//先刷新目标页面控件(指令带screen id,可预刷新后台页面)
	SetScreen(NVRAM0[EM_DC_PAGE]);//再切换页面,切换时控件已是最新内容,避免上一页控件残留
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
	
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_TREATMENT_TIME, (uint8_t*)dispBuf1);		
	treatmentLog.releaseTime = temp0;//发射时间 单位秒
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
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_ENERGY, (uint8_t*)dispBuf1); 
	treatmentLog.releaseEnergy = temp2;//已发射能量(0.1J, decijoule; 与EM_LASER_RELEASE_ENERGY同源, 显示时除以10保留1位小数)
}
void updateWarnMsgDisplay(MSG_ID_T id){//更新警号显示框
	const char *msg;
//	switch(NVRAM0[DM_LANGUAGE]){
//		case LANGUAGE_CODE_EN:{
//			break;
//		}
//		case LANGUAGE_CODE_GB:{
//			break;
//		}
//		default:{
//			break;
//		}
//	}
	if((MsgId != id) || (NVRAM0[EM_DC_PAGE] != NVRAM1[EM_DC_PAGE])){
		msg = getErrorString(id);		
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_WARN, (uint8_t*)msg);
		MsgId = id;
	}
}

void updateSchemeInfo(int16_t classify, int16_t index){//更新SCHEME 详细参数
	char dispBuf1[CONFIG_DCHMI_DISKBUF_SIZE], dispBuf2[CONFIG_DCHMI_DISKBUF_SIZE];
	int16_t mode, select;
	int16_t	power_ch0, power_ch1, power_ch2, posWidth, negWidth;
	power_ch0 &= power_ch0;
	power_ch1 &= power_ch1;
	memset(dispBuf1, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);	
	memset(dispBuf2, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(classify){
#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1470_980_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
		case SCHEME_PHLEBOLOGY:{
			if(index > (CONFIG_PHLEBOLOGY_SIZE - 1)){
				index = (CONFIG_PHLEBOLOGY_SIZE - 1);
			}
			select = sPhlebology[index].channel;
			power_ch0 = sPhlebology[index].power_ch0;
			power_ch1 = sPhlebology[index].power_ch1;
			power_ch2 = sPhlebology[index].power_ch2;
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
			power_ch2 = sProctology[index].power_ch2;
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
			power_ch2 = sGynecology[index].power_ch2;
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
			power_ch2 = sENT[index].power_ch2;
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
			power_ch2 = sNeurosurgery[index].power_ch2;
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
			power_ch2 = sDermatology[index].power_ch2;
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
			power_ch2 = sLiposuction[index].power_ch2;
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
			power_ch2 = sDentistry[index].power_ch2;
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
			power_ch2 = sTherapy[index].power_ch2;
			posWidth = sTherapy[index].poswidth;
			negWidth = sTherapy[index].negwidth;
			mode = sTherapy[index].pulse_mode;
			break;				
		}
		case SCHEME_ENDOLIFT:{
			if(index > (CONFIG_ENDOLIFT_SIZE - 1)){
				index = (CONFIG_ENDOLIFT_SIZE - 1);
			}
			select = sEndolift[index].channel;
			power_ch0 = sEndolift[index].power_ch0;
			power_ch1 = sEndolift[index].power_ch1;
			power_ch2 = sEndolift[index].power_ch2;
			posWidth = sEndolift[index].poswidth;
			negWidth = sEndolift[index].negwidth;
			mode = sEndolift[index].pulse_mode;
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
			power_ch2 = FDRAM1[index * 64 + FD_LASER_POWER_CH2];
			posWidth = FDRAM1[index * 64 + FD_LASER_POSWIDTH];
			negWidth = FDRAM1[index * 64 + FD_LASER_NEGWIDTH];
			mode = FDRAM1[index * 64 + FD_LASER_PULSE_MODE];
			break;
		}
		default:break;
	}
	switch(select){
		case LASER_CHANNEL_CH0:{
#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1470_980_635)
			sprintf(dispBuf1, "1470nm: %3.1fW", ((float)power_ch0 / 10.0F));
#endif

#if defined(APP_CONFIG_WAVE_1940_635)
			sprintf(dispBuf1, "1940nm: %3.1fW", ((float)power_ch0 / 10.0F));
#endif	

#if defined(APP_CONFIG_WAVE_450_980)
			sprintf(dispBuf1, "450nm: %3.1fW", ((float)power_ch0 / 10.0F));
#endif
#if defined(APP_CONFIG_WAVE_1940_1470_635)
			sprintf(dispBuf1, "1940nm: %3.1fW", ((float)power_ch0 / 10.0F));
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
#if defined(APP_CONFIG_WAVE_1940_1470_635)
			sprintf(dispBuf1, "1470nm: %3.1fW", ((float)power_ch1 / 10.0F));
#else
      sprintf(dispBuf1, "980nm: %3.1fW", ((float)power_ch1 / 10.0F));
#endif
			if(mode == LASER_MODE_CW){
				sprintf(dispBuf2, "Mode: CW");
			}
			if(mode == LASER_MODE_MP){
				sprintf(dispBuf2, "Mode: Pulse, On: %dmS, Off: %dmS", posWidth, negWidth);
			}						
			break;
		}
		case    LASER_CHANNEL_CH2:{
			sprintf(dispBuf1, "635nm: %3.1fW", ((float)power_ch2 / 10.0F));
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
	SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_DETAIL0, (uint8_t*)dispBuf1);
	SetTextValue(GDDC_PAGE_SCHEME_DETAIL, GDDC_PAGE_SCHEME_DETAIL_TEXT_DETAIL1, (uint8_t*)dispBuf2);
}

void unselectSchemeNum(int16_t index){//反选方案条
	if(index >= 16){
		index = index - 16;
	}
	SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, (GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0 + index), 0x0);
}
void seletcSchemeNum(int16_t classify, int16_t index){//选中方案条
	if(index >= 16){
		SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, (GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0 + index - 16), 0x1);
	}
	else{
		SetButtonValue(GDDC_PAGE_SCHEME_DETAIL, (GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0 + index), 0x1);
	}
	updateSchemeInfo(classify, index);
}
void unselectSchemeAll(void){//反选第一页全部方案条
	BatchBegin(GDDC_PAGE_SCHEME_DETAIL);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_0, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_1, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_2, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_3, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_4, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_5, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_6, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_7, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_8, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_9, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_10, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_11, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_12, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_13, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_14, 0x0);
	BatchSetButtonValue(GDDC_PAGE_SCHEME_DETAIL_KEY_SELECT_15, 0x0);
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
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_FREQUENCY, (uint8_t*)dispBuf);			
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_DUTYCYCLE, (uint8_t*)dispBuf);		
		averagePower = (float)(NVRAM0[EM_LASER_POWER_TOTAL]) / 10.0F;		
	}
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		freq = 1000.0F / (float)(NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH]);
		sprintf(dispBuf, "%5.2f Hz", freq);
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_FREQUENCY, (uint8_t*)dispBuf);		

		dutyCycle = (float)NVRAM0[EM_LASER_POSWIDTH] / (float)(NVRAM0[EM_LASER_POSWIDTH] + NVRAM0[EM_LASER_NEGWIDTH]);
		sprintf(dispBuf, "%4.1f %%", dutyCycle * 100.0F);			
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_DUTYCYCLE, (uint8_t*)dispBuf);		
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
		case LASER_CHANNEL_CH2:{
			averagePower = dutyCycle * (float)(NVRAM0[EM_LASER_POWER_CH2]) / 10.0F;
			break;
		}
		default:{
			averagePower = dutyCycle * ((float)(NVRAM0[EM_LASER_POWER_CH0]) + (float)NVRAM0[EM_LASER_POWER_CH1] + (float)NVRAM0[EM_LASER_POWER_CH2]) / 10.0F;
			break;
		}
	}
	sprintf(dispBuf, "%3.1f W", averagePower);
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_AVERAGE_POWER, (uint8_t*)dispBuf);		
	//总功率显示
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	totalPower = (float)NVRAM0[EM_LASER_POWER_TOTAL] / 10.0F;
	sprintf(dispBuf, "%3.1f W", totalPower);
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_TOTAL_POWER, (uint8_t*)dispBuf);
}

void updatePosWidthDisplay(void){//更新正脉宽显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	if(NVRAM0[EM_LASER_POSWIDTH] < 1000){
		sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_POSWIDTH]);
	}
	else{
		sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_POSWIDTH] / 1000));
	}		
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_POSWIDTH, (uint8_t*)dispBuf);		
}
void updateNegWidthDisplay(void){//更新负脉宽显示
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	if(NVRAM0[EM_LASER_NEGWIDTH] < 1000){
		sprintf(dispBuf, "%d ms", NVRAM0[EM_LASER_NEGWIDTH]);
	}
	else{
		sprintf(dispBuf, "%d S", (NVRAM0[EM_LASER_NEGWIDTH] / 1000));
	}
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_NEGWIDTH, (uint8_t*)dispBuf);
}

//前向声明: 待机页PATIENT_NAME刷新访问器(实现依赖文件后面才定义的listTreatmentCtx, 故先声明原型)
static void listTreatmentWriteStandbyPatientName(void);

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
		case LASER_CHANNEL_CH2:{
			NVRAM0[EM_LASER_POWER_TOTAL] = NVRAM0[EM_LASER_POWER_CH2];
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
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_POSWIDTH, false);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_NEGWIDTH, false);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_ICON_MPKEY, false);
		
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, false);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, false);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, false);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, false);	
		
		sprintf(dispBuf, "N/A");
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_FREQUENCY, (uint8_t*)dispBuf);			
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_DUTYCYCLE, (uint8_t*)dispBuf);
	}
	if(NVRAM0[EM_LASER_PULSE_MODE] == LASER_MODE_MP){
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_MODE_CW, false);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_MODE_MP, true);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, true);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_POSWIDTH, true);
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_NEGWIDTH, true);
		
		SetControlVisiable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_ICON_MPKEY, true);
		
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_ADD, true);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_POSWIDTH_INC, true);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_ADD, true);	
		SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_NEGWIDTH_INC, true);
		updatePosWidthDisplay();
		updateNegWidthDisplay();
	}

	SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_AIM, NVRAM0[DM_RAIM_BRG]);
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){
		sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_CH0]) / 10));
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_SET_POWER_SEL, (uint8_t*)dispBuf);		
		barValue = NVRAM0[EM_LASER_POWER_CH0] * 100.0F / CONFIG_MAX_LASER_POWER_CH0;
		if(barValue <= 2){
			barValue = 2;
		}
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL, (uint32_t)barValue);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0, true);	
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1, false);	
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH2, false);
	}
	if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){
		sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_CH1]) / 10));
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_SET_POWER_SEL, (uint8_t*)dispBuf);
		barValue = NVRAM0[EM_LASER_POWER_CH1] * 100.0F / CONFIG_MAX_LASER_POWER_CH1;
		if(barValue <= 2){
			barValue = 2;
		}
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL, (uint32_t)barValue);
    SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0, false);
    SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1, true);
		SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH2, false);
	}
	if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH2){//635
		sprintf(dispBuf, "%3.1f W\n", ((float)(NVRAM0[EM_LASER_POWER_CH2]) / 10));
		SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_SET_POWER_SEL, (uint8_t*)dispBuf);
		barValue = NVRAM0[EM_LASER_POWER_CH2] * 100.0F / CONFIG_MAX_LASER_POWER_CH2;
		if(barValue <= 2){
			barValue = 2;
		}
		SetProgressValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_PROGRESS_SET_POWER_SEL, (uint32_t)barValue);
    SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH0, false);    
    SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH1, false);
    SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SELECT_CH2, true);
	}	
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%d%%\n", NVRAM0[DM_RAIM_BRG] * 10);
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_SET_POWER_AIM, (uint8_t*)dispBuf);
	SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_NAME, (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME]);
	listTreatmentWriteStandbyPatientName();//待机页PATIENT_NAME: 经访问器下发当前选中患者名(未选择则清空)
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
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_BEEP_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//更新BEEM音量进度条
	BatchSetProgressValue(GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);//更新LCD亮度
	BatchEnd();
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXT_BEEP_VOLUME ,NVRAM0[DM_BEEM_VOLUME], 1, 0);
	SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXT_LCD_BRG ,NVRAM0[DM_LCD_BRG], 1, 0);
}

void updateReadyDisplay(void){//更新READY显示
	float displayPower;
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	switch(NVRAM0[EM_LASER_CHANNEL_SELECT]){
		case LASER_CHANNEL_CH0:{
			displayPower = (float)NVRAM0[EM_LASER_POWER_CH0] / 10.0F;
#if defined(APP_CONFIG_WAVE_1470_635)	|| defined(APP_CONFIG_WAVE_1470_980_635)
			sprintf(dispBuf, "1470nm");
			treatmentLog.laserWave = WAVE_1470;
#endif
#if defined(APP_CONFIG_WAVE_1940_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
			sprintf(dispBuf, "1940nm");
			treatmentLog.laserWave = WAVE_1940;
#endif
#if defined(APP_CONFIG_WAVE_450_980)
			sprintf(dispBuf, "450nm");
			treatmentLog.laserWave = WAVE_450;
#endif     
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_SHOW_WAVE, (uint8_t*)dispBuf);
			break;
		}
		case LASER_CHANNEL_CH1:{
			displayPower = (float)NVRAM0[EM_LASER_POWER_CH1] / 10.0F;
#if defined(APP_CONFIG_WAVE_1940_1470_635)
      sprintf(dispBuf, "1470nm");
			treatmentLog.laserWave = WAVE_1470;
#else
			sprintf(dispBuf, "980nm");
			treatmentLog.laserWave = WAVE_980;
#endif
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_SHOW_WAVE, (uint8_t*)dispBuf);
			break;
		}
		case LASER_CHANNEL_CH2:{
			displayPower = (float)NVRAM0[EM_LASER_POWER_CH2] / 10.0F;
			sprintf(dispBuf, "635nm");
			treatmentLog.laserWave = WAVE_635;
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_SHOW_WAVE, (uint8_t*)dispBuf);
			break;
		}			
		default:{
			sprintf(dispBuf, "1470+980nm");
			treatmentLog.laserWave = WAVE_1470_980;
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_SHOW_WAVE, (uint8_t*)dispBuf);
			displayPower = ((float)NVRAM0[EM_LASER_POWER_CH0] + (float)NVRAM0[EM_LASER_POWER_CH1] + (float)NVRAM0[EM_LASER_POWER_CH2])/ 10.0F;
			break;
		}
	}
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	sprintf(dispBuf, "%3.1f W\n", displayPower);
	treatmentLog.laserPower = (int16_t)(displayPower + 0.5F);//复制实际功率(四舍五入为整数W)
	treatmentLog.protocol = eCustiom;//复制方案类别(自定义)
	if((NVRAM0[DM_SCHEME_CLASSIFY] >= SCHEME_PHLEBOLOGY) && (NVRAM0[DM_SCHEME_CLASSIFY] <= SCHMEM_THERAPY)){
		treatmentLog.protocol = (PROTOCOL_ENUM)(NVRAM0[DM_SCHEME_CLASSIFY] - SCHEME_PHLEBOLOGY);
	}
	//脉冲参数快照来源: 发射模式/方案编号/正负脉宽随治疗记录落盘(停光快照会保留这些值)
	treatmentLog.pulseMode = (uint8_t)NVRAM0[EM_LASER_PULSE_MODE];
	treatmentLog.schemeIndex = (uint8_t)NVRAM0[DM_SCHEME_INDEX];
	treatmentLog.posWidth = (uint16_t)NVRAM0[EM_LASER_POSWIDTH];
	treatmentLog.negWidth = (uint16_t)NVRAM0[EM_LASER_NEGWIDTH];
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_POWER_TOTAL, (uint8_t*)dispBuf);
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_NAME, (uint8_t*)&NVRAM0[EM_LASER_SCHEME_NAME]);
	clearReleaseTimeEnergy();
	updateReleaseTimeEnergy();
	updateAcousticDisplay();
}

/*****************************************************************************/
//病历储存页面:显示病历信息(idText: ID显示文本; log: 病历数据指针, NULL显示为空)
//注册页与编辑页控件编号完全一致, 仅页面ID不同, 由screenId指定目标页面
static void dcHmiShowTreatmentCommon(uint16_t screenId, const char *idText, const treatmentLog_t *log){
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	if(log == NULL){
		SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)"--");
		SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_NAME, (uint8_t*)"--");
		SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_AGE, (uint8_t*)"--");
		SetSelectorValue(screenId, GDDC_PAGE_EDIT_PATIENT_MENU_GENDER, 0);//性别下拉默认第0项
		return;
	}
	memset(dispBuf, 0x0, sizeof(dispBuf));
	SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)idText);
	memset(dispBuf, 0x0, sizeof(dispBuf));
	sprintf(dispBuf, "%s", log->name);
	SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_NAME, (uint8_t*)dispBuf);
	memset(dispBuf, 0x0, sizeof(dispBuf));
	sprintf(dispBuf, "%d", log->age);
	SetTextValue(screenId, GDDC_PAGE_EDIT_PATIENT_TEXT_AGE, (uint8_t*)dispBuf);
	//性别下拉菜单: 屏幕工程选项顺序"FeMale;Male"(索引0=女FEMALE, 1=男MALE)
	SetSelectorValue(screenId, GDDC_PAGE_EDIT_PATIENT_MENU_GENDER,
	                 (uint8_t)((log->gender == FEMALE) ? 0 : 1));
}

void dcHmiShowTreatmentRecord(uint16_t index, const treatmentLog_t *log){//显示EPROM历史病历
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	uint16_t screenId = NVRAM0[EM_DC_PAGE];//保持函数签名不变, 目标页面取当前页
	(void)index;
	if(log == NULL){
		dcHmiShowTreatmentCommon(screenId, "--", NULL);
		return;
	}
	memset(dispBuf, 0x0, sizeof(dispBuf));
	sprintf(dispBuf, "AR %04u", (unsigned int)log->id);//患者ID取自记录本身(与患者绑定), 规则见treatment.c注释
	dcHmiShowTreatmentCommon(screenId, dispBuf, log);
}

void updateListTreatmentDisplay(void){//病历储存页面:显示当前治疗记录(待保存)
  dcHmiShowTreatmentCommon(NVRAM0[EM_DC_PAGE], "NEW", &treatmentLog);
}

//病历列表页单页可显示的患者数量(对应GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_0-4)
#define LIST_TREATMENT_WINDOW_SIZE 5
//患者历史记录页单页可显示的记录数量(对应GDDC_PAGE_LIST_RECORD各5行控件)
#define LIST_RECORD_WINDOW_SIZE 5
//病历相关运行状态集中管理: 列表页窗口/选中 + U盘提示页状态机 + 待存病历快照
typedef struct{
  uint16_t topIndex;//列表窗口第一个患者在"过滤后患者视图"中的位置(整页翻页, 恒为窗口大小的整数倍)
  uint16_t selectedIndex;//当前选中患者在"过滤后患者视图"中的位置
  uint16_t usbState;//U盘流程状态: 0空闲 6确认页等待按键 7导出/导入执行中(读写在轮询完成)
  uint16_t usbCount;//本次保存/载入的病历条数
  char usbText[64];//USB操作页SUMMARY_USB当前应显示的内容(默认U盘在位状态, 导出/导入后为本次结果, 取消后为空)
  uint16_t driveStep;//上一拍HMI治疗步骤(用于识别停光, 开机为0不等于发射中步骤)
  uint8_t  usbOp;//1=导出(save) 2=导入(load), 决定确认页文案与轮询执行分支
  uint8_t  usbErr;//U盘操作结果(0=成功)
  uint8_t  pendingValid;//1=本次治疗确实发射过且尚未落成病历
  treatmentLog_t pending;//待存病历快照(功率/波长/方案/发射时间/发射能量)
  //患者视图过滤: findText为SEARCH_NAME输入的查找字母(空串=不过滤), filteredCount为命中总数;
  //紧凑索引sortedIndex存命中患者的全局索引(按姓名+原始索引全序排序), 仅2字节/条, 物理上限4710字节;
  //窗口/选择直接按索引O(1)定位, 渲染时才回读整行, 不再为每次翻页做全表多轮扫描
  char findText[16];
  uint16_t filteredCount;//过滤后命中的患者数量(视图总数)
  uint16_t sortedIndex[TREATMENT_PHYSICAL_PATIENT_CAP];//命中患者全局索引, 已按显示顺序排序
  //当前选中患者: selectedPatientId为稳定患者编号(0=未选择), 后续治疗记录以该id为外键归属; selectedPatientName供待机页PATIENT_NAME显示
  uint16_t selectedPatientId;
  char selectedPatientName[TREATMENT_NAME_SIZE];
  //删除确认页: deletePatientId缓存待删除患者编号(0=不在删除确认流程), 确认后级联删除该患者及其全部治疗记录
  uint16_t deletePatientId;
  //LIST_RECORD治疗记录列表: recordPatientId为当前查看患者(0=未进入), recordTop为窗口起始(整页),
  //recordCount为该患者记录总数(u16), 不缓存全量索引, 仅按窗口(5)按需扫描, recordWindow存当前窗口全局索引
  uint16_t recordPatientId;
  uint16_t recordTop;
  uint16_t recordCount;//该患者记录总数(无上限, 仅受区块物理容量约束)
  uint16_t recordWindowTop;//recordWindow当前对应窗口起点(0xFFFF=缓存失效)
  uint16_t recordWindow[LIST_RECORD_WINDOW_SIZE];//当前窗口记录在扁平表中的全局索引
  //DELETE_RECORD单条记录删除确认: deleteRecordGlobalIndex缓存待删记录全局索引(0xFFFF=不在流程)
  uint16_t deleteRecordGlobalIndex;
  //EDIT_PATIENT患者信息编辑模式: 0=正常新建/追加流程, 1=从记录页进入只更新患者信息(不追加记录)
  uint8_t editPatientMode;
  //REGISTER_PATIENT注册页: registerReturnPage为进入注册页之前的来源页(13=CREATE_NEW手动, 22=核对页SAVE_RECORD),
  //CANCEL/完成后返回该页; verifySelectMode=1表示列表页正被核对页用来选择已有患者, 选中后回核对页而非待机页
  uint16_t registerReturnPage;
  uint8_t verifySelectMode;
}listTreatmentCtx_t;
static listTreatmentCtx_t listTreatmentCtx;//病历页相关运行状态(开机全为0, 全部放ZI段)

//待机页PATIENT_NAME访问器: 已选患者显示其姓名, 未选择(开机selectedPatientId=0)清空, 保证任何路径回待机页显示一致
static void listTreatmentWriteStandbyPatientName(void){
  if(listTreatmentCtx.selectedPatientId != 0U){
    SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME,
                 (uint8_t*)listTreatmentCtx.selectedPatientName);
  }
  else{
    SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_PATIENT_NAME, (uint8_t*)"");
  }
}

//获取EPROM中有效病历数量:数量由DM_TREATMENT_NUM寄存器维护(treatment数据层增删时自动同步)
static uint16_t listTreatmentGetCount(void){
  if(NVRAM0[DM_TREATMENT_NUM] < 0){//异常负值防御
    return 0;
  }
  return (uint16_t)NVRAM0[DM_TREATMENT_NUM];
}

//姓名是否命中查找字母: 按SEARCH_NAME输入做大小写敏感的前缀匹配(输入"l"不命中大写"L"开头, 输入"la"只命中"la"前缀);
//findText为空串时不过滤全部命中; 姓名提前结束或任一位不同(含大小写不同)即不匹配
static uint8_t listTreatmentMatchFind(const char *name){
  uint8_t i;
  if(name == NULL){
    return 0U;
  }
  for(i = 0U; i < 16U; i++){
    char fc = listTreatmentCtx.findText[i];
    if(fc == '\0'){
      return 1U;//查找字母已全部匹配完
    }
    if(name[i] != fc){//大小写敏感: 直接逐位比较, 不做大小写归一
      return 0U;
    }
  }
  return 0U;//findText达到16位仍未结束(理论上findText被限制在15位内, 防御兜底)
}

//两个姓名的大小写敏感字典序(ASCII)比较: nameA靠前返回负, 靠后返回正, 完全相同返回0;
//按字符原始值逐位比较(大写A-Z码值65-90, 排在小写a-z 97-122之前), 短名先结束(如"li"排在"linqing"前), 非ASCII字节按原值比较
static int16_t listTreatmentCompareName(const char *nameA, const char *nameB){
  uint8_t i;
  for(i = 0U; i < TREATMENT_NAME_SIZE; i++){
    char ca = nameA[i];
    char cb = nameB[i];
    if(ca != cb){
      return (int16_t)((uint8_t)ca - (uint8_t)cb);
    }
    if(ca == '\0'){
      return 0;//两者同时结束
    }
  }
  return 0;
}

//全序键: 先按姓名ASCII字典序, 姓名相同再按患者表原始索引(唯一且稳定), 保证重名患者也能正确逐条枚举
static int16_t listTreatmentOrderCmp(const char *nameA, uint16_t idxA,
                                     const char *nameB, uint16_t idxB){
  int16_t c = listTreatmentCompareName(nameA, nameB);
  if(c != 0){ return c; }
  if(idxA < idxB){ return -1; }
  if(idxA > idxB){ return 1; }
  return 0;
}

//RAM内排序键: 仅缓存排序所需的全局索引+姓名(不缓存整行), 排序过程零FRAM访问
typedef struct{
  uint16_t globalIndex;
  char name[TREATMENT_NAME_SIZE];
}listPatientKey_t;
//RAM排序键缓冲(快速路径, 固定大小); 命中数超过该值时改用FRAM堆排序回退
static listPatientKey_t ramKeys[CONFIG_LIST_TREATMENT_RAM_KEYS];
//患者表批量读分块缓冲(对齐的患者行数组, 单次FRAM事务读16行)
static patientRecord_t chunkPat[CONFIG_LIST_TREATMENT_PATIENT_CHUNK_ROWS];

//两个RAM键的全序比较: 复用姓名ASCII+全局索引口径, 纯内存不读FRAM
static int16_t listTreatmentKeyCmp(const listPatientKey_t *a, const listPatientKey_t *b){
  return listTreatmentOrderCmp(a->name, a->globalIndex, b->name, b->globalIndex);
}

//RAM键堆排序下沉: 大顶堆(全序键最大者在根), 无递归、栈占用恒定, 全程零FRAM
static void listTreatmentSiftDownKeys(listPatientKey_t *arr, uint16_t heapSize, uint16_t root){
  uint16_t cur = root;
  while(1){
    uint16_t left = (uint16_t)(2U * cur + 1U);
    uint16_t right = (uint16_t)(2U * cur + 2U);
    uint16_t largest = cur;
    if((left < heapSize) && (listTreatmentKeyCmp(&arr[left], &arr[largest]) > 0)){
      largest = left;
    }
    if((right < heapSize) && (listTreatmentKeyCmp(&arr[right], &arr[largest]) > 0)){
      largest = right;
    }
    if(largest == cur){ break; }
    {
      listPatientKey_t tmp = arr[cur];
      arr[cur] = arr[largest];
      arr[largest] = tmp;
    }
    cur = largest;
  }
}

//对RAM键做原地堆排序(升序), 纯CPU O(N log N), 之后由键序列生成sortedIndex
static void listTreatmentSortKeys(listPatientKey_t *arr, uint16_t n){
  if(n < 2U){ return; }
  for(int32_t k = (int32_t)(n / 2U) - 1; k >= 0; k--){
    listTreatmentSiftDownKeys(arr, n, (uint16_t)k);
  }
  for(uint16_t end = (uint16_t)(n - 1U); end > 0U; end--){
    listPatientKey_t tmp = arr[0];
    arr[0] = arr[end];
    arr[end] = tmp;
    listTreatmentSiftDownKeys(arr, end, 0U);
  }
}

//全序比较两个全局索引对应患者: 读两行(仅排序时一次性发生), 按姓名+原始索引全序键
static int16_t listTreatmentOrderOfIndices(uint16_t idxA, uint16_t idxB){
  patientRecord_t a, b;
  if(treatmentPatientGetByIndex(idxA, &a) != TREATMENT_EPROM_OK){ return 0; }
  if(treatmentPatientGetByIndex(idxB, &b) != TREATMENT_EPROM_OK){ return 0; }
  return listTreatmentOrderCmp(a.name, idxA, b.name, idxB);
}

//堆排序下沉: 维护"全序键最大者在根"的大顶堆, 比较时按需读FRAM, 无递归、栈占用恒定
static void listTreatmentSiftDown(uint16_t *arr, uint16_t heapSize, uint16_t root){
  uint16_t cur = root;
  while(1){
    uint16_t left = (uint16_t)(2U * cur + 1U);
    uint16_t right = (uint16_t)(2U * cur + 2U);
    uint16_t largest = cur;
    if((left < heapSize) && (listTreatmentOrderOfIndices(arr[left], arr[largest]) > 0)){
      largest = left;
    }
    if((right < heapSize) && (listTreatmentOrderOfIndices(arr[right], arr[largest]) > 0)){
      largest = right;
    }
    if(largest == cur){ break; }
    uint16_t tmp = arr[cur];
    arr[cur] = arr[largest];
    arr[largest] = tmp;
    cur = largest;
  }
}

//对命中全局索引做原地堆排序(升序), 一次性O(N log N)比较, 之后任意翻页/选择O(1)
static void listTreatmentSortIndices(uint16_t *arr, uint16_t n){
  if(n < 2U){ return; }
  for(int32_t k = (int32_t)(n / 2U) - 1; k >= 0; k--){
    listTreatmentSiftDown(arr, n, (uint16_t)k);
  }
  for(uint16_t end = (uint16_t)(n - 1U); end > 0U; end--){
    uint16_t tmp = arr[0];
    arr[0] = arr[end];
    arr[end] = tmp;
    listTreatmentSiftDown(arr, end, 0U);
  }
}

//重建过滤视图: 分块批量读患者表(每块1次FRAM事务), 单遍收集命中患者的全局索引与RAM排序键;
//命中数在RAM键缓冲内则纯内存排序(零FRAM回读), 超限回退FRAM堆排序。数据变化(新建/删除/U盘载入)
//或查找字母变化时调用, 翻页期间直接复用排序结果, 不再重复扫描
static void listTreatmentRebuildFilter(void){
  uint16_t total = treatmentGetPatientCount();
  uint16_t start = 0U;
  uint16_t hits = 0U;
  listTreatmentCtx.filteredCount = 0U;
  while(start < total){
    //批量读一个分块(对齐的患者行), 读不到即终止
    uint16_t rows = treatmentPatientReadRows(start, (uint8_t*)chunkPat, (uint16_t)sizeof(chunkPat));
    if(rows == 0U){ break; }
    for(uint16_t r = 0U; r < rows; r++){
      patientRecord_t *pat = &chunkPat[r];
      uint16_t globalIndex;
      if(listTreatmentMatchFind(pat->name) == 0U){
        continue;
      }
      //物理容量保护: 命中数不超过紧凑索引上界(实际由区块容量保证, 防御兜底)
      if(hits >= TREATMENT_PHYSICAL_PATIENT_CAP){
        break;
      }
      globalIndex = (uint16_t)(start + r);
      //sortedIndex始终收集全部命中(回退路径也需要), RAM键仅在缓冲容量内填充
      listTreatmentCtx.sortedIndex[hits] = globalIndex;
      if(hits < CONFIG_LIST_TREATMENT_RAM_KEYS){
        ramKeys[hits].globalIndex = globalIndex;
        memcpy(ramKeys[hits].name, pat->name, TREATMENT_NAME_SIZE);
      }
      hits++;
    }
    start = (uint16_t)(start + rows);
  }
  listTreatmentCtx.filteredCount = hits;
  if(hits <= CONFIG_LIST_TREATMENT_RAM_KEYS){
    //快速路径: RAM键纯内存排序, 再由键序列生成sortedIndex, 排序过程零FRAM
    uint16_t k;
    listTreatmentSortKeys(ramKeys, hits);
    for(k = 0U; k < hits; k++){
      listTreatmentCtx.sortedIndex[k] = ramKeys[k].globalIndex;
    }
  }
  else{
    //回退路径: 命中超过RAM键缓冲, 用FRAM堆排序(正确, 不限制写入, 仅更慢)
    listTreatmentSortIndices(listTreatmentCtx.sortedIndex, hits);
  }
}

//视图位置 -> 患者行: 视图外位置返回0, 命中则经紧凑索引O(1)定位全局索引并回读整行;
//不再依赖窗口缓存, 任意有效视图位置都可取, 每次仅1次FRAM行读
static uint8_t listTreatmentGetViewPatient(uint16_t viewPos, patientRecord_t *out){
  uint16_t globalIndex;
  if(out == NULL){
    return 0U;
  }
  if(viewPos >= listTreatmentCtx.filteredCount){
    return 0U;
  }
  globalIndex = listTreatmentCtx.sortedIndex[viewPos];
  if(treatmentPatientGetByIndex(globalIndex, out) != TREATMENT_EPROM_OK){
    return 0U;
  }
  return 1U;
}

//窗口起始索引的合法上限(整页对齐): 视图患者超过一屏时, 取不超过"末位索引"的最大整页边界;
//不足一屏(无需滚动)时为0。保证topIndex恒为窗口大小的整数倍, 与整页翻页(±窗口大小)及页码计算一致
static uint16_t listTreatmentGetMaxTop(void){
  uint16_t viewCount = listTreatmentCtx.filteredCount;
  if(viewCount <= LIST_TREATMENT_WINDOW_SIZE){
    return 0U;
  }
  return (uint16_t)(((viewCount - 1U) / LIST_TREATMENT_WINDOW_SIZE) * LIST_TREATMENT_WINDOW_SIZE);
}

//把窗口/选中钳制到当前过滤视图的合法范围(防御: 记录式删除等路径改完索引后视图仍保持一致)
static void listTreatmentClampWindow(void){
  if(listTreatmentCtx.filteredCount == 0U){
    listTreatmentCtx.topIndex = 0U;
    listTreatmentCtx.selectedIndex = 0U;
    return;
  }
  //先把窗口起点向下对齐到整页边界(消除非整页路径遗留的偏移), 再夹到合法上限
  listTreatmentCtx.topIndex = (uint16_t)((listTreatmentCtx.topIndex / LIST_TREATMENT_WINDOW_SIZE)
                                         * LIST_TREATMENT_WINDOW_SIZE);
  if(listTreatmentCtx.topIndex > listTreatmentGetMaxTop()){
    listTreatmentCtx.topIndex = listTreatmentGetMaxTop();
  }
  if(listTreatmentCtx.selectedIndex >= listTreatmentCtx.filteredCount){
    listTreatmentCtx.selectedIndex = (uint16_t)(listTreatmentCtx.filteredCount - 1U);
  }
}

//刷新病历列表页:按窗口起始位置把过滤后患者的姓名/ID/病历数写入对应控件,并更新选中按钮状态;
//空槽位三类文本清空, 选择/删除/编辑三个按键隐藏并禁止触摸, 有效槽位恢复显示与使能
void refreshListTreatmentDisplay(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t recordCount = listTreatmentGetCount();
  uint16_t pageCount;
  uint16_t pageNow;
  patientRecord_t windowPat[LIST_TREATMENT_WINDOW_SIZE];
  uint16_t windowRecCount[LIST_TREATMENT_WINDOW_SIZE];
  listTreatmentClampWindow();
  //第一步: 预读当前窗口患者行(最多5次FRAM行读), 记录数先清零
  for(uint8_t i = 0U; i < LIST_TREATMENT_WINDOW_SIZE; i++){
    uint16_t viewPos = (uint16_t)(listTreatmentCtx.topIndex + i);
    memset(&windowPat[i], 0, sizeof(windowPat[i]));
    windowRecCount[i] = 0U;
    (void)listTreatmentGetViewPatient(viewPos, &windowPat[i]);
  }
  //第二步: 单遍记录id轻读(2字节/条), 一次性统计窗口各患者记录数;
  //替代原先每个患者一次全表28字节扫描(5次), 字节量降约14倍
  {
    uint16_t totalRec = treatmentEpromGetCount();
    for(uint16_t r = 0U; r < totalRec; r++){
      uint16_t rid;
      if(treatmentRecordGetPatientIdByIndex(r, &rid) != TREATMENT_EPROM_OK){
        break;
      }
      for(uint8_t s = 0U; s < LIST_TREATMENT_WINDOW_SIZE; s++){
        if((windowPat[s].id != 0U) && (rid == windowPat[s].id)){
          windowRecCount[s]++;
          break;
        }
      }
    }
  }
  //进入/重进本页先建立"全部按键未按下"基线: 显式清零页面13全部20个按钮(20-29, 31-40),
  //不依赖切页前后无应答的逐个复位; 选中患者仍由selectedPatientId/Name记录, 不再用按钮down态高亮
  for(uint16_t btn = GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0;
      btn <= GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_4; btn++){
    SetButtonValue(GDDC_PAGE_LIST_TREATMENT, btn, 0);
  }
  for(uint16_t btn = GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0;
      btn <= GDDC_PAGE_LIST_TREATMENT_KEY_OPERATOR_USB; btn++){
    SetButtonValue(GDDC_PAGE_LIST_TREATMENT, btn, 0);
  }
  //第三步: 按预读结果渲染各槽位(渲染循环内不再产生FRAM访问)
  for(uint8_t i = 0; i < LIST_TREATMENT_WINDOW_SIZE; i++){
    uint16_t nameCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_TEXT_NAME_0 + i);
    uint16_t idCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_TEXT_ID_0 + i);
    uint16_t countCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_TEXT_RECORD_COUNT_0 + i);
    uint16_t selectCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_KEY_SELECT_PATIENT_0 + i);
    uint16_t deleteCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_KEY_DELETE_0 + i);
    uint16_t editCtrl = (uint16_t)(GDDC_PAGE_LIST_TREATMENT_KEY_EDIT_RECORD_0 + i);
    uint8_t slotOccupied = (windowPat[i].id != 0U) ? 1U : 0U;
    memset(dispBuf, 0x0, sizeof(dispBuf));
    if(slotOccupied != 0U){
      //列表只显示患者姓名: 患者信息存在即显示, 同一患者只出现一次, 与其病历数量无关(含0个病历)
      strncpy(dispBuf, windowPat[i].name, sizeof(windowPat[i].name));
      dispBuf[sizeof(windowPat[i].name) - 1U] = '\0';
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, nameCtrl, (uint8_t*)dispBuf);
      sprintf(dispBuf, "AR %04u", (unsigned int)windowPat[i].id);//患者ID(AR编号)
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, idCtrl, (uint8_t*)dispBuf);
      sprintf(dispBuf, "Records: %u", (unsigned int)windowRecCount[i]);//该患者已有病历数, 0条时显示"Records: 0"
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, countCtrl, (uint8_t*)dispBuf);
    }
    else{//视图外空槽位: 三类文本全部清空
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, nameCtrl, (uint8_t*)"");
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, idCtrl, (uint8_t*)"");
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, countCtrl, (uint8_t*)"");
    }
    //有效槽位三个按键显示并允许触摸, 空槽位三个按键隐藏并禁止触摸; 过滤/翻页/重进后槽位状态变化也按此显式恢复
    SetControlVisiable(GDDC_PAGE_LIST_TREATMENT, selectCtrl, slotOccupied);
    SetControlEnable(GDDC_PAGE_LIST_TREATMENT, selectCtrl, slotOccupied);
    SetControlVisiable(GDDC_PAGE_LIST_TREATMENT, deleteCtrl, slotOccupied);
    SetControlEnable(GDDC_PAGE_LIST_TREATMENT, deleteCtrl, slotOccupied);
    SetControlVisiable(GDDC_PAGE_LIST_TREATMENT, editCtrl, slotOccupied);
    SetControlEnable(GDDC_PAGE_LIST_TREATMENT, editCtrl, slotOccupied);
  }
  memset(dispBuf, 0x0, sizeof(dispBuf));
  //CAPACITY保持全局口径: 去重患者人数/治疗记录次数(同一患者多次治疗只计1人, 不受当前过滤影响)
  sprintf(dispBuf, "P:%u/R:%u",
    (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)recordCount);
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_CAPACITY, (uint8_t*)dispBuf);
  //PAGE_NUM: 当前页/总页数(空视图按1页显示, 避免出现0/0)
  pageCount = (listTreatmentCtx.filteredCount + LIST_TREATMENT_WINDOW_SIZE - 1U) / LIST_TREATMENT_WINDOW_SIZE;
  if(pageCount == 0U){
    pageCount = 1U;
  }
  pageNow = (uint16_t)(listTreatmentCtx.topIndex / LIST_TREATMENT_WINDOW_SIZE + 1U);
  sprintf(dispBuf, "PAGE %u/%u", (unsigned int)pageNow, (unsigned int)pageCount);
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_PAGE_NUM, (uint8_t*)dispBuf);
}

//SEARCH_NAME文本通知: 保存查找字母并重建过滤视图, 新查找下窗口回到第一页(空串=恢复全部患者)
void listTreatmentSetFindText(const char *text){
  if(text == NULL){
    listTreatmentCtx.findText[0] = '\0';
  }
  else{
    strncpy(listTreatmentCtx.findText, text, sizeof(listTreatmentCtx.findText) - 1U);
    listTreatmentCtx.findText[sizeof(listTreatmentCtx.findText) - 1U] = '\0';
  }
  listTreatmentCtx.topIndex = 0U;
  listTreatmentRebuildFilter();
  refreshListTreatmentDisplay();
}

//进入病历列表页:清空查找字母并重建患者视图, 窗口从第一页开始, 默认选中第一个;
//同时清空屏幕搜索框, 保证CLOSE关闭后再进入页面时上次输入不残留(USB操作页返回不走此函数, 保留搜索内容)
void enterListTreatmentPage(void){
  listTreatmentCtx.topIndex = 0U;
  listTreatmentCtx.selectedIndex = 0U;
  listTreatmentCtx.findText[0] = '\0';
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_SEARCH_NAME, (uint8_t*)"");
  listTreatmentRebuildFilter();
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_CAPACITY, (uint8_t*)"");
  refreshListTreatmentDisplay();
}

//USB操作页SUMMARY_USB文案: 统一由usbText保存, 页面冷加载重发同一内容, 避免本次导出/导入结果被"UDISK OK"覆盖
static void setOperatorUsbText(const char *text){
  if(text == NULL){
    listTreatmentCtx.usbText[0] = '\0';
    return;
  }
  strncpy(listTreatmentCtx.usbText, text, sizeof(listTreatmentCtx.usbText) - 1U);
  listTreatmentCtx.usbText[sizeof(listTreatmentCtx.usbText) - 1U] = '\0';
}

//USB操作页: 刷新机内病历摘要(患者数/记录数), SUMMARY_USB按usbText下发(默认U盘在位状态, 导出/导入后为本次结果)
void refreshOperatorUsbDisplay(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  //进入/重进先建立"全部按键未按下"基线: 显式清零本页SAVE/LOAD/CANCEL三个自锁键,
  //不依赖切页前后的逐个复位, 与页面13进入即全键未按下的规则保持一致
  for(uint16_t btn = GDDC_PAGE_OPERATOR_USB_KEY_SAVE_UDISK;
      btn <= GDDC_PAGE_OPERATOR_USB_KEY_CLOSE; btn++){
    SetButtonValue(GDDC_PAGE_OPERATOR_USB, btn, 0);
  }
  memset(dispBuf, 0x0, sizeof(dispBuf));
  //机内病历储存概况: 现有患者数量/累计历史治疗记录数(全局去重患者数/记录数, 不受列表过滤影响); 文本控件一律英文显示
  sprintf(dispBuf, "Existing patients: %u, total treatment records: %u",
    (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentGetCount());
  SetTextValue(GDDC_PAGE_OPERATOR_USB, GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY, (uint8_t*)dispBuf);
  SetTextValue(GDDC_PAGE_OPERATOR_USB, GDDC_PAGE_OPERATOR_USB_TEXT_SUMMARY_USB, (uint8_t*)listTreatmentCtx.usbText);
}

//列表页"操作USB"按键: 进入USB导入导出操作页(保存/载入的U盘检测与读写沿用既有流程)
void enterOperatorUsbPage(void){
  //重新进入操作页: SUMMARY_USB回到U盘在位状态, 覆盖上一次残留的导出/导入结果
  setOperatorUsbText((treatmentUsbDiskPresent() != 0U) ? "UDISK OK" : "NO UDISK");
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPERATOR_USB;
  refreshOperatorUsbDisplay();//先刷新本页控件, 再切页避免上一页控件残留
  SetScreen(GDDC_PAGE_OPERATOR_USB);
}

//USB操作页返回: 回到病历列表页(EPROM不改变, 保留当前名字窗口与选中)
void listTreatmentOperatorUsbBack(void){
  //从USB流程返回: 导入可能已整体替换EPROM, RAM里的filteredCount/sortedIndex/ramKeys是旧数据,
  //必须先按当前findText重建过滤再渲染, 否则会显示空白/旧数量(关闭重进才正常); findText与窗口保留
  listTreatmentRebuildFilter();
  refreshListTreatmentDisplay();
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
  //CANCEL自锁键释放已上移到notify层(无条件)
}

//PAGE_UP键: 向前翻一整页, 已在第一页(窗口起始位置为0)时不再移动
void listTreatmentMoveUp(void){
  if(listTreatmentCtx.topIndex >= LIST_TREATMENT_WINDOW_SIZE){
    listTreatmentCtx.topIndex = (uint16_t)(listTreatmentCtx.topIndex - LIST_TREATMENT_WINDOW_SIZE);
    refreshListTreatmentDisplay();
  }
}

//PAGE_DOWN键: 向后翻一整页, 当前页之后已无患者时不再移动
void listTreatmentMoveDown(void){
  if((uint16_t)(listTreatmentCtx.topIndex + LIST_TREATMENT_WINDOW_SIZE) < listTreatmentCtx.filteredCount){
    listTreatmentCtx.topIndex = (uint16_t)(listTreatmentCtx.topIndex + LIST_TREATMENT_WINDOW_SIZE);
    refreshListTreatmentDisplay();
  }
}

//选择窗口内第slot个患者(slot 0-4对应KEY_SELECT_PATIENT_0-4),空槽位不响应;
//选中后缓存患者编号/姓名并自动返回待机页(PATIENT_NAME显示该患者), 后续治疗记录归属该患者
static void listTreatmentEnterVerifyPage(void);
void listTreatmentSelect(uint8_t slot){
  uint16_t viewPos;
  patientRecord_t pat;
  if(slot >= LIST_TREATMENT_WINDOW_SIZE){
    return;
  }
  viewPos = (uint16_t)(listTreatmentCtx.topIndex + slot);
  if(viewPos >= listTreatmentCtx.filteredCount){//空槽位: 不响应
    return;
  }
  if(listTreatmentGetViewPatient(viewPos, &pat) == 0U){//视图位置取不到患者(数据异常): 不响应
    return;
  }
  if(listTreatmentCtx.verifySelectMode != 0U){//核对页选择已有患者: 载入该患者并回核对页, 不回待机
    listTreatmentCtx.verifySelectMode = 0U;
    treatmentLog.id = pat.id;
    treatmentLog.age = pat.age;
    treatmentLog.gender = (GENDER_ENUM)pat.gender;
    memcpy(treatmentLog.name, pat.name, TREATMENT_NAME_SIZE);
    listTreatmentEnterVerifyPage();
    return;
  }
  listTreatmentCtx.selectedIndex = viewPos;//列表内选中位置(仅内部状态, 按钮未按下基线见refreshListTreatmentDisplay)
  listTreatmentCtx.selectedPatientId = pat.id;//缓存稳定患者编号, 后续治疗记录以该id为外键归属
  memset(listTreatmentCtx.selectedPatientName, 0x0, sizeof(listTreatmentCtx.selectedPatientName));
  strncpy(listTreatmentCtx.selectedPatientName, pat.name, sizeof(listTreatmentCtx.selectedPatientName) - 1U);
  refreshListTreatmentDisplay();//先刷新列表选中按钮状态
  returnStandbyDisplay();//自动返回待机页: 内部updateStandbyDisplay会向PATIENT_NAME下发该患者名
}

//删除当前选中病历: 后续病历前移并重新编号(treatment层同步DM_TREATMENT_NUM), 删完刷新列表与总数
void listTreatmentDelete(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t count = listTreatmentGetCount();
  treatmentEpromErr_t err;
  treatmentLog_t rec;
  //注: 本函数为旧记录式删除逻辑(无调用者, 暂保留); 新UI的DELETE_0-4患者级联删除已由listTreatmentDeleteStart/Confirm确认页实现
  if(count == 0U){//没有病历可删
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "NO RECORD");
    SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
    return;
  }
  if(listTreatmentCtx.selectedIndex >= count){//选中索引越界时退到最后一条
    listTreatmentCtx.selectedIndex = (uint16_t)(count - 1U);
  }
  memset(dispBuf, 0x0, sizeof(dispBuf));
  if(treatmentEpromGet(listTreatmentCtx.selectedIndex, &rec) == TREATMENT_EPROM_OK){//提示正在删除的是哪个ID(直接取记录里的id字段)
    sprintf(dispBuf, "DEL AR %04u...", (unsigned int)rec.id);
  }
  else{
    sprintf(dispBuf, "DEL...");
  }
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
  err = treatmentEpromDelete(listTreatmentCtx.selectedIndex);//删除(后续病历前移, 各患者ID保持不变)
  if(err != TREATMENT_EPROM_OK){
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "DEL ERR:%d", (int)err);
    SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
    return;
  }
  count--;//有效病历数量-1
  if(count == 0U){//删空: 窗口与选中回到第一条
    listTreatmentCtx.selectedIndex = 0;
    listTreatmentCtx.topIndex = 0;
  }
  else{
    if(listTreatmentCtx.selectedIndex >= count){//删的是最后一条: 选中新的最后一条
      listTreatmentCtx.selectedIndex = (uint16_t)(count - 1U);
    }
    if(count <= LIST_TREATMENT_WINDOW_SIZE){//病历不足一页: 窗口从头开始
      listTreatmentCtx.topIndex = 0;
    }
    else if((uint16_t)(listTreatmentCtx.topIndex + LIST_TREATMENT_WINDOW_SIZE) > count){//窗口尾部越过新末尾: 前移到刚好显示末尾
      listTreatmentCtx.topIndex = (uint16_t)(count - LIST_TREATMENT_WINDOW_SIZE);
    }
  }
  refreshListTreatmentDisplay();
  memset(dispBuf, 0x0, sizeof(dispBuf));
  sprintf(dispBuf, "DEL OK, NUM:%d", NVRAM0[DM_TREATMENT_NUM]);
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
}

//***************************************************************************
//待存病历快照: 在停光那一刻把本次实际治疗参数(发射时间/能量/功率/波长/方案)整条存下来,
//避免停光后操作员在待机页改方案或功率, 造成"存档参数与本次实际发射不匹配"; 没有实际发射时保持无效

//记录治疗时刻RTC(完整4位年): 停光瞬间取当前时刻, 随病历一起落盘
static void listTreatmentStampRtc(treatmentLog_t *log){
  if(log == NULL){
    return;
  }
  RtcGetDateTime(&log->rtcYear,
                 &log->rtcMonth,
                 &log->rtcDay,
                 &log->rtcHour,
                 &log->rtcMinute,
                 &log->rtcSecond);
}

static void listTreatmentPendingCapture(void){//停光时调用: 补齐最后一段累计后整条快照
  int32_t trigTicks;
  updateReleaseTimeEnergy();//用停光前的当前参数刷新累计时间/能量, 补齐最后一个100ms节拍
  trigTicks = *((int32_t*)&NVRAM0[EM_LASER_TRIG_TIME]);//激光实际打开时间(20ms计数)
  if(trigTicks <= 0){//本次没有实际发射: 不产生待存病历
    return;
  }
  listTreatmentCtx.pending = treatmentLog;//整条快照: 功率/波长/方案/发射时间/发射能量
  //停光瞬间捕获RTC治疗时刻, 随病历一起落盘(完整4位年)
  listTreatmentStampRtc(&listTreatmentCtx.pending);
  listTreatmentCtx.pendingValid = 1U;
}

static void listTreatmentStepWatch(void){//监视治疗步骤: 从"发射中"切走即视为停光, 抓取待存病历快照
  uint16_t stepNow = (uint16_t)NVRAM0[EM_HMI_OPERA_STEP];
  if((listTreatmentCtx.driveStep == (uint16_t)FSMSTEP_LASER_EMITING) && (stepNow != (uint16_t)FSMSTEP_LASER_EMITING)){
    listTreatmentPendingCapture();
    //正常停光(回等待触发)且有有效待存: 自动弹核对页; ESTOP/回待机等路径不弹, 仍由其原导航处理
    if((listTreatmentCtx.pendingValid != 0U) && (stepNow == (uint16_t)FSMSTEP_LASER_WAIT_TRIGGER)){
      listTreatmentVerifyAfterLaser();
    }
  }
  listTreatmentCtx.driveStep = stepNow;
}

//姓名非空判定(全部为空格等同于没填)
static uint8_t listTreatmentNameValid(const char *name){
  uint8_t i;
  if(name == NULL){
    return 0U;
  }
  for(i = 0U; i < sizeof(treatmentLog.name); i++){
    if(name[i] == '\0'){
      break;
    }
    if((name[i] != ' ') && (name[i] != '\t')){
      return 1U;
    }
  }
  return 0U;
}

void listTreatmentCreateStart(void){//CREATE按键: 本次治疗确实发射过激光才允许新建病历(编辑页确认后追加到区块末尾)
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  int32_t trigTicks;
  patientRecord_t selPat;//已选患者路径: 按id取出的患者行
  uint16_t patIndex;//已选患者在患者表内的索引
  if(listTreatmentCtx.pendingValid == 0U){//没抓到停光快照(极短发射/步骤跳变): 再用发射时间计数判断
    trigTicks = *((int32_t*)&NVRAM0[EM_LASER_TRIG_TIME]);//激光实际打开时间(20ms计数)
    if(trigTicks <= 0){//本次没有实际发射: 不允许凭空新建病历
      memset(dispBuf, 0x0, sizeof(dispBuf));
      sprintf(dispBuf, "CREATE:NO LASER");
      SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
      return;
    }
    listTreatmentCtx.pending = treatmentLog;//漏抓兜底: 直接用当前累计值
    listTreatmentStampRtc(&listTreatmentCtx.pending);//兜底: 用当前时刻补齐治疗时间
    listTreatmentCtx.pendingValid = 1U;
  }
  //用停光快照还原本次实际治疗参数(与之后是否改方案/功率无关)
  treatmentLog.releaseEnergy = listTreatmentCtx.pending.releaseEnergy;
  treatmentLog.releaseTime = listTreatmentCtx.pending.releaseTime;
  treatmentLog.laserPower = listTreatmentCtx.pending.laserPower;
  treatmentLog.laserWave = listTreatmentCtx.pending.laserWave;
  treatmentLog.protocol = listTreatmentCtx.pending.protocol;
  //治疗时刻RTC随病历落盘(编辑页OK后treatmentEpromAdd写入EPROM)
  treatmentLog.rtcYear = listTreatmentCtx.pending.rtcYear;
  treatmentLog.rtcMonth = listTreatmentCtx.pending.rtcMonth;
  treatmentLog.rtcDay = listTreatmentCtx.pending.rtcDay;
  treatmentLog.rtcHour = listTreatmentCtx.pending.rtcHour;
  treatmentLog.rtcMinute = listTreatmentCtx.pending.rtcMinute;
  treatmentLog.rtcSecond = listTreatmentCtx.pending.rtcSecond;
  //患者信息按是否已选患者分路径: 默认清空(新患者, id=0由treatmentEpromAdd分配); 已选则预填该患者(老患者, 保存时id已存在不新建)
  treatmentLog.id = 0U;
  treatmentLog.age = 0U;
  treatmentLog.gender = (GENDER_ENUM)0;
  memset(treatmentLog.name, 0x0, sizeof(treatmentLog.name));
  if(listTreatmentCtx.selectedPatientId != 0U){
    patIndex = 0U;
    if((treatmentPatientFind(listTreatmentCtx.selectedPatientId, &patIndex) == TREATMENT_EPROM_OK)
       && (treatmentPatientGetByIndex(patIndex, &selPat) == TREATMENT_EPROM_OK)){
      treatmentLog.id = selPat.id;
      treatmentLog.age = selPat.age;
      treatmentLog.gender = (GENDER_ENUM)selPat.gender;
      strncpy(treatmentLog.name, selPat.name, sizeof(treatmentLog.name) - 1U);
    }
    //选中患者若已被删除等导致查不到: 保持id=0的新患者兜底路径, 避免外键悬空
  }
  //新患者进注册页, 已选老患者进编辑页; 先定页面再刷新, 避免控件残留
  NVRAM0[EM_DC_PAGE] = (treatmentLog.id == 0U)
    ? GDDC_PAGE_REGISTER_PATIENT : GDDC_PAGE_EDIT_PATIENT;
  updateListTreatmentDisplay();
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_EDIT_TREATMENT;
  SetScreen(NVRAM0[EM_DC_PAGE]);
}

void listTreatmentCreateConfirm(void){//编辑页OK: 校验患者信息后把当前治疗记录追加到EPROM末尾
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  treatmentEpromErr_t err;
  treatmentLog_t rec;
  uint16_t count;
  //校验提示写入当前所在页面(注册页/编辑页控件编号一致)
  if(listTreatmentNameValid(treatmentLog.name) == 0U){//姓名必须录入
    SetTextValue(NVRAM0[EM_DC_PAGE], GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)"SET NAME");
    return;
  }
  if((treatmentLog.gender != MALE) && (treatmentLog.gender != FEMALE)){//性别必须选择
    SetTextValue(NVRAM0[EM_DC_PAGE], GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)"SET GENDER");
    return;
  }
  if((treatmentLog.age == 0U) || (treatmentLog.age > 120U)){//年龄范围检查
    SetTextValue(NVRAM0[EM_DC_PAGE], GDDC_PAGE_EDIT_PATIENT_TEXT_ID, (uint8_t*)"SET AGE");
    return;
  }
  err = treatmentEpromAdd(&treatmentLog);//末尾追加: 自动分配新患者ID, 已有病历位置不变
  memset(dispBuf, 0x0, sizeof(dispBuf));
  if(err == TREATMENT_EPROM_OK){
    clearReleaseTimeEnergy();//本次发射已落成病历: 清发射计数, 防止同一台治疗被重复新建
    listTreatmentCtx.pendingValid = 0U;//本次治疗已落成病历, 避免重复新建
    //新患者建在患者表末尾: 清空查找字母保证新患者可见, 重建视图后窗口滚到末尾并选中新患者
    listTreatmentCtx.findText[0] = '\0';
    SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_CAPACITY, (uint8_t*)"");
    listTreatmentRebuildFilter();
    if(listTreatmentCtx.filteredCount > 0U){
      listTreatmentCtx.selectedIndex = (uint16_t)(listTreatmentCtx.filteredCount - 1U);
      listTreatmentCtx.topIndex = listTreatmentGetMaxTop();
      count = listTreatmentGetCount();
      if(treatmentEpromGet((uint16_t)(count - 1U), &rec) == TREATMENT_EPROM_OK){
        sprintf(dispBuf, "NEW AR %04u", (unsigned int)rec.id);
      }
    }
  }
  else if(err == TREATMENT_EPROM_ERR_FULL){
    sprintf(dispBuf, "TREAT FULL");
  }
  else{
    sprintf(dispBuf, "SAVE ERR:%d", (int)err);
  }
  refreshListTreatmentDisplay();
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

void listTreatmentCreateCancel(void){//编辑页CANCEL: 放弃本次新建, 返回病历列表页(EPROM不变)
  refreshListTreatmentDisplay();
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

//***************************************************************************
// 新建患者注册页(18) + 激光核对页(22)/放弃页(23)流程(见规格第十七节)
// 两入口: 激光停光自动弹核对页(22)后SAVE_RECORD; 列表页(13)CREATE_NEW手动新建
//***************************************************************************
static void listTreatmentEnterRegisterPage(void);
static void listTreatmentEnterVerifyPage(void);
static void listTreatmentRefreshVerifyDisplay(void);
static void listTreatmentGoListPage(void);

// 回病历列表页(13): 刷新并切页
static void listTreatmentGoListPage(void){
  refreshListTreatmentDisplay();
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

// 进入注册页: 建立按键未按下基线、清空提示, 显示预生成的最小空缺ID, 再切页
static void listTreatmentEnterRegisterPage(void){
  char idBuf[16];
  uint16_t suggestId = treatmentPatientSuggestId();
  SetButtonValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_KEY_OK, 0);
  SetButtonValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_KEY_CANCEL, 0);
  SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0, (uint8_t*)"");
  if(suggestId != 0U){
    sprintf(idBuf, "%04u", (unsigned int)suggestId);
  }
  else{
    sprintf(idBuf, "----");
  }
  dcHmiShowTreatmentCommon(GDDC_PAGE_REGISTER_PATIENT, idBuf, &treatmentLog);
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_REGISTER_PATIENT;
  SetScreen(GDDC_PAGE_REGISTER_PATIENT);
}

// 列表页CREATE_NEW: 手动新建患者(不要求激光发射), 清空患者字段后进注册页
void listTreatmentRegisterNewPatient(void){
  treatmentLog.id = 0U;
  treatmentLog.age = 0U;
  treatmentLog.gender = (GENDER_ENUM)0;
  memset(treatmentLog.name, 0, sizeof(treatmentLog.name));
  listTreatmentCtx.registerReturnPage = GDDC_PAGE_LIST_TREATMENT;
  listTreatmentEnterRegisterPage();
}

// 注册页OK: 校验姓名/年龄(1-150)/性别, 通过则新建患者(仅建患者);
// 若本次有激光待存记录则一并把治疗记录归属到新患者
void listTreatmentRegisterConfirm(void){
  patientRecord_t pat;
  uint16_t newId = 0U;
  treatmentEpromErr_t ce;
  uint8_t hadPending = listTreatmentCtx.pendingValid;
  if((listTreatmentNameValid(treatmentLog.name) == 0U)
     || ((treatmentLog.gender != MALE) && (treatmentLog.gender != FEMALE))
     || (treatmentLog.age == 0U) || (treatmentLog.age > PATIENT_AGE_LIMIT)){
    SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0,
                 (uint8_t*)"Invalid input, please re-enter!");
    return;
  }
  memset(&pat, 0, sizeof(pat));
  pat.age = treatmentLog.age;
  pat.gender = (uint8_t)treatmentLog.gender;
  memcpy(pat.name, treatmentLog.name, TREATMENT_NAME_SIZE);
  ce = treatmentPatientCreate(&pat, &newId);
  if(ce != TREATMENT_EPROM_OK){
    SetTextValue(GDDC_PAGE_REGISTER_PATIENT, GDDC_PAGE_REGISTER_PATIENT_TEXT_SUMMARY_0,
                 (uint8_t*)"Save failed, please retry!");
    return;
  }
  if(hadPending != 0U){//激光流程: 患者已建, 把本次治疗记录归属到新患者
    treatmentLog.id = newId;
    (void)treatmentEpromAddToPatient(newId, &treatmentLog);
    listTreatmentCtx.pendingValid = 0U;
    returnStandbyDisplay();//记录已落盘, 回待机页
  }
  listTreatmentGoListPage();//手动新建: 回列表页
}

// 注册页CANCEL: 不写入, 按来源页返回(核对页22/列表页13), 激光待存记录保留
void listTreatmentRegisterCancel(void){
  if(listTreatmentCtx.registerReturnPage == GDDC_PAGE_VERIFY_TREATMENT){
    listTreatmentEnterVerifyPage();
  }
  else{
    listTreatmentGoListPage();
  }
}

// 核对页渲染: 把待存治疗(已在treatmentLog)写入核对页各控件
static void listTreatmentRefreshVerifyDisplay(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  char idBuf[16];
  uint16_t suggestId;
  int32_t energyWhole, energyFrac;
  uint16_t mm, ss;
  suggestId = treatmentPatientSuggestId();
  if(suggestId != 0U){
    sprintf(idBuf, "%04u", (unsigned int)suggestId);
  }
  else{
    sprintf(idBuf, "----");
  }
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_ID, (uint8_t*)idBuf);
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_NAME,
               (uint8_t*)treatmentLog.name);
  if(treatmentLog.age != 0U){
    sprintf(dispBuf, "%u", (unsigned int)treatmentLog.age);
  }
  else{
    sprintf(dispBuf, "");
  }
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_AGE, (uint8_t*)dispBuf);
  //性别菜单(0=FeMale,1=Male)与性别文本
  if(treatmentLog.gender == FEMALE){
    SetSelectorValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER, 0);
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER, (uint8_t*)"FeMale");
  }
  else if(treatmentLog.gender == MALE){
    SetSelectorValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER, 1);
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER, (uint8_t*)"Male");
  }
  else{
    SetSelectorValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER, 0);
    SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_GENDER, (uint8_t*)"");
  }
  //治疗时刻
  if(treatmentLog.rtcYear >= 2000U){
    sprintf(dispBuf, "%04u-%02u-%02u %02u:%02u",
            (unsigned int)treatmentLog.rtcYear, (unsigned int)treatmentLog.rtcMonth,
            (unsigned int)treatmentLog.rtcDay, (unsigned int)treatmentLog.rtcHour,
            (unsigned int)treatmentLog.rtcMinute);
  }
  else{
    sprintf(dispBuf, "----");
  }
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_TIME, (uint8_t*)dispBuf);
  //能量(0.1J)
  energyWhole = treatmentLog.releaseEnergy / 10;
  energyFrac = treatmentLog.releaseEnergy % 10;
  if(energyFrac < 0){ energyFrac = -energyFrac; }
  sprintf(dispBuf, "%d.%d J", (int)energyWhole, (int)energyFrac);
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_ENERGY, (uint8_t*)dispBuf);
  //输出时长
  mm = (uint16_t)(treatmentLog.releaseTime / 60);
  ss = (uint16_t)(treatmentLog.releaseTime % 60);
  sprintf(dispBuf, "%02u:%02u", (unsigned int)mm, (unsigned int)ss);
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_OUT_TIME, (uint8_t*)dispBuf);
  //功率
  sprintf(dispBuf, "%d W", (int)treatmentLog.laserPower);
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_POWER, (uint8_t*)dispBuf);
  //方案
  if(treatmentLog.protocol == eCustiom){
    sprintf(dispBuf, "Custom");
  }
  else if(treatmentLog.pulseMode == LASER_MODE_MP){
    sprintf(dispBuf, "%s %u - Pulse", treatmentProtocolName(treatmentLog.protocol),
            (unsigned int)treatmentLog.schemeIndex + 1U);
  }
  else{
    sprintf(dispBuf, "%s %u - CW", treatmentProtocolName(treatmentLog.protocol),
            (unsigned int)treatmentLog.schemeIndex + 1U);
  }
  SetTextValue(GDDC_PAGE_VERIFY_TREATMENT, GDDC_PAGE_VERIFY_TREATMENT_TEXT_SUMMARY_SCHEME, (uint8_t*)dispBuf);
}

// 进入核对页: 渲染并切页(不复制快照, 调用方负责treatmentLog内容)
static void listTreatmentEnterVerifyPage(void){
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_VERIFY_TREATMENT;
  listTreatmentRefreshVerifyDisplay();
  SetScreen(GDDC_PAGE_VERIFY_TREATMENT);
}

// 激光停光后自动进入核对页: 用待存快照填充treatmentLog, 再进核对页
void listTreatmentVerifyAfterLaser(void){
  if(listTreatmentCtx.pendingValid != 0U){
    treatmentLog = listTreatmentCtx.pending;
  }
  treatmentLog.id = 0U;//新患者路径
  listTreatmentEnterVerifyPage();
}

// 核对页SAVE_RECORD: 已选已有患者则直接归属记录; 新患者进注册页填写
void listTreatmentVerifySaveRecord(void){
  if(treatmentLog.id != 0U){
    (void)treatmentEpromAddToPatient(treatmentLog.id, &treatmentLog);
    listTreatmentCtx.pendingValid = 0U;
    returnStandbyDisplay();
    return;
  }
  listTreatmentCtx.registerReturnPage = GDDC_PAGE_VERIFY_TREATMENT;
  listTreatmentEnterRegisterPage();
}

// 核对页SELECT_TREATMENT: 列表页进入"选择已有患者"模式, 选中后回核对页
void listTreatmentVerifySelect(void){
  listTreatmentCtx.verifySelectMode = 1U;
  enterListTreatmentPage();
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

// 核对页DISCARD_RECORD: 进入放弃页(23)
void listTreatmentVerifyDiscard(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  int32_t energyWhole, energyFrac;
  SetButtonValue(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_KEY_RETURN, 0);
  SetButtonValue(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_KEY_CANCEL, 0);
  SetTextValue(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_TEXT_NAME,
               (uint8_t*)treatmentLog.name);
  energyWhole = treatmentLog.releaseEnergy / 10;
  energyFrac = treatmentLog.releaseEnergy % 10;
  if(energyFrac < 0){ energyFrac = -energyFrac; }
  sprintf(dispBuf, "%d.%d J", (int)energyWhole, (int)energyFrac);
  SetTextValue(GDDC_PAGE_DISCARD_TREATMENT, GDDC_PAGE_DISCARD_TREATMENT_TEXT_ENERGY, (uint8_t*)dispBuf);
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DISCARD_TREATMENT;
  SetScreen(GDDC_PAGE_DISCARD_TREATMENT);
}

// 放弃页RETURN: 不放弃, 回核对页(22)
void listTreatmentDiscardReturn(void){
  listTreatmentEnterVerifyPage();
}

// 放弃页CANCEL: 确认放弃本次记录, 清除待存, 回待机页
void listTreatmentDiscardCancel(void){
  listTreatmentCtx.pendingValid = 0U;
  returnStandbyDisplay();
}

//***************************************************************************
//U盘操作确认页流程(非阻塞): SAVE/LOAD按键先进入确认页, 按CONFIRM才在轮询中执行一次整块读写, 按CANCEL直接回操作页
//导出与导入共用GDDC_PAGE_OPERATOR_USB_CONFIRM页面, 由usbOp区分(1=导出, 2=导入); 导入必须先确认, 避免未授权就覆盖机内病历

//触摸放行判断: 写入期间屏蔽一切触摸; 确认页只放行本页的确认与取消按键
//============================================================================
// 病历相关页面按键互锁: 任一按键按下(置1)到被单片机清零(置0)期间, 其他按键一律锁定
//============================================================================
static uint8_t  g_btnLockActive = 0U;//1=有按键处于"在途"状态
static uint16_t g_btnLockScreen = 0U;//在途按键所在画面
static uint16_t g_btnLockControl = 0U;//在途按键控件ID

//画面是否属于需要按键互锁的11个病历相关页面
static uint8_t treatmentIsLockPage(uint16_t screen){
  switch(screen){
    case GDDC_PAGE_LIST_TREATMENT:
    case GDDC_PAGE_DELETE_TREATMENT:
    case GDDC_PAGE_LIST_RECORD:
    case GDDC_PAGE_DELETE_RECORD:
    case GDDC_PAGE_EDIT_PATIENT:
    case GDDC_PAGE_REGISTER_PATIENT:
    case GDDC_PAGE_OPERATOR_USB:
    case GDDC_PAGE_OPERATOR_USB_SAVE:
    case GDDC_PAGE_OPERATOR_USB_LOAD:
    case GDDC_PAGE_VERIFY_TREATMENT:
    case GDDC_PAGE_DISCARD_TREATMENT:
      return 1U;
    default:
      return 0U;
  }
}

static void treatmentBtnLockArm(uint16_t screen, uint16_t control){
  g_btnLockActive = 1U;
  g_btnLockScreen = screen;
  g_btnLockControl = control;
}

//仅当释放的是当前在途按键时才解锁(防止误清其他按键的锁)
static void treatmentBtnLockRelease(uint16_t screen, uint16_t control){
  if((g_btnLockActive != 0U) && (g_btnLockScreen == screen) && (g_btnLockControl == control)){
    g_btnLockActive = 0U;
    g_btnLockScreen = 0U;
    g_btnLockControl = 0U;
  }
}

//画面切换/异常路径强制解锁, 防止在途按键被切走后整页永久锁死
static void treatmentBtnLockReset(void){
  g_btnLockActive = 0U;
  g_btnLockScreen = 0U;
  g_btnLockControl = 0U;
}

//按键互锁放行门: 非锁定页不干预; 按下时若已有在途按键则只放行同一按键(重复通知), 拒绝其他按键;
//弹起(瞬态键state=0)时释放对应锁。返回1=放行, 0=锁定
uint8_t treatmentButtonLockAllowed(uint16_t screen, uint16_t control, uint8_t state){
  if(treatmentIsLockPage(screen) == 0U){
    return 1U;
  }
  if(state == 0U){
    treatmentBtnLockRelease(screen, control);
    return 1U;
  }
  if(g_btnLockActive == 0U){
    treatmentBtnLockArm(screen, control);
    return 1U;
  }
  if((g_btnLockScreen == screen) && (g_btnLockControl == control)){
    return 1U;
  }
  return 0U;
}

//在途按键复位包装: 下发清零并同步解除互锁, 供各页自锁键复位统一调用
void treatmentReleaseButton(uint16_t screen, uint16_t control){
  SetButtonValue(screen, control, 0);
  treatmentBtnLockRelease(screen, control);
}

uint8_t listTreatmentUsbButtonAllowed(uint16_t screen_id, uint16_t control_id){
  //删除确认页等待期间: 只放行本页DELETE/CANCEL, 其余控件与页面一律屏蔽(与USB流程互斥)
  if(listTreatmentCtx.deletePatientId != 0U){
    if(screen_id != GDDC_PAGE_DELETE_TREATMENT){
      return 0U;
    }
    if((control_id == GDDC_PAGE_DELETE_TREATMENT_KEY_OK) ||
       (control_id == GDDC_PAGE_DELETE_TREATMENT_KEY_CANCEL)){
      return 1U;
    }
    return 0U;
  }
  if(listTreatmentCtx.usbState == 0U){
    return 1U;//空闲: 正常响应
  }
  if(listTreatmentCtx.usbState == 6U){//确认页(导出/导入分两页): 只放行本页OK/CANCEL
    if((screen_id != GDDC_PAGE_OPERATOR_USB_SAVE) &&
       (screen_id != GDDC_PAGE_OPERATOR_USB_LOAD)){
      return 0U;
    }
    //两个确认页的OK(11)/CANCEL(10)编号一致
    if((control_id == GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK) ||
       (control_id == GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL)){
      return 1U;
    }
    return 0U;
  }
  return 0U;//写入中(状态7): 不响应任何触摸操作
}

uint8_t listTreatmentUsbBusy(void){//提示页/确认页显示中
  return (listTreatmentCtx.usbState != 0U) ? 1U : 0U;
}

static uint16_t listTreatmentUsbPageOf(uint16_t state){//确认页状态(6/7)对应页面ID, 用于判断页面是否被别处切走
  (void)state;
  //按操作类型返回拆分后的确认页: 导入LOAD, 导出SAVE
  if(listTreatmentCtx.usbOp == 2U){
    return GDDC_PAGE_OPERATOR_USB_LOAD;
  }
  return GDDC_PAGE_OPERATOR_USB_SAVE;
}

//进入USB操作确认页: 导出进SAVE页/导入进LOAD页, 先刷新英文文案再切页, 避免上一页控件残留; 状态6等待用户按键
static void enterOperatorUsbConfirmPage(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t page;
  listTreatmentCtx.usbState = 6U;
  if(listTreatmentCtx.usbOp == 2U){//导入(LOAD): 两条文案分别说明"替换范围"与"备份内容", 数量取进入确认页时的机内值
    page = GDDC_PAGE_OPERATOR_USB_LOAD;
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "Replace all %u patients and %u treatment records on the device with the USB backup?",
      (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentGetCount());
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_0, (uint8_t*)dispBuf);
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "Backup contents: %u patients, %u treatment records.",
      (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentGetCount());
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_1, (uint8_t*)dispBuf);
    //屏幕工程LOAD页只保留SUMMARY_0/1两条文案: 第三方文本(控件3)按空串下发, 避免残留旧文案
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_LOAD_TEXT_SUMMARY_2, (uint8_t*)"");
  }
  else{//导出(SAVE): 文案带本次待导出的患者数/已保存治疗记录数, 屏幕页只有SUMMARY_0/1两个文本框
    page = GDDC_PAGE_OPERATOR_USB_SAVE;
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "Export %u patients and %u saved treatment records to USB?",
      (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentGetCount());
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_0, (uint8_t*)dispBuf);
    SetTextValue(page, GDDC_PAGE_OPERATOR_USB_SAVE_TEXT_SUMMARY_1,
      (uint8_t*)"The existing patient backup in this USB will be replaced.");
  }
  //进入确认页建立"全部按键未按下且可用"基线: 先显式清零OK/CANCEL自锁键按下态(屏幕会保留
  //自锁键运行态、不随切页复位, 不主动清零会出现两键同时显示按下), 再恢复触摸使能;
  //与页面13/19进入即清零一致, 两确认页OK=11/CANCEL=10编号一致
  SetButtonValue(page, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK, 0);
  SetButtonValue(page, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 0);
  SetControlEnable(page, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK, 1);
  SetControlEnable(page, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 1);
  NVRAM0[EM_DC_PAGE] = page;
  SetScreen(page);
}

void listTreatmentSaveUsbStart(void){//SAVE_USB按键: 不立即写盘, 先进入导出确认页, 由用户确认/取消(实际CSV写入在确认后执行)
  if(listTreatmentCtx.usbState != 0U){
    return;//上一次操作未结束
  }
  listTreatmentCtx.usbOp = 1U;
  listTreatmentCtx.usbErr = (uint8_t)TREATMENT_USB_ERR_MOUNT;
  listTreatmentCtx.usbCount = 0U;
  enterOperatorUsbConfirmPage();//进入导出确认页(状态6), 等待CANCEL/CONFIRM
  //SAVE自锁键释放已上移到notify层(无条件)
}

void listTreatmentLoadUsbStart(void){//LOAD_USB按键: 不立即读盘, 先进入确认页(确认后才读取U盘CSV覆盖机内病历)
  if(listTreatmentCtx.usbState != 0U){
    return;
  }
  listTreatmentCtx.usbOp = 2U;
  listTreatmentCtx.usbErr = (uint8_t)TREATMENT_USB_ERR_MOUNT;
  listTreatmentCtx.usbCount = 0U;
  enterOperatorUsbConfirmPage();//进入确认页(状态6), 等待CANCEL/CONFIRM
  //LOAD自锁键释放已上移到notify层(无条件)
}

void listTreatmentUsbConfirm(void){//确认页"OK"(导出/导入通用): 授权执行, 实际读写在轮询里完成一次
  if(listTreatmentCtx.usbState != 6U){
    return;
  }
  //OK按键保持按下: 待listTreatmentUsbLoop中功能执行完毕后再弹起
  listTreatmentCtx.usbState = 7U;
  //U盘读写期间锁定同页CANCEL: 状态7触摸门(互锁+USB门)已屏蔽全部操作, 这里再显式弹起CANCEL
  //并禁用其触摸, 明确禁止中途取消(两确认页CANCEL编号一致为10); 下次进入确认页时统一恢复
  {
    uint16_t confirmPage = (listTreatmentCtx.usbOp == 2U)
      ? GDDC_PAGE_OPERATOR_USB_LOAD : GDDC_PAGE_OPERATOR_USB_SAVE;
    SetButtonValue(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 0);
    SetControlEnable(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 0);
  }
}

void listTreatmentUsbCancel(void){//确认页"CANCEL"(导出/导入通用): 不读写, 直接返回USB操作页
  if(listTreatmentCtx.usbState != 6U){
    return;
  }
  listTreatmentCtx.usbState = 0U;
  //取消: 清空结果栏返回操作页。进入确认页前的LOAD/SAVE释放帧在切页前下发, 但屏幕对自锁键
  //运行态保留不可靠, 故返回前用refreshOperatorUsbDisplay重建"全部按键未按下"基线(含SAVE/LOAD/CANCEL),
  //否则LOAD键会停在按下态; usbText已置空, 该函数同时把SUMMARY_USB下发为空
  setOperatorUsbText("");
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPERATOR_USB;
  refreshOperatorUsbDisplay();//先清键+刷新控件(当前页仍为确认页, 帧目标操作页), 再切页
  SetScreen(GDDC_PAGE_OPERATOR_USB);
  //CANCEL自锁键释放已上移到notify层(无条件, 按SAVE/LOAD各自页面下发)
}

//***************************************************************************
//删除患者确认流程: DELETE_0-4先进入删除确认页(不立即删除), 确认后级联删除患者及其全部病历, 取消则返回列表页

//列表页DELETE_0-4: 解析窗口内对应患者, 缓存其id并进入删除确认页(英文文案), 等待确认/取消
void listTreatmentDeleteStart(uint8_t slot){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  uint16_t viewPos;
  patientRecord_t pat;
  if(listTreatmentCtx.deletePatientId != 0U){//已有删除流程在等待确认
    return;
  }
  if(slot >= LIST_TREATMENT_WINDOW_SIZE){
    return;
  }
  viewPos = (uint16_t)(listTreatmentCtx.topIndex + slot);
  if(viewPos >= listTreatmentCtx.filteredCount){//空槽位: 不响应
    return;
  }
  if(listTreatmentGetViewPatient(viewPos, &pat) == 0U){//视图位置取不到患者: 不响应
    return;
  }
  listTreatmentCtx.deletePatientId = pat.id;//缓存待删除患者编号(非0=进入删除确认流程)
  SetTextValue(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_TEXT_NAME_ID,
    (uint8_t*)"Delete Patient?");
  memset(dispBuf, 0x0, sizeof(dispBuf));
  sprintf(dispBuf, "Delete patient %s and all their treatment records?", pat.name);
  SetTextValue(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_0,
    (uint8_t*)dispBuf);
  memset(dispBuf, 0x0, sizeof(dispBuf));
  sprintf(dispBuf, "This patient has %u treatment record(s).",
    (unsigned int)treatmentGetRecordCountForPatient(pat.id));
  SetTextValue(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_1,
    (uint8_t*)dispBuf);
  SetTextValue(GDDC_PAGE_DELETE_TREATMENT, GDDC_PAGE_DELETE_TREATMENT_TEXT_SUMMARY_2,
    (uint8_t*)"This action cannot be undone.");
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DELETE_TREATMENT;
  SetScreen(GDDC_PAGE_DELETE_TREATMENT);
}

//删除确认页KEY_DELETE: 确认后级联删除患者及其全部病历, 再重建视图返回列表页
void listTreatmentDeleteConfirm(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  treatmentEpromErr_t err;
  uint16_t delId;
  if(listTreatmentCtx.deletePatientId == 0U){
    return;
  }
  delId = listTreatmentCtx.deletePatientId;
  //自锁键释放已上移到notify层(无条件), 本函数只做级联删除与视图重建
  err = treatmentPatientDelete(delId);//级联删除: 该患者全部记录+患者行
  listTreatmentCtx.deletePatientId = 0U;//退出删除流程
  if(delId == listTreatmentCtx.selectedPatientId){//删的正是当前选中患者: 清空选中, 避免外键/待机名悬空
    listTreatmentCtx.selectedPatientId = 0U;
    memset(listTreatmentCtx.selectedPatientName, 0x0, sizeof(listTreatmentCtx.selectedPatientName));
  }
  listTreatmentRebuildFilter();//患者表已变, 重建过滤视图
  refreshListTreatmentDisplay();//刷新列表(窗口自动夹取)
  memset(dispBuf, 0x0, sizeof(dispBuf));
  if(err == TREATMENT_EPROM_OK){
    sprintf(dispBuf, "DEL AR %04u OK", (unsigned int)delId);
  }
  else{
    sprintf(dispBuf, "DEL ERR:%d", (int)err);
  }
  SetTextValue(GDDC_PAGE_LIST_TREATMENT, GDDC_PAGE_LIST_TREATMENT_TEXT_DEBUG, (uint8_t*)dispBuf);
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

//删除确认页KEY_CANCEL: 不删除, 清除待删除id并返回列表页
void listTreatmentDeleteCancel(void){
  if(listTreatmentCtx.deletePatientId == 0U){
    return;
  }
  //自锁键释放已上移到notify层(无条件)
  listTreatmentCtx.deletePatientId = 0U;
  refreshListTreatmentDisplay();
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

/*****************************************************************************/
//患者历史治疗记录页(GDDC_PAGE_LIST_RECORD, 15): 单患者全部记录的浏览/翻页/删除/患者信息编辑
//单页条数 LIST_RECORD_WINDOW_SIZE 已在文件前部与 LIST_TREATMENT_WINDOW_SIZE 一并定义

//波长数值文本: 单波长"1470 nm", 双波长"1470+980 nm"
static void listRecordWaveText(uint8_t wave, char *buf){
  switch(wave){
    case WAVE_450:       sprintf(buf, "450 nm"); break;
    case WAVE_915:       sprintf(buf, "915 nm"); break;
    case WAVE_980:       sprintf(buf, "980 nm"); break;
    case WAVE_1064:      sprintf(buf, "1064 nm"); break;
    case WAVE_1470:      sprintf(buf, "1470 nm"); break;
    case WAVE_1920:      sprintf(buf, "1920 nm"); break;
    case WAVE_635:       sprintf(buf, "635 nm"); break;
    case WAVE_1940:      sprintf(buf, "1940 nm"); break;
    case WAVE_1470_980:  sprintf(buf, "1470+980 nm"); break;
    default:             sprintf(buf, "-- nm"); break;
  }
}

//按需收集当前患者记录窗口: 单遍扫描扁平记录, 用2字节id轻读过滤并统计该患者记录总数,
//仅缓存当前窗口(5)的全局索引, 完整行在渲染时才读; 记录按存储顺序(即追加/时间顺序)枚举
static void listTreatmentRecordCollectWindow(void){
  uint16_t total = treatmentEpromGetCount();
  uint16_t n = 0U;//该患者记录的累计序号
  uint8_t slot;
  listTreatmentCtx.recordCount = 0U;
  for(slot = 0U; slot < LIST_RECORD_WINDOW_SIZE; slot++){
    listTreatmentCtx.recordWindow[slot] = 0U;
  }
  for(uint16_t i = 0U; i < total; i++){
    uint16_t rowId;
    //id轻读: 仅读外键2字节(替代整行28字节), 写不下/读失败即终止
    if(treatmentRecordGetPatientIdByIndex(i, &rowId) != TREATMENT_EPROM_OK){
      break;
    }
    if(rowId == listTreatmentCtx.recordPatientId){
      if((n >= listTreatmentCtx.recordTop) &&
         (n < (uint16_t)(listTreatmentCtx.recordTop + LIST_RECORD_WINDOW_SIZE))){
        listTreatmentCtx.recordWindow[(uint8_t)(n - listTreatmentCtx.recordTop)] = i;
      }
      n++;
    }
  }
  listTreatmentCtx.recordCount = n;
  listTreatmentCtx.recordWindowTop = listTreatmentCtx.recordTop;
}

//重新枚举(进入/删除后): 令窗口缓存失效并立即按当前recordTop收集
static void listTreatmentRecordEnumerate(void){
  listTreatmentCtx.recordWindowTop = 0xFFFFU;
  listTreatmentRecordCollectWindow();
}

//记录页窗口最后一个合法recordTop(整页翻页, 恒为窗口大小整数倍)
static uint16_t listTreatmentRecordMaxTop(void){
  if(listTreatmentCtx.recordCount == 0U){
    return 0U;
  }
  return (uint16_t)(((uint16_t)listTreatmentCtx.recordCount - 1U)
                    / LIST_RECORD_WINDOW_SIZE * LIST_RECORD_WINDOW_SIZE);
}

//从病历列表页(13)KEY_EDIT_RECORD进入: slot为该页窗口内的槽位(0-4)
void listTreatmentRecordEnter(uint8_t slot){
  uint16_t viewPos;
  patientRecord_t pat;
  if(listTreatmentCtx.recordPatientId != 0U){
    return;
  }
  if(slot >= LIST_TREATMENT_WINDOW_SIZE){
    return;
  }
  viewPos = (uint16_t)(listTreatmentCtx.topIndex + slot);
  if(viewPos >= listTreatmentCtx.filteredCount){
    return;
  }
  if(listTreatmentGetViewPatient(viewPos, &pat) == 0U){
    return;
  }
  listTreatmentCtx.recordPatientId = pat.id;
  listTreatmentCtx.recordTop = 0U;
  listTreatmentCtx.deleteRecordGlobalIndex = 0xFFFFU;
  listTreatmentCtx.editPatientMode = 0U;
  listTreatmentRecordEnumerate();
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_RECORD;
  //先建立"全部按键未按下"基线并渲染, 再切页(与页面13/19进入路径一致); 不依赖屏幕冷加载
  //回传(DeviceScreenNotify=0时该回传不可靠), 否则进入即空白且按键停在按下态。控件20-28均为按钮
  for(uint16_t btn = GDDC_PAGE_LIST_RECORD_KEY_DELETE_0;
      btn <= GDDC_PAGE_LIST_RECORD_KEY_EDIT_PATIENT; btn++){
    SetButtonValue(GDDC_PAGE_LIST_RECORD, btn, 0);
  }
  refreshListRecordDisplay();
  SetScreen(GDDC_PAGE_LIST_RECORD);
}

//记录页显示刷新: 姓名行 + 5个记录槽(空槽隐藏) + 页码
void refreshListRecordDisplay(void){
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  char waveText[24];
  uint16_t patientIndex;
  patientRecord_t pat;
  uint16_t pageCount, pageNow;
  uint16_t maxTop;
  //先钳制recordTop到合法范围, 再按需收集当前窗口(翻页/删除后缓存可能失效)
  maxTop = listTreatmentRecordMaxTop();
  if(listTreatmentCtx.recordTop > maxTop){
    listTreatmentCtx.recordTop = maxTop;
  }
  if(listTreatmentCtx.recordWindowTop != listTreatmentCtx.recordTop){
    listTreatmentRecordCollectWindow();
  }
  //姓名行: "name - AR 0001", 患者ID统一加AR前缀(EPROM内仅存数字)
  if((treatmentPatientFind(listTreatmentCtx.recordPatientId, &patientIndex) == TREATMENT_EPROM_OK)
     && (treatmentPatientGetByIndex(patientIndex, &pat) == TREATMENT_EPROM_OK)){
    sprintf(dispBuf, "%s - AR %04u", pat.name, (unsigned int)pat.id);
  }
  else{
    sprintf(dispBuf, "-- - AR %04u", (unsigned int)listTreatmentCtx.recordPatientId);
  }
  SetTextValue(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_TEXT_NAME, (uint8_t*)dispBuf);
  //5个记录槽
  for(uint8_t i=0U; i<LIST_RECORD_WINDOW_SIZE; i++){
    uint16_t recPos = (uint16_t)(listTreatmentCtx.recordTop + i);
    uint16_t energyCtrl = (uint16_t)(GDDC_PAGE_LIST_RECORD_TEXT_TIME_ENERGY_0 + i);
    uint16_t schemeCtrl = (uint16_t)(GDDC_PAGE_LIST_RECORD_TEXT_SCHEME_WIDTH_0 + i);
    uint16_t deleteCtrl = (uint16_t)(GDDC_PAGE_LIST_RECORD_KEY_DELETE_0 + i);
    uint8_t occupied = 0U;
    if(recPos < listTreatmentCtx.recordCount){
      treatmentLog_t log;
      if(treatmentEpromGet(listTreatmentCtx.recordWindow[i], &log) == TREATMENT_EPROM_OK){
        uint16_t mm, ss;
        int32_t energyWhole, energyFrac;
        occupied = 1U;
        //时间/能量行: "2026-11-10 18:00 - 262.7 J - 00:19 - 30 W - 1470 nm"
        listRecordWaveText(log.laserWave, waveText);
        mm = (uint16_t)(log.releaseTime / 60);
        ss = (uint16_t)(log.releaseTime % 60);
        energyWhole = log.releaseEnergy / 10;
        energyFrac = log.releaseEnergy % 10;
        if(energyFrac < 0){
          energyFrac = -energyFrac;
        }
        if(log.rtcYear >= 2000U){
          sprintf(dispBuf,
                  "%04u-%02u-%02u %02u:%02u - %d.%d J - %02u:%02u - %d W - %s",
                  (unsigned int)log.rtcYear, (unsigned int)log.rtcMonth,
                  (unsigned int)log.rtcDay, (unsigned int)log.rtcHour,
                  (unsigned int)log.rtcMinute, (int)energyWhole, (int)energyFrac,
                  (unsigned int)mm, (unsigned int)ss, (int)log.laserPower, waveText);
        }
        else{
          sprintf(dispBuf,
                  "---- --:-- - %d.%d J - %02u:%02u - %d W - %s",
                  (int)energyWhole, (int)energyFrac, (unsigned int)mm,
                  (unsigned int)ss, (int)log.laserPower, waveText);
        }
        SetTextValue(GDDC_PAGE_LIST_RECORD, energyCtrl, (uint8_t*)dispBuf);
        //方案/模式行: 连续"Phlebology 1 - CW"; 脉冲"Phlebology 1 - Pulse - ON 600 / OFF 700 ms"
        if(log.protocol == eCustiom){
          sprintf(dispBuf, "Custom");
        }
        else if(log.pulseMode == LASER_MODE_MP){
          sprintf(dispBuf, "%s %u - Pulse - ON %u / OFF %u ms",
                  treatmentProtocolName(log.protocol),
                  (unsigned int)log.schemeIndex + 1U,
                  (unsigned int)log.posWidth, (unsigned int)log.negWidth);
        }
        else{
          sprintf(dispBuf, "%s %u - CW",
                  treatmentProtocolName(log.protocol),
                  (unsigned int)log.schemeIndex + 1U);
        }
        SetTextValue(GDDC_PAGE_LIST_RECORD, schemeCtrl, (uint8_t*)dispBuf);
      }
    }
    //空槽: 两行文本与删除键全部隐藏, 删除键同时禁用
    SetControlVisiable(GDDC_PAGE_LIST_RECORD, energyCtrl, occupied);
    SetControlVisiable(GDDC_PAGE_LIST_RECORD, schemeCtrl, occupied);
    SetControlVisiable(GDDC_PAGE_LIST_RECORD, deleteCtrl, occupied);
    SetControlEnable(GDDC_PAGE_LIST_RECORD, deleteCtrl, occupied);
  }
  //页码: "PAGE 1/2"(recordTop已在函数开头钳制)
  pageCount = (uint16_t)((listTreatmentCtx.recordCount
                         + (LIST_RECORD_WINDOW_SIZE - 1U)) / LIST_RECORD_WINDOW_SIZE);
  if(pageCount == 0U){
    pageCount = 1U;
  }
  pageNow = (uint16_t)(listTreatmentCtx.recordTop / LIST_RECORD_WINDOW_SIZE + 1U);
  sprintf(dispBuf, "PAGE %u/%u", (unsigned int)pageNow, (unsigned int)pageCount);
  SetTextValue(GDDC_PAGE_LIST_RECORD, GDDC_PAGE_LIST_RECORD_TEXT_PAGE, (uint8_t*)dispBuf);
}

//向前翻页(记录窗口上移5条)
void listTreatmentRecordPageUp(void){
  if(listTreatmentCtx.recordTop >= LIST_RECORD_WINDOW_SIZE){
    listTreatmentCtx.recordTop = (uint16_t)(listTreatmentCtx.recordTop - LIST_RECORD_WINDOW_SIZE);
    refreshListRecordDisplay();
  }
}

//向后翻页(记录窗口下移5条)
void listTreatmentRecordPageDown(void){
  uint16_t maxTop = listTreatmentRecordMaxTop();
  if(listTreatmentCtx.recordTop < maxTop){
    listTreatmentCtx.recordTop = (uint16_t)(listTreatmentCtx.recordTop + LIST_RECORD_WINDOW_SIZE);
    refreshListRecordDisplay();
  }
}

//CLOSE返回病历列表页(13)
void listTreatmentRecordClose(void){
  listTreatmentCtx.recordPatientId = 0U;
  listTreatmentCtx.editPatientMode = 0U;
  refreshListTreatmentDisplay();
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;
  SetScreen(GDDC_PAGE_LIST_TREATMENT);
}

//DELETE进入删除确认页(16): slot为记录页窗口内槽位(0-4)
void listTreatmentRecordDeleteStart(uint8_t slot){
  uint16_t recPos;
  if(listTreatmentCtx.deleteRecordGlobalIndex != 0xFFFFU){
    return;
  }
  if(slot >= LIST_RECORD_WINDOW_SIZE){
    return;
  }
  recPos = (uint16_t)(listTreatmentCtx.recordTop + slot);
  if(recPos >= listTreatmentCtx.recordCount){
    return;
  }
  listTreatmentCtx.deleteRecordGlobalIndex = listTreatmentCtx.recordWindow[slot];
  SetTextValue(GDDC_PAGE_DELETE_RECORD, GDDC_PAGE_DELETE_RECORD_TEXT_NAME,
               (uint8_t*)"Delete Record?");
  SetTextValue(GDDC_PAGE_DELETE_RECORD, GDDC_PAGE_DELETE_RECORD_TEXT_SUMMARY_0,
               (uint8_t*)"Delete this treatment record?");
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DELETE_RECORD;
  SetScreen(GDDC_PAGE_DELETE_RECORD);
}

//删除确认页OK: 删除该条记录, 重新枚举后回记录页(15)
void listTreatmentDeleteRecordConfirm(void){
  uint16_t idx = listTreatmentCtx.deleteRecordGlobalIndex;
  if(idx != 0xFFFFU){
    if(idx < treatmentEpromGetCount()){
      treatmentRecordDeleteByIndex(idx);
    }
    listTreatmentCtx.deleteRecordGlobalIndex = 0xFFFFU;
    listTreatmentRecordEnumerate();
  }
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_RECORD;
  SetScreen(GDDC_PAGE_LIST_RECORD);
}

//删除确认页CANCEL: 不删除, 回记录页(15)
void listTreatmentDeleteRecordCancel(void){
  listTreatmentCtx.deleteRecordGlobalIndex = 0xFFFFU;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_RECORD;
  SetScreen(GDDC_PAGE_LIST_RECORD);
}

//EDIT_PATIENT进入患者信息编辑页(17): 预填患者信息, 置更新模式(OK只更新患者, 不追加记录)
void listTreatmentRecordEditPatient(void){
  uint16_t patientIndex;
  patientRecord_t pat;
  char idBuf[16];
  if((treatmentPatientFind(listTreatmentCtx.recordPatientId, &patientIndex) != TREATMENT_EPROM_OK)
     || (treatmentPatientGetByIndex(patientIndex, &pat) != TREATMENT_EPROM_OK)){
    return;
  }
  memset(&treatmentLog, 0x0, sizeof(treatmentLog));
  treatmentLog.id = pat.id;
  treatmentLog.age = pat.age;
  treatmentLog.gender = (GENDER_ENUM)pat.gender;
  memcpy(treatmentLog.name, pat.name, TREATMENT_NAME_SIZE);
  sprintf(idBuf, "AR %04u", (unsigned int)pat.id);
  listTreatmentCtx.editPatientMode = 1U;
  dcHmiShowTreatmentCommon(GDDC_PAGE_EDIT_PATIENT, idBuf, &treatmentLog);
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_EDIT_PATIENT;
  SetScreen(GDDC_PAGE_EDIT_PATIENT);
}

//患者信息编辑页OK: 校验后更新患者信息, 回记录页(15)
void listTreatmentEditPatientConfirm(void){
  patientRecord_t row;
  if(listTreatmentCtx.editPatientMode == 0U){
    return;
  }
  if(treatmentLog.name[0] == 0){
    return;
  }
  memset(&row, 0x0, sizeof(row));
  row.id = listTreatmentCtx.recordPatientId;
  row.age = treatmentLog.age;
  row.gender = (uint8_t)treatmentLog.gender;
  memcpy(row.name, treatmentLog.name, TREATMENT_NAME_SIZE);
  treatmentPatientUpdate(listTreatmentCtx.recordPatientId, &row);
  listTreatmentCtx.editPatientMode = 0U;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_RECORD;
  SetScreen(GDDC_PAGE_LIST_RECORD);
}

//患者信息编辑页CANCEL: 不更新, 回记录页(15)
void listTreatmentEditPatientCancel(void){
  listTreatmentCtx.editPatientMode = 0U;
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_RECORD;
  SetScreen(GDDC_PAGE_LIST_RECORD);
}

//供NotifyButton判断当前编辑页是否为"患者信息更新模式"
uint8_t listTreatmentIsEditPatientMode(void){
  return listTreatmentCtx.editPatientMode;
}

//供NotifyButton判断列表页是否处于核对页"选择已有患者"模式
uint8_t listTreatmentIsVerifySelectMode(void){
  return listTreatmentCtx.verifySelectMode;
}

//核对选择模式下不选择而关闭列表: 取消该模式, 回核对页
void listTreatmentVerifySelectCancel(void){
  listTreatmentCtx.verifySelectMode = 0U;
  listTreatmentEnterVerifyPage();
}

void listTreatmentUsbLoop(void){//USB确认页轮询(非阻塞): 确认页等待按键, 确认后执行一次CSV导出/导入, 完成回USB操作页
  char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
  if(listTreatmentCtx.usbState == 0U){
    return;
  }
  if(NVRAM0[EM_DC_PAGE] != listTreatmentUsbPageOf(listTreatmentCtx.usbState)){//页面被别处切走(如关机确认/休眠): 放弃本次流程
    uint16_t confirmPage = (listTreatmentCtx.usbOp == 2U)
      ? GDDC_PAGE_OPERATOR_USB_LOAD : GDDC_PAGE_OPERATOR_USB_SAVE;
    //中止路径: 本确认页OK/CANCEL都可能处于按下态, 统一弹起并解除互锁避免按键永久锁死
    treatmentReleaseButton(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK);
    treatmentReleaseButton(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL);
    //恢复按键可用基线(读写期间CANCEL曾被禁用), 便于下次进入确认页状态一致
    SetControlEnable(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK, 1);
    SetControlEnable(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_CANCEL, 1);
    listTreatmentCtx.usbState = 0U;//退出忙状态, 否则触摸会被一直屏蔽
    return;
  }
  if(listTreatmentCtx.usbState == 6U){//确认页: 等用户按键, 不做读写
    return;
  }
  //状态7: 已确认, 执行一次导出或导入, 再回操作页并在SUMMARY_USB显示结果
  memset(dispBuf, 0x0, sizeof(dispBuf));
  if(listTreatmentCtx.usbOp == 2U){//导入: 读U盘CSV覆盖机内EPROM, 再回读本机与U盘逐条比较; 载入失败或比较不一致统一按失败提示
    listTreatmentCtx.usbErr = (uint8_t)treatmentLogLoadFromUdisk(&listTreatmentCtx.usbCount);
    if((listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_OK) && (treatmentLogVerifyUdisk() != 0U)){
      sprintf(dispBuf, "Backup imported from USB. Device records have been replaced.");
    }
    else{
      sprintf(dispBuf, "USB backup import failed!");
    }
  }
  else{//导出: 机内病历写CSV到U盘; 成功文案由下方"USB backup: X patients, Y treatment records"统一生成
    listTreatmentCtx.usbErr = (uint8_t)treatmentLogSaveToUdisk(&listTreatmentCtx.usbCount);
    if(listTreatmentCtx.usbErr != (uint8_t)TREATMENT_USB_OK){//失败: 按错误码填结果栏; 成功文案在下方统一生成
      if(listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_ERR_MOUNT){
        sprintf(dispBuf, "NO UDISK");
      }
      else if(listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_ERR_EMPTY){
        sprintf(dispBuf, "NO RECORDS");
      }
      else if(listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_ERR_OPEN){
        sprintf(dispBuf, "USB OPEN FAILED");
      }
      else{
        sprintf(dispBuf, "USB BACKUP FAILED");
      }
    }
  }
  listTreatmentCtx.usbState = 0U;//先退出忙状态(允许后续触摸)
  if((listTreatmentCtx.usbOp != 2U) && (listTreatmentCtx.usbErr == (uint8_t)TREATMENT_USB_OK)){
    //导出成功: 结果栏显示本次备份概况(患者数/已写入的治疗记录数), 替代原来的成功提示
    memset(dispBuf, 0x0, sizeof(dispBuf));
    sprintf(dispBuf, "USB backup: %u patients, %u treatment records",
      (unsigned int)treatmentEpromGetPatientCount(), (unsigned int)listTreatmentCtx.usbCount);
  }
  setOperatorUsbText(dispBuf);//结果文案交给usbText统一维护, 页面冷加载重发同内容不会覆盖
  refreshOperatorUsbDisplay();//刷新操作页摘要并下发结果栏
  //OK自锁键: 功能已全部执行完毕, 必须在切回操作页之前(确认页仍为当前页)下发清零,
  //切页后屏幕无法可靠清零旧页控件, 会导致OK键视觉停在按下态
  {
    uint16_t confirmPage = (listTreatmentCtx.usbOp == 2U)
      ? GDDC_PAGE_OPERATOR_USB_LOAD : GDDC_PAGE_OPERATOR_USB_SAVE;
    treatmentReleaseButton(confirmPage, GDDC_PAGE_OPERATOR_USB_SAVE_KEY_OK);
  }
  NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPERATOR_USB;
  SetScreen(GDDC_PAGE_OPERATOR_USB);
}

void updateAcousticDisplay(void){//更新提示音设置
	char dispBuf[CONFIG_DCHMI_DISKBUF_SIZE];
	float ftmp;
	int16_t cycle = 0;
	if(NVRAM0[EM_LASER_PULSE_MODE] ==LASER_MODE_CW){//CW
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "");
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_ACOUSTIC_CYCLE, (uint8_t*)dispBuf);
		
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%d S", NVRAM0[EM_ACOUSTIC_TIME]);
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_ACOUSTIC_TIME, (uint8_t*)dispBuf);
	}
	if(LD(R_ACOUSTIC_ENABLE)){
		cycle = NVRAM0[EM_ACOUSTIC_TIME] / NVRAM0[EM_ACOUSTIC_TIME_STEP];
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%d Cycle", cycle);
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_ACOUSTIC_CYCLE, (uint8_t*)dispBuf);
		
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "%d S", NVRAM0[EM_ACOUSTIC_TIME]);
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_ACOUSTIC_TIME, (uint8_t*)dispBuf);
	}
	else{
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "");
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_ACOUSTIC_CYCLE, (uint8_t*)dispBuf);
		memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
		sprintf(dispBuf, "N/A");
		SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_ACOUSTIC_TIME, (uint8_t*)dispBuf);		
	}
	memset(dispBuf, 0x0, CONFIG_DCHMI_DISKBUF_SIZE);
	ftmp = ((float)(NVRAM0[EM_ACOUSTIC_ENERGY])) / 10.0F;
	if(LD(R_ACOUSTIC_ENABLE)){
		sprintf(dispBuf, "%4.1fJ", ftmp);
	}
	else{
		sprintf(dispBuf, "N/A");
	}
	SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_ACOUSTIC_ENERGY, (uint8_t*)dispBuf);
	//调试信息
	printf("%s,%d,%s:acoustic time = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_TIME]);
	printf("%s,%d,%s:acoustic energy = %d\n", __FILE__, __LINE__, __func__, NVRAM0[EM_ACOUSTIC_ENERGY]);
	printf("%s,%d,%s:acoustic cycle = %d\n", __FILE__, __LINE__, __func__, cycle);	
}

void dcHmiLoopInit(void){//初始化模块
	//PID参数初始化
	loadDeviceConfig();//载入硬件配置
  if(LD(SPCOIL_DM_CRC_FAIL) || (LD(SPCOIL_MR_CRC_FAIL))){//DM或MR校验失败恢复默认设置
#if (CONFIG_DEBUG_NVRAM == 1)
    printf("%s,%d,%s:[DIAG]NVRAM CRC FAIL -> restoreDefault() (dm=%d mr=%d)\n",__FILE__, __LINE__, __func__, LD(SPCOIL_DM_CRC_FAIL), LD(SPCOIL_MR_CRC_FAIL));
#endif
    restoreDefault();//需要添加内容
    RRES(SPCOIL_DM_CRC_FAIL);
    RRES(SPCOIL_MR_CRC_FAIL);
#if (CONFIG_DEBUG_NVRAM == 1)
    printf("%s,%d,%s:[DIAG]restoreDefault done, mark cleared (dm=%d mr=%d)\n",__FILE__, __LINE__, __func__, LD(SPCOIL_DM_CRC_FAIL), LD(SPCOIL_MR_CRC_FAIL));
#endif
  }
  if(LD(SPCOIL_FD_CRC_FAIL)){//FD校验失败恢复默认方案
#if (CONFIG_DEBUG_NVRAM == 1)
    printf("%s,%d,%s:[DIAG]FD CRC FAIL -> restoreScheme(1)\n",__FILE__, __LINE__, __func__);
#endif
    restoreScheme(1);//恢复默认方案
    RRES(SPCOIL_FD_CRC_FAIL);
#if (CONFIG_DEBUG_NVRAM == 1)
    printf("%s,%d,%s:[DIAG]restoreScheme done, mark cleared (fd=%d)\n",__FILE__, __LINE__, __func__, LD(SPCOIL_FD_CRC_FAIL));
#endif
  }
  if(LD(SPCOIL_BK_CRC_FAIL)){//BK校验失败: 重置BKSRAM默认值并写回EPROM(自愈, 保证下次上电CRC通过)
#if (CONFIG_DEBUG_NVRAM == 1)
    printf("%s,%d,%s:[DIAG]BK CRC FAIL -> BKSRAM clear + BkramSave + BkramLoad\n",__FILE__, __LINE__, __func__);
#endif
    memset((uint8_t*)CONFIG_BKSRAM_BASE_ADDR, 0x0, (CONFIG_BKRAM_SIZE * 4));//BKSRAM清默认值
    sPlcBkramSave();//默认值写回EPROM(含CRC)
    sPlcBkramLoad();//重校验(成功自动清除BK失败标记)
#if (CONFIG_DEBUG_NVRAM == 1)
    printf("%s,%d,%s:[DIAG]BK self-heal done (bk=%d)\n",__FILE__, __LINE__, __func__, LD(SPCOIL_BK_CRC_FAIL));
#endif
  }
	//固件变化判断: 计算当前固件CRC32与上次保存值比较, 不一致(首次烧录/固件升级/CRC失败恢复默认)则清空病历区块
	uint32_t curFwCrc = treatmentEpromCalcFwCrc();
	uint32_t savedFwCrc = (uint32_t)(uint16_t)NVRAM0[DM_TREATMENT_FW_CRC_L]
	                   | ((uint32_t)(uint16_t)NVRAM0[DM_TREATMENT_FW_CRC_H] << 16);
	if(curFwCrc != savedFwCrc){
		treatmentEpromClear();//清空病历区块(逐槽写0xFF,并置DM_TREATMENT_NUM=0)
		NVRAM0[DM_TREATMENT_FW_CRC_L] = (int16_t)(curFwCrc & 0xFFFFu);
		NVRAM0[DM_TREATMENT_FW_CRC_H] = (int16_t)((curFwCrc >> 16) & 0xFFFFu);
	}
	//校准病历数量:扫描EPROM治疗记录区块得到实际有效病历数,写入DM_TREATMENT_NUM。
	//固件变化时已在上一步清空,扫描结果为0; 其余情况NVRAM与实际不一致时,以此处扫描结果为准完成自愈
	NVRAM0[DM_TREATMENT_NUM] = (int16_t)treatmentEpromGetCount();
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
	standbyKeyTouchEnableStatus = -1;
	setRedLaserPwm(0);
	hmiUartInit();
	restoreScheme(0);//不恢复自定义方案
	loadSelectScheme(NVRAM0[DM_SCHEME_CLASSIFY], NVRAM0[DM_SCHEME_INDEX]);
	//NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_HIBERNATE;
  NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_IDLE;
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
	
	SSET(Y_GREEN_LED);//打开绿灯
	RRES(Y_RED_LED);
	RRES(Y_YELLOW_LED);
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
	//wfswLoop(&APP_CONFIG_WFSW_PORT);
	speakerLoop();
	statusLoop();
	tempControlLoop();
	gddcHmiLoop();
	listTreatmentUsbLoop();//U盘提示页面轮询(非阻塞)
	listTreatmentStepWatch();//监视停光: 抓取待新建病历快照
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
		tempControlInit();
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
			FlashRestoreControl(HMI_FLASH_DATA_VERSION, HMI_FLASH_DATA_ADDR);
			RRES(R_DCHMI_RESTORE_DOING);
			SSET(R_DCHMI_RESTORE_DONE);
			//设置HMI页面
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_WAIT_ENTER_PASSCODE;
			MsgId = ERR_NO_ERROR;//当前显示的信息ID
		
			SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, false);			
			SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_STANDBY, true);
			
			SetButtonValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, false);					
			SetControlEnable(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_KEY_SCHEME_SAVE, true);

			SetTextValue(GDDC_PAGE_STANDBY, GDDC_PAGE_STANDBY_TEXT_WARN, " ");//清空警报信息栏
			
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_RFID, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FIBER_PROBE, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_AUTO_FAN, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_CLEAR_EPROM, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FOOTSWITCH, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_TEMPERATURE, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_ESTOP, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_INTERLOCK, false);		
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_FLOW, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_DISABLE_HUMIDITY, false);	
			
			SetTextValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, (uint8_t*)(""));
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, false);
			
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, true);
			
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			
			SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
      NVRAM0[EM_DC_PAGE] = GDDC_PAGE_POWERUP;	
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
					if(LD(R_LASER_A_DIODE_TEMP_HIGH)){//激光器高温保护
						updateWarnMsgDisplay(ERR_LASER_A_DIODE_TEMP_HIGH);
					}
					else if(LD(R_LASER_A_DIODE_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_LASER_A_DIODE_TEMP_LOW);
					}
					else if(LD(R_LASER_B_DIODE_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_LASER_B_DIODE_TEMP_HIGH);
					}
					else if(LD(R_LASER_B_DIODE_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_LASER_B_DIODE_TEMP_LOW);
					}					
					else if(LD(R_LASER_A_COUPLER_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_LASER_A_COUPLER_TEMP_HIGH);
					}
					else if(LD(R_LASER_B_COUPLER_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_LASER_B_COUPLER_TEMP_HIGH);
					}
					else if(LD(R_LASER_A_COUPLER_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_LASER_A_COUPLER_TEMP_LOW);
					}
					else if(LD(R_LASER_B_COUPLER_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_LASER_B_COUPLER_TEMP_LOW);
					}
					else if(LD(R_LASER_A_CRYST0_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_LASER_A_CRYST0_TEMP_HIGH);
					}						
					else if(LD(R_LASER_A_CRYST0_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_LASER_A_CRYST0_TEMP_LOW);
					}						
					else if(LD(R_LASER_A_CRYST1_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_LASER_A_CRYST1_TEMP_HIGH);
					}						
					else if(LD(R_LASER_A_CRYST1_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_LASER_A_CRYST1_TEMP_LOW);
					}						
					else if(LD(R_LASER_B_CRYST0_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_LASER_B_CRYST0_TEMP_HIGH);
					}						
					else if(LD(R_LASER_B_CRYST0_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_LASER_B_CRYST0_TEMP_LOW);
					}						
					else if(LD(R_LASER_B_CRYST1_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_LASER_B_CRYST1_TEMP_HIGH);
					}						
					else if(LD(R_LASER_B_CRYST1_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_LASER_B_CRYST1_TEMP_LOW);
					}						
					else if(LD(R_HT0_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_HT0_TEMP_HIGH);
					}						
					else if(LD(R_HT1_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_HT1_TEMP_HIGH);
					}						
					else if(LD(R_HT2_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_HT2_TEMP_HIGH);
					}						
					else if(LD(R_HT3_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_HT3_TEMP_HIGH);
					}
					else if(LD(R_HWATER_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_HWATER_TEMP_HIGH);
					}						
					else if(LD(R_HWATER_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_HWATER_TEMP_LOW);
					}			
					else if(LD(R_CWATER_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_CWATER_TEMP_HIGH);
					}			
					else if(LD(R_CWATER_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_CWATER_TEMP_LOW);
					}				
					else if(LD(R_AMBIENT0_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_AMBIENT0_TEMP_HIGH);
					}		
					else if(LD(R_AMBIENT0_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_AMBIENT0_TEMP_LOW);
					}		
					else if(LD(R_AMBIENT1_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_AMBIENT1_TEMP_HIGH);
					}		
					else if(LD(R_AMBIENT1_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_AMBIENT1_TEMP_LOW);
					}		
					else if(LD(R_AMBIENT2_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_AMBIENT2_TEMP_HIGH);
					}		
					else if(LD(R_AMBIENT2_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_AMBIENT2_TEMP_LOW);
					}		
					else if(LD(R_AMBIENT3_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_AMBIENT3_TEMP_HIGH);
					}		
					else if(LD(R_AMBIENT3_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_AMBIENT3_TEMP_LOW);
					}	
					else if(LD(R_HDC1080_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_HDC1080_TEMP_HIGH);
					}		
					else if(LD(R_HDC1080_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_HDC1080_TEMP_LOW);
					}	
					else if(LD(R_DHT11_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_DHT11_TEMP_HIGH);
					}
					else if(LD(R_DHT11_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_DHT11_TEMP_HIGH);
					}			
					else if(LD(R_MCU_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_MCU_TEMP_HIGH);
					}						
					else if(LD(R_MCU_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_MCU_TEMP_LOW);
					}						
					else if(LD(R_MBAT_TEMP_HIGH)){
						updateWarnMsgDisplay(ERR_MBAT_TEMP_HIGH);
					}
					else if(LD(R_MBAT_TEMP_LOW)){
						updateWarnMsgDisplay(ERR_MBAT_TEMP_LOW);
					}
					else if(LD(R_HWATER_FLOW_LOW)){
						updateWarnMsgDisplay(ERR_HWATER_FLOW_LOW);
					}
					else if(LD(R_CWATER_FLOW_LOW)){
						updateWarnMsgDisplay(ERR_CWATER_FLOW_LOW);
					}						
				}
				else if(LD(R_FLOW_FAULT)){
					if(LD(R_HWATER_FLOW_LOW)){
						updateWarnMsgDisplay(ERR_HWATER_FLOW_LOW);
					}
					else if(LD(R_CWATER_FLOW_LOW)){
						updateWarnMsgDisplay(ERR_CWATER_FLOW_LOW);
					}
				}
				else if(LD(R_HUMIDITY_FALUT)){					
					if(LD(R_DHT11_HUMIDITY_HIGH)){
						updateWarnMsgDisplay(ERR_DHT11_TEMP_HIGH);
					}
					else if(LD(R_DHT11_HUMIDITY_LOW)){
						updateWarnMsgDisplay(ERR_DHT11_TEMP_LOW);
					}
					else if(LD(R_HDC1080_HUMIDITY_HIGH)){
						updateWarnMsgDisplay(ERR_HDC1080_HUMIDITY_HIGH);
					}
					else if(LD(R_HDC1080_HUMIDITY_LOW)){
						updateWarnMsgDisplay(ERR_HDC1080_HUMIDITY_LOW);
					}					
				}
				else if(LD(R_ESTOP)){//急停按下
					updateWarnMsgDisplay(ERR_ESTOP_PRESS);		
				}
				else if(LD(R_INTERLOCK)){//安全连锁拔出
					updateWarnMsgDisplay(ERR_INTERLOCK_UNPLUG);
				}
				else if(LDB(R_FIBER_PROBE)){//光纤拔出
					updateWarnMsgDisplay(ERR_FIBER_UNPLUG);
				}
				else if(LDB(R_FOOTSWITCH_PLUG)){//脚踏拔出
					updateWarnMsgDisplay(ERR_FOOTSWITCH_UNPLUG);
				}
				else if(LDB(R_RFID_PASS)){//光纤ID不匹配
					updateWarnMsgDisplay(ERR_FIBER_MISSMATE);
				}
				standbyKeyTouchEnable(false);//禁止Standby触摸
				NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_3;//设置喇叭声音模式
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SSET(SPCOIL_BEEM_ENABLE);//启动喇叭
			}
			else{//无故障显示
				RRES(SPCOIL_BEEM_ENABLE);
				updateWarnMsgDisplay(ERR_NO_ERROR);
				standbyKeyTouchEnable(true);
			}
		}
		if(LDB(R_FAULT) && LDP(SPCOIL_PS100MS)){//无故障显示
			RRES(SPCOIL_BEEM_ENABLE);
			updateWarnMsgDisplay(ERR_NO_ERROR);
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
		if(LD(R_STANDBY_KEY_STNADBY_DOWN) && LD(X_ESTOP_NC)){//点击READY 且急停未按下
			SET_SAFE_RESET_ON;//复位急停
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
			
#if defined(APP_CONFIG_WAVE_1470_635)
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
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH2){
				NVRAM0[SPREG_DAC_0] = 0;UPDAC0();
				NVRAM0[SPREG_DAC_1] = 0;UPDAC1();
			}	
			NVRAM0[SPREG_DAC_16] = (NVRAM0[DM_RAIM_BRG] * deviceConfig.redAimGain) + deviceConfig.redOffset;
			UPDAC16();//打开红光
#endif

#if defined(APP_CONFIG_WAVE_1940_1470_635)
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
			if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH2){
				NVRAM0[SPREG_DAC_0] = 0;UPDAC0();
				NVRAM0[SPREG_DAC_1] = 0;UPDAC1();
			}	
			NVRAM0[SPREG_DAC_16] = (NVRAM0[DM_RAIM_BRG] * deviceConfig.redAimGain) + deviceConfig.redOffset;
			UPDAC16();//打开红光
#endif
     
			printf("%s,%d,%s:SPREG_DAC_0=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_0]);
			printf("%s,%d,%s:SPREG_DAC_1=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_1]);
			printf("%s,%d,%s:SPREG_DAC_2=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_2]);
			printf("%s,%d,%s:SPREG_DAC_3=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_3]);
			printf("%s,%d,%s:SPREG_DAC_4=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_4]);
			printf("%s,%d,%s:SPREG_DAC_5=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_5]);
			printf("%s,%d,%s:SPREG_DAC_6=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_6]);
			printf("%s,%d,%s:SPREG_DAC_7=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_7]);
			printf("%s,%d,%s:SPREG_DAC_16=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_16]);
			printf("%s,%d,%s:SPREG_DAC_17=0x%04X\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_DAC_17]);
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_READY_LOAD_PARA;	
			RRES(R_STANDBY_KEY_STNADBY_DOWN);
			standbyKeyValue(0);
			//先刷新READY页控件(指令带screen id,可预刷新后台页面)
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//指定目标页面
			readyPageTouchEnable(0);
			readyKeyValue(1);
			updateReadyDisplay();
			SetScreen(NVRAM0[EM_DC_PAGE]);//再切换页面,避免上一页控件残留
			SET_SAFE_RESET_OFF;//复位急停
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
		if(LD(R_STANDBY_KEY_ENTER_LIST_TREATMENT_DOWN)){
      //切换到GDDC_PAGE_LIST_TREATMENT页面: 患者按EPROM储存顺序排列, 每页5人(NAME/ID/RECORD_COUNT_0-4)
      //KEY_PAGE_UP/KEY_PAGE_DOWN为整页翻页: 按一次向前/向后翻5个患者, 到第一页/最后一页时不再移动
      //KEY_SELECT_PATIENT_0-4选择当前页对应位置的患者; SEARCH_NAME输入字母时按姓名前缀实时过滤
      //PAGE_NUM显示当前页/总页数, CAPACITY显示全局去重患者数与记录数
			
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_LIST_TREATMENT;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_LIST_TREATMENT;	
			//先重建患者视图并显示第一页, 再切页避免上一页控件残留
			enterListTreatmentPage();
			SetScreen(NVRAM0[EM_DC_PAGE]);//再切换页面,避免上一页控件残留
			//清除进入标志,避免返回待机状态后标志残留导致再次自动进入本页
			RRES(R_STANDBY_KEY_ENTER_LIST_TREATMENT_DOWN);
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
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_READY;//指定目标页面
			//先刷新READY页控件使能状态(指令带screen id,可预刷新)
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
			SetScreen(NVRAM0[EM_DC_PAGE]);//控件刷新后再切页,避免控件残留
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
			returnStandbyDisplay();//统一返回待机页面:状态机+页面+SetScreen+刷新
			standbyKeyValue(false);
			if(LD(R_STANDBY_KEY_STNADBY_UP)){
				RRES(R_STANDBY_KEY_STNADBY_UP);
			}
			updateWarnMsgDisplay(ERR_NO_ERROR);//显示警告信息
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
		if(LDP(SPCOIL_PS10MS) && LD(R_LASER_FALG_EMITING)){
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
		if(LDB(X_ESTOP_NC) || LD(R_STANDBY_KEY_STNADBY_UP) || LD(R_FAULT)){//回到等待状态
			EDLAR();//停止发射
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			NVRAM0[SPREG_DAC_4] = 0;NVRAM0[SPREG_DAC_5] = 0;NVRAM0[SPREG_DAC_6] = 0;NVRAM0[SPREG_DAC_7] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();UPDAC4();UPDAC5();UPDAC6();UPDAC7();
			NVRAM0[SPREG_DAC_16] = 0;NVRAM0[SPREG_DAC_17] = 0;
			UPDAC16();UPDAC17();
			returnStandbyDisplay();//统一返回待机页面:状态机+页面+SetScreen+刷新
			standbyKeyValue(0);
			if(LD(R_STANDBY_KEY_STNADBY_UP)){
				RRES(R_STANDBY_KEY_STNADBY_UP);
			}
			updateWarnMsgDisplay(ERR_NO_ERROR);//显示警告信息
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
			updateWarnMsgDisplay(ERR_NO_ERROR);
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
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXT_BEEP_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
				SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEP_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//更新进度条
			}
			RRES(R_OPTION_KEY_BEEM_VOLUME_ADD_DOWN);
		}
		if(LD(R_OPTION_KEY_BEEM_VOLUME_DEC_DOWN)){
			if(NVRAM0[DM_BEEM_VOLUME] > 0){
				NVRAM0[DM_BEEM_VOLUME] -= 1;
				NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXT_BEEP_VOLUME , NVRAM0[DM_BEEM_VOLUME], 1, 0);
				SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_BEEP_VOLUME, NVRAM0[DM_BEEM_VOLUME]);//更新进度条
			}
			RRES(R_OPTION_KEY_BEEM_VOLUME_DEC_DOWN);
		}
		if(LD(R_OPTION_KEY_LCD_BRG_ADD_DOWN)){					
			if(NVRAM0[DM_LCD_BRG] < CONFIG_LCD_MAX_DC){
				NVRAM0[DM_LCD_BRG] += 1;
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXT_LCD_BRG , NVRAM0[DM_LCD_BRG], 1, 0);
				SetProgressValue(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_PROGRESS_LCD_BRG, NVRAM0[DM_LCD_BRG]);
				SetBackLight(getLcdDuty(NVRAM0[DM_LCD_BRG]));
			}
			RRES(R_OPTION_KEY_LCD_BRG_ADD_DOWN);
		}
		if(LD(R_OPTION_KEY_LCD_BRG_DEC_DOWN)){					
			if(NVRAM0[DM_LCD_BRG] > CONFIG_LCD_MIN_DC){
				NVRAM0[DM_LCD_BRG] -= 1;
				SetTextInt32(GDDC_PAGE_OPTION, GDDC_PAGE_OPTION_TEXT_LCD_BRG , NVRAM0[DM_LCD_BRG], 1, 0);
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
			updateDiagnosis();//先刷新诊断页控件(指令带screen id,可预刷新)
			SetScreen(NVRAM0[EM_DC_PAGE]);//再切页,避免控件残留
			RRES(R_OPTION_KEY_ENTER_DIAGNOSIS_DOWN);
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_INFORMATION){//信息界面
		if(LD(R_INFORMATION_KEY_OK_DOWN)){
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_OPTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_OPTION;
			updateOptionDisplay();
			SetScreen(NVRAM0[EM_DC_PAGE]);
			RRES(R_INFORMATION_KEY_OK_DOWN);	
		}
		if(LDP(SPCOIL_PS500MS)){//刷新RTC 显示
			uint8_t year = 0, month = 0, day = 0, hour = 0, minute = 0, second = 0;
			char dispBuf[64];

			RtcGetNowTime(&year, &month, &day, &hour, &minute, &second);//获取当前时间可循环调用
			memset(dispBuf, 0x0, sizeof(dispBuf));
			sprintf(dispBuf, "Year:%d-Month:%d-Day:%d  Hour:%d-Minute:%d-Second:%d", year, month, day, hour, minute, second);
			SetTextValue(GDDC_PAGE_READY, GDDC_PAGE_READY_TEXT_ACOUSTIC_TIME, (uint8_t*)dispBuf);
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
			SetTextValue(GDDC_PAGE_RENAME, GDDC_PAGE_RENAME_TEXT_NEWNAME, (uint8_t*)(FDRAM1 + (NVRAM0[EM_SCHEME_NUM_TMP] * 64)));
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
			updateOptionDisplay();
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
			treatmentEpromClear();//清空病历治疗区块(逐槽写0xFF,并置DM_TREATMENT_NUM=0)
			resetGddcHmi();
      softDelayMs(1000);
			REBOOT();	
		}
		else if(LD(R_SAVE_EPROM)){//储存配制到EPROM
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			__set_PRIMASK(0);//关闭中断
			sPlcNvramSave();//更新NVRAM
			sPlcFdramSave();//更新FDRAM
			saveDeviceConfig();//更新配制
			resetGddcHmi();
			softDelayMs(1000);
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
			softDelayMs(1000);//等待4秒
			REBOOT();	
		}
		else if(LD(R_UPDATE_BOOTLOAD_REQ)){//更新Boot load请求
			SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_TEXT_FIRMWARE_INFO, true);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
			if(updateBootloadReq()){
				SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, true);
				SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, true);
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, true);	
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, true);	
			}
			else{
				SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
				SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);	
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);	
				
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, true);
				
				SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
				SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);
			}
			RRES(R_UPDATE_BOOTLOAD_REQ);
		}
		else if(LD(R_UPDATE_BOOTLOAD_YES)){//执行Bootload更新	
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			confirmBootloadUpdate();
		}
		else if(LD(R_UPDATE_BOOTLOAD_NO)){//错误Bootload更新序列
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			
			exitBootloadUpdate();
			
			SetButtonValue(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_REQ, true);
			
			SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_YES, false);
			SetControlVisiable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_UPDATE_BOOTLOAD_NO, false);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS, GDDC_PAGE_DIAGNOSIS_KEY_ENTER_OK, true);
			RRES(R_UPDATE_BOOTLOAD_NO);
		}
		else if(LDP(R_DIAGNOSIS_GOTO_CORRECTION_DOWN)){//进入校正页面
			SET_SAFE_RESET_ON;
			NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_CORRECTION;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS_CALI;
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH0, true);	
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH1, true);	
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH2, true);	
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH3, true);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH4, true);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH5, true);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH6, true);
			SetControlEnable(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH7, true);

      SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH0, false);
      SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH1, false);
      SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH2, false);
      SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH3, false);
      SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH4, false);
      SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH5, false);
      SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH6, false);
      SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH7, false);
      
      SetTextInt32( GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH0, 0, 0, 3);
      SetTextInt32( GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH1, 0, 0, 3);
      SetTextInt32( GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH2, 0, 0, 3);
      SetTextInt32( GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH3, 0, 0, 3);
      SetTextInt32( GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH4, 0, 0, 3);
      SetTextInt32( GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH5, 0, 0, 3);
      SetTextInt32( GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH6, 0, 0, 3);
      SetTextInt32( GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_TEXT_CSET_CH7, 0, 0, 3);
      
			SET_LASER_CH0_OFF;SET_LASER_CH1_OFF;SET_LASER_CH2_OFF;SET_LASER_CH3_OFF;
			SET_LASER_CH4_OFF;SET_LASER_CH5_OFF;SET_LASER_CH6_OFF;SET_LASER_CH7_OFF;
			NVRAM0[EM_CALI_CUR_SET_CH0] = 0;NVRAM0[EM_CALI_CUR_SET_CH1] = 0;NVRAM0[EM_CALI_CUR_SET_CH2] = 0;NVRAM0[EM_CALI_CUR_SET_CH3] = 0;
			NVRAM0[EM_CALI_CUR_SET_CH4] = 0;NVRAM0[EM_CALI_CUR_SET_CH5] = 0;NVRAM0[EM_CALI_CUR_SET_CH6] = 0;NVRAM0[EM_CALI_CUR_SET_CH7] = 0;
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
			NVRAM0[SPREG_DAC_4] = 0;NVRAM0[SPREG_DAC_5] = 0;NVRAM0[SPREG_DAC_6] = 0;NVRAM0[SPREG_DAC_7] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();UPDAC4();UPDAC5();UPDAC6();UPDAC7();

      SET_RAIM_SHDN_ON;
			NVRAM0[SPREG_DAC_16] = (NVRAM0[DM_RAIM_BRG] * deviceConfig.redAimGain) + deviceConfig.redOffset;
			UPDAC16();
			
			updateDiagnosisCali();//先刷新校准页控件(指令带screen id,可预刷新)
			SetScreen(NVRAM0[EM_DC_PAGE]);//再切页,避免控件残留
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
			SET_SAFE_RESET_OFF;
			SET_LASER_CH0_OFF;SET_LASER_CH1_OFF;SET_LASER_CH2_OFF;SET_LASER_CH3_OFF;
			SET_LASER_CH4_OFF;SET_LASER_CH5_OFF;SET_LASER_CH6_OFF;SET_LASER_CH7_OFF;
			NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;//关闭激光
			NVRAM0[SPREG_DAC_4] = 0;NVRAM0[SPREG_DAC_5] = 0;NVRAM0[SPREG_DAC_6] = 0;NVRAM0[SPREG_DAC_7] = 0;
			UPDAC0();UPDAC1();UPDAC2();UPDAC3();UPDAC4();
			UPDAC4();UPDAC5();UPDAC6();UPDAC6();UPDAC7();
			NVRAM0[SPREG_DAC_16] = 0;NVRAM0[SPREG_DAC_17] = 0;
			UPDAC16();UPDAC17();
			SET_RAIM_SHDN_OFF;
			SET_GAIM_SHDN_OFF;
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH0, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH1, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH2, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH3, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH4, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH5, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH6, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH7, false);
      RRES(R_LASER_FALG_EMITING);
      NVRAM0[EM_HMI_OPERA_STEP] = FSMSTEP_DIAGNOSIS;
			NVRAM0[EM_DC_PAGE] = GDDC_PAGE_DIAGNOSIS;
			SetScreen(NVRAM0[EM_DC_PAGE]);	
			RRES(R_DIAGNOSIS_CORRECTION_RETURN_DOWN);
			return;
		}
		if(GET_LASER_CH0 || GET_LASER_CH1 || GET_LASER_CH2 || GET_LASER_CH3 || GET_LASER_CH4 || GET_LASER_CH5 || GET_LASER_CH6 || GET_LASER_CH7){
      SSET(R_LASER_FALG_EMITING);
		}
		else{
      RRES(R_LASER_FALG_EMITING);
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
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH0, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH1, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH2, false);	
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH3, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH4, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH5, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH6, false);
			SetButtonValue(GDDC_PAGE_DIAGNOSIS_CALI, GDDC_PAGE_DIAGNOSIS_CALI_KEY_LAS_PWM_CH7, false);
			SET_RAIM_SHDN_OFF;
			SET_GAIM_SHDN_OFF;			
		}
		if(LDP(SPCOIL_PS200MS)){
			updateDiagnosisCaliInfo();
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_POWEROFF_CONFIRM){//关机确认
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_LIST_TREATMENT){//显示编辑导入导出EPROM储存的病历
		if(LD(R_ENGINEER_MODE)){//工程模式显示调试信息
			if(LDP(SPCOIL_PS1000MS)){
				updateDebugInfo();
			}
		}
		return;
	}
	if(NVRAM0[EM_HMI_OPERA_STEP] == FSMSTEP_EDIT_TREATMENT){//编辑选择的病历
		if(LD(R_ENGINEER_MODE)){//工程模式显示调试信息
			if(LDP(SPCOIL_PS1000MS)){
				updateDebugInfo();
			}
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
        // [分支范围说明 - run_treatment] 握手通知当前为空处理。
        // 已知遗留: 缺少主动握手检测, 断链时需等待约 5 秒握手超时; 修复在 master
        // 提交 b8478dc2(queue_detect_handshake), 经确认本分支暂不修复, 勿在此改动。
        //NOTIFYHandShake();
        break;
    default:
        break;
    }
}


static void NotifyScreen(uint16_t screen_id){
	//页面切换完成通知(屏幕主动上报,MSG_GET_CURRENT_SCREEN): 页面加载完成后重新下发该页全部显示值,
	//修复"SetScreen 后立即大批量刷新"在页面冷加载窗口丢帧导致首次进入个别控件不显示(如待机页650指示功率文本)
	//切页安全解锁: 新页面与在途按键所在页不同(原页面被切走, 其按键无法正常复位), 强制解除互锁防止新页面永久锁死;
	//同一页面的加载通知不解锁, 避免在途动作期间被误放行
	if((g_btnLockActive != 0U) && (g_btnLockScreen != screen_id)){
		treatmentBtnLockReset();
	}
	switch(screen_id){
		case GDDC_PAGE_STANDBY_DUAL_1470_635:
		case GDDC_PAGE_STANDBY_DUAL_1940_635:
		case GDDC_PAGE_STANDBY_DUAL_450_980:
		case GDDC_PAGE_STANDBY_TRI_1470_980_635:
		case GDDC_PAGE_STANDBY_TRI_1940_1470_635:{
			updateStandbyDisplay();
			break;
		}
		case GDDC_PAGE_READY:{
			updateReadyDisplay();
			break;
		}
		case GDDC_PAGE_OPTION:{
			updateOptionDisplay();
			break;
		}
		case GDDC_PAGE_INFORMATION:{
			updateInformationDisplay();
			break;
		}
		case GDDC_PAGE_DIAGNOSIS:{
			updateDiagnosis();
			break;
		}
		case GDDC_PAGE_DIAGNOSIS_RAW:{
			updateDiagnosisInfoRaw();
			break;
		}
		case GDDC_PAGE_DIAGNOSIS_CALI:{
			updateDiagnosisCali();
			break;
		}
		case GDDC_PAGE_LIST_TREATMENT:{
			if(LD(R_ENGINEER_MODE)){//工程模式:页面加载完成立即刷新一次,不等下一个1秒节拍
				updateDebugInfo();
			}
			break;
		}
    case GDDC_PAGE_EDIT_PATIENT:
    case GDDC_PAGE_REGISTER_PATIENT:{
      //患者注册/编辑页无调试控件, 页面加载不做调试刷新
      break;
    }
    case GDDC_PAGE_LIST_RECORD:{
      //历史治疗记录页冷加载: 重新枚举并下发姓名行/记录槽/页码(空槽隐藏)
      listTreatmentRecordEnumerate();
      refreshListRecordDisplay();
      break;
    }
    case GDDC_PAGE_DELETE_RECORD:{
      //单条删除确认页内容在进入时已下发, 冷加载无需额外刷新
      break;
    }
		case GDDC_PAGE_OPERATOR_USB:{
			refreshOperatorUsbDisplay();//页面冷加载完成后再下发一次摘要与U盘状态
			break;
		}
		default:break;
	}
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
  if(state == 0U){
    return;
  }
  //三页性别菜单选项顺序均为"FeMale;Male": 索引0=女(FEMALE), 1=男(MALE)
  if(((screen_id == GDDC_PAGE_EDIT_PATIENT) || (screen_id == GDDC_PAGE_REGISTER_PATIENT))
     && (control_id == GDDC_PAGE_EDIT_PATIENT_MENU_GENDER)){
    treatmentLog.gender = (item == 1U) ? MALE : FEMALE;
  }
  else if((screen_id == GDDC_PAGE_VERIFY_TREATMENT)
          && (control_id == GDDC_PAGE_VERIFY_TREATMENT_MENU_GENDER)){
    treatmentLog.gender = (item == 1U) ? MALE : FEMALE;
  }
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



