#include "sPlcIoOut.h"
/*****************************************************************************/
void outputInit(void){//IO�����ʼ��
	NVRAM0[Y_START] = 0x0;
	HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_SET);//Laser fan off
	HAL_GPIO_WritePin(LAS_TEC_GPIO_Port, LAS_TEC_Pin, GPIO_PIN_SET);//laser tec off
	
	setRedLedBrightness(CONFIG_SPLC_RLED_OFF_DC);
	setGreenLedBrightness(CONFIG_SPLC_GLED_OFF_DC);
	setBlueLedBrightness(CONFIG_SPLC_BLED_OFF_DC);
}

void outputRefresh(void){//�������IO
	//YOUT0 24V ���ȿ���
	if(LDP(Y_LAS_FAN)){
		//HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y0\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_LAS_FAN)){
		//HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y0\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT1 ���俪��
	if(LDP(Y_LAS_TEC)){
		HAL_GPIO_WritePin(LAS_TEC_GPIO_Port, LAS_TEC_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y1\n",__FILE__, __LINE__, __func__);
#endif	
	}
	if(LDN(Y_LAS_TEC)){
		HAL_GPIO_WritePin(LAS_TEC_GPIO_Port, LAS_TEC_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y1\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT2 �̵�
	if(LDP(Y_GREEN_LED)){
		setGreenLedBrightness(CONFIG_SPLC_GLED_ON_DC);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y2\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_GREEN_LED)){
		setGreenLedBrightness(CONFIG_SPLC_GLED_OFF_DC);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y2\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT3 ���
	if(LDP(Y_RED_LED)){
		setRedLedBrightness(CONFIG_SPLC_RLED_ON_DC);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y3\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_RED_LED)){
		setRedLedBrightness(CONFIG_SPLC_RLED_OFF_DC);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y3\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT4 ����
	if(LDP(Y_BLUE_LED)){
		setBlueLedBrightness(CONFIG_SPLC_BLED_ON_DC);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y4\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_BLUE_LED)){
		setBlueLedBrightness(CONFIG_SPLC_BLED_OFF_DC);//���ú������
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y4\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT5 TICK LED
	if(LDP(Y_TICK_LED)){
		HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y5\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_TICK_LED)){
		HAL_GPIO_WritePin(TICK_LED_GPIO_Port, TICK_LED_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y5\n",__FILE__, __LINE__, __func__);
#endif
	}
	
	//YOUT6 ERR LED
	if(LDP(Y_ERR_LED)){
		HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_SET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:set Y6\n",__FILE__, __LINE__, __func__);
#endif
	}
	if(LDN(Y_ERR_LED)){
		HAL_GPIO_WritePin(ERR_LED_GPIO_Port, ERR_LED_Pin, GPIO_PIN_RESET);
#if CONFIG_DEBUG_IO == 1
		printf("%s,%d,%s:reset Y6\n",__FILE__, __LINE__, __func__);
#endif
	}
}




