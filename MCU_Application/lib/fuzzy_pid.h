#ifndef FUZZY_PID_H
#define FUZZY_PID_H

#include "stm32f4xx_hal.h"

// 模糊集合定义
typedef enum {
    NB = 0,  // 负大
    NM,      // 负中
    NS,      // 负小
    ZO,      // 零
    PS,      // 正小
    PM,      // 正中
    PB       // 正大
} FuzzySet;

// 模糊PID控制器结构体
typedef struct {
    // 基本参数
    float Kp;         // 当前比例系数
    float Ki;         // 当前积分系数
    float Kd;         // 当前微分系数
    
    // 基础参数（模糊调整的基准）
    float Kp_base;    // 基础比例系数
    float Ki_base;    // 基础积分系数
    float Kd_base;    // 基础微分系数
    
    // 温度参数
    int16_t setpoint; // 目标温度(10倍值)
    int16_t last_temp;// 上一次温度值
    int16_t error;    // 当前误差(测量值-目标值)
    int16_t error_dot;// 误差变化率
    
    // 控制参数
    uint32_t control_period; // 控制周期(ms)
    uint16_t output;         // 输出值(0-1023)
    
    // 输出限制
    uint16_t output_min;
    uint16_t output_max;
    
    // 积分项及限制
    float integral;
    float integral_limit;
    
    // 模糊控制参数范围
    int16_t error_range;     // 误差范围
    int16_t error_dot_range; // 误差变化率范围
} FuzzyPID_HandleTypeDef;

// 函数声明
void FuzzyPID_Init(FuzzyPID_HandleTypeDef *pid, float Kp, float Ki, float Kd,
                  uint16_t output_min, uint16_t output_max, float integral_limit,
                  uint32_t control_period, int16_t error_range, int16_t error_dot_range);
void FuzzyPID_SetSetpoint(FuzzyPID_HandleTypeDef *pid, int16_t setpoint);
uint16_t FuzzyPID_Compute(FuzzyPID_HandleTypeDef *pid, int16_t current_temp);
static void Fuzzy_AdjustParams(FuzzyPID_HandleTypeDef *pid);
static FuzzySet Fuzzy_GetErrorSet(FuzzyPID_HandleTypeDef *pid);
static FuzzySet Fuzzy_GetErrorDotSet(FuzzyPID_HandleTypeDef *pid);

#endif /* FUZZY_PID_H */
    
									
									
									
									
									
									
									
									
									
									
									
									
									
									
									
									
									
									
									
									
									
