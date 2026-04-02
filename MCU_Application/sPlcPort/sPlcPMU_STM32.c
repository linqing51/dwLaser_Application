#include "sPlcPMU.h"
/*****************************************************************************/
#if defined(CONFIG_PMU_STM32)
void PmuPowerUp(void){//开机函数
	//打开电源
	SSET(Y_VN5016_INPUT);
	SSET(Y_PWR_LED);
	RRES(Y_VN5016_CSDIS);//打开电流监控
	printf("%s,%d,%s:powerup!\n",__FILE__, __LINE__, __func__);
}

void PmuPowerDown(void){//关机函数
	//关闭模拟量暑出
	printf("%s,%d,%s:shutdown dac!\n",__FILE__, __LINE__, __func__);
	NVRAM0[SPREG_DAC_0] = 0;NVRAM0[SPREG_DAC_1] = 0;NVRAM0[SPREG_DAC_2] = 0;NVRAM0[SPREG_DAC_3] = 0;
	NVRAM0[SPREG_DAC_4] = 0;NVRAM0[SPREG_DAC_5] = 0;NVRAM0[SPREG_DAC_6] = 0;NVRAM0[SPREG_DAC_7] = 0;
	NVRAM0[SPREG_DAC_8] = 0;NVRAM0[SPREG_DAC_9] = 0;NVRAM0[SPREG_DAC_10] = 0;NVRAM0[SPREG_DAC_11] = 0;
	NVRAM0[SPREG_DAC_12] = 0;NVRAM0[SPREG_DAC_13] = 0;NVRAM0[SPREG_DAC_14] = 0;NVRAM0[SPREG_DAC_15] = 0;
	NVRAM0[SPREG_DAC_16] = 0;NVRAM0[SPREG_DAC_17] = 0;
	UPDAC0();UPDAC1();UPDAC2();UPDAC3();UPDAC4();UPDAC5();UPDAC6();UPDAC7();
	UPDAC8();UPDAC9();UPDAC10();UPDAC11();UPDAC12();UPDAC13();UPDAC14();UPDAC15();
	UPDAC16();UPDAC17();
	
	SET_LASER_CH0_OFF;
	SET_LASER_CH1_OFF;
	SET_LASER_CH2_OFF;
	SET_LASER_CH3_OFF;
	SET_LASER_CH4_OFF;
	SET_LASER_CH5_OFF;
	SET_LASER_CH6_OFF;
	SET_LASER_CH7_OFF;
	SET_TEC_CH0_OFF;
	SET_TEC_CH1_OFF;
	SET_TEC_CH2_OFF;
	SET_TEC_CH3_OFF;
	SET_TEC_CH4_OFF;
	SET_TEC_CH5_OFF;
	SET_TEC_CH6_OFF;
	SET_TEC_CH7_OFF;
	RRES(Y_TEC);//关闭TEC
	printf("%s,%d,%s:shutdown laser and tec power!\n",__FILE__, __LINE__, __func__);
	EDLAR();//停止发射
	SET_RAIM_TIM_OFF;SET_GAIM_TIM_OFF;//停止指示激光发射
	printf("%s,%d,%s:shutdown red aim and greend aim!\n",__FILE__, __LINE__, __func__);
	RRES(SPCOIL_BEEM_ENABLE);//关闭蜂鸣器
	sPlcSpeakerDisable();//关闭SPK AP
	SET_SPK_TIM_OFF;//关闭SPK TIM
	printf("%s,%d,%s:shutdown rbg led!\n",__FILE__, __LINE__, __func__);
	RRES(Y_GREEN_LED);//打开绿灯
	RRES(Y_YELLOW_LED);//关闭黄灯
	RRES(Y_RED_LED);//关闭红灯
	printf("%s,%d,%s:shutdown 24V power!\n",__FILE__, __LINE__, __func__);
	RRES(Y_PWR_LED);
	RRES(Y_VN5016_INPUT);//关闭24V电源
	SSET(Y_VN5016_CSDIS);//关闭电流监控	
}

#endif











