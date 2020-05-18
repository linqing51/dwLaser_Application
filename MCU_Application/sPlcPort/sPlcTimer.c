#include "sPlcTimer.h"
#include "main.h"
/*****************************************************************************/
extern TIM_HandleTypeDef htim7;
/*****************************************************************************/
void initSplcTimer(void){//硬件sTimer计时器初始化
	HAL_TIM_Base_Start_IT(&htim7);
	TD_10MS_SP = 0;
	TD_100MS_SP = 0;
	TD_1000MS_SP = 0;
	TimerCounter_1mS = 0;
	TimerCounter_10mS = 0;
	TimerCounter_100mS = 0;
}
void sPlcTimerIsr(void){//硬件sTimer计时器中断 10mS
	uint16_t i;
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
	if(TimerCounter_1mS >= 10){//10mS计算
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
		if(TD_10MS_SP < CHAR_MAX){
			TD_10MS_SP ++;
		}
		TimerCounter_10mS ++;
		TimerCounter_1mS = 0;
	}
	if(TimerCounter_10mS >= 10){//100ms计算
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
	}
//#if CONFIG_SPLC_USING_ADC == 1
//	chipAdcProcess();//ADC扫描
//#endif
	TimerCounter_1mS ++;
}


