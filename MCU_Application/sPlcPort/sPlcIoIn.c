#include "sPlcIoIn.h"
/*****************************************************************************/
int8_t inputFilter[(X_END - X_START + 1) * 16];//IO输入滤波器缓冲区
/*****************************************************************************/
void inputInit(void){//IO输入滤波器初始化
#if CONFIG_SPLC_USING_IO_INPUT == 1
	memset((uint8_t*)inputFilter, 0x0, ((X_END - X_START + 1) * 16));
#endif
}
void inputRefresh(void){//获取输入IO
	uint8_t	temp;
	//X0 急停
	temp = HAL_GPIO_ReadPin(ESTOP_NC_GPIO_Port, ESTOP_NC_Pin);
	if(temp == GPIO_PIN_RESET){//急停常闭
		if(inputFilter[0] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[0] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 0);
		}
	}
	else{//急停常开
		if(inputFilter[0] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[0] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 0);
		}
	}
	//X1 安全连锁
	temp = HAL_GPIO_ReadPin(INTERLOCK_NC_GPIO_Port, INTERLOCK_NC_Pin);
	if(temp == GPIO_PIN_RESET){
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
	//X2 脚踏常开
	temp = HAL_GPIO_ReadPin(FS_NO_GPIO_Port, FS_NO_Pin);
	if(temp == GPIO_PIN_RESET){
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
	//X3 脚踏常闭
	temp = HAL_GPIO_ReadPin(FS_NC_GPIO_Port, FS_NC_Pin);
	if(temp == GPIO_PIN_RESET){
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
	//X4 光纤探测
	if(NVRAM0[SPREG_ADC_2] > CONFIG_FIBER_PD_THRESHOLD){
		if(inputFilter[4] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[4] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 4);
		}
	}
	else{
		if(inputFilter[4] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[4] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 4);
		}
	}
}

