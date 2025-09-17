#include "sPlc.h"
#include "boardConfig.h"
/*****************************************************************************/
void sPlcOutputInit(void){//IO输出初始化
	NVRAM0[Y_START] = 0x0;
	SET_TEC_OFF;
	SET_RED_LED_OFF;
	SET_GREEN_LED_OFF;
	SET_BLUE_LED_OFF;
	SET_TICK_LED_OFF;
	SET_ERR_LED_OFF;
	printf("%s,%d,%s:output init......\n",__FILE__, __LINE__, __func__);
}

void sPlcOutputRefresh(void){//设置输出IO	
	//YOUT0 绿灯
	if(LDP(Y_GREEN_LED)){
		SET_GREEN_LED_ON;
	}
	if(LDN(Y_GREEN_LED)){
		SET_GREEN_LED_OFF;
	}
	//YOUT1 红灯
	if(LDP(Y_RED_LED)){
		SET_RED_LED_ON;
	}
	if(LDN(Y_RED_LED)){
		SET_RED_LED_OFF;
	}
	
	//YOUT2 黄灯
	if(LDP(Y_YELLOW_LED)){
		//绿色+蓝色模拟黄色
		SET_BLUE_LED_ON;
	}
	if(LDN(Y_YELLOW_LED)){
		SET_BLUE_LED_OFF;
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
	
	//YOUT5 BEEM LED
	if(LDP(Y_BEEM_LED)){
	}
	if(LDN(Y_BEEM_LED)){
	}
	//YOUT6 TEC
	if(LDP(Y_TEC)){
		SET_TEC_ON;
	}
	if(LDN(Y_TEC)){
		SET_TEC_OFF;
	}
		
	//YOUT7 PWR ON
	if(LDP(Y_VN5016_INPUT)){
		SET_VN5016_INPUT_ON;
	}
	if(LDN(Y_VN5016_INPUT)){
		SET_VN5016_INPUT_OFF;
	}	
	
	//YOUT8 POWER DIS
	if(LDP(Y_VN5016_CSDIS)){
		SET_VN5016_CSDIS_ON;
	}
	if(LDN(Y_VN5016_CSDIS)){
		SET_VN5016_CSDIS_OFF;
	}	
	
	//YOUT9 POWER LED
	if(LDP(Y_PWR_LED)){
		SET_PWR_LED_ON;
	}
	if(LDN(Y_PWR_LED)){
		SET_PWR_LED_OFF;
	}
}


