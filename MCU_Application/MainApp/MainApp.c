#include "MainApp.h"
/*****************************************************************************/



void mainTask(void *pvParameters){
	while(1){
		HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		 osDelay(500);
	}
}


