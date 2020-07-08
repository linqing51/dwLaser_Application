#include "sPlc.h"
//避免指针和动态RAM分配 移植大部分8BIT和16BIT单片机效率低存在问题
/*****************************************************************************/
int16_t NVRAM0[CONFIG_NVRAM_SIZE];//掉电保持寄存器 当前 包含存档寄存器
int16_t NVRAM1[CONFIG_NVRAM_SIZE];//掉电保持寄存器 上一次
int16_t FDRAM[CONFIG_FDRAM_SIZE];//存档寄存器
uint8_t LKSRAM[CONFIG_LKSRAM_SIZE];//通信发送缓冲区
uint8_t LKRRAM[CONFIG_LKRRAM_SIZE];//通信接收缓冲区
uint8_t TimerCounter_1mS = 0;
uint8_t TimerCounter_10mS = 0;
uint8_t TimerCounter_100mS = 0;
uint8_t TD_10MS_SP = 0;
uint8_t TD_100MS_SP = 0;
uint8_t TD_1000MS_SP = 0;
uint32_t sPlcEnterTime, sPlcExitTime, sPlcScanTime;
/******************************************************************************/
void errorHandler(uint16_t errCode){
	while(1);
}


void assertCoilAddress(uint16_t adr){//检查线圈地址
#if CONFIG_SPLC_ASSERT == 1
	uint32_t maxCoilAdr = CONFIG_NVRAM_SIZE * 16 - 1;
	if(adr > (maxCoilAdr)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
void assertRegisterAddress(uint16_t adr){//检查寄存器地址
#if CONFIG_SPLC_ASSERT == 1
	if(adr > (CONFIG_NVRAM_SIZE - 1)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
void loadNvram(void){//从EPROM中载入NVRAM
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));
#if CONFIG_SPLC_USING_EPROM == 1
	epromRead(CONFIG_EPROM_NVRAM_START, (uint8_t*)NVRAM0, ((DM_END -  DM_START + 1) * 2));//从EPROM中恢复MR
#endif
	memcpy((uint8_t*)NVRAM1, (uint8_t*)NVRAM0, (CONFIG_NVRAM_SIZE * 2));
}
void saveNvram(void){//强制将NVRAM存入EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	epromWrite(CONFIG_EPROM_NVRAM_START, (uint8_t*)NVRAM0, ((MR_END + 1) * 2));
#endif
}
void updateNvram(void){//更新NVRAM->EPROM
	uint8_t *sp0, *sp1;
	uint16_t i;
	sp0 = (uint8_t*)NVRAM0;
	sp1 = (uint8_t*)NVRAM1;
	//储存MR和DM
	for(i = (CONFIG_EPROM_NVRAM_START + (MR_START * 2));i < ((DM_END + 1) * 2);i ++){//储存MR
		if(*sp0 != *sp1){
#if CONFIG_SPLC_USING_EPROM == 1
			epromWriteByte(i, *sp0);
#endif
		}
		sp0 ++;
		sp1 ++;
	}
	memcpy((uint8_t*)(NVRAM1), (uint8_t*)(NVRAM0), (CONFIG_NVRAM_SIZE * 2));//更新NVRAM1 非保持寄存器
}
void clearNvram(void){//清除NVRAM数据	
	uint16_t i = 0;
	enterSplcIsr();
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = CONFIG_EPROM_NVRAM_START; i< (CONFIG_NVRAM_SIZE * 2);i ++){
		epromWriteByte(i, 0x0);//
	}
#endif
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));//初始化NVRAM0
	memset((uint8_t*)NVRAM1, 0x0, (CONFIG_NVRAM_SIZE * 2));//初始化NVRAM1
	exitSplcIsr();//恢复中断
}
void clearEprom(void){
	uint16_t i;
	//清空EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		epromWriteByte(i, 0x0);
	}
	//写入校验码
	epromWriteByte((CONFIG_EPROM_SIZE - 4), 0x55);
	epromWriteByte((CONFIG_EPROM_SIZE - 3), 0xAA);
	epromWriteByte((CONFIG_EPROM_SIZE - 2), 0xBC);
	epromWriteByte((CONFIG_EPROM_SIZE - 1), 0xD4);
#endif
}
extern void loadDefault(void);
void checkEprom(void){
	uint16_t i;
	uint8_t checkCode[4];
#if CONFIG_SPLC_USING_EPROM == 1
	checkCode[0] = 0;
	checkCode[1] = 0;
	checkCode[2] = 0;
	checkCode[3] = 0;
	epromRead((CONFIG_EPROM_SIZE - 4), checkCode, 4);//从EPROM中恢复MR
	if((checkCode[0] != 0x55) || (checkCode[1] != 0xAA) || (checkCode[2] != 0xBC) || (checkCode[3] != 0xD1)){
		//检测到校验码错误清空EPROM
#if CONFIG_SPLC_USING_EPROM == 1
		for(i = 0; i< CONFIG_EPROM_SIZE;i ++){
			epromWriteByte(i, 0x0);
		}
		epromWriteByte((CONFIG_EPROM_SIZE - 4), 0x55);
		epromWriteByte((CONFIG_EPROM_SIZE - 3), 0xAA);
		epromWriteByte((CONFIG_EPROM_SIZE - 2), 0xBC);
		epromWriteByte((CONFIG_EPROM_SIZE - 1), 0xD1);
#endif
		loadDefault();
	}
#endif
}

void loadFdram(void){//从EPROM中载入FDRAM
#if CONFIG_SPLC_USING_EPROM == 1
	epromRead(CONFIG_EPROM_FDRAM_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));//从EPROM中恢复MR
#endif
}
void saveFdram(void){//强制将FDRAM存入EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	epromWrite(CONFIG_EPROM_FDRAM_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));
#endif
}
void clearFdram(void){//清楚FDRAM数据
	uint16_t i;
	//disableWatchDog();
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = CONFIG_EPROM_FDRAM_START; i< (CONFIG_FDRAM_SIZE * 2) ; i++){
#if CONFIG_SPLC_USING_EPROM == 1
		epromWriteByte(i, 0x0);
#endif
	}
#endif
	memset(FDRAM, 0x0, (CONFIG_FDRAM_SIZE * 2));//初始化FDRAM
}

void sPlcSpwmLoop(void){//SPWM轮询	
	if(LDP(SPCOIL_PS10MS)){//每10mS执行一次
		//SPWM0
		if(LD(SPCOIL_SPWM_RESET_0)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_0] = SHRT_MAX;
			RRES(SPCOIL_SPWM_RESET_0);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_0] == NVRAM0[SPREG_SPWM_POS_SHADOW_0]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
			RRES(SPCOIL_SPWM_OUT_0);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_0] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_0] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_0] = NVRAM0[SPREG_SPWM_POS_0];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = NVRAM0[SPREG_SPWM_CYCLE_0];
			SSET(SPCOIL_SPWM_OUT_0);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
		}
		//SPWM1
		if(LD(SPCOIL_SPWM_RESET_1)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_1] = SHRT_MAX;
			RRES(SPCOIL_SPWM_RESET_1);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_1] == NVRAM0[SPREG_SPWM_POS_SHADOW_1]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
			RRES(SPCOIL_SPWM_OUT_1);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_1] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_1] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_1] = NVRAM0[SPREG_SPWM_POS_1];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = NVRAM0[SPREG_SPWM_CYCLE_1];
			SSET(SPCOIL_SPWM_OUT_1);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
		}
		//SPWM2
		if(LD(SPCOIL_SPWM_RESET_2)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_2] = SHRT_MAX;
			RRES(SPCOIL_SPWM_RESET_2);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_2] == NVRAM0[SPREG_SPWM_POS_SHADOW_2]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
			RRES(SPCOIL_SPWM_OUT_2);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_2] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_2] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_2] = NVRAM0[SPREG_SPWM_POS_2];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2] = NVRAM0[SPREG_SPWM_CYCLE_2];
			SSET(SPCOIL_SPWM_OUT_2);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
		}
		//SPWM3
		if(LD(SPCOIL_SPWM_RESET_3)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_3] = SHRT_MAX;
			RRES(SPCOIL_SPWM_RESET_3);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_3] == NVRAM0[SPREG_SPWM_POS_SHADOW_3]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
			RRES(SPCOIL_SPWM_OUT_3);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_3] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_3] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_3] = NVRAM0[SPREG_SPWM_POS_3];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = NVRAM0[SPREG_SPWM_CYCLE_3];
			SSET(SPCOIL_SPWM_OUT_3);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
		}
	}
}

/*****************************************************************************/
void sPlcInit(void){//软逻辑初始化
	//sPlcEpromTest();
#if CONFIG_DEBUG_SPLC == 1
	printf("\r\r\r\n\n\n");
	printf("sPlc:Start load Nvram......\n");
#endif
	loadNvram();//上电恢复NVRAM
#if CONFIG_DEBUG_SPLC == 1
	printf("sPlc:Start load Fdram......\n");
#endif
	loadFdram();//上电恢复FDRAM
	SSET(SPCOIL_ON);
	SSET(SPCOIL_START_UP);
	//NVRAM0[SPREG_MUSIC_VOLUME] = 0;									
	//NVRAM0[SPREG_PLAYING_MUSIC_ID] = 0;							
	//NVRAM0[SPREG_NEXT_MUSIC_ID] = 0;									
	//NVRAM0[SPREG_CONTROL_MUSIC]	= CMD_MUSIC_STOP;
	NVRAM0[SPREG_IDENTITY] = CONFIG_SPLC_DEV;
#if CONFIG_SPLC_USING_CLEAR_NVRAM == 1 && CONFIG_SPLC_USING_EPROM == 1
	if(NVRAM0[SPREG_CLEAR_NVRAM] == (int16_t)CONFIG_SPLC_CLEAR_CODE){
		disableSplcTimer();//关闭中断	
		if(epromTest()){//EPROM测试成功
			__nop();
		}
		else{//EPROM测试失败
			__nop();
		}
		clearNvram();
		REBOOT();	
	}
#endif

#if CONFIG_SPLC_USING_IO_INPUT == 1
#if CONFIG_DEBUG_SPLC == 1
	printf("sPlc:Start input init......\n");
#endif	
	inputInit();
#endif

#if CONFIG_SPLC_USING_IO_OUTPUT == 1
#if CONFIG_DEBUG_SPLC == 1
	printf("sPlc:Start output init......\n");
#endif	
	outputInit();
#endif

#if CONFIG_SPLC_USING_DAC == 1	
#if CONFIG_DEBUG_SPLC == 1
	printf("sPlc:Start Dac init......\n");
#endif	
	initChipDac();//初始化DAC模块
#endif

#if CONFIG_SPLC_USING_ADC == 1
#if CONFIG_DEBUG_SPLC == 1
	printf("sPlc:Start Adc init......\n");
#endif	
	initChipAdc();//初始化ADC模块
#endif


#if CONFIG_SPLC_USING_LASER == 1
#if CONFIG_DEBUG_SPLC == 1
	printf("sPlc:Start laser timer init......\n");
#endif
	sPlcLaserInit();
#endif

#if CONFIG_SPLC_USING_DK25L == 1
#if CONFIG_DEBUG_SPLC == 1
	printf("sPlc:Start NFC init......\n");
#endif
	delayMs(100);
	DL25L_Init();//打开中断后运行
#endif

#if CONFIG_DEBUG_SPLC == 1
	printf("sPlc:Start splc timer init......\n");
#endif
	initSplcTimer();//初始化硬件计时器模块 启动计时器
}
void sPlcProcessStart(void){//sPLC轮询起始
	sPlcEnterTime = HAL_GetTick();
	if(TD_10MS_SP >= 1){
		FLIP(SPCOIL_PS10MS);
		TD_10MS_SP = 0;
	}
	if(TD_100MS_SP >= 1){
		FLIP(SPCOIL_PS100MS);
		TD_100MS_SP = 0;
	}
	if(TD_1000MS_SP >= 1){
		FLIP(SPCOIL_PS1000MS);
		TD_1000MS_SP = 0;
	}
#if CONFIG_SPLC_USING_IO_INPUT == 1
	inputRefresh();//读取X口输入
#endif
#if CONFIG_SPLC_USING_SPWM == 1
	sPlcSpwmLoop();
#endif
#if CONFIG_SPLC_USING_ADC == 1
	chipAdcProcess();//ADC 更新NVRAM
#endif
}
void sPlcProcessEnd(void){//sPLC轮询结束
#if CONFIG_SPLC_USING_IO_OUTPUT == 1
	outputRefresh();//更新Y口输出
#endif
#if CONFIG_SPLC_USING_BEEM == 1
	sPlcBeemLoop();
#endif
#if	CONFIG_SPLC_USING_LEDAIM == 1
	sPlcAimLoop();
#endif
	updateNvram();//更新NVRAM
	RRES(SPCOIL_START_UP);
	sPlcExitTime = HAL_GetTick();
	sPlcScanTime = sPlcExitTime - sPlcEnterTime;
	NVRAM0[SPREG_SCAN_TIME] = (uint16_t)sPlcScanTime;
}




