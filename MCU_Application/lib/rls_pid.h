#ifndef __RLS_PID_H__
#define __RLS_PID_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include <stdint.h>
#include <math.h>
/*****************************************************************************/
// RLS 递推辨识 + 极点配置自校正 PID（RLS-PID）
// 原理：
//   1) 递推最小二乘(RLS, 遗忘因子λ)在线辨识被控对象 ARX 模型：
//        y(k) = -a1·y(k-1) - a2·y(k-2) + b0·u(k-1) + b1·u(k-2)
//      预测误差小于辨识死区时不更新（无激励不学习，防协方差退化/参数漂移）。
//   2) 极点配置自校正：取积分型控制器 R = 1 - q^-1（增量式），
//       控制律：Δu(k) = t0·w(k) - s0·y(k) - s1·y(k-1)
//       求解 A·R + B·S = Ac：期望主导极点 p_target（由开环极点收缩获得，
//       保证闭环略快于开环、无激进超调），第三极点由方程自然决定并校验稳定。
//       前馈系数 t0 = Ac(1)/B(1) 保证闭环直流增益为 1（无静差跟踪）。
//   3) 模型未就绪（辨识拍数不足或模型增益无效）时，以默认比例增量控制
//      (k_default) 过渡，就绪后每拍按最新模型重算 s0/s1/t0，在线自校正。
// 输入温度单位：℃；输出：制冷比例 0.0 ~ 1.0（单冷 TEC）。
typedef struct {
	// --- RLS 辨识状态 ---
	float a1, a2, b0, b1;      // ARX 模型参数 θ=[a1,a2,b0,b1]
	float P[4][4];             // 协方差矩阵（RLS 增益）
	float lambda;              // 遗忘因子（0.95~0.99，慢时变系统取大值）
	float y_prev, y_prev2;     // 历史输出 y(k-1)、y(k-2)（℃）
	float u_prev, u_prev2;     // 历史输入 u(k-1)、u(k-2)（制冷比例）
	// --- 极点配置控制器参数 ---
	float s0, s1, t0;          // 控制律系数：Δu = t0·w - s0·y - s1·y_prev
	float p_target;            // 期望主导极点（由开环极点收缩自适应）
	float k_default;           // 模型未就绪期间的默认比例增量增益
	// --- 保护与状态 ---
	float target;              // 目标温度 (℃)
	float out_min, out_max;    // 输出限幅（制冷比例）
	float learn_deadband;      // 辨识更新死区 (℃)，预测误差小于此值不更新
	float b_min;               // 模型增益有效下限（|b0| 小于此值视为模型无效）
	uint32_t ident_count;      // 辨识拍数
	uint8_t  model_ready;      // 模型就绪标志（1=极点配置已生效）
	float u_out;               // 当前输出（制冷比例）
} RLSPid_t;
/*****************************************************************************/
// 对外接口函数声明

/**
 * @brief 初始化 RLS 自校正 PID 控制器
 * @param pid 控制器结构体指针
 * @param target_temp 目标温度 (℃)
 * @note 辨识期自动以默认比例控制过渡，模型收敛后无缝切换极点配置
 */
void RLSPid_Init(RLSPid_t *pid, float target_temp);

/**
 * @brief 在线修改目标温度
 * @param pid 控制器结构体指针
 * @param target_temp 新目标温度 (℃)
 */
void RLSPid_SetTarget(RLSPid_t *pid, float target_temp);

/**
 * @brief 递推辨识 + 极点配置计算制冷输出比例
 * @param pid 控制器结构体指针
 * @param current_temp 当前实测温度 (℃)
 * @return 制冷比例 0.0f(关闭) ~ 1.0f(最大制冷)
 * @note 必须在固定周期(如500ms)内周期性调用；内部自动完成 RLS 一步辨识、
 *       模型有效性检查与极点配置控制律计算
 */
float RLSPid_Compute(RLSPid_t *pid, float current_temp);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
