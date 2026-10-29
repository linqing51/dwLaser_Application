/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "fuzzy_pid.h"
/*****************************************************************************/
struct fuzzy *fuzzy_init(unsigned int input_num, unsigned int output_num) {
	struct fuzzy *fuzzy_struct = (struct fuzzy *) malloc(sizeof(struct fuzzy));
	fuzzy_struct->input_num = input_num;
	fuzzy_struct->output_num = output_num;
	fuzzy_struct->mf_type = (unsigned int *) malloc((input_num + output_num) * sizeof(unsigned int));
#ifdef fuzzy_pid_rule_base_deep_copy
	fuzzy_struct->mf_params = (int *) malloc(4 * qf_default * sizeof(int));
	fuzzy_struct->rule_base = (int *) malloc(output_num * qf_default * qf_default * sizeof(int));
#endif
	fuzzy_struct->output = (float *) malloc(output_num * sizeof(float));
	return fuzzy_struct;
}

void delete_fuzzy(struct fuzzy *fuzzy_struct) {
	free(fuzzy_struct->mf_type);
	free(fuzzy_struct->output);
	free(fuzzy_struct);
}

void fuzzy_params_init(struct fuzzy *fuzzy_struct, unsigned int mf_type, unsigned int fo_type, unsigned int df_type, int mf_params[], int rule_base[][qf_default]) {
	for (unsigned int i = 0; i < fuzzy_struct->input_num + fuzzy_struct->output_num; ++i) {
		fuzzy_struct->mf_type[i] = mf_type;
	}
	for (unsigned int i = 0; i < fuzzy_struct->output_num; ++i) {
		fuzzy_struct->output[i] = 0;
	}
#ifdef fuzzy_pid_rule_base_deep_copy
	for (unsigned int j = 0; j < 4 * qf_default; ++j) {
		 fuzzy_struct->mf_params[j] = mf_params[j];
	 }
	 for (unsigned int k = 0; k < fuzzy_struct->output_num * qf_default; ++k) {
		 for (unsigned int i = 0; i < qf_default; ++i) {
				 fuzzy_struct->rule_base[k * 7 + i] = rule_base[k][i];
		 }
	 }
#else
	fuzzy_struct->mf_params = mf_params;
	fuzzy_struct->rule_base = (int *) rule_base;
#endif
	fuzzy_struct->fo_type = fo_type;
	fuzzy_struct->df_type = df_type;
}

#define inverse(parameter) 1.0f/(float)parameter

// Gaussian membership function
float gaussmf(float x, float sigma, float c) {
	float t = (x - c) / sigma;
	return expf(-(t * t));//powf(x,2)→x*x，避免 libm pow 函数调用
}

// Generalized bell-shaped membership function
float gbellmf(float x, float a, float b, float c) {
	return inverse(1.0f + powf(fabsf((x - c) / a), 2.0f * b));
}

// Sigmoidal membership function
float sigmf(float x, float a, float c) {
	return inverse(1.0f + expf(a * (c - x)));
}

// Trapezoidal membership function
float trapmf(float x, float a, float b, float c, float d) {
	if (x >= a && x < b)
		return (x - a) / (b - a);
	else if (x >= b && x < c)
		return 1.0f;
	else if (x >= c && x <= d)
		return (d - x) / (d - c);
	else return 0.0f;
}

// Triangular membership function
float trimf(float x, float a, float b, float c) {
	return trapmf(x, a, b, b, c);
}

// Z-shaped membership function
float zmf(float x, float a, float b) {
	if (x <= a)
		return 1.0f;
	else if (x >= a && x <= (a + b) / 2.0f) {
		float t = (x - a) / (b - a);
		return 1.0f - 2.0f * (t * t);
	}
	else if (x >= (a + b) / 2.0f && x < b) {
		float t = (x - b) / (b - a);
		return 2.0f * (t * t);
	}
	else return 0;
}

// Membership function
float mf(float x, unsigned int mf_type, int *params) {
	switch (mf_type) {
		case 0:
			return gaussmf(x, params[0], params[1]);
		case 1:
			return gbellmf(x, params[0], params[1], params[2]);
		case 2:
			return sigmf(x, params[0], params[2]);
		case 3:
			return trapmf(x, params[0], params[1], params[2], params[3]);
		case 5:
			return zmf(x, params[0], params[1]);
		default: // set triangular as default membership function
			return trimf(x, params[0], params[1], params[2]);
	}
}

// Union operator
float or(float a, float b, unsigned int type) {
	if (type == 1) { // algebraic sum
		return a + b - a * b;
	} else if (type == 2) { // bounded sum
		return fminf(1, a + b);
	} else { // fuzzy union
		return fmaxf(a, b);
	}
}

// Intersection operator
float and(float a, float b, unsigned int type) {
	if (type == 1) { // algebraic product
		return a * b;
	} else if (type == 2) { // bounded product
		return fmaxf(0, a + b - 1);
	} else { // fuzzy intersection
		return fminf(a, b);
	}
}

// Equilibrium operator
float equilibrium(float a, float b, float params) {
	float r1, r2;
	if (params == 0.5f) {// fo() 仅以 params=0.5 调用: powf(x,0.5)≡sqrt(x)
		arm_sqrt_f32(a * b, &r1);// ARM DSP 快速开方（VSQRT 硬件指令）
		arm_sqrt_f32(1.0f - (1.0f - a) * (1.0f - b), &r2);
		return r1 * r2;
	}
	return powf(a * b, 1.0f - params) * powf(1.0f - (1.0f - a) * (1.0f - b), params);
}

// Fuzzy operator
float fo(float a, float b, unsigned int type) {
	if (type < 3) {
		return and(a, b, type);
	} else if (type < 6) {
		return or(a, b, type - 3);
	} else {
		return equilibrium(a, b, 0.5f);
	}
}

// Mean of centers defuzzifier, only for two input multiple index
void moc(const float *joint_membership, const unsigned int *index, const unsigned int *count, struct fuzzy *fuzzy_struct) {

	float denominator_count = 0;
	float numerator_count[fuzzy_struct->output_num];
	for (unsigned int l = 0; l < fuzzy_struct->output_num; ++l) {
		numerator_count[l] = 0;
	}

	for (int i = 0; i < count[0]; ++i) {
		for (int j = 0; j < count[1]; ++j) {
			denominator_count += joint_membership[i * count[1] + j];
		}
	}
	if (denominator_count < 1e-9F) {//去模糊分母为0保护, 避免除零产生NaN
		for (unsigned int l = 0; l < fuzzy_struct->output_num; ++l) {
			fuzzy_struct->output[l] = 0;
		}
		return;
	}
	for(unsigned int k = 0; k < fuzzy_struct->output_num; ++k) {
		for(unsigned int i = 0; i < count[0]; ++i) {
			for(unsigned int j = 0; j < count[1]; ++j) {
				numerator_count[k] += joint_membership[i * count[1] + j] * fuzzy_struct->rule_base[k * qf_default * qf_default + index[i] * qf_default + index[count[0] + j]];
			}
		}
	}

#ifdef fuzzy_pid_debug_print
    printf("output:\n");
#endif
    for (unsigned int l = 0; l < fuzzy_struct->output_num; ++l) {
        fuzzy_struct->output[l] = numerator_count[l] / denominator_count;
#ifdef fuzzy_pid_debug_print
        printf("%f,%f,%f\n", numerator_count[l], denominator_count, fuzzy_struct->index[l]);
#endif
    }
}

// Defuzzifier
void df(const float *joint_membership, const unsigned int *output, const unsigned int *count, struct fuzzy *fuzzy_struct,
        int df_type) {
    if(df_type == 0)
        moc(joint_membership, output, count, fuzzy_struct);
    else {
        printf("Waring: No such of defuzzifier!\n");
        moc(joint_membership, output, count, fuzzy_struct);
    }
}

void fuzzy_control(float e, float de, struct fuzzy *fuzzy_struct) {
    float membership[qf_default * 2]; // Store membership
    unsigned int index[qf_default * 2]; // Store the index of each membership
    unsigned int count[2] = {0, 0};

    {
        int j = 0;
        for (int i = 0; i < qf_default; ++i) {
            float temp = mf(e, fuzzy_struct->mf_type[0], fuzzy_struct->mf_params + 4 * i);
            if (temp > 1e-4F) {
                membership[j] = temp;
                index[j++] = i;
            }
        }

        count[0] = j;

        for (int i = 0; i < qf_default; ++i) {
            float temp = mf(de, fuzzy_struct->mf_type[1], fuzzy_struct->mf_params + 4 * i);
            if (temp > 1e-4F) {
                membership[j] = temp;
                index[j++] = i;
            }
        }

        count[1] = j - count[0];
    }

#ifdef fuzzy_pid_debug_print
    printf("membership:\n");
    for (unsigned int k = 0; k < j; ++k) {
        printf("%f\n", membership[k]);
    }

    printf("index:\n");
    for (unsigned int k = 0; k < j; ++k) {
        printf("%d\n", index[k]);
    }

    printf("count:\n");
    for (unsigned int k = 0; k < 2; ++k) {
        printf("%d\n", count[k]);
    }
#endif

    if (count[0] == 0 || count[1] == 0) {
        for (unsigned int l = 0; l < fuzzy_struct->output_num; ++l) {
            fuzzy_struct->output[l] = 0;
        }
        return;
    }

    // Joint membership
    float joint_membership[count[0] * count[1]];

    for (int i = 0; i < count[0]; ++i) {
        for (int j = 0; j < count[1]; ++j) {
            joint_membership[i * count[1] + j] = fo(membership[i], membership[count[0] + j], fuzzy_struct->fo_type);
        }
    }

    df(joint_membership, index, count, fuzzy_struct, 0);
}

struct PID *raw_fuzzy_pid_init(float kp, float ki, float kd, float integral_limit, float dead_zone,
                               float feed_forward, float error_max, float delta_error_max, float delta_kp_max,
                               float delta_ki_max, float delta_kd_max, unsigned int mf_type, unsigned int fo_type,
                               unsigned int df_type, int mf_params[], int rule_base[][qf_default],
                               int output_min_value, int output_middle_value, int output_max_value) {
    struct PID *pid = (struct PID *) malloc(sizeof(struct PID));
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->delta_kp_max = delta_kp_max;
    pid->delta_ki_max = delta_ki_max;
    pid->delta_kd_max = delta_kd_max;

    pid->delta_kp = 0;
    pid->delta_ki = 0;
    pid->delta_kd = 0;

    pid->error_max = error_max;
    pid->delta_error_max = delta_error_max;

    int output_count = 1;
    if (ki > 1e-4F) {
        output_count += 1;
        if (kd > 1e-4F)
            output_count += 1;
    }

    pid->fuzzy_struct = fuzzy_init(2, output_count);
    fuzzy_params_init(pid->fuzzy_struct, mf_type, fo_type, df_type, mf_params, rule_base);

    pid->last_error = 0;
    pid->current_error = 0;

    pid->intergral = 0;
    pid->intergral_limit = integral_limit;

    pid->dead_zone = dead_zone;
    pid->feed_forward = feed_forward;

    pid->output_max_value = output_max_value;
    pid->output_middle_value = output_middle_value;
    pid->output_min_value = output_min_value;

    return pid;
}

struct PID *fuzzy_pid_init(float *params, float delta_k, unsigned int mf_type, unsigned int fo_type,
                           unsigned int df_type, int mf_params[], int rule_base[][qf_default]) {
    return raw_fuzzy_pid_init(params[0], params[1], params[2], params[3], params[4], params[5], max_error,
                              max_delta_error, params[0] / delta_k, params[1] / delta_k, params[2] / delta_k, mf_type,
                              fo_type, df_type, mf_params,
                              rule_base, min_pwm_output, middle_pwm_output, max_pwm_output);
}

struct PID *raw_pid_init(float kp, float ki, float kd, float integral_limit, float dead_zone,
                         float feed_forward, float linear_adaptive_kp, float error_max, float delta_error_max,
                         int output_min_value, int output_middle_value, int output_max_value) {
    struct PID *pid = (struct PID *) malloc(sizeof(struct PID));
    pid->kp = kp;
    pid->ki = ki;
    pid->kd = kd;

    pid->delta_kp_max = 0;
    pid->delta_ki_max = 0;
    pid->delta_kd_max = 0;

    pid->delta_kp = 0;
    pid->delta_ki = 0;
    pid->delta_kd = 0;

    pid->error_max = error_max;
    pid->delta_error_max = delta_error_max;

    pid->fuzzy_struct = NULL;

    pid->last_error = 0;
    pid->current_error = 0;

    pid->intergral = 0;
    pid->intergral_limit = integral_limit;

    pid->dead_zone = dead_zone;
    pid->feed_forward = feed_forward;

    pid->output_max_value = output_max_value;
    pid->output_middle_value = output_middle_value;
    pid->output_min_value = output_min_value;

    pid->linear_adaptive_kp = linear_adaptive_kp;
    return pid;
}

struct PID *pid_init(float *params) {
    return raw_pid_init(params[0], params[1], params[2], params[3], params[4], params[5], params[6], max_error,
                        max_delta_error, min_pwm_output, middle_pwm_output, max_pwm_output);
}

int round_user(float parameter) {
    if ((int) (parameter * 10.0F) % 10 >= 5)
        return parameter + 1;
    else
        return parameter;
}

int limit(int value, int max_limit, int min_limit) {
    if (value > max_limit)
        return max_limit;
    if (value < min_limit)
        return min_limit;
    return value;
}

float fuzzy_pid_control(float real, float idea, struct PID *pid) {
    pid->last_error = pid->current_error;
    pid->current_error = idea - real;
    float delta_error = pid->current_error - pid->last_error;
#ifdef fuzzy_pid_dead_zone
    if (pid->current_error < pid->dead_zone && pid->current_error > -pid->dead_zone) {
        pid->current_error = 0;
    } else {
        if (pid->current_error > pid->dead_zone)
            pid->current_error = pid->current_error - pid->dead_zone;
        else {
            if (pid->current_error < -pid->dead_zone)
                pid->current_error = pid->current_error + pid->dead_zone;
        }
    }
#endif
    // 输入论域限幅: 误差/变化率超出 ±error_max 时钳位到边界,
    // 避免隶属度全零导致 count=0 而输出突变(原实现直接清零)
    float e_norm = pid->current_error / pid->error_max * 3.0f;
    if (e_norm > 3.0f) e_norm = 3.0f;
    else if (e_norm < -3.0f) e_norm = -3.0f;
    float de_norm = delta_error / pid->delta_error_max * 3.0f;
    if (de_norm > 3.0f) de_norm = 3.0f;
    else if (de_norm < -3.0f) de_norm = -3.0f;
    fuzzy_control(e_norm, de_norm, pid->fuzzy_struct);

    pid->delta_kp = pid->fuzzy_struct->output[0] / 3.0f * pid->delta_kp_max + pid->kp;

    if (pid->fuzzy_struct->output_num >= 2)
        pid->delta_ki = pid->fuzzy_struct->output[1] / 3.0f * pid->delta_ki_max;
    else pid->delta_ki = 0;

    if (pid->fuzzy_struct->output_num >= 3)
        pid->delta_kd = pid->fuzzy_struct->output[2] / 3.0f * pid->delta_kd_max;
    else pid->delta_kd = 0;

#ifdef fuzzy_pid_debug_print
    printf("kp : %f, ki : %f, kd : %f\n", kp, ki, kd);
#endif

    pid->intergral += (pid->ki + pid->delta_ki) * pid->current_error;
    // 积分限幅(抗积分饱和): 运行时始终钳位, 防止积分 windup 引起输出极限环振荡
    if (pid->intergral > pid->intergral_limit)
        pid->intergral = pid->intergral_limit;
    else {
        if (pid->intergral < -pid->intergral_limit)
            pid->intergral = -pid->intergral_limit;
    }
    pid->output = (pid->kp + pid->delta_kp) * pid->current_error + pid->intergral +
                  (pid->kd + pid->delta_kd) * (pid->current_error - pid->last_error);
    pid->output += pid->feed_forward * (float) idea;
    return pid->output;
}


float pid_control(float real, float idea, struct PID *pid) {
    pid->last_error = pid->current_error;
    pid->current_error = idea - real;

#ifdef pid_dead_zone
    if (pid->current_error < pid->dead_zone && pid->current_error > -pid->dead_zone) {
        pid->current_error = 0;
    } else {
        if (pid->current_error > pid->dead_zone)
            pid->current_error = pid->current_error - pid->dead_zone;
        else {
            if (pid->current_error < -pid->dead_zone)
                pid->current_error = pid->current_error + pid->dead_zone;
        }
    }
#endif

#ifdef pid_debug_print
    printf("kp : %f, ki : %f, kd : %f\n", kp, ki, kd);
#endif

    pid->intergral += (pid->ki) * pid->current_error;
#ifdef pid_integral_limit
    if (pid->intergral > pid->intergral_limit)
        pid->intergral = pid->intergral_limit;
    else {
        if (pid->intergral < -pid->intergral_limit)
            pid->intergral = -pid->intergral_limit;
    }
#endif

    float linear_adaptive_kp = 1;
    if (pid->linear_adaptive_kp > 1e-4F)
        linear_adaptive_kp =
                (1 - pid->linear_adaptive_kp) * pid->current_error / pid->error_max + pid->linear_adaptive_kp;

    pid->output = pid->kp * linear_adaptive_kp * pid->current_error + pid->intergral +
                  (pid->kd) * (pid->current_error - pid->last_error);
    pid->output += pid->feed_forward * (float) idea;
    return pid->output;
}


void delete_pid(struct PID *pid) {
    if (pid->fuzzy_struct != NULL) {
        delete_fuzzy(pid->fuzzy_struct);
    }
    free(pid);
}

void delete_pid_vector(struct PID **pid_vector, unsigned int count) {
    for (unsigned int i = 0; i < count; ++i) {
        delete_pid(pid_vector[i]);
    }
    free(pid_vector);
}

struct PID **pid_vector_init(float params[][pid_params_count], unsigned int count) {
    struct PID **pid = (struct PID **) malloc(sizeof(struct PID *) * count);
    for (unsigned int i = 0; i < count; ++i) {
        pid[i] = pid_init(params[i]);
    }
    return pid;
}

struct PID **
fuzzy_pid_vector_init(float params[][pid_params_count], float delta_k, unsigned int mf_type, unsigned int fo_type,
                      unsigned int df_type, int *mf_params, int rule_base[][qf_default],
                      unsigned int count) {
    struct PID **pid = (struct PID **) malloc(sizeof(struct PID *) * count);
    for (unsigned int i = 0; i < count; ++i) {
        pid[i] = fuzzy_pid_init(params[i], delta_k, mf_type, fo_type, df_type, mf_params, rule_base);
    }
    return pid;
}

int direct_control(int zero_value, int offset_value, bool direct) {
    if (direct == true) {
        return zero_value + offset_value;
    } else {
        return zero_value - offset_value;
    }
}

int fuzzy_pid_motor_pwd_output(float real, float idea, bool direct, struct PID *pid) {
    return limit(direct_control(pid->output_middle_value, fuzzy_pid_control(real, idea, pid), direct),
                 pid->output_max_value, pid->output_min_value);
}

int pid_motor_pwd_output(float real, float idea, bool direct, struct PID *pid) {
    return limit(direct_control(pid->output_middle_value, pid_control(real, idea, pid), direct), pid->output_max_value,
                 pid->output_min_value);
}

/*============================================================================*/
/* 模糊PID应用层封装实现 (FuzzyPID_HandleTypeDef)                              */
/* 默认隶属函数: 7 个三角隶属函数, 论域 ±3, 中心 -3..3 等距                    */
/* 默认规则表: 标准对称模糊PID规则表(ΔKp/ΔKi/ΔKd, 每表 7×7)                    */
/*============================================================================*/
static int fuzzy_default_mf_params[7 * 4] = {
    -4, -3, -2, 0,   // NB
    -3, -2, -1, 0,   // NM
    -2, -1,  0, 0,   // NS
    -1,  0,  1, 0,   // ZO
     0,  1,  2, 0,   // PS
     1,  2,  3, 0,   // PM
     2,  3,  4, 0    // PB
};

static int fuzzy_default_rule_base[3][7][7] = {
    { // ΔKp: 误差大时加大比例, 误差小且变化率大时减小比例
        { 3, 3, 2, 2, 1, 0, 0},
        { 3, 3, 2, 1, 1, 0,-1},
        { 2, 2, 2, 1, 0,-1,-1},
        { 2, 2, 1, 0,-1,-2,-2},
        { 1, 1, 0,-1,-1,-2,-2},
        { 1, 0,-1,-2,-2,-2,-3},
        { 0, 0,-2,-2,-2,-3,-3}
    },
    { // ΔKi: 误差小且同向时加强积分消除静差, 误差大时减弱防超调
        {-3,-3,-2,-2,-1, 0, 0},
        {-3,-3,-2,-1,-1, 0, 0},
        {-3,-2,-1,-1, 0, 1, 1},
        {-2,-2,-1, 0, 1, 2, 2},
        {-2,-1, 0, 1, 1, 2, 3},
        { 0, 0, 1, 1, 2, 3, 3},
        { 0, 0, 1, 2, 2, 3, 3}
    },
    { // ΔKd: 误差变化剧烈时加大微分阻尼, 误差大时适度减小防滞后
        { 1,-1,-3,-3,-3,-2, 1},
        { 1,-1,-3,-2,-2,-1, 0},
        { 0,-1,-2,-2,-1,-1, 0},
        { 0,-1,-1,-1,-1,-1, 0},
        { 0, 0, 0, 0, 0, 0, 0},
        { 3,-1, 1, 1, 1, 1, 3},
        { 3, 2, 2, 2, 1, 1, 3}
    }
};

void FuzzyPID_Init(FuzzyPID_HandleTypeDef *handle, float kp, float ki, float kd,
                   int output_min, int output_max, float integral_limit,
                   uint32_t control_period, float error_max_c, float delta_error_max_c) {
    if (handle == NULL) return;
    handle->setpoint_x10 = 0.0f;
    handle->error_max_c = error_max_c;
    handle->delta_error_max_c = delta_error_max_c;
    handle->output_min = output_min;
    handle->output_max = output_max;
    handle->integral_limit = integral_limit;
    // 底层量纲统一为 ×10: 误差论域/变化率论域 ×10 与反馈一致;
    // 模糊增益调节幅度取基础增益的 50%; 死区 1(×10)=0.1℃ 防温控抖振
    handle->pid = raw_fuzzy_pid_init(kp, ki, kd, integral_limit, 1.0f, 0.0f,
                                     error_max_c * 10.0f, delta_error_max_c * 10.0f,
                                     kp * 0.5f, ki * 0.5f, kd * 0.5f,
                                     4, 0, 0,
                                     fuzzy_default_mf_params,
                                     (int (*)[qf_default])fuzzy_default_rule_base,//3张7×7表连续内存, 按线性布局访问
                                     output_min, 0, output_max);
    (void)control_period; // 控制周期由外部调用周期决定, 此处仅接口占位
}

void FuzzyPID_SetSetpoint(FuzzyPID_HandleTypeDef *handle, int16_t setpoint_x10) {
    if (handle == NULL) return;
    handle->setpoint_x10 = (float)setpoint_x10;
}

int16_t FuzzyPID_Compute(FuzzyPID_HandleTypeDef *handle, int16_t real_x10) {
    if (handle == NULL || handle->pid == NULL) return 0;
    float out = fuzzy_pid_control((float)real_x10, handle->setpoint_x10, handle->pid);
    if (out > (float)handle->output_max) out = (float)handle->output_max;
    else if (out < (float)handle->output_min) out = (float)handle->output_min;
    return (int16_t)out;
}

