#include "FuzzyPIDController.h"
/*****************************************************************************/
// 初始化模糊PID控制器
void FuzzyPID_Init(FuzzyPIDController* pid, float Kp, float Ki, float Kd) {
	pid->Kp = Kp;
	pid->Ki = Ki;
	pid->Kd = Kd;
	pid->prev_error = 0.0f;
	pid->integral = 0.0f;
	pid->output = 0.0f;
}

// 模糊化处理函数
float fuzzy_adjustment(float error, float error_rate) {
    // 简单模糊规则：根据误差和误差变化率调整增益
    float adjustment = 1.0f;
    
    // 大误差时增强P和D作用
    if (fabs(error) > 5.0f) {
        adjustment *= 1.5f;
    }
    // 小误差时增强I作用
    else if (fabs(error) < 1.0f) {
        adjustment *= 0.7f;
    }
    
    // 误差快速变化时增强D作用
    if (fabs(error_rate) > 2.0f) {
        adjustment *= 1.3f;
    }
    
    return adjustment;
}

// 模糊PID计算函数
float FuzzyPID_Calculate(FuzzyPIDController* pid, float setpoint, float current_temp) {
    float error = setpoint - current_temp;
    float error_rate = error - pid->prev_error;
    
    // 模糊调整增益
    float fuzzy_factor = fuzzy_adjustment(error, error_rate);
    
    // 计算PID各项
    float proportional = pid->Kp * error * fuzzy_factor;
    
    pid->integral += pid->Ki * error;
    // 积分限幅
    pid->integral = (pid->integral > MAX_OUTPUT) ? MAX_OUTPUT : pid->integral;
    pid->integral = (pid->integral < MIN_OUTPUT) ? MIN_OUTPUT : pid->integral;
    
    float derivative = pid->Kd * error_rate * fuzzy_factor;
    
    // 计算总输出
    pid->output = proportional + pid->integral + derivative;    
    pid->prev_error = error;
    
    return pid->output;
}

// 示例使用方式
/*
int main() {
    FuzzyPIDController pid;
    FuzzyPID_Init(&pid, 2.0f, 0.5f, 1.0f);  // 初始化PID参数
    
    float setpoint = 25.0f;  // 目标温度
    float current_temp = 30.0f;  // 当前温度
    
    // 在循环中调用
    float output = FuzzyPID_Calculate(&pid, setpoint, current_temp);
    
    // 将output转换为半导体制冷器的控制信号
    // ...
    
    return 0;
}
*/
