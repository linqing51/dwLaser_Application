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
  
  // 初始化自整定状态
  pid->tune_state = PID_AUTO_TUNE_IDLE;
  pid->tune_kp_critical = 0.0f;
  pid->tune_period = 0;
  pid->osc_cnt = 0;
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

void PID_StartAutoTune(PID_Controller_t *pid){// 手动启动PID参数自整定
  if(pid->tune_state == PID_AUTO_TUNE_IDLE){
    pid->tune_state = PID_AUTO_TUNE_START;
    pid->tune_kp_critical = 1.0f;
    pid->osc_cnt = 0;
    pid->tune_temp_max = pid->setpoint;
    pid->tune_temp_min = pid->setpoint;
    printf("PID Done...\r\n");
  }
}

// 自整定逻辑处理（内嵌在计算函数）
static void PID_AutoTuneProcess(PID_Controller_t *pid, int16_t curr_temp){
  switch (pid->tune_state){
    case PID_AUTO_TUNE_START:{
      pid->tick_start = HAL_GetTick();
      pid->tune_state = PID_AUTO_TUNE_WAIT_OSC;
      break;
    }
    case PID_AUTO_TUNE_WAIT_OSC:{
      // 捕捉温度峰值谷值，判定振荡
      if(curr_temp > pid->tune_temp_max){
        pid->tune_temp_max = curr_temp;
      }
      if(curr_temp < pid->tune_temp_min){
        pid->tune_temp_min = curr_temp;
      }
      // 出现一次完整波峰波谷判定一次振荡
      if((pid->tune_temp_max - pid->tune_temp_min) > 5){
        pid->osc_cnt++;
        pid->tune_temp_max = curr_temp;
        pid->tune_temp_min = curr_temp;
      }
      // 振荡3次后停止振荡，计算参数
      if(pid->osc_cnt >= 3){
        pid->tune_period = HAL_GetTick() - pid->tick_start;
        pid->tune_state = PID_AUTO_TUNE_CALC_PARAM;
      }
      break;
    }
    case PID_AUTO_TUNE_CALC_PARAM:{
      // 临界比例度法整定公式
      pid->Kp = 0.6f * pid->tune_kp_critical;
      pid->Ki = 2.0f * pid->Kp / pid->tune_period;
      pid->Kd = pid->Kp * pid->tune_period / 8.0f;

      // 输出整定后参数
      printf("=====PID Done==========\r\n");
      printf("Kp = %.3f\r\n", pid->Kp);
      printf("Ki = %.3f\r\n", pid->Ki);
      printf("Kd = %.3f\r\n", pid->Kd);
      printf("=======================\r\n");

      pid->tune_state = PID_AUTO_TUNE_IDLE;
      break;
    }
    default:{
      break;
    }
  }
}

int32_t PID_Compute(PID_Controller_t *pid, int16_t current_temp){// 增量式PID计算
  // 自整定运行中，优先执行整定逻辑
  if(pid->tune_state != PID_AUTO_TUNE_IDLE){
    PID_AutoTuneProcess(pid, current_temp);
    // 整定过程简单比例输出促振荡
    int16_t err = current_temp - pid->setpoint;
    pid->output = pid->tune_kp_critical * err;
    // 限幅
    if(pid->output > pid->max_output){
      pid->output = pid->max_output;
    }
    if(pid->output < pid->min_output){
      pid->output = pid->min_output;
    }
    // 更新历史温度
    pid->prev_temp = pid->last_temp;
    pid->last_temp = current_temp;
    return pid->output;
  }

  // 常规增量PID运算
  int16_t error = current_temp - pid->setpoint;
  
  float delta_p = pid->Kp * (error - (current_temp - pid->last_temp));
  float delta_i = pid->Ki * error;
  float delta_d = pid->Kd * (error - 2*(current_temp - pid->last_temp) + 
                            (pid->last_temp - pid->prev_temp));
  
  float delta_output = delta_p + delta_i + delta_d;
  pid->output += delta_output;
    
  // 输出限幅
  if (pid->output > pid->max_output){
    pid->output = pid->max_output;
  }
  else if (pid->output < pid->min_output){
    pid->output = pid->min_output;
  }
  // 更新历史值
  pid->prev_temp = pid->last_temp;
  pid->last_temp = current_temp;
  return pid->output;
}

#endif
















