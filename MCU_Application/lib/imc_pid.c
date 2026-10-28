#include "imc_pid.h"
#include <string.h>
/*****************************************************************************/
#define IMC_EPS 1e-6f
#define IMC_P_INIT 100.0f
#define IMC_P_MAX 1000.0f
/*****************************************************************************/
static float imcClampf(float v, float lo, float hi){
	if(v < lo){
		return lo;
	}
	if(v > hi){
		return hi;
	}
	return v;
}
/*****************************************************************************/
void IMCPid_Init(IMCPid_t *pid, float target_temp){
	memset(pid, 0, sizeof(IMCPid_t));
	pid->target = target_temp;
	pid->lambda = 0.99f;
	pid->alpha = 0.8f;              // 滤波器：鲁棒性/平滑度直接可调
	pid->k_default = 0.05f;
	pid->learn_deadband = IMC_DEADBAND;
	pid->b_min = IMC_B_MIN;
	pid->out_min = 0.0f;
	pid->out_max = 1.0f;
	pid->model_ready = 0;
	pid->init_flag = 0;
	pid->P[0][0] = IMC_P_INIT;
	pid->P[1][1] = IMC_P_INIT;
}
/*****************************************************************************/
void IMCPid_SetTarget(IMCPid_t *pid, float target_temp){
	pid->target = target_temp;
}
/*****************************************************************************/
float IMCPid_Compute(IMCPid_t *pid, float current_temp){
	float y, u, delta_u, denom, yhat_pred, epred, d, e_imc;
	float phi[2], Pphi[2], K[2];
	y = current_temp;
	/* 首拍：模型输出与测量对齐，避免初始瞬态 */
	if(pid->init_flag == 0){
		pid->yhat = y;
		pid->init_flag = 1;
	}
	/* ---------- 1. RLS 一步辨识（一阶 ARX） ---------- */
	phi[0] = -pid->y_prev;
	phi[1] = pid->u_prev;
	yhat_pred = phi[0] * pid->a1 + phi[1] * pid->b0;
	epred = y - yhat_pred;
	if(fabsf(epred) > pid->learn_deadband){
		Pphi[0] = pid->P[0][0] * phi[0] + pid->P[0][1] * phi[1];
		Pphi[1] = pid->P[1][0] * phi[0] + pid->P[1][1] * phi[1];
		denom = pid->lambda + phi[0] * Pphi[0] + phi[1] * Pphi[1];
		if(denom > IMC_EPS){
			K[0] = Pphi[0] / denom;
			K[1] = Pphi[1] / denom;
			pid->a1 += K[0] * epred;
			pid->b0 += K[1] * epred;
			pid->a1 = imcClampf(pid->a1, -IMC_A1_MAX, IMC_A1_MAX);
			pid->b0 = imcClampf(pid->b0, -IMC_B_MAX, IMC_B_MAX);
			/* P = (P - K·φ'·P)/λ，对称化 */
			{
				float p00, p01, p11;
				p00 = (pid->P[0][0] - K[0] * Pphi[0]) / pid->lambda;
				p01 = (pid->P[0][1] - K[0] * Pphi[1]) / pid->lambda;
				p11 = (pid->P[1][1] - K[1] * Pphi[1]) / pid->lambda;
				pid->P[0][0] = p00;
				pid->P[0][1] = (p01 + (pid->P[1][0] - K[1] * Pphi[0]) / pid->lambda) * 0.5f;
				pid->P[1][0] = pid->P[0][1];
				pid->P[1][1] = p11;
			}
			if(pid->P[0][0] < 1e-4f){ pid->P[0][0] = 1e-4f; }
			if(pid->P[1][1] < 1e-4f){ pid->P[1][1] = 1e-4f; }
			if(pid->P[0][0] > IMC_P_MAX){ pid->P[0][0] = IMC_P_MAX; }
			if(pid->P[1][1] > IMC_P_MAX){ pid->P[1][1] = IMC_P_MAX; }
		}
	}
	/* ---------- 2. 模型就绪判定 ---------- */
	pid->ident_count++;
	if(pid->ident_count < IMC_IDENT_MIN){
		pid->model_ready = 0;
	}
	else{
		pid->model_ready = (fabsf(pid->b0) > pid->b_min) ? 1 : 0;
	}
	/* ---------- 3. IMC 控制律 ---------- */
	if(pid->model_ready){
		/* 内模扰动估计：d = y - yhat（模型输出按模型方程演化） */
		d = y - pid->yhat;
		e_imc = pid->target - d;
		/* Q = Ĝ⁻¹·F 差分方程：u(k) = α·u(k-1) + (1-α)(e_imc(k) + a1·e_imc(k-1))/b0 */
		delta_u = (1.0f - pid->alpha) * (e_imc + pid->a1 * pid->e_prev) / pid->b0;
		u = pid->alpha * pid->u_prev + delta_u;
		/* 模型输出演化（供下一拍扰动估计） */
		pid->yhat = -pid->a1 * pid->yhat + pid->b0 * pid->u_prev;
		pid->e_prev = e_imc;
	}
	else{
		/* 模型未就绪：默认比例增量过渡，模型输出跟随测量（扰动=0） */
		delta_u = pid->k_default * (pid->target - y);
		u = pid->u_prev + delta_u;
		pid->yhat = y;
		pid->e_prev = pid->target;
	}
	u = imcClampf(u, pid->out_min, pid->out_max);
	/* ---------- 4. 更新历史 ---------- */
	pid->y_prev = y;
	pid->u_prev = u;
	pid->u_out = u;
	return u;
}
/*****************************************************************************/
