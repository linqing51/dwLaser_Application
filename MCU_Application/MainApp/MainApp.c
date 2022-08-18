#include "MainApp.h"
/*****************************************************************************/
//UART1 ต๗สิ
//UART2 NFC
//UART4 DCLCD
//SYSTICK->HAL_Delay
//TIM6->RTOS
//TIM7->DAC DMA
//TIM14 SPLC TIMER
//TIM10 LASER TIMER
//TIM2 CH1 AIM
//TIM12 CH2 FAN
extern UART_HandleTypeDef huart1;//ต๗สิ
extern TIM_HandleTypeDef htim12;//FAN PWM


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




