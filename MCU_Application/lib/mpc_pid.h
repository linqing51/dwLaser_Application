/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#ifndef __MPC_PID_H__
#define __MPC_PID_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include <stdint.h>
#include <math.h>
/*****************************************************************************/
// MPC 模型预测控制（内置 RLS 在线辨识 ARX 模型 + 单步滚动优化解析解）
// 原理：
//   1) RLS(遗忘因子λ)在线辨识二阶 ARX：y(k) = -a1·y(k-1) - a2·y(k-2)
//                                            + b0·u(k-1) + b1·u(k-2)
//   2) 预测：以单位阶跃响应系数 S_i 与自由响应 yf_i 外推 N 步，
//      假设未来控制量为当前增量 Δu 并保持（M=1、N=3）。
//   3) 目标函数 J = Σ q·(y_pred_i - r)² + ρ·Δu²，对 Δu 求导得解析解：
//        Δu* = q·Σ(S_i·(r - yf_i)) / (q·ΣS_i² + ρ)
//      输出限幅 [0,1]，ρ 惩罚控制增量抑制振荡。
//   4) 模型未就绪（辨识拍数不足或增益无效）时以默认比例增量过渡，
//      就绪后每拍按最新模型滚动计算（在线自校正）。
// 输入温度单位：℃；输出：制冷比例 0.0 ~ 1.0（单冷 TEC，模型符号由辨识自动确定）。
#define MPC_HORIZON      3    // 预测步数 N
#define MPC_IDENT_MIN    60   // 最小辨识拍数（500ms×60=30s）
#define MPC_DEADBAND     0.05f// 辨识更新死区（℃）
#define MPC_B_MIN        1e-3f// 模型增益有效下限
#define MPC_A1_MAX       1.98f// a1 限幅
#define MPC_A2_MAX       0.99f// a2 限幅
#define MPC_B_MAX        0.5f // b0/b1 限幅（℃/控制比例）
typedef struct {
	// --- 目标 ---
	float target;           // 目标温度 (℃)
	// --- RLS 辨识状态 ---
	float a1, a2, b0, b1;   // ARX 模型参数
	float P[4][4];          // 协方差矩阵
	float lambda;           // 遗忘因子
	float y_prev, y_prev2;  // 历史输出 y(k-1)、y(k-2)
	float u_prev, u_prev2;  // 历史输入 u(k-1)、u(k-2)
	// --- MPC 参数 ---
	float q;                // 跟踪权重（默认 1.0）
	float rho;              // 控制增量惩罚（默认 0.1，越大输出越平滑）
	float k_default;        // 模型未就绪期间默认比例增量增益
	// --- 状态 ---
	float learn_deadband;   // 辨识更新死区
	float b_min;            // 模型增益有效下限
	uint32_t ident_count;   // 辨识拍数
	uint8_t  model_ready;   // 模型就绪标志
	float u_out;            // 当前输出
	float out_min, out_max; // 输出限幅
} MPCPid_t;
/*****************************************************************************/
// 对外接口函数声明

/**
 * @brief 初始化 RLS+MPC 控制器
 * @param pid 控制器结构体指针
 * @param target_temp 目标温度 (℃)
 */
void MPCPid_Init(MPCPid_t *pid, float target_temp);

/**
 * @brief 在线修改目标温度
 * @param pid 控制器结构体指针
 * @param target_temp 新目标温度 (℃)
 */
void MPCPid_SetTarget(MPCPid_t *pid, float target_temp);

/**
 * @brief RLS 辨识 + MPC 滚动优化计算制冷输出比例
 * @param pid 控制器结构体指针
 * @param current_temp 当前实测温度 (℃)
 * @return 制冷比例 0.0f(关闭) ~ 1.0f(最大制冷)
 * @note 必须在固定周期(500ms)内周期性调用
 */
float MPCPid_Compute(MPCPid_t *pid, float current_temp);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
