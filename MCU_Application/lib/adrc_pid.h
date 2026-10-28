#ifndef __ADRC_PID_H__
#define __ADRC_PID_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include <stdint.h>
#include <math.h>
/*****************************************************************************/
// ADRC 自抗扰控制（一阶对象 + 一阶扩张状态观测器 LESO）
// 原理：
//   对象 ẏ = f(t) + b·u，f(t) 为总扰动（未建模动态 + 环境/散热器变化）。
//   一阶 LESO 在线估计 z1≈y、z2≈f(t)，控制律 u = (u0 - z2)/b 直接补偿扰动，
//   剩余部分退化为纯比例 u0 = ωc·(target - z1)，无需积分（扰动已补偿，无静差）。
//   采样周期固定 500ms（与 tempCtrLoop 一致），欧拉法离散，ωo·T<<1 稳定。
//   抗饱和：ESO 输入用限幅后的实际执行值 u，饱和时观测器自然停止积分。
// 输入温度单位：℃；输出：制冷比例 0.0 ~ 1.0（单冷 TEC，b 取负值即制冷增益）。
typedef struct {
	// --- 目标与增益 ---
	float target;           // 目标温度 (℃)
	float b;                // 控制增益估计（℃/s 每单位 u，单冷取负值，如 -0.2）
	float wc;               // 控制器带宽 ωc (rad/s)，决定跟踪速度
	float wo;               // 观测器带宽 ωo (rad/s)，取 ωo ≈ (3~10)·ωc
	// --- ESO 状态 ---
	float z1, z2;           // z1 跟踪温度，z2 估计总扰动
	float u_prev;           // 上一拍实际输出（限幅后，供 ESO 与抗饱和）
	float ts;               // 采样周期 (s)，固定 0.5
	// --- 输出 ---
	float u_out;            // 当前输出（制冷比例）
	float out_min, out_max; // 输出限幅
} ADRCPid_t;
/*****************************************************************************/
// 对外接口函数声明

/**
 * @brief 初始化 ADRC 控制器
 * @param pid 控制器结构体指针
 * @param target_temp 目标温度 (℃)
 * @note 无需辨识、无需训练；b 为控制增益估算（单冷 TEC 取负），现场可按
 *       实际制冷速率微调；wc/wo 为带宽参数，默认值已适配 500ms 采样
 */
void ADRCPid_Init(ADRCPid_t *pid, float target_temp);

/**
 * @brief 在线修改目标温度
 * @param pid 控制器结构体指针
 * @param target_temp 新目标温度 (℃)
 */
void ADRCPid_SetTarget(ADRCPid_t *pid, float target_temp);

/**
 * @brief ADRC 计算制冷输出比例
 * @param pid 控制器结构体指针
 * @param current_temp 当前实测温度 (℃)
 * @return 制冷比例 0.0f(关闭) ~ 1.0f(最大制冷)
 * @note 必须在固定周期(500ms)内周期性调用
 */
float ADRCPid_Compute(ADRCPid_t *pid, float current_temp);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
