#ifndef __PID_TEMP_CONTROL_H__
#define __PID_TEMP_CONTROL_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "stm32f4xx_hal.h" // 根据实际使用的STM32系列修改
#include "AppConfig.h"
#include "BoardConfig.h"
// PID控制器结构体
#if CONFIG_USING_CLASSIC_PID== 1
typedef enum
{
    PID_AUTO_TUNE_IDLE,        // 空闲未整定
    PID_AUTO_TUNE_START,       // 开始整定
    PID_AUTO_TUNE_WAIT_OSC,    // 等待振荡
    PID_AUTO_TUNE_CALC_PARAM   // 计算整定参数
}PID_TuneState_t;


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
  
    // 自整定私有变量
    PID_TuneState_t tune_state;
    float tune_kp_critical;    // 临界比例系数
    uint32_t tune_period;       // 临界振荡周期
    int16_t tune_temp_max;
    int16_t tune_temp_min;
    uint32_t osc_cnt;
    uint32_t tick_start;
}PID_Controller_t;

// 初始化PID控制器
void PID_Init(PID_Controller_t *pid, float kp, float ki, float kd, 
             int16_t setpoint, int32_t integral_limit);

// 设置PID参数
void PID_SetParams(PID_Controller_t *pid, float kp, float ki, float kd);

// 设置温度目标值
void PID_SetSetpoint(PID_Controller_t *pid, int16_t setpoint);

// 增量式PID计算
int32_t PID_Compute(PID_Controller_t *pid, int16_t current_temp);
void PID_StartAutoTune(PID_Controller_t *pid);// 手动启动PID参数自整定

#endif
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif /* PID_TEMP_CONTROL_H */


















