#ifndef __ILC_PID_H__
#define __ILC_PID_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include <stdint.h>
#include <math.h>
/*****************************************************************************/
// ILC 迭代学习控制（P 型，面向重复工艺轨迹）
// 原理：
//   1) 将控制任务视为重复过程（如每次出光/打标前的升温段），轨迹按相位对齐
//      （相位循环 0..traj_len-1，一拍一拍推进）。
//   2) 基础反馈 u_fb = kp·(y - target) 保证每一轮自身稳定（保底）；
//      学习前馈 u_ff[phase] 用上一轮同相位误差修正：
//        u_ff[phase] += γ·e_prev[phase]
//      本轮输出 u = clamp(u_fb + u_ff[phase])。
//   3) 本轮误差记录到 e_prev[phase]，供下一轮学习。多轮迭代后前馈项
//      逐步逼近理想控制轨迹，稳态误差随轮次递减。
//   4) 误差方向：e = y - target（温度高于目标为正 → 增加制冷）。
// 输入温度单位：℃；输出：制冷比例 0.0 ~ 1.0（单冷 TEC）。
#define ILC_TRAJ_LEN 128      // 轨迹长度（拍）：500ms×128 = 64s
typedef struct {
	// --- 目标与增益 ---
	float target;           // 目标温度 (℃)
	float kp;               // 基础反馈增益（每轮保底稳定）
	float gamma;            // ILC 学习增益（0.1~0.5，过大振荡）
	// --- 轨迹状态 ---
	uint16_t traj_len;      // 轨迹长度（拍），固定 ILC_TRAJ_LEN
	uint16_t phase;         // 当前相位 0..traj_len-1
	float u_ff[ILC_TRAJ_LEN];   // 学习前馈表（逐相位）
	float e_prev[ILC_TRAJ_LEN]; // 上一轮误差表（逐相位）
	// --- 输出 ---
	float u_out;            // 当前输出
	float out_min, out_max; // 输出限幅
} ILCPid_t;
/*****************************************************************************/
// 对外接口函数声明

/**
 * @brief 初始化 ILC 控制器
 * @param pid 控制器结构体指针
 * @param target_temp 目标温度 (℃)
 * @note 前馈表清零，第一轮表现为纯反馈控制；适用于重复升温工艺
 */
void ILCPid_Init(ILCPid_t *pid, float target_temp);

/**
 * @brief 在线修改目标温度
 * @param pid 控制器结构体指针
 * @param target_temp 新目标温度 (℃)
 */
void ILCPid_SetTarget(ILCPid_t *pid, float target_temp);

/**
 * @brief ILC 计算制冷输出比例
 * @param pid 控制器结构体指针
 * @param current_temp 当前实测温度 (℃)
 * @return 制冷比例 0.0f(关闭) ~ 1.0f(最大制冷)
 * @note 必须在固定周期(500ms)内周期性调用；连续运行按固定相位循环学习
 */
float ILCPid_Compute(ILCPid_t *pid, float current_temp);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
