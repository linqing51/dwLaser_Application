#include "sPlc.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;
extern uint8_t uart5_rxDat;
extern uint8_t uart6_rxDat;
extern void modbusGetChar(uint8_t Data);
extern ringBuff_t fpRingBuff_Rx;//自由协议接收缓冲
extern freeProtocol_t freeProtocol;
/*****************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart5){
		modbusGetChar(uart5_rxDat);
		HAL_UART_Receive_IT(&huart5, &uart5_rxDat, 1);
	}
	if(huart == &huart6){
		sPlcRingBuffPush(&fpRingBuff_Rx, uart6_rxDat);//循环缓冲压入
		HAL_UART_Receive_IT(&huart6, &uart6_rxDat, 1);
	}
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart6){
		freeProtocol.txRuning = 0;
		freeProtocol.txDone = 1;
	}
}
