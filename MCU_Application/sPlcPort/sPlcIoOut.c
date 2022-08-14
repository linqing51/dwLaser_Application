#include "sPlcIoOut.h"
/*****************************************************************************/
void outputInit(void){//IO ‰≥ˆ≥ı ºªØ
	NVRAM0[Y_START] = 0x0;
	SET_RED_LED_OFF;
	SET_GREEN_LED_OFF;
	SET_BLUE_LED_OFF;
	SET_TICK_LED_OFF;
	SET_ERR_LED_OFF;
}

void outputRefresh(void){//…Ë÷√ ‰≥ˆIO	
	//YOUT0 ¬Ãµ∆
	if(LDP(Y_GREEN_LED)){
		SET_GREEN_LED_ON;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y0 GLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_GREEN_LED)){
		SET_GREEN_LED_OFF;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y0 GLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT1 ∫Ïµ∆
	if(LDP(Y_RED_LED)){
		SET_RED_LED_ON;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y1 RLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_RED_LED)){
		SET_RED_LED_OFF;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y1 RLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT2 ¿∂µ∆
	if(LDP(Y_YELLOW_LED)){
		SET_BLUE_LED_ON;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y2 BLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_YELLOW_LED)){
		SET_BLUE_LED_OFF;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y2 BLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT3 TICK LED
	if(LDP(Y_TICK_LED)){
		SET_TICK_LED_ON;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y3 TICK LED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_TICK_LED)){
		SET_TICK_LED_OFF;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y3 TICK LED\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT4 ERR LED
	if(LDP(Y_ERR_LED)){
		SET_ERR_LED_ON;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y4 ERR LED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_ERR_LED)){
		SET_ERR_LED_OFF;
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y4 ERR LED\n",__FILE__, __LINE__, __func__);
#endif
	}
}


