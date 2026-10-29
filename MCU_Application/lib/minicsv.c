/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "minicsv.h"

static inline void
_minicsv_out_col(char * const col_start, char ** const cols,
                 size_t * const cols_count_p, const size_t cols_max)
{
    if (*cols_count_p < cols_max) {
        cols[*cols_count_p] = col_start;
    }
    (*cols_count_p)++;
}

static inline void
_minicsv_parse_line_noquote(const int c, char ** const pos_p,
                            char ** const col_start_p, int * const state_p,
                            char ** const cols, size_t * const cols_count_p,
                            const size_t cols_max)
{
    switch (c) {
    case '\n':
        *state_p = 2;
    case MINICSV_DELIM:
        *(*pos_p)++ = 0;
        _minicsv_out_col(*col_start_p, cols, cols_count_p, cols_max);
        *col_start_p = *pos_p;
        break;
    case MINICSV_QUOTE:
        *state_p = 1;
        *col_start_p = ++*pos_p;
        break;
    case '\r':
        **pos_p = 0;
    default:
        (*pos_p)++;
    }
}

static inline void
_minicsv_parse_line_quote(const int c, char ** const pos_p,
                          int * const state_p)
{
    if (c == MINICSV_QUOTE) {
        if (*(*pos_p + 1U) == MINICSV_QUOTE) {
            memmove(*pos_p, *pos_p + 1U, strlen(*pos_p));
        } else {
            **pos_p = 0;
            *state_p = 0;
        }
    }
    (*pos_p)++;
}

char *
minicsv_parse_line(char * const buf, char ** const cols,
                   size_t * const cols_count_p, const size_t cols_max)
{
    char *col_start = buf;
    char *pos       = buf;
    int   c;
    int   state = 0;

    *cols_count_p = (size_t) 0U;
    while ((c = *pos) != 0) {
        switch (state) {
        case 0:
            _minicsv_parse_line_noquote(c, &pos, &col_start, &state,
                                        cols, cols_count_p, cols_max);
            break;
        case 1:
            _minicsv_parse_line_quote(c, &pos, &state);
            break;
        case 2:
            return pos;
        }
    }
    if (state == 0) {
        _minicsv_out_col(col_start, cols, cols_count_p, cols_max);
    }
    return pos;
}

void
minicsv_trim_cols(char ** const cols, const size_t cols_count)
{
    char   *col;
    size_t  col_end;
    size_t  i = (size_t) 0U;

    while (i < cols_count) {
        col = cols[i];
        while (*col != 0 && isspace((int) (unsigned char) *col)) {
            cols[i] = ++col;
        }
        col_end = strlen(col);
        while (col_end > (size_t) 0U &&
               isspace((int) (unsigned char) col[--col_end])) {
            col[col_end] = 0;
        }
        i++;
    }
}

/*****************************************************************************/
//minicsv 扩展
static bool MiniCSV_IsDelimiter(char ch){
    return ((ch == ',') || (ch == '\r') || (ch == '\n'));
}

MiniCSV_StatusTypeDef MiniCSV_ParseOneRow(const char* in_buf, char* work_buf, uint16_t work_buf_size, MiniCSV_RowTypeDef* out_row){
	if((in_buf == NULL) || (work_buf == NULL) || (out_row == NULL)){
		return MINICSV_ERR_NULL_POINTER;
	}
	if(work_buf_size < 4U){
		return MINICSV_ERR_BUF_TOO_SMALL;
	}

	/* 初始化输出结构体 */
	for(uint16_t i = 0U; i < MINICSV_MAX_COLUMNS; i++){
		out_row->fields[i] = NULL;
		out_row->field_len[i] = 0U;
	}
	out_row->field_count = 0U;

	uint16_t wk_idx = 0U;
	bool inside_quote = false;
	bool field_start = true;

	const char* p_in = in_buf;

	while((*p_in != '\0')){
		char ch = *p_in;

		if(inside_quote){
			if(ch == '\"'){
				/* 双引号：判断是否是转义 "" */
				if(*(p_in + 1U) == '\"'){
					/* "" 转义为一个 " */
					p_in++;
					if(wk_idx >= work_buf_size)
					{
							return MINICSV_ERR_BUF_TOO_SMALL;
					}
					work_buf[wk_idx++] = '\"';
				}
				else{
					/* 结束引号 */
					inside_quote = false;
				}
			}
			else{
				/* 引号内部原样拷贝，包含逗号、换行 */
				if(wk_idx >= work_buf_size){
					return MINICSV_ERR_BUF_TOO_SMALL;
				}
				work_buf[wk_idx++] = ch;
			}
			p_in++;
		}
		else{
			if(field_start){
				field_start = false;
				/* 开启新字段 */
				if(out_row->field_count >= MINICSV_MAX_COLUMNS)
				{
						return MINICSV_ERR_COLUMN_OVERFLOW;
				}
				out_row->fields[out_row->field_count] = &work_buf[wk_idx];
				out_row->field_len[out_row->field_count] = 0U;
			}

			if(ch == '\"'){
				inside_quote = true;
				p_in++;
			}
			else if(MiniCSV_IsDelimiter(ch)){
				/* 字段结束 */
				out_row->field_len[out_row->field_count] = wk_idx - (uint16_t)(out_row->fields[out_row->field_count] - work_buf);
				out_row->field_count++;

				/* 如果是换行，本行解析完成 */
				if((ch == '\r') || (ch == '\n')){
					/* 跳过LF/CR组合 */
					if((ch == '\r') && (*(p_in+1U) == '\n')){
							p_in++;
					}
					break;
				}
				/* 逗号，开启下一个字段 */
				field_start = true;
				p_in++;
			}
			else{
				/* 普通字符 */
				if(wk_idx >= work_buf_size){
					return MINICSV_ERR_BUF_TOO_SMALL;
				}
				work_buf[wk_idx++] = ch;
				p_in++;
			}
		}
	}

	/* 循环结束后，如果引号未关闭，报错 */
	if(inside_quote){
		return MINICSV_ERR_QUOTE_UNCLOSED;
	}

	/* 如果缓冲区结束，但还没有闭合最后一个字段 */
	if(!field_start && (out_row->field_count < MINICSV_MAX_COLUMNS)){
		out_row->field_len[out_row->field_count] = wk_idx - (uint16_t)(out_row->fields[out_row->field_count] - work_buf);
		out_row->field_count++;
	}

	return MINICSV_OK;
}

MiniCSV_StatusTypeDef MiniCSV_WriteOneRow(const MiniCSV_RowTypeDef* row, char* out_buf, uint16_t out_buf_size, uint16_t* out_len){
	if((row == NULL) || (out_buf == NULL) || (out_len == NULL)){
		return MINICSV_ERR_NULL_POINTER;
	}
	*out_len = 0U;
	uint16_t idx = 0U;

	for(uint16_t col = 0U; col < row->field_count; col++){
		if(col > 0U){
			/* 输出逗号分隔符 */
			if(idx >= out_buf_size - 1U){
					return MINICSV_ERR_BUF_TOO_SMALL;
			}
			out_buf[idx++] = ',';
		}

		char* field_ptr = row->fields[col];
		uint16_t field_sz = row->field_len[col];

		bool need_quote = false;
		/* 判断字段是否需要双引号包裹：包含逗号、换行、双引号 */
		for(uint16_t i = 0U; i < field_sz; i++){
			char c = field_ptr[i];
			if((c == ',') || (c == '\n') || (c == '\r') || (c == '\"')){
				need_quote = true;
				break;
			}
		}

		if(need_quote){
			if(idx >= out_buf_size - 2U){
				return MINICSV_ERR_BUF_TOO_SMALL;
			}
			out_buf[idx++] = '\"';

			for(uint16_t i = 0U; i < field_sz; i++){
				char c = field_ptr[i];
				if(c == '\"'){
					if(idx >= out_buf_size - 2U){
						return MINICSV_ERR_BUF_TOO_SMALL;
					}
					out_buf[idx++] = '\"';
					out_buf[idx++] = '\"';
				}
				else{
					if(idx >= out_buf_size -1U)
					{
							return MINICSV_ERR_BUF_TOO_SMALL;
					}
					out_buf[idx++] = c;
				}
			}
			if(idx >= out_buf_size -2U){
				return MINICSV_ERR_BUF_TOO_SMALL;
			}
			out_buf[idx++] = '\"';
		}
		else{
			for(uint16_t i = 0U; i < field_sz; i++){
				if(idx >= out_buf_size -1U){
					return MINICSV_ERR_BUF_TOO_SMALL;
				}
				out_buf[idx++] = field_ptr[i];
			}
		}
	}

	/* 添加换行 CRLF windows csv格式 */
	if(idx + 2U < out_buf_size){
		out_buf[idx++] = '\r';
		out_buf[idx++] = '\n';
	}
	*out_len = idx;
	return MINICSV_OK;
}


