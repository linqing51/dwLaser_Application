/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/

/*
 * Copyright (c) 2015-2021
 * Frank Denis <j at pureftpd dot org>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#ifndef __MINICSV_H__
#define __MINICSV_H__
/*****************************************************************************/
#ifdef __cplusplus
 extern "C" {
#endif
/*****************************************************************************/
#include <stddef.h>
#include "sPlc.h"
#define MINICSV_DELIM ','
#define MINICSV_QUOTE '"'
/*****************************************************************************/
/* 配置项 - 可根据MCU资源修改，全部宏定义，无全局堆 */
#define MINICSV_MAX_COLUMNS     																64U     /* 单一行最大字段数 */
#define MINICSV_FIELD_BUF_SIZE  																256U    /* 单个字段最大字节 */
/*****************************************************************************/
/* 解析状态返回码 */
typedef enum{
    MINICSV_OK = 0,
    MINICSV_ERR_BUF_TOO_SMALL,
    MINICSV_ERR_QUOTE_UNCLOSED,
    MINICSV_ERR_COLUMN_OVERFLOW,
    MINICSV_ERR_NULL_POINTER
}MiniCSV_StatusTypeDef;

/* 单行解析输出结构
 * fields: 指向各个字段起始指针(指向用户传入的work_buf内部)
 * field_len: 每个字段有效字节长度，不含结束符
 * field_count: 当前行实际解析出多少列
 */
typedef struct{
    char*       fields[MINICSV_MAX_COLUMNS];
    uint16_t    field_len[MINICSV_MAX_COLUMNS];
    uint16_t    field_count;
}MiniCSV_RowTypeDef;

/**
 * @brief  解析内存缓冲区中一整行CSV文本(非流式)
 * @param  in_buf: 输入原始csv文本缓冲区，'\0'结束
 * @param  work_buf: 工作缓存，用于存放去除引号转义后的字段内容，调用者提供，静态/栈
 * @param  work_buf_size: work_buf总字节大小
 * @param  out_row: 输出解析后的行结果
 * @retval MiniCSV_StatusTypeDef
 * @note   不修改in_buf；解析结果指针全部指向work_buf内部；无malloc；无goto
 */
MiniCSV_StatusTypeDef MiniCSV_ParseOneRow(const char* in_buf, char* work_buf, uint16_t work_buf_size, MiniCSV_RowTypeDef* out_row);

/**
 * @brief  将一行字段数组序列化为CSV行文本（写入用户提供输出buffer）
 * @param  row: 输入行数据
 * @param  out_buf: 输出缓存
 * @param  out_buf_size:输出缓存大小
 * @param  out_len: 返回实际生成字节数
 * @retval MiniCSV_StatusTypeDef
 */
MiniCSV_StatusTypeDef MiniCSV_WriteOneRow(const MiniCSV_RowTypeDef* row, char* out_buf, uint16_t out_buf_size, uint16_t* out_len);

char * minicsv_parse_line(char * const buf, char ** const cols, size_t * const cols_count_p, const size_t cols_max);

void minicsv_trim_cols(char ** const cols, const size_t cols_count);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif

#endif
