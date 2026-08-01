#include "bootLoader.h"
/*****************************************************************************/
//SECTOR0->16K:BOOTLOADER
//SECTOR1->16K:BOOTLOADER
//SECTOR2->16K:BOOTLOADER
//SECTOR3->16K:BOOTLOADER
/*****************************************************************************/
#pragma import(__use_no_semihosting_swi)
/*****************************************************************************/
#define BT_STATE_IDLE														0//空闲
#define BT_STATE_LOAD_FWINFO										1//EPROM载入固件信息
#define BT_STATE_USBHOST_INIT										2//FATFS 初始化
#define BT_STATE_WAIT_UDISK											3//等待USB DISK就绪
#define BT_STATE_READ_CFG												4//读取配置文件
#define BT_STATE_UPDATE_MCU_BOT									5//更新BOOTLOAD
#define BT_STATE_UPDATE_MCU_APP									6//更新单片机应用固件
#define BT_STATE_UPDATE_LCD_APP									7//更新屏幕应用固件
#define BT_STATE_UPDATE_BOTH_APP								8//更新单片机和屏固件
#define BT_STATE_UPDATE_EPROM										9//更新UDISK->EPROM
#define BT_STATE_UPDATE_FORCE_BOTH_APP					10//强制更新
#define BT_STATE_DUMP_EPROM											11//储存全部EPROM到UDISK
#define BT_STATE_CLEAT_ALL											12//清除FLASH和EPROM全部
#define BT_STATE_RESET													90//重启
#define BT_STATE_RUN_APP												99//跳转到APP应用程序

#define BT_FAIL_READ_CFG												'0'//从U盘读取CFG失败
#define BT_FAIL_READ_LMCU_APP										'1'//从U盘读取MCU APP失败
#define BT_FAIL_READ_LCD_APP										'2'//从U盘读取LCD APP失败
#define BT_FAIL_READ_EPROM_BIN									'3'//从U盘读取EPROM BIN失败
#define BT_FAIL_WRITE_EPROM_BIN									'4'//向U盘写入EPROM BIN失败
#define BT_FAIL_ERASE_MCU_APP										'5'//擦除FLASH失败
#define BT_FAIL_READ_EPROM											'6'//读取EPROM失败
#define BT_FAIL_WRITE_EPROM											'7'//写入EPROM失败
#define BT_FAIL_LMCU_APP_CHECK									'8'//ld_mcu.bin CRC检查错误
#define BT_FAIL_LMCU_BOT_CHECK									'9'//ld_bot.bin CRC检查错误
#define BT_FAIL_LCD_APP_CHECK										'A'//ld_lcd.bin CRC检查错误
#define BT_FAIL_CHECKSUM_MCU_APP_FLASH					'B'//校验 mcu app 错误
#define BT_FAIL_WRITE_MCU_APP_FLASH							'C'//写mcu app flash错误
#define BT_FAIL_LCD_NOT_RESPOND									'D'//LCD串口通信超时或错误
#define BT_FAIL_LCD_DOWNLOAD										'E'//LCD下载失败
#define BT_FAIL_VECTOR_TABLE_INVALID						'F'//APP 向量表错误
#define BT_FAIL_CHECK_BLANK											'G'//FLASH查空错误
#define BT_DONE_CLEAR_ALL												'H'//FLASH和EPROM清除完成
#define BT_DONE_UPDATE_EPROM										'I'//更新EPROM完成
#define BT_DONE_DUMP_EPROM											'J'//下载EPROM完成
#define BT_FAIL_LCD_RESPOND_ERROR								'K'//LCD 响应错误

#define BT_DONE_FIRMWARE_UPDATE									'L'//
/*****************************************************************************/
#define GDDC_RX_BUF_SIZE												128
#define GDDC_TX_BUF_SIZE												(2048 + 4)
#define GDDC_HEX 																0
#define GDDC_DEC 																1 
#define GDDC_CHR 																2
#define GDDC_RX_TIMEOUT													0xFFFF
#define GDDC_TX_TIMEOUT													0xFFFF
#define GDDC_RETRY_TIMES												10//发送重试次数
/*****************************************************************************/
uint32_t crcEpromMcu, crcEpromLcd;//EPROM中储存的CRC记录值
uint32_t TmpReadSize = 0x00;
uint32_t RamAddress = 0x00;
static __IO uint32_t LastPGAddress = APPLICATION_FLASH_START_ADDRESS;
uint8_t RAM_Buf[BUFFER_SIZE] = {0x00};//文件读写缓冲
/*****************************************************************************/
const char BootLoadMainVer __attribute__((at(BOOTLOAD_MAIN_ADDRESS)))   		= '2';
const char BootLoadMinorVer __attribute__((at(BOOTLAOD_MINOR_ADDRESS)))  		= '2';
/*****************************************************************************/
uint8_t cmdShakeHandOp[] = {0xEE,0x04,0xFF,0xFC,0xFF,0xFF};
uint8_t cmdShakeHandRespondOp[] = {0xEE,0x55,0xFF,0xFC,0xFF,0xFF};
	//复位大彩指令集
uint8_t cmdResetOp[] = {0x61,0x78,0x72,0x63, 0x65,0x6b,0x67,0x64, 0x79,0x68,0x74,0x73, 0x75,0x6e,0x71,0x77, 0x70,0x6a,0x62,0x76, 0x69,0x66,0x6f,0x6d, 0x7a,0x6c};
	//格式化文件系统
uint8_t cmdFormatOp[] = {0xee,0xab,0xba,0xaa,0xbb,0x36,0x3f,0xff,0xfc,0xff,0xff};         
uint8_t cmdResetHmiOp[] = {0xEE,0x07,0x35,0x5A,0x53,0xA5,0xFF,0xFC,0xFF,0xFF};
uint8_t gddcRxBuf[GDDC_RX_BUF_SIZE];//屏幕串口接收缓冲区
uint8_t gddcTxBuf[GDDC_TX_BUF_SIZE];//屏幕串口发送缓冲区
uint16_t gddcRxIndex, gddcTxIndex;//发送接收指针
/*****************************************************************************/
FRESULT retUsbH;
FATFS	USBH_fatfs;
FIL LogFile;//FATFS File Object 记录信息
FIL CfgFile;//FATFS File Object 下载完成信息
FIL McuFile;//FATFS File Object 单片机固件
FIL LcdFile;//FATFS File Object 屏幕固件
FIL BotFile;//FATFS File Object BOOTLOAD固件
FIL SepromFile;//FATFS File Object EPROM->UDISK
FIL LepromFile;//FATFS File Object UDISK->EPROM
DIR	FileDir;//FATFS 文件目录
FILINFO FileInfo;//FATFS 文件信息
/*****************************************************************************/
static uint8_t bootLoadState;
static uint8_t forceUpdateMcu, forceUpdateLcd;
static uint32_t crcFlash, crcUdisk;
int32_t releaseTime0, releaseTime1, overTime, releaseCounter;
uint32_t JumpAddress;
pFunction Jump_To_Application;
/*****************************************************************************/
void resetInit(void);
static void bootLoadFailHandler(uint8_t ftype);//引导故障程序
static void prepareUpdateLcd(void);//LCD远程升级准备
static uint32_t getOriginAppCrc(void);
static uint32_t getNewMcuAppCrc(void);
static uint32_t getNewLcdAppCrc(char* filePath);//获取文件校验码　CRC32
static uint32_t updateMcuApp(void);
static uint32_t updateLcdApp(char* filePath);//更新LCD APP
static void DBGU_Printk_num(uint8_t *buffer, uint16_t datanum);
static void dp_display_text_num(uint8_t *text,uint16_t datanum);	
static void clearFlash(void);
static uint8_t cmpByte(uint8_t *psrc, uint8_t *pdist, uint16_t len);
static FRESULT crcLcdFile(char* scanPath);
static FRESULT updateLcdFile(char* scanPath);
/******************************************************************************/
static uint8_t cmpByte(uint8_t *psrc, uint8_t *pdist, uint16_t len){
	uint16_t i;
	for(i = 0;i < len;i ++){
		if(*(psrc + i) != *(pdist + i)){
			return false;
		}
	}
	return true;
}

void bootLoadInit(void){//引导程序初始化
	forceUpdateMcu = 0;
	forceUpdateLcd = 0;
	SET_SPK_AP_OFF;//关闭蜂鸣器
	printf("Bootloader:OUTPUT->SKP_EN       = LOW\n");
	//关闭指示激光
	SET_RAIM_TIM_OFF;
	SET_GAIM_TIM_OFF;//关闭指示激光
	printf("Bootloader:OUTPUT->AIM_PWM      = LOW\n");
	SET_FAN0_OFF;//打开激光器冷却风扇
	SET_FAN1_OFF;//打开激光器冷却风扇
	SET_FAN2_OFF;//打开激光器冷却风扇
	printf("Bootloader:OUTPUT->AIM_PWM      = LOW\n");

	printf("Bootloader:OUTPUT->LAS_FAN      = LOW\n");
	SET_TEC_CH0_OFF;//关闭制冷
	SET_TEC_CH1_OFF;//关闭制冷
	SET_TEC_CH2_OFF;//关闭制冷
	SET_TEC_CH3_OFF;//关闭制冷
	SET_TEC_CH4_OFF;//关闭制冷
	SET_TEC_CH5_OFF;//关闭制冷
	SET_TEC_CH6_OFF;//关闭制冷
	SET_TEC_CH7_OFF;//关闭制冷
	SET_TEC_GATE_CH0_OFF;
	SET_TEC_GATE_CH1_OFF;
	printf("Bootloader:OUTPUT->LAS_TEC      = LOW\n");
	//关闭所有激光
	SET_RED_LED_DC(50);										
	SET_GREEN_LED_DC(50);										
	SET_BLUE_LED_DC(50);										
	
	SET_LASER_CH0_OFF;
	SET_LASER_CH1_OFF;
	SET_LASER_CH2_OFF;
	SET_LASER_CH3_OFF;
	SET_LASER_CH4_OFF;
	SET_LASER_CH5_OFF;
	SET_LASER_CH6_OFF;
	SET_LASER_CH7_OFF;
	//关闭所有LED
	SET_RED_LED_OFF;
	SET_GREEN_LED_OFF;
	SET_BLUE_LED_OFF;
	SET_TICK_LED_OFF;
	SET_ERR_LED_OFF;
	//R-G-Y流水
	//R
	SET_RED_LED_ON;
	SET_GREEN_LED_OFF;
	SET_BLUE_LED_OFF;
	HAL_Delay(500);
	//G
	SET_RED_LED_OFF;
	SET_GREEN_LED_ON;
	SET_BLUE_LED_OFF;
	HAL_Delay(500);
	//B
	SET_RED_LED_OFF;
	SET_GREEN_LED_OFF;
	SET_BLUE_LED_ON;
	HAL_Delay(500);
	//G
	SET_RED_LED_OFF;
	SET_GREEN_LED_ON;
	SET_BLUE_LED_OFF;
	releaseTime0 = 0;
	releaseTime1 = 0;
	bootLoadState = BT_STATE_IDLE; 
	printf("\r\n");
	//显示输入IO状态
	if(GET_ESTOP_NC == GPIO_PIN_SET){//TTL=H
		printf("Bootloader:INPUT->ESTOP_NC      = HIGH\n");
	}
	else{//TTL=L
		printf("Bootloader:INPUT->ESTOP_NC      = LOW\n");
	}

	if(GET_FSWITCH_NC == GPIO_PIN_SET){//TTL=H
		printf("Bootloader:INPUT->FSWITCH_NC    = HIGH\n");
	}
	else{//TTL=L
		printf("Bootloader:INPUT->FSWITCH_NC    = LOW\n");
	}
	if(GET_FSWITCH_NO == GPIO_PIN_SET){//TTL=H
		printf("Bootloader:INPUT->FSWITCH_NO    = HIGH\n");
	}
	else{//TTL=L
		printf("Bootloader:INPUT->FSWITCH_NO    = LOW\n");
	}
	if(GET_INTERLOCK_NC == GPIO_PIN_SET){//TTL=H
		printf("Bootloader:INPUT->INTERLOCK     = HIGH\n");
	}
	else{
		printf("Bootloader:INPUT->INTERLOCK     = LOW\n");
	}	
	HAL_Delay(10);
	
}
void bootLoadProcess(void){//bootload 执行程序
	HAL_StatusTypeDef ret;
	uint8_t fileBuff[256];
	uint32_t brByte;//实际读取的字节数
	crcFlash = 0;
	crcUdisk = 0;
	switch(bootLoadState){
		case BT_STATE_IDLE:{//开机等待U盘识别
			//关闭激光
			SET_LASER_CH0_OFF;
			SET_LASER_CH1_OFF;
			SET_LASER_CH2_OFF;
			SET_LASER_CH3_OFF;
			SET_LASER_CH4_OFF;
			SET_LASER_CH5_OFF;
			SET_LASER_CH6_OFF;
			SET_LASER_CH7_OFF;
			//关闭TEC
			SET_TEC_CH0_OFF;
			SET_TEC_CH1_OFF;
			SET_TEC_CH2_OFF;
			SET_TEC_CH3_OFF;
			SET_TEC_CH4_OFF;
			SET_TEC_CH5_OFF;
			SET_TEC_CH6_OFF;
			SET_TEC_CH7_OFF;
			
			SET_GAIM_TIM_OFF;
			SET_RAIM_TIM_OFF;
			SET_FAN0_OFF;
			SET_FAN1_OFF;
			SET_FAN2_OFF;			
			SET_RED_LED_OFF;
			SET_GREEN_LED_OFF;
			SET_BLUE_LED_OFF;
             
			printf("\n\n\n\n");
			printf("Bootloader:Start...............\n");
			listEpromTable();
			crcEpromMcu = 0xFFFFFFFF;
			ret = epromReadDword(CONFIG_EPROM_MCU_FW_CRC, &crcEpromMcu);//从EPROM载入设备配置
			if(ret == HAL_OK){
				printf("Bootloader:Read eprom MCU FW CRC32:0x%08X\n", crcEpromMcu);
			}
			else{
				printf("Bootloader:Read eprom MCU FW CRC32 fail!\n");
			}
			crcEpromLcd = 0xFFFFFFFF;
			ret = epromReadDword(CONFIG_EPROM_LCD_FW_CRC, &crcEpromLcd);//从EPROM载入设备配置
			if(ret == HAL_OK){
				printf("Bootloader:Read eprom LCD FW CRC32:0x%08X\n", crcEpromLcd);
			}
			else{
				printf("Bootloader:Read eprom LCD FW CRC32 fail!\n");
			}
			printf("Bootloader:Version->%c.%c\n", BootLoadMainVer, BootLoadMinorVer);	
			printf("Bootloader:Build->%s:%s\n", __DATE__, __TIME__);
			printf("Bootloader:Bootload Start  :0x%08X,End:0x%08X,Size:0x%08X\n", BOOTLOADER_FLASH_START_ADDRESS, BOOTLOADER_FLASH_END_ADDRESS ,BOOTLOADER_FLASH_SIZE);
			printf("Bootloader:Applicent Start :0x%08X,End:0x%08X,Size:0x%08X\n", APPLICATION_FLASH_START_ADDRESS, APPLICATION_FLASH_END_ADDRESS, APPLICATION_FLASH_SIZE);
				
			if((GET_ESTOP_NC == GPIO_PIN_SET) &&//安全连锁未插入
				(GET_FSWITCH_NC == GPIO_PIN_SET) &&//脚踏插入
				(GET_FSWITCH_NO == GPIO_PIN_RESET)){//脚踏踩下					
          bootLoadState = BT_STATE_USBHOST_INIT;//进入USB更新APP流程
          break;
      }
    }
		case BT_STATE_USBHOST_INIT:{//在USB HOST上挂载FATFS
			retUsbH = f_mount(&USBH_fatfs, FATFS_ROOT, 0);
			if(retUsbH != FR_OK){//挂载U盘失败
				printf("Bootloader:Mount Fatfs errror:%d!\n", retUsbH);
				bootLoadState = BT_STATE_RUN_APP;//跳转到APP
			}
			else{//挂载U盘成功
				printf("Bootloader:Mount Fatfs sucess!\n");
				bootLoadState = BT_STATE_WAIT_UDISK;
				overTime = HAL_GetTick() + CONFIG_JUMP_DELAY;
			}
			break;
		}
		case BT_STATE_WAIT_UDISK:{//等待USB DISK就绪
			//显示倒计时
			releaseTime0 = (overTime - (int32_t)HAL_GetTick()) / 1000;
			if(releaseTime0 != releaseTime1){
				printf("Bootloader:Wait usb disk init:%d Second!\n", releaseTime0);
				releaseTime1 = releaseTime0;
			} 
			if(releaseTime0 <= 1){
				bootLoadState = BT_STATE_READ_CFG;
			}
			break;
		}
		case BT_STATE_READ_CFG:{
			//检查U盘是否存在Flash Down文件
			SET_RED_LED_ON;
			retUsbH = f_open(&CfgFile, CFG_FIRMWARE_FILENAME, FA_OPEN_EXISTING | FA_READ);//读取完成信息文件
			SET_RED_LED_OFF;
			if(retUsbH != FR_OK){//读取失败跳过固件更新直接运行程序
				printf("BootLoader:Open %s fail,ECODE=0x%02XH\n", CFG_FIRMWARE_FILENAME, retUsbH);
				bootLoadState = BT_STATE_RUN_APP;//跳转到更新MCU APP固件
			}
			else{//读取成功检查文件内容
				printf("BootLoader:Open %s sucess,ECODE=0x%02XH\n", CFG_FIRMWARE_FILENAME, retUsbH);
				f_lseek(&CfgFile, 0);//读取指针移动到开头
				SET_RED_LED_ON;
				retUsbH = f_read(&CfgFile, fileBuff, 5, &brByte);
				SET_RED_LED_OFF;
				if((retUsbH != FR_OK) || (brByte < 5)){//读取文件开头4个字节
					bootLoadFailHandler(BT_FAIL_READ_CFG);//读取CFG错误
				}
				if(fileBuff[0] == 'U' && fileBuff[1] == '0' && fileBuff[2] == '1'){//U01 更新 MCU应用
					if(fileBuff[3] == DEVID_L && fileBuff[4] == DEVID_H){//设备匹配
						printf("Bootloader:Start upgrade mcu application!\n");
						bootLoadState = BT_STATE_UPDATE_MCU_APP;
					}
					else{
						bootLoadState = BT_STATE_RUN_APP;
					}
				}
				else if(fileBuff[0] == 'U' && fileBuff[1] == '0' && fileBuff[2] == '2'){//U02 更新 触摸屏
					if(fileBuff[3] == DEVID_L && fileBuff[4] == DEVID_H){//设备匹配
						printf("Bootloader:Start upgrade lcd application!\n");
						bootLoadState = BT_STATE_UPDATE_LCD_APP;
					}
					else{
						bootLoadState = BT_STATE_RUN_APP;
					}
				}
				else if(fileBuff[0] == 'U' && fileBuff[1] == '0' && fileBuff[2] == '3'){//U03 更新 应用&触摸屏
					if(fileBuff[3] == DEVID_L && fileBuff[4] == DEVID_H){//设备匹配				
						printf("Bootloader:Start upgrade mcu application & lcd application!\n");
						bootLoadState = BT_STATE_UPDATE_BOTH_APP;
					}
					else{
						printf("Bootloader:Device ID is not mate,run app!\n");
						bootLoadState = BT_STATE_RUN_APP;
					}
				}
				else if(fileBuff[0] == 'U' && fileBuff[1] == '0' && fileBuff[2] == '4'){//U04 更新 EPROM
					if(fileBuff[3] == DEVID_L && fileBuff[4] == DEVID_H){//设备匹配
						printf("Bootloader:Start update eprom!\n");
						bootLoadState = BT_STATE_UPDATE_EPROM;
					}
					else{
						printf("Bootloader:Device ID is not mate,run app!\n");
						bootLoadState = BT_STATE_RUN_APP;
					}
				}	
				else if(fileBuff[0] == 'U' && fileBuff[1] == '0' && fileBuff[2] == '5'){//U05 强制更新MCU
					if(fileBuff[3] == DEVID_L && fileBuff[4] == DEVID_H){//设备匹配
						printf("Bootloader:Start force update mcu!\n");
						forceUpdateMcu = 1;
						bootLoadState = BT_STATE_UPDATE_MCU_APP;
					}
					else{
						printf("Bootloader:Device ID is not mate,run app!\n");
						bootLoadState = BT_STATE_RUN_APP;
					}
				}
				
				else if(fileBuff[0] == 'U' && fileBuff[1] == '0' && fileBuff[2] == '6'){//U06 强制更新LCD
					if(fileBuff[3] == DEVID_L && fileBuff[4] == DEVID_H){//设备匹配
						printf("Bootloader:Start force update lcd!\n");
						forceUpdateLcd = 1;
						bootLoadState = BT_STATE_UPDATE_LCD_APP;
					}
					else{
						printf("Bootloader:Device ID is not mate,run app!\n");
						bootLoadState = BT_STATE_RUN_APP;
					}
				}

				else if(fileBuff[0] == 'U' && fileBuff[1] == '0' && fileBuff[2] == '7'){//U07 强制更新MCU & LCD
					if(fileBuff[3] == DEVID_L && fileBuff[4] == DEVID_H){//设备匹配
						printf("Bootloader:Start force update mcu & lcd!\n");
						forceUpdateMcu = 1;
						forceUpdateLcd = 1;
						bootLoadState = BT_STATE_UPDATE_BOTH_APP;
					}
					else{
						printf("Bootloader:Device ID is not mate,run app!\n");
						bootLoadState = BT_STATE_RUN_APP;
					}
				}
				else if(fileBuff[0] == 'D' && fileBuff[1] == '0' && fileBuff[2] == '1'){//D1 读取EPROM
					if(fileBuff[3] == DEVID_L && fileBuff[4] == DEVID_H){//设备匹配
						printf("Bootloader:Start dump eprom to udisk!\n");
						bootLoadState = BT_STATE_DUMP_EPROM;
					}
					else{
						printf("Bootloader:Device ID is not mate,run app!\n");
						bootLoadState = BT_STATE_RUN_APP;
					}
				}
				else if(fileBuff[0] == 'C' && fileBuff[1] == '0' && fileBuff[2] == '1'){//U01 清除所有
					if(fileBuff[3] == DEVID_L && fileBuff[4] == DEVID_H){//设备匹配
						printf("Bootloader:Start clear flash and eprom!\n");
						bootLoadState = BT_STATE_CLEAT_ALL;
					}
					else{
						printf("Bootloader:Device ID is not mate,run app!\n");
						bootLoadState = BT_STATE_RUN_APP;
					}
				}
				else{//其它无需更新跳转到执行APP
					bootLoadState = BT_STATE_RUN_APP;
				}
				f_close(&CfgFile);
			}
			break;
		}
		case BT_STATE_UPDATE_MCU_APP:{//更新ld_mcu.bin
			crcFlash = getOriginAppCrc();//计算FLASH中APP固件CRC32
			crcUdisk = getNewMcuAppCrc();//计算U盘中MCU APP固件CRC32
			printf("Bootloader:MCU crcFlash:%08XH,crcUdisk:%08XH!\n", crcFlash, crcUdisk);
			if((crcUdisk == crcEpromMcu) && (crcFlash == crcEpromMcu) && (forceUpdateMcu == 0)){//校验码相同跳过更新
				printf("Bootloader:Check mcu app crc same,skip!\n");
				bootLoadState = BT_STATE_RUN_APP;
				break;
			}
			crcUdisk = updateMcuApp();//写入UDISK FILE
			crcFlash = getOriginAppCrc();//校验MCU FLASH
			crcEpromMcu = crcFlash;//CRC值写入EPROM
			if(crcUdisk != crcFlash){
				bootLoadFailHandler(BT_FAIL_CHECKSUM_MCU_APP_FLASH);
			}
			else{
				printf("Bootloader:Checksum mcu app sucess.\n");
				clearEprom(CLEAR_EPROM_NVRAM);//清除NVRAM掉电储存区
				clearEprom(CLEAR_EPROM_MCU_FIRMWARE_CRC);
				epromWriteDword(CONFIG_EPROM_MCU_FW_CRC, &crcEpromMcu);
				printf("Bootloader:Update new crc32 sucess,0x08%XH\n", crcFlash);
			}
			bootLoadState = BT_STATE_RESET;//更新APP
			break;
		}
		case BT_STATE_UPDATE_LCD_APP:{//更新LCD应用程序			
			crcUdisk = 0;
			strcpy((char*)fileBuff, "/private");
			crcLcdFile((char*)fileBuff);//扫描文件
			printf("Bootloader:LCD crcLcd:%08XH,crcUdisk:%08XH!\n", crcEpromLcd, crcUdisk);
			if((crcUdisk == crcEpromLcd) && (forceUpdateLcd == 0)){//校验码相同跳过更新
				printf("Bootloader:Check lcd app crc same,skip!\n");
				bootLoadState = BT_STATE_RUN_APP;
				break;
			}
			prepareUpdateLcd();//LCD远程升级准备
			
			crcUdisk = 0;
			strcpy((char*)fileBuff, "/private");
			updateLcdFile((char*)fileBuff);
			
			crcEpromLcd = crcUdisk;//更新EPROM中LCD APP CRC值
			clearEprom(CLEAR_EPROM_LCD_FIRMWARE_CRC);
			epromWriteDword(CONFIG_EPROM_LCD_FW_CRC, &crcEpromLcd);
			printf("Bootloader:Update lcd app new crc32 sucess,wait 60s lcd upgrade done\n");
			//等待60秒 LCD FLASH写入完成后重启
			//重启HMI
			dp_display_text_num(cmdResetHmiOp, strlen((char*)cmdResetHmiOp));	
			HAL_Delay(5000);HAL_Delay(5000);HAL_Delay(5000);HAL_Delay(5000);HAL_Delay(5000);
			bootLoadState = BT_STATE_RESET;//更新APP
			break;
		}
		case BT_STATE_UPDATE_BOTH_APP:{//更新全部应用程序
			//MCU 更新
			crcFlash = getOriginAppCrc();//计算FLASH中APP固件CRC32
			crcUdisk = getNewMcuAppCrc();//计算U盘中MCU APP固件CRC32
			printf("Bootloader:MCU crcFlash:%08XH,crcUdisk:%08XH,crcEprom:%08XH\n", crcFlash, crcUdisk, crcEpromMcu);
			if((crcUdisk == crcEpromMcu) && (crcFlash == crcEpromMcu) && (forceUpdateMcu == 0)){//校验码相同跳过更新
				printf("Bootloader:Check mcu app crc same,skip!\n");
			}
			else{//从U盘更新固件
				crcUdisk = updateMcuApp();	
				crcFlash = getOriginAppCrc();//校验MCU FLASH
				if(crcUdisk != crcFlash){
					bootLoadFailHandler(BT_FAIL_CHECKSUM_MCU_APP_FLASH);
				}
				crcEpromMcu = crcFlash;//CRC值写入EPROM
				printf("Bootloader:Check mcu app sucess.\n");
				clearEprom(CLEAR_EPROM_NVRAM);
				clearEprom(CLEAR_EPROM_MCU_FIRMWARE_CRC);
				epromWriteDword(CONFIG_EPROM_MCU_FW_CRC, &crcEpromMcu);
				printf("Bootloader:Update mcu app new crc32 sucess.\n");
			}
			
			//LCD 更新
			crcUdisk = 0;
			strcpy((char*)fileBuff, "/private");
			crcLcdFile((char*)fileBuff);//扫描文件
			printf("Bootloader:LCD crcLcd:%08XH,crcUdisk:%08XH!\n", crcEpromLcd, crcUdisk);
			if(crcUdisk == crcEpromLcd && (forceUpdateLcd == 0)){//校验码相同跳过更新
				printf("Bootloader:Check lcd app crc same,skip!\n");
				bootLoadState = BT_STATE_RUN_APP;
				break;
			}
			prepareUpdateLcd();//LCD远程升级准备
			
			crcUdisk = 0;
			strcpy((char*)fileBuff, "/private");
			updateLcdFile((char*)fileBuff);
			
			crcEpromLcd = crcUdisk;//更新EPROM中LCD APP CRC值
			clearEprom(CLEAR_EPROM_LCD_FIRMWARE_CRC);
			epromWriteDword(CONFIG_EPROM_LCD_FW_CRC, &crcEpromLcd);
			printf("Bootloader:Update lcd app new crc32 sucess,wait 60s lcd upgrade done\n");
			//等待60秒 LCD FLASH写入完成后重启
			//重启HMI
			dp_display_text_num(cmdResetHmiOp, strlen((char*)cmdResetHmiOp));	
			HAL_Delay(5000);HAL_Delay(5000);HAL_Delay(5000);HAL_Delay(5000);HAL_Delay(5000);
			bootLoadState = BT_STATE_RESET;//更新APP
			break;
		}		
		case BT_STATE_UPDATE_EPROM:{//更新EPROM
			break;
		}
		case BT_STATE_DUMP_EPROM:{
			break;
		}
		case BT_STATE_CLEAT_ALL:{//清除FLASH和EPROM全部
			clearFlash();
			clearEprom(CLEAR_EPROM_ALL);
			bootLoadFailHandler(BT_DONE_CLEAR_ALL);
			break;
		}
		case BT_STATE_RESET:{//复位
			printf("Bootloader:System Reset\n");
			__set_FAULTMASK(1);
			NVIC_SystemReset();/* Software reset */
			break;
		}
		case BT_STATE_RUN_APP:{//运行应用程序
			HAL_FLASH_Lock();//锁定FLASH
			/* Check Vector Table: Test if user code is programmed starting from* address "APPLICATION_ADDRESS" */
			if((((*(__IO uint32_t *) APPLICATION_FLASH_START_ADDRESS) & 0xFF000000) == 0x20000000) || (((*(__IO uint32_t *) APPLICATION_FLASH_START_ADDRESS) & 0xFF000000) == 0x10000000)){
				/* Jump to user application */
				printf("Bootloader:Jump application address.\n");
				JumpAddress = *(__IO uint32_t *) (APPLICATION_FLASH_START_ADDRESS + 4);
				printf("Bootloader:Jump Address:0x%X\n", JumpAddress);
				Jump_To_Application = (pFunction) JumpAddress;
				/* Initialize user application's Stack Pointer */
				__set_MSP(*(__IO uint32_t *) APPLICATION_FLASH_START_ADDRESS);
				printf("Bootloader:Stack Pointer:0x%X\n", *(__IO uint32_t *) APPLICATION_FLASH_START_ADDRESS);
				printf("\n\n\n\r\r\r");
				SET_RED_LED_OFF;
				SET_GREEN_LED_OFF;
				SET_BLUE_LED_OFF;
				SET_FAN0_OFF;
				SET_FAN1_OFF;
				SET_FAN2_OFF;     
				__disable_irq();
				SysTick->CTRL = 0;//关键代码
				//关闭中断                                    				
				HAL_NVIC_DisableIRQ(SysTick_IRQn); 
				HAL_NVIC_DisableIRQ(OTG_FS_IRQn);
				HAL_NVIC_ClearPendingIRQ(SysTick_IRQn);
				HAL_NVIC_ClearPendingIRQ(OTG_FS_IRQn);
				Jump_To_Application();
			}
			bootLoadFailHandler(BT_FAIL_VECTOR_TABLE_INVALID);
		}
		default:break;
	}
}

static void bootLoadFailHandler(uint8_t ftype){//引导错误程序
	MX_DriverVbusFS(FALSE);//关闭USB VBUS
	printf("Bootloader:SYS_ERR_LED->On!\n");
	SET_RED_LED_ON;
	SET_GREEN_LED_OFF;
	SET_BLUE_LED_OFF;
	switch(ftype){
		case BT_FAIL_READ_CFG:{//从U盘读取CFG失败
			printf("Bootloader:FailHandler,Read config file fail!.\n");
			while(1);
		}
		case BT_FAIL_READ_LMCU_APP:{//从U盘读取MCU APP失败
			printf("Bootloader:FailHandler,Read mcu firmware fail!.\n");
			while(1);
		}
		case BT_FAIL_READ_LCD_APP:{//从U盘读取LCD APP失败
			printf("Bootloader:FailHandler,Read lcd firmware fail!.\n");
			while(1);
		}
		case BT_FAIL_ERASE_MCU_APP:{//擦除MCU APP FLASH区域失败
			printf("Bootloader:FailHandler,Erase mcu application fail\n");
			while(1);
		}
		case BT_FAIL_READ_EPROM_BIN:{
			printf("Bootloader:FailHandler,Read eprom file fail!\n");
			while(1);
		}
		case BT_FAIL_WRITE_EPROM_BIN:{
			printf("Bootloader:FailHandler,Write eprom file fail!\n");
			while(1);
		}
		case BT_FAIL_LMCU_APP_CHECK:{//lmcu.bin 检查错误
			printf("Bootloader:FailHandler,%s size is invalid!\n", LMCU_FIRMWARE_FILENAME);
			while(1);
		}
		case BT_FAIL_LCD_APP_CHECK:{//llcd.bin 检查错误
			printf("Bootloader:FailHandler,%s size is invalid!\n", LLCD_FIRMWARE_FILENAME);
			while(1);
		}
		case BT_FAIL_CHECKSUM_MCU_APP_FLASH:{//校验 lmcu.bin 错误
			printf("Bootloader:FailHandler,Verify %s fail!.\n", LMCU_FIRMWARE_FILENAME);
			while(1);
		}
		case BT_FAIL_LCD_NOT_RESPOND:{//LCD 串口无响应或错误
			printf("Bootloader:FailHandler,LCD is not responsed!.\n");
			while(1);
		}
		case BT_FAIL_LCD_DOWNLOAD:{//LCD 命令无响应
			printf("Bootloader:FailHandler,LCD download fail!.\n");
			while(1);
		}
		case BT_FAIL_VECTOR_TABLE_INVALID:{//APP无效向量表
			printf("Bootloader:FailHandler,App vector table invalid.\n");
			while(1);
		}
		case BT_FAIL_CHECK_BLANK:{//FLASH 查空错误
			printf("Bootloader:FailHandler,Flash is not blank!.\n");
			while(1);
		}
		case BT_DONE_CLEAR_ALL:{
			printf("Bootloader:DoneHandler,Flash and Eprom easer done!.\n");
			while(1);
		}
		case BT_DONE_UPDATE_EPROM:{
			printf("Bootloader:DoneHandler,Update eprom form udisk done!.\n");
			while(1);
		}
		case BT_DONE_DUMP_EPROM:{
			printf("Bootloader:DoneHandler,Dump eprom to udisk done!\n");
			while(1);
		}
    case BT_DONE_FIRMWARE_UPDATE:{
			printf("Bootloader:DoneHandler, Update Firmware done!\n");
			while(1);
		}
		default:{
			printf("Bootloader:DoneHandler,unknown error!\n");
			break;
		}
	}
}
static void clearFlash(void){//清除MCU FLASH
	HAL_FLASH_Unlock();
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGSERR|FLASH_FLAG_WRPERR);
	if (FLASH_If_EraseApplication() != 0x00){//擦除APP FLASH区域失败
		bootLoadFailHandler(BT_FAIL_ERASE_MCU_APP);
	}
	checkBlank(APPLICATION_FLASH_START_ADDRESS, APPLICATION_FLASH_SIZE);//FLASH 查空
}
static uint32_t getNewMcuAppCrc(void){//获取待更新MCU APP CRC32
	uint32_t crc32;
	uint32_t i;
	uint8_t readflag = TRUE;
	uint16_t bytesread;//实际文件读取字节数
	retUsbH = f_open(&McuFile, LMCU_FIRMWARE_FILENAME, FA_OPEN_EXISTING | FA_READ);
	if(retUsbH != FR_OK){//读取失败
		bootLoadFailHandler(BT_FAIL_READ_LMCU_APP);			
	}
	if(f_size(&McuFile) > APPLICATION_FLASH_SIZE){//MCU固件大于FLSAH容量
		bootLoadFailHandler(BT_FAIL_LMCU_APP_CHECK);
	}
	crc32 = 0;
	crc32Clear();
	while(readflag){
		SET_RED_LED_ON;
		/* Read maximum 512 Kbyte from the selected file */
		f_read(&McuFile, RAM_Buf, BUFFER_SIZE, (void*)&bytesread);
		SET_RED_LED_OFF;
		crc32 = crc32Calculate(RAM_Buf, bytesread);
		/* Temp variable */
		TmpReadSize = bytesread;
		/* The read data < "BUFFER_SIZE" Kbyte */
		if(TmpReadSize < BUFFER_SIZE){
			readflag = FALSE;
		}
		LastPGAddress += TmpReadSize;
	}
	for(i = LastPGAddress;i < APPLICATION_FLASH_END_ADDRESS;i ++){//补完剩余CRC
		crc32 = crc32CalculateAdd(0xFF);
	}
	f_close(&McuFile);
	
	return crc32;
}
static uint32_t getNewLcdAppCrc(char* filePath){//获取待更新LCD APP CRC16
	uint32_t crc32;
	uint8_t readflag = TRUE;
	uint16_t bytesread;//实际文件读取字节数
	SET_RED_LED_ON;
	retUsbH = f_open(&LcdFile, filePath, FA_OPEN_EXISTING | FA_READ);
	SET_RED_LED_OFF;
	if(retUsbH != FR_OK){//读取失败
		bootLoadFailHandler(BT_FAIL_READ_LCD_APP);			
	}
	f_lseek(&LcdFile, 0);//读取指针移动到开头
	crc32 = 0;
	crc32Clear();
	while(readflag){
		/* Read maximum 512 Kbyte from the selected file */
		SET_RED_LED_ON;
		f_read(&LcdFile, RAM_Buf, BUFFER_SIZE, (void*)&bytesread);
		SET_RED_LED_OFF;
		crc32 = crc32Calculate(RAM_Buf, bytesread);
		/* Temp variable */
		TmpReadSize = bytesread;
		/* The read data < "BUFFER_SIZE" Kbyte */
		if(TmpReadSize < BUFFER_SIZE){
			readflag = FALSE;
		}
		LastPGAddress += TmpReadSize;
	}
	f_close(&LcdFile);
	return crc32;
}
static uint32_t updateMcuApp(void){//更新MCU APP
	uint32_t crc32;
	uint32_t i;
	uint32_t programcounter = 0x00;
	uint8_t readflag = TRUE;
	uint32_t bytesread;//实际文件读取字节数
	retUsbH = f_open(&McuFile, LMCU_FIRMWARE_FILENAME, FA_OPEN_EXISTING | FA_READ);
	if(retUsbH != FR_OK){//读取失败
		bootLoadFailHandler(BT_FAIL_READ_LMCU_APP);			
	}
	printf("Bootloader:Open %s sucess,ECODE=0x%02XH.\n", LMCU_FIRMWARE_FILENAME, retUsbH);
	if(f_size(&McuFile) > APPLICATION_FLASH_SIZE){//MCU固件大于FLSAH容量
		bootLoadFailHandler(BT_FAIL_LMCU_APP_CHECK);
	}
	HAL_FLASH_Unlock();
	HAL_Delay(1000);
	__HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGSERR|FLASH_FLAG_WRPERR);
	if (FLASH_If_EraseApplication() != 0x00){//擦除APP FLASH区域失败
		bootLoadFailHandler(BT_FAIL_ERASE_MCU_APP);
	}
	HAL_Delay(1000);
	checkBlank(APPLICATION_FLASH_START_ADDRESS, APPLICATION_FLASH_SIZE);//FLASH 查空
	HAL_Delay(1000);
	printf("Bootloader:Erase mcu application sucess.\n");
	RamAddress = (uint32_t)&RAM_Buf;//获取RAM缓存区地址
	/* Erase address init */
	LastPGAddress = APPLICATION_FLASH_START_ADDRESS;
	/* While file still contain data */
	crc32 = 0;
	crc32Clear();
	while(readflag){
		SET_RED_LED_ON;
		/* Read maximum 512 Kbyte from the selected file */
		f_read(&McuFile, RAM_Buf, BUFFER_SIZE, (void*)&bytesread);
		SET_RED_LED_OFF;
		crc32 = crc32Calculate(RAM_Buf, bytesread);
		/* Temp variable */
		TmpReadSize = bytesread;
		/* The read data < "BUFFER_SIZE" Kbyte */
		if(TmpReadSize < BUFFER_SIZE){
			readflag = FALSE;
		}
		/* Program flash memory */
		for(programcounter = 0; programcounter < TmpReadSize; programcounter += 4){
			/* Write word into flash memory */
			if(FLASH_If_Write((LastPGAddress + programcounter), *(uint32_t *) (RamAddress + programcounter)) != 0x00){
				bootLoadFailHandler(BT_FAIL_WRITE_MCU_APP_FLASH);//写入FLASH错误
			}
		}
		/* Update last programmed address value */
		LastPGAddress += TmpReadSize;
	}
	for(i = LastPGAddress;i < APPLICATION_FLASH_END_ADDRESS;i ++){//补完剩余CRC
		crc32 = crc32CalculateAdd(0xFF);
	}
	HAL_FLASH_Lock();
	HAL_Delay(1000);
	printf("Bootloader:Write mcu app finish.\n");
	f_close(&McuFile);
	return crc32;
}

static void prepareUpdateLcd(void){//LCD远程升级准备        
	memset(gddcRxBuf, 0x0, sizeof(gddcRxBuf));
	dp_display_text_num(cmdShakeHandOp, strlen((char*)cmdShakeHandOp));		
	HAL_UART_Receive(&CONFIG_GDDC_UART, gddcRxBuf, 6, 1000);//查询串口接收数据 超时1000       
	if(cmpByte(gddcRxBuf, cmdShakeHandRespondOp, sizeof(cmdShakeHandRespondOp))){
		printf("Bootloader:DoneHandler,lcd shake hand respond!\n");
	}
	dp_display_text_num(cmdResetOp, strlen((char*)cmdResetOp));//切换成大彩指令集
	HAL_Delay(10);
	dp_display_text_num(cmdFormatOp, strlen((char*)cmdFormatOp));//格式化文件系统
	HAL_Delay(3000);
}
static uint32_t updateLcdApp(char* filePath){//更新LCD APP单个文件
	UART_HandleTypeDef *puart;
	HAL_StatusTypeDef uRet;
	uint32_t crc32, i;
	uint8_t signName;  
	uint8_t cmdResponse[] = {0xEE,0xFB,0x01,0xFF,0xFC,0xFF,0xFF};//屏幕答应
	uint32_t bufIndex;
	uint32_t fileSize;//文件大小
	uint32_t blockSize = 2048;//需要读取的数据包大小
	uint32_t transferByte;//读取字节数
	uint32_t actualByte;//实际读取的字节数
	uint32_t fileIndex;
	uint16_t checkSum;//校验码
	uint8_t lcdRetry;//错误重复次数
	char* fileCmdPath;    
	puart = &CONFIG_GDDC_UART;
	retUsbH = f_open(&LcdFile, filePath, FA_OPEN_EXISTING | FA_READ);
	if(retUsbH != FR_OK){//读取失败
		bootLoadFailHandler(BT_FAIL_READ_LCD_APP);
	}
	f_lseek(&LcdFile, 0);//读取指针移动到开头
	printf("Bootloader:Open %s sucess,ECODE=0x%02XH.\n", filePath, retUsbH);
  fileSize =  f_size(&LcdFile);
	gddcTxBuf[0] = 0xEE;
	gddcTxBuf[1] = 0xFB;
	//下载包大小
	gddcTxBuf[2] = ((blockSize + 4) >> 8) & 0xFF;
	gddcTxBuf[3] = ((blockSize + 4) >> 0) & 0xFF;
	//波特率不改变
	gddcTxBuf[4] = 0;
	gddcTxBuf[5] = 0;
	//文件大小
	gddcTxBuf[6] = (fileSize >> 24) & 0xff;
	gddcTxBuf[7] = (fileSize >> 16) & 0xff;
	gddcTxBuf[8] = (fileSize >>  8) & 0xff;
	gddcTxBuf[9] = (fileSize) & 0xff;
	//文件名
	gddcTxBuf[10] = 0x33;
	gddcTxBuf[11] = 0x3A;
	//下载命令中的路径从实际路劲的第一个‘/’开始，忽略‘private’
  //例：实际路劲为 private/bin/image.bin
  //命令中的路径为 3:/bin/image.bin
  fileCmdPath = strchr((filePath + 1),'/');                           
	for(i = 0;i < strlen(fileCmdPath);i++){
		if(fileCmdPath[i] == '/'){
			gddcTxBuf[12 + i] = 0x5C;
		}
		else{
			gddcTxBuf[12 + i] = fileCmdPath[i];
		}
	}
	gddcTxBuf[strlen(fileCmdPath) + 12] = 0xFF;
  gddcTxBuf[strlen(fileCmdPath) + 13] = 0xFC;
  gddcTxBuf[strlen(fileCmdPath) + 14] = 0xFF;
  gddcTxBuf[strlen(fileCmdPath) + 15] = 0xFF;

  //发送下载命令
	printf("Bootloader->updateLcdApp:Send download command.\n");
	lcdRetry = 0;
	do{
		lcdRetry++;
		uRet = HAL_UART_Receive(puart, gddcRxBuf, sizeof(gddcRxBuf), 1);//清空接收缓冲区
		memset(gddcRxBuf, 0x0, sizeof(gddcRxBuf));	
		gddcRxIndex = 0;
		dp_display_text_num(gddcTxBuf, (strlen(fileCmdPath) + 16));//计算得到命令长度
		uRet = HAL_UART_Receive(puart, gddcRxBuf, 7, 5000);//串口接收数据 超时10000mS
		HAL_Delay(10);
		if(cmpByte(gddcRxBuf, cmdResponse, 7) == true){
			break;
		}
		else{
			HAL_Delay(10);
			if(lcdRetry > GDDC_RETRY_TIMES){//发送次数超时
				bootLoadFailHandler(BT_FAIL_LCD_DOWNLOAD);
			}
		}
	}while(1);
  //一个数据包固定为2052字节
  //格式:SN ~SN DATA CHECKSUM
  //SN为包序号,1字节0~255循环使用
  //~SN为上述序号取反
  //DATA固定为2048字节,不够补0
  //CHECKSUM,2字节,前面2050字节求和后取反
	signName = 0;
	crc32 = 0;
	crc32Clear();
	for(fileIndex = 0; fileIndex < fileSize; fileIndex += blockSize){
		memset(gddcTxBuf, 0x0, sizeof(gddcTxBuf));  
		gddcTxBuf[0] = signName;
		gddcTxBuf[1] = ~signName;
    transferByte = blockSize;
		if(fileIndex + transferByte > fileSize){//读取2048个字节但不超过文件大小
			transferByte = fileSize - fileIndex;
		}
		SET_RED_LED_ON;
		retUsbH = f_read(&LcdFile, &gddcTxBuf[2], transferByte, &actualByte);
		SET_RED_LED_OFF;
		crc32 = crc32Calculate(&gddcTxBuf[2], actualByte);
		if(retUsbH != FR_OK){
			bootLoadFailHandler(BT_FAIL_READ_LCD_APP);
    }
    //计算校验和
		checkSum = 0x0;
		bufIndex = 0;
		do{
			checkSum += (uint16_t)gddcTxBuf[bufIndex];
			bufIndex ++;
		}while(bufIndex < 2050);
		checkSum = (uint16_t)~(checkSum);//取反填充在包末尾
		gddcTxBuf[2050] = (checkSum >> 8) & 0xFF;
		gddcTxBuf[2051] = (checkSum >> 0) & 0xFF;   
		lcdRetry = 0;
		do{
			lcdRetry ++;
			//发送数据包，直到成功或次数超过限制	
			printf("Bootloader->updateLcdApp:Send file block at 0x%08XH,", fileIndex);
			HAL_UART_Receive(puart, gddcRxBuf, sizeof(gddcRxBuf), 1);//清空接收缓冲区
			memset(gddcRxBuf, 0x0, sizeof(gddcRxBuf));
			dp_display_text_num(gddcTxBuf, (blockSize + 4));//send data
			uRet = HAL_UART_Receive(puart, gddcRxBuf, 2, 3000);//查询串口接收数据 超时3000            
			if(uRet == HAL_OK){
				if(gddcRxBuf[1] == (uint8_t)(~(signName + 1)) || gddcRxBuf[0] == (signName+1) && gddcRxBuf[1] == (uint8_t)(~(signName+1))){//wait ack
					signName = signName + 1;
					printf("ok!\n");
					break;
				}
			}
			else{//超时或无效SN
				printf("timeout or invalid SN!\n");
				HAL_Delay(100);
				if(lcdRetry > GDDC_RETRY_TIMES){//发送次数超时
					bootLoadFailHandler(BT_FAIL_LCD_DOWNLOAD);
				}
			}
		}while(1);
	}
	f_close(&LcdFile);
	return crc32;
}

static uint32_t getOriginAppCrc(void){//计算MCU APP CRC32
	uint8_t val;
	uint32_t i;
	uint32_t crc32;
	crc32Clear();
	for(i = APPLICATION_FLASH_START_ADDRESS;i < APPLICATION_FLASH_END_ADDRESS;i ++){
		val = *(__IO uint8_t*)(i);
		crc32 = crc32CalculateAdd(val);//CRC32计算连续字节
	}
	return crc32;	
}
/*****************************************************************************/
//触摸屏程序
static void DBGU_Printk_num(uint8_t *buffer, uint16_t datanum){//arg pointer to a string ending by
	HAL_UART_Transmit(&CONFIG_GDDC_UART, (const uint8_t*)buffer, datanum, GDDC_TX_TIMEOUT);
}

static void dp_display_text_num(uint8_t *text, uint16_t datanum){
    /* User Specific Code   */
    DBGU_Printk_num(text, datanum);
}

/*****************************************************************************/
static FRESULT crcLcdFile(char* scanPath){//扫描文件夹内全部文件并计算CRC值
	DIR memofsrcdir;
	DIR *srcdir;
	FILINFO menoffinfo;
	FILINFO *finfo;
	char fileName[256];
	char *fn;
	finfo=&menoffinfo; 
	srcdir=&memofsrcdir;  //源目录
	retUsbH = f_opendir(srcdir, (const TCHAR*)scanPath);
	while(retUsbH == FR_OK){
		retUsbH = f_readdir(srcdir, finfo);
		if(retUsbH != FR_OK || finfo->fname[0] == 0){//无效文件
			break;
		}
		if(finfo->fname[0] == '.'){
			continue;
		}
		fn = finfo->fname;
		memset(fileName, 0x0, sizeof(fileName));
		sprintf(fileName, "%s%c%s",scanPath , '/', fn);
		if(finfo->fattrib & AM_DIR){//文件夹
			retUsbH = crcLcdFile(fileName);
			if(retUsbH != FR_OK){
				return retUsbH;
			}
		}
		else{
			printf("Bootloader:crc Lcd file:%s\n", fileName);
			crcUdisk += getNewLcdAppCrc(fileName);//计算U盘中MCU APP固件CRC32
		}		
	}
	f_closedir(srcdir);
	return retUsbH;
}	

static FRESULT updateLcdFile(char* scanPath){//扫描文件夹内全部文件并上传
	DIR memofsrcdir;
	DIR *srcdir;
	FILINFO menoffinfo;
	FILINFO *finfo;
	char fileName[256];
	char *fn;
	finfo=&menoffinfo; 
	srcdir=&memofsrcdir;  //源目录
	retUsbH = f_opendir(srcdir, (const TCHAR*)scanPath);
	while(retUsbH == FR_OK){
		retUsbH = f_readdir(srcdir, finfo);
		if(retUsbH != FR_OK || finfo->fname[0] == 0){//无效文件
			break;
		}
		if(finfo->fname[0] == '.'){
			continue;
		}
		fn = finfo->fname;
		memset(fileName, 0x0, sizeof(fileName));
		sprintf(fileName, "%s%c%s",scanPath , '/', fn);
		if(finfo->fattrib & AM_DIR){//文件夹
			retUsbH = updateLcdFile(fileName);
			if(retUsbH != FR_OK){
				return retUsbH;
			}
		}
		else{
			printf("Bootloader:crc Lcd file:%s\n", fileName);
			crcUdisk += updateLcdApp(fileName);//计算U盘中MCU APP固件CRC32
		}		
	}
	f_closedir(srcdir);
	return retUsbH;
}

