#include "sPlcTimer.h"
#include "main.h"
/*****************************************************************************/
extern TIM_HandleTypeDef htim7;
/*****************************************************************************/
uint32_t sPlcTick;
/*****************************************************************************/
void initSplcTimer(void){//硬件sTimer计时器初始化
	HAL_TIM_Base_Start_IT(&htim7);
	TD_10MS_SP = 0;
	TD_100MS_SP = 0;
	TD_1000MS_SP = 0;
	TimerCounter_1mS = 0;
	TimerCounter_10mS = 0;
	TimerCounter_100mS = 0;
	sPlcTick = 0;
}
void sPlcTimerIsr(void){//硬件sTimer计时器中断 10mS
	uint16_t i;
	uint32_t temp;
	for(i = 0;i <= TD_1MS_SIZE;i ++){
		if(LD(TYPE_T_1MS_ENA, i)){
			if(NVRAM0_TD_1MS[i] < SHRT_MAX){
				NVRAM0_TD_1MS[i] ++;
			}
		}
		else{
			NVRAM0_TD_1MS[i] = 0;
		}
	}
	if(TimerCounter_1mS >= 10){//10mS计算
		for(i = 0;i <= TD_10MS_SIZE;i ++){
			if(LD(TYPE_T_10MS_ENA, i)){
				if(NVRAM0_TD_10MS[i] < SHRT_MAX){
					NVRAM0_TD_10MS[i] ++;
				}
			}
			else{
				NVRAM0_TD_10MS[i] = 0;
			}
		}
		if(TD_10MS_SP < CHAR_MAX){
			TD_10MS_SP ++;
		}
		TimerCounter_10mS ++;
		TimerCounter_1mS = 0;
	}
	if(TimerCounter_10mS >= 10){//100ms计算
		for(i = 0;i < TD_100MS_SIZE;i ++){
			if(LD(TYPE_T_100MS_ENA,  i)){
				if(NVRAM0_TD_100MS[i] < SHRT_MAX){
					NVRAM0_TD_100MS[i] ++;
				}
			}
			else{
				NVRAM0_TD_100MS[i] = 0;
			}
		}
		if(TD_100MS_SP < CHAR_MAX){
			TD_100MS_SP ++;
		}
		TimerCounter_100mS ++;
		TimerCounter_10mS = 0;
	}
	if(TimerCounter_100mS >= 10){
		if(TD_1000MS_SP < CHAR_MAX){
			TD_1000MS_SP ++;
		}
		TimerCounter_100mS = 0;
		temp = *(uint32_t*)(NVRAM0_SPREG + SPREG_TICK_L);
		if(temp < UINT_MAX){
			temp ++;
			*(uint32_t*)(NVRAM0_SPREG + SPREG_TICK_L) = temp;
		}
	}
	TimerCounter_1mS ++;
	sPlcTick ++;
}


