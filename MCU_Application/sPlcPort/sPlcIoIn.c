#include "sPlcIoIn.h"
/*****************************************************************************/
int8_t inputFilter[(X_END - X_START + 1) * 16];//IO输入滤波器缓冲区
/*****************************************************************************/
void inputInit(void){//IO输入滤波器初始化
#if CONFIG_SPLC_USING_IO_INPUT == 1

#endif
}
void inputRefresh(void){//获取输入IO
	uint8_t	temp;
	//X0
	temp = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_11);//PC11
	if(temp){
		if(inputFilter[0] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[0] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 0);
		}
	}
	else{
		if(inputFilter[0] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[0] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 0);
		}
	}
	//X1
	temp = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12);//PC12
	if(temp){
		if(inputFilter[1] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[1] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 1);
		}
	}
	else{
		if(inputFilter[1] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[1] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 1);
		}
	}
	//X2
	temp = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_10);//PC10
	if(temp){
		if(inputFilter[2] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[2] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 2);
		}
	}
	else{
		if(inputFilter[2] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[2] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 2);
		}
	}
	//X3
	temp = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_15);//PA15
	if(temp){
		if(inputFilter[3] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[3] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 3);
		}
	}
	else{
		if(inputFilter[3] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[3] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 3);
		}
	}
	//X4
	temp = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_8);//PC8
	if(temp){
		if(inputFilter[2] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[2] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 2);
		}
	}
	else{
		if(inputFilter[2] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[2] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 2);
		}
	}
	
}

