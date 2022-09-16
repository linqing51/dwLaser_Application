#ifndef __PID_FUZZY_H__
#define __PID_FUZZY_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
#include "arm_math.h"
/*****************************************************************************/
typedef struct PID {
	double Kp; // 增量式积分系数
	double Ki; 
	double Kd;
	double T;
	double K1; // 增量式积分系数
	double K2; 
	double K3; 
	double LastError; //Error[-1]
	double PrevError; // Error[-2]
	double pwm_out;
	uint16_t flag;//温度状态标志位
	uint8_t dir;//0 制热 1制冷
}fuzzyPid_t;
/*****************************************************************************/
void fuzzyPidSet(fuzzyPid_t *structpid,float Kp,float Ki,float Kd,float T, uint8_t dir);
double fuzzyPidRealize(fuzzyPid_t *structpid, double set, double input);
void fuzzyPidInit(fuzzyPid_t *structpid);
#endif /* PID_H_ */
