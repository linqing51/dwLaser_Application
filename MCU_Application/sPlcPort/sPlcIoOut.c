#include "sPlcIoOut.h"
/*****************************************************************************/
void outputInit(void){//IO�����ʼ��
	NVRAM0[Y_START] = 0x0;
	HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_SET);//Laser fan off
	HAL_GPIO_WritePin(LAS_TEC_GPIO_Port, LAS_TEC_Pin, GPIO_PIN_SET);//laser tec off
	
	setRedLedBrightness(0);
	setGreenLedBrightness(0);
	setYellowLedBrightness(0);
}

void outputRefresh(void){//�������IO	
	//YOUT0 �̵�
	if(LDP(Y_GREEN_LED)){
		setGreenLedBrightness(CONFIG_SPLC_DEFAULT_GLED_DC);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y0 GLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_GREEN_LED)){
		setGreenLedBrightness(0);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y0 GLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT1 ���
	if(LDP(Y_RED_LED)){
		setRedLedBrightness(CONFIG_SPLC_DEFAULT_RLED_DC);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y1 RLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_RED_LED)){
		setRedLedBrightness(0);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y1 RLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT2 �Ƶ�
	if(LDP(Y_YELLOW_LED)){
		setYellowLedBrightness(CONFIG_SPLC_DEFAULT_YLED_DC);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y2 BLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_YELLOW_LED)){
		setYellowLedBrightness(0);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y2 BLED\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT3 TICK LED
	if(LDP(Y_TICK_LED)){
		setTickLed(true);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y3 TICK LED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_TICK_LED)){
		setTickLed(false);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y3 TICK LED\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT4 ERR LED
	if(LDP(Y_ERR_LED)){
		setErrorLed(true);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y4 ERR LED\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_ERR_LED)){
		setErrorLed(false);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y4 ERR LED\n",__FILE__, __LINE__, __func__);
#endif
	}
}


