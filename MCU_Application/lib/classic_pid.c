#include "classic_pid.h"
#include <stdio.h>  // 用于终端输出

#if CONFIG_USING_CLASSIC_PID == 1

// 系统TICK获取函数（需根据硬件实现，此处为示例）
#define GET_TICK() HAL_GetTick()  // STM32 HAL库默认毫秒级TICK

// 自整定核心参数（可根据系统调整）
#define TUNE_TIMEOUT_MS    300000  // 整定超时时间(30秒)
#define TUNE_OSC_MIN_COUNT 3      // 最小振荡次数
#define TUNE_PEAK_DELTA    6      // 温度峰值判定阈值(10倍实际温度，如5=0.5℃)

// 初始化PID控制器
void PID_Init(PID_Controller_t *pid, float kp, float ki, float kd, int16_t setpoint, int32_t integral_limit){
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->setpoint = setpoint;
    pid->last_temp = 0;
    pid->prev_temp = 0;
    pid->output = 0;
    pid->last_error_c = 0;
    pid->prev_error_c = 0;
    pid->first_run = 1;
    pid->min_output = 0;
    pid->max_output = 4095;
    pid->integral_limit = integral_limit;

    // 初始化自整定变量
    pid->tune_state = PID_TUNE_IDLE;
    pid->tune_start_tick = 0;
    pid->tune_current_tick = 0;
    pid->tune_period = 0;
    pid->tune_max_temp = 0;
    pid->tune_min_temp = 0;
    pid->tune_error_peak = 0;
    pid->tune_osc_count = 0;
    pid->tune_osc_threshold = TUNE_OSC_MIN_COUNT;
    pid->tune_is_peak = 0;
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

// 启动PID自整定
void PID_StartTune(PID_Controller_t *pid) {
    pid->tune_state = PID_TUNE_RUNNING;
    pid->tune_start_tick = GET_TICK();
    pid->tune_max_temp = pid->last_temp;
    pid->tune_min_temp = pid->last_temp;
    pid->tune_osc_count = 0;
    pid->tune_is_peak = 0;
    pid->tune_error_peak = 0;
    pid->tune_period = 0;

    // 终端输出整定启动信息
    printf("PID Auto-tune start. Setpoint: %d, Timeout: %dms\r\n", 
           pid->setpoint, TUNE_TIMEOUT_MS);
}

// 峰值检测（内部函数）
static void PID_Tune_PeakDetect(PID_Controller_t *pid, int16_t current_temp) {
    //int16_t error = current_temp - pid->setpoint;

    // 检测最大值峰值
    if (current_temp > pid->tune_max_temp + TUNE_PEAK_DELTA) {
        pid->tune_max_temp = current_temp;
        pid->tune_is_peak = 1;
    }
    // 检测最小值峰值（振荡谷值）
    if (current_temp < pid->tune_min_temp - TUNE_PEAK_DELTA) {
        pid->tune_min_temp = current_temp;
        pid->tune_is_peak = 2;
    }

    // 峰值确认（温度反向变化）
    if (pid->tune_is_peak == 1 && current_temp < pid->tune_max_temp - TUNE_PEAK_DELTA) {
        // 记录误差峰值
        pid->tune_error_peak = pid->tune_max_temp - pid->setpoint;
        pid->tune_osc_count++;
        pid->tune_is_peak = 0;
        // 输出振荡信息
        printf("PID Tune: Oscillation %d, Peak temp: %d, Error peak: %d\r\n",
               pid->tune_osc_count, pid->tune_max_temp, pid->tune_error_peak);
        // 重置极值用于下次检测
        pid->tune_min_temp = current_temp;
    } else if (pid->tune_is_peak == 2 && current_temp > pid->tune_min_temp + TUNE_PEAK_DELTA) {
        pid->tune_osc_count++;
        pid->tune_is_peak = 0;
        // 输出振荡信息
        printf("PID Tune: Oscillation %d, Valley temp: %d\r\n",
               pid->tune_osc_count, pid->tune_min_temp);
        // 重置极值用于下次检测
        pid->tune_max_temp = current_temp;
    }
}

    // 标准增量式PID计算(集成自整定)
    // 误差统一换算为摄氏度(输入×10单位), 参数语义: Kp/Ki/Kd 为 %/℃, 输出=百分比×4095/100
    // Δu = Kp*(e(k)-e(k-1)) + Ki*e(k) + Kd*(e(k)-2e(k-1)+e(k-2))
    // (原实现微分项系数错乱(-1,+3,-1)、比例项滞后一拍、误差符号反向, 导致噪声放大与输出极限环振荡, 已修正)
    int32_t PID_Compute(PID_Controller_t *pid, int16_t current_temp) {
    // 自整定逻辑（优先执行）
    if (pid->tune_state == PID_TUNE_RUNNING) {
        pid->tune_current_tick = GET_TICK();
        
        // 1. 检测整定超时
        if (pid->tune_current_tick - pid->tune_start_tick > TUNE_TIMEOUT_MS) {
            pid->tune_state = PID_TUNE_FAILED;
            printf("PID Auto-tune failed: Timeout\r\n");
        }

        // 2. 峰值检测与振荡计数
        PID_Tune_PeakDetect(pid, current_temp);

        // 3. 满足振荡次数，计算PID参数（Ziegler-Nichols法）
        if (pid->tune_osc_count >= pid->tune_osc_threshold * 2) { // 2次完整振荡
            // 计算振荡周期
            pid->tune_period = (pid->tune_current_tick - pid->tune_start_tick) / pid->tune_osc_count;
            // Ziegler-Nichols参数计算（适用于增量式PID）
            double Kp_tune = 0.6 * pid->tune_error_peak / pid->max_output * 100;
            double Ki_tune = Kp_tune / (pid->tune_period / 1000.0f) * 0.5;
            double Kd_tune = Kp_tune * (pid->tune_period / 1000.0f) * 0.125;

            // 更新PID参数
            PID_SetParams(pid, Kp_tune, Ki_tune, Kd_tune);
            pid->tune_state = PID_TUNE_COMPLETED;

            // 终端输出整定结果
            printf("PID Auto-tune completed!\r\n");
            printf("Tune result - Period: %dms, Kp: %.2f, Ki: %.4f, Kd: %.2f\r\n",
                   pid->tune_period, pid->Kp, pid->Ki, pid->Kd);
        }
    }

    // 误差换算为摄氏度(输入为×10单位, 如280=28.0℃), 符号: 正误差=需要制冷
    float e_c = ((float)pid->setpoint - (float)current_temp) / 10.0f;

    // 首运行初始化误差历史, 消除第一个控制周期的启动冲击
    if (pid->first_run) {
        pid->last_error_c = e_c;
        pid->prev_error_c = e_c;
        pid->first_run = 0;
    }

    // 误差死区 ±0.1℃: 稳态小幅噪声不再驱动输出, 防极限环微振
    if (e_c < 0.1f && e_c > -0.1f) {
        e_c = 0.0f;
    }

    // 标准增量式PID三项
    float delta_p = pid->Kp * (e_c - pid->last_error_c);
    float delta_i = pid->Ki * e_c;
    float delta_d = pid->Kd * (e_c - 2.0f * pid->last_error_c + pid->prev_error_c);

    // 输出增量: 百分比(%/周期) 映射为 0~4095 计数
    float delta_output = (delta_p + delta_i + delta_d) * (4095.0f / 100.0f);

    // 累加输出并限幅(增量式结构输出钳位即抗积分饱和)
    pid->output += (int32_t)delta_output;
    if (pid->output > pid->max_output) {
        pid->output = pid->max_output;
    } else if (pid->output < pid->min_output) {
        pid->output = pid->min_output;
    }

    // 保存误差历史与温度历史(温度历史兼容自整定)
    pid->prev_error_c = pid->last_error_c;
    pid->last_error_c = e_c;
    pid->prev_temp = pid->last_temp;
    pid->last_temp = current_temp;
    
    // 输出当前PID状态（仅自整定过程中）
    if (pid->tune_state == PID_TUNE_RUNNING) {
        printf("PID Tune: Current temp: %d, Error: %d, Output: %d\r\n",
               current_temp, (int32_t)(e_c * 10.0f), pid->output);
    }

    return pid->output;
}

#endif












