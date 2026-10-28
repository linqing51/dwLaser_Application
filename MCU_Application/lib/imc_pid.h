#ifndef __IMC_PID_H__
#define __IMC_PID_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include <stdint.h>
#include <math.h>
/*****************************************************************************/
// IMC 内模控制（内置一阶 RLS 在线辨识 + 一阶低通滤波器化的模型逆）
// 原理：
//   1) RLS 在线辨识一阶 ARX 模型：y(k+1) = -a1·y(k) + b0·u(k)
//   2) 内模结构：模型输出 yhat 与实际输出之差 d = y - yhat 视为扰动/模型误差，
//      参考输入经扰动补偿后 e_imc = r - d 送入模型逆控制器。
//   3) 控制器 Q = Ĝ⁻¹·F，F = (1-α)/(1-α·z⁻¹) 为可调低通滤波器（α 越大越平滑越慢），
//      差分方程实现：u(k) = α·u(k-1) + (1-α)·(e_imc(k) + a1·e_imc(k-1))/b0
//   4) 模型精确时闭环传递函数 = F（内模控制的鲁棒性来源：滤波器 α 直接整定鲁棒性）；
//      单冷 TEC 的负增益符号由 RLS 辨识自动确定，控制器符号自动正确。
// 输入温度单位：℃；输出：制冷比例 0.0 ~ 1.0（单冷 TEC）。
#define IMC_IDENT_MIN    60   // 最小辨识拍数
#define IMC_DEADBAND     0.05f// 辨识更新死区（℃）
#define IMC_B_MIN        1e-3f// 模型增益有效下限
#define IMC_A1_MAX       1.98f// a1 限幅
#define IMC_B_MAX        0.5f // b0 限幅（℃/控制比例）
typedef struct {
	// --- 目标 ---
	float target;           // 目标温度 (℃)
	// --- RLS 辨识状态（一阶 ARX：a1, b0） ---
	float a1, b0;           // 模型参数 y(k+1) = -a1·y(k) + b0·u(k)
	float P[2][2];          // 协方差矩阵
	float lambda;           // 遗忘因子
	float y_prev, u_prev;   // 历史输出/输入
	// --- IMC 参数 ---
	float alpha;            // 滤波器参数（0.7~0.95，越大越平滑越慢，默认 0.8）
	float k_default;        // 模型未就绪期间默认比例增量增益
	// --- 状态 ---
	float yhat;             // 模型输出（内模）
	float e_prev;           // 上一拍 e_imc
	float learn_deadband;   // 辨识更新死区
	float b_min;            // 模型增益有效下限
	uint32_t ident_count;   // 辨识拍数
	uint8_t  model_ready;   // 模型就绪标志
	uint8_t  init_flag;     // 首拍初始化标志
	float u_out;            // 当前输出
	float out_min, out_max; // 输出限幅
} IMCPid_t;
/*****************************************************************************/
// 对外接口函数声明

/**
 * @brief 初始化 IMC 控制器
 * @param pid 控制器结构体指针
 * @param target_temp 目标温度 (℃)
 */
void IMCPid_Init(IMCPid_t *pid, float target_temp);

/**
 * @brief 在线修改目标温度
 * @param pid 控制器结构体指针
 * @param target_temp 新目标温度 (℃)
 */
void IMCPid_SetTarget(IMCPid_t *pid, float target_temp);

/**
 * @brief RLS 辨识 + IMC 计算制冷输出比例
 * @param pid 控制器结构体指针
 * @param current_temp 当前实测温度 (℃)
 * @return 制冷比例 0.0f(关闭) ~ 1.0f(最大制冷)
 * @note 必须在固定周期(500ms)内周期性调用
 */
float IMCPid_Compute(IMCPid_t *pid, float current_temp);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
