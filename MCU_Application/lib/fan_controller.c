#include "fan_controller.h"
/*****************************************************************************/
TempSpeedPoint fan_curve_0[CONFIG_FAN_CURVE_POINTS] = {
  {20.0f, 20}, 
	{25.0f, 30},
	{30.0f, 35},
	{35.0f, 40},
	{40.0f, 45},
	{45.0f, 60},
	{50.0f, 70}, 
	{55.0f, 75}, 
	{60.0f, 85}, 
	{65.0f, 100}
};

TempSpeedPoint fan_curve_1[CONFIG_FAN_CURVE_POINTS] = {
  {20.0f, 20}, 
	{25.0f, 30},
	{30.0f, 35},
	{35.0f, 40},
	{40.0f, 45},
	{45.0f, 60},
	{50.0f, 70}, 
	{55.0f, 75}, 
	{60.0f, 85}, 
	{65.0f, 100}
};

TempSpeedPoint fan_curve_2[CONFIG_FAN_CURVE_POINTS] = {
  {20.0f, 20}, 
	{25.0f, 30},
	{30.0f, 35},
	{35.0f, 40},
	{40.0f, 45},
	{45.0f, 60},
	{50.0f, 70}, 
	{55.0f, 75}, 
	{60.0f, 85}, 
	{65.0f, 100}
};

static void calculate_target_speed(FanController* fan){//内部函数：计算目标转速（基于曲线插值）
	if(fan->curve_point_count < 2){
		fan->target_speed = fan->min_speed;
		return;
	}
	float temp = fan->filtered_temp;
	if(temp <= fan->speed_curve[0].temperature){//低于最低温度点
			fan->target_speed = fan->speed_curve[0].speed;
			return;
	}
	
	if(temp >= fan->speed_curve[fan->curve_point_count - 1].temperature){//高于最高温度点
			fan->target_speed = fan->speed_curve[fan->curve_point_count - 1].speed;
			return;
	}
 
	for (uint16_t i = 0; i < fan->curve_point_count - 1; i++){//区间插值
		TempSpeedPoint* p1 = &fan->speed_curve[i];
		TempSpeedPoint* p2 = &fan->speed_curve[i + 1];
		if (temp >= p1->temperature && temp <= p2->temperature){
			float ratio = (temp - p1->temperature) / (p2->temperature - p1->temperature);
			fan->target_speed = (uint8_t)(p1->speed + ratio * (p2->speed - p1->speed));
			break;
		}
	}
	// 限幅
	if(fan->target_speed < fan->min_speed){
		fan->target_speed = fan->min_speed; 
	}
	if (fan->target_speed > fan->max_speed){
		fan->target_speed = fan->max_speed;
	}
}

void FanController_Init(FanController* fan, TempSpeedPoint* curve, uint16_t point_count, uint8_t max_step, float temp_filter, uint8_t min_spd, uint8_t max_spd){// 初始化控制器
	// 配置参数
	fan->speed_curve = curve;
	fan->curve_point_count = point_count;
	fan->max_step = (max_step > 0) ? max_step : 1;  // 确保步进至少为1
	fan->temp_smooth_factor = (temp_filter < 0) ? 0 : (temp_filter > 1) ? 1 : temp_filter;
	fan->min_speed = min_spd;
	fan->max_speed = (max_spd > min_spd) ? max_spd : min_spd;  // 确保max ≥ min
	// 状态初始化
	fan->current_temp = 0.0f;
	fan->filtered_temp = 0.0f;
	fan->target_speed = min_spd;
	fan->current_speed = min_spd;
}

void FanController_Run(FanController* fan){// 执行控制逻辑（核心循环）
	// 1. 读取温度
	fan->filtered_temp = fan->filtered_temp * (1.0f - fan->temp_smooth_factor) + fan->current_temp * fan->temp_smooth_factor;// 温度滤波（一阶低通）
	// 2. 计算目标转速
	calculate_target_speed(fan);
	// 3. 平滑调节转速
	int16_t diff = fan->target_speed - fan->current_speed;
	if(diff > 0){
		fan->current_speed += (diff > fan->max_step) ? fan->max_step : diff;
	}else if(diff < 0){
		diff = -diff;
		fan->current_speed -= (diff > fan->max_step) ? fan->max_step : diff;
	}
	// 4. 限幅并设置转速（通过硬件接口）
	if(fan->current_speed < fan->min_speed){
		fan->current_speed = fan->min_speed;
	}
	if(fan->current_speed > fan->max_speed){
		fan->current_speed = fan->max_speed;
	}
}

void FanController_UpdateCurve(FanController* fan, TempSpeedPoint* new_curve, uint16_t new_point_count){// 更新转速曲线
	if(new_curve != NULL && new_point_count >= 2){
		fan->speed_curve = new_curve;
		fan->curve_point_count = new_point_count;
	}
}

void FanController_GetState(FanController* fan, float* temp, uint8_t* speed, uint8_t* target){//获取当前状态
	if(temp != NULL){ 
		*temp = fan->filtered_temp;
	}
	if(speed != NULL){
		*speed = fan->current_speed;
	}
	if(target != NULL){
		*target = fan->target_speed;
	}
}






