#include "rls_pid.h"
#include <string.h>
/*****************************************************************************/
#define RLS_EPS           1e-6f
#define RLS_P_INIT        100.0f     // 协方差初值（无先验，给大初值加速收敛）
#define RLS_P_MAX         1000.0f    // 协方差对角上限（防吹涨）
#define RLS_MIN_IDENT     60         // 最小辨识拍数（500ms×60=30s）后允许切极点配置
#define RLS_DEADBAND      0.05f      // 辨识更新死区（℃），预测误差小于此值不更新
#define RLS_B_MIN         1e-3f      // 模型增益有效下限
#define RLS_A1_MAX        1.98f      // a1 稳定域近似限幅
#define RLS_A2_MAX        0.99f      // a2 稳定域近似限幅
#define RLS_B_MAX         0.5f       // b0/b1 物理量级限幅（℃/控制比例）
#define RLS_P_TARGET_MIN  0.5f       // 目标主导极点下限（不过度激进）
#define RLS_P_TARGET_MAX  0.99f      // 目标主导极点上限（保证闭环稳定裕度）
#define RLS_K_DEFAULT     0.05f      // 模型未就绪期间默认比例增量增益
/*****************************************************************************/
static float rlsClampf(float v, float lo, float hi){
	if(v < lo){
		return lo;
	}
	if(v > hi){
		return hi;
	}
	return v;
}
/*****************************************************************************/
void RLSPid_Init(RLSPid_t *pid, float target_temp){
	uint8_t i;
	memset(pid, 0, sizeof(RLSPid_t));
	pid->target = target_temp;
	pid->lambda = 0.99f;              // 遗忘因子：慢时变热系统，记忆长、噪声免疫好
	pid->k_default = RLS_K_DEFAULT;   // 辨识期默认比例增量
	pid->p_target = 0.97f;            // 初始目标主导极点（约16s时间常数）
	pid->learn_deadband = RLS_DEADBAND;
	pid->b_min = RLS_B_MIN;
	pid->out_min = 0.0f;
	pid->out_max = 1.0f;
	pid->model_ready = 0;
	pid->ident_count = 0;
	for(i = 0; i < 4; i++){
		pid->P[i][i] = RLS_P_INIT;
	}
}
/*****************************************************************************/
void RLSPid_SetTarget(RLSPid_t *pid, float target_temp){
	pid->target = target_temp;
}
/*****************************************************************************/
/* 极点配置控制器系数重算（模型就绪后每拍调用）
 * A=1+a1q^-1+a2q^-2, B=b0q^-1+b1q^-2, R=1-q^-1
 * 期望闭环 A·R+B·S = 1+ac1q^-1+ac2q^-2 (+ac3q^-3 自由)
 * s0=(ac1-a1+1)/b0, s1=(ac2-a2+a1-b1·s0)/b0
 * ac3_actual = a2 - b1·s1（第三极点由方程自然决定，须 |ac3_actual|<1）
 * t0 = Ac(1)/B(1) 直流增益归一化
 * 返回 0 成功 / 1 失败（保持旧参数） */
static uint8_t rlsPolePlace(RLSPid_t *pid){
	float p1, ac1, ac2, s0, s1, ac3, t0, b0b1;
	float po_abs;
	/* 由开环极点半径收缩得目标主导极点（保证闭环略快于开环） */
	po_abs = 0.0f;
	/* ARM DSP 快速开方（内联 __sqrtf → VSQRT 硬件指令），入参经 fabsf 保证非负 */
	(void)arm_sqrt_f32(fabsf(pid->a2), &po_abs);
	p1 = po_abs * 0.8f;
	p1 = rlsClampf(p1, RLS_P_TARGET_MIN, RLS_P_TARGET_MAX);
	pid->p_target = p1;
	/* 期望闭环：双实主导极点 p1（临界阻尼无振荡） */
	ac1 = -(p1 + p1);
	ac2 = p1 * p1;
	/* 求解控制器系数（r1=-1 已代入） */
	s0 = (ac1 - pid->a1 + 1.0f) / pid->b0;
	s1 = (ac2 - pid->a2 + pid->a1 - pid->b1 * s0) / pid->b0;
	/* 第三极点：ac3_actual = a2 - b1·s1，必须稳定 |ac3|<1 */
	ac3 = pid->a2 - pid->b1 * s1;
	if((fabsf(ac3) >= 1.0f) || (!isfinite(s0)) || (!isfinite(s1))){
		return 1;
	}
	/* 直流增益归一化前馈：t0 = Ac(1)/B(1) */
	b0b1 = pid->b0 + pid->b1;
	if(fabsf(b0b1) < RLS_EPS){
		return 1;
	}
	t0 = (1.0f + ac1 + ac2 + ac3) / b0b1;
	if(!isfinite(t0)){
		return 1;
	}
	pid->s0 = s0;
	pid->s1 = s1;
	pid->t0 = t0;
	return 0;
}
/*****************************************************************************/
float RLSPid_Compute(RLSPid_t *pid, float current_temp){
	float y, e_ctrl, u, delta_u;
	float phi[4], Pphi[4], K[4], denom, yhat, epred;
	uint8_t i, j;
	y = current_temp;
	/* ---------- 1. RLS 一步辨识 ---------- */
	phi[0] = -pid->y_prev;         /* 对应 a1 */
	phi[1] = -pid->y_prev2;        /* 对应 a2 */
	phi[2] = pid->u_prev;          /* 对应 b0 */
	phi[3] = pid->u_prev2;         /* 对应 b1 */
	yhat = phi[0] * pid->a1 + phi[1] * pid->a2 + phi[2] * pid->b0 + phi[3] * pid->b1;
	epred = y - yhat;
	/* 预测误差超过死区才更新（持续激励保护：无激励/噪声区不学习） */
	if(fabsf(epred) > pid->learn_deadband){
		/* P·φ */
		for(i = 0; i < 4; i++){
			Pphi[i] = pid->P[i][0] * phi[0] + pid->P[i][1] * phi[1]
			        + pid->P[i][2] * phi[2] + pid->P[i][3] * phi[3];
		}
		denom = pid->lambda + (phi[0] * Pphi[0] + phi[1] * Pphi[1]
		                     + phi[2] * Pphi[2] + phi[3] * Pphi[3]);
		if(denom > RLS_EPS){
			for(i = 0; i < 4; i++){
				K[i] = Pphi[i] / denom;
			}
			/* θ += K·epred */
			pid->a1 += K[0] * epred;
			pid->a2 += K[1] * epred;
			pid->b0 += K[2] * epred;
			pid->b1 += K[3] * epred;
			/* 参数物理限幅（防发散） */
			pid->a1 = rlsClampf(pid->a1, -RLS_A1_MAX, RLS_A1_MAX);
			pid->a2 = rlsClampf(pid->a2, -RLS_A2_MAX, RLS_A2_MAX);
			pid->b0 = rlsClampf(pid->b0, -RLS_B_MAX, RLS_B_MAX);
			pid->b1 = rlsClampf(pid->b1, -RLS_B_MAX, RLS_B_MAX);
			/* P = (P - K·φ'·P)/λ，对称化 + 对角下限 */
			for(i = 0; i < 4; i++){
				for(j = 0; j < 4; j++){
					float pij = (pid->P[i][j] - K[i] * Pphi[j]) / pid->lambda;
					pid->P[i][j] = (pij + pid->P[j][i]) * 0.5f;/* 对称化 */
				}
			}
			for(i = 0; i < 4; i++){
				if(pid->P[i][i] < 1e-4f){
					pid->P[i][i] = 1e-4f;
				}
				if(pid->P[i][i] > RLS_P_MAX){
					pid->P[i][i] = RLS_P_MAX;
				}
			}
		}
	}
	/* ---------- 2. 模型就绪判定与控制器选择 ---------- */
	pid->ident_count++;
	if(pid->ident_count < RLS_MIN_IDENT){
		pid->model_ready = 0;
	}
	else{
		if((fabsf(pid->b0) > pid->b_min) && (fabsf(pid->b1) <= RLS_B_MAX)){
			if(pid->model_ready == 0){
				/* 首次就绪：初始化控制器参数 */
				if(rlsPolePlace(pid) == 0){
					pid->model_ready = 1;
				}
			}
			else{
				/* 已就绪：每拍跟随最新模型重算（在线自校正），失败保持旧参数 */
				rlsPolePlace(pid);
			}
		}
		else{
			pid->model_ready = 0;
		}
	}
	/* ---------- 3. 控制律 ---------- */
	e_ctrl = pid->target - y;
	if(pid->model_ready){
		/* 极点配置增量式：Δu = t0·w - s0·y - s1·y_prev */
		delta_u = pid->t0 * pid->target - pid->s0 * y - pid->s1 * pid->y_prev;
	}
	else{
		/* 模型未就绪：默认比例增量过渡（等价于简易P） */
		delta_u = pid->k_default * e_ctrl;
	}
	u = pid->u_prev + delta_u;
	u = rlsClampf(u, pid->out_min, pid->out_max);
	/* ---------- 4. 更新历史 ---------- */
	pid->y_prev2 = pid->y_prev;
	pid->y_prev = y;
	pid->u_prev2 = pid->u_prev;
	pid->u_prev = u;
	pid->u_out = u;
	return u;
}
/*****************************************************************************/
