#include "MainApp.h"
extern UART_HandleTypeDef huart4;
extern uint8_t uart4_rxDat;
/*****************************************************************************/
void mainAppTask(void *argument){
	sPlcInit();
	while(1){
		sPlcProcessStart();
		if(LD(SPCOIL_START_UP)){//
			dcHmiLoopInit();	
		}
		dcHmiLoop();
		sPlcProcessEnd();
		//检测串口发生错误重新启动接收
		if(huart4.RxState == HAL_UART_STATE_READY){
			HAL_UART_Receive_IT(&huart4, &uart4_rxDat, 1);
		}
	}
}




