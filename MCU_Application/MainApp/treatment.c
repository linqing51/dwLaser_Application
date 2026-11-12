/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "treatment.h"
#include <stddef.h>
#include <string.h>
/*****************************************************************************/
//编译期校验: RAM视图结构体必须能完整放进落盘槽位(落盘字节数由常量定义, 与此处sizeof无关)
typedef char treatmentAssertRecordFits[(sizeof(treatmentRecord_t) <= CONFIG_EPROM_TREATMENT_RECORD_BYTES) ? 1 : -1];
typedef char treatmentAssertPatientFits[(sizeof(treatmentPatient_t) <= CONFIG_EPROM_TREATMENT_PATIENT_BYTES) ? 1 : -1];
/*****************************************************************************/
treatmentLog_t treatmentLog;//本次治疗会话(待保存):患者信息 + 实时治疗参数
uint8_t treatmentLogValid = 0;//当前治疗记录有效性:任意一次激光发射后置1,上电复位/保存病历后清0
const char* treatmentProtocolName(PROTOCOL_ENUM protocol){//治疗方案名称映射
	switch(protocol){
		case ePhlebology: return "Phlebology";
		case eProctology: return "Proctology";
		case eGynecology: return "Gynecology";
		case eENT: return "ENT";
		case eNeurosurgery: return "Neurosurgery";
		case eDermatology: return "Dermatology";
		case eLiposuction: return "Liposuction";
		case eDentistry: return "Dentistry";
		case eTherapy: return "Therapy";
		default: return "Custom";
	}
}
const char* treatmentLaserWaveName(LASER_WAVE_ENUM wave){//激光波长名称映射
	switch(wave){
		case WAVE_450: return "450nm";
		case WAVE_915: return "915nm";
		case WAVE_980: return "980nm";
		case WAVE_1064: return "1064nm";
		case WAVE_1470: return "1470nm";
		case WAVE_1920: return "1920nm";
		case WAVE_635: return "635nm";
		case WAVE_1940: return "1940nm";
		case WAVE_1470_980: return "1470+980nm";
		default: return "--";
	}
}

//EPROM患者档案区块管理(定长患者块顺序存储, 块内病历紧凑存储, patientId=空块标记, 删除后块整体前移无空洞)
//存储寻址: 患者块i = START + i*PATIENT_BYTES; 块内病历r = 块起点 + OFF_RECORD + r*RECORD_BYTES
//落盘字节由本文件的小端编解码生成, 与结构体内存布局(填充/对齐/枚举宽度)完全解耦
/*****************************************************************************/
//小端编解码(落盘格式固定为小端): 显式逐字节拼装, 不依赖编译器端序与结构体布局
static void treatmentPutU16(uint8_t *p, uint16_t v){
	p[0] = (uint8_t)(v & 0xFFu);
	p[1] = (uint8_t)((v >> 8) & 0xFFu);
}
static uint16_t treatmentGetU16(const uint8_t *p){
	return (uint16_t)((uint16_t)p[0] | ((uint16_t)p[1] << 8));
}
static void treatmentPutU32(uint8_t *p, uint32_t v){
	p[0] = (uint8_t)(v & 0xFFu);
	p[1] = (uint8_t)((v >> 8) & 0xFFu);
	p[2] = (uint8_t)((v >> 16) & 0xFFu);
	p[3] = (uint8_t)((v >> 24) & 0xFFu);
}
static uint32_t treatmentGetU32(const uint8_t *p){
	return ((uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24));
}

//一条病历: RAM视图 -> 落盘字节
static void treatmentRecordToBytes(const treatmentRecord_t *rec, uint8_t *buf){
	treatmentPutU32(buf + CONFIG_EPROM_TREATMENT_REC_OFF_ENERGY, (uint32_t)rec->releaseEnergy);
	treatmentPutU32(buf + CONFIG_EPROM_TREATMENT_REC_OFF_TIME, (uint32_t)rec->releaseTime);
	treatmentPutU16(buf + CONFIG_EPROM_TREATMENT_REC_OFF_POWER, (uint16_t)rec->laserPower);
	buf[CONFIG_EPROM_TREATMENT_REC_OFF_WAVE] = rec->laserWave;
	buf[CONFIG_EPROM_TREATMENT_REC_OFF_PROTOCOL] = rec->protocol;
}

//一条病历: 落盘字节 -> RAM视图
static void treatmentRecordFromBytes(const uint8_t *buf, treatmentRecord_t *rec){
	rec->releaseEnergy = (int32_t)treatmentGetU32(buf + CONFIG_EPROM_TREATMENT_REC_OFF_ENERGY);
	rec->releaseTime = (int32_t)treatmentGetU32(buf + CONFIG_EPROM_TREATMENT_REC_OFF_TIME);
	rec->laserPower = (int16_t)treatmentGetU16(buf + CONFIG_EPROM_TREATMENT_REC_OFF_POWER);
	rec->laserWave = buf[CONFIG_EPROM_TREATMENT_REC_OFF_WAVE];
	rec->protocol = buf[CONFIG_EPROM_TREATMENT_REC_OFF_PROTOCOL];
}

//一个患者块: RAM视图 -> 落盘字节(未用字节写0)
static void treatmentPatientToBytes(const treatmentPatient_t *patient, uint8_t *buf){
	uint8_t recCount = patient->recordCount;
	if(recCount > CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT){
		recCount = CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT;//异常值钳位
	}
	memset(buf, 0, CONFIG_EPROM_TREATMENT_PATIENT_BYTES);
	memcpy(buf + CONFIG_EPROM_TREATMENT_OFF_NAME, patient->name, CONFIG_EPROM_TREATMENT_NAME_BYTES);
	treatmentPutU16(buf + CONFIG_EPROM_TREATMENT_OFF_PATIENT_ID, patient->patientId);
	buf[CONFIG_EPROM_TREATMENT_OFF_AGE] = patient->age;
	buf[CONFIG_EPROM_TREATMENT_OFF_GENDER] = patient->gender;
	buf[CONFIG_EPROM_TREATMENT_OFF_RECORD_COUNT] = recCount;
	for(uint8_t r = 0; r < CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT; r++){
		treatmentRecordToBytes(&patient->record[r], buf + CONFIG_EPROM_TREATMENT_OFF_RECORD + ((uint32_t)r * CONFIG_EPROM_TREATMENT_RECORD_BYTES));
	}
}

//一个患者块: 落盘字节 -> RAM视图(结构体先清零, 避免残留旧内容)
static void treatmentPatientFromBytes(const uint8_t *buf, treatmentPatient_t *patient){
	memset(patient, 0, sizeof(treatmentPatient_t));
	memcpy(patient->name, buf + CONFIG_EPROM_TREATMENT_OFF_NAME, CONFIG_EPROM_TREATMENT_NAME_BYTES);
	patient->name[CONFIG_EPROM_TREATMENT_NAME_BYTES - 1] = '\0';
	patient->patientId = treatmentGetU16(buf + CONFIG_EPROM_TREATMENT_OFF_PATIENT_ID);
	patient->age = buf[CONFIG_EPROM_TREATMENT_OFF_AGE];
	patient->gender = buf[CONFIG_EPROM_TREATMENT_OFF_GENDER];
	patient->recordCount = buf[CONFIG_EPROM_TREATMENT_OFF_RECORD_COUNT];
	if(patient->recordCount > CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT){
		patient->recordCount = CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT;//异常值钳位
	}
	for(uint8_t r = 0; r < patient->recordCount; r++){
		treatmentRecordFromBytes(buf + CONFIG_EPROM_TREATMENT_OFF_RECORD + ((uint32_t)r * CONFIG_EPROM_TREATMENT_RECORD_BYTES), &patient->record[r]);
	}
}
/*****************************************************************************/
//计算指定患者块在EPROM中的起始地址
static uint32_t treatmentEpromPatientAddr(uint16_t patientIndex){
	return (uint32_t)CONFIG_EPROM_TREATMENT_START + ((uint32_t)patientIndex * (uint32_t)CONFIG_EPROM_TREATMENT_PATIENT_BYTES);
}

//计算指定患者块内指定病历槽位在EPROM中的起始地址
static uint32_t treatmentEpromRecordAddr(uint16_t patientIndex, uint8_t recIndex){
	return treatmentEpromPatientAddr(patientIndex) + (uint32_t)CONFIG_EPROM_TREATMENT_OFF_RECORD + ((uint32_t)recIndex * (uint32_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES);
}

//患者块判空: 空块标记0xFFFF, 兼容整区被写成0x00的情况(把patientId=0也视为空, 患者ID最小为1)
static uint8_t treatmentEpromPatientIsEmpty(uint16_t patientId){
	return ((patientId == CONFIG_EPROM_TREATMENT_PATIENT_EMPTY) || (patientId < CONFIG_EPROM_TREATMENT_PATIENT_ID_MIN)) ? 1 : 0;
}

//只读取患者ID(2字节)
static treatmentEpromErr_t treatmentEpromReadPatientId(uint16_t patientIndex, uint16_t *outId){
	uint8_t buf[2];
	if(outId == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	if(epromRead(treatmentEpromPatientAddr(patientIndex) + (uint32_t)CONFIG_EPROM_TREATMENT_OFF_PATIENT_ID, buf, 2) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	*outId = treatmentGetU16(buf);
	return TREATMENT_EPROM_OK;
}

//读患者块头(患者信息部分, 不含病历), out其余内容不保证有效
static treatmentEpromErr_t treatmentEpromLoadPatientHeader(uint16_t patientIndex, treatmentPatient_t *out){
	uint8_t hdr[CONFIG_EPROM_TREATMENT_HEAD_BYTES];
	if((out == NULL) || (patientIndex >= treatmentEpromPatientCapacity())){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	if(epromRead(treatmentEpromPatientAddr(patientIndex), hdr, (uint16_t)CONFIG_EPROM_TREATMENT_HEAD_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	memset(out, 0, sizeof(treatmentPatient_t));
	memcpy(out->name, hdr + CONFIG_EPROM_TREATMENT_OFF_NAME, CONFIG_EPROM_TREATMENT_NAME_BYTES);
	out->name[CONFIG_EPROM_TREATMENT_NAME_BYTES - 1] = '\0';
	out->patientId = treatmentGetU16(hdr + CONFIG_EPROM_TREATMENT_OFF_PATIENT_ID);
	out->age = hdr[CONFIG_EPROM_TREATMENT_OFF_AGE];
	out->gender = hdr[CONFIG_EPROM_TREATMENT_OFF_GENDER];
	out->recordCount = hdr[CONFIG_EPROM_TREATMENT_OFF_RECORD_COUNT];
	if(treatmentEpromPatientIsEmpty(out->patientId)){
		return TREATMENT_EPROM_ERR_EMPTY;
	}
	if(out->recordCount > CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT){
		out->recordCount = CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT;//异常值钳位
	}
	return TREATMENT_EPROM_OK;
}

//把会话参数转成一条病历(电量/时间/功率/波长/方案)
void treatmentLogToRecord(const treatmentLog_t *session, treatmentRecord_t *rec){
	if((session == NULL) || (rec == NULL)){
		return;
	}
	rec->releaseEnergy = session->releaseEnergy;
	rec->releaseTime = session->releaseTime;
	rec->laserPower = session->laserPower;
	rec->laserWave = (uint8_t)session->laserWave;
	rec->protocol = (uint8_t)session->protocol;
}

uint16_t treatmentEpromPatientCapacity(void){//获取病历区可容纳患者数量(物理容量)
	return (uint16_t)CONFIG_EPROM_TREATMENT_PATIENT_MAX;
}

uint16_t treatmentEpromPatientLimit(void){//获取应用层患者人数上限(写入按此拦截, 超物理容量时钳位)
	uint16_t limit = (uint16_t)CONFIG_EPROM_TREATMENT_PATIENT_LIMIT;
	uint16_t cap = treatmentEpromPatientCapacity();
	return ((limit > cap) ? cap : limit);
}

uint8_t treatmentEpromRecordLimit(void){//获取应用层每人病历条数上限(写入按此拦截, 超槽位数时钳位)
	uint8_t limit = (uint8_t)CONFIG_EPROM_TREATMENT_RECORD_LIMIT;
	uint8_t slotMax = (uint8_t)CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT;
	return ((limit > slotMax) ? slotMax : limit);
}

uint16_t treatmentEpromPatientCount(void){//获取当前有效患者数量(紧凑存储:遇空块即止)
	uint16_t count = 0;
	uint16_t patientId;
	for(uint16_t i = 0; i < treatmentEpromPatientCapacity(); i++){
		if(treatmentEpromReadPatientId(i, &patientId) != TREATMENT_EPROM_OK){
			break;
		}
		if(treatmentEpromPatientIsEmpty(patientId)){
			break;
		}
		count++;
	}
	return count;
}

uint16_t treatmentEpromFlatRecordCount(void){//获取全部病历总条数(界面扁平浏览用)
	uint16_t total = 0;
	uint16_t patientId;
	uint8_t recCount;
	for(uint16_t i = 0; i < treatmentEpromPatientCapacity(); i++){
		if(treatmentEpromReadPatientId(i, &patientId) != TREATMENT_EPROM_OK){
			break;
		}
		if(treatmentEpromPatientIsEmpty(patientId)){
			break;
		}
		if(epromRead(treatmentEpromPatientAddr(i) + (uint32_t)CONFIG_EPROM_TREATMENT_OFF_RECORD_COUNT, &recCount, 1) != HAL_OK){
			break;
		}
		if(recCount > CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT){
			recCount = CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT;//异常值钳位
		}
		total += recCount;
	}
	return total;
}

uint16_t treatmentEpromNextPatientId(void){//生成新患者ID(现有最大ID+1)
	uint16_t maxId = 0;
	uint16_t patientId;
	for(uint16_t i = 0; i < treatmentEpromPatientCapacity(); i++){
		if(treatmentEpromReadPatientId(i, &patientId) != TREATMENT_EPROM_OK){
			break;
		}
		if(treatmentEpromPatientIsEmpty(patientId)){
			break;
		}
		if(patientId > maxId){
			maxId = patientId;
		}
	}
	if(maxId >= CONFIG_EPROM_TREATMENT_PATIENT_ID_MAX){
		return CONFIG_EPROM_TREATMENT_PATIENT_EMPTY;//ID空间用尽
	}
	return (uint16_t)(maxId + 1u);
}

treatmentEpromErr_t treatmentEpromPatientFind(uint16_t patientId, uint16_t *outPatientIndex){//按患者ID查找患者块索引
	if((outPatientIndex == NULL) || treatmentEpromPatientIsEmpty(patientId)){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	uint16_t curId;
	for(uint16_t i = 0; i < treatmentEpromPatientCapacity(); i++){
		if(treatmentEpromReadPatientId(i, &curId) != TREATMENT_EPROM_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		if(treatmentEpromPatientIsEmpty(curId)){
			break;//紧凑存储:遇空块即结束
		}
		if(curId == patientId){
			*outPatientIndex = i;
			return TREATMENT_EPROM_OK;
		}
	}
	return TREATMENT_EPROM_ERR_EMPTY;
}

uint16_t treatmentEpromPatientIdAt(uint16_t patientIndex){//只读取患者ID(不占144B栈, 无效返回0)
	uint16_t patientId = 0;
	if(patientIndex >= treatmentEpromPatientCapacity()){
		return 0;
	}
	if(treatmentEpromReadPatientId(patientIndex, &patientId) != TREATMENT_EPROM_OK){
		return 0;
	}
	if(treatmentEpromPatientIsEmpty(patientId)){
		return 0;
	}
	return patientId;
}

treatmentEpromErr_t treatmentEpromPatientGet(uint16_t patientIndex, treatmentPatient_t *out){//按患者块索引读取整个患者档案
	uint8_t blk[CONFIG_EPROM_TREATMENT_PATIENT_BYTES];
	if((out == NULL) || (patientIndex >= treatmentEpromPatientCapacity())){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	if(epromRead(treatmentEpromPatientAddr(patientIndex), blk, (uint16_t)CONFIG_EPROM_TREATMENT_PATIENT_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	treatmentPatientFromBytes(blk, out);
	if(treatmentEpromPatientIsEmpty(out->patientId)){
		return TREATMENT_EPROM_ERR_EMPTY;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromPatientAdd(const treatmentLog_t *session, uint16_t *outPatientIndex){//新建患者档案(仅患者信息, 暂无病历)
	if(session == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	uint16_t count = treatmentEpromPatientCount();
	if(count >= treatmentEpromPatientLimit()){//应用层人数上限(默认即物理容量)
		return TREATMENT_EPROM_ERR_FULL;
	}
	uint16_t patientId = treatmentEpromNextPatientId();
	if(treatmentEpromPatientIsEmpty(patientId)){
		return TREATMENT_EPROM_ERR_FULL;//ID空间用尽
	}
	treatmentPatient_t patient;
	uint8_t blk[CONFIG_EPROM_TREATMENT_PATIENT_BYTES];
	memset(&patient, 0, sizeof(patient));//整块清零: 同时覆盖该槽位残留的旧患者数据
	patient.patientId = patientId;
	patient.age = session->age;
	patient.gender = (uint8_t)session->gender;
	patient.recordCount = 0;
	memcpy(patient.name, session->name, CONFIG_EPROM_TREATMENT_NAME_BYTES);//name在会话侧已保证'\0'结尾
	patient.name[CONFIG_EPROM_TREATMENT_NAME_BYTES - 1] = '\0';
	treatmentPatientToBytes(&patient, blk);
	if(epromWrite(treatmentEpromPatientAddr(count), blk, (uint16_t)CONFIG_EPROM_TREATMENT_PATIENT_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	if(outPatientIndex != NULL){
		*outPatientIndex = count;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromPatientUpdate(uint16_t patientIndex, const treatmentPatient_t *patient){//覆盖更新患者信息(病历条数保持原值)
	uint8_t hdr[CONFIG_EPROM_TREATMENT_HEAD_BYTES];
	uint16_t curId;
	uint16_t newId;
	if((patient == NULL) || (patientIndex >= treatmentEpromPatientCapacity())){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	if(epromRead(treatmentEpromPatientAddr(patientIndex), hdr, (uint16_t)CONFIG_EPROM_TREATMENT_HEAD_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	curId = treatmentGetU16(hdr + CONFIG_EPROM_TREATMENT_OFF_PATIENT_ID);
	if(treatmentEpromPatientIsEmpty(curId)){
		return TREATMENT_EPROM_ERR_EMPTY;
	}
	newId = curId;//保留原患者ID/病历条数, 只更新患者信息
	if(!treatmentEpromPatientIsEmpty(patient->patientId)){
		newId = patient->patientId;//传入ID合规则沿用, 用于界面改ID后回写
	}
	treatmentPutU16(hdr + CONFIG_EPROM_TREATMENT_OFF_PATIENT_ID, newId);
	hdr[CONFIG_EPROM_TREATMENT_OFF_AGE] = patient->age;
	hdr[CONFIG_EPROM_TREATMENT_OFF_GENDER] = patient->gender;
	memcpy(hdr + CONFIG_EPROM_TREATMENT_OFF_NAME, patient->name, CONFIG_EPROM_TREATMENT_NAME_BYTES);
	hdr[CONFIG_EPROM_TREATMENT_OFF_NAME + CONFIG_EPROM_TREATMENT_NAME_BYTES - 1] = '\0';
	if(epromWrite(treatmentEpromPatientAddr(patientIndex), hdr, (uint16_t)CONFIG_EPROM_TREATMENT_HEAD_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromPatientDelete(uint16_t patientIndex){//删除整个患者档案(后续患者块整体前移)
	uint16_t count = treatmentEpromPatientCount();
	uint8_t blk[CONFIG_EPROM_TREATMENT_PATIENT_BYTES];
	if(patientIndex >= count){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	for(uint16_t i = patientIndex; (uint16_t)(i + 1u) < count; i++){//后续患者块逐个前移
		if(epromRead(treatmentEpromPatientAddr(i + 1u), blk, (uint16_t)CONFIG_EPROM_TREATMENT_PATIENT_BYTES) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		if(epromWrite(treatmentEpromPatientAddr(i), blk, (uint16_t)CONFIG_EPROM_TREATMENT_PATIENT_BYTES) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
	}
	//清空原末尾块(写0xFF空块标记)
	memset(blk, 0xFF, sizeof(blk));
	if(epromWrite(treatmentEpromPatientAddr((uint16_t)(count - 1u)), blk, (uint16_t)CONFIG_EPROM_TREATMENT_PATIENT_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

uint8_t treatmentEpromRecordCount(uint16_t patientIndex){//读取该患者已保存病历条数(异常返回0)
	treatmentPatient_t hdr;
	if(treatmentEpromLoadPatientHeader(patientIndex, &hdr) != TREATMENT_EPROM_OK){
		return 0;
	}
	return hdr.recordCount;
}

//回写患者块头的病历条数
static treatmentEpromErr_t treatmentEpromWriteRecordCount(uint16_t patientIndex, uint8_t recCount){
	uint8_t count = recCount;
	if(epromWrite(treatmentEpromPatientAddr(patientIndex) + (uint32_t)CONFIG_EPROM_TREATMENT_OFF_RECORD_COUNT, &count, 1) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromRecordAdd(uint16_t patientIndex, const treatmentRecord_t *rec, uint8_t *outRecIndex){//末尾追加病历
	uint8_t blk[CONFIG_EPROM_TREATMENT_RECORD_BYTES];
	treatmentPatient_t hdr;
	treatmentEpromErr_t ret;
	if(rec == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	ret = treatmentEpromLoadPatientHeader(patientIndex, &hdr);
	if(ret != TREATMENT_EPROM_OK){
		return ret;
	}
	uint8_t recLimit = treatmentEpromRecordLimit();//应用层每人条数上限(默认即块内槽位数)
	uint8_t recCount = hdr.recordCount;
	if(recCount > recLimit){
		recCount = recLimit;//异常值钳位
	}
	uint8_t slot;
#if (CONFIG_EPROM_TREATMENT_OVERWRITE_OLDEST != 0)
	if(recCount >= recLimit){//满: 整体前移覆盖最旧一条
		for(uint8_t i = 1; i < recLimit; i++){
			if(epromRead(treatmentEpromRecordAddr(patientIndex, i), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
				return TREATMENT_EPROM_ERR_IO;
			}
			if(epromWrite(treatmentEpromRecordAddr(patientIndex, (uint8_t)(i - 1u)), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
				return TREATMENT_EPROM_ERR_IO;
			}
		}
		slot = (uint8_t)(recLimit - 1u);
	}
	else{
		slot = recCount;
	}
#else
	if(recCount >= recLimit){
		return TREATMENT_EPROM_ERR_FULL;//满: 拒绝保存, 由界面提示用户先删旧病历
	}
	slot = recCount;
#endif
	treatmentRecordToBytes(rec, blk);
	if(epromWrite(treatmentEpromRecordAddr(patientIndex, slot), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	uint8_t newCount = (uint8_t)((slot + 1u > recCount) ? (slot + 1u) : recCount);
	ret = treatmentEpromWriteRecordCount(patientIndex, newCount);//先写病历再改条数: 掉电最坏情况是"多条无效病历", 不会"条数超过实际"
	if(ret != TREATMENT_EPROM_OK){
		return ret;
	}
	if(outRecIndex != NULL){
		*outRecIndex = slot;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromRecordInsert(uint16_t patientIndex, uint8_t recIndex, const treatmentRecord_t *rec, uint8_t *outRecIndex){//插入病历到指定位置(后续病历后移)
	uint8_t blk[CONFIG_EPROM_TREATMENT_RECORD_BYTES];
	treatmentPatient_t hdr;
	treatmentEpromErr_t ret;
	if(rec == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	ret = treatmentEpromLoadPatientHeader(patientIndex, &hdr);
	if(ret != TREATMENT_EPROM_OK){
		return ret;
	}
	uint8_t recLimit = treatmentEpromRecordLimit();//应用层每人条数上限
	uint8_t recCount = hdr.recordCount;
	if(recCount > recLimit){
		recCount = recLimit;
	}
	if(recIndex > recCount){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	if(recCount >= recLimit){
		return TREATMENT_EPROM_ERR_FULL;
	}
	for(uint8_t i = recCount; i > recIndex; i--){//从末尾向前逐个后移
		if(epromRead(treatmentEpromRecordAddr(patientIndex, (uint8_t)(i - 1u)), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		if(epromWrite(treatmentEpromRecordAddr(patientIndex, i), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
	}
	treatmentRecordToBytes(rec, blk);
	if(epromWrite(treatmentEpromRecordAddr(patientIndex, recIndex), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	ret = treatmentEpromWriteRecordCount(patientIndex, (uint8_t)(recCount + 1u));
	if(ret != TREATMENT_EPROM_OK){
		return ret;
	}
	if(outRecIndex != NULL){
		*outRecIndex = recIndex;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromRecordGet(uint16_t patientIndex, uint8_t recIndex, treatmentRecord_t *out){//按位置读取病历
	uint8_t blk[CONFIG_EPROM_TREATMENT_RECORD_BYTES];
	treatmentPatient_t hdr;
	treatmentEpromErr_t ret;
	if(out == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	ret = treatmentEpromLoadPatientHeader(patientIndex, &hdr);
	if(ret != TREATMENT_EPROM_OK){
		return ret;
	}
	if(recIndex >= hdr.recordCount){
		return TREATMENT_EPROM_ERR_EMPTY;
	}
	if(epromRead(treatmentEpromRecordAddr(patientIndex, recIndex), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	treatmentRecordFromBytes(blk, out);
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromRecordUpdate(uint16_t patientIndex, uint8_t recIndex, const treatmentRecord_t *rec){//覆盖更新病历
	uint8_t blk[CONFIG_EPROM_TREATMENT_RECORD_BYTES];
	treatmentPatient_t hdr;
	treatmentEpromErr_t ret;
	if(rec == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	ret = treatmentEpromLoadPatientHeader(patientIndex, &hdr);
	if(ret != TREATMENT_EPROM_OK){
		return ret;
	}
	if(recIndex >= hdr.recordCount){
		return TREATMENT_EPROM_ERR_EMPTY;
	}
	treatmentRecordToBytes(rec, blk);
	if(epromWrite(treatmentEpromRecordAddr(patientIndex, recIndex), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromRecordDelete(uint16_t patientIndex, uint8_t recIndex){//删除病历(后续病历前移, 不删患者块)
	uint8_t blk[CONFIG_EPROM_TREATMENT_RECORD_BYTES];
	treatmentPatient_t hdr;
	treatmentEpromErr_t ret;
	ret = treatmentEpromLoadPatientHeader(patientIndex, &hdr);
	if(ret != TREATMENT_EPROM_OK){
		return ret;
	}
	uint8_t recCount = hdr.recordCount;
	if(recIndex >= recCount){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	for(uint8_t i = recIndex; (uint8_t)(i + 1u) < recCount; i++){//后续病历逐个前移
		if(epromRead(treatmentEpromRecordAddr(patientIndex, (uint8_t)(i + 1u)), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		if(epromWrite(treatmentEpromRecordAddr(patientIndex, i), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
	}
	//清空原末尾病历槽位(写0xFF, 与空槽约定一致)
	memset(blk, 0xFF, sizeof(blk));
	if(epromWrite(treatmentEpromRecordAddr(patientIndex, (uint8_t)(recCount - 1u)), blk, (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_BYTES) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return treatmentEpromWriteRecordCount(patientIndex, (uint8_t)(recCount - 1u));
}

treatmentEpromErr_t treatmentEpromSaveSession(const treatmentLog_t *session, uint16_t *outPatientIndex, uint8_t *outRecIndex){//会话保存:patientId=0新建患者, 非0追加到该患者
	if(session == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	treatmentRecord_t rec;
	treatmentLogToRecord(session, &rec);
	uint16_t patientIndex = 0;
	treatmentEpromErr_t ret = TREATMENT_EPROM_ERR_EMPTY;
	if(!treatmentEpromPatientIsEmpty(session->patientId)){
		ret = treatmentEpromPatientFind(session->patientId, &patientIndex);//复诊:追加到已有患者
	}
	if(ret != TREATMENT_EPROM_OK){//新患者(或指定ID不存在):新建档案
		ret = treatmentEpromPatientAdd(session, &patientIndex);
		if(ret != TREATMENT_EPROM_OK){
			return ret;
		}
	}
	ret = treatmentEpromRecordAdd(patientIndex, &rec, outRecIndex);
	if(ret != TREATMENT_EPROM_OK){
		return ret;
	}
	if(outPatientIndex != NULL){
		*outPatientIndex = patientIndex;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromFlatLocate(uint16_t flatIndex, uint16_t *outPatientIndex, uint8_t *outRecIndex){//扁平索引定位(患者块顺序×病历顺序)
	uint16_t patientId;
	uint8_t recCount;
	uint16_t acc = 0;
	for(uint16_t i = 0; i < treatmentEpromPatientCapacity(); i++){
		if(treatmentEpromReadPatientId(i, &patientId) != TREATMENT_EPROM_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		if(treatmentEpromPatientIsEmpty(patientId)){
			break;
		}
		if(epromRead(treatmentEpromPatientAddr(i) + (uint32_t)CONFIG_EPROM_TREATMENT_OFF_RECORD_COUNT, &recCount, 1) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		if(recCount > CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT){
			recCount = CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT;
		}
		if(flatIndex < (uint16_t)(acc + recCount)){
			if(outPatientIndex != NULL){
				*outPatientIndex = i;
			}
			if(outRecIndex != NULL){
				*outRecIndex = (uint8_t)(flatIndex - acc);
			}
			return TREATMENT_EPROM_OK;
		}
		acc = (uint16_t)(acc + recCount);
	}
	return TREATMENT_EPROM_ERR_EMPTY;
}

treatmentEpromErr_t treatmentEpromClear(void){//清空整个病历区块(按32字节分块写0xFF空块标记)
	uint8_t ffBuf[32];
	memset(ffBuf, 0xFF, sizeof(ffBuf));
	uint32_t remain = (uint32_t)CONFIG_EPROM_TREATMENT_SIZE;
	uint32_t addr = (uint32_t)CONFIG_EPROM_TREATMENT_START;
	while(remain > 0){
		uint16_t len = (remain >= sizeof(ffBuf)) ? (uint16_t)sizeof(ffBuf) : (uint16_t)remain;
		if(epromWrite(addr, ffBuf, len) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		addr += len;
		remain -= len;
	}
	return TREATMENT_EPROM_OK;
}

void treatmentEpromTraverse(treatmentEpromVisitFn fn){//遍历所有有效患者档案(索引升序)
	uint8_t blk[CONFIG_EPROM_TREATMENT_PATIENT_BYTES];
	treatmentPatient_t patient;
	if(fn == NULL){
		return;
	}
	for(uint16_t i = 0; i < treatmentEpromPatientCapacity(); i++){
		if(epromRead(treatmentEpromPatientAddr(i), blk, (uint16_t)CONFIG_EPROM_TREATMENT_PATIENT_BYTES) != HAL_OK){
			break;
		}
		treatmentPatientFromBytes(blk, &patient);
		if(treatmentEpromPatientIsEmpty(patient.patientId)){
			break;//紧凑存储:遇空块即结束
		}
		fn(i, &patient);
	}
}
/*****************************************************************************/
