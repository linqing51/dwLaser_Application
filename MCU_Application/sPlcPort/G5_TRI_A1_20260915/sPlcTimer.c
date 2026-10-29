/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "sPlc.h"
/*****************************************************************************/
uint32_t sPlcTick;
/*****************************************************************************/
void sPlcTimerInit(void){//纭欢sTimer璁℃椂鍣ㄥ垵濮嬪寲
	HAL_TIM_Base_Start_IT(&CONFIG_SPLC_TIM_HANDLE);
	TD_10MS_SP = 0;
	TD_100MS_SP = 0;
	TD_200MS_SP = 0;
	TD_500MS_SP = 0;
	TD_1000MS_SP = 0;
	TimerCounter_10mS = 0;//10姣
	TimerCounter_100mS = 0;//100姣
	TimerCounter_200mS = 0;//200姣
	TimerCounter_500mS = 0;//500姣
	TimerCounter_1000mS = 0;//1绉?
	TimerCounter_60000mS = 0;//1鍒嗛挓
	sPlcTick = 0;
	printf("%s,%d,%s:splc timer init......\n",__FILE__, __LINE__, __func__);
}
void sPlcTimerDisable(void) {//SPLC鍏抽棴璁℃椂鍣?
	HAL_TIM_Base_Stop_IT(&CONFIG_SPLC_TIM_HANDLE);
}
void sPlcTimerEnable(void) {//SPLC鎵撳紑璁℃椂鍣?
	HAL_TIM_Base_Start_IT(&CONFIG_SPLC_TIM_HANDLE);
}
__forceinline void sPlcTimerIsr(void){//纭欢sTimer璁℃椂鍣ㄤ腑鏂?1mS
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
	if(TimerCounter_10mS > 10){//10mS璁＄畻
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
	if(TimerCounter_100mS > 100){//100ms璁＄畻
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
	if(TimerCounter_200mS > 200){//200ms璁＄畻
		TD_200MS_SP = 1;
		TimerCounter_200mS = 0;
	}
	if(TimerCounter_500mS > 500){//500ms璁＄畻
		TD_500MS_SP = 1;
		TimerCounter_500mS = 0;
	}
	if(TimerCounter_1000mS > 1000){//1000ms璁＄畻
		TD_1000MS_SP = 1;
		TimerCounter_1000mS = 0;
	}
	if(TimerCounter_60000mS > 60000){//1鍒嗛挓璁℃椂
		TD_60000MS_SP = 1;
		TimerCounter_60000mS = 0;
	}
	
	TimerCounter_10mS ++;//10姣
	TimerCounter_100mS ++;//100姣
	TimerCounter_200mS ++;//200姣
	TimerCounter_500mS ++;//500姣
	TimerCounter_1000mS ++;//1绉?
	TimerCounter_60000mS ++;//1鍒嗛挓
	
	sPlcTick ++;
}

