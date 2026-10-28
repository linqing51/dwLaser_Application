#ifndef __NN_PID_H__
#define __NN_PID_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include <stdint.h>
#include <math.h>
/*****************************************************************************/
// 单神经元自适应 PID（NN-PID）
// 核心思想：以误差 e(k) 及其一阶差分 Δe(k)、二阶差分 Δ²e(k) 作为神经元三个输入，
// 采用改进有监督 Hebb 学习规则在线调整三个权值（对应 P/I/D 通道），
// 无需任何离线参数整定，所有调节均在运行中动态完成。
// 增量式输出：u(k) = u(k-1) + K * Σ(wi*xi) / Σ|wi|，输出限幅 [out_min, out_max]。
// 学习规则：性能指标 z(k) = e(k) + Δe(k)；Δwi = ηi * z(k) * xi(k)；
//           误差小于学习死区或输出饱和时冻结学习；权值限幅 ±w_max 防发散。
// 输入温度单位：℃；输出：制冷比例 0.0 ~ 1.0（单冷 TEC，温度高于目标时输出制冷）。
typedef struct {
	// --- 目标与增益 ---
	float target;           // 目标温度 (℃)
	float k_neuron;         // 神经元输出增量增益 K
	// --- 神经元权值（P/I/D 三通道） ---
	float w1, w2, w3;       // 比例/积分/微分通道权值
	float eta1, eta2, eta3; // 各通道学习率
	float w_max;            // 权值限幅（防发散）
	// --- 运算状态 ---
	float e1, e2;           // 历史误差 e(k-1)、e(k-2)（Δe、Δ²e 计算）
	float u_prev;           // 上一拍输出（增量累加器，兼积分作用）
	float learn_deadband;   // 学习死区 (℃)，误差绝对值小于此值冻结学习
	float out_min, out_max; // 输出限幅（制冷比例）
} NNPid_t;
/*****************************************************************************/
// 对外接口函数声明

/**
 * @brief 初始化单神经元自适应 PID 控制器
 * @param pid 控制器结构体指针
 * @param target_temp 目标温度 (℃)
 * @note 权值初始为比例主导，学习过程在线自适应，无离线整定
 */
void NNPid_Init(NNPid_t *pid, float target_temp);

/**
 * @brief 在线修改目标温度
 * @param pid 控制器结构体指针
 * @param target_temp 新目标温度 (℃)
 * @note 支持运行中改设定，误差历史随之自然过渡
 */
void NNPid_SetTarget(NNPid_t *pid, float target_temp);

/**
 * @brief 计算单冷制冷输出比例
 * @param pid 控制器结构体指针
 * @param current_temp 当前实测温度 (℃)
 * @return 制冷比例 0.0f(关闭) ~ 1.0f(最大制冷)，已做输出限幅
 * @note 必须在固定周期(如500ms)内周期性调用；内含学习死区与饱和冻结
 */
float NNPid_Compute(NNPid_t *pid, float current_temp);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
