#include "sPlc.h"
/*****************************************************************************/
extern UART_HandleTypeDef huart5;
extern UART_HandleTypeDef huart6;
extern uint8_t uart5_rxDat;
extern uint8_t uart6_rxDat;
extern void modbusGetChar(uint8_t Data);
extern freeProtocol_t freeProtocol;
/*****************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart5){
		modbusGetChar(uart5_rxDat);
		HAL_UART_Receive_IT(&huart5, &uart5_rxDat, 1);
	}
	if(huart == &huart6){	
		if((uart6_rxDat == 'A') || (uart6_rxDat == 'V') || (uart6_rxDat == 'L') || (uart6_rxDat == 'T') || (uart6_rxDat == 'G') || (uart6_rxDat == 'R') ||(uart6_rxDat == '$')){//接收到起始字符
			memset(freeProtocol.cmdBufRx, 0x00, CONFIG_FREEPROTOCOL_SIZE);
			freeProtocol.rxIndex = 0;
			freeProtocol.rxRuning = true;
			freeProtocol.rxDone = false;
			freeProtocol.cmdBufRx[freeProtocol.rxIndex] = uart6_rxDat;
			freeProtocol.rxIndex ++;
		}
		else if((uart6_rxDat == 'E') || (uart6_rxDat == '#')){//接收到结束字符
			freeProtocol.rxRuning = false;
			freeProtocol.rxDone = true;
			freeProtocol.cmdBufRx[freeProtocol.rxIndex] = uart6_rxDat;
		}
		else if(freeProtocol.rxRuning){
			if(freeProtocol.rxIndex < (CONFIG_FREEPROTOCOL_SIZE - 1)){//缓冲区未溢出
				freeProtocol.cmdBufRx[freeProtocol.rxIndex] = uart6_rxDat;
				freeProtocol.rxIndex ++;
			}
			else{//超出缓冲区
				freeProtocol.rxIndex = 0;
				freeProtocol.rxDone = false;
				freeProtocol.rxRuning = false;
			}
		}
		HAL_UART_Receive_IT(&huart6, &uart6_rxDat, 1);
	}
}
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
	if(huart == &huart6){
		freeProtocol.txRuning = 0;
		freeProtocol.txDone = 1;
	}
}
