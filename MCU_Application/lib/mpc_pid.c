/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "mpc_pid.h"
#include <string.h>
/*****************************************************************************/
#define MPC_EPS 1e-6f
#define MPC_P_INIT 100.0f
#define MPC_P_MAX 1000.0f
/*****************************************************************************/
static float mpcClampf(float v, float lo, float hi){
	if(v < lo){
		return lo;
	}
	if(v > hi){
		return hi;
	}
	return v;
}
/*****************************************************************************/
void MPCPid_Init(MPCPid_t *pid, float target_temp){
	uint8_t i;
	memset(pid, 0, sizeof(MPCPid_t));
	pid->target = target_temp;
	pid->lambda = 0.99f;
	pid->q = 1.0f;
	pid->rho = 0.1f;                 // 增量惩罚：接近稳态时输出平滑，防 MPC 抖动
	pid->k_default = 0.05f;
	pid->learn_deadband = MPC_DEADBAND;
	pid->b_min = MPC_B_MIN;
	pid->out_min = 0.0f;
	pid->out_max = 1.0f;
	pid->model_ready = 0;
	for(i = 0; i < 4; i++){
		pid->P[i][i] = MPC_P_INIT;
	}
}
/*****************************************************************************/
void MPCPid_SetTarget(MPCPid_t *pid, float target_temp){
	pid->target = target_temp;
}
/*****************************************************************************/
float MPCPid_Compute(MPCPid_t *pid, float current_temp){
	float y, u, delta_u, denom, yhat, epred, num = 0.0f, den = 0.0f;
	float phi[4], Pphi[4], K[4];
	float S[MPC_HORIZON + 1], yf[MPC_HORIZON + 1];
	uint8_t i;
	y = current_temp;
	/* ---------- 1. RLS 一步辨识（同 RLS-PID 的 ARX 辨识核心） ---------- */
	phi[0] = -pid->y_prev;
	phi[1] = -pid->y_prev2;
	phi[2] = pid->u_prev;
	phi[3] = pid->u_prev2;
	yhat = phi[0] * pid->a1 + phi[1] * pid->a2 + phi[2] * pid->b0 + phi[3] * pid->b1;
	epred = y - yhat;
	if(fabsf(epred) > pid->learn_deadband){
		for(i = 0; i < 4; i++){
			Pphi[i] = pid->P[i][0] * phi[0] + pid->P[i][1] * phi[1]
			        + pid->P[i][2] * phi[2] + pid->P[i][3] * phi[3];
		}
		denom = pid->lambda + (phi[0] * Pphi[0] + phi[1] * Pphi[1]
		                     + phi[2] * Pphi[2] + phi[3] * Pphi[3]);
		if(denom > MPC_EPS){
			uint8_t j;
			for(i = 0; i < 4; i++){
				K[i] = Pphi[i] / denom;
			}
			pid->a1 += K[0] * epred;
			pid->a2 += K[1] * epred;
			pid->b0 += K[2] * epred;
			pid->b1 += K[3] * epred;
			pid->a1 = mpcClampf(pid->a1, -MPC_A1_MAX, MPC_A1_MAX);
			pid->a2 = mpcClampf(pid->a2, -MPC_A2_MAX, MPC_A2_MAX);
			pid->b0 = mpcClampf(pid->b0, -MPC_B_MAX, MPC_B_MAX);
			pid->b1 = mpcClampf(pid->b1, -MPC_B_MAX, MPC_B_MAX);
			for(i = 0; i < 4; i++){
				for(j = 0; j < 4; j++){
					float pij = (pid->P[i][j] - K[i] * Pphi[j]) / pid->lambda;
					pid->P[i][j] = (pij + pid->P[j][i]) * 0.5f;
				}
			}
			for(i = 0; i < 4; i++){
				if(pid->P[i][i] < 1e-4f){ pid->P[i][i] = 1e-4f; }
				if(pid->P[i][i] > MPC_P_MAX){ pid->P[i][i] = MPC_P_MAX; }
			}
		}
	}
	/* ---------- 2. 模型就绪判定 ---------- */
	pid->ident_count++;
	if(pid->ident_count < MPC_IDENT_MIN){
		pid->model_ready = 0;
	}
	else{
		pid->model_ready = (fabsf(pid->b0) > pid->b_min) ? 1 : 0;
	}
	/* ---------- 3. MPC 预测与单步优化 ---------- */
	if(pid->model_ready){
		/* 单位阶跃响应系数 S_i（Δu 阶跃并保持的响应） */
		S[1] = pid->b0;
		S[2] = -pid->a1 * S[1] + pid->b0 + pid->b1;
		for(i = 3; i <= MPC_HORIZON; i++){
			S[i] = -pid->a1 * S[i - 1] - pid->a2 * S[i - 2] + pid->b0 + pid->b1;
		}
		/* 自由响应 yf_i（未来控制保持 u_prev） */
		yf[1] = -pid->a1 * y - pid->a2 * pid->y_prev + pid->b0 * pid->u_prev + pid->b1 * pid->u_prev2;
		yf[2] = -pid->a1 * yf[1] - pid->a2 * y + pid->b0 * pid->u_prev + pid->b1 * pid->u_prev;
		for(i = 3; i <= MPC_HORIZON; i++){
			yf[i] = -pid->a1 * yf[i - 1] - pid->a2 * yf[i - 2] + pid->b0 * pid->u_prev + pid->b1 * pid->u_prev;
		}
		/* J = q·Σ(yf_i + S_i·Δu - r)² + ρ·Δu² → 解析解 Δu* */
		num = 0.0f;
		den = 0.0f;
		for(i = 1; i <= MPC_HORIZON; i++){
			num += pid->q * S[i] * (pid->target - yf[i]);
			den += pid->q * S[i] * S[i];
		}
		den += pid->rho;
		if(den > MPC_EPS){
			delta_u = num / den;
		}
		else{
			delta_u = 0.0f;
		}
	}
	else{
		/* 模型未就绪：默认比例增量过渡 */
		delta_u = pid->k_default * (pid->target - y);
	}
	u = pid->u_prev + delta_u;
	u = mpcClampf(u, pid->out_min, pid->out_max);
	/* ---------- 4. 更新历史 ---------- */
	pid->y_prev2 = pid->y_prev;
	pid->y_prev = y;
	pid->u_prev2 = pid->u_prev;
	pid->u_prev = u;
	pid->u_out = u;
	return u;
}
/*****************************************************************************/
