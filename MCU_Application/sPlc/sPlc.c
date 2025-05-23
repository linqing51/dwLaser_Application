#include "sPlc.h"
//避免指针和动态RAM分配 移植大部分8BIT和16BIT单片机效率低存在问题
/*****************************************************************************/
#pragma pack(push, 4)
int16_t NVRAM0[CONFIG_NVRAM_SIZE];//掉电保持寄存器 当前 包含存档寄存器
int16_t NVRAM1[CONFIG_NVRAM_SIZE];//掉电保持寄存器 上一次
int16_t FDRAM0[CONFIG_FDRAM_SIZE], FDRAM1[CONFIG_FDRAM_SIZE];//存档寄存器
uint32_t BootloadCrc, ApplicationCrc;//当前固件校验码
#pragma pack(pop)
/*****************************************************************************/
uint16_t TimerCounter_10mS = 0;//10毫秒
uint16_t TimerCounter_100mS = 0;//100毫秒
uint16_t TimerCounter_200mS = 0;//200毫秒
uint16_t TimerCounter_500mS = 0;//500毫秒
uint16_t TimerCounter_1000mS = 0;//1秒
uint16_t TimerCounter_60000mS = 0;//1分钟
/*****************************************************************************/
uint8_t TD_10MS_SP = 0;
uint8_t TD_100MS_SP = 0;
uint8_t TD_200MS_SP = 0;
uint8_t TD_500MS_SP = 0;
uint8_t TD_1000MS_SP = 0;
uint8_t TD_60000MS_SP = 0;
/******************************************************************************/
void sPlcIsrEnable(void){
}
void sPlcIsrDisable(void){
}
void sPlcErrorHandler(uint16_t errCode){
	while(1);
}

void sPlcAssertCoilAddress(uint16_t adr){//检查线圈地址
#if CONFIG_SPLC_ASSERT == 1
	uint32_t maxCoilAdr = CONFIG_NVRAM_SIZE * 16 - 1;
	if(adr > (maxCoilAdr)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
void sPlcAssertRegisterAddress(uint16_t adr){//检查寄存器地址
#if CONFIG_SPLC_ASSERT == 1
	if(adr > (CONFIG_NVRAM_SIZE - 1)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
void sPlcNvramLoad(void){//从EPROM中载入NVRAM MR和DM
	uint32_t crc32_mr, crc32_dm;
	uint32_t crc32_eprom_mr, crc32_eprom_dm;
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));
	//从EPROM中恢复MR NVRAM
	epromRead(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE * 2));//从EPROM中恢复MR
	epromReadDword(CONFIG_EPROM_MR_CRC, &crc32_eprom_mr);
	crc32_mr = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE / 2));
	
	//从EPROM中恢复DM NVRAM
	epromRead(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE * 2));//从EPROM中恢复DM
	epromReadDword(CONFIG_EPROM_DM_CRC, &crc32_eprom_dm);
	crc32_dm = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE / 2));
	
	memcpy((uint8_t*)NVRAM1, (uint8_t*)NVRAM0, (CONFIG_NVRAM_SIZE * 2));
	printf("%s,%d,%s:MR EPROM CRC:0x%08X,MR CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_mr, crc32_mr);
	printf("%s,%d,%s:DM EPROM CRC:0x%08X,DM CALC CRC:0x%08X\n",__FILE__, __LINE__, __func__, crc32_eprom_dm, crc32_dm);
	if((crc32_eprom_mr != crc32_mr) && (crc32_eprom_dm != crc32_dm)){
		printf("%s,%d,%s:load NVRAM crc fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load NVRAM done...\n",__FILE__, __LINE__, __func__);
	}
}
void sPlcNvramSave(void){//强制将NVRAM存入EPROM
	uint32_t crc32_mr, crc32_dm;
	//MR NVRAM写入EPROM
	epromWrite(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE * 2));//将NVRAM中MR储存入EPROM																				
	crc32_mr = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE / 2));
	epromWriteDword(CONFIG_EPROM_MR_CRC, &crc32_mr);//在的指定地址开始写入32位数
	//DM NVRAM写入EPROM
	epromWrite(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE * 2));//将NVRAM中DM储存入EPROM
	crc32_dm = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE / 2));
	epromWriteDword(CONFIG_EPROM_DM_CRC, &crc32_dm);//在的指定地址开始写入32位数
	printf("%s,%d,%s:save NVRAM done...(MR CRC:0x%08X,DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr, crc32_dm);
}
void sPlcNvramUpdate(void){//更新NVRAM->EPROM
	uint8_t *sp0, *sp1;
	uint8_t updateFlagMr, updateFlagDm;
	uint16_t i;
	uint32_t crc32_mr, crc32_dm;
	//储存MR
	updateFlagMr = 0;
	sp0 = (uint8_t*)(NVRAM0 + MR_START);
	sp1 = (uint8_t*)(NVRAM1 + MR_START);
	for(i = 0;i < (CONFIG_MRRAM_SIZE * 2);i ++){//储存MR
		if(*sp0 != *sp1){
			epromWriteByte((i + CONFIG_EPROM_MR_START), sp0);
			updateFlagMr |= 0xFF;
		}
		sp0 ++;
		sp1 ++;
	}
	if(updateFlagMr){
		crc32_mr = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE / 2));
		epromWriteDword(CONFIG_EPROM_MR_CRC, &crc32_mr);//在的指定地址开始写入32位数
	}
	//储存DM
	updateFlagDm = 0;
	sp0 = (uint8_t*)(NVRAM0 + DM_START);
	sp1 = (uint8_t*)(NVRAM1 + DM_START);
	for(i = 0;i < (CONFIG_DMRAM_SIZE * 2);i ++){//储存MR
		if(*sp0 != *sp1){
			epromWriteByte((i + CONFIG_EPROM_DM_START), sp0);
			updateFlagDm |= 0xFF;
		}
		sp0 ++;
		sp1 ++;
	}
	if(updateFlagDm){
		crc32_dm = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE / 2));
		epromWriteDword(CONFIG_EPROM_DM_CRC, &crc32_dm);//在的指定地址开始写入32位数
	}
	memcpy((uint8_t*)(NVRAM1), (uint8_t*)(NVRAM0), (CONFIG_NVRAM_SIZE * 2));//更新NVRAM1 非保持寄存器
	if(updateFlagMr){
		printf("%s,%d,%s:update MR NVRAM done...(MR CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr);
	}
	if(updateFlagDm){
		printf("%s,%d,%s:update DM NVRAM done...(DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_dm);
	}
}
void sPlcNvramClear(void){//清除NVRAM数据	
	sPlcIsrDisable();
	clearEprom(CLEAR_EPROM_NVRAM);//clear mr dm
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));//初始化NVRAM0
	memset((uint8_t*)NVRAM1, 0x0, (CONFIG_NVRAM_SIZE * 2));//初始化NVRAM1
	sPlcIsrEnable();//恢复中断
	printf("%s,%d,%s:clear NVRAM done...\n",__FILE__, __LINE__, __func__);
}
void sPlcFdramLoad(void){//从EPROM中载入FDRAM
	HAL_StatusTypeDef ref;
	sPlcIsrDisable();
	ref = epromRead(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));//从EPROM中恢复MR
	sPlcIsrEnable();//恢复中断
	if(ref != HAL_OK){
		printf("%s,%d,%s:load FD NVRAM crc fail!!!\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	}
}
void sPlcFdramSave(void){//强制将FDRAM存入EPROM
	HAL_StatusTypeDef ref;
	sPlcIsrDisable();
	ref = epromWrite(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM0, (CONFIG_FDRAM_SIZE * 2));
	if(ref != HAL_OK){
		printf("%s,%d,%s:save FD NVRAM fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:save FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	}
	sPlcIsrEnable();//恢复中断
}
void sPlcFdramClear(void){//清除FDRAM数据
	sPlcIsrDisable();
	clearEprom(CLEAR_EPROM_FDRAM);//clear mr dm
	memset(FDRAM0, 0x0, (CONFIG_FDRAM_SIZE * 2));//初始化FDRAM
	printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	sPlcIsrEnable();//恢复中断
}
void sPlcDeviceConfigClear(void){//清除设备配置参数
	sPlcIsrDisable();
	clearEprom(CLEAR_EPROM_DEVICE_CONFIG);
	printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	sPlcIsrEnable();//恢复中断	
}
void sPlcDeviceLogClear(void){//清除设备记录
	sPlcIsrDisable();
	clearEprom(CLEAR_EPROM_LOG_INFO);
	printf("%s,%d,%s:clear device log done...\n",__FILE__, __LINE__, __func__);
	sPlcIsrEnable();//恢复中断	
}

void sPlcSpwmLoop(void){//SPWM轮询	
	if(LDP(SPCOIL_PS10MS)){//每10mS执行一次
		//SPWM0
		if(LD(SPCOIL_SPWM_RESET_0)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_0] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = 0;
			RRES(SPCOIL_SPWM_RESET_0);
			RRES(SPCOIL_SPWM_OUT_0);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_0] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_0] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_0] = NVRAM0[SPREG_SPWM_POS_0];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = NVRAM0[SPREG_SPWM_CYCLE_0];
			SSET(SPCOIL_SPWM_OUT_0);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_0] == NVRAM0[SPREG_SPWM_POS_SHADOW_0]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
			RRES(SPCOIL_SPWM_OUT_0);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
		}
		//SPWM1
		if(LD(SPCOIL_SPWM_RESET_1)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_1] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = 0; 
			RRES(SPCOIL_SPWM_RESET_1);
			RRES(SPCOIL_SPWM_OUT_1);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_1] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_1] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_1] = NVRAM0[SPREG_SPWM_POS_1];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = NVRAM0[SPREG_SPWM_CYCLE_1];
			SSET(SPCOIL_SPWM_OUT_1);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_1] == NVRAM0[SPREG_SPWM_POS_SHADOW_1]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
			RRES(SPCOIL_SPWM_OUT_1);
		}
		
		else{
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
		}
		//SPWM2
		if(LD(SPCOIL_SPWM_RESET_2)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_2] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = 0;
			RRES(SPCOIL_SPWM_RESET_2);
			RRES(SPCOIL_SPWM_OUT_2);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_2] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_2] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_2] = NVRAM0[SPREG_SPWM_POS_2];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2] = NVRAM0[SPREG_SPWM_CYCLE_2];
			SSET(SPCOIL_SPWM_OUT_2);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_2] == NVRAM0[SPREG_SPWM_POS_SHADOW_2]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
			RRES(SPCOIL_SPWM_OUT_2);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
		}
		//SPWM3
		if(LD(SPCOIL_SPWM_RESET_3)){//复位
			NVRAM0[SPREG_SPWM_COUNTER_3] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = 0;
			RRES(SPCOIL_SPWM_RESET_3);
			RRES(SPCOIL_SPWM_OUT_3);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_3] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3]){//发生溢出
			NVRAM0[SPREG_SPWM_COUNTER_3] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_3] = NVRAM0[SPREG_SPWM_POS_3];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = NVRAM0[SPREG_SPWM_CYCLE_3];
			SSET(SPCOIL_SPWM_OUT_3);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_3] == NVRAM0[SPREG_SPWM_POS_SHADOW_3]){//发生匹配翻转输出
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
			RRES(SPCOIL_SPWM_OUT_3);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
		}
	}
}

/*****************************************************************************/
void sPlcInit(void){//软逻辑初始化	
	printf("%s,%d,%s:start App......\n",__FILE__, __LINE__, __func__);
	listEpromTable();
	readStm32UniqueID();
#if CONFIG_SPLC_USING_EPROM_TEST == 1
	sPlcEpromTest();
#endif
	loadDeviceConfig();//载入硬件配置
	sPlcNvramLoad();//上电恢复NVRAM
	sPlcFdramLoad();//上电恢复FDRAM
	BootloadCrc = getOriginBootloadCrc();
	ApplicationCrc = getOriginAppCrc();
	printf("%s,%d,%s:bootload crc:0x%08X\n",__FILE__, __LINE__, __func__, BootloadCrc);
	printf("%s,%d,%s:app crc:0x%08X\n",__FILE__, __LINE__, __func__, ApplicationCrc);
	SSET(SPCOIL_ON);
	SSET(SPCOIL_START_UP);
	sPlcInputInit();
	sPlcOutputInit();	
	sPlcDacInit();//初始化DAC模块
	sPlcAdcInit();//初始化ADC模块
	sPlcLaserInit();
	sPlcTimerInit();//初始化硬件计时器模块 启动计时器
	sPlcSpeakerInit();
	SET_RED_LED_OFF;
	SET_GREEN_LED_OFF;	
	SET_BLUE_LED_OFF;
	RRES(Y_TICK_LED);
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
}
void sPlcProcessStart(void){//sPLC轮询起始
	if(TD_10MS_SP >= 1){
		FLIP(SPCOIL_PS10MS);
		TD_10MS_SP = 0;
		if(NVRAM0[SPREG_BEEM_COUNTER] < INT16_MAX){
			NVRAM0[SPREG_BEEM_COUNTER] ++;
		}
	}
	if(TD_100MS_SP >= 1){
		FLIP(SPCOIL_PS100MS);
		TD_100MS_SP = 0;
	}
	if(TD_200MS_SP >= 1){
		FLIP(SPCOIL_PS200MS);
		TD_200MS_SP = 0;
	}
	if(TD_500MS_SP >= 1){
		FLIP(SPCOIL_PS500MS);
		TD_500MS_SP = 0;
	}
	if(TD_1000MS_SP >= 1){
		FLIP(SPCOIL_PS1000MS);
		TD_1000MS_SP = 0;
	}
	if(TD_60000MS_SP >= 1){
		FLIP(SPCOIL_PS1MINS);
		TD_60000MS_SP = 0;
	}
	sPlcInputRefresh();//读取X口输入
#if CONFIG_SPLC_USING_SPWM == 1
	sPlcSpwmLoop();
#endif
	sPlcAdcProcess();//ADC 更新NVRAM
}

void sPlcProcessEnd(void){//sPLC轮询结束
//	if(LDP(SPCOIL_PS500MS)){
//		FLIP(Y_TICK_LED);
//	}
	sPlcOutputRefresh();//更新Y口输出
	sPlcNvramUpdate();//更新NVRAM
	RRES(SPCOIL_START_UP);
}




