#include "sPlc.h"
/*****************************************************************************/
void sPlcDacInit(void){//DAC初始化
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0x0000);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 0x0000);	 
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
	printf("%s,%d,%s:init dac done!\n",__FILE__, __LINE__, __func__);
}
void UPDAC0(void){//立即从SPREG_DAC_0中更新DAC0
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_0] & 0x0FFF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, temp);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
	printf("%s,%d,%s:update dac0=%d\n",__FILE__, __LINE__, __func__, temp);
}
void UPDAC1(void){//立即从SPREG_DAC_1更新DAC1
	uint16_t temp;
	temp = NVRAM0[SPREG_DAC_1] & 0x0FFF;
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, temp);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	printf("%s,%d,%s:update dac1=%d\n",__FILE__, __LINE__, __func__, temp);
}

void CLDAC(void){//立即清空全部DAC
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0x0);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 0x0);
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
	printf("%s,%d,%s:clear all dac!\n",__FILE__, __LINE__, __func__);
}








