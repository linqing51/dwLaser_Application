/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "minicsvApp.h"



//患者 ID 的编码规则是：
//1. AR + 一个空格 + 至少 4 位的递增数字，例如：AR 0001、AR 0002、AR 0011。
//- 自动生成、不可手动修改：取现有患者 ID 中最大的数字加 1，不足 4 位时前面补零。
//- 新患者分配新 ID：目前 Demo 已有编号到 AR 0010，所以下一位是 AR 0011。
//- 已有患者继续使用原 ID：再次治疗时追加治疗记录，不重新编号。
//- 同名不代表同一患者：选择已有患者就复用其 ID；选择「Create New Patient」则生成新 ID。


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
void MiniCSV_WriteCsvFile(const char* file_path, treatmentLog_t *plog){
	FIL file;
	FRESULT fr;
	MiniCSV_StatusTypeDef csv_ret;
	MiniCSV_RowTypeDef csv_row;
	UINT write_len;
	uint16_t out_len;

	/* 重置行结构 */
	memset(&csv_row, 0, sizeof(csv_row));

	printf("Free heap: %d bytes\n", xPortGetFreeHeapSize());
  printf("Min ever:  %d bytes\n", xPortGetMinimumEverFreeHeapSize());
	
	char *pf0 = (char *)pvPortMalloc(64);
	configASSERT(pf0 != NULL);
	memset(pf0, 0, 64);
	sprintf(pf0, "%u", plog->id);
	
	char *pf1 = (char *)pvPortMalloc(64);
	configASSERT(pf1 != NULL);
	memset(pf1, 0, 64);
	sprintf(pf1, "%s", plog->name);
	
	char *pf2 = (char *)pvPortMalloc(64);
	configASSERT(pf2 != NULL);
	memset(pf2, 0, 64);
	sprintf(pf2, "%s", (plog->gender == MALE) ? "Male" : "Female");
	
	char *pf3 = (char *)pvPortMalloc(64);
	configASSERT(pf3 != NULL);
	memset(pf3, 0, 64);
	sprintf(pf3, "%u", plog->age);
	
	char *pf4 = (char *)pvPortMalloc(64);
	configASSERT(pf4 != NULL);
	memset(pf4, 0, 64);
	sprintf(pf4, "%d", plog->laserPower);
	
	char *pf5 = (char *)pvPortMalloc(64);
	configASSERT(pf5 != NULL);
	memset(pf5, 0, 64);
	sprintf(pf5, "%s", treatmentLaserWaveName(plog->laserWave));
	
	char *pf6 = (char *)pvPortMalloc(64);
	configASSERT(pf6 != NULL);
	memset(pf6, 0, 64);
	sprintf(pf6, "%s", treatmentProtocolName(plog->protocol));
		
	char *pf7 = (char *)pvPortMalloc(64);
	configASSERT(pf7 != NULL);
	memset(pf7, 0, 64);
	sprintf(pf7, "%ld", (long)plog->releaseEnergy);
	
	char *pf8 = (char *)pvPortMalloc(64);
	configASSERT(pf8 != NULL);
	memset(pf8, 0, 64);
	sprintf(pf8, "%ld", (long)plog->releaseTime);

	printf("Free heap: %d bytes\n", xPortGetFreeHeapSize());
  printf("Min ever:  %d bytes\n", xPortGetMinimumEverFreeHeapSize());
	
	csv_row.fields[0] = pf0;csv_row.field_len[0] = strlen(pf0);

	csv_row.fields[1] = pf1;csv_row.field_len[1] = strlen(pf1);

	csv_row.fields[2] = pf2;csv_row.field_len[2] = strlen(pf2);

	csv_row.fields[3] = pf3;csv_row.field_len[3] = strlen(pf3);

	csv_row.fields[4] = pf4;csv_row.field_len[4] = strlen(pf4);

	csv_row.fields[5] = pf5;csv_row.field_len[5] = strlen(pf5);
	
	csv_row.fields[6] = pf6;csv_row.field_len[6] = strlen(pf6);
	
	csv_row.fields[7] = pf7;csv_row.field_len[7] = strlen(pf7);

	csv_row.fields[8] = pf8;csv_row.field_len[8] =strlen(pf8);

	csv_row.field_count = 9U;

	/* 序列化为CSV行文本 */
	csv_ret = MiniCSV_WriteOneRow(&csv_row, csv_write_buf, sizeof(csv_write_buf), &out_len);
	if(csv_ret != MINICSV_OK){
		goto csv_cleanup;
	}
	
	
	
	
	fr = f_open(&file, TREATMENTLOG_FILENAME, FA_OPEN_ALWAYS | FA_WRITE);
	if(fr != FR_OK){
		goto csv_cleanup;
	}
	f_lseek(&file, f_size(&file)); /* 追加模式，跳到文件末尾 */

	fr = f_write(&file, csv_write_buf, out_len, &write_len);
	f_close(&file);

	csv_cleanup:
	vPortFree(pf0);pf0 = NULL;  // 防野指针
	vPortFree(pf1);pf1 = NULL;  // 防野指针
	vPortFree(pf2);pf2 = NULL;  // 防野指针
	vPortFree(pf3);pf3 = NULL;  // 防野指针
	vPortFree(pf4);pf4 = NULL;  // 防野指针
	vPortFree(pf5);pf5 = NULL;  // 防野指针
	vPortFree(pf6);pf6 = NULL;  // 防野指针
	vPortFree(pf7);pf7 = NULL;  // 防野指针
	vPortFree(pf8);pf8 = NULL;  // 防野指针
}

/**
 * @brief FreeRTOS任务入口示例
 */
void vMiniCSVTestTask(void *pvParameters){
	(void) pvParameters;

	for(;;){
			MiniCSV_ReadCsvFile("0:/test.csv");
			MiniCSV_WriteCsvFile("0:/test.csv", &treatmentLog);
			vTaskDelay(pdMS_TO_TICKS(5000));
	}
}
