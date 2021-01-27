#include "sPlcIoOut.h"
/*****************************************************************************/
void outputInit(void){//IO输出初始化
	NVRAM0[Y_START] = 0x0;
	HAL_GPIO_WritePin(FAN5V_OUT_GPIO_Port, FAN5V_OUT_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(HEN_OUT1_GPIO_Port, HEN_OUT1_Pin, GPIO_PIN_SET);//FAN 24V
	HAL_GPIO_WritePin(HEN_OUT0_GPIO_Port, HEN_OUT0_Pin, GPIO_PIN_RESET);//TEC
	setRedLedBrightness(CONFIG_SPLC_RLED_OFF_DC);
	setGreenLedBrightness(CONFIG_SPLC_GLED_OFF_DC);
	setBlueLedBrightness(CONFIG_SPLC_BLED_OFF_DC);
}

void outputRefresh(void){//设置输出IO
	//YOUT0 5V 风扇开关
	if(LDP(Y_FAN_SP)){
		HAL_GPIO_WritePin(FAN5V_OUT_GPIO_Port, FAN5V_OUT_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set y0\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_FAN_SP)){
		HAL_GPIO_WritePin(FAN5V_OUT_GPIO_Port, FAN5V_OUT_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset y0\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT1 24V 风扇开关
	if(LDP(Y_FAN_LD)){
		HAL_GPIO_WritePin(HEN_OUT1_GPIO_Port, HEN_OUT1_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set y1\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_FAN_LD)){
		HAL_GPIO_WritePin(HEN_OUT1_GPIO_Port, HEN_OUT1_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset y1\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT2 制冷开关
	if(LDP(Y_TEC)){
		HAL_GPIO_WritePin(HEN_OUT0_GPIO_Port, HEN_OUT0_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set y2\n",__FILE__, __LINE__, __func__);
#endif	
	}
	if(LDN(Y_TEC)){
		HAL_GPIO_WritePin(HEN_OUT0_GPIO_Port, HEN_OUT0_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset y2\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT3 绿灯
	if(LDP(Y_GLED)){
		setGreenLedBrightness(CONFIG_SPLC_GLED_ON_DC);//设置红灯亮度
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set y3\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_GLED)){
		setGreenLedBrightness(CONFIG_SPLC_GLED_OFF_DC);//设置红灯亮度
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset y3\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT4 红灯
	if(LDP(Y_RLED)){
		setRedLedBrightness(CONFIG_SPLC_RLED_ON_DC);//设置红灯亮度
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set y4\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_RLED)){
		setRedLedBrightness(CONFIG_SPLC_RLED_OFF_DC);//设置红灯亮度
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset y4\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT5 蓝灯
	if(LDP(Y_BLED)){
		setBlueLedBrightness(CONFIG_SPLC_BLED_ON_DC);//设置红灯亮度
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set y5\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_BLED)){
		setBlueLedBrightness(CONFIG_SPLC_BLED_OFF_DC);//设置红灯亮度
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset y5\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT6 LCD电源
	if(LDP(Y_LCDPWR)){
		HAL_GPIO_WritePin(LCD_PWR_GPIO_Port, LCD_PWR_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set y6\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_LCDPWR)){
		HAL_GPIO_WritePin(LCD_PWR_GPIO_Port, LCD_PWR_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset y6\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT7 板载LED RUN
	if(LDP(Y_RUN_LED)){
		HAL_GPIO_WritePin(SYS_LED_RUN_GPIO_Port, SYS_LED_RUN_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set y7\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_RUN_LED)){
		HAL_GPIO_WritePin(SYS_LED_RUN_GPIO_Port, SYS_LED_RUN_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset y7\n",__FILE__, __LINE__, __func__);
#endif
	}
	//YOUT8 板载LED ERR
	if(LDP(Y_ERR_LED)){
		HAL_GPIO_WritePin(SYS_LED_ERR_GPIO_Port, SYS_LED_ERR_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set y8\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_ERR_LED)){
		HAL_GPIO_WritePin(SYS_LED_ERR_GPIO_Port, SYS_LED_ERR_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset y8\n",__FILE__, __LINE__, __func__);
#endif
	}
}




