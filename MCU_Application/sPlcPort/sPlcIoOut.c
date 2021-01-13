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
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y0 FAN power supply\n");
#endif
	}
	if(LDN(Y_FAN_SP)){
		HAL_GPIO_WritePin(FAN5V_OUT_GPIO_Port, FAN5V_OUT_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y0 FAN power supply\n");
#endif
	}
	
	//YOUT1 24V 风扇开关
	if(LDP(Y_FAN_LD)){
		HAL_GPIO_WritePin(HEN_OUT1_GPIO_Port, HEN_OUT1_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y1 FAN laser cool\n");
#endif
	}
	if(LDN(Y_FAN_LD)){
		HAL_GPIO_WritePin(HEN_OUT1_GPIO_Port, HEN_OUT1_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y1 FAN laser cool\n");
#endif
	}
	
	//YOUT2 制冷开关
	if(LDP(Y_TEC)){
		HAL_GPIO_WritePin(HEN_OUT0_GPIO_Port, HEN_OUT0_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y2 TEC\n");
#endif	
	}
	if(LDN(Y_TEC)){
		HAL_GPIO_WritePin(HEN_OUT0_GPIO_Port, HEN_OUT0_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y2 TEC\n");
#endif
	}
	
	//YOUT3 绿灯
	if(LDP(Y_GLED)){
		setGreenLedBrightness(CONFIG_SPLC_GLED_ON_DC);//设置红灯亮度
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y3 GLED\n");
#endif
	}
	if(LDN(Y_GLED)){
		setGreenLedBrightness(CONFIG_SPLC_GLED_OFF_DC);//设置红灯亮度
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y3 GLED\n");
#endif
	}
	
	//YOUT4 红灯
	if(LDP(Y_RLED)){
		setRedLedBrightness(CONFIG_SPLC_RLED_ON_DC);//设置红灯亮度
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y4 RLED\n");
#endif
	}
	if(LDN(Y_RLED)){
		setRedLedBrightness(CONFIG_SPLC_RLED_OFF_DC);//设置红灯亮度
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y4 RLED\n");
#endif
	}
	
	//YOUT5 蓝灯
	if(LDP(Y_BLED)){
		setBlueLedBrightness(CONFIG_SPLC_BLED_ON_DC);//设置红灯亮度
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y5 BLED\n");
#endif
	}
	if(LDN(Y_BLED)){
		setBlueLedBrightness(CONFIG_SPLC_BLED_OFF_DC);//设置红灯亮度
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
	
	//YOUT7 板载LED RUN
	if(LDP(Y_RUN_LED)){
		HAL_GPIO_WritePin(SYS_LED_RUN_GPIO_Port, SYS_LED_RUN_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y7 RUN LED\n");
#endif
	}
	if(LDN(Y_RUN_LED)){
		HAL_GPIO_WritePin(SYS_LED_RUN_GPIO_Port, SYS_LED_RUN_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y7 RUN LED\n");
#endif
	}
	//YOUT8 板载LED ERR
	if(LDP(Y_ERR_LED)){
		HAL_GPIO_WritePin(SYS_LED_ERR_GPIO_Port, SYS_LED_ERR_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:SET Y8 ERR LED\n");
#endif
	}
	if(LDN(Y_RUN_LED)){
		HAL_GPIO_WritePin(SYS_LED_ERR_GPIO_Port, SYS_LED_ERR_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_APP == 1
		printf("sPlcIoOut->outputRefresh:RESET Y8 ERR LED\n");
#endif
	}
}


