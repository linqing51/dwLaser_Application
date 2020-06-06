#include "sPlc.h"
/*****************************************************************************/
int16_t NVRAM0_MR[MR_SIZE];//线圈 保持
int16_t NVRAM1_MR[MR_SIZE];//线圈 保持
/*****************************************************************************/
int16_t NVRAM0_DM[DM_SIZE];//数据寄存器
int16_t NVRAM1_DM[DM_SIZE];//数据寄存器
/*****************************************************************************/
int16_t NVRAM0_R[R_SIZE];//线圈非保持
int16_t NVRAM1_R[R_SIZE];//线圈非保持
/*****************************************************************************/
int16_t NVRAM0_EM[EM_SIZE];//数据寄存器非保持
/*****************************************************************************/
int16_t NVRAM0_T_1MS[T_1MS_SIZE];//延时线圈1MS
int16_t NVRAM1_T_1MS[T_1MS_SIZE];//延时线圈1MS
int16_t NVRAM0_T_10MS[T_10MS_SIZE];//延时线圈10MS
int16_t NVRAM1_T_10MS[T_10MS_SIZE];//延时线圈10MS
int16_t NVRAM0_T_100MS[T_100MS_SIZE];//延时线圈100MS
int16_t NVRAM1_T_100MS[T_100MS_SIZE];//延时线圈100MS
/*****************************************************************************/
int16_t NVRAM0_T_1MS_ENA[T_1MS_ENA_SIZE];//延时器使能1MS
int16_t NVRAM1_T_1MS_ENA[T_1MS_ENA_SIZE];//延时器使能1MS
int16_t NVRAM0_T_10MS_ENA[T_10MS_ENA_SIZE];//延时器使能10MS
int16_t NVRAM1_T_10MS_ENA[T_10MS_ENA_SIZE];//延时器使能10MS
int16_t NVRAM0_T_100MS_ENA[T_100MS_ENA_SIZE];//延时器使能100MS
int16_t NVRAM1_T_100MS_ENA[T_100MS_ENA_SIZE];//延时器使能100MS
/*****************************************************************************/
int16_t NVRAM0_TD_1MS[TD_1MS_SIZE];//延时计时器1MS
int16_t NVRAM0_TD_10MS[TD_10MS_SIZE];//延时计时器10MS
int16_t NVRAM0_TD_100MS[TD_100MS_SIZE];//延时计时器100MS
/*****************************************************************************/
int16_t NVRAM0_X[X_SIZE];//输入位寄存器
int16_t NVRAM1_X[X_SIZE];//输入位寄存器
/*****************************************************************************/
int16_t NVRAM0_Y[Y_SIZE];//输出位寄存器
int16_t NVRAM1_Y[Y_SIZE];//输出位寄存器
/*****************************************************************************/
int16_t NVRAM0_SPREG[SPREG_SIZE];//特殊寄存器
/*****************************************************************************/
int16_t NVRAM0_SPCOIL[SPCOIL_SIZE];//特殊线圈
int16_t NVRAM1_SPCOIL[SPCOIL_SIZE];//特殊线圈
/*****************************************************************************/
int16_t NVRAM0_TMP[TMP_SIZE];//临时寄存器
/*****************************************************************************/
int16_t FDRAM0[FDRAM_SIZE];//存档寄存器
/*****************************************************************************/
uint8_t TimerCounter_1mS = 0;
uint8_t TimerCounter_10mS = 0;
uint8_t TimerCounter_100mS = 0;
uint8_t TD_10MS_SP = 0;
uint8_t TD_100MS_SP = 0;
uint8_t TD_1000MS_SP = 0;
uint32_t sPlcEnterTime, sPlcExitTime, sPlcScanTime;
/******************************************************************************/
void assertAddress(uint8_t tp, uint16_t adr){//检查地址
#if CONFIG_SPLC_ASSERT == 1
	adr += 1;
	switch(tp){
		case TYPE_MR:{
			if(adr > (MR_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_DM:{
			if(adr > DM_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_R:{
			if(adr > (R_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_EM:{
			if(adr > EM_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_T_1MS:{
			if(adr > (T_1MS_SIZE * 16)){
				while(1);
			}
		}
		case TYPE_T_10MS:{
			if(adr > (T_10MS_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_T_100MS:{
			if(adr > (T_100MS_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_T_1MS_ENA:{
			if(adr > (T_1MS_ENA_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_T_10MS_ENA:{
			if(adr > (T_10MS_ENA_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_T_100MS_ENA:{
			if(adr > (T_100MS_ENA_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_TD_1MS:{
			if(adr > TD_1MS_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_TD_10MS:{
			if(adr > TD_10MS_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_TD_100MS:{
			if(adr > TD_100MS_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_X:{
			if(adr > (TYPE_X_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_Y:{
			if(adr > (TYPE_Y_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_SPREG:{
			if(adr > TYPE_SPREG_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_SPCOIL:{
			if(adr >> (TYPE_SPCOIL_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_TMP:{
			if(adr > TYPE_TMP_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_FDRAM:{
			if(adr > TYPE_FDRAM_SIZE){
				while(1);
			}
			break;
		}
		default:break;
	}
#endif
}
void loadNvram(void){//从EPROM中载入NVRAM
	uint16_t i;
#if CONFIG_SPLC_USING_EPROM == 1
	epromRead(CONFIG_EPROM_MR_START, (uint8_t*)NVRAM0_MR, (MR_SIZE * 2));//从EPROM中恢复MR
	epromRead(CONFIG_EPROM_DM_START, (uint8_t*)NVRAM0_DM, (DM_SIZE * 2));//从EPROM中恢复DM
#endif
	memcpy((uint8_t*)NVRAM1_MR, (uint8_t*)NVRAM0_MR, (MR_SIZE * 2));
	memcpy((uint8_t*)NVRAM1_DM, (uint8_t*)NVRAM0_DM, (DM_SIZE * 2));
}
void saveNvram(void){//强制将NVRAM存入EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	epromWrite(CONFIG_EPROM_MR_START, (uint8_t*)NVRAM0_MR, (MR_SIZE * 2));//将MR存入EPROM
	epromWrite(CONFIG_EPROM_DM_START, (uint8_t*)NVRAM0_DM, (DM_SIZE * 2));//将DM存入EPROM
#endif
}
void updateNvram(void){//更新NVRAM->EPROM
	uint8_t *sp0, *sp1;
	uint16_t i;
	//储存MR
	sp0 = (uint8_t*)NVRAM0_MR;
	sp1 = (uint8_t*)NVRAM1_MR;
	for(i = CONFIG_EPROM_MR_START;i < (MR_SIZE * 2);i ++){//储存MR
		if(*sp0 != *sp1){
#if CONFIG_SPLC_USING_EPROM == 1
			epromWriteByte(i, *sp0);
#endif
		}
		sp0 ++;
		sp1 ++;
	}
	//储存DM
	sp0 = (uint8_t*)NVRAM0_DM;
	sp1 = (uint8_t*)NVRAM1_DM;
	for(i = CONFIG_EPROM_DM_START;i < (DM_SIZE * 2);i ++){//储存DM
		if(*sp0 != *sp1){
#if CONFIG_SPLC_USING_EPROM == 1
			epromWriteByte(i, *sp0);
#endif
		}
		sp0 ++;
		sp1 ++;
	}
	memcpy((uint8_t*)(NVRAM1_MR),          (uint8_t*)(NVRAM0_MR),          (MR_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_DM),          (uint8_t*)(NVRAM0_DM),          (DM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_R),           (uint8_t*)(NVRAM0_R),           (R_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_1MS),       (uint8_t*)(NVRAM0_T_1MS),       (T_1MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_10MS),      (uint8_t*)(NVRAM0_T_10MS),      (T_10MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_100MS),     (uint8_t*)(NVRAM0_T_100MS),     (T_100MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_1MS_ENA),   (uint8_t*)(NVRAM0_T_1MS_ENA),   (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_10MS_ENA),  (uint8_t*)(NVRAM0_T_10MS_ENA),  (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_100MS_ENA), (uint8_t*)(NVRAM0_T_100MS_ENA), (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_X_SIZE),      (uint8_t*)(NVRAM0_X_SIZE),      (X_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_Y_SIZE),      (uint8_t*)(NVRAM0_Y_SIZE),      (Y_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_SPCOIL),      (uint8_t*)(NVRAM0_SPCOIL),      (SPCOIL_SIZE * 2));
}
void clearNvram(void){//清除NVRAM数据	
	uint16_t i = 0;
	enterSplcIsr();
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = CONFIG_EPROM_MR_START; i< (MR_SIZE * 2);i ++){
		epromWriteByte(i, 0x00);
	}
	for(i = CONFIG_EPROM_DM_START; i< (DM_SIZE * 2);i ++){
		epromWriteByte(i, 0x00);
	}
#endif
	memset((uint8_t*)(NVRAM0_MR), 			0x0, (MR_SIZE * 2));
	memset((uint8_t*)(NVRAM1_MR), 			0x0, (MR_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_DM), 			0x0, (DM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_DM), 			0x0, (DM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_R), 			0x0, (R_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_R), 			0x0, (R_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_EM), 			0x0, (EM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_EM), 			0x0, (EM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_1MS), 		0x0, (T_1MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_1MS), 		0x0, (T_1MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_10MS), 		0x0, (T_10MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_10MS), 		0x0, (T_10MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_100MS), 		0x0, (T_100MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_100MS), 		0x0, (T_100MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_1MS_ENA),   	0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_1MS_ENA),   	0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_10MS_ENA),  	0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_10MS_ENA),  	0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_100MS_ENA),  0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_100MS_ENA),  0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_X_SIZE),       0x0, (X_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_X_SIZE),       0x0, (X_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_Y_SIZE),       0x0, (Y_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_Y_SIZE),       0x0, (Y_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_SPCOIL),       0x0, (SPCOIL_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_SPCOIL),       0x0, (SPCOIL_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_TMP),          0x0, (TMP_SIZE * 2));
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
	epromRead(CONFIG_EPROM_FDRAM_START, (uint8_t*)FDRAM, (FDRAM_SIZE * 2));//从EPROM中恢复MR
	feedWatchDog();
#endif
}
void saveFdram(void){//强制将FDRAM存入EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	epromWrite(CONFIG_EPROM_FDRAM_START, (uint8_t*)FDRAM, (FDRAM_SIZE * 2));
	feedWatchDog();
#endif
}
void clearFdram(void){//清楚FDRAM数据
	uint16_t i;
	disableWatchDog();
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = CONFIG_EPROM_FDRAM_START; i< (FDRAM_SIZE * 2) ; i++){
#if CONFIG_SPLC_USING_EPROM == 1
		epromWriteByte(i, 0x0);
#endif
	}
#endif
	memset(FDRAM, 0x0, (FDRAM_SIZE * 2));//初始化FDRAM
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
	loadNvram();//上电恢复NVRAM
	SSET(SPCOIL_ON);
	RRES(SPCOIL_BEEM_ENABLE);
	NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_BEEM_FREQ;
	NVRAM0[SPREG_BEEM_DUTYCYCLE] = CONFIG_SPLC_DEFAULT_BEEM_DUTYCYCLE;
	NVRAM0[SPREG_BEEM_COUNTER] = 0;
	RRES(SPCOIL_AIM_ENABEL);
	NVRAM0[SPREG_AIM_DUTYCYCLE] = 0;
	NVRAM0[SPREG_RED_LED_DUTYCYCLE] = 0;
	NVRAM0[SPREG_GREEN_LED_DUTYCYCLE] = 0;
	NVRAM0[SPREG_BLUE_LED_DUTYCYCLE] = 0;
	NVRAM0[SPREG_MUSIC_VOLUME] = 0;									
	NVRAM0[SPREG_PLAYING_MUSIC_ID] = 0;							
	NVRAM0[SPREG_NEXT_MUSIC_ID] = 0;									
	NVRAM0[SPREG_CONTROL_MUSIC]	= CMD_MUSIC_STOP;									
#if CONFIG_SPLC_USING_IO_INPUT == 1
	inputInit();
#endif
#if CONFIG_SPLC_USING_IO_OUTPUT == 1
	outputInit();
#endif
#if CONFIG_SPLC_USING_DAC == 1	
	initChipDac();//初始化DAC模块
#endif
#if CONFIG_SPLC_USING_ADC == 1
	initChipAdc();//初始化ADC模块
#endif
#if CONFIG_SPLC_USING_LASER == 1
	sPlcLaserInit();
#endif
	SSET(SPCOIL_ON);
	SSET(SPCOIL_START_UP);
	NVRAM0[SPREG_IDENTITY] = CONFIG_SPLC_DEV;
#if CONFIG_SPLC_USING_DK25L == 1
	delayMs(100);
	DL25L_Init();//打开中断后运行
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




