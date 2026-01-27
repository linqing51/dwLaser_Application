#include "fuzzy_pid.h"

// 模糊规则表 - 行:误差 列:误差变化率
// 表格值为[Kp调整系数, Ki调整系数, Kd调整系数]
static const float fuzzy_rules[7][7][3] = {
    // 误差=NB
    {{1.5f, 0.1f, 0.8f}, {1.5f, 0.1f, 0.4f}, {1.0f, 0.2f, 0.2f}, {1.0f, 0.2f, 0.0f}, {0.8f, 0.5f, 0.0f}, {0.8f, 0.5f, 0.0f}, {0.8f, 1.0f, 0.0f}},
    // 误差=NM
    {{1.5f, 0.1f, 0.8f}, {1.5f, 0.1f, 0.4f}, {1.0f, 0.2f, 0.2f}, {1.0f, 0.2f, 0.0f}, {0.8f, 0.5f, 0.0f}, {0.8f, 0.5f, 0.0f}, {0.5f, 1.0f, 0.0f}},
    // 误差=NS
    {{1.0f, 0.2f, 0.8f}, {1.0f, 0.2f, 0.4f}, {1.0f, 0.5f, 0.2f}, {0.8f, 0.5f, 0.0f}, {0.5f, 0.8f, 0.0f}, {0.5f, 1.0f, 0.0f}, {0.2f, 1.0f, 0.2f}},
    // 误差=ZO
    {{1.0f, 0.2f, 0.8f}, {1.0f, 0.5f, 0.4f}, {0.8f, 0.8f, 0.2f}, {0.5f, 1.0f, 0.0f}, {0.2f, 0.8f, 0.2f}, {0.1f, 0.5f, 0.4f}, {0.1f, 0.2f, 0.8f}},
    // 误差=PS
    {{0.8f, 0.2f, 0.8f}, {0.5f, 0.5f, 0.4f}, {0.5f, 0.8f, 0.2f}, {0.2f, 1.0f, 0.0f}, {0.0f, 0.8f, 0.2f}, {0.0f, 0.5f, 0.4f}, {0.0f, 0.2f, 0.8f}},
    // 误差=PM
    {{0.8f, 0.1f, 1.0f}, {0.5f, 0.1f, 0.8f}, {0.2f, 0.2f, 0.8f}, {0.0f, 0.5f, 0.8f}, {0.0f, 0.5f, 1.0f}, {0.0f, 0.2f, 1.0f}, {0.0f, 0.1f, 1.5f}},
    // 误差=PB
    {{0.8f, 0.1f, 1.5f}, {0.5f, 0.1f, 1.5f}, {0.2f, 0.2f, 1.0f}, {0.0f, 0.2f, 1.0f}, {0.0f, 0.5f, 0.8f}, {0.0f, 0.5f, 0.8f}, {0.0f, 0.1f, 1.5f}}
};

// 初始化模糊PID控制器
void FuzzyPID_Init(FuzzyPID_HandleTypeDef *pid, float Kp, float Ki, float Kd,
                  uint16_t output_min, uint16_t output_max, float integral_limit,
                  uint32_t control_period, int16_t error_range, int16_t error_dot_range) {
    pid->Kp_base = Kp;
    pid->Ki_base = Ki;
    pid->Kd_base = Kd;
    
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    
    pid->setpoint = 0;
    pid->last_temp = 0;
    pid->error = 0;
    pid->error_dot = 0;
    
    pid->output = 0;
    pid->output_min = output_min;
    pid->output_max = output_max;
    
    pid->integral = 0.0f;
    pid->integral_limit = integral_limit;
    
    pid->control_period = control_period;
    pid->error_range = error_range;
    pid->error_dot_range = error_dot_range;
}

// 设置目标温度
void FuzzyPID_SetSetpoint(FuzzyPID_HandleTypeDef *pid, int16_t setpoint) {
    pid->setpoint = setpoint;
    // 重置积分项，避免目标变化时积分饱和
    pid->integral = 0.0f;
}

// 计算PID输出
uint16_t FuzzyPID_Compute(FuzzyPID_HandleTypeDef *pid, int16_t current_temp) {
    // 计算当前误差 (测量值 - 目标值)
    // 温度越高，误差越大，输出越大，符合制冷需求
    pid->error = current_temp - pid->setpoint;
    
    // 计算误差变化率 (当前误差 - 上一次误差) / 控制周期
    pid->error_dot = (pid->error - (pid->last_temp - pid->setpoint)) * 1000 / pid->control_period;
    
    // 根据模糊规则调整PID参数
    Fuzzy_AdjustParams(pid);
    
    // 计算比例项
    float proportional = pid->Kp * pid->error;
    
    // 计算积分项 (带抗积分饱和)
    if ((pid->output > pid->output_min && pid->output < pid->output_max) || 
        (pid->error * pid->integral < 0)) {
        pid->integral += pid->Ki * pid->error * pid->control_period / 1000.0f;
        
        // 积分限幅
        if (pid->integral > pid->integral_limit)
            pid->integral = pid->integral_limit;
        else if (pid->integral < -pid->integral_limit)
            pid->integral = -pid->integral_limit;
    }
    
    // 计算微分项
    float derivative = pid->Kd * pid->error_dot;
    
    // 计算总输出
    float total = proportional + pid->integral + derivative;
    
    // 输出限幅
    if (total > pid->output_max)
        pid->output = pid->output_max;
    else if (total < pid->output_min)
        pid->output = pid->output_min;
    else
        pid->output = (uint16_t)total;
    
    // 保存当前温度用于下次计算
    pid->last_temp = current_temp;
    
    return pid->output;
}

// 模糊参数调整
static void Fuzzy_AdjustParams(FuzzyPID_HandleTypeDef *pid) {
    FuzzySet error_set = Fuzzy_GetErrorSet(pid);
    FuzzySet error_dot_set = Fuzzy_GetErrorDotSet(pid);
    
    // 根据模糊规则表调整PID参数
    pid->Kp = pid->Kp_base * fuzzy_rules[error_set][error_dot_set][0];
    pid->Ki = pid->Ki_base * fuzzy_rules[error_set][error_dot_set][1];
    pid->Kd = pid->Kd_base * fuzzy_rules[error_set][error_dot_set][2];
}

// 确定误差的模糊集合
static FuzzySet Fuzzy_GetErrorSet(FuzzyPID_HandleTypeDef *pid) {
    // 归一化误差到[-1, 1]范围
    double norm_error = (float)pid->error / pid->error_range;
    
    if (norm_error <= -0.8) return NB;
    else if (norm_error <= -0.4) return NM;
    else if (norm_error <= -0.1) return NS;
    else if (norm_error <= 0.1) return ZO;
    else if (norm_error <= 0.4) return PS;
    else if (norm_error <= 0.8) return PM;
    else return PB;
}

// 确定误差变化率的模糊集合
static FuzzySet Fuzzy_GetErrorDotSet(FuzzyPID_HandleTypeDef *pid) {
    // 归一化误差变化率到[-1, 1]范围
    double norm_dot = (float)pid->error_dot / pid->error_dot_range;
    
    if (norm_dot <= -0.8) return NB;
    else if (norm_dot <= -0.4) return NM;
    else if (norm_dot <= -0.1) return NS;
    else if (norm_dot <= 0.1) return ZO;
    else if (norm_dot <= 0.4) return PS;
    else if (norm_dot <= 0.8) return PM;
    else return PB;
}
    































