#include "sPlcIoOut.h"
/*****************************************************************************/
void outputInit(void){//IO输出初始化
#if CONFIG_SPLC_USING_IO_OUTPUT == 1	

#endif
}

void outputRefresh(void){//设置输出IO
	//YOUT0
	if((NVRAM0[Y_START] >> 0) & 0x01){//PB10
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
	}
	//YOUT1
	if((NVRAM0[Y_START] >> 1) & 0x01){//P3_6
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);
	}
	else{
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
	}
}


