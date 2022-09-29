#include "sPlc.h"
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim2;//FAN PWM
/*****************************************************************************/
void sPlcOutputInit(void){//IO输出初始化
	NVRAM0[Y_START] = 0x0;
	SET_TEC_OFF;
	SET_RED_LED_OFF;
	SET_GREEN_LED_OFF;
	SET_BLUE_LED_OFF;
	SET_TICK_LED_OFF;
	SET_ERR_LED_OFF;
	SET_AIM_OFF;
	printf("%s,%d,%s:output init......\n",__FILE__, __LINE__, __func__);
}

void sPlcOutputRefresh(void){//设置输出IO	
	//YOUT0 绿灯
	if(LDP(Y_GREEN_LED)){
		SET_GREEN_LED_ON;
		//printf("%s,%d,%s:set Y0 GLED\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_GREEN_LED)){
		SET_GREEN_LED_OFF;
		//printf("%s,%d,%s:reset Y0 GLED\n",__FILE__, __LINE__, __func__);
	}
	
	//YOUT1 红灯
	if(LDP(Y_RED_LED)){
		SET_RED_LED_ON;
		//printf("%s,%d,%s:set Y1 RLED\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_RED_LED)){
		SET_RED_LED_OFF;
		//printf("%s,%d,%s:reset Y1 RLED\n",__FILE__, __LINE__, __func__);
	}
	
	//YOUT2 黄灯
	if(LDP(Y_YELLOW_LED)){
		//绿色+蓝色模拟黄色
		SET_BLUE_LED_ON;
		SET_GREEN_LED_ON;
		//printf("%s,%d,%s:set Y2 BLED\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_YELLOW_LED)){
		SET_BLUE_LED_OFF;
		SET_GREEN_LED_OFF;
		//printf("%s,%d,%s:reset Y2 BLED\n",__FILE__, __LINE__, __func__);
	}
	
	//YOUT3 TICK LED
	if(LDP(Y_TICK_LED)){
		SET_TICK_LED_ON;
	}
	if(LDN(Y_TICK_LED)){
		SET_TICK_LED_OFF;
	}
	
	//YOUT4 ERR LED
	if(LDP(Y_ERR_LED)){
		SET_ERR_LED_ON;
	}
	if(LDN(Y_ERR_LED)){
		SET_ERR_LED_OFF;
	}
	
	//YOUT5 TEC
	if(LDP(Y_TEC)){
		SET_TEC_ON;
	}
	if(LDN(Y_TEC)){
		SET_TEC_OFF;
	}
	
	//YOUT7 AIM
	if(LDP(Y_AIM)){
		SET_AIM_ON;
		//printf("%s,%d,%s:set Y6 FAN\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_AIM)){
		SET_AIM_OFF;
		//printf("%s,%d,%s:reset Y6 FAN\n",__FILE__, __LINE__, __func__);
	}
	
}


