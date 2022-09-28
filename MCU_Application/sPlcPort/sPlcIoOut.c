#include "sPlc.h"
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim2;//FAN PWM
/*****************************************************************************/
void sPlcOutputInit(void){//IO输出初始化
	NVRAM0[Y_START] = 0x0;
	SET_TEC_PWM(GPIO_PIN_RESET);
	SET_ALARM_LED(GPIO_PIN_RESET);	
	SET_LASER1_LED(GPIO_PIN_RESET);			
	SET_LASER2_LED(GPIO_PIN_RESET);
	SET_TICK_LED(GPIO_PIN_RESET);
	SET_ERR_LED(GPIO_PIN_RESET);	
	SET_LASER1_AIM(GPIO_PIN_RESET);	
	SET_LASER2_AIM(GPIO_PIN_RESET);		
	SET_LASER_PWM(GPIO_PIN_RESET);	
	SET_SPEAK_ENA(GPIO_PIN_RESET);		
	printf("%s,%d,%s:output init......\n",__FILE__, __LINE__, __func__);
}

void sPlcOutputRefresh(void){//设置输出IO	
	//Y0 心跳灯
	if(LDP(Y_TICK_LED)){
		SET_TICK_LED(GPIO_PIN_SET);
		printf("%s,%d,%s:set Y0(tick led)\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_TICK_LED)){
		SET_TICK_LED(GPIO_PIN_RESET);
		printf("%s,%d,%s:reset Y0(tick led)\n",__FILE__, __LINE__, __func__);
	}
	
	//Y1 错误灯
	if(LDP(Y_ERR_LED)){
		SET_ERR_LED(GPIO_PIN_SET);
		printf("%s,%d,%s:set Y1(error led)\n",__FILE__, __LINE__, __func__);
	}	
	if(LDN(Y_ERR_LED)){
		SET_ERR_LED(GPIO_PIN_RESET);
		printf("%s,%d,%s:reset Y1(error led)\n",__FILE__, __LINE__, __func__);
	}
	
	//Y2 报警灯
	if(LDP(Y_ALARM_LED)){
		SET_ALARM_LED(GPIO_PIN_SET);
		printf("%s,%d,%s:set Y2(alarm led)\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_ALARM_LED)){
		SET_ALARM_LED(GPIO_PIN_RESET);
		printf("%s,%d,%s:reset Y2(alarm led)\n",__FILE__, __LINE__, __func__);
	}
	
	//Y3 通行指示灯
	if(LDP(Y_LINK_LED)){
		SET_LINK_LED(GPIO_PIN_SET);
		printf("%s,%d,%s:set Y3(lock led)\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_LINK_LED)){
		SET_LINK_LED(GPIO_PIN_RESET);
		printf("%s,%d,%s:reset Y3(lock led)\n",__FILE__, __LINE__, __func__);
	}
	
	//Y4 通道1 激光指示灯
	if(LDP(Y_LASER1_LED)){
		SET_LASER1_LED(GPIO_PIN_SET);
		printf("%s,%d,%s:set Y4(laser1 led)\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_LASER1_LED)){
		SET_LASER1_LED(GPIO_PIN_RESET);
		printf("%s,%d,%s:reset Y4(laser1 led)\n",__FILE__, __LINE__, __func__);
	}
	
	//Y5 ERR LED
	if(LDP(Y_LASER2_LED)){
		SET_LASER2_LED(GPIO_PIN_SET);
		printf("%s,%d,%s:set Y5(laser2 led)\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_LASER2_LED)){
		SET_LASER2_LED(GPIO_PIN_RESET);
		printf("%s,%d,%s:reset Y5(laser2 led)\n",__FILE__, __LINE__, __func__);
	}
	
	//Y6 通道1 指示光使能
	if(LDP(Y_AIM1_ENA)){
		SET_LASER1_AIM(GPIO_PIN_SET);
		printf("%s,%d,%s:set Y6(laser1 aim)\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_AIM1_ENA)){
		SET_LASER1_AIM(GPIO_PIN_RESET);
		printf("%s,%d,%s:reset Y6(laser1 aim)\n",__FILE__, __LINE__, __func__);
	}
	
	//Y7 通道2 指示光使能
	if(LDP(Y_AIM2_ENA)){
		SET_LASER2_AIM(GPIO_PIN_SET);
		printf("%s,%d,%s:set Y7(laser2 aim)\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_AIM2_ENA)){
		SET_LASER2_AIM(GPIO_PIN_RESET);
		printf("%s,%d,%s:reset Y7(laser2 aim)\n",__FILE__, __LINE__, __func__);
	}
		
	//Y8 制冷器使能
	if(LDP(Y_TEC_ENA)){
		SET_TEC_PWM(GPIO_PIN_SET);
		printf("%s,%d,%s:set Y9(tec enable)\n",__FILE__, __LINE__, __func__);
	}
	if(LDN(Y_TEC_ENA)){
		SET_TEC_PWM(GPIO_PIN_RESET);
		printf("%s,%d,%s:reset Y9(tec enable)\n",__FILE__, __LINE__, __func__);
	}
	
}


