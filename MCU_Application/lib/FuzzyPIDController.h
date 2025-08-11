#ifndef __FUZZYPIDCONTROLLER_H__
#define __FUZZYPIDCONTROLLER_H__
/*****************************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include "sPlc.h"
/*****************************************************************************/
typedef struct {
    float Kp;       // 比例系数
    float Ki;       // 积分系数
    float Kd;       // 微分系数
    float prev_error;  // 上一次误差
    float integral;    // 积分项
    float output;      // 输出值
} FuzzyPIDController;
/*****************************************************************************/
void FuzzyPID_Init(FuzzyPIDController *pid);
float FuzzyPID_Calculate(FuzzyPIDController *pid, float setpoint, float measured);
#endif
