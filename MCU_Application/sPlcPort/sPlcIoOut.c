#include "sPlcIoOut.h"
/*****************************************************************************/
void outputInit(void){//IO输出初始化
	NVRAM0[Y_START] = 0x0;
	HAL_GPIO_WritePin(FAN_SP_GPIO_Port, FAN_SP_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(FAN_LD_GPIO_Port, FAN_LD_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(RLED_OUT_GPIO_Port, RLED_OUT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GLED_OUT_GPIO_Port, GLED_OUT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(BLED_OUT_GPIO_Port, BLED_OUT_Pin, GPIO_PIN_RESET);
}

void outputRefresh(void){//设置输出IO
	//YOUT0 5V 风扇开关
	if(LDP(Y_FAN_SP)){
		HAL_GPIO_WritePin(FAN_SP_GPIO_Port, FAN_SP_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y0 FAN power supply\n");
#endif
	}
	if(LDN(Y_FAN_SP)){
		HAL_GPIO_WritePin(FAN_SP_GPIO_Port, FAN_SP_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y0 FAN power supply\n");
#endif
	}
	
	//YOUT1 24V 风扇开关
	if(LDP(Y_FAN_LD)){
		HAL_GPIO_WritePin(FAN_LD_GPIO_Port, FAN_LD_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y1 FAN laser cool\n");
#endif
	}
	if(LDN(Y_FAN_LD)){
		HAL_GPIO_WritePin(FAN_LD_GPIO_Port, FAN_LD_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y1 FAN laser cool\n");
#endif
	}
	
	//YOUT2 制冷开关
	if(LDP(Y_TEC)){
		HAL_GPIO_WritePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y2 TEC\n");
#endif	
	}
	if(LDN(Y_TEC)){
		HAL_GPIO_WritePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y2 TEC\n");
#endif
	}
	
	//YOUT3 绿灯
	if(LDP(Y_GLED)){
		HAL_GPIO_WritePin(GLED_OUT_GPIO_Port, GLED_OUT_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y3 GLED\n");
#endif
	}
	if(LDN(Y_GLED)){
		HAL_GPIO_WritePin(GLED_OUT_GPIO_Port, GLED_OUT_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y3 GLED\n");
#endif
	}
	
	//YOUT4 红灯
	if(LDP(Y_RLED)){
		HAL_GPIO_WritePin(RLED_OUT_GPIO_Port, RLED_OUT_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y4 RLED\n");
#endif
	}
	if(LDN(Y_RLED)){
		HAL_GPIO_WritePin(RLED_OUT_GPIO_Port, RLED_OUT_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y4 RLED\n");
#endif
	}
	
	//YOUT5 蓝灯
	if(LDP(Y_BLED)){
		HAL_GPIO_WritePin(BLED_OUT_GPIO_Port, BLED_OUT_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y5 BLED\n");
#endif
	}
	if(LDN(Y_BLED)){
		HAL_GPIO_WritePin(BLED_OUT_GPIO_Port, BLED_OUT_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y5 BLED\n");
#endif
	}
	
	//YOUT6 LCD电源
	if(LDP(Y_LCDPWR)){
		HAL_GPIO_WritePin(LCD_PWR_GPIO_Port, LCD_PWR_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y6 LCD PWR\n");
#endif
	}
	if(LDN(Y_LCDPWR)){
		HAL_GPIO_WritePin(LCD_PWR_GPIO_Port, LCD_PWR_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y6 LCD PWR\n");
#endif
	}
}


