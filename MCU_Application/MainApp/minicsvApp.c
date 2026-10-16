#include "minicsvApp.h"
/*****************************************************************************/
/* 全局静态缓冲区，不要放在栈上！STM32栈很小 */
static char csv_file_buf[1024];     /* FATFS读取文件块缓冲区 */
static char csv_work_buf[512];      /* MiniCSV解析工作缓冲区 */
static char csv_write_buf[512];     /* CSV行输出序列化缓冲区 */
/*****************************************************************************/
/**
 * @brief 示例1：读取SD/U盘上csv文件，逐行解析
 */
void MiniCSV_ReadCsvFile(const char* file_path){
	FIL file;
	FRESULT fr;
	MiniCSV_StatusTypeDef csv_ret;
	MiniCSV_RowTypeDef csv_row;
	TCHAR *pGet;   // f_gets 返回指针

	fr = f_open(&file, file_path, FA_READ);
	if(fr != FR_OK){
		return;
	}
	while(1){
		/* FATFS读取一行，简单实现：读取一块，找到换行；适合嵌入式 */
		pGet = f_gets(csv_file_buf, sizeof(csv_file_buf), &file);
		if(pGet == NULL){//文件结束或者读取出错
			break;
		}
		
		csv_ret = MiniCSV_ParseOneRow(csv_file_buf, csv_work_buf, sizeof(csv_work_buf), &csv_row);
		if(csv_ret == MINICSV_OK){
			/* 打印解析结果，示例：串口输出 */
			for(uint16_t col = 0; col < csv_row.field_count; col++){
				/* csv_row.fields[col] 指向csv_work_buf内部，csv_row.field_len[col]长度 */
				(void)col;
				/* 使用示例：
				printf("col%d:[%.*s]\r\n", col, csv_row.field_len[col], csv_row.fields[col]);
				*/
			}
		}
	}

	f_close(&file);
}

/**
 * @brief 示例2：构造一行CSV数据，写入文件
 */
void MiniCSV_WriteCsvFile(const char* file_path){
	FIL file;
	FRESULT fr;
	MiniCSV_StatusTypeDef csv_ret;
	MiniCSV_RowTypeDef csv_row;
	UINT write_len;
	uint16_t out_len;

	/* 重置行结构 */
	memset(&csv_row, 0, sizeof(csv_row));

	/* 构造3个字段，字段指向静态数组 */
	static char f0[] = "传感器A";
	static char f1[] = "23.45";
	static char f2[] = "测试,带逗号";

	csv_row.fields[0] = f0;
	csv_row.field_len[0] = strlen(f0);

	csv_row.fields[1] = f1;
	csv_row.field_len[1] = strlen(f1);

	csv_row.fields[2] = f2;
	csv_row.field_len[2] = strlen(f2);

	csv_row.field_count = 3U;

	/* 序列化为CSV行文本 */
	csv_ret = MiniCSV_WriteOneRow(&csv_row, csv_write_buf, sizeof(csv_write_buf), &out_len);
	if(csv_ret != MINICSV_OK){
		return;
	}

	fr = f_open(&file, file_path, FA_OPEN_ALWAYS | FA_WRITE);
	if(fr != FR_OK){
		return;
	}
	f_lseek(&file, f_size(&file)); /* 追加模式，跳到文件末尾 */

	fr = f_write(&file, csv_write_buf, out_len, &write_len);
	f_close(&file);
}

/**
 * @brief FreeRTOS任务入口示例
 */
void vMiniCSVTestTask(void *pvParameters){
	(void) pvParameters;

	for(;;){
			MiniCSV_ReadCsvFile("0:/test.csv");
			MiniCSV_WriteCsvFile("0:/test.csv");
			vTaskDelay(pdMS_TO_TICKS(5000));
	}
}
