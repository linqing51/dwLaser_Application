#include "classic_pid.h"

#if (CONFIG_USING_CLASSIC_PID == 1)
/* 时间戳函数实例(需根据平台实现，此处为HAL库示例) */
//PID_GetTickFunc_t PID_GetTick = HAL_GetTick;

/* 私有函数：输出限幅 */
static int32_t PID_LimitOutput(int32_t output)
{
    if (output > PID_MAX_OUTPUT) {
        return PID_MAX_OUTPUT;
    } else if (output < PID_MIN_OUTPUT) {
        return PID_MIN_OUTPUT;
    }
    return output;
}

/* 私有函数：自整定核心逻辑 */
static void PID_AutoTuneProcess(PID_Controller_t *pid)
{
    if (pid == NULL || PID_GetTick == NULL) {
        return;
    }

    switch (pid->tune_state) {
        case PID_TUNE_START:
            pid->tick_start = PID_GetTick();
            pid->tune_temp_max = pid->curr_temp;
            pid->tune_temp_min = pid->curr_temp;
            pid->osc_cnt = 0;
            pid->cross_flag = false;
            pid->tune_state = PID_TUNE_WAIT_OSC;
            printf("PID Auto Tune Start...\r\n");
            break;

        case PID_TUNE_WAIT_OSC: {
            // 更新温度极值
            pid->tune_temp_max = (pid->curr_temp > pid->tune_temp_max) ? pid->curr_temp : pid->tune_temp_max;
            pid->tune_temp_min = (pid->curr_temp < pid->tune_temp_min) ? pid->curr_temp : pid->tune_temp_min;

            // 计算温差和时间差
            int16_t temp_diff = pid->tune_temp_max - pid->tune_temp_min;
            uint32_t time_diff = PID_GetTick() - pid->tick_start;

            // 检测温度穿越设定值
            if ((pid->last_osc_temp < pid->setpoint && pid->curr_temp >= pid->setpoint) ||
                (pid->last_osc_temp > pid->setpoint && pid->curr_temp <= pid->setpoint)) {
                pid->cross_flag = true;
            }

            // 振荡判定：温差达标 + 穿越设定值 + 时间稳定
            if (temp_diff > PID_OSC_TEMP_THRESH && pid->cross_flag && time_diff > PID_OSC_TIME_MIN) {
                pid->osc_cnt++;
                pid->cross_flag = false;
                pid->tune_temp_max = pid->curr_temp;
                pid->tune_temp_min = pid->curr_temp;
                printf("Oscillation Count: %d\r\n", pid->osc_cnt);

                // 动态调整临界比例系数(防止振荡过强/过弱)
                if (pid->osc_cnt == 1 && temp_diff > PID_OSC_TEMP_THRESH * 2) {
                    pid->tune_kp_critical *= 0.8f; // 振荡过强，降低KP
                } else if (pid->osc_cnt == 1 && temp_diff < PID_OSC_TEMP_THRESH) {
                    pid->tune_kp_critical *= 1.2f; // 振荡过弱，提升KP
                }
            }

            // 满足整定条件：3次振荡 + 稳定时间
            if (pid->osc_cnt >= 3 && time_diff > PID_TUNE_STABLE_TIME) {
                pid->tune_period = time_diff / pid->osc_cnt;
                pid->tune_state = PID_TUNE_CALC_PARAM;
            }

            pid->last_osc_temp = pid->curr_temp;
            break;
        }

        case PID_TUNE_CALC_PARAM: {
            // Ziegler-Nichols公式(位置式PID优化版)
            float tune_period_sec = (float)pid->tune_period / 1000.0f;
            pid->Kp = 0.6f * pid->tune_kp_critical;
            pid->Ki = pid->Kp / (1.0f * tune_period_sec);  // 位置式Ki适配
            pid->Kd = pid->Kp * (0.125f * tune_period_sec);

            // 参数合法性修正
            pid->Ki = (pid->Ki < 0.001f) ? 0.001f : pid->Ki;
            pid->Kd = (pid->Kd < 0.0f) ? 0.0f : pid->Kd;
            pid->Kd = (pid->Kd > 1000.0f) ? 1000.0f : pid->Kd;

            // 输出整定结果
            printf("=====PID Auto Tune Result==========\r\n");
            printf("Critical Kp: %.3f\r\n", pid->tune_kp_critical);
            printf("Critical Period: %d ms\r\n", pid->tune_period);
            printf("Tuned Kp = %.3f\r\n", pid->Kp);
            printf("Tuned Ki = %.3f\r\n", pid->Ki);
            printf("Tuned Kd = %.3f\r\n", pid->Kd);
            printf("====================================\r\n");

            pid->tune_state = PID_TUNE_IDLE;
            break;
        }

        default:
            break;
    }
}

/* 公开函数：初始化PID */
void PID_Init(PID_Controller_t *pid, float kp, float ki, float kd,
              int16_t setpoint, int32_t integ_limit, int16_t env_temp, float feed_gain)
{
    if (pid == NULL) {
        return;
    }

    // 基础参数初始化
    pid->Kp = (kp >= 0.0f) ? kp : 0.0f;
    pid->Ki = (ki >= 0.0f) ? ki : 0.0f;
    pid->Kd = (kd >= 0.0f) ? kd : 0.0f;
    pid->setpoint = (setpoint >= 0) ? setpoint : 0;
    pid->integ_limit = (integ_limit > 0) ? integ_limit : 1000;

    // 运行时状态初始化
    pid->curr_temp = 0;
    pid->last_temp = 0;
    pid->diff_filter = 0.0f;
    pid->integ_sum = 0.0f;
    pid->output = 0;

    // 自整定参数初始化
    pid->tune_state = PID_TUNE_IDLE;
    pid->tune_kp_critical = 2.0f;
    pid->tune_period = 0;
    pid->tune_temp_max = 0;
    pid->tune_temp_min = 0;
    pid->osc_cnt = 0;
    pid->tick_start = 0;
    pid->last_osc_temp = 0;
    pid->cross_flag = false;

    // 前馈参数初始化
    pid->env_temp = (env_temp >= 0) ? env_temp : PID_TEMP_SCALE * 25; // 默认25℃
    pid->feedforward_gain = (feed_gain >= 0.0f) ? feed_gain : 0.1f;
}

/* 公开函数：设置PID参数 */
bool PID_SetParams(PID_Controller_t *pid, float kp, float ki, float kd)
{
    if (pid == NULL || kp < 0.0f || ki < 0.0f || kd < 0.0f) {
        return false; // 参数非法
    }

    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    return true;
}

/* 公开函数：设置目标温度 */
bool PID_SetSetpoint(PID_Controller_t *pid, int16_t setpoint)
{
    if (pid == NULL || setpoint < 0) {
        return false;
    }
    pid->setpoint = setpoint;
    return true;
}

/* 公开函数：设置前馈参数 */
bool PID_SetFeedforward(PID_Controller_t *pid, int16_t env_temp, float feed_gain)
{
    if (pid == NULL || env_temp < 0 || feed_gain < 0.0f) {
        return false;
    }
    pid->env_temp = env_temp;
    pid->feedforward_gain = feed_gain;
    return true;
}

/* 公开函数：启动自整定 */
bool PID_StartAutoTune(PID_Controller_t *pid)
{
    if (pid == NULL || pid->tune_state != PID_TUNE_IDLE || PID_GetTick == NULL) {
        return false;
    }
    pid->tune_state = PID_TUNE_START;
    return true;
}

/* 公开函数：PID计算核心 */
int32_t PID_Compute(PID_Controller_t *pid, int16_t current_temp)
{
    if (pid == NULL || PID_GetTick == NULL) {
        return 0;
    }

    // 更新当前/历史温度
    pid->last_temp = pid->curr_temp;
    pid->curr_temp = current_temp;

    // 自整定优先执行
    if (pid->tune_state != PID_TUNE_IDLE) {
        PID_AutoTuneProcess(pid);
        // 自整定输出：临界比例系数*误差(限幅)
        int16_t err = pid->setpoint - current_temp;
        pid->output = PID_LimitOutput((int32_t)(pid->tune_kp_critical * err));
        return pid->output;
    }

    // 1. 计算偏差
    int16_t error = pid->setpoint - current_temp;

    // 2. 前馈控制计算
    int32_t feedforward = (int32_t)((pid->setpoint - pid->env_temp) * pid->feedforward_gain);

    // 3. 位置式PID计算
    float p_term = pid->Kp * error; // 比例项

    float i_term = 0.0f;
    // 积分分离：偏差小于阈值时才积分
    if (abs(error) < PID_INTEG_SEP_THRESH) {
        i_term = pid->Ki * error;
        pid->integ_sum += i_term;
        // 积分限幅
        pid->integ_sum = (pid->integ_sum > pid->integ_limit) ? pid->integ_limit : pid->integ_sum;
        pid->integ_sum = (pid->integ_sum < -pid->integ_limit) ? -pid->integ_limit : pid->integ_sum;
    }

    // 微分项：带一阶滤波，降低噪声影响
    float diff = current_temp - pid->last_temp;
    pid->diff_filter = PID_DIFF_FILTER_ALPHA * diff + (1 - PID_DIFF_FILTER_ALPHA) * pid->diff_filter;
    float d_term = -pid->Kd * pid->diff_filter; // 负号：微分负反馈

    // 4. 总输出 = 比例 + 积分 + 微分 + 前馈
    float total_output = p_term + pid->integ_sum + d_term + feedforward;
    pid->output = PID_LimitOutput((int32_t)total_output);

    return pid->output;
}

#endif






