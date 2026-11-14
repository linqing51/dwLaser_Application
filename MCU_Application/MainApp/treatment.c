/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "treatment.h"
#include <string.h>
/*****************************************************************************/
treatmentLog_t treatmentLog;/*患者记录全局变量(RAM)*/

/*============================================================================
 * 名称映射
 *============================================================================*/
const char* treatmentProtocolName(PROTOCOL_ENUM protocol){
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
const char* treatmentLaserWaveName(LASER_WAVE_ENUM wave){
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

/*============================================================================
 * 区块几何与持久化计数
 *============================================================================*/
#define REG_START								((uint32_t)CONFIG_EPROM_TREATMENT_START)
#define REG_END									((uint32_t)CONFIG_EPROM_TREATMENT_END)
#define REG_SIZE								((uint32_t)CONFIG_EPROM_TREATMENT_SIZE)
#define PAT_BYTES								((uint16_t)sizeof(patientRecord_t))	/*20*/
#define REC_BYTES								((uint16_t)sizeof(treatmentRecord_t))	/*16*/

/* 编译期尺寸固化: 防止结构调整后尺寸假设失效 */
_Static_assert(sizeof(patientRecord_t)==20U, "patient row 20");
_Static_assert(sizeof(treatmentRecord_t)==16U, "record row 16");

/* 患者表索引 i 地址(低端向上) */
static uint32_t PatientAddr(uint16_t i){
	return REG_START + (uint32_t)i * (uint32_t)PAT_BYTES;
}
/* 记录表索引 j 地址(高端向下) */
static uint32_t RecordAddr(uint16_t j){
	return (REG_END + 1U) - (uint32_t)(j + 1U) * (uint32_t)REC_BYTES;
}
/* 两表之间剩余空闲字节(计数下, 行已致密时准确) */
static uint32_t FreeBytesPR(uint16_t p, uint16_t r){
	return (REG_END + 1U - (uint32_t)r * REC_BYTES) - (REG_START + (uint32_t)p * PAT_BYTES);
}
/* 区间校验: 行 [addr, addr+n-1] 必须完全落在病历区块内 */
static uint8_t InRegion(uint32_t addr, uint16_t n){
	return (addr >= REG_START) && (addr <= REG_END) &&
	       ((uint32_t)addr + (uint32_t)n <= REG_END + 1U);
}

/* ---- 持久化计数原始访问(DM 为 int16, 空白 FRAM 为 0xFFFF) ---- */
static int16_t RawAt(uint16_t idx){ return NVRAM0[idx]; }
static void SetAt(uint16_t idx, uint16_t v){ NVRAM0[idx] = (int16_t)v; }

/*============================================================================
 * 恢复用位图(单一 8KB, 患者/记录阶段复用; 仅开机恢复时使用)
 *============================================================================*/
static uint8_t g_bmp[8192];
static void BmpClear(void){ memset(g_bmp, 0, sizeof(g_bmp)); }
static uint8_t BmpTest(uint32_t bit){
	return (g_bmp[bit >> 3] & (uint8_t)(1UL << (bit & 7UL))) ? 1U : 0U;
}
static void BmpSet(uint32_t bit){
	g_bmp[bit >> 3] |= (uint8_t)(1UL << (bit & 7UL));
}

/*============================================================================
 * 开机恢复状态与行有效性
 *============================================================================*/
static uint8_t  g_ready = 0U;
static uint16_t g_nextRecSeq = 1U;

static uint8_t NameHasNul(const char *name, uint8_t len){
	for(uint8_t i = 0U; i < len; i++){ if(name[i] == '\0'){ return 1U; } }
	return 0U;
}
/* 患者行: id 为提交点(0xFFFF=空白), 其余字段须落在合法范围 */
static uint8_t PatientRowValid(const patientRecord_t *r){
	return (r->id != 0U) && (r->id != CONFIG_EPROM_TREATMENT_SLOT_EMPTY) &&
	       (r->id <= PATIENT_ID_LIMIT) &&
	       ((r->gender == (uint8_t)MALE) || (r->gender == (uint8_t)FEMALE)) &&
	       (r->age <= PATIENT_AGE_LIMIT) &&
	       (NameHasNul(r->name, (uint8_t)sizeof(r->name)) != 0U);
}
/* 记录行内容: 外键/序列非空, 波/协议 nibble 在范围 */
static uint8_t RecordContentValid(const treatmentRecord_t *r){
	uint8_t wave = (uint8_t)((r->waveProto >> 4) & 0x0FU);
	uint8_t proto = (uint8_t)(r->waveProto & 0x0FU);
	return (r->patientId != 0U) && (r->patientId != CONFIG_EPROM_TREATMENT_SLOT_EMPTY) &&
	       (r->recSeq != 0U) && (r->recSeq != CONFIG_EPROM_TREATMENT_SLOT_EMPTY) &&
	       (wave >= (uint8_t)WAVE_450) && (wave <= (uint8_t)WAVE_1470_980) &&
	       (proto <= (uint8_t)eCustiom);
}

/*============================================================================
 * 行级读写(带区间校验)
 *============================================================================*/
static treatmentEpromErr_t RowRead(uint32_t addr, void *dst, uint16_t n){
	if(!InRegion(addr, n)){ return TREATMENT_EPROM_ERR_PARAM; }
	return (epromRead(addr, (uint8_t*)dst, n) == HAL_OK)
	       ? TREATMENT_EPROM_OK : TREATMENT_EPROM_ERR_IO;
}
static treatmentEpromErr_t RowWrite(uint32_t addr, const void *src, uint16_t n){
	if(!InRegion(addr, n)){ return TREATMENT_EPROM_ERR_PARAM; }
	return (epromWrite(addr, (uint8_t*)src, n) == HAL_OK)
	       ? TREATMENT_EPROM_OK : TREATMENT_EPROM_ERR_IO;
}
static void EraseRow(uint32_t addr, uint16_t n){
	uint8_t blank[32];
	memset(blank, 0xFF, sizeof(blank));
	while(n > 0U){
		uint16_t chunk = (n > (uint16_t)sizeof(blank)) ? (uint16_t)sizeof(blank) : n;
		(void)RowWrite(addr, blank, chunk);
		addr += chunk; n = (uint16_t)(n - chunk);
	}
}

/*============================================================================
 * 安全移动(目标为空洞; 先在目标提交, 再清除源; 掉电产生的重复由恢复去重)
 *============================================================================*/
/* 患者移动: 先写正文(目标 id 保持 0xFFFF), 再写 id 提交, 最后擦源 */
static void PatientMove(const patientRecord_t *row, uint16_t src, uint16_t dst){
	uint32_t d = PatientAddr(dst);
	(void)RowWrite(d + 2U, &row->age, (uint16_t)(PAT_BYTES - 2U));/*正文18B*/
	(void)RowWrite(d, &row->id, 2U);/*提交点*/
	EraseRow(PatientAddr(src), PAT_BYTES);
}
/* 记录移动: 目标先写 PENDING, 再翻 COMMIT, 最后擦源 */
static void RecordMove(const treatmentRecord_t *row, uint16_t src, uint16_t dst){
	treatmentRecord_t out = *row;
	uint32_t d = RecordAddr(dst);
	uint8_t commit = ROW_MAGIC_COMMIT;
	out.magic = ROW_MAGIC_PENDING;
	(void)RowWrite(d, &out, REC_BYTES);
	(void)RowWrite(d + 7U, &commit, 1U);/*提交点*/
	EraseRow(RecordAddr(src), REC_BYTES);
}

/*============================================================================
 * 开机权威扫描恢复 (Recovery)
 *   容忍 0xFF(空白 FRAM) 与 0x00(clearEprom) 两种空白态;
 *   分类 blank/pending/commit/tomb, 去重、外键完整性、回收孤儿, 重建计数。
 *============================================================================*/
static void Recovery(void){
	uint16_t wp = 0U, wr = 0U, maxId = 0U;
	uint32_t maxSeq = 0UL;
	uint32_t patMax = REG_SIZE / PAT_BYTES;
	uint32_t recMax = REG_SIZE / REC_BYTES;

	if(g_ready != 0U){ return; }

	/* ---- Phase 1: 患者表 校验/去重/致密 ---- */
	BmpClear();
	for(uint32_t s32 = 0U; s32 < patMax; s32++){
		uint16_t s = (uint16_t)s32;
		patientRecord_t row;
		if(RowRead(PatientAddr(s), &row, PAT_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if(PatientRowValid(&row) == 0U){ EraseRow(PatientAddr(s), PAT_BYTES); continue; }
		if(BmpTest(row.id) != 0U){ EraseRow(PatientAddr(s), PAT_BYTES); continue; }/*重复 id*/
		BmpSet(row.id);
		if(row.id > maxId){ maxId = row.id; }
		if(s != wp){ PatientMove(&row, s, wp); }
		wp++;
	}

	/* ---- Phase 2a: 外键孤儿(患者不存在)的已提交记录 -> 墓碑; 位图仍为患者 id ---- */
	for(uint32_t s32 = 0U; s32 < recMax; s32++){
		uint16_t s = (uint16_t)s32;
		treatmentRecord_t row;
		uint8_t tomb = ROW_MAGIC_TOMB;
		if(RowRead(RecordAddr(s), &row, REC_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if((row.magic == ROW_MAGIC_COMMIT) && (BmpTest(row.patientId) == 0U)){
			(void)RowWrite(RecordAddr(s) + 7U, &tomb, 1U);
		}
	}

	/* ---- Phase 2b: 记录表 校验/去重/致密 ---- */
	BmpClear();
	for(uint32_t s32 = 0U; s32 < recMax; s32++){
		uint16_t s = (uint16_t)s32;
		treatmentRecord_t row;
		if(RowRead(RecordAddr(s), &row, REC_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if(row.magic != ROW_MAGIC_COMMIT){ EraseRow(RecordAddr(s), REC_BYTES); continue; }
		if(RecordContentValid(&row) == 0U){ EraseRow(RecordAddr(s), REC_BYTES); continue; }
		if(BmpTest(row.recSeq) != 0U){ EraseRow(RecordAddr(s), REC_BYTES); continue; }/*重复序列*/
		BmpSet(row.recSeq);
		if(row.recSeq > maxSeq){ maxSeq = row.recSeq; }
		if(s != wr){ RecordMove(&row, s, wr); }
		wr++;
	}

	/* 记录序列游标: 扫描最大值 +1, 受 u16 上限钳制 */
	g_nextRecSeq = (maxSeq >= RECORD_SEQ_LIMIT) ? RECORD_SEQ_LIMIT : (uint16_t)(maxSeq + 1U);

	SetAt(DM_TREATMENT_PATIENT_NUM, wp);
	SetAt(DM_TREATMENT_NUM, wr);
	SetAt(DM_TREATMENT_NEXT_ID, (maxId >= PATIENT_ID_LIMIT) ? PATIENT_ID_LIMIT : (uint16_t)(maxId + 1U));
	g_ready = 1U;
}

/* 运行时致密(开机恢复后无重复; 自身移动即时清源, 故无需位图) */
static uint16_t CompactPatients(void){
	uint16_t w = 0U;
	uint32_t patMax = REG_SIZE / PAT_BYTES;
	for(uint32_t s32 = 0U; s32 < patMax; s32++){
		uint16_t s = (uint16_t)s32;
		patientRecord_t row;
		if(RowRead(PatientAddr(s), &row, PAT_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if(PatientRowValid(&row) != 0U){
			if(s != w){ PatientMove(&row, s, w); }
			w++;
		}
		else { EraseRow(PatientAddr(s), PAT_BYTES); }
	}
	SetAt(DM_TREATMENT_PATIENT_NUM, w);
	return w;
}
static uint16_t CompactRecords(void){
	uint16_t w = 0U;
	uint32_t recMax = REG_SIZE / REC_BYTES;
	for(uint32_t s32 = 0U; s32 < recMax; s32++){
		uint16_t s = (uint16_t)s32;
		treatmentRecord_t row;
		if(RowRead(RecordAddr(s), &row, REC_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if((row.magic == ROW_MAGIC_COMMIT) && (RecordContentValid(&row) != 0U)){
			if(s != w){ RecordMove(&row, s, w); }
			w++;
		}
		else { EraseRow(RecordAddr(s), REC_BYTES); }
	}
	SetAt(DM_TREATMENT_NUM, w);
	return w;
}

static uint16_t CntP(void){ Recovery(); return (uint16_t)RawAt(DM_TREATMENT_PATIENT_NUM); }
static uint16_t CntR(void){ Recovery(); return (uint16_t)RawAt(DM_TREATMENT_NUM); }
static uint16_t CntNext(void){ Recovery(); return (uint16_t)RawAt(DM_TREATMENT_NEXT_ID); }

/*============================================================================
 * 原子替换(更新): 新槽位两阶段提交 -> 旧行墓碑/空白 -> 致密
 *   掉电时旧行始终保留到新行提交之后; 撕裂/重复由 Recovery 按稳定 id/recSeq 去重。
 *   需一个空闲槽位; 满盘(无空闲)返回 ERR_FULL, 先删除再更新。
 *============================================================================*/
/* 记录替换: 新槽 PENDING->COMMIT(保留原 recSeq), 再旧槽 TOMB, 再致密 */
static treatmentEpromErr_t RecordReplaceAt(uint16_t index, const treatmentRecord_t *in){
	uint16_t r;
	treatmentRecord_t old, row;
	uint8_t commit = ROW_MAGIC_COMMIT, tomb = ROW_MAGIC_TOMB;
	treatmentEpromErr_t e;
	if(in == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	r = CntR();
	if(index >= r){ return TREATMENT_EPROM_ERR_PARAM; }
	if(FreeBytesPR(CntP(), r) < REC_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
	e = RowRead(RecordAddr(index), &old, REC_BYTES);
	if(e != TREATMENT_EPROM_OK){ return e; }
	row = *in;
	row.patientId = old.patientId;/*外键不可改*/
	row.recSeq = old.recSeq;/*稳定序列不可改*/
	row.magic = ROW_MAGIC_PENDING;
	if(RowWrite(RecordAddr(r), &row, REC_BYTES) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	if(RowWrite(RecordAddr(r) + 7U, &commit, 1U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	if(RowWrite(RecordAddr(index) + 7U, &tomb, 1U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	(void)CompactRecords();
	return TREATMENT_EPROM_OK;
}

/* 患者替换: 新槽先写正文再写 id(保留原 id), 再旧槽 id 写 0xFFFF, 再致密 */
static treatmentEpromErr_t PatientReplaceAt(uint16_t index, const patientRecord_t *in){
	uint16_t p;
	patientRecord_t old, row;
	uint16_t blank = CONFIG_EPROM_TREATMENT_SLOT_EMPTY;
	treatmentEpromErr_t e;
	if(in == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	p = CntP();
	if(index >= p){ return TREATMENT_EPROM_ERR_PARAM; }
	if(FreeBytesPR(p, CntR()) < PAT_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
	e = RowRead(PatientAddr(index), &old, PAT_BYTES);
	if(e != TREATMENT_EPROM_OK){ return e; }
	row = *in;
	row.id = old.id;/*稳定 id 不可改*/
	if(RowWrite(PatientAddr(p) + 2U, &row.age, (uint16_t)(PAT_BYTES - 2U)) != TREATMENT_EPROM_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	if(RowWrite(PatientAddr(p), &row.id, 2U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	if(RowWrite(PatientAddr(index), &blank, 2U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	(void)CompactPatients();
	return TREATMENT_EPROM_OK;
}

/*============================================================================
 * 一级 API: 患者
 *============================================================================*/
uint16_t treatmentGetNextPatientId(void){ return CntNext(); }
uint16_t treatmentGetPatientCount(void){ return CntP(); }
uint16_t treatmentGetRecordCount(void){ return CntR(); }

uint32_t treatmentGetFreeBytes(void){
	return FreeBytesPR(CntP(), CntR());
}

treatmentEpromErr_t treatmentPatientFind(uint16_t pid, uint16_t *indexOut){
	uint16_t p = CntP();
	patientRecord_t row;
	for(uint16_t i = 0U; i < p; i++){
		if(RowRead(PatientAddr(i), &row, PAT_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if(row.id == pid){
			if(indexOut != NULL){ *indexOut = i; }
			return TREATMENT_EPROM_OK;
		}
	}
	return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND;
}

treatmentEpromErr_t treatmentPatientGetByIndex(uint16_t index, patientRecord_t *out){
	if(out == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	if(index >= CntP()){ return TREATMENT_EPROM_ERR_PARAM; }
	return RowRead(PatientAddr(index), out, PAT_BYTES);
}

/* 新建患者(两阶段: 先写正文, id 最后提交) */
treatmentEpromErr_t treatmentPatientCreate(const patientRecord_t *in, uint16_t *newId){
	uint16_t p, r, id;
	patientRecord_t row;
	if(in == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	p = CntP(); r = CntR();
	if(FreeBytesPR(p, r) < PAT_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
	id = CntNext();
	if((id == 0U) || (id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY) || (id > PATIENT_ID_LIMIT)){
		return TREATMENT_EPROM_ERR_FULL;
	}
	row = *in; row.id = id;
	(void)RowWrite(PatientAddr(p) + 2U, &row.age, (uint16_t)(PAT_BYTES - 2U));/*正文*/
	if(RowWrite(PatientAddr(p), &row.id, 2U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	SetAt(DM_TREATMENT_PATIENT_NUM, (uint16_t)(p + 1U));
	SetAt(DM_TREATMENT_NEXT_ID, (uint16_t)(id + 1U));
	if(newId != NULL){ *newId = id; }
	return TREATMENT_EPROM_OK;
}

/* 内部: 以指定 id 确保患者存在(供 CSV 等带外键来源); 已存在则返回表索引 */
static treatmentEpromErr_t EnsurePatientWithId(uint16_t id, const patientRecord_t *tpl, uint16_t *indexOut){
	uint16_t found;
	treatmentEpromErr_t fe = treatmentPatientFind(id, &found);
	if(fe == TREATMENT_EPROM_OK){
		if(indexOut != NULL){ *indexOut = found; }
		return TREATMENT_EPROM_OK;
	}
	{
		uint16_t p = CntP(), r = CntR();
		patientRecord_t row;
		if((id == 0U) || (id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY) || (id > PATIENT_ID_LIMIT)){
			return TREATMENT_EPROM_ERR_PARAM;
		}
		if(FreeBytesPR(p, r) < PAT_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
		row = (tpl != NULL) ? *tpl : (patientRecord_t){0};
		row.id = id;
		(void)RowWrite(PatientAddr(p) + 2U, &row.age, (uint16_t)(PAT_BYTES - 2U));
		if(RowWrite(PatientAddr(p), &row.id, 2U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
		SetAt(DM_TREATMENT_PATIENT_NUM, (uint16_t)(p + 1U));
		if((uint16_t)(id + 1U) > CntNext()){ SetAt(DM_TREATMENT_NEXT_ID, (uint16_t)(id + 1U)); }
		if(indexOut != NULL){ *indexOut = p; }
	}
	return TREATMENT_EPROM_OK;
}

/* 删除患者: 先墓碑其全部记录并致密, 再空白其 id 并致密患者表(级联) */
treatmentEpromErr_t treatmentPatientDelete(uint16_t pid){
	uint16_t pi;
	uint32_t recMax;
	treatmentEpromErr_t fe;

	fe = treatmentPatientFind(pid, &pi);
	if(fe != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND; }

	/* 级联: 墓碑该患者全部记录(单字节原子), 再致密 */
	recMax = REG_SIZE / REC_BYTES;
	for(uint32_t s32 = 0U; s32 < recMax; s32++){
		uint16_t s = (uint16_t)s32;
		treatmentRecord_t row;
		uint8_t tomb = ROW_MAGIC_TOMB;
		if(RowRead(RecordAddr(s), &row, REC_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if((row.patientId == pid) && (row.magic == ROW_MAGIC_COMMIT)){
			(void)RowWrite(RecordAddr(s) + 7U, &tomb, 1U);
		}
	}
	(void)CompactRecords();

	/* 空白患者 id(逻辑删除点), 再致密患者表 */
	{
		uint16_t blank = CONFIG_EPROM_TREATMENT_SLOT_EMPTY;
		(void)RowWrite(PatientAddr(pi), &blank, 2U);
	}
	(void)CompactPatients();
	return TREATMENT_EPROM_OK;
}

/*============================================================================
 * 一级 API: 记录
 *============================================================================*/
uint16_t treatmentGetRecordCountForPatient(uint16_t pid){
	uint16_t r = CntR();
	uint16_t cnt = 0U;
	treatmentRecord_t rec;
	for(uint16_t i = 0U; i < r; i++){
		if(RowRead(RecordAddr(i), &rec, REC_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if(rec.patientId == pid){ cnt++; }
	}
	return cnt;
}

/* 追加记录(两阶段: 先 PENDING, 再翻 COMMIT) */
treatmentEpromErr_t treatmentRecordAdd(const treatmentRecord_t *in){
	uint16_t p, r;
	treatmentEpromErr_t fe;
	treatmentRecord_t row;
	uint8_t commit;
	if(in == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	fe = treatmentPatientFind(in->patientId, NULL);
	if(fe != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND; }
#if (CONFIG_EPROM_TREATMENT_RECORD_MAX_PER_PATIENT > 0)
	if(treatmentGetRecordCountForPatient(in->patientId) >=
	   (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_MAX_PER_PATIENT){
		return TREATMENT_EPROM_ERR_PATIENT_FULL;
	}
#endif
	p = CntP(); r = CntR();
	if(FreeBytesPR(p, r) < REC_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
	if((g_nextRecSeq == 0U) || (g_nextRecSeq > RECORD_SEQ_LIMIT)){ return TREATMENT_EPROM_ERR_FULL; }
	row = *in;
	row.recSeq = g_nextRecSeq;
	row.magic = ROW_MAGIC_PENDING;
	if(RowWrite(RecordAddr(r), &row, REC_BYTES) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	commit = ROW_MAGIC_COMMIT;
	if(RowWrite(RecordAddr(r) + 7U, &commit, 1U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	SetAt(DM_TREATMENT_NUM, (uint16_t)(r + 1U));
	g_nextRecSeq++;
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentRecordGetByIndex(uint16_t index, treatmentRecord_t *out){
	if(out == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	if(index >= CntR()){ return TREATMENT_EPROM_ERR_PARAM; }
	return RowRead(RecordAddr(index), out, REC_BYTES);
}

/* 删除单条: 墓碑(原子)后致密 */
treatmentEpromErr_t treatmentRecordDeleteByIndex(uint16_t index){
	uint8_t tomb;
	if(index >= CntR()){ return TREATMENT_EPROM_ERR_PARAM; }
	tomb = ROW_MAGIC_TOMB;
	if(RowWrite(RecordAddr(index) + 7U, &tomb, 1U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	(void)CompactRecords();
	return TREATMENT_EPROM_OK;
}

/* 更新记录: 新槽两阶段 + 旧行墓碑(非原地覆盖), 保留外键/稳定序列 */
treatmentEpromErr_t treatmentRecordUpdateByIndex(uint16_t index, const treatmentRecord_t *in){
	return RecordReplaceAt(index, in);
}

/*============================================================================
 * split / join: 复合视图 <-> 片上结构
 *============================================================================*/
static void JoinLog(const treatmentRecord_t *rec, const patientRecord_t *pat, treatmentLog_t *out){
	memset(out, 0, sizeof(*out));
	out->id = pat->id;
	out->age = pat->age;
	out->gender = (GENDER_ENUM)pat->gender;
	(void)memcpy(out->name, pat->name, sizeof(out->name));
	out->name[sizeof(out->name) - 1U] = '\0';
	out->laserPower = rec->laserPower;
	out->laserWave = (LASER_WAVE_ENUM)((rec->waveProto >> 4) & 0x0FU);
	out->protocol = (PROTOCOL_ENUM)(rec->waveProto & 0x0FU);
	out->releaseEnergy = rec->releaseEnergy;
	out->releaseTime = rec->releaseTime;
}
static void SplitPatient(const treatmentLog_t *log, patientRecord_t *pat){
	memset(pat, 0, sizeof(*pat));
	pat->id = log->id;
	pat->age = log->age;
	pat->gender = (uint8_t)log->gender;
	(void)memset(pat->name, 0xFF, sizeof(pat->name));
	(void)memcpy(pat->name, log->name, sizeof(pat->name));
	pat->name[sizeof(pat->name) - 1U] = '\0';
}
static void SplitRecord(const treatmentLog_t *log, treatmentRecord_t *rec){
	memset(rec, 0, sizeof(*rec));
	rec->patientId = log->id;
	rec->laserPower = log->laserPower;
	rec->releaseEnergy = log->releaseEnergy;
	rec->releaseTime = log->releaseTime;
	rec->waveProto = (uint8_t)(((uint8_t)log->laserWave << 4) | ((uint8_t)log->protocol & 0x0FU));
	rec->magic = ROW_MAGIC_PENDING;
}

/*============================================================================
 * 扁平复合视图 API
 *============================================================================*/
uint16_t treatmentEpromGetCapacity(void){
	Recovery();
	return (uint16_t)(REG_SIZE / REC_BYTES);/*全为记录时的理论上限*/
}
uint16_t treatmentEpromGetCount(void){ return CntR(); }
uint16_t treatmentEpromGetPatientCount(void){ return CntP(); }
uint16_t treatmentEpromGetPatientRecordCount(uint16_t patientId){
	return treatmentGetRecordCountForPatient(patientId);
}

treatmentEpromErr_t treatmentEpromGet(uint16_t index, treatmentLog_t *out){
	treatmentRecord_t rec;
	uint16_t pi;
	treatmentEpromErr_t e;
	if(out == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	if(index >= CntR()){ return TREATMENT_EPROM_ERR_PARAM; }
	e = RowRead(RecordAddr(index), &rec, REC_BYTES);
	if(e != TREATMENT_EPROM_OK){ return e; }
	e = treatmentPatientFind(rec.patientId, &pi);
	if(e != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND; }
	{
		patientRecord_t pat;
		e = RowRead(PatientAddr(pi), &pat, PAT_BYTES);
		if(e != TREATMENT_EPROM_OK){ return e; }
		JoinLog(&rec, &pat, out);
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromAdd(const treatmentLog_t *log){
	uint16_t pid;
	if(log == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	pid = log->id;
	if((pid == 0U) || (treatmentPatientFind(pid, NULL) != TREATMENT_EPROM_OK)){
		/*新患者: 自动建患者并分配新 id*/
		patientRecord_t pat;
		treatmentEpromErr_t ce;
		SplitPatient(log, &pat);
		ce = treatmentPatientCreate(&pat, &pid);
		if(ce != TREATMENT_EPROM_OK){ return ce; }
	}
	{
		treatmentRecord_t rec;
		SplitRecord(log, &rec);
		rec.patientId = pid;
		return treatmentRecordAdd(&rec);
	}
}

treatmentEpromErr_t treatmentEpromAddToPatient(uint16_t patientId, const treatmentLog_t *log){
	treatmentEpromErr_t fe;
	treatmentRecord_t rec;
	if(log == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	fe = treatmentPatientFind(patientId, NULL);
	if(fe != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND; }
	SplitRecord(log, &rec);
	rec.patientId = patientId;
	return treatmentRecordAdd(&rec);
}

/* 批量写: 顺序追加(索引==当前记录数)时确保患者存在再落记录; 已存在索引则覆盖 */
treatmentEpromErr_t treatmentEpromWriteAt(uint16_t index, const treatmentLog_t *log){
	uint16_t r;
	if(log == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	r = CntR();
	if(index > r){ return TREATMENT_EPROM_ERR_PARAM; }
	if(index == r){
		/*追加路径: 带外键确保患者(同 id 复用, 新 id 建患者), 再追加记录*/
		patientRecord_t pat;
		treatmentRecord_t rec;
		treatmentEpromErr_t e;
		uint16_t pid = log->id;
		if(pid == 0U){ pid = CntNext(); }
		SplitPatient(log, &pat); pat.id = pid;
		e = EnsurePatientWithId(pid, &pat, NULL);
		if(e != TREATMENT_EPROM_OK){ return e; }
		SplitRecord(log, &rec); rec.patientId = pid;
		return treatmentRecordAdd(&rec);
	}
	/*覆盖已有索引: 记录与患者均走"新槽两阶段+旧行墓碑"(非原地覆盖)*/
	{
		treatmentRecord_t oldRec, newRec;
		patientRecord_t newPat;
		uint16_t pi;
		treatmentEpromErr_t e;
		e = RowRead(RecordAddr(index), &oldRec, REC_BYTES);
		if(e != TREATMENT_EPROM_OK){ return e; }
		e = treatmentPatientFind(oldRec.patientId, &pi);
		if(e != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND; }
		SplitRecord(log, &newRec);
		e = RecordReplaceAt(index, &newRec);
		if(e != TREATMENT_EPROM_OK){ return e; }
		SplitPatient(log, &newPat);
		return PatientReplaceAt(pi, &newPat);
	}
}

treatmentEpromErr_t treatmentEpromSaveCurrent(void){
	return treatmentEpromAdd(&treatmentLog);
}

/* 归一化记录按插入顺序排列, 不保留任意位置插入; 映射为末尾追加 */
treatmentEpromErr_t treatmentEpromInsert(uint16_t index, const treatmentLog_t *log){
	(void)index;
	return treatmentEpromAdd(log);
}

treatmentEpromErr_t treatmentEpromDelete(uint16_t index){
	return treatmentRecordDeleteByIndex(index);
}

treatmentEpromErr_t treatmentEpromUpdate(uint16_t index, const treatmentLog_t *log){
	treatmentRecord_t oldRec, newRec;
	patientRecord_t newPat;
	uint16_t pi;
	treatmentEpromErr_t e;
	if(log == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	if(index >= CntR()){ return TREATMENT_EPROM_ERR_PARAM; }
	e = RowRead(RecordAddr(index), &oldRec, REC_BYTES);
	if(e != TREATMENT_EPROM_OK){ return e; }
	e = treatmentPatientFind(oldRec.patientId, &pi);
	if(e != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND; }
	SplitRecord(log, &newRec);
	e = RecordReplaceAt(index, &newRec);
	if(e != TREATMENT_EPROM_OK){ return e; }
	SplitPatient(log, &newPat);
	return PatientReplaceAt(pi, &newPat);
}

treatmentEpromErr_t treatmentEpromClear(void){
	uint32_t addr = REG_START;
	uint8_t blank[64];
	memset(blank, 0xFF, sizeof(blank));
	while(addr <= REG_END){
		uint16_t chunk = ((REG_END + 1U - addr) > sizeof(blank))
		                 ? (uint16_t)sizeof(blank) : (uint16_t)(REG_END + 1U - addr);
		if(epromWrite(addr, blank, chunk) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;/*失败保留原计数*/
		}
		addr += chunk;
	}
	SetAt(DM_TREATMENT_PATIENT_NUM, 0U);
	SetAt(DM_TREATMENT_NUM, 0U);
	SetAt(DM_TREATMENT_NEXT_ID, 0U);
	g_nextRecSeq = 1U;
	return TREATMENT_EPROM_OK;
}

uint32_t treatmentEpromCalcFwCrc(void){
	uint32_t crc32;
	crc32Clear();
	for(uint32_t addr = APPLICATION_FLASH_START_ADDRESS; addr < APPLICATION_FLASH_END_ADDRESS; addr++){
		crc32 = crc32CalculateAdd(*(__IO uint8_t*)addr);
	}
	return crc32;
}

void treatmentEpromTraverse(treatmentEpromVisitFn fn){
	uint16_t r;
	if(fn == NULL){ return; }
	r = CntR();
	for(uint16_t i = 0U; i < r; i++){
		treatmentLog_t tmp;
		if(treatmentEpromGet(i, &tmp) != TREATMENT_EPROM_OK){ break; }
		fn(i, &tmp);
	}
}

/*============================================================================
 * 虚拟病历生成(测试数据填充)
 *============================================================================*/
typedef struct{
	PROTOCOL_ENUM protocol;
	uint8_t weight;
	uint8_t ageMin;
	uint8_t ageMax;
	uint8_t femaleRate;
	int16_t powerMin;
	int16_t powerMax;
	uint16_t timeMin;
	uint16_t timeMax;
	uint8_t duty;
}demoProfile_t;

static const demoProfile_t demoProfileTable[] = {
	{ePhlebology,   30, 28, 78,  55,  6, 13,  120,  600, 100},
	{eProctology,   12, 22, 80,  45,  8, 15,   60,  360,  60},
	{eGynecology,   12, 20, 58, 100,  4, 10,   60,  420,  75},
	{eENT,           8,  5, 70,  50,  3,  8,   30,  180,  50},
	{eNeurosurgery,  2, 18, 72,  50,  2,  6,   60,  300,  40},
	{eDermatology,  14, 14, 68,  65,  1,  8,   30,  300,  50},
	{eLiposuction,   8, 22, 55,  80,  8, 15,  300, 1200, 100},
	{eDentistry,     6,  8, 75,  55,  1,  4,   20,  120,  30},
	{eTherapy,       8, 18, 78,  50,  2, 10,   60,  600,  60}
};
#define DEMO_PROFILE_NUM								(sizeof(demoProfileTable) / sizeof(demoProfile_t))
#define DEMO_PROFILE_WEIGHT_TOTAL						100

static const char *const demoSurnamePool[] = {
	"ZHANG", "WANG", "LI", "ZHAO", "LIU", "CHEN", "YANG", "HUANG", "ZHOU", "WU",
	"XU", "SUN", "MA", "ZHU", "HU", "GUO", "HE", "GAO", "LIN", "LUO",
	"ZHENG", "LIANG", "XIE", "SONG", "TANG", "HAN", "FENG", "DENG", "CAO", "PENG"
};
static const char *const demoGivenMalePool[] = {
	"WEI", "QIANG", "LEI", "JUN", "TAO", "MING", "BIN", "CHAO", "HONG", "GANG",
	"KAI", "HAI", "YONG", "JIAN", "ZHI", "FENG", "PENG", "HAO", "SHENG", "BO"
};
static const char *const demoGivenFemalePool[] = {
	"MIN", "JING", "YAN", "PING", "HUI", "NA", "FANG", "XIN", "LAN", "XUE",
	"RUI", "TING", "YI", "QING", "SHAN", "LING", "NING", "MEI", "JIE", "QIAN"
};
#define DEMO_SURNAME_NUM								(sizeof(demoSurnamePool)/sizeof(demoSurnamePool[0]))
#define DEMO_GIVEN_MALE_NUM								(sizeof(demoGivenMalePool)/sizeof(demoGivenMalePool[0]))
#define DEMO_GIVEN_FEMALE_NUM							(sizeof(demoGivenFemalePool)/sizeof(demoGivenFemalePool[0]))

static uint32_t demoRandState = 1U;
static void demoRandSeed(uint32_t seed){
	if(seed == 0U){ seed = (uint32_t)HAL_GetTick() ^ 0x5A5A5A5AU; }
	demoRandState = (seed == 0U) ? 1U : seed;
}
static uint32_t demoRandNext(void){
	uint32_t x = demoRandState;
	x ^= x << 13; x ^= x >> 17; x ^= x << 5;
	demoRandState = x;
	return x;
}
static uint32_t demoRandRange(uint32_t mn, uint32_t mx){
	if(mx <= mn){ return mn; }
	return mn + (demoRandNext() % (mx - mn + 1U));
}
static uint32_t demoRandTri(uint32_t mn, uint32_t mx){
	if(mx <= mn){ return mn; }
	return (demoRandRange(mn, mx) + demoRandRange(mn, mx) + 1U) / 2U;
}

static int16_t demoPowerCap(void){
#if defined(CONFIG_MAX_LASER_POWER_CH0)
	int16_t cap = (int16_t)(CONFIG_MAX_LASER_POWER_CH0 / 10);
	if(cap < 1){ cap = 1; }
	return cap;
#else
	return 15;
#endif
}
static LASER_WAVE_ENUM demoPrimaryWave(void){
#if defined(APP_CONFIG_WAVE_1470_635) || defined(APP_CONFIG_WAVE_1470_980_635)
	return WAVE_1470;
#elif defined(APP_CONFIG_WAVE_1940_635) || defined(APP_CONFIG_WAVE_1940_1470_635)
	return WAVE_1940;
#elif defined(APP_CONFIG_WAVE_450_980)
	return WAVE_450;
#else
	return WAVE_1470;
#endif
}
static const demoProfile_t* demoPickProfile(void){
	uint32_t r = demoRandRange(1U, DEMO_PROFILE_WEIGHT_TOTAL);
	uint32_t acc = 0U;
	for(uint16_t i = 0U; i < (uint16_t)DEMO_PROFILE_NUM; i++){
		acc += demoProfileTable[i].weight;
		if(r <= acc){ return &demoProfileTable[i]; }
	}
	return &demoProfileTable[(uint16_t)DEMO_PROFILE_NUM - 1U];
}

static void demoBuildRecord(uint16_t id, treatmentLog_t *rec){
	const demoProfile_t *profile;
	int16_t power, powerCap;
	uint32_t timeSec, energy, surnameIdx, givenIdx;
	uint8_t female;

	profile = demoPickProfile();
	female = (demoRandRange(0U, 99U) < (uint32_t)profile->femaleRate) ? 1U : 0U;
	memset(rec, 0, sizeof(*rec));
	rec->id = id;
	rec->gender = (female != 0U) ? FEMALE : MALE;
	rec->age = (uint8_t)demoRandTri(profile->ageMin, profile->ageMax);
	rec->protocol = profile->protocol;
	rec->laserWave = demoPrimaryWave();

	powerCap = demoPowerCap();
	power = (int16_t)demoRandTri((uint32_t)profile->powerMin, (uint32_t)profile->powerMax);
	if(power > powerCap){ power = powerCap; }
	if(power < 1){ power = 1; }
	rec->laserPower = power;

	timeSec = demoRandTri(profile->timeMin, profile->timeMax);
	rec->releaseTime = (int32_t)timeSec;

	energy = (uint32_t)power * timeSec * (uint32_t)profile->duty / 100U;
	energy = energy * demoRandRange(96U, 104U) / 100U;
	if(energy < 1U){ energy = 1U; }
	rec->releaseEnergy = (int32_t)energy;

	surnameIdx = demoRandRange(0U, (uint32_t)DEMO_SURNAME_NUM - 1U);
	if(female != 0U){
		givenIdx = demoRandRange(0U, (uint32_t)DEMO_GIVEN_FEMALE_NUM - 1U);
		(void)sprintf(rec->name, "%s %s", demoSurnamePool[surnameIdx], demoGivenFemalePool[givenIdx]);
	}
	else{
		givenIdx = demoRandRange(0U, (uint32_t)DEMO_GIVEN_MALE_NUM - 1U);
		(void)sprintf(rec->name, "%s %s", demoSurnamePool[surnameIdx], demoGivenMalePool[givenIdx]);
	}
}

static uint8_t demoNameValid(const char *name){
	for(uint8_t i = 0U; i < (uint8_t)sizeof(treatmentLog.name); i++){
		if(name[i] == '\0'){ return (i > 0U) ? 1U : 0U; }
	}
	return 0U;
}
static uint8_t demoRecordValid(const treatmentLog_t *rec){
	int32_t maxEnergy;
	if((rec->id == 0U) || (rec->id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY)){ return 0U; }
	if((rec->gender != MALE) && (rec->gender != FEMALE)){ return 0U; }
	if((rec->age == 0U) || (rec->age > 110U)){ return 0U; }
	if((rec->laserPower < 1) || (rec->laserPower > demoPowerCap())){ return 0U; }
	if(rec->releaseTime <= 0){ return 0; }
	if((rec->laserWave < WAVE_450) || (rec->laserWave > WAVE_1470_980)){ return 0; }
	if(rec->protocol > eCustiom){ return 0U; }
	maxEnergy = (int32_t)rec->laserPower * rec->releaseTime * 110 / 100;
	if((rec->releaseEnergy <= 0) || (rec->releaseEnergy > maxEnergy)){ return 0U; }
	if(demoNameValid(rec->name) == 0U){ return 0U; }
	return 1U;
}
static treatmentDemoErr_t demoVerify(uint16_t count){
	uint16_t sample[3];
	uint16_t n = 0U;
	treatmentLog_t rec;
	if(count == 0U){ return TREATMENT_DEMO_OK; }
	sample[n++] = 0U;
	if(count > 2U){ sample[n++] = (uint16_t)(count / 2U); }
	sample[n++] = (uint16_t)(count - 1U);
	for(uint16_t i = 0U; i < n; i++){
		if(treatmentEpromGet(sample[i], &rec) != TREATMENT_EPROM_OK){ return TREATMENT_DEMO_ERR_VERIFY; }
		if(demoRecordValid(&rec) == 0U){ return TREATMENT_DEMO_ERR_VERIFY; }
	}
	return TREATMENT_DEMO_OK;
}

treatmentDemoErr_t treatmentDemoGenerate(uint16_t count, uint32_t seed, uint8_t clearFirst, uint16_t *written){
	uint16_t target, done = 0U;

	if(written != NULL){ *written = 0U; }
	if(count == 0U){ return TREATMENT_DEMO_ERR_PARAM; }
	demoRandSeed(seed);
	if(clearFirst != 0U){
		if(treatmentEpromClear() != TREATMENT_EPROM_OK){ return TREATMENT_DEMO_ERR_IO; }
	}
#if (CONFIG_TREATMENT_DEMO_VERBOSE == 1)
	uint32_t tickStart = HAL_GetTick();
#endif
	target = count;
	/* 每条 demo 为独立患者(患者20+记录16=36B); 空间满即停, 不把 FULL 当 IO 错误 */
	while(done < target){
		treatmentLog_t rec;
		treatmentEpromErr_t e;
		demoBuildRecord(treatmentGetNextPatientId(), &rec);
		e = treatmentEpromAdd(&rec);
		if(e == TREATMENT_EPROM_ERR_FULL){ break; }
		if(e != TREATMENT_EPROM_OK){ return TREATMENT_DEMO_ERR_IO; }
		done++;
	}
	if(demoVerify(done) != TREATMENT_DEMO_OK){ return TREATMENT_DEMO_ERR_VERIFY; }
	if(written != NULL){ *written = done; }
#if (CONFIG_TREATMENT_DEMO_VERBOSE == 1)
	printf("%s:demo fill ok, count=%u requested=%u cost=%lums free=%lu\n",
		__func__, done, target, (unsigned long)(HAL_GetTick() - tickStart),
		(unsigned long)treatmentGetFreeBytes());
#endif
	return TREATMENT_DEMO_OK;
}
