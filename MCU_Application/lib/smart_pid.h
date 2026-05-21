#ifndef __SMART_PID_H__
#define __SMART_PID_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include <stdint.h>
#include <math.h>
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "AppConfig.h"
#include "BoardConfig.h"
/*****************************************************************************/
#if (CONFIG_USING_SMART_PID == 1)
// 最大TEC驱动电压，用于输出限幅保护硬件
#define MAX_TEC_VOLTAGE 5.0f 

typedef enum {// 辨识状态枚举
	IDENTIFY_IDLE = 0,      // 空闲状态，等待触发条件
	IDENTIFY_STEP_ON,       // 阶跃激励进行中，正在观测温度斜率
	IDENTIFY_COMPLETED      // 辨识完成，PID参数已就绪
} IdentifyState_t;

typedef struct {
// 智能PID控制器结构体
	// --- 基础PID参数 ---
	float target;           // 目标设定温度 (℃)
	float kp;               // 比例系数
	float ki;               // 积分系数
	float kd;               // 微分系数
	
	// --- 运算中间变量 ---
	float integral;         // 积分累积项
	float prev_error;       // 上一次的温度误差
	float prev_measurement; // 上一次的实测温度（用于微分先行计算）
	
	// --- 开环辨识专用变量 ---
	IdentifyState_t identify_state; // 当前辨识状态
	float identify_start_time;      // 阶跃激励开始的时间戳
	float temp_before_step;         // 施加阶跃前的初始温度
	float step_power;               // 辨识阶段使用的安全测试功率 (0.0~1.0)   
} SmartPID_Controller;

// --- 对外接口函数声明 ---

/**
 * @brief 初始化PID控制器
 * @param pid 控制器结构体指针
 * @param target_temp 设定的目标温度
 * @note 调用此函数后，系统会自动进入 IDENTIFY_IDLE 状态
 */
void SmartPID_Init(SmartPID_Controller *pid, float target_temp);

/**
 * @brief 执行开环阶跃辨识逻辑
 * @param pid 控制器结构体指针
 * @param current_temp 当前采集到的实际温度
 * @return 1 表示辨识已完成或已跳过；0 表示辨识仍在进行中
 * @note 必须在主循环中周期性调用，仅在满足高温条件时触发短暂的安全观测
 */
uint8_t SmartPID_Identify(SmartPID_Controller *pid, float current_temp, float *tec_out);

/**
 * @brief 计算单向制冷输出功率
 * @param pid 控制器结构体指针
 * @param current_temp 当前采集到的实际温度
 * @return 制冷功率比例，范围严格限制在 0.0f (关闭) ~ 1.0f (最大制冷)
 * @note 内含零误差截断与抗积分饱和逻辑，专为单冷TEC优化
 */
float SmartPID_Compute(SmartPID_Controller *pid, float current_temp);
/*****************************************************************************/
#endif

#ifdef __cplusplus
}
#endif
#endif










