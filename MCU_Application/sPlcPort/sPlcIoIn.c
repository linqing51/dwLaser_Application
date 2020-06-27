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
	//X0
	temp = HAL_GPIO_ReadPin(ESTOP_IN_GPIO_Port, ESTOP_IN_Pin);//急停
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
	temp = HAL_GPIO_ReadPin(INTLOCK_IN_GPIO_Port, INTLOCK_IN_Pin);//安全连锁
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
	temp = HAL_GPIO_ReadPin(FSWITCH_NO_GPIO_Port, FSWITCH_NO_Pin);//脚踏常开
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
	temp = HAL_GPIO_ReadPin(FSWITCH_NC_GPIO_Port, FSWITCH_NC_Pin);//脚踏常闭
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
	temp = HAL_GPIO_ReadPin(PWR_KEY_GPIO_Port, PWR_KEY_Pin);//电源开关
	if(temp){
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
	//X5
	if(NVRAM0[SPREG_ADC_2] > CONFIG_FIBER_PD_HIGH){
		if(inputFilter[5] < CONFIG_INPUT_FILTER_TIME){
			inputFilter[5] ++;
		}
		else{
			NVRAM0[X_START] |= (int16_t)(1 << 5);
		}
	}
	else{
		if(inputFilter[5] > (CONFIG_INPUT_FILTER_TIME * -1)){
			inputFilter[5] --;
		}
		else{
			NVRAM0[X_START] &= ~(uint16_t)(1 << 5);
		}
	}
}

