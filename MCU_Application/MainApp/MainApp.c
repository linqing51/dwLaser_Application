#include "MainApp.h"
/*****************************************************************************/
//SYSTICK->HAL_Delay
//TIM2->CH3 BEEM ������
//TIM3->CH1 AIM_PWM ָʾ����
//TIM3->CH2 LED GREEN �̵�
//TIM4->CH1 LED RED ���
//TIM4->CH2 LED BLUE ����
//TIM6->RTOS
//TIM7->DAC DMA
//TIM14 SPLC TIMER
//TIM10 LASER TIMER
void mainAppTask(void *argument){
	sPlcInit();
	while(1){
		sPlcProcessStart();
		if(LD(SPCOIL_START_UP)){//
#if CONFIG_USING_DCHMI_APP == 1			
			dcHmiLoopInit();
#endif			
		}
#if CONFIG_USING_DCHMI_APP == 1
			dcHmiLoop();
#endif
#if CONFIG_SPLC_FUNTEST == 1
#endif
		sPlcProcessEnd();
	}
}




