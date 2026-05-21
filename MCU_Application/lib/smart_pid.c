#include "smart_pid.h"
/*****************************************************************************/
#if (CONFIG_USING_SMART_PID == 1)
// 初始化PID控制器
void SmartPID_Init(SmartPID_Controller *pid, float target_temp) {
	pid->target = target_temp;
	// 预设一组保守的默认参数，防止环境温低于设定值时系统失控
	pid->kp = 2.0f; 
	pid->ki = 0.05f; 
	pid->kd = 10.0f; 
	pid->integral = 0.0f;
	pid->prev_error = 0.0f;
	pid->prev_measurement = 0.0f;
	
	// 辨识状态初始化
	pid->identify_state = IDENTIFY_IDLE;
	pid->identify_start_time = 0.0f;
	pid->temp_before_step = 0.0f;
	pid->step_power = 0.15f; // 使用15%的低功率进行安全辨识，避免过冲
}

// 开环阶跃辨识逻辑（安全无振荡）
// 仅在系统刚启动且当前温度明显高于目标温度时触发
uint8_t SmartPID_Identify(SmartPID_Controller *pid, float current_temp, float *tec_out) {
	float current_time = xTaskGetTickCount();
	if (pid->identify_state == IDENTIFY_IDLE) {
		// 只有当当前温度比目标高5度以上，才执行辨识，避免低温环境误触发
		if (current_temp > pid->target + 5.0f) {
			pid->identify_state = IDENTIFY_STEP_ON;
			pid->identify_start_time = current_time;
			pid->temp_before_step = current_temp;
			//HAL_SetTECPower(pid->step_power); // 施加小幅阶跃激励
			*tec_out = pid->step_power;
		} else {
			// 环境温度已低于设定值，跳过辨识，直接使用默认保守参数
			pid->identify_state = IDENTIFY_COMPLETED;
			return 1; 
		}
	} 
	else if (pid->identify_state == IDENTIFY_STEP_ON) {
			// 持续施加小功率制冷，观测10秒内的温度变化斜率
		if (current_time - pid->identify_start_time >= 10.0f) {
			float temp_drop = pid->temp_before_step - current_temp;
			
			// 如果10秒内温度下降了超过1度，说明系统响应正常，开始计算参数
			if (temp_drop > 1.0f) {
				float slope = temp_drop / 10.0f; // ℃/s
				// 简化的Cohen-Coon整定公式，根据系统惯性自动适配Kp, Ki, Kd
				// 这种方法无需让系统产生振荡，完全避免了温度失控
				pid->kp = (0.9f * pid->step_power) / (slope * 2.0f); 
				pid->ki = pid->kp / (3.0f * 10.0f); 
				pid->kd = pid->kp * (10.0f / 3.0f);
				
				pid->identify_state = IDENTIFY_COMPLETED;
				//HAL_SetTECPower(0.0f); // 辨识结束，关闭输出
				*tec_out = 0.0f;
				return 1; // 辨识完成
			} else {
				// 温度几乎没变，可能是传感器故障或TEC未工作，停止辨识保护系统
				pid->identify_state = IDENTIFY_COMPLETED;
				//HAL_SetTECPower(0.0f);
				*tec_out = 0.0f;
				return 1;
			}
		}
	}
	return 0; // 仍在辨识中
}

// 增量式PID计算（单向制冷专用，带微分先行与抗积分饱和）
float SmartPID_Compute(SmartPID_Controller *pid, float current_temp) {
	if (pid->identify_state != IDENTIFY_COMPLETED) return 0.0f;

	float error = pid->target - current_temp;
	
	// 【关键保护】如果环境温度已经低于设定温度，直接输出0，停止制冷
	// 这解决了单制冷系统在无负载时可能出现的积分负向累积问题
	if (error <= 0) {
		pid->integral = 0.0f; // 清零积分项，防止下次需要制冷时响应迟滞
		pid->prev_error = error;
		pid->prev_measurement = current_temp;
		return 0.0f;
	}
	
	// 比例项 P
	float p_term = pid->kp * error;
	
	// 积分项 I (带抗饱和限幅，防止TEC长时间满负荷运行)
	pid->integral += error;
	if (pid->integral > 50.0f) pid->integral = 50.0f;
	float i_term = pid->ki * pid->integral;
	
	// 微分项 D (微分先行：仅对测量值求微分，避免设定值突变引起TEC电流冲击)
	float d_measurement = current_temp - pid->prev_measurement;
	float d_term = -pid->kd * d_measurement;
	
	pid->prev_measurement = current_temp;
	pid->prev_error = error;
	
	float output = p_term + i_term + d_term;
	
	// 单向输出限幅：严格限制在 0.0 ~ 1.0 之间
	if (output > 1.0f) output = 1.0f;
	if (output < 0.0f) output = 0.0f;
	
	return output;
}

#endif









