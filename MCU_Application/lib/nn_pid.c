#include "nn_pid.h"
#include <string.h>
/*****************************************************************************/
#define NN_EPS 1e-6f
/*****************************************************************************/
static float nnClampf(float v, float lo, float hi){
	if(v < lo){
		return lo;
	}
	if(v > hi){
		return hi;
	}
	return v;
}
/*****************************************************************************/
void NNPid_Init(NNPid_t *pid, float target_temp){
	memset(pid, 0, sizeof(NNPid_t));
	pid->target = target_temp;
	pid->k_neuron = 0.05f;      // 增量增益：误差5℃时约25%输出/拍，误差收敛后自衰减
	pid->w1 = 0.5f;             // 初始比例主导（预留双向调节余量，避免单调饱和）
	pid->w2 = 0.0f;
	pid->w3 = 0.0f;
	pid->eta1 = 0.01f;          // P 通道学习率（e 量级 ℃）
	pid->eta2 = 0.001f;         // I 通道学习率（Δe 量级小）
	pid->eta3 = 0.001f;         // D 通道学习率（Δ²e 量级更小）
	pid->w_max = 1.0f;          // 权值限幅，防发散
	pid->learn_deadband = 0.1f; // 0.1℃ 学习死区，抑制 NTC 噪声引起的权值漂移
	pid->out_min = 0.0f;
	pid->out_max = 1.0f;
}
/*****************************************************************************/
void NNPid_SetTarget(NNPid_t *pid, float target_temp){
	pid->target = target_temp;
}
/*****************************************************************************/
float NNPid_Compute(NNPid_t *pid, float current_temp){
	float e, x1, x2, x3, z, denom, delta_u, u;
	e = current_temp - pid->target;    // 误差：温度高于目标为正（单冷需制冷）
	x1 = e;                            // 比例通道输入
	x2 = e - pid->e1;                  // 误差变化率（增量式中的稳态修正通道）
	x3 = e - 2.0f * pid->e1 + pid->e2; // 误差加速度（阻尼通道）
	denom = fabsf(pid->w1) + fabsf(pid->w2) + fabsf(pid->w3) + NN_EPS;
	delta_u = pid->k_neuron * (pid->w1 * x1 + pid->w2 * x2 + pid->w3 * x3) / denom;
	u = pid->u_prev + delta_u;
	u = nnClampf(u, pid->out_min, pid->out_max);
	/* 改进有监督 Hebb 学习：z = e + Δe（性能指标），Δwi = ηi * z * xi。
	   误差恒正时 z 随 Δe 变号（趋稳/超调回落时 Δe<0），权值双向调节；
	   误差小于死区或输出饱和时冻结学习，防止权值漂移与积分饱和。 */
	z = e + x2;
	if((fabsf(e) > pid->learn_deadband) && (u > pid->out_min) && (u < pid->out_max)){
		pid->w1 = nnClampf(pid->w1 + pid->eta1 * z * x1, -pid->w_max, pid->w_max);
		pid->w2 = nnClampf(pid->w2 + pid->eta2 * z * x2, -pid->w_max, pid->w_max);
		pid->w3 = nnClampf(pid->w3 + pid->eta3 * z * x3, -pid->w_max, pid->w_max);
	}
	/* 更新历史 */
	pid->e2 = pid->e1;
	pid->e1 = e;
	pid->u_prev = u;
	return u;
}
/*****************************************************************************/
