#include "sPlcTimer.h"
/*****************************************************************************/
extern TIM_HandleTypeDef htim14;
/*****************************************************************************/
uint32_t sPlcTick;
/*****************************************************************************/
void initSplcTimer(void){//硬件sTimer计时器初始化
	htim14.Instance = TIM14;
	htim14.Init.Prescaler = 96;
	htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim14.Init.Period = 1000;
	htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim14) != HAL_OK){
		Error_Handler();
	}
	HAL_TIM_Base_Start_IT(&htim14);
	TD_10MS_SP = 0;
	TD_100MS_SP = 0;
	TD_200MS_SP = 0;
	TD_500MS_SP = 0;
	TD_1000MS_SP = 0;
	TimerCounter_10mS = 0;//10毫秒
	TimerCounter_100mS = 0;//100毫秒
	TimerCounter_200mS = 0;//200毫秒
	TimerCounter_500mS = 0;//500毫秒
	TimerCounter_1000mS = 0;//1秒
	TimerCounter_60000mS = 0;//1分钟
	sPlcTick = 0;
}
void disableSplcTimer(void) {//SPLC关闭计时器
	HAL_TIM_Base_Stop_IT(&htim14);
}
void enableSplcTimer(void) {//SPLC打开计时器
	HAL_TIM_Base_Start_IT(&htim14);
}
void sPlcTimerIsr(void){//硬件sTimer计时器中断 1mS
	uint16_t i;
	uint32_t temp;
	for(i = TD_1MS_START;i <= TD_1MS_END;i ++){
		if(LD(T_1MS_ENA_START * 16 + (i - TD_1MS_START))){
			if(NVRAM0[i] < SHRT_MAX){
				NVRAM0[i] ++;
			}
		}
		else{
			NVRAM0[i] = 0;
		}
	}
	if(TimerCounter_10mS > 10){//10mS计算
		for(i = TD_10MS_START;i <= TD_10MS_END;i ++){
			if(LD(T_10MS_ENA_START * 16 + (i - TD_10MS_START))){
				if(NVRAM0[i] < SHRT_MAX){
					NVRAM0[i] ++;
				}
			}
			else{
				NVRAM0[i] = 0;
			}
		}
		TD_10MS_SP = 1;
		TimerCounter_10mS = 0;
	}
	if(TimerCounter_100mS > 100){//100ms计算
		for(i = TD_100MS_START;i < TD_100MS_END;i ++){
			if(LD(T_100MS_ENA_START * 16 + (i - TD_100MS_START))){
				if(NVRAM0[i] < SHRT_MAX){
					NVRAM0[i] ++;
				}
			}
			else{
				NVRAM0[i] = 0;
			}
		}
		TD_100MS_SP = 1;
		TimerCounter_100mS = 0;
	}
	if(TimerCounter_200mS > 200){//200ms计算
		TD_200MS_SP = 1;
		TimerCounter_200mS = 0;
	}
	if(TimerCounter_500mS > 500){//500ms计算
		TD_500MS_SP = 1;
		TimerCounter_500mS = 0;
	}
	if(TimerCounter_1000mS > 1000){//1000ms计算
		temp = *(uint32_t*)(NVRAM0 + SPREG_TICK_L);
		if(temp < UINT_MAX){
			temp ++;
			*(uint32_t*)(NVRAM0 + SPREG_TICK_L) = temp;
		}
		TD_1000MS_SP = 1;
		TimerCounter_1000mS = 0;
	}
	if(TimerCounter_60000mS > 60000){//1分钟计时
		TD_60000MS_SP = 1;
		TimerCounter_60000mS = 0;
	}
	
	if(NVRAM0[SPREG_LINK_SEND_TCOUNTER] < SHRT_MAX){
		NVRAM0[SPREG_LINK_SEND_TCOUNTER] ++;
	}
	if(NVRAM0[SPREG_LINK_RECE_TCOUNTER] < SHRT_MAX){
		NVRAM0[SPREG_LINK_RECE_TCOUNTER] ++;
	}
	TimerCounter_10mS ++;//10毫秒
	TimerCounter_100mS ++;//100毫秒
	TimerCounter_200mS ++;//200毫秒
	TimerCounter_500mS ++;//500毫秒
	TimerCounter_1000mS ++;//1秒
	TimerCounter_60000mS ++;//1分钟
	
	sPlcTick ++;
}

