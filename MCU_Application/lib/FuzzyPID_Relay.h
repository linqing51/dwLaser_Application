/*****************************************************************************/
/**
 * 模糊PID温度控制器 - 继电器控制版本
 * 针对半导体制冷器优化，模块化设计
 */
#ifndef FUZZY_PID_CONTROLLER_H
#define FUZZY_PID_CONTROLLER_H
#include "sPlc.h"
// 控制器状态结构体
typedef struct {
    float Kp;           // 比例系数
    float Ki;           // 积分系数  
    float Kd;           // 微分系数
    float prev_error;   // 上一次误差
    float integral;     // 积分项
    float output;       // 输出值(0-100%)
    float hysteresis;   // 继电器滞回宽度
    int relay_state;    // 继电器当前状态(0=关,1=开)
} FuzzyPIDController;

// 初始化函数
void FuzzyPID_Init(FuzzyPIDController* pid, float Kp, float Ki, float Kd, float hysteresis);

// 模糊PID计算函数
float FuzzyPID_Calculate(FuzzyPIDController* pid, float setpoint, float current_temp);

// 获取继电器控制状态
int FuzzyPID_GetRelayState(FuzzyPIDController* pid, float output);

// 重置控制器
void FuzzyPID_Reset(FuzzyPIDController* pid);

#endif
