#include "sPlc.h"
/*****************************************************************************/
void sPlcDacInit(void){//DAC初始化
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1); // 开启DAC输出
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2); // 开启DAC输出
	//writeDac7311(0);
}
void UPDAC0(void){//立即从SPREG_DAC_0中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_0] & 0x0FFF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, temp); // 设置DAC输出值	
}
void UPDAC1(void){//立即从SPREG_DAC_1中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_1] & 0x0FFF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, temp); // 设置DAC输出值	
}
void UPDAC2(void){}
void UPDAC3(void){}
void UPDAC4(void){}
void UPDAC5(void){}
void UPDAC6(void){}
void UPDAC7(void){}
void UPDAC8(void){
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_8] & 0x0FFF;
	//
}
void UPDAC9(void){}
void UPDAC10(void){}
void UPDAC11(void){}
void UPDAC12(void){}
void UPDAC13(void){}
void UPDAC14(void){}
void UPDAC15(void){}
void UPDAC16(void){
	if(NVRAM0[SPREG_DAC_16] > CONFIG_DAC_MAXBIT_CH16){
		NVRAM0[SPREG_DAC_16] = CONFIG_DAC_MAXBIT_CH16;
	}
	setRedLaserPwm(NVRAM0[SPREG_DAC_16]);
}
void UPDAC17(void){


}

void CLDAC(void){//立即清空全部DAC
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 1); // 设置DAC输出值	
	
}




