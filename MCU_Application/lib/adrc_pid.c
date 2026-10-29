/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "adrc_pid.h"
#include <string.h>
/*****************************************************************************/
void ADRCPid_Init(ADRCPid_t *pid, float target_temp){
	memset(pid, 0, sizeof(ADRCPid_t));
	pid->target = target_temp;
	pid->b = -0.2f;         // 控制增益估计：u=1(满制冷)约0.2℃/s降温，现场按实测微调
	pid->wc = 0.15f;        // 控制器带宽：闭环时间常数约 1/0.15≈6.7s
	pid->wo = 0.6f;         // 观测器带宽：4×wc，ESO 收敛快于控制环
	pid->ts = 0.5f;         // 采样周期 500ms（与 tempCtrLoop 周期一致）
	pid->out_min = 0.0f;
	pid->out_max = 1.0f;
}
/*****************************************************************************/
void ADRCPid_SetTarget(ADRCPid_t *pid, float target_temp){
	pid->target = target_temp;
}
/*****************************************************************************/
float ADRCPid_Compute(ADRCPid_t *pid, float current_temp){
	float e_obs, u0, u;
	/* ---- LESO 一步（欧拉离散） ----
	   z1' = z2 + β1·(y-z1) + b·u,  β1 = 2·ωo
	   z2' = β2·(y-z1),             β2 = ωo²   */
	e_obs = current_temp - pid->z1;
	pid->z1 += pid->ts * (pid->z2 + pid->b * pid->u_prev + 2.0f * pid->wo * e_obs);
	pid->z2 += pid->ts * (pid->wo * pid->wo * e_obs);
	/* ---- 控制律：扰动补偿 + 比例 ---- */
	u0 = pid->wc * (pid->target - pid->z1);
	u = (u0 - pid->z2) / pid->b;
	if(u < pid->out_min){
		u = pid->out_min;
	}
	else if(u > pid->out_max){
		u = pid->out_max;
	}
	/* 抗饱和：ESO 下一拍使用限幅后的实际执行值 */
	pid->u_prev = u;
	pid->u_out = u;
	return u;
}
/*****************************************************************************/
