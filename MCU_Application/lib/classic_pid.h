#ifndef __CLASSIC_PID_H__
#define __CLASSIC_PID_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include "BoardConfig.h"
#include "AppConfig.h"
#include "sPlc.h"

#if (CONFIG_USING_CLASSIC_PID == 1)

/* 配置项 - 可根据平台调整 */
#define PID_MAX_OUTPUT          4095    // PWM最大输出值(12位ADC)
#define PID_MIN_OUTPUT          0       // PWM最小输出值
#define PID_TEMP_SCALE          10      // 温度放大倍数(eg: 250 = 25.0℃)
#define PID_OSC_TEMP_THRESH     5       // 自整定振荡温差阈值(℃，已放大)
#define PID_OSC_TIME_MIN        1000    // 自整定最小振荡判定时间(ms)
#define PID_TUNE_STABLE_TIME    5000    // 自整定稳定判定时间(ms)
#define PID_DIFF_FILTER_ALPHA   0.2f    // 微分滤波系数(0~1，越小滤波越强)
#define PID_INTEG_SEP_THRESH    20      // 积分分离阈值(℃，已放大)

/* PID自整定状态枚举 */
typedef enum {
    PID_TUNE_IDLE = 0,        // 空闲
    PID_TUNE_START,           // 启动整定
    PID_TUNE_WAIT_OSC,        // 等待振荡
    PID_TUNE_CALC_PARAM       // 计算参数
} PID_TuneState_t;

/* PID控制器结构体 */
typedef struct {
    /* 核心参数 */
    float Kp;                 // 比例系数
    float Ki;                 // 积分系数
    float Kd;                 // 微分系数
    int16_t setpoint;         // 目标温度(放大10倍)
    int32_t integ_limit;      // 积分限幅

    /* 运行时状态 */
    int16_t curr_temp;        // 当前温度(放大10倍)
    int16_t last_temp;        // 上一次温度(放大10倍)
    float diff_filter;        // 微分滤波缓存
    float integ_sum;          // 积分和(替代静态变量)
    int32_t output;           // 当前输出值

    /* 自整定参数 */
    PID_TuneState_t tune_state;
    float tune_kp_critical;   // 临界比例系数
    uint32_t tune_period;     // 临界振荡周期(ms)
    int16_t tune_temp_max;    // 自整定最大温度
    int16_t tune_temp_min;    // 自整定最小温度
    uint32_t osc_cnt;         // 振荡次数
    uint32_t tick_start;      // 自整定启动时间戳(ms)
    int16_t last_osc_temp;    // 上次振荡检测温度
    bool cross_flag;          // 温度穿越设定值标志(替代静态变量)

    /* 前馈控制 */
    int16_t env_temp;         // 环境温度(放大10倍)
    float feedforward_gain;   // 前馈增益
} PID_Controller_t;

/* 时间戳获取函数类型(解耦HAL库) */
typedef uint32_t (*PID_GetTickFunc_t)(void);
extern PID_GetTickFunc_t PID_GetTick; // 需外部实现(如绑定HAL_GetTick)

/* 函数声明 */
// 初始化PID控制器
void PID_Init(PID_Controller_t *pid, float kp, float ki, float kd,
              int16_t setpoint, int32_t integ_limit, int16_t env_temp, float feed_gain);

// 设置PID参数(带合法性校验)
bool PID_SetParams(PID_Controller_t *pid, float kp, float ki, float kd);

// 设置目标温度
bool PID_SetSetpoint(PID_Controller_t *pid, int16_t setpoint);

// 设置前馈参数
bool PID_SetFeedforward(PID_Controller_t *pid, int16_t env_temp, float feed_gain);

// 启动PID自整定
bool PID_StartAutoTune(PID_Controller_t *pid);

// 位置式PID计算核心函数
int32_t PID_Compute(PID_Controller_t *pid, int16_t current_temp);

#ifdef __cplusplus
}
#endif


#endif

#endif /* __CLASSIC_PID_H__ */


