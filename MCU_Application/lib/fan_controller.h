 #ifndef __FAN_CONTROLLER_H__
#define __FAN_CONTROLLER_H__
/*****************************************************************************/
#include "stm32f4xx.h"
#include <stdint.h>
#include <stdbool.h>
#include "appConfig.h"
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
typedef struct{//温度-转速曲线点结构体（温度单位: °C，转速单位: 占空比0-100）
	float temperature;  // 温度值(°C)
	uint8_t speed;      // 对应转速(0-100%)
}TempSpeedPoint;

typedef struct{//风扇控制器结构体（封装状态、配置和硬件接口）
	// 配置参数
	TempSpeedPoint* speed_curve;       // 温度-转速曲线
	uint16_t curve_point_count;        // 曲线点数量
	uint8_t max_step;                  // 最大转速步进（1-5）
	float temp_smooth_factor;          // 温度滤波系数（0-1）
	uint8_t min_speed;                 // 最小转速限制
	uint8_t max_speed;                 // 最大转速限制    
	// 状态变量
	float current_temp;                // 当前温度（原始值）
	float filtered_temp;               // 滤波后温度
	uint8_t target_speed;              // 目标转速
	uint8_t current_speed;             // 当前输出转速
}FanController;

/**
 * @brief 初始化风扇控制器
 * @param fan：控制器实例
 * @param curve：温度-转速曲线数组
 * @param point_count：曲线点数量（显式传入）
 * @param max_step：最大转速步进
 * @param temp_filter：温度滤波系数（0-1）
 * @param min_spd：最小转速
 * @param max_spd：最大转速
 * @param hw：硬件接口函数指针结构体
 */
void FanController_Init(FanController* fan,
                       TempSpeedPoint* curve,
                       uint16_t point_count,
                       uint8_t max_step,
                       float temp_filter,
                       uint8_t min_spd,
                       uint8_t max_spd);

/**
 * @brief 执行一次风扇控制逻辑（建议100ms调用一次）
 * @param fan：控制器实例
 */
void FanController_Run(FanController* fan);

/**
 * @brief 动态更新转速曲线
 * @param fan：控制器实例
 * @param new_curve：新曲线数组
 * @param new_point_count：新曲线点数量
 */
void FanController_UpdateCurve(FanController* fan,
                              TempSpeedPoint* new_curve,
                              uint16_t new_point_count);

/**
 * @brief 获取当前控制器状态（温度、转速等）
 * @param fan：控制器实例
 * @param temp：输出参数（当前滤波后温度）
 * @param speed：输出参数（当前转速）
 * @param target：输出参数（目标转速）
 */
void FanController_GetState(FanController* fan,
                           float* temp,
                           uint8_t* speed,
                           uint8_t* target);

													 
extern TempSpeedPoint fan_curve_0[CONFIG_FAN_CURVE_POINTS];
extern TempSpeedPoint fan_curve_1[CONFIG_FAN_CURVE_POINTS];	
extern TempSpeedPoint fan_curve_2[CONFIG_FAN_CURVE_POINTS];
extern TempSpeedPoint fan_curve_3[CONFIG_FAN_CURVE_POINTS];
extern TempSpeedPoint fan_curve_4[CONFIG_FAN_CURVE_POINTS];	
extern TempSpeedPoint fan_curve_5[CONFIG_FAN_CURVE_POINTS];
extern TempSpeedPoint fan_curve_6[CONFIG_FAN_CURVE_POINTS];
extern TempSpeedPoint fan_curve_7[CONFIG_FAN_CURVE_POINTS];																 
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
												 
#endif
