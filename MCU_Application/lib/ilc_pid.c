/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "ilc_pid.h"
#include <string.h>
/*****************************************************************************/
void ILCPid_Init(ILCPid_t *pid, float target_temp){
	memset(pid, 0, sizeof(ILCPid_t));
	pid->target = target_temp;
	pid->kp = 0.05f;        // 基础反馈增益：误差1℃ → 5%输出（每轮保底）
	pid->gamma = 0.3f;      // 学习增益：上一轮同相位误差的30%修正入前馈
	pid->traj_len = ILC_TRAJ_LEN;
	pid->phase = 0;
	pid->out_min = 0.0f;
	pid->out_max = 1.0f;
	/* u_ff / e_prev 由 memset 清零（第一轮纯反馈） */
}
/*****************************************************************************/
void ILCPid_SetTarget(ILCPid_t *pid, float target_temp){
	pid->target = target_temp;
}
/*****************************************************************************/
float ILCPid_Compute(ILCPid_t *pid, float current_temp){
	float e, u_fb, u;
	uint16_t ph;
	/* 误差：温度高于目标为正 → 增加制冷 */
	e = current_temp - pid->target;
	ph = pid->phase;
	/* P 型学习：上一轮同相位误差修正本轮前馈（限幅防积累发散） */
	pid->u_ff[ph] += pid->gamma * pid->e_prev[ph];
	if(pid->u_ff[ph] > 1.0f){
		pid->u_ff[ph] = 1.0f;
	}
	else if(pid->u_ff[ph] < -1.0f){
		pid->u_ff[ph] = -1.0f;
	}
	/* 基础反馈 + 学习前馈 */
	u_fb = pid->kp * e;
	u = u_fb + pid->u_ff[ph];
	if(u < pid->out_min){
		u = pid->out_min;
	}
	else if(u > pid->out_max){
		u = pid->out_max;
	}
	/* 记录本轮误差（供下一轮学习） */
	pid->e_prev[ph] = e;
	/* 相位推进（循环） */
	pid->phase++;
	if(pid->phase >= pid->traj_len){
		pid->phase = 0;
	}
	pid->u_out = u;
	return u;
}
/*****************************************************************************/
