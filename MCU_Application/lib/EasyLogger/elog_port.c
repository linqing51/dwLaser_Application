/*
 * This file is part of the EasyLogger Library.
 *
 * Copyright (c) 2015, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: Portable interface for each platform.
 * Created on: 2015-04-28
 */
/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
/* 移植适配: 调试串口输出(与 printf 同串口 CONFIG_DEBUG_UART = huart3)
 * 单线程主循环使用, 无需互斥锁; 时间/进程/线程信息未启用(默认纯文本输出) */
#include <elog.h>
#include "main.h"
#include "BoardConfig.h"                     /* CONFIG_DEBUG_UART = huart3(调试串口) */

extern UART_HandleTypeDef CONFIG_DEBUG_UART; /* 宏展开为 huart3 调试串口句柄 */

/**
 * EasyLogger port initialize
 */
ElogErrCode elog_port_init(void) {
    ElogErrCode result = ELOG_NO_ERR;
    /* 串口已由系统初始化, 此处无需额外动作 */
    return result;
}

/**
 * EasyLogger port deinitialize
 */
void elog_port_deinit(void) {
}

/**
 * output log port interface: 整条日志发送到调试串口
 */
void elog_port_output(const char *log, size_t size) {
    if(size == 0){ return; }
    HAL_UART_Transmit(&CONFIG_DEBUG_UART, (const uint8_t *)log, (uint16_t)size, HAL_MAX_DELAY);
}

/**
 * output lock (单线程无需互斥)
 */
void elog_port_output_lock(void) {
}

/**
 * output unlock
 */
void elog_port_output_unlock(void) {
}

/**
 * get current time interface (未启用时间格式)
 */
const char *elog_port_get_time(void) {
    return "";
}

/**
 * get current process name interface (未启用)
 */
const char *elog_port_get_p_info(void) {
    return "";
}

/**
 * get current thread name interface (未启用)
 */
const char *elog_port_get_t_info(void) {
    return "";
}
