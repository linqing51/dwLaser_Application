#ifndef __PID_FUZZY_H__
#define __PID_FUZZY_H__
/*****************************************************************************/
#include "stm32f4xx_hal.h"
#include "arm_math.h"
/*****************************************************************************/
typedef struct PID 
{
	float Kp; // ����ʽ����ϵ��
	float Ki; 
	float Kd;
	float T;
	
	float K1; // ����ʽ����ϵ��
	float K2; 
	float K3; 
	float LastError; //Error[-1]
	float PrevError; // Error[-2]
	float pwm_out;
	
	uint16_t flag;//�¶�״̬��־λ
}PID;

//void PID_init(PID *structpid);
void PID_Set(PID *structpid,float Kp,float Ki,float Kd,float T);
int PID_realize(PID *structpid,uint16_t s,uint16_t in);
void PID_Init(PID *structpid);
#endif /* PID_H_ */
