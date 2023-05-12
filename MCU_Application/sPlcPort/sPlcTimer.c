#include "sPlc.h"
/*****************************************************************************/
uint32_t sPlcTick;
/*****************************************************************************/
void sPlcTimerInit(void){//硬件sTimer计时器初始化
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
	printf("%s,%d,%s:splc timer init......\n",__FILE__, __LINE__, __func__);
}
void sPlcTimerDisable(void) {//SPLC关闭计时器
	HAL_TIM_Base_Stop_IT(&htim14);
}
void sPlcTimerEnable(void) {//SPLC打开计时器
	HAL_TIM_Base_Start_IT(&htim14);
}
void sPlcTimerIsr(void){//硬件sTimer计时器中断 1mS
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
		TD_1000MS_SP = 1;
		TimerCounter_1000mS = 0;
	}
	if(TimerCounter_60000mS > 60000){//1分钟计时
		TD_60000MS_SP = 1;
		TimerCounter_60000mS = 0;
	}
	
	TimerCounter_10mS ++;//10毫秒
	TimerCounter_100mS ++;//100毫秒
	TimerCounter_200mS ++;//200毫秒
	TimerCounter_500mS ++;//500毫秒
	TimerCounter_1000mS ++;//1秒
	TimerCounter_60000mS ++;//1分钟
	
	sPlcTick ++;
}

