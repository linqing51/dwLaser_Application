#include "MainApp.h"
extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart3;
extern uint8_t dchmi_rxDat;
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
#if defined(MODEL_PVGLS_15W_1470_A0) || defined(MODEL_PVGLS_15W_1470_A1)
		if(huart4.RxState == HAL_UART_STATE_READY){
			HAL_UART_Receive_IT(&huart4, &dchmi_rxDat, 1);
		}
#endif
#if defined(MODEL_PVGLS_10W_1940_A1)
		if(huart3.RxState == HAL_UART_STATE_READY){
			HAL_UART_Receive_IT(&huart3, &dchmi_rxDat, 1);
		}
#endif
	}
}




