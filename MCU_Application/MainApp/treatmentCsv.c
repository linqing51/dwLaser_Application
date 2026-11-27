// ----------------------------------------------------------------------------
 // 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 // 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 // 请以 UTF-8 编码保存, 并在文件头保留本注释。
 // ----------------------------------------------------------------------------
#include "treatmentCsv.h"
#include <stdlib.h>//strtol
#include "FreeRTOS.h"//vTaskDelay
#include "task.h"//pdMS_TO_TICKS
#include "usbh_core.h"//USBH_HandleTypeDef
#include "usbh_msc.h"//USBH_MSC_IsReady



//***************************************************************************
//治疗记录导出/导入(U盘CSV): 文件名由TREATMENTLOG_FILENAME定义
//列顺序: id,name,gender,age,power,wave,protocol,energy,time,rtc,pulseMode,posWidth,negWidth
//id=患者ID, 导出加"AR "前缀(如"AR 0001"), 导入解析回数字; rtc=治疗时刻(YYYY-MM-DD HH:MM:SS), 未记录留空
//pulseMode=激光发射模式(CW/Pulse), posWidth/negWidth=正/负脉宽(ms), 仅脉冲模式有意义
//旧版9列(无rtc及脉冲列)/10列(仅rtc)备份仍可载入: 缺省rtc按未记录时间, 缺省脉冲列按CW处理
//文件由同一固件生成, 读出时按字符串反查波长/方案枚举, 不做多语言兼容
//***************************************************************************
#define TREATMENT_CSV_COLUMNS_MIN           9U  //旧格式最小列数(无rtc及脉冲列)
#define TREATMENT_CSV_COLUMNS_RTC           10U //含rtc的中间格式列数(脉冲列之前)
#define TREATMENT_CSV_COLUMNS            13U //当前格式列数(含rtc+脉冲模式+正负脉宽)
//导入进度三阶段边界(0-100): 预检0-30, 写入30-70, 核对70-100; 同时覆盖U盘读取与软件处理进度
#define TREATMENT_USB_PROGRESS_PRECHECK_END   30U  //预检阶段上界(读+解析, 按文件读取位置)
#define TREATMENT_USB_PROGRESS_WRITE_END      70U  //写入阶段上界(清空+写EPROM, 按已写入记录)
#define TREATMENT_USB_PROGRESS_VERIFY_END    100U  //核对阶段上界(回读+逐字段比较, 按已核对记录)
static char treatmentCsvLineBuf[512];//单行序列化缓冲
static char treatmentCsvReadBuf[256];//f_gets行缓冲
static char treatmentCsvWorkBuf[512];//解析工作缓冲
static MiniCSV_RowTypeDef treatmentCsvRow;//行结构(静态, 避免占用任务栈)
static const char treatmentCsvHeader[] = "id,name,gender,age,power,wave,protocol,energy,time,rtc,pulseMode,posWidth,negWidth";

//把一条病历组装成CSV行并序列化, 返回序列化字节数(0=失败)
static uint16_t treatmentCsvBuildRow(const treatmentLog_t *log){
  char f0[12], f1[TREATMENT_NAME_SIZE + 4], f2[8], f3[8], f4[8], f5[16], f6[16], f7[16], f8[16], f9[24];
  char f10[8], f11[8], f12[8];
  uint16_t outLen = 0U;

  sprintf(f0, "AR %04u", (unsigned int)log->id);//ID加AR前缀(EPROM内仅存数字)
  sprintf(f1, "%s", log->name);//姓名已在录入处按TREATMENT_NAME_SIZE-1截断
  sprintf(f2, "%s", (log->gender == MALE) ? "Male" : "Female");
  sprintf(f3, "%u", (unsigned int)log->age);
  sprintf(f4, "%d", (int)log->laserPower);
  sprintf(f5, "%s", treatmentLaserWaveName(log->laserWave));
  sprintf(f6, "%s", treatmentProtocolName(log->protocol));
  sprintf(f7, "%ld", (long)log->releaseEnergy);
  sprintf(f8, "%ld", (long)log->releaseTime);
  if(log->rtcYear >= 2000U){//治疗时刻: 完整4位年 + 月日时分秒
    sprintf(f9, "%04u-%02u-%02u %02u:%02u:%02u",
      (unsigned int)log->rtcYear, (unsigned int)log->rtcMonth, (unsigned int)log->rtcDay,
      (unsigned int)log->rtcHour, (unsigned int)log->rtcMinute, (unsigned int)log->rtcSecond);
  }
  else{
    f9[0] = '\0';//未记录时间: 该列留空
  }
  //脉冲模式(CW/Pulse)与正负脉宽(ms)
  sprintf(f10, "%s", (log->pulseMode == LASER_MODE_MP) ? "Pulse" : "CW");
  sprintf(f11, "%u", (unsigned int)log->posWidth);
  sprintf(f12, "%u", (unsigned int)log->negWidth);

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
  treatmentCsvRow.fields[9] = f9; treatmentCsvRow.field_len[9] = (uint16_t)strlen(f9);
  treatmentCsvRow.fields[10] = f10; treatmentCsvRow.field_len[10] = (uint16_t)strlen(f10);
  treatmentCsvRow.fields[11] = f11; treatmentCsvRow.field_len[11] = (uint16_t)strlen(f11);
  treatmentCsvRow.fields[12] = f12; treatmentCsvRow.field_len[12] = (uint16_t)strlen(f12);
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

//解析患者ID列: 支持"AR 0001"(当前格式, 带AR前缀)与纯数字(旧格式), 成功返回1
static uint8_t treatmentCsvParseId(const char *text, long *out){
  long num;
  if((text[0] == 'A') && (text[1] == 'R') && (text[2] == ' ')){
    num = strtol(text + 3, NULL, 10);
  }
  else{
    num = strtol(text, NULL, 10);
  }
  *out = num;
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
  if(treatmentCsvRow.field_count < TREATMENT_CSV_COLUMNS_MIN){
    return 0U;
  }
  memset(rec, 0, sizeof(treatmentLog_t));
  rec->pulseMode = LASER_MODE_CW;//旧备份无脉冲列时默认连续模式
  if((treatmentCsvFieldText(&treatmentCsvRow, 0U, tmp, (uint16_t)sizeof(tmp)) == 0U)
     || (treatmentCsvParseId(tmp, &v) == 0U)
     || (v < 1L) || (v > (long)PATIENT_ID_LIMIT)){
    return 0U;//患者ID须为有效编号(对齐片上PATIENT_ID_LIMIT)
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
  if((treatmentCsvFieldLong(&treatmentCsvRow, 3U, &v) == 0U) || (v < 0L) || (v > (long)PATIENT_AGE_LIMIT)){
    return 0U;//年龄(对齐片上PATIENT_AGE_LIMIT,允许0)
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
  //第10列rtc(可选): 旧备份无此列或该列为空时按"未记录时间"处理; 有值但格式非法返回失败
  if(treatmentCsvRow.field_count > TREATMENT_CSV_COLUMNS_MIN){
    if(treatmentCsvFieldText(&treatmentCsvRow, TREATMENT_CSV_COLUMNS_MIN, tmp, (uint16_t)sizeof(tmp)) != 0U){
      unsigned int ty = 0U, tmo = 0U, td = 0U, th = 0U, tmi = 0U, ts = 0U;
      if(sscanf(tmp, "%u-%u-%u %u:%u:%u", &ty, &tmo, &td, &th, &tmi, &ts) != 6){
        return 0U;
      }
      //年份用于回写治疗时刻: 限定2000-2099(片上只存两位), 月日时分秒按自然范围校验
      if((ty < 2000U) || (ty > 2099U) || (tmo < 1U) || (tmo > 12U) || (td < 1U) || (td > 31U)
         || (th > 23U) || (tmi > 59U) || (ts > 59U)){
        return 0U;
      }
      rec->rtcYear = (uint16_t)ty;
      rec->rtcMonth = (uint8_t)tmo;
      rec->rtcDay = (uint8_t)td;
      rec->rtcHour = (uint8_t)th;
      rec->rtcMinute = (uint8_t)tmi;
      rec->rtcSecond = (uint8_t)ts;
    }
  }
  //第11-13列脉冲模式/正负脉宽(可选): 旧备份无这些列时保持默认CW; 有值但非法返回失败
  if(treatmentCsvRow.field_count > TREATMENT_CSV_COLUMNS_RTC){
    if(treatmentCsvFieldText(&treatmentCsvRow, TREATMENT_CSV_COLUMNS_RTC, tmp, (uint16_t)sizeof(tmp)) == 0U){
      return 0U;
    }
    if(strcmp(tmp, "Pulse") == 0){
      rec->pulseMode = LASER_MODE_MP;
    }
    else if(strcmp(tmp, "CW") == 0){
      rec->pulseMode = LASER_MODE_CW;
    }
    else{
      return 0U;//发射模式名称不认识
    }
    if((treatmentCsvFieldLong(&treatmentCsvRow, 11U, &v) == 0U)
       || (v < 0L) || (v > 65535L)){
      return 0U;//正脉宽(ms)
    }
    rec->posWidth = (uint16_t)v;
    if((treatmentCsvFieldLong(&treatmentCsvRow, 12U, &v) == 0U)
       || (v < 0L) || (v > 65535L)){
      return 0U;//负脉宽(ms)
    }
    rec->negWidth = (uint16_t)v;
  }
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
  //开始逐条写入前确保进度为0%(进入确认页时已清零, 这里再确保一次), 经回调上报不直接调HMI
  treatmentReportProgress(0);
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
    //按已写入记录数上报进度: written/count 映射0-100, 写完最后一条到100%
    treatmentReportProgress((uint8_t)((uint32_t)written * 100U / count));
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
  uint32_t fileSize;//CSV文件总字节数(预检阶段按文件读取位置计算进度)
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
  fileSize = (uint32_t)f_size(&file);
  //开始读取前确保进度为0%(进入确认页时已清零, 这里再确保一次), 经回调上报不直接调HMI
  treatmentReportProgress(0);

  //第一遍: 只预检, 统计可写入条数
  while(f_gets(treatmentCsvReadBuf, (int)sizeof(treatmentCsvReadBuf), &file) != NULL){
    //预检阶段: 按文件读取位置(f_tell/fileSize)映射0-30%, 放在行类型判断前使每行都更新
    if(fileSize > 0U){
      treatmentReportProgress((uint8_t)((uint32_t)f_tell(&file) * TREATMENT_USB_PROGRESS_PRECHECK_END / fileSize));
    }
    if(treatmentCsvReadBuf[0] == '\0'){
      continue;//空行
    }
    if((treatmentCsvReadBuf[0] != 'A') && ((treatmentCsvReadBuf[0] < '0') || (treatmentCsvReadBuf[0] > '9'))){
      continue;//表头/非数据行(数据行以"AR "开头, 旧格式以数字开头)
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
    if((treatmentCsvReadBuf[0] != 'A') && ((treatmentCsvReadBuf[0] < '0') || (treatmentCsvReadBuf[0] > '9'))){
      continue;//与预检(528)一致: 数据行以"AR "开头, 旧格式以数字开头
    }
    if(treatmentCsvParseRecord(treatmentCsvReadBuf, &rec) == 0U){
      continue;//预检已保证不会到这里
    }
    if(treatmentEpromWriteAt(written, &rec) != TREATMENT_EPROM_OK){
      pass = 1U;
      break;
    }
    written++;
    //写入阶段: 按已写入记录数(written/validCount)映射30-70%, 与预检末尾30%衔接, 最后一条到70%
    treatmentReportProgress((uint8_t)(TREATMENT_USB_PROGRESS_PRECHECK_END
      + (uint32_t)written * (TREATMENT_USB_PROGRESS_WRITE_END - TREATMENT_USB_PROGRESS_PRECHECK_END) / validCount));
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

//两条病历是否完全相同: 比较CSV保存的全部字段(ID/姓名/性别/年龄/功率/波长/方案/能量/治疗时间/治疗时刻/脉冲模式/正负脉宽)
static uint8_t treatmentRecordEqual(const treatmentLog_t *a, const treatmentLog_t *b){
  if((a->id != b->id) || (a->age != b->age) || (a->gender != b->gender)){
    return 0U;
  }
  if((a->laserPower != b->laserPower) || (a->laserWave != b->laserWave) || (a->protocol != b->protocol)){
    return 0U;
  }
  if((a->releaseEnergy != b->releaseEnergy) || (a->releaseTime != b->releaseTime)){
    return 0U;
  }
  if((a->pulseMode != b->pulseMode) || (a->posWidth != b->posWidth) || (a->negWidth != b->negWidth)){
    return 0U;
  }
  if((a->rtcYear != b->rtcYear) || (a->rtcMonth != b->rtcMonth) || (a->rtcDay != b->rtcDay)
     || (a->rtcHour != b->rtcHour) || (a->rtcMinute != b->rtcMinute) || (a->rtcSecond != b->rtcSecond)){
    return 0U;
  }
  if(strcmp(a->name, b->name) != 0){
    return 0U;
  }
  return 1U;
}

//载入后核对: 重新读U盘CSV, 与本机当前病历按索引逐条逐字段比较; 条数与内容全部相同返回1, 任一差异/读取失败返回0
uint8_t treatmentLogVerifyUdisk(void){
  FIL file;
  FATFS fs;
  FRESULT fr;
  uint16_t localCount, i = 0U;
  uint8_t mismatch = 0U, result = 0U;
  treatmentLog_t localRec, csvRec;

  localCount = treatmentEpromGetCount();
  if(localCount == 0U){
    return 0U;
  }
  if(treatmentUsbMount(&fs) == 0U){
    return 0U;
  }
  fr = f_open(&file, TREATMENTLOG_FILENAME, FA_OPEN_EXISTING | FA_READ);
  if(fr != FR_OK){
    f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
    printf("%s,%d,%s:open %s fail,code=%d\n", __FILE__, __LINE__, __func__, TREATMENTLOG_FILENAME, (int)fr);
    return 0U;
  }
  while(f_gets(treatmentCsvReadBuf, (int)sizeof(treatmentCsvReadBuf), &file) != NULL){
    if((treatmentCsvReadBuf[0] != 'A') && ((treatmentCsvReadBuf[0] < '0') || (treatmentCsvReadBuf[0] > '9'))){
      continue;//空行/表头/非数据行(数据行以"AR "开头, 旧格式以数字开头)
    }
    //U盘行数比本机多 / 行解析失败 / 本机读取失败 / 任一字段不同: 判为不相同
    if((i >= localCount)
       || (treatmentCsvParseRecord(treatmentCsvReadBuf, &csvRec) == 0U)
       || (treatmentEpromGet(i, &localRec) != TREATMENT_EPROM_OK)
       || (treatmentRecordEqual(&localRec, &csvRec) == 0U)){
      mismatch = 1U;
      break;
    }
    i++;
    //核对阶段: 按已核对记录数(i/localCount)映射70-100%, 最后一条核对完到100%
    treatmentReportProgress((uint8_t)(TREATMENT_USB_PROGRESS_WRITE_END
      + (uint32_t)i * (TREATMENT_USB_PROGRESS_VERIFY_END - TREATMENT_USB_PROGRESS_WRITE_END) / localCount));
  }
  f_close(&file);
  f_mount(NULL, (const TCHAR*)FATFS_ROOT, 1);
  if((mismatch == 0U) && (i == localCount)){
    result = 1U;
  }
  printf("%s,%d,%s:verify %u/%u records, equal=%u\n", __FILE__, __LINE__, __func__, i, localCount, result);
  return result;
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
