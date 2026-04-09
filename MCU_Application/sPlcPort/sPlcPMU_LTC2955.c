#include "sPlcPMU.h"
/*****************************************************************************/
#if defined(CONFIG_PMU_LTC2955)

void PmuPowerUp(void){//开机函数
//空硬件开机与软件无关

}

void PmuPowerDown(void){//关机函数
	
	
	SET_PWR_KILL_OFF;//给LTC2955 KILL信号实现软关机
}

#endif





