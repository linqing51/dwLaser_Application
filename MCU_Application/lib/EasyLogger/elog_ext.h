/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * Name:    EasyLogger 工程扩展层
 * Purpose: 提供与 printf 完全兼容的分级输出宏 LOG_PRINT(级别, 格式串, ...)
 * Note(s): 基于官方 armink/EasyLogger v2.2.99 的公开接口 elog_output().
 *          级别语义: 数字越大越详细
 *          ASSERT(0)<ERROR(1)<WARN(2)<INFO(3)<DEBUG(4)<VERBOSE(5)
 *          设置过滤级别 X 后仅输出 level<=X 的消息:
 *          设 VERBOSE(5) 输出全部(高优先级包含低优先级全部内容);
 *          设 ERROR(1)  仅输出 ERROR/ASSERT.
 *----------------------------------------------------------------------------*/
#ifndef __ELOG_EXT_H__
#define __ELOG_EXT_H__

#include "elog.h"

/* 与 printf 格式完全兼容的分级输出: LOG_PRINT(级别, 格式串, ...)
 * 输出内容 = 原格式串文本(默认无前缀纯文本, 与 printf 一致;
 *           如需级别标识可调用 elog_set_fmt(level, ELOG_FMT_LVL) 开启 [A/E/W/I/D/V] 前缀) */
#define LOG_PRINT(level, fmt, ...)  elog_output(level, "", NULL, NULL, 0, fmt, ##__VA_ARGS__)

#endif
