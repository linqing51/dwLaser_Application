/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "minicsvApp.h"
/*****************************************************************************/
/* 全局静态缓冲区，不要放在栈上！STM32栈很小 */
static char csv_file_buf[1024];     /* FATFS读取文件块缓冲区 */
static char csv_work_buf[512];      /* MiniCSV解析工作缓冲区 */
static char csv_write_buf[512];     /* CSV行输出序列化缓冲区 */
static char csv_col_buf[10][48];    /* 单行10列文本缓冲(患者ID/序号/姓名/性别/年龄/功率/波长/方案/能量/时间) */
/*****************************************************************************/
/* 病历导出列定义: 一行 = 一条病历(患者信息随行重复, 便于第三方软件按行过滤) */
#define CSV_COL_PATIENT_ID											0
#define CSV_COL_RECORD_NO												1
#define CSV_COL_NAME														2
#define CSV_COL_GENDER													3
#define CSV_COL_AGE														4
#define CSV_COL_POWER													5
#define CSV_COL_WAVE													6
#define CSV_COL_PROTOCOL												7
#define CSV_COL_ENERGY													8
#define CSV_COL_TIME														9
#define CSV_COL_COUNT														10
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
 * @brief 取CSV表头(字段顺序与csvWriteRecordRow一致)
 */
static const char* csvHeaderLine(void){
	return "PatientID,Record,Name,Gender,Age,Power(W),Wave,Protocol,Energy(J),Time(s)\r\n";
}

/**
 * @brief 把一条病历写成一行CSV追加到已打开文件
 */
static FRESULT csvWriteRecordRow(FIL *file, uint16_t patientId, uint8_t recNo, const char *name, uint8_t gender, uint8_t age, const treatmentRecord_t *rec){
	MiniCSV_RowTypeDef csv_row;
	MiniCSV_StatusTypeDef csv_ret;
	uint16_t out_len = 0;
	UINT write_len = 0;
	FRESULT fr;

	memset(&csv_row, 0, sizeof(csv_row));
	memset(csv_col_buf, 0, sizeof(csv_col_buf));

	sprintf(csv_col_buf[CSV_COL_PATIENT_ID], "%04u", patientId);//患者ID与界面显示一致(4位补零)
	sprintf(csv_col_buf[CSV_COL_RECORD_NO], "%u", (unsigned)recNo);//该患者内的病历序号(从1开始)
	strncpy(csv_col_buf[CSV_COL_NAME], name, sizeof(csv_col_buf[CSV_COL_NAME]) - 1);
	csv_col_buf[CSV_COL_NAME][sizeof(csv_col_buf[CSV_COL_NAME]) - 1] = '\0';//截断保护
	sprintf(csv_col_buf[CSV_COL_GENDER], "%s", ((gender == MALE) ? "Male" : "Female"));
	sprintf(csv_col_buf[CSV_COL_AGE], "%u", (unsigned)age);
	sprintf(csv_col_buf[CSV_COL_POWER], "%d", rec->laserPower);
	sprintf(csv_col_buf[CSV_COL_WAVE], "%s", treatmentLaserWaveName((LASER_WAVE_ENUM)rec->laserWave));
	sprintf(csv_col_buf[CSV_COL_PROTOCOL], "%s", treatmentProtocolName((PROTOCOL_ENUM)rec->protocol));
	sprintf(csv_col_buf[CSV_COL_ENERGY], "%ld", (long)rec->releaseEnergy);
	sprintf(csv_col_buf[CSV_COL_TIME], "%ld", (long)rec->releaseTime);

	for(uint8_t i = 0; i < CSV_COL_COUNT; i++){
		csv_row.fields[i] = csv_col_buf[i];
		csv_row.field_len[i] = (uint16_t)strlen(csv_col_buf[i]);
	}
	csv_row.field_count = CSV_COL_COUNT;

	csv_ret = MiniCSV_WriteOneRow(&csv_row, csv_write_buf, sizeof(csv_write_buf), &out_len);
	if(csv_ret != MINICSV_OK){
		return FR_INT_ERR;
	}
	fr = f_write(file, csv_write_buf, out_len, &write_len);
	if(fr != FR_OK){
		return fr;
	}
	return ((write_len == out_len) ? FR_OK : FR_INT_ERR);
}

/**
 * @brief 导出全部患者病历到CSV(每行一条病历, 首行为表头)
 * @param  file_path: 目标文件路径, 例如 TREATMENTLOG_FILENAME
 * @retval 实际写入的病历条数; 0表示失败或无病历
 * @note   患者信息随每条病历重复写入, 便于Excel/第三方系统直接按行处理
 */
uint16_t MiniCSV_ExportAllPatients(const char* file_path){
	FIL file;
	FRESULT fr;
	UINT write_len = 0;
	uint16_t patient_count;
	uint16_t written = 0;
	treatmentPatient_t patient;
	treatmentRecord_t rec;

	if(file_path == NULL){
		return 0;
	}
	patient_count = treatmentEpromPatientCount();
	if(patient_count == 0){
		return 0;
	}
	fr = f_open(&file, file_path, FA_OPEN_ALWAYS | FA_WRITE);
	if(fr != FR_OK){
		return 0;
	}
	if(f_size(&file) == 0){//新文件: 先写表头
		fr = f_write(&file, csvHeaderLine(), (UINT)strlen(csvHeaderLine()), &write_len);
		if(fr != FR_OK){
			f_close(&file);
			return 0;
		}
	}
	f_lseek(&file, f_size(&file));//追加模式: 跳到文件末尾
	for(uint16_t p = 0; p < patient_count; p++){
		if(treatmentEpromPatientGet(p, &patient) != TREATMENT_EPROM_OK){
			break;
		}
		for(uint8_t r = 0; r < patient.recordCount; r++){
			if(treatmentEpromRecordGet(p, r, &rec) != TREATMENT_EPROM_OK){
				break;
			}
			if(csvWriteRecordRow(&file, patient.patientId, (uint8_t)(r + 1u), patient.name, patient.gender, patient.age, &rec) != FR_OK){
				break;
			}
			written++;
		}
	}
	f_close(&file);
	printf("%s,%d,%s:exported %u records, %u patients\n", __FILE__, __LINE__, __func__, (unsigned)written, (unsigned)patient_count);
	return written;
}

/**
 * @brief FreeRTOS任务入口示例
 */
void vMiniCSVTestTask(void *pvParameters){
	(void) pvParameters;

	for(;;){
			MiniCSV_ReadCsvFile("0:/test.csv");
			MiniCSV_ExportAllPatients(TREATMENTLOG_FILENAME);
			vTaskDelay(pdMS_TO_TICKS(5000));
	}
}
