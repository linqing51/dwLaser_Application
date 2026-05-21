#include "classic_pid.h"

#if CONFIG_USING_CLASSIC_PID == 1

void PID_Init(PID_Controller_t *pid, float kp, float ki, float kd, int16_t setpoint, int32_t integral_limit){// 初始化PID控制器
	pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;
	pid->setpoint = setpoint;
	pid->last_temp = 0;
	pid->prev_temp = 0;
	pid->output = 0;
	pid->min_output = 0;
	pid->max_output = 4095;
	pid->integral_limit = integral_limit;
}

// 设置PID参数
void PID_SetParams(PID_Controller_t *pid, float kp, float ki, float kd) {
	pid->Kp = kp;
	pid->Ki = ki;
	pid->Kd = kd;
}

// 设置温度目标值
void PID_SetSetpoint(PID_Controller_t *pid, int16_t setpoint) {
    pid->setpoint = setpoint;
}

// 增量式PID计算
int32_t PID_Compute(PID_Controller_t *pid, int16_t current_temp) {
    // 计算当前误差 (测量温度越高，输出越大，因此误差 = 当前温度 - 设定值)
    int16_t error = current_temp - pid->setpoint;
    
    // 计算增量式PID的三个部分
    float delta_p = pid->Kp * (error - (current_temp - pid->last_temp));
    float delta_i = pid->Ki * error;
    float delta_d = pid->Kd * (error - 2*(current_temp - pid->last_temp) + 
                              (pid->last_temp - pid->prev_temp));
    
    // 计算输出增量
    float delta_output = delta_p + delta_i + delta_d;
    
    // 更新输出值
    pid->output += delta_output;
    
    // 输出限幅
    if (pid->output > pid->max_output) {
        pid->output = pid->max_output;
    } else if (pid->output < pid->min_output) {
        pid->output = pid->min_output;
    }
    
    // 保存温度历史值，用于下次计算
    pid->prev_temp = pid->last_temp;
    pid->last_temp = current_temp;
    
    return pid->output;
}


#endif
















