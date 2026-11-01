/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
/**
 * @file    compiler.h
 * @brief   编译器抽象层: 让用户自有程序与第三方库同时兼容
 *          ARM Compiler 5(armcc, AC5) 与 ARM Compiler 6(armclang, AC6)。
 *
 * 本头不依赖任何 HAL/RTOS, 处于最底层, 可被任意用户源文件直接包含。
 * STM32Cube 生成的 targetBoard 目录代码不在双兼容改造范围内。
 *
 * 预定义宏判定依据(已在本机实测):
 *   armcc    : __ARMCC_VERSION=5060960, 且定义 __CC_ARM, 不定义 __clang__
 *   armclang : __ARMCC_VERSION=6240002(>=6000000), 定义 __clang__ 与 __GNUC__
 */
#ifndef __COMPILER_H__
#define __COMPILER_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/

/* ---- 编译器识别 ----------------------------------------------------------*/
#if defined(__clang__)
  #define SPLC_COMPILER_ARMCLANG 1
#elif defined(__ARMCC_VERSION)
  #define SPLC_COMPILER_ARMCC 1
#else
  #error 暂不支持的编译器: 仅支持 ARM Compiler 5(armcc) 与 ARM Compiler 6(armclang)
#endif

/* ---- 字符串化工具 --------------------------------------------------------*/
#define SPLC_STRINGIFY(x)      #x
#define SPLC_XSTRINGIFY(x)     SPLC_STRINGIFY(x)

/* ---- 强制内联 ------------------------------------------------------------*/
/* armcc 用 __forceinline 在同一翻译单元内强制内联; armclang 默认不识别该
 * 关键字。本工程所有 __forceinline 函数均在对应头文件中有普通声明, 且被
 * 其他翻译单元跨文件调用(外部链接); 跨文件调用在两个编译器下都不会真正
 * 内联, 故 armclang 下退化为普通外部函数, 链接性质与运行语义保持一致。 */
#if defined(SPLC_COMPILER_ARMCC)
  #define SPLC_FORCE_INLINE    __forceinline
#else
  #define SPLC_FORCE_INLINE
#endif

/* ---- 绝对地址放置 --------------------------------------------------------*/
/* armcc 用 __attribute__((at(addr))); armclang 不支持 at 属性(会告警并忽略)。
 * 统一改用 armlink 在两个编译器下都识别的特殊命名段 ".ARM.__at_0x<hex>"。
 * 参数 hex 必须是【不带 0x 前缀、不带 UL 后缀】的十六进制数字, 例如:
 *   SPLC_PLACE_AT(10000000)  -> section(".ARM.__at_0x10000000")
 * 固定地址段统一附加 zero_init(UNINIT, 不生成加载段内容):
 *   1) 消除 Keil Flash 下载时 "No Algorithm found for: <地址>" 警告——下载器无需向
 *      无烧写算法的 RAM/备份SRAM 等地址写入初始化块;
 *   2) 语义更正确: 掉电存储区(BKPSRAM)与 CCM 缓冲保持上电原始内容, 不被清零。
 *   仅适用于 RAM 类绝对地址段; 若需在绝对地址存放带初值的只读数据, 请勿使用本宏。
 */
#define SPLC_PLACE_AT(hex)     __attribute__((section(".ARM.__at_0x" SPLC_STRINGIFY(hex)), zero_init))

/* ---- 禁用半主机 ----------------------------------------------------------*/
/* armcc 用 #pragma import(__use_no_semihosting); armclang 不支持 #pragma
 * import, 改用声明全局符号的内联汇编。Cortex-M 上原 __use_no_semihosting_swi
 * 与 __use_no_semihosting 效果相同, 统一为后者。 */
#if defined(SPLC_COMPILER_ARMCC)
  #define SPLC_NO_SEMIHOSTING  _Pragma("import(__use_no_semihosting)")
#else
  #define SPLC_NO_SEMIHOSTING  __asm(".global __use_no_semihosting");
#endif

/* ---- NOP 指令 ------------------------------------------------------------*/
/* armcc 内置 __nop(); armclang 无此内置函数, 映射为 GNU 风格内联汇编。
 * 这样用户代码中已有的裸 __nop() 无需逐处修改。 */
#if defined(SPLC_COMPILER_ARMCLANG)
  #ifndef __nop
    #define __nop()           __asm volatile("nop")
  #endif
#endif

/*****************************************************************************/
#ifdef __cplusplus
}
#endif
/*****************************************************************************/
#endif /* __COMPILER_H__ */
