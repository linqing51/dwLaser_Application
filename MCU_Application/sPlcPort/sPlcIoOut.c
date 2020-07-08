#include "sPlcIoOut.h"
/*****************************************************************************/
void outputInit(void){//IO输出初始化
	NVRAM0[Y_START] = 0x0;
	HAL_GPIO_WritePin(FAN_OUT_GPIO_Port, FAN_OUT_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin, GPIO_PIN_RESET);
	setGreenLedDutyCycle(CONFIG_SPLC_GLED_OFF_DC);
	setRedLedDutyCycle(CONFIG_SPLC_RLED_OFF_DC);
	setBlueLedDutyCycle(CONFIG_SPLC_BLED_OFF_DC);
}

void outputRefresh(void){//设置输出IO
	//YOUT0 风扇开关
	if((NVRAM0[Y_START] >> 0) & 0x01){
		HAL_GPIO_WritePin(FAN_OUT_GPIO_Port, FAN_OUT_Pin, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(FAN_OUT_GPIO_Port, FAN_OUT_Pin, GPIO_PIN_RESET);
	}
	//YOUT1 制冷开关
	if((NVRAM0[Y_START] >> 1) & 0x01){
#if CONFIG_SPLC_USING_LEDAIM == 1	
		HAL_GPIO_WritePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin, GPIO_PIN_SET);
#endif
	}
	else{
#if CONFIG_SPLC_USING_LEDAIM == 1
		HAL_GPIO_WritePin(TEC_OUT_GPIO_Port, TEC_OUT_Pin, GPIO_PIN_RESET);
#endif
	}
	//YOUT2 绿灯
	if((NVRAM0[Y_START] >> 2) & 0x01){
#if CONFIG_SPLC_USING_LEDAIM == 1
		setGreenLedDutyCycle(CONFIG_SPLC_GLED_ON_DC);
#endif
	}
	else{
#if CONFIG_SPLC_USING_LEDAIM == 1
		setGreenLedDutyCycle(CONFIG_SPLC_GLED_OFF_DC);
#endif
	}
	//YOUT3 红灯
	if((NVRAM0[Y_START] >> 3) & 0x01){
#if CONFIG_SPLC_USING_LEDAIM == 1
		setRedLedDutyCycle(CONFIG_SPLC_RLED_ON_DC);
#endif
	}
	else{
#if CONFIG_SPLC_USING_LEDAIM == 1
		setRedLedDutyCycle(CONFIG_SPLC_RLED_OFF_DC);
#endif
	}
	//YOUT4 蓝灯
	if((NVRAM0[Y_START] >> 4) & 0x01){
#if CONFIG_SPLC_USING_LEDAIM == 1
		setBlueLedDutyCycle(CONFIG_SPLC_BLED_ON_DC);
#endif	
	}
	else{
#if CONFIG_SPLC_USING_LEDAIM == 1
		setBlueLedDutyCycle(CONFIG_SPLC_BLED_OFF_DC);
#endif
	}
	
}


