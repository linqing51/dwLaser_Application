#include "FuzzyPID_Relay.h"
/*****************************************************************************/
#define MAX_OUTPUT 100.0f
#define MIN_OUTPUT 0.0f
#define RELAY_ON_THRESHOLD 50.0f  // 继电器开启阈值

// 初始化控制器
void FuzzyPID_Init(FuzzyPIDController* pid, float Kp, float Ki, float Kd, float hysteresis) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->prev_error = 0.0f;
    pid->integral = 0.0f;
    pid->output = 0.0f;
    pid->hysteresis = hysteresis;
    pid->relay_state = 0;
}

// 模糊规则函数 - 根据误差动态调整PID行为
static float fuzzy_adjustment(float error, float error_rate) {
    float abs_error = fabsf(error);
    float abs_rate = fabsf(error_rate);
    float factor = 1.0f;
    
    // 大误差区域 - 增强P和D作用，快速响应
    if (abs_error > 3.0f) {
        factor = 1.8f;
    }
    // 中等误差区域 - 平衡控制
    else if (abs_error > 1.0f) {
        factor = 1.2f;
    }
    // 小误差区域 - 增强I作用，精细调节
    else {
        factor = 0.6f;
    }
    
    // 误差快速变化时增强微分作用
    if (abs_rate > 1.5f) {
        factor *= 1.3f;
    }
    
    return factor;
}

// 计算PID输出
float FuzzyPID_Calculate(FuzzyPIDController* pid, float setpoint, float current_temp) {
    float error = setpoint - current_temp;
    float error_rate = error - pid->prev_error;
    
    // 模糊调整
    float fuzzy_factor = fuzzy_adjustment(error, error_rate);
    
    // 计算比例项
    float P = pid->Kp * error * fuzzy_factor;
    
    // 计算积分项（带抗饱和）
    pid->integral += pid->Ki * error;
    if (pid->integral > MAX_OUTPUT) pid->integral = MAX_OUTPUT;
    if (pid->integral < MIN_OUTPUT) pid->integral = MIN_OUTPUT;
    
    // 计算微分项
    float D = pid->Kd * error_rate * fuzzy_factor;
    
    // 计算总输出
    pid->output = P + pid->integral + D;
    
    // 输出限幅
    if (pid->output > MAX_OUTPUT) pid->output = MAX_OUTPUT;
    if (pid->output < MIN_OUTPUT) pid->output = MIN_OUTPUT;
    
    pid->prev_error = error;
    
    return pid->output;
}

// 获取继电器控制状态（带滞回功能）
int FuzzyPID_GetRelayState(FuzzyPIDController* pid, float output) {
    // 滞回控制逻辑
    if (pid->relay_state == 0) {
        // 当前关闭，需要超过阈值+滞回才开启
        if (output > (RELAY_ON_THRESHOLD + pid->hysteresis)) {
            pid->relay_state = 1;
        }
    } else {
        // 当前开启，需要低于阈值-滞回才关闭
        if (output < (RELAY_ON_THRESHOLD - pid->hysteresis)) {
            pid->relay_state = 0;
        }
    }
    
    return pid->relay_state;
}

// 重置控制器状态
void FuzzyPID_Reset(FuzzyPIDController* pid) {
    pid->prev_error = 0.0f;
    pid->integral = 0.0f;
    pid->output = 0.0f;
    pid->relay_state = 0;
}

///**
// * 使用示例 - 主应用程序
// */

//#include <stdio.h>
//#include "fuzzy_pid_controller.h"

//// 模拟温度传感器读取函数
//float read_temperature_sensor(void) {
//    // 这里应该是实际的传感器读取代码
//    static float temp = 30.0f;
//    // 模拟温度变化
//    temp += (rand() % 10 - 5) * 0.1f;
//    return temp;
//}

//// 继电器控制函数
//void control_relay(int state) {
//    if (state) {
//        printf("继电器: 开启制冷\n");
//        // 实际控制继电器的代码
//    } else {
//        printf("继电器: 关闭制冷\n");
//        // 实际控制继电器的代码
//    }
//}

//int main() {
//    FuzzyPIDController pid;
//    
//    // 初始化控制器
//    // 参数针对半导体制冷器优化，通常无需调整
//    FuzzyPID_Init(&pid, 3.0f, 0.8f, 2.0f, 5.0f);  // 滞回宽度5%
//    
//    float setpoint = 25.0f;  // 目标温度
//    
//    printf("开始温度控制，目标温度: %.1f°C\n", setpoint);
//    
//    // 主控制循环
//    for (int i = 0; i < 50; i++) {
//        float current_temp = read_temperature_sensor();
//        
//        // 计算PID输出
//        float output = FuzzyPID_Calculate(&pid, setpoint, current_temp);
//        
//        // 获取继电器状态
//        int relay_state = FuzzyPID_GetRelayState(&pid, output);
//        
//        // 控制继电器
//        control_relay(relay_state);
//        
//        printf("温度: %.2f°C, 输出: %.1f%%, 继电器: %s\n", 
//               current_temp, output, relay_state ? "ON" : "OFF");
//    }
//    
//    return 0;
//}
//程序特点：
//模块化设计：头文件和实现文件分离，便于集成
//继电器优化：内置滞回控制，防止继电器频繁开关
//模糊逻辑：根据误差大小自动调整PID参数
//免调参数：参数已针对半导体制冷器优化
//无时间依赖：完全基于当前状态计算
//抗饱和处理：积分项有限幅保护
//使用方法：
//包含头文件 #include "fuzzy_pid_controller.h"
//声明控制器实例 FuzzyPIDController pid;
//初始化控制器 FuzzyPID_Init(&pid, Kp, Ki, Kd, hysteresis);
//在循环中调用计算函数获取输出
//使用 FuzzyPID_GetRelayState() 获取继电器控制信号
//参数建议值：Kp=3.0, Ki=0.8, Kd=2.0, hysteresis=5.0（针对大多数半导体制冷器）







