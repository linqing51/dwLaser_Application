#include "sPlc.h"
//避免指针和动态RAM分配 移植大部分8BIT和16BIT单片机效率低存在问题
/*****************************************************************************/
#pragma pack(push, 4)
int16_t NVRAM0[CONFIG_NVRAM_SIZE];//掉电保持寄存器 当前 包含存档寄存器
int16_t NVRAM1[CONFIG_NVRAM_SIZE];//掉电保持寄存器 上一次
int16_t FDRAM[CONFIG_FDRAM_SIZE];//存档寄存器
uint8_t LKSRAM[CONFIG_LKSRAM_SIZE];//通信发送缓冲区
uint8_t LKRRAM[CONFIG_LKRRAM_SIZE];//通信接收缓冲区
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
uint32_t sPlcEnterTime, sPlcExitTime, sPlcScanTime;
/******************************************************************************/
extern CRC_HandleTypeDef hcrc;
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
void loadNvram(void){//从EPROM中载入NVRAM MR和DM
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

	if((crc32_eprom_mr != crc32_mr) && (crc32_eprom_dm != crc32_dm)){
		printf("%s,%d,%s:load NVRAM crc fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load NVRAM done...\n",__FILE__, __LINE__, __func__);
	}
}
void saveNvram(void){//强制将NVRAM存入EPROM
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
void updateNvram(void){//更新NVRAM->EPROM
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
void clearNvram(void){//清除NVRAM数据	
	enterSplcIsr();
	clearEprom(CLEAR_EPROM_NVRAM);//clear mr dm
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));//初始化NVRAM0
	memset((uint8_t*)NVRAM1, 0x0, (CONFIG_NVRAM_SIZE * 2));//初始化NVRAM1
	exitSplcIsr();//恢复中断
	printf("%s,%d,%s:clear NVRAM done...\n",__FILE__, __LINE__, __func__);
}
void loadFdram(void){//从EPROM中载入FDRAM
	uint32_t crc32_eprom_fd, crc32_fd;
	enterSplcIsr();
	epromRead(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));//从EPROM中恢复MR
	epromReadDword(CONFIG_EPROM_FD_CRC, &crc32_eprom_fd);
	crc32_fd = HAL_CRC_Calculate(&hcrc,(uint32_t *)FDRAM, (CONFIG_FDRAM_SIZE / 2));
	exitSplcIsr();//恢复中断
	if(crc32_eprom_fd != crc32_fd){
		printf("%s,%d,%s:load FD NVRAM crc fail!!!\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	}
}
void saveFdram(void){//强制将FDRAM存入EPROM
	uint32_t crc32;
	enterSplcIsr();
	epromWrite(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));
	crc32 = HAL_CRC_Calculate(&hcrc,(uint32_t *)(FDRAM), (CONFIG_FDRAM_SIZE / 2));
	epromWriteDword(CONFIG_EPROM_FD_CRC, &crc32);//在的指定地址开始写入32位数	
	printf("%s,%d,%s:save FD NVRAM done...(FD CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32);
	exitSplcIsr();//恢复中断
}
void clearFdram(void){//清除FDRAM数据
	enterSplcIsr();
	clearEprom(CLEAR_EPROM_FDRAM);//clear mr dm
	memset(FDRAM, 0x0, (CONFIG_FDRAM_SIZE * 2));//初始化FDRAM
	printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	exitSplcIsr();//恢复中断
}
void clearDeviceConfig(void){//清除设备配置参数
	enterSplcIsr();
	clearEprom(CLEAR_EPROM_DEVICE_CONFIG);
	printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	exitSplcIsr();//恢复中断	
}
void clearDeviceLog(void){//清除设备记录
	enterSplcIsr();
	clearEprom(CLEAR_EPROM_LOG_INFO);
	printf("%s,%d,%s:clear device log done...\n",__FILE__, __LINE__, __func__);
	exitSplcIsr();//恢复中断	
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
void sPlcLoudspeakerLoop(void){//蜂鸣器轮询
	int8_t laserStatus0, laserStatus1, laserStatus2, laserStatus3;
	if(LD(SPCOIL_BEEM_ENABLE)){
		setLoudspeakerVolume(NVRAM0[SPREG_BEEM_VOLUME]);
		switch(NVRAM0[SPREG_BEEM_MODE]){//模式
			case BEEM_MODE_0:{
				if(LDB(SPCOIL_BEEM_BUSY)){
					setLoudspeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				break;
			}
			case BEEM_MODE_1:{//模式1 声光同步
				laserStatus0 = getLaserEnable(LASER_CHANNEL_0);
				laserStatus1 = getLaserEnable(LASER_CHANNEL_1);
				laserStatus2 = getLaserEnable(LASER_CHANNEL_2);
				laserStatus3 = getLaserEnable(LASER_CHANNEL_3);
				if(laserStatus0 || laserStatus1 || laserStatus2 || laserStatus3){//LT3763 PWM ON
					if(LDB(SPCOIL_BEEM_BUSY)){//如果PWM无输出-> 有输出
						setLoudspeakerEnable();//启动音频
						SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
					}
				}
				else{
					if(LD(SPCOIL_BEEM_BUSY)){
						setLoudspeakerDisable();//启动音频
						RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器	
					}
				}
				break;
			}
			case BEEM_MODE_2:{//模式2 长间隔 激光发射音		
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 20){//1
					setLoudspeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 20 && NVRAM0[SPREG_BEEM_COUNTER] < 120){//0
					setLoudspeakerDisable();//停止音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 120){
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			case BEEM_MODE_3:{//模式3 滴滴两下一停 报警音
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 50){//1
					setLoudspeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
					
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
					setLoudspeakerDisable();//关闭音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100 && NVRAM0[SPREG_BEEM_COUNTER] < 150){//1
					setLoudspeakerEnable();//启动音频
					SSET(SPCOIL_BEEM_BUSY);//启动蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 150 && NVRAM0[SPREG_BEEM_COUNTER] < 250){//0
					setLoudspeakerDisable();//关闭音频
					RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 250){//停1秒
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			default:break;
		}
	}
	else{
		setLoudspeakerDisable();//关闭音频
		RRES(SPCOIL_BEEM_BUSY);//关闭蜂鸣器
		NVRAM0[SPREG_BEEM_COUNTER]  = 0;
	}
}
void sPlcAimLoop(void){//AIM轮询程序
	if(LDP(SPCOIL_AIM_ENABEL) && (NVRAM0[DM_AIM_BRG] > 0)){
		setAimBrightness(NVRAM0[DM_AIM_BRG]);
		SSET(SPCOIL_AIM_BUSY);
	}
	if(LDN(SPCOIL_AIM_ENABEL)){
		setAimBrightness(0);
		RRES(SPCOIL_AIM_BUSY);
	}
}
void sPlcAutoFanLoop(void){//风扇速轮询程序
	if(NVRAM0[SPREG_LAS_FAN_SPEED] > 0 && NVRAM0[SPREG_LAS_FAN_SPEED] < CONFIG_SPLC_FAN_MIN_PWM){
		NVRAM0[SPREG_LAS_FAN_SPEED] = CONFIG_SPLC_FAN_MIN_PWM;
	}

	if(NVRAM0[SPREG_LAS_FAN_SPEED] <= 0){//风扇速度小于0
		HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_RESET);
	}
	else{
		HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_SET);
	}
/*
	uint8_t lasFanPwm;
	if(NVRAM0[SPREG_LAS_FAN_SPEED] <= 0){
		NVRAM0[SPREG_LAS_FAN_SPEED] = 0;
	}
	if(NVRAM0[SPREG_LAS_FAN_SPEED] >= 100){
		NVRAM0[SPREG_LAS_FAN_SPEED] = 100;
	}
	if(NVRAM0[SPREG_LAS_FAN_SPEED] > 0){
		lasFanPwm = NVRAM0[SPREG_LAS_FAN_SPEED] * 255 / 100;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, lasFanPwm);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//打开TIM
	}
	else{
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);//关闭TIM
	}
#if CONFIG_DEBUG_FAN == 1
	printf("%s,%d,%s:set laser fan pwm,:%d\n",__FILE__, __LINE__, __func__, lasFanPwm);
#endif	
*/
}

/*****************************************************************************/
void sPlcInit(void){//软逻辑初始化
	printf("%s,%d,%s:start App......\n",__FILE__, __LINE__, __func__);
	listEpromTable();
	readStm32UniqueID();
#if CONFIG_SPLC_USING_EPROM_TEST == 1
	sPlcEpromTest();
#endif
	printf("%s,%d,%s:start load Config......\n",__FILE__, __LINE__, __func__);
	loadDeviceConfig();
	printf("%s,%d,%s:start load Nvram......\n",__FILE__, __LINE__, __func__);
	loadNvram();//上电恢复NVRAM
	printf("%s,%d,%s:start load Fdram......\n",__FILE__, __LINE__, __func__);
	loadFdram();//上电恢复FDRAM
#if CONFIG_USING_DCHMI_APP == 1
	lockPreScheme();//恢复预设方案
#endif
	SSET(SPCOIL_ON);
	SSET(SPCOIL_START_UP);
	NVRAM0[SPREG_IDENTITY] = CONFIG_SPLC_DEV;
#if CONFIG_SPLC_USING_IO_INPUT == 1
	printf("%s,%d,%s:start input init......\n",__FILE__, __LINE__, __func__);
	inputInit();
#endif

#if CONFIG_SPLC_USING_IO_OUTPUT == 1
	printf("%s,%d,%s:start output init......\n",__FILE__, __LINE__, __func__);
	outputInit();
#endif

#if CONFIG_SPLC_USING_DAC == 1	
	printf("%s,%d,%s:start Dac init......\n",__FILE__, __LINE__, __func__);
	initChipDac();//初始化DAC模块
	UPDAC0();
#endif

#if CONFIG_SPLC_USING_ADC == 1
	printf("%s,%d,%s:start adc init......\n",__FILE__, __LINE__, __func__);
	initChipAdc();//初始化ADC模块
#endif

#if CONFIG_SPLC_USING_LASER == 1
	printf("%s,%d,%s:start laser timer init......\n",__FILE__, __LINE__, __func__);
	sPlcLaserInit();
#endif

#if CONFIG_SPLC_USING_DK25L == 1
	printf("%s,%d,%s:start NFC init......\n",__FILE__, __LINE__, __func__);
	delayMs(100);
	DL25L_Init();//打开中断后运行
#endif

	printf("%s,%d,%s:start splc timer init......\n",__FILE__, __LINE__, __func__);
	initSplcTimer();//初始化硬件计时器模块 启动计时器

#if CONFIG_SPLC_USING_SPK == 1	
	printf("%s,%d,%s:start loudspeaker dma init......\n",__FILE__, __LINE__, __func__);
	initLoudspeaker();
#endif

#if CONFIG_SPLC_USING_AIM_PWM == 1
	printf("%s,%d,%s:start aim timer pwm init......\n",__FILE__, __LINE__, __func__);
	setAimFreq(CONFIG_SPLC_AIM_PWM_FREQ);
#endif

#if CONFIG_SPLC_USING_LED_PWM == 1
	printf("%s,%d,%s:start led timer pwm init......\n",__FILE__, __LINE__, __func__);
	setLedFreq(CONFIG_SPLC_LED_PWM_FREQ);
#endif

#if CONFIG_SPLC_USING_FAN_PWM == 1
	printf("%s,%d,%s:start fan timer pwm init......\n",__FILE__, __LINE__, __func__);
	setFanFreq(CONFIG_SPLC_FAN_PWM_FREQ);
#endif
}
void sPlcProcessStart(void){//sPLC轮询起始
	sPlcEnterTime = HAL_GetTick();
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
	if(LDP(SPCOIL_PS1000MS)){
		SSET(Y_TICK_LED);
	}
	if(LDN(SPCOIL_PS1000MS)){
		RRES(Y_TICK_LED);
	}
#if CONFIG_SPLC_USING_IO_OUTPUT == 1
	outputRefresh();//更新Y口输出
#endif
#if CONFIG_SPLC_USING_SPK == 1
	sPlcLoudspeakerLoop();
#endif
#if	CONFIG_SPLC_USING_AIM_PWM == 1
	sPlcAimLoop();
#endif
#if CONFIG_SPLC_USING_AIM_PWM == 1
	sPlcAutoFanLoop();
#endif
	updateNvram();//更新NVRAM
	RRES(SPCOIL_START_UP);
	sPlcExitTime = HAL_GetTick();
	sPlcScanTime = sPlcExitTime - sPlcEnterTime;
	NVRAM0[SPREG_SCAN_TIME] = (uint16_t)sPlcScanTime;
}




