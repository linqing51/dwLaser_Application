/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
//TIM11->璁℃椂
#include "sPlc.h"
/*****************************************************************************/
int8_t LaserOn_635;
int8_t LaserOn_535;
int8_t LaserTimer_Mode;
int16_t LaserTimer_TCounter;
int16_t LaserTimer_TMate;
int16_t LaserTimer_TOvertime;
int16_t LaserTimer_PCounter;
int16_t LaserTimer_PMate;
int16_t LaserTimer_POvertime;
int16_t LaserTimer_ReleaseTime;
int16_t LaserTimer_ReleaseCounter;
int8_t LaserFlag_Emiting;//婵€鍏夊彂灏勪腑鏍囧織
int8_t LaserFlag_Request;//婵€鍏夊彂灏勮剼韪忚姹?
int8_t LaserFlag_Emitover;//婵€鍏夊彂灏勫畬姣曟爣蹇?
/*****************************************************************************/
void laserStop(void);
void laserStart(void);
/*****************************************************************************/
#if CONFIG_SPLC_USING_LASER_TEST == 1
void sPlcLaserTimerTestBench(uint8_t st){//LASER婵€鍏夊彂灏勬祴璇?
	EDLAR();
	if(st == 0){//CH0 CW妯″紡娴嬭瘯
		STLAR();
	}
	if(st == 1){//CH1 CW妯″紡娴嬭瘯
		STLAR();
	}
	if(st == 2){//CH0+CH1 CW妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_CW;
		STLAR();
	}
	if(st == 3){//CH0 SP妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_TMate = 5000;//婵€鍏夎剦鍐叉鑴夊 10mS
		STLAR();
	}
	if(st == 4){//CH1 SP妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_TMate = 25;//婵€鍏夎剦鍐叉鑴夊 10mS
		STLAR();
	}
	if(st == 5){//CH0+CH1 SP妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_TMate = 30;//婵€鍏夎剦鍐叉鑴夊 10mS
		STLAR();
	}
	if(st == 6){//CH0 MP妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_TMate = 30;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 90;//婵€鍏夎剦鍐插懆鏈?25mS
		STLAR();
	}
	if(st == 7){//CH1 MP妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_TMate = 74;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 96;//婵€鍏夎剦鍐插懆鏈?25mS
		STLAR();
	}
	if(st == 8){//CH0+CH1 MP妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_TMate = 53;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 130;//婵€鍏夎剦鍐插懆鏈?25mS
		STLAR();
	}
	if(st == 9){//CH0 GP妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_TMate = 10;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 15;//婵€鍏夎剦鍐插懆鏈?25mS
		LaserTimer_PMate = 10;//10涓剦鍐?
		LaserTimer_POvertime = 33;//闂撮殧33mS
		STLAR();
	}
	if(st == 10){//CH1 GP妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_TMate = 19;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 86;//婵€鍏夎剦鍐插懆鏈?25mS
		LaserTimer_PMate = 12;//10涓剦鍐?
		LaserTimer_POvertime = 43;//闂撮殧33mS
		STLAR();
	}
	if(st == 11){//CH0+CH1 GP妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_TMate = 5;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 24;//婵€鍏夎剦鍐插懆鏈?25mS
		LaserTimer_PMate = 6;//10涓剦鍐?
		LaserTimer_POvertime = 60;//闂撮殧33mS
		STLAR();
	}	
	if(st == 12){//CH0 DERMA妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_TMate = 10;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 15;//婵€鍏夎剦鍐插懆鏈?25mS
		STLAR();
	}
	if(st == 13){//CH1 DERMA妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_TMate = 19;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 86;//婵€鍏夎剦鍐插懆鏈?25mS
		STLAR();
	}
	if(st == 14){//CH0+CH1 DERMA妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_TMate = 5;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 24;//婵€鍏夎剦鍐插懆鏈?25mS
		STLAR();
	}	
	if(st == 15){//CH0 SIGNAL妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		LaserTimer_TMate = 10;//婵€鍏夎剦鍐叉鑴夊 10mS
		LaserTimer_TOvertime = 15;//婵€鍏夎剦鍐插懆鏈?25mS
		STLAR();
	}
	if(st == 16){//CH1 SIGNAL妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		STLAR();
	}
	if(st == 17){//CH0+CH1 SIGNAL妯″紡娴嬭瘯
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		STLAR();
	}
}

#endif
void STLAR(void){//寮€濮嬪彂灏勮剦鍐?
	printf("%s,%d,%s:laser start!\n",__FILE__, __LINE__, __func__);
	if((NVRAM0[DM_SCHEME_CLASSIFY] == SCHEME_PROCTOLOGY) && (NVRAM0[DM_SCHEME_INDEX] <= 2)){
		NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_5;//PROCTOLOGY涓撶敤
	}
	else{
		if(LD(R_ACOUSTIC_ENABLE)){
			NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_4;//BEEP + 鎻愮ず闊?CW妯″紡
		}
		else{
			NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_2;//婵€鍏夊彂灏勫浐瀹氶棿闅?
		}
	}
	NVRAM0[SPREG_BEEM_FREQ] = CONFIG_DEFAULT_SPK_FREQ;
	NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
	NVRAM0[SPREG_BEEM_COUNTER]= 0;
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserTimer_ReleaseCounter = 0x0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = false;
	__HAL_TIM_SET_COUNTER(&CONFIG_LASER_TIM_HANDLE, 0x0);//娓呴浂璁℃暟鍊?
	HAL_TIM_Base_Start_IT(&CONFIG_LASER_TIM_HANDLE);//鎵撳紑璁℃椂鍣?
}
void EDLAR(void){//鍋滄鍙戝皠鑴夊啿
	printf("%s,%d,%s:laser stop!\n",__FILE__, __LINE__, __func__);
	__HAL_TIM_SET_COUNTER(&CONFIG_LASER_TIM_HANDLE, 0x0);//娓呴浂璁℃暟鍊?
	HAL_TIM_Base_Stop_IT(&CONFIG_LASER_TIM_HANDLE);//鍋滄璁℃椂鍣?
	laserStop();//鍏抽棴DAC杈撳嚭
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = true;
}
void sPlcLaserInit(void){//婵€鍏夎剦鍐插姛鑳藉垵濮嬪寲
	SET_LASER_CH0_OFF;
	SET_LASER_CH1_OFF;
	setRedLaserPwm(0);
	//璁惧畾璁℃椂鍣?
	LaserTimer_Mode = 0;
	LaserTimer_TCounter = 0;
	LaserTimer_TMate = 0;
	LaserTimer_TOvertime = 0;
	LaserTimer_PCounter = 0;
	LaserTimer_PMate = 0;
	LaserTimer_POvertime = 0;
	LaserTimer_ReleaseTime = 0;
	LaserTimer_ReleaseCounter = 0;
	LaserFlag_Emiting = false;//婵€鍏夊彂灏勪腑鏍囧織
	LaserFlag_Emitover = false;
	printf("%s,%d,%s:laser timer init......\n",__FILE__, __LINE__, __func__);
}
void laserStart(void){//鎸夐€氶亾閫夋嫨鎵撳紑婵€鍏?
	if(LaserFlag_Emiting == false){
		if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH0){
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1) ||\
		defined(MODEL_PVGLS_10W_1940_A1)
			SET_LASER_CH0_ON;
#endif
#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
			SET_LASER_CH0_ON;
			SET_LASER_CH1_ON;
#endif
#if defined(LYPE_MCU_1V0_20260106)
			SET_LASER_CH0_ON;
			SET_LASER_CH1_ON;
			SET_LASER_CH2_ON;
			SET_LASER_CH3_ON;
#endif			
		}
		if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_CH1){
#if defined(LDR2P1_G5_A1_20250731_DUAL) ||\
		defined(LDR2P1_G5_A1_20250910_DUAL) ||\
		defined(LDR2P1_G5_A1_20250731_TRIP) ||\
		defined(LDR2P1_G5_A1_20250910_TRIP) ||\
		defined(MODEL_PVGLS_15W_1470_A0) ||\
		defined(MODEL_PVGLS_15W_1470_A1) ||\
		defined(MODEL_PVGLS_10W_1940_A1)
			SET_LASER_CH1_ON;
#endif
#if defined(LDR2P1_RASPI_G9_A1_20250322_DUAL)
			SET_LASER_CH2_ON;
#endif
#if defined(LYPE_MCU_1V0_20260106)
			SET_LASER_CH4_ON;
#endif
		}
		if(NVRAM0[EM_LASER_CHANNEL_SELECT] == LASER_CHANNEL_RAIM){//鎵撳紑绾㈡縺鍏?
			setRedLaserPwm(NVRAM0[EM_LASER_POWER_635] * 1000);
		}
		LaserFlag_Emiting = true;
		SET_BEEM_LED_ON;
	}
}
void laserStop(void){//鎸夐€氶亾閫夋嫨鍏抽棴婵€鍏?
	if(LaserFlag_Emiting == true){
		SET_LASER_CH0_OFF;		
		SET_LASER_CH1_OFF;
		SET_LASER_CH2_OFF;
		SET_LASER_CH3_OFF;
		SET_LASER_CH4_OFF;
		SET_LASER_CH5_OFF;
		SET_LASER_CH6_OFF;
		SET_LASER_CH7_OFF;
		NVRAM0[SPREG_DAC_16] = NVRAM0[DM_RAIM_BRG] * deviceConfig.redAimGain;
		UPDAC16();	
		LaserFlag_Emiting = false;
		SET_BEEM_LED_OFF;
	}
}
__forceinline void sPlcLaserTimerIsr(void){//TIM 涓柇鍥炶皟 婵€鍏夊彂灏?
	switch(LaserTimer_Mode){
		case LASER_MODE_CW:{//CW杩炵画妯″紡
			if(LaserTimer_TCounter == 0){
					laserStart();
					LaserTimer_TCounter ++;
			}
			break;
		}
		case LASER_MODE_MP:{//MP澶氳剦鍐叉ā寮?
			if((LaserTimer_TCounter >= 0) && (LaserTimer_TCounter < LaserTimer_TMate)){//婵€鍏夊彂灏?
				laserStart();
			}
			if((LaserTimer_TCounter >= LaserTimer_TMate) && (LaserTimer_TCounter < LaserTimer_TOvertime)){//璁℃椂鍣ㄥ尮閰?
				laserStop();
			}
			if(LaserTimer_TCounter >= LaserTimer_TOvertime){//璁℃椂鍣ㄦ孩鍑?
				LaserTimer_TCounter = -1;//娓呴浂
			}	
			LaserTimer_TCounter ++;
			break;
		}
		default:break;
	}
}
	
void setRedLaserPwm(int16_t pwm){//璁剧疆绾㈡縺鍏夊崰绌烘瘮 0-100
	if(pwm < 0){
		pwm = 0;
	}
	SET_RAIM_TIM_PWM(pwm);
	if(pwm != 0){
		SET_RAIM_SHDN_ON;
		__nop();__nop();__nop();__nop();__nop();
		SET_RAIM_TIM_ON;//鎵撳紑TIM
		LaserOn_635 = true;
	}
	else{
		SET_RAIM_TIM_OFF;//鍏抽棴TIM
		__nop();__nop();__nop();__nop();__nop();
		SET_RAIM_SHDN_OFF;
		LaserOn_635 = false;
	}
#if (CONFIG_DEBUG_AIM == 1)
	printf("%s,%d,%s:set red laser(635) pwm:%d\n",__FILE__, __LINE__, __func__, pwm);
#endif
}

void setGreenLaserPwm(int16_t pwm){//璁剧疆缁挎縺鍏夊崰绌烘瘮
	if(pwm < 0){
		pwm = 0;
	}
	SET_GAIM_TIM_PWM(pwm);
	if(pwm != 0){
		SET_GAIM_SHDN_ON;
		__nop();__nop();__nop();__nop();__nop();
		SET_GAIM_TIM_ON;//鎵撳紑TIM
		LaserOn_535 = true;
	}
	else{
		SET_GAIM_TIM_OFF;//鍏抽棴TIM
		__nop();__nop();__nop();__nop();__nop();
		SET_GAIM_SHDN_OFF;
		LaserOn_535 = false;
	}
#if (CONFIG_DEBUG_AIM == 1)
	printf("%s,%d,%s:set laser(535) pwm:%d\n",__FILE__, __LINE__, __func__, pwm);
#endif	
}





