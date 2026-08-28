#ifndef __PID_TEMP_CONTROL_H__
#define __PID_TEMP_CONTROL_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "stm32f4xx_hal.h" // 根据实际使用的STM32系列修改
#include "..\config\myConfig.h"
/*****************************************************************************/
// PID自整定状态枚举
typedef enum {
    PID_TUNE_IDLE = 0,    // 未整定
    PID_TUNE_RUNNING,     // 整定中
    PID_TUNE_COMPLETED,   // 整定完成
    PID_TUNE_FAILED       // 整定失败
} PID_Tune_State_t;

typedef struct {
    // PID参数
    float Kp;           // 比例系数
    float Ki;           // 积分系数
    float Kd;           // 微分系数
    
    // 温度设定值 (10倍实际温度，例如250代表25.0℃)
    int16_t setpoint;
    
    // PID计算中间变量
    int16_t last_temp;  // 上一次温度
    int16_t prev_temp;  // 上上次温度
    int32_t output;     // 当前输出值
    
    // 输出限制
    int16_t min_output;  // 最小输出(0)
    int16_t max_output;  // 最大输出(1023)
    
    // 积分限幅，防止积分饱和
    int32_t integral_limit;

    // 自整定新增变量
    PID_Tune_State_t tune_state;  // 自整定状态
    uint32_t tune_start_tick;     // 整定开始时间(ms)
    uint32_t tune_current_tick;   // 整定当前时间(ms)
    uint32_t tune_period;         // 系统振荡周期(ms)
    int16_t tune_max_temp;        // 整定过程最大温度
    int16_t tune_min_temp;        // 整定过程最小温度
    int16_t tune_error_peak;     // 误差峰值
    uint8_t tune_osc_count;       // 振荡次数计数
    uint8_t tune_osc_threshold;   // 完成整定所需振荡次数(建议≥2)
    uint8_t tune_is_peak;         // 峰值检测标记
}PID_Controller_t;

// 初始化PID控制器
void PID_Init(PID_Controller_t *pid, float kp, float ki, float kd, 
             int16_t setpoint, int32_t integral_limit);

// 设置PID参数
void PID_SetParams(PID_Controller_t *pid, float kp, float ki, float kd);

// 设置温度目标值
void PID_SetSetpoint(PID_Controller_t *pid, int16_t setpoint);

// 增量式PID计算（集成自整定）
int32_t PID_Compute(PID_Controller_t *pid, int16_t current_temp);

// 启动PID参数自整定
void PID_StartTune(PID_Controller_t *pid);

// 半导体制冷片控制初始化
void Thermoelectric_Init(void);

// 设置半导体制冷片输出
void Thermoelectric_SetOutput(uint16_t output);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* PID_TEMP_CONTROL_H */














