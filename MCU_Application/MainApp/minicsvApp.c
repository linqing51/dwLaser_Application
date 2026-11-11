/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "minicsvApp.h"
#include <stdlib.h>//strtol
#include "usbh_core.h"//USBH_HandleTypeDef
#include "usbh_msc.h"//USBH_MSC_IsReady



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

/*****************************************************************************/
//治疗记录导出/导入(U盘CSV): 文件名由TREATMENTLOG_FILENAME定义
//列顺序: id,name,gender,age,power,wave,protocol,energy,time
//文件由同一固件生成, 读出时按字符串反查波长/方案枚举, 不做多语言兼容
/*****************************************************************************/
#define TREATMENT_CSV_COLUMNS												9U
static char treatmentCsvLineBuf[512];//单行序列化缓冲
static char treatmentCsvReadBuf[256];//f_gets行缓冲
static char treatmentCsvWorkBuf[512];//解析工作缓冲
static MiniCSV_RowTypeDef treatmentCsvRow;//行结构(静态, 避免占用任务栈)
static const char treatmentCsvHeader[] = "id,name,gender,age,power,wave,protocol,energy,time";

//把一条病历组装成CSV行并序列化, 返回序列化字节数(0=失败)
static uint16_t treatmentCsvBuildRow(const treatmentLog_t *log){
	char f0[8], f1[20], f2[8], f3[8], f4[8], f5[16], f6[16], f7[16], f8[16];
	uint16_t outLen = 0U;

	sprintf(f0, "%u", (unsigned int)log->id);
	sprintf(f1, "%.15s", log->name);
	sprintf(f2, "%s", (log->gender == MALE) ? "Male" : "Female");
	sprintf(f3, "%u", (unsigned int)log->age);
	sprintf(f4, "%d", (int)log->laserPower);
	sprintf(f5, "%s", treatmentLaserWaveName(log->laserWave));
	sprintf(f6, "%s", treatmentProtocolName(log->protocol));
	sprintf(f7, "%ld", (long)log->releaseEnergy);
	sprintf(f8, "%ld", (long)log->releaseTime);

	memset(&treatmentCsvRow, 0, sizeof(treatmentCsvRow));
	treatmentCsvRow.fields[0] = f0; treatmentCsvRow.field_len[0] = (uint16_t)strlen(f0);
	treatmentCsvRow.fields[1] = f1; treatmentCsvRow.field_len[1] = (uint16_t)strlen(f1);
	treatmentCsvRow.fields[2] = f2; treatmentCsvRow.field_len[2] = (uint16_t)strlen(f2);
	treatmentCsvRow.fields[3] = f3; treatmentCsvRow.field_len[3] = (uint16_t)strlen(f3);
	treatmentCsvRow.fields[4] = f4; treatmentCsvRow.field_len[4] = (uint16_t)strlen(f4);
	treatmentCsvRow.fields[5] = f5; treatmentCsvRow.field_len[5] = (uint16_t)strlen(f5);
	treatmentCsvRow.fields[6] = f6; treatmentCsvRow.field_len[6] = (uint16_t)strlen(f6);
	treatmentCsvRow.fields[7] = f7; treatmentCsvRow.field_len[7] = (uint16_t)strlen(f7);
	treatmentCsvRow.fields[8] = f8; treatmentCsvRow.field_len[8] = (uint16_t)strlen(f8);
	treatmentCsvRow.field_count = TREATMENT_CSV_COLUMNS;

	if(MiniCSV_WriteOneRow(&treatmentCsvRow, treatmentCsvLineBuf, (uint16_t)sizeof(treatmentCsvLineBuf), &outLen) != MINICSV_OK){
		return 0U;
	}
	return outLen;
}

//取一个字段的文本(去引号后的内容), 越界或为空时返回失败
static uint8_t treatmentCsvFieldText(const MiniCSV_RowTypeDef *row, uint16_t col, char *buf, uint16_t size){
	uint16_t len;
	if((col >= row->field_count) || (size == 0U)){
		return 0U;
	}
	len = row->field_len[col];
	if((len == 0U) || (len >= size)){
		return 0U;
	}
	memcpy(buf, row->fields[col], len);
	buf[len] = '\0';
	return 1U;
}

//取一个字段的整数值
static uint8_t treatmentCsvFieldLong(const MiniCSV_RowTypeDef *row, uint16_t col, long *out){
	char tmp[24];
	if(treatmentCsvFieldText(row, col, tmp, (uint16_t)sizeof(tmp)) == 0U){
		return 0U;
	}
	*out = strtol(tmp, NULL, 10);
	return 1U;
}

//解析一行CSV为病历记录, 字段非法返回0
static uint8_t treatmentCsvParseRecord(const char *line, treatmentLog_t *rec){
	char tmp[24];
	long v;
	uint16_t i;

	if(MiniCSV_ParseOneRow(line, treatmentCsvWorkBuf, (uint16_t)sizeof(treatmentCsvWorkBuf), &treatmentCsvRow) != MINICSV_OK){
		return 0U;
	}
	if(treatmentCsvRow.field_count < TREATMENT_CSV_COLUMNS){
		return 0U;
	}
	memset(rec, 0, sizeof(treatmentLog_t));
	if((treatmentCsvFieldLong(&treatmentCsvRow, 0U, &v) == 0U) || (v < 1L) || (v > (long)(CONFIG_EPROM_TREATMENT_SLOT_EMPTY - 1U))){
		return 0U;//患者ID须为有效编号
	}
	rec->id = (uint16_t)v;
	if(treatmentCsvFieldText(&treatmentCsvRow, 1U, rec->name, (uint16_t)sizeof(rec->name)) == 0U){
		return 0U;//姓名不能为空
	}
	if(treatmentCsvFieldText(&treatmentCsvRow, 2U, tmp, (uint16_t)sizeof(tmp)) == 0U){
		return 0U;
	}
	if(strcmp(tmp, "Male") == 0){
		rec->gender = MALE;
	}
	else if(strcmp(tmp, "Female") == 0){
		rec->gender = FEMALE;
	}
	else{
		return 0U;
	}
	if((treatmentCsvFieldLong(&treatmentCsvRow, 3U, &v) == 0U) || (v < 1L) || (v > 120L)){
		return 0U;//年龄
	}
	rec->age = (uint8_t)v;
	if((treatmentCsvFieldLong(&treatmentCsvRow, 4U, &v) == 0U) || (v < 1L) || (v > 32767L)){
		return 0U;//功率
	}
	rec->laserPower = (int16_t)v;
	if(treatmentCsvFieldText(&treatmentCsvRow, 5U, tmp, (uint16_t)sizeof(tmp)) == 0U){
		return 0U;
	}
	for(i = (uint16_t)WAVE_450; i <= (uint16_t)WAVE_1470_980; i++){
		if(strcmp(tmp, treatmentLaserWaveName((LASER_WAVE_ENUM)i)) == 0){
			rec->laserWave = (LASER_WAVE_ENUM)i;
			break;
		}
	}
	if(i > (uint16_t)WAVE_1470_980){
		return 0U;//波长名称不认识
	}
	if(treatmentCsvFieldText(&treatmentCsvRow, 6U, tmp, (uint16_t)sizeof(tmp)) == 0U){
		return 0U;
	}
	for(i = (uint16_t)ePhlebology; i <= (uint16_t)eCustiom; i++){
		if(strcmp(tmp, treatmentProtocolName((PROTOCOL_ENUM)i)) == 0){
			rec->protocol = (PROTOCOL_ENUM)i;
			break;
		}
	}
	if(i > (uint16_t)eCustiom){
		return 0U;//方案名称不认识
	}
	if((treatmentCsvFieldLong(&treatmentCsvRow, 7U, &v) == 0U) || (v < 1L) || (v > 2147483647L)){
		return 0U;//能量
	}
	rec->releaseEnergy = (int32_t)v;
	if((treatmentCsvFieldLong(&treatmentCsvRow, 8U, &v) == 0U) || (v < 1L) || (v > 2147483647L)){
		return 0U;//治疗时间
	}
	rec->releaseTime = (int32_t)v;
	return 1U;
}

//挂载U盘(偶发枚举慢, 最多重试3次)
static uint8_t treatmentUsbMount(FATFS *fs){
	FRESULT fr = FR_INT_ERR;
	uint8_t retry;
	for(retry = 0U; retry < 3U; retry++){
		fr = f_mount(fs, (const TCHAR*)FATFS_ROOT, 1);
		if(fr == FR_OK){
			return 1U;
		}
		vTaskDelay(pdMS_TO_TICKS(500));
	}
	printf("%s,%d,%s:mount udisk fail,code=%d\n", __FILE__, __LINE__, __func__, (int)fr);
	return 0U;
}

//把机内全部病历写入U盘CSV(同一文件名先删后建, 覆盖旧文件)
treatmentUsbErr_t treatmentLogSaveToUdisk(uint16_t *saved){
	FIL file;
	FATFS fs;
	FRESULT fr;
	UINT bw = 0U;
	uint16_t count, outLen, i, written = 0U;

	if(saved != NULL){
		*saved = 0U;
	}
	count = treatmentEpromGetCount();
	if(count == 0U){
		return TREATMENT_USB_ERR_EMPTY;//没有病历, 不生成空文件
	}
	if(treatmentUsbMount(&fs) == 0U){
		return TREATMENT_USB_ERR_MOUNT;
	}
	fr = f_open(&file, TREATMENTLOG_FILENAME, FA_CREATE_ALWAYS | FA_WRITE);
	if(fr != FR_OK){
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		printf("%s,%d,%s:open %s fail,code=%d\n", __FILE__, __LINE__, __func__, TREATMENTLOG_FILENAME, (int)fr);
		return TREATMENT_USB_ERR_OPEN;
	}
	outLen = (uint16_t)strlen(treatmentCsvHeader);
	outLen = (uint16_t)(outLen + 2U);
	//表头: 末尾补CRLF
	memcpy(treatmentCsvLineBuf, treatmentCsvHeader, strlen(treatmentCsvHeader));
	treatmentCsvLineBuf[strlen(treatmentCsvHeader)] = '\r';
	treatmentCsvLineBuf[strlen(treatmentCsvHeader) + 1U] = '\n';
	if((f_write(&file, treatmentCsvLineBuf, outLen, &bw) != FR_OK) || (bw != outLen)){
		f_close(&file);
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		return TREATMENT_USB_ERR_IO;
	}
	for(i = 0U; i < count; i++){
		treatmentLog_t rec;
		if(treatmentEpromGet(i, &rec) != TREATMENT_EPROM_OK){
			break;//读失败: 已写入的部分保留, 返回错误
		}
		outLen = treatmentCsvBuildRow(&rec);
		if(outLen == 0U){
			f_close(&file);
			f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
			return TREATMENT_USB_ERR_FORMAT;
		}
		if((f_write(&file, treatmentCsvLineBuf, outLen, &bw) != FR_OK) || (bw != outLen)){
			f_close(&file);
			f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
			return TREATMENT_USB_ERR_IO;
		}
		written++;
	}
	f_close(&file);
	f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
	if(saved != NULL){
		*saved = written;
	}
	printf("%s,%d,%s:save %u/%u records to %s\n", __FILE__, __LINE__, __func__, written, count, TREATMENTLOG_FILENAME);
	return (written == count) ? TREATMENT_USB_OK : TREATMENT_USB_ERR_IO;
}

//读取U盘CSV覆盖机内病历: 先整份预检, 通过后才清空并写入(避免坏文件把机内数据抹掉)
treatmentUsbErr_t treatmentLogLoadFromUdisk(uint16_t *loaded){
	FIL file;
	FATFS fs;
	FRESULT fr;
	uint16_t capacity, validCount = 0U, written = 0U;
	uint16_t pass;
	treatmentLog_t rec;

	if(loaded != NULL){
		*loaded = 0U;
	}
	capacity = treatmentEpromGetCapacity();
	if(capacity == 0U){
		return TREATMENT_USB_ERR_FORMAT;
	}
	if(treatmentUsbMount(&fs) == 0U){
		return TREATMENT_USB_ERR_MOUNT;
	}
	fr = f_open(&file, TREATMENTLOG_FILENAME, FA_OPEN_EXISTING | FA_READ);
	if(fr != FR_OK){
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		printf("%s,%d,%s:open %s fail,code=%d\n", __FILE__, __LINE__, __func__, TREATMENTLOG_FILENAME, (int)fr);
		return TREATMENT_USB_ERR_OPEN;
	}

	//第一遍: 只预检, 统计可写入条数
	while(f_gets(treatmentCsvReadBuf, (int)sizeof(treatmentCsvReadBuf), &file) != NULL){
		if(treatmentCsvReadBuf[0] == '\0'){
			continue;//空行
		}
		if((treatmentCsvReadBuf[0] < '0') || (treatmentCsvReadBuf[0] > '9')){
			continue;//表头/非数据行
		}
		if(treatmentCsvParseRecord(treatmentCsvReadBuf, &rec) == 0U){
			f_close(&file);
			f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
			printf("%s,%d,%s:bad csv row\n", __FILE__, __LINE__, __func__);
			return TREATMENT_USB_ERR_FORMAT;
		}
		validCount++;
		if(validCount >= capacity){
			break;//超出区块容量: 只取前capacity条
		}
	}
	if(validCount == 0U){
		f_close(&file);
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		return TREATMENT_USB_ERR_FORMAT;//文件里没有有效病历
	}

	//预检通过: 清空区块后按索引逐条写入(索引顺序即列表顺序)
	if(treatmentEpromClear() != TREATMENT_EPROM_OK){
		f_close(&file);
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		return TREATMENT_USB_ERR_IO;
	}
	fr = f_lseek(&file, 0);
	if(fr != FR_OK){
		f_close(&file);
		f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
		return TREATMENT_USB_ERR_IO;
	}
	pass = 0U;
	while((f_gets(treatmentCsvReadBuf, (int)sizeof(treatmentCsvReadBuf), &file) != NULL) && (written < validCount)){
		if(treatmentCsvReadBuf[0] == '\0'){
			continue;
		}
		if((treatmentCsvReadBuf[0] < '0') || (treatmentCsvReadBuf[0] > '9')){
			continue;
		}
		if(treatmentCsvParseRecord(treatmentCsvReadBuf, &rec) == 0U){
			continue;//预检已保证不会到这里
		}
		if(treatmentEpromWriteAt(written, &rec) != TREATMENT_EPROM_OK){
			pass = 1U;
			break;
		}
		written++;
	}
	f_close(&file);
	f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
	if(pass != 0U){
		NVRAM0[DM_TREATMENT_NUM] = (int16_t)written;//写入中断: 数量与实际已写入条数保持一致
		return TREATMENT_USB_ERR_IO;
	}
	NVRAM0[DM_TREATMENT_NUM] = (int16_t)written;//同步有效病历数量
	if(treatmentEpromGetCount() != written){
		return TREATMENT_USB_ERR_IO;
	}
	if(loaded != NULL){
		*loaded = written;
	}
	printf("%s,%d,%s:load %u records from %s\n", __FILE__, __LINE__, __func__, written, TREATMENTLOG_FILENAME);
	return TREATMENT_USB_OK;
}

//检查U盘是否在位(1=在位): 本机U盘固定插USBFS口, 且FatFs底层也只绑定该口
// (ffconf.h: #define hUSB_Host hUsbHostFS, usbh_diskio.c 用 hUSB_Host 读写) 所以只查USBFS
uint8_t treatmentUsbDiskPresent(void){
	extern USBH_HandleTypeDef hUsbHostFS;
	USBH_ClassTypeDef *cls;
	if(hUsbHostFS.gState != HOST_CLASS){
		return 0U;//主机不在"类已激活"状态(未插入/正在枚举), U盘不可用
	}
	cls = hUsbHostFS.pActiveClass;
	if((cls == NULL) || (cls->Name == NULL)){
		return 0U;
	}
	if(strcmp(cls->Name, "MSC") != 0){//只认U盘类, 避免激光模块(CDC)等其它USB设备误判
		return 0U;
	}
	if(hUsbHostFS.pActiveClass != cls){//检查期间类被切换(拔出/重新枚举)
		return 0U;
	}
	return (USBH_MSC_UnitIsReady(&hUsbHostFS, 0) != 0U) ? 1U : 0U;//与FatFs底层判定一致
}
