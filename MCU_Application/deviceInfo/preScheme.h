#ifndef __PRESCHEME_H__
#define __PRESCHEME_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
typedef struct{
	char *name;//治疗名字
	int16_t channel;//激光通道选择
	int16_t pulse_mode;//脉冲模式
	int16_t power_ch0;//功率 1470
	int16_t power_ch1;//功率 980
	int16_t power_red;//功率 635
	int16_t poswidth;
	int16_t negwidth;
}myScheme_t;
/*****************************************************************************/
extern myScheme_t sPhlebology[32];//0
extern myScheme_t sProctology[32];//1
extern myScheme_t sGynecology[32];//2
extern myScheme_t sENT[32];//3
extern myScheme_t sNeurosurgery[32];//4
extern myScheme_t sDermatology[32];//5
extern myScheme_t sLiposuction[32];//6
extern myScheme_t sDentistry[32];//7
extern myScheme_t sTherapy[32];//8
/*****************************************************************************/
void schemeInit(uint8_t reDef);//治疗方案初始化
void goNextScheme(void);//切换下一个方案
void goLastScheme(void);//切换上一个方案
#endif


