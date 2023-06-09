#include "sPlc.h"
extern TIM_HandleTypeDef htim12;//FAN PWM
extern TIM_HandleTypeDef htim2;//FAN PWM
/*****************************************************************************/
void sPlcOutputInit(void){//IO�����ʼ��
	NVRAM0[Y_START] = 0x0;
	SET_RED_LED_OFF;
	SET_GREEN_LED_OFF;
	SET_BLUE_LED_OFF;
	printf("%s,%d,%s:output init......\n",__FILE__, __LINE__, __func__);
}

void sPlcOutputRefresh(void){//�������IO	
	//YOUT0 �̵�
	if(LDP(Y_GREEN_LED)){
		SET_GREEN_LED_ON;
	}
	if(LDN(Y_GREEN_LED)){
		SET_GREEN_LED_OFF;
	}
	//YOUT1 ���
	if(LDP(Y_RED_LED)){
		SET_RED_LED_ON;
	}
	if(LDN(Y_RED_LED)){
		SET_RED_LED_OFF;
	}
	
	//YOUT2 �Ƶ�
	if(LDP(Y_YELLOW_LED)){
		//��ɫ+��ɫģ���ɫ
		SET_BLUE_LED_ON;
	}
	if(LDN(Y_YELLOW_LED)){
		SET_BLUE_LED_OFF;
	}

}


