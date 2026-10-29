/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "sPlc.h"
#include "tim.h"
/*****************************************************************************/
void sPlcDacInit(void){//DAC初始化
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_1, DAC_ALIGN_12B_R, 0); // 设置DAC输出值
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, 0); // 设置DAC输出值	
	HAL_DAC_Start(&hdac, DAC_CHANNEL_1); // 开启DAC输出
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2); // 开启DAC输出
	HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);//启动TIM9 CH2 PWM输出(TEC驱动, 经GP8101C-SH转模拟电压)
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
void UPDAC8(void){//立即从SPREG_DAC_8中更新DAC8(TIM9 CH2 PWM -> GP8101C-SH 模拟电压)
	uint32_t temp;
	temp = NVRAM0[SPREG_DAC_8] & 0x0FFF;
	//SPREG_DAC_8(0~4095)映射为TIM9 CH2占空比CCR2(0~65535), 经GP8101C-SH输出0~满量程模拟电压
	__HAL_TIM_SET_COMPARE(&htim9, TIM_CHANNEL_2, (uint32_t)((float)temp / 4095.0f * 65535.0f));
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




