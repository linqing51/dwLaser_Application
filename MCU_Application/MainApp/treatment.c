/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "treatment.h"
#include <string.h>
/*****************************************************************************/
treatmentLog_t treatmentLog;// 患者记录全局变量(RAM)

//============================================================================
// 名称映射
//============================================================================
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

//============================================================================
// 区块几何与持久化计数
//============================================================================
#define REG_START        ((uint32_t)CONFIG_EPROM_TREATMENT_START)
#define REG_END          ((uint32_t)CONFIG_EPROM_TREATMENT_END)
#define REG_SIZE         ((uint32_t)CONFIG_EPROM_TREATMENT_SIZE)
#define PAT_BYTES        ((uint16_t)sizeof(patientRecord_t)) // 24
#define REC_BYTES        ((uint16_t)sizeof(treatmentRecord_t)) // 28
// 字段偏移统一用 offsetof 取编译器真实布局, 不写死魔法数字:
// 结构字段增减时偏移自动跟随, 从根本上消除"数据偏移"(正文/magic写错位置)隐患。
#define PAT_BODY_OFFSET  ((uint32_t)offsetof(patientRecord_t, age)) // 患者正文(age)起始偏移
#define REC_MAGIC_OFFSET ((uint32_t)offsetof(treatmentRecord_t, magic)) // 记录magic状态字段偏移

// 编译期尺寸固化: 防止结构调整后尺寸假设失效。
// ARMCC5(本工程,C99)不支持C11关键字_Static_assert, 改用负数组惯用法:
// 条件成立时typedef正常; 条件失败则数组尺寸为负, 触发编译错误#94, 等效静态断言。
#define STATIC_ASSERT(cond, ident) typedef char sa_##ident[(cond) ? 1 : -1]
STATIC_ASSERT(sizeof(patientRecord_t)==24U,   patient_row_24);
STATIC_ASSERT(sizeof(treatmentRecord_t)==28U, record_row_28);

// 无患者数/单患者记录数的显式业务上限: 两表均按剩余空间动态致密增长,
// 写入前由 FreeBytesPR 保证不碰撞、不越界; 总量上限即病历区块物理容量。

// 患者表索引 i 地址(低端向上)
static uint32_t PatientAddr(uint16_t i){
	return REG_START + (uint32_t)i * (uint32_t)PAT_BYTES;
}
// 记录表索引 j 地址(高端向下)
static uint32_t RecordAddr(uint16_t j){
	return (REG_END + 1U) - (uint32_t)(j + 1U) * (uint32_t)REC_BYTES;
}
// 两表之间剩余空闲字节(计数下, 行已致密时准确)
static uint32_t FreeBytesPR(uint16_t p, uint16_t r){
	return (REG_END + 1U - (uint32_t)r * REC_BYTES) - (REG_START + (uint32_t)p * PAT_BYTES);
}
// 区间校验: 行 [addr, addr+n-1] 必须完全落在病历区块内
static uint8_t InRegion(uint32_t addr, uint16_t n){
	return (addr >= REG_START) && (addr <= REG_END) &&
	       ((uint32_t)addr + (uint32_t)n <= REG_END + 1U);
}

// ---- 持久化计数原始访问(DM 为 int16, 空白 FRAM 为 0xFFFF) ----
static int16_t RawAt(uint16_t idx){ return NVRAM0[idx]; }
static void SetAt(uint16_t idx, uint16_t v){ NVRAM0[idx] = (int16_t)v; }

//============================================================================
// 恢复用位图(单一 8KB, 患者/记录阶段复用; 仅开机恢复时使用)
//============================================================================
static uint8_t g_bmp[8192];
static void BmpClear(void){ memset(g_bmp, 0, sizeof(g_bmp)); }
static uint8_t BmpTest(uint32_t bit){
	return (g_bmp[bit >> 3] & (uint8_t)(1UL << (bit & 7UL))) ? 1U : 0U;
}
static void BmpSet(uint32_t bit){
	g_bmp[bit >> 3] |= (uint8_t)(1UL << (bit & 7UL));
}

//============================================================================
// 开机恢复状态与行有效性
//============================================================================
static uint8_t  g_ready = 0U;
static uint16_t g_nextRecSeq = 1U;

static treatmentEpromErr_t writeGateCheck(void);

static uint8_t NameHasNul(const char *name, uint8_t len){
	for(uint8_t i = 0U; i < len; i++){ if(name[i] == '\0'){ return 1U; } }
	return 0U;
}
// 患者行: id 为提交点(0xFFFF=空白), 其余字段须落在合法范围
static uint8_t PatientRowValid(const patientRecord_t *r){
	return (r->id != 0U) && (r->id != CONFIG_EPROM_TREATMENT_SLOT_EMPTY) &&
	       (r->id <= PATIENT_ID_LIMIT) &&
	       ((r->gender == (uint8_t)MALE) || (r->gender == (uint8_t)FEMALE)) &&
	       (r->age <= PATIENT_AGE_LIMIT) &&
	       (NameHasNul(r->name, (uint8_t)sizeof(r->name)) != 0U);
}
// 记录行内容: 外键/序列非空, 波/协议 nibble 在范围
static uint8_t RecordContentValid(const treatmentRecord_t *r){
	uint8_t wave = (uint8_t)((r->waveProto >> 4) & 0x0FU);
	uint8_t proto = (uint8_t)(r->waveProto & 0x0FU);
	return (r->patientId != 0U) && (r->patientId != CONFIG_EPROM_TREATMENT_SLOT_EMPTY) &&
	       (r->recSeq != 0U) && (r->recSeq != CONFIG_EPROM_TREATMENT_SLOT_EMPTY) &&
	       (wave >= (uint8_t)WAVE_450) && (wave <= (uint8_t)WAVE_1470_980) &&
	       (proto <= (uint8_t)eCustiom);
}

//============================================================================
// 行级读写(带区间校验)
//============================================================================
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

//============================================================================
// 安全移动(目标为空洞; 先在目标提交, 再清除源; 掉电产生的重复由恢复去重)
//============================================================================
// 患者移动: 先写正文(目标 id 保持 0xFFFF), 再写 id 提交, 最后擦源
static void PatientMove(const patientRecord_t *row, uint16_t src, uint16_t dst){
	uint32_t d = PatientAddr(dst);
	(void)RowWrite(d + PAT_BODY_OFFSET, &row->age, (uint16_t)(PAT_BYTES - PAT_BODY_OFFSET));// 正文: age+gender+name+尾部对齐填充
	(void)RowWrite(d, &row->id, 2U);// 提交点
	EraseRow(PatientAddr(src), PAT_BYTES);
}
// 记录移动: 目标先写 PENDING, 再翻 COMMIT, 最后擦源
static void RecordMove(const treatmentRecord_t *row, uint16_t src, uint16_t dst){
	treatmentRecord_t out = *row;
	uint32_t d = RecordAddr(dst);
	uint8_t commit = ROW_MAGIC_COMMIT;
	out.magic = ROW_MAGIC_PENDING;
	(void)RowWrite(d, &out, REC_BYTES);
	(void)RowWrite(d + REC_MAGIC_OFFSET, &commit, 1U);// 提交点
	EraseRow(RecordAddr(src), REC_BYTES);
}

//============================================================================
// 开机权威扫描恢复 (Recovery)
//  容忍 0xFF(空白 FRAM) 与 0x00(clearEprom) 两种空白态;
//  分类 blank/pending/commit/tomb, 去重、外键完整性、回收孤儿, 重建计数。
//  几何安全: 患者表(低端)与记录表(高端)是覆盖同一物理区块的两套下标, 这里以存储计数推导
//  互不重叠的扫描上界, 并在遇到空白间隙时停止, 保证任一阶段的擦除/墓碑都不会落到对端表。
static void Recovery(void){
	uint16_t wp = 0U, wr = 0U, maxId = 0U;
	uint32_t maxSeq = 0UL;
	uint32_t physPat = REG_SIZE / PAT_BYTES;
	uint32_t physRec = REG_SIZE / REC_BYTES;
	// 存储计数仅作下界提示(计数总是在提交点之后才递增, 故不会多算; 断电可能少算 1 行)。
	// 这里必须用 RawAt 直读, 不能调 CntP/CntR(二者内部会再次进入 Recovery 形成递归)。
	int16_t pcStore = RawAt(DM_TREATMENT_PATIENT_NUM);
	int16_t rcStore = RawAt(DM_TREATMENT_NUM);
	uint32_t pc = (pcStore > 0) ? (uint32_t)pcStore : 0UL;
	uint32_t rc = (rcStore > 0) ? (uint32_t)rcStore : 0UL;
	uint32_t recStartAddr;
	uint32_t patEndAddr;
	uint32_t patScanMax;
	uint32_t recScanMax;

	if(g_ready != 0U){ return; }

	if(pc > physPat){ pc = physPat; }
	if(rc > physRec){ rc = physRec; }
	// 已计数患者区末端 / 已计数记录区始端
	recStartAddr = (REG_END + 1U) - rc * REC_BYTES;
	patEndAddr = REG_START + pc * PAT_BYTES;
	// 患者扫描上界: 槽位整行止于 recStartAddr 之前, 几何上不触及记录区
	patScanMax = (recStartAddr - REG_START) / PAT_BYTES;
	if(patScanMax > physPat){ patScanMax = physPat; }
	// 记录扫描上界: 槽位始端不低于 patEndAddr, 几何上不触及患者区
	recScanMax = (REG_END + 1U - patEndAddr) / REC_BYTES;
	if(recScanMax > physRec){ recScanMax = physRec; }

	// ---- Phase 1: 患者表 校验/去重/致密(仅低端) ----
	BmpClear();
	for(uint32_t s32 = 0U; s32 < patScanMax; s32++){
		uint16_t s = (uint16_t)s32;
		patientRecord_t row;
		if(RowRead(PatientAddr(s), &row, PAT_BYTES) != TREATMENT_EPROM_OK){ continue; }
		// 空白槽(0xFF 或 0x00 空白态)即致密表尽头/空闲区开始: 停止, 绝不向记录区擦除
		if((row.id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY) || (row.id == 0U)){ break; }
		if(PatientRowValid(&row) == 0U){ EraseRow(PatientAddr(s), PAT_BYTES); continue; }
		if(BmpTest(row.id) != 0U){ EraseRow(PatientAddr(s), PAT_BYTES); continue; }// 重复 id
		BmpSet(row.id);
		if(row.id > maxId){ maxId = row.id; }
		if(s != wp){ PatientMove(&row, s, wp); }
		wp++;
	}

	// ---- Phase 2a: 外键孤儿(患者不存在)的已提交记录 -> 墓碑; 位图仍为患者 id ----
	for(uint32_t s32 = 0U; s32 < recScanMax; s32++){
		uint16_t s = (uint16_t)s32;
		treatmentRecord_t row;
		uint8_t tomb = ROW_MAGIC_TOMB;
		if(RowRead(RecordAddr(s), &row, REC_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if((row.magic == 0xFFU) || (row.magic == 0x00U)){ break; }// 空白间隙, 停止
		if((row.magic == ROW_MAGIC_COMMIT) && (BmpTest(row.patientId) == 0U)){
			(void)RowWrite(RecordAddr(s) + REC_MAGIC_OFFSET, &tomb, 1U);
		}
	}

	// ---- Phase 2b: 记录表 校验/去重/致密(仅高端) ----
	BmpClear();
	for(uint32_t s32 = 0U; s32 < recScanMax; s32++){
		uint16_t s = (uint16_t)s32;
		treatmentRecord_t row;
		if(RowRead(RecordAddr(s), &row, REC_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if((row.magic == 0xFFU) || (row.magic == 0x00U)){ break; }// 空白间隙, 停止
		if(row.magic != ROW_MAGIC_COMMIT){ EraseRow(RecordAddr(s), REC_BYTES); continue; }
		if(RecordContentValid(&row) == 0U){ EraseRow(RecordAddr(s), REC_BYTES); continue; }
		if(BmpTest(row.recSeq) != 0U){ EraseRow(RecordAddr(s), REC_BYTES); continue; }// 重复序列
		BmpSet(row.recSeq);
		if(row.recSeq > maxSeq){ maxSeq = row.recSeq; }
		if(s != wr){ RecordMove(&row, s, wr); }
		wr++;
	}

	// 记录序列游标: 扫描最大值 +1, 受 u16 上限钳制
	g_nextRecSeq = (maxSeq >= RECORD_SEQ_LIMIT) ? RECORD_SEQ_LIMIT : (uint16_t)(maxSeq + 1U);

	SetAt(DM_TREATMENT_PATIENT_NUM, wp);
	SetAt(DM_TREATMENT_NUM, wr);
	SetAt(DM_TREATMENT_NEXT_ID, (maxId >= PATIENT_ID_LIMIT) ? PATIENT_ID_LIMIT : (uint16_t)(maxId + 1U));
	g_ready = 1U;
}

// 运行时致密(开机恢复后无重复; 自身移动即时清源, 故无需位图)
// 前向声明: 致密范围取自当前计数(CntP/CntR 定义在本节之后), 有效行恒致密在计数区间内
static uint16_t CntP(void);
static uint16_t CntR(void);
static uint16_t CompactPatients(void){
	uint16_t w = 0U;
	// 仅扫描本表当前已占用下标: 患者槽与记录槽是覆盖同一物理区块的两套独立下标, 若按
	// REG_SIZE/PAT_BYTES 扫满整个区块, 高端患者槽会越过空闲区覆盖到记录表, 把对端有效行擦除
	uint32_t patMax = (uint32_t)CntP();
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
	// 同 CompactPatients: 只在记录表当前计数范围内致密, 避免低端记录槽越过空闲区擦除患者表
	uint32_t recMax = (uint32_t)CntR();
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

// 最小空闲患者编号位图尺寸(字节): n 个患者的最小空缺正整数编号恒 <= n+1(抽屉原理),
// 故按"物理患者容量+1"位预留即可, 最坏约 295 字节
#define FIRST_FREE_PATIENT_ID_BITMAP_BYTES (((TREATMENT_PHYSICAL_PATIENT_CAP + 1U) + 7U) / 8U)

// 计算最小空闲患者编号: 单遍扫描患者表, 把落在 1..n 内的已用编号置位,
// 再从编号 1 起找首个未置位者; 若 1..n 全部占用则返回 n+1。
// 不依赖 NEXT_ID 高水位, 删除患者留下的空缺会被优先复用。
static uint16_t FirstFreePatientId(void){
  uint16_t n = CntP();
  uint8_t seen[FIRST_FREE_PATIENT_ID_BITMAP_BYTES];
  memset(seen, 0, sizeof(seen));
  for(uint16_t i = 0U; i < n; i++){
    patientRecord_t row;
    if(RowRead(PatientAddr(i), &row, PAT_BYTES) != TREATMENT_EPROM_OK){ continue; }
    if((row.id >= 1U) && (row.id <= n)){
      uint16_t b = (uint16_t)(row.id - 1U);
      seen[b / 8U] |= (uint8_t)(1U << (b % 8U));
    }
  }
  for(uint16_t b = 0U; b < n; b++){
    if((seen[b / 8U] & (uint8_t)(1U << (b % 8U))) == 0U){
      return (uint16_t)(b + 1U);
    }
  }
  return (uint16_t)(n + 1U);
}

//============================================================================
// 按需扫描(无 RAM 镜像, 每次直接读 FRAM; 仅占用单行工作变量, 与患者/记录数量无关)
//============================================================================
// 按编号扫描患者表, 返回其表索引(常量内存: 仅一个患者行变量)
static treatmentEpromErr_t findPatientIndexById(uint16_t pid, uint16_t *indexOut){
  uint16_t total = CntP();
  for(uint16_t i = 0U; i < total; i++){
    patientRecord_t row;
    if(RowRead(PatientAddr(i), &row, PAT_BYTES) != TREATMENT_EPROM_OK){ continue; }
    if(row.id == pid){
      if(indexOut != NULL){ *indexOut = i; }
      return TREATMENT_EPROM_OK;
    }
  }
  return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND;
}

// 扫描扁平记录表, 统计指定患者的已提交记录数(常量内存: 仅一个记录行变量)
static uint16_t countRecordsForPatient(uint16_t pid){
  uint16_t total = CntR();
  uint16_t n = 0U;
  for(uint16_t i = 0U; i < total; i++){
    treatmentRecord_t row;
    if(RowRead(RecordAddr(i), &row, REC_BYTES) != TREATMENT_EPROM_OK){ continue; }
    if(row.patientId == pid){ n++; }
  }
  return n;
}

//============================================================================
// 原子替换(更新): 新槽位两阶段提交 -> 旧行墓碑/空白 -> 致密
//  掉电时旧行始终保留到新行提交之后; 撕裂/重复由 Recovery 按稳定 id/recSeq 去重。
//  需一个空闲槽位; 满盘(无空闲)返回 ERR_FULL, 先删除再更新。
//============================================================================
// 记录替换: 新槽 PENDING->COMMIT(保留原 recSeq), 再旧槽 TOMB, 再致密
static treatmentEpromErr_t RecordReplaceAt(uint16_t index, const treatmentRecord_t *in){
	uint16_t r;
	treatmentRecord_t old, row;
	uint8_t commit = ROW_MAGIC_COMMIT, tomb = ROW_MAGIC_TOMB;
	treatmentEpromErr_t e;
	if(in == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	e = writeGateCheck();
	if(e != TREATMENT_EPROM_OK){ return e; }
	r = CntR();
	if(index >= r){ return TREATMENT_EPROM_ERR_PARAM; }
	if(FreeBytesPR(CntP(), r) < REC_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
	e = RowRead(RecordAddr(index), &old, REC_BYTES);
	if(e != TREATMENT_EPROM_OK){ return e; }
	row = *in;
	row.patientId = old.patientId;// 外键不可改
	row.recSeq = old.recSeq;// 稳定序列不可改
	row.magic = ROW_MAGIC_PENDING;
	if(RowWrite(RecordAddr(r), &row, REC_BYTES) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	if(RowWrite(RecordAddr(r) + REC_MAGIC_OFFSET, &commit, 1U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	if(RowWrite(RecordAddr(index) + REC_MAGIC_OFFSET, &tomb, 1U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	(void)CompactRecords();
	return TREATMENT_EPROM_OK;
}

// 患者替换: 新槽先写正文再写 id(保留原 id), 再旧槽 id 写 0xFFFF, 再致密
static treatmentEpromErr_t PatientReplaceAt(uint16_t index, const patientRecord_t *in){
	uint16_t p;
	patientRecord_t old, row;
	uint16_t blank = CONFIG_EPROM_TREATMENT_SLOT_EMPTY;
	treatmentEpromErr_t e;
	if(in == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	e = writeGateCheck();
	if(e != TREATMENT_EPROM_OK){ return e; }
	p = CntP();
	if(index >= p){ return TREATMENT_EPROM_ERR_PARAM; }
	if(FreeBytesPR(p, CntR()) < PAT_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
	e = RowRead(PatientAddr(index), &old, PAT_BYTES);
	if(e != TREATMENT_EPROM_OK){ return e; }
	row = *in;
	row.id = old.id;// 稳定 id 不可改
	if(RowWrite(PatientAddr(p) + PAT_BODY_OFFSET, &row.age, (uint16_t)(PAT_BYTES - PAT_BODY_OFFSET)) != TREATMENT_EPROM_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	if(RowWrite(PatientAddr(p), &row.id, 2U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	if(RowWrite(PatientAddr(index), &blank, 2U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	(void)CompactPatients();
	return TREATMENT_EPROM_OK;
}

//============================================================================
// 一级 API: 患者
//============================================================================
uint16_t treatmentGetNextPatientId(void){ return CntNext(); }
// 建议的新建患者编号(最小空缺优先, 无空缺取最大+1); 超出编号上限返回 0 表示无法再分配
uint16_t treatmentPatientSuggestId(void){
  uint16_t id = FirstFreePatientId();
  if((id == 0U) || (id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY) || (id > PATIENT_ID_LIMIT)){
    return 0U;
  }
  return id;
}
uint16_t treatmentGetPatientCount(void){ return CntP(); }
uint16_t treatmentGetRecordCount(void){ return CntR(); }

uint32_t treatmentGetFreeBytes(void){
	return FreeBytesPR(CntP(), CntR());
}

treatmentEpromErr_t treatmentPatientFind(uint16_t pid, uint16_t *indexOut){
  return findPatientIndexById(pid, indexOut);
}

treatmentEpromErr_t treatmentPatientGetByIndex(uint16_t index, patientRecord_t *out){
  if(out == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
  if(index >= CntP()){ return TREATMENT_EPROM_ERR_PARAM; }
  return RowRead(PatientAddr(index), out, PAT_BYTES);
}

// 连续批量读患者表: 患者行 24B 在低端连续致密, 一次 FRAM 事务内地址自增读完整个分块;
// 按 bufBytes 能容纳的整行数与剩余可用行数取小, 返回实际读取行数, 供 HMI 批量构建排序
uint16_t treatmentPatientReadRows(uint16_t startIndex, uint8_t *buf, uint16_t bufBytes){
  uint16_t total;
  uint16_t availRows;
  uint16_t wantRows;
  uint16_t rows;
  uint16_t len;
  if((buf == NULL) || (bufBytes == 0U)){ return 0U; }
  total = CntP();
  if(startIndex >= total){ return 0U; }
  availRows = (uint16_t)(total - startIndex);
  wantRows = (uint16_t)(bufBytes / PAT_BYTES);
  if(wantRows == 0U){ return 0U; }
  rows = (wantRows < availRows) ? wantRows : availRows;
  len = (uint16_t)(rows * PAT_BYTES);
  if(RowRead(PatientAddr(startIndex), buf, len) != TREATMENT_EPROM_OK){
    return 0U;
  }
  return rows;
}

// 新建患者(两阶段: 先写正文, id 最后提交)
treatmentEpromErr_t treatmentPatientCreate(const patientRecord_t *in, uint16_t *newId){
	uint16_t p, r, id;
	patientRecord_t row;
	if(in == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	{
		treatmentEpromErr_t ge = writeGateCheck();
		if(ge != TREATMENT_EPROM_OK){ return ge; }
	}
	p = CntP(); r = CntR();
	if(FreeBytesPR(p, r) < PAT_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
	id = FirstFreePatientId();//最小空缺优先, 无空缺取最大+1
	if((id == 0U) || (id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY) || (id > PATIENT_ID_LIMIT)){
		return TREATMENT_EPROM_ERR_FULL;
	}
	row = *in; row.id = id;
	(void)RowWrite(PatientAddr(p) + PAT_BODY_OFFSET, &row.age, (uint16_t)(PAT_BYTES - PAT_BODY_OFFSET));// 正文
	if(RowWrite(PatientAddr(p), &row.id, 2U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	SetAt(DM_TREATMENT_PATIENT_NUM, (uint16_t)(p + 1U));
	//高水位仅在新编号超过它时推进, 补空缺编号不会拉低 NEXT_ID
	if((uint16_t)(id + 1U) > CntNext()){ SetAt(DM_TREATMENT_NEXT_ID, (uint16_t)(id + 1U)); }
	if(newId != NULL){ *newId = id; }
	return TREATMENT_EPROM_OK;
}

// 内部: 以指定 id 确保患者存在(供 CSV 等带外键来源); 已存在则返回表索引
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
		treatmentEpromErr_t ge;
		ge = writeGateCheck();
		if(ge != TREATMENT_EPROM_OK){ return ge; }
		if((id == 0U) || (id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY) || (id > PATIENT_ID_LIMIT)){
			return TREATMENT_EPROM_ERR_PARAM;
		}
		if(FreeBytesPR(p, r) < PAT_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
		row = (tpl != NULL) ? *tpl : (patientRecord_t){0};
		row.id = id;
		(void)RowWrite(PatientAddr(p) + PAT_BODY_OFFSET, &row.age, (uint16_t)(PAT_BYTES - PAT_BODY_OFFSET));
		if(RowWrite(PatientAddr(p), &row.id, 2U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
		SetAt(DM_TREATMENT_PATIENT_NUM, (uint16_t)(p + 1U));
		if((uint16_t)(id + 1U) > CntNext()){ SetAt(DM_TREATMENT_NEXT_ID, (uint16_t)(id + 1U)); }
		if(indexOut != NULL){ *indexOut = p; }
	}
	return TREATMENT_EPROM_OK;
}

// 原地更新患者信息: id 保持不变, 仅覆盖姓名/性别/年龄(不新建患者、不动其治疗记录)
treatmentEpromErr_t treatmentPatientUpdate(uint16_t patientId, const patientRecord_t *in){
  uint16_t index;
  patientRecord_t row;
  treatmentEpromErr_t ge;
  if(in == NULL){
    return TREATMENT_EPROM_ERR_PARAM;
  }
  ge = writeGateCheck();
  if(ge != TREATMENT_EPROM_OK){
    return ge;
  }
  if(treatmentPatientFind(patientId, &index) != TREATMENT_EPROM_OK){
    return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND;
  }
  row = *in;
  row.id = patientId;//强制沿用原 id, 忽略调用方传入的 id
  if(PatientRowValid(&row) == 0U){
    return TREATMENT_EPROM_ERR_PARAM;
  }
  //正文从 age 偏移开始覆盖(长度=PAT_BYTES-2), id 字段不写
  if(RowWrite(PatientAddr(index) + PAT_BODY_OFFSET, &row.age, (uint16_t)(PAT_BYTES - PAT_BODY_OFFSET)) != TREATMENT_EPROM_OK){
    return TREATMENT_EPROM_ERR_IO;
  }
  return TREATMENT_EPROM_OK;
}

// 删除患者: 先墓碑其全部记录并致密, 再空白其 id 并致密患者表(级联)
treatmentEpromErr_t treatmentPatientDelete(uint16_t pid){	uint16_t pi;
	uint32_t recMax;
	treatmentEpromErr_t fe;

	fe = treatmentPatientFind(pid, &pi);
	if(fe != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND; }
	{
		treatmentEpromErr_t ge = writeGateCheck();
		if(ge != TREATMENT_EPROM_OK){ return ge; }
	}

	// 级联: 墓碑该患者全部记录(单字节原子), 再致密
	recMax = REG_SIZE / REC_BYTES;
	for(uint32_t s32 = 0U; s32 < recMax; s32++){
		uint16_t s = (uint16_t)s32;
		treatmentRecord_t row;
		uint8_t tomb = ROW_MAGIC_TOMB;
		if(RowRead(RecordAddr(s), &row, REC_BYTES) != TREATMENT_EPROM_OK){ continue; }
		if((row.patientId == pid) && (row.magic == ROW_MAGIC_COMMIT)){
			(void)RowWrite(RecordAddr(s) + REC_MAGIC_OFFSET, &tomb, 1U);
		}
	}
	(void)CompactRecords();

	// 空白患者 id(逻辑删除点), 再致密患者表
	{
		uint16_t blank = CONFIG_EPROM_TREATMENT_SLOT_EMPTY;
		(void)RowWrite(PatientAddr(pi), &blank, 2U);
	}
	(void)CompactPatients();
	return TREATMENT_EPROM_OK;
}

//============================================================================
// 一级 API: 记录
//============================================================================
uint16_t treatmentGetRecordCountForPatient(uint16_t pid){
	return countRecordsForPatient(pid);
}

// 追加记录(两阶段: 先 PENDING, 再翻 COMMIT)
treatmentEpromErr_t treatmentRecordAdd(const treatmentRecord_t *in){
	uint16_t p, r;
	treatmentRecord_t row;
	uint8_t commit;
	if(in == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	{
		treatmentEpromErr_t ge = writeGateCheck();
		if(ge != TREATMENT_EPROM_OK){ return ge; }
	}
	// 外键患者须存在(按需扫描, 仅校验, 不保留索引)
	if(findPatientIndexById(in->patientId, NULL) != TREATMENT_EPROM_OK){
		return TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND;
	}
	p = CntP(); r = CntR();
	if(FreeBytesPR(p, r) < REC_BYTES){ return TREATMENT_EPROM_ERR_FULL; }
	if((g_nextRecSeq == 0U) || (g_nextRecSeq > RECORD_SEQ_LIMIT)){ return TREATMENT_EPROM_ERR_FULL; }
	row = *in;
	row.recSeq = g_nextRecSeq;
	row.magic = ROW_MAGIC_PENDING;
	if(RowWrite(RecordAddr(r), &row, REC_BYTES) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	commit = ROW_MAGIC_COMMIT;
	if(RowWrite(RecordAddr(r) + REC_MAGIC_OFFSET, &commit, 1U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	SetAt(DM_TREATMENT_NUM, (uint16_t)(r + 1U));
	g_nextRecSeq++;
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentRecordGetByIndex(uint16_t index, treatmentRecord_t *out){
	if(out == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	if(index >= CntR()){ return TREATMENT_EPROM_ERR_PARAM; }
	return RowRead(RecordAddr(index), out, REC_BYTES);
}

// 轻量读外键: patientId是treatmentRecord_t首字段(2字节), 只读2字节替代整行28字节, 供记录页/计数扫描
treatmentEpromErr_t treatmentRecordGetPatientIdByIndex(uint16_t index, uint16_t *idOut){
	if(idOut == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	if(index >= CntR()){ return TREATMENT_EPROM_ERR_PARAM; }
	return RowRead(RecordAddr(index), idOut, 2U);
}

// 连续批量读记录行(单事务地址自增): 从startIndex起, 读bufBytes能容纳的若干完整REC_BYTES行, 返回行数。
// 记录高端向下(索引越大地址越低), 本批覆盖索引[startIndex,startIndex+rows), 最低地址属于最大索引,
// 故从该最低地址连续向上读, 数据按"索引递减"顺序填入buf; 计数只取每行首字段patientId, 不依赖顺序。
uint16_t treatmentRecordReadRows(uint16_t startIndex, uint8_t *buf, uint16_t bufBytes){
	uint16_t total;
	uint16_t availRows;
	uint16_t wantRows;
	uint16_t rows;
	uint32_t lowAddr;
	if((buf == NULL) || (bufBytes == 0U)){ return 0U; }
	total = CntR();
	if(startIndex >= total){ return 0U; }
	availRows = (uint16_t)(total - startIndex);
	wantRows = (uint16_t)(bufBytes / REC_BYTES);
	if(wantRows == 0U){ return 0U; }
	rows = (wantRows < availRows) ? wantRows : availRows;
	lowAddr = RecordAddr((uint16_t)(startIndex + rows - 1U));
	if(RowRead(lowAddr, buf, (uint16_t)(rows * REC_BYTES)) != TREATMENT_EPROM_OK){
		return 0U;
	}
	return rows;
}

// 删除单条: 墓碑(原子)后致密
treatmentEpromErr_t treatmentRecordDeleteByIndex(uint16_t index){
	uint8_t tomb;
	treatmentEpromErr_t ge;
	if(index >= CntR()){ return TREATMENT_EPROM_ERR_PARAM; }
	ge = writeGateCheck();
	if(ge != TREATMENT_EPROM_OK){ return ge; }
	tomb = ROW_MAGIC_TOMB;
	if(RowWrite(RecordAddr(index) + REC_MAGIC_OFFSET, &tomb, 1U) != TREATMENT_EPROM_OK){ return TREATMENT_EPROM_ERR_IO; }
	(void)CompactRecords();
	return TREATMENT_EPROM_OK;
}

// 更新记录: 新槽两阶段 + 旧行墓碑(非原地覆盖), 保留外键/稳定序列
treatmentEpromErr_t treatmentRecordUpdateByIndex(uint16_t index, const treatmentRecord_t *in){
	return RecordReplaceAt(index, in);
}

//============================================================================
// split / join: 复合视图 <-> 片上结构
//============================================================================
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
	//RTC治疗时刻: 片上存年份后两位, 复合视图还原为完整4位年; 0=未记录保持0
	out->rtcYear = (rec->rtcYear == 0U) ? 0U : (uint16_t)((uint16_t)rec->rtcYear + 2000U);
	out->rtcMonth = rec->rtcMonth;
	out->rtcDay = rec->rtcDay;
	out->rtcHour = rec->rtcHour;
	out->rtcMinute = rec->rtcMinute;
	out->rtcSecond = rec->rtcSecond;
	//脉冲模式/方案编号: 打包字节拆分(低5位=schemeIndex, 高3位中bit5-6=pulseMode)
	out->pulseMode = (uint8_t)((rec->modeScheme >> 5) & 0x07U);
	out->schemeIndex = (uint8_t)(rec->modeScheme & 0x1FU);
	out->posWidth = rec->posWidth;
	out->negWidth = rec->negWidth;
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
	//RTC治疗时刻: 复合视图为完整4位年, 片上收窄为后两位; 0=未记录
	rec->rtcYear = (log->rtcYear >= 2000U) ? (uint8_t)(log->rtcYear - 2000U) : 0U;
	rec->rtcMonth = log->rtcMonth;
	rec->rtcDay = log->rtcDay;
	rec->rtcHour = log->rtcHour;
	rec->rtcMinute = log->rtcMinute;
	rec->rtcSecond = log->rtcSecond;
	//脉冲模式/方案编号打包(pulseMode占bit5-6, schemeIndex占bit0-4); 保留字节显式置0
	rec->modeScheme = (uint8_t)(((uint8_t)(log->pulseMode & 0x07U) << 5)
	                            | (uint8_t)(log->schemeIndex & 0x1FU));
	rec->reserved1 = 0U;
	rec->posWidth = log->posWidth;
	rec->negWidth = log->negWidth;
}

//============================================================================
// 扁平复合视图 API
//============================================================================
uint16_t treatmentEpromGetCapacity(void){
	Recovery();
	return (uint16_t)(REG_SIZE / REC_BYTES);// 全为记录时的理论上限
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
		// 新患者: 自动建患者并分配新 id
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

// 批量写: 顺序追加(索引==当前记录数)时确保患者存在再落记录; 已存在索引则覆盖
treatmentEpromErr_t treatmentEpromWriteAt(uint16_t index, const treatmentLog_t *log){
	uint16_t r;
	if(log == NULL){ return TREATMENT_EPROM_ERR_PARAM; }
	r = CntR();
	if(index > r){ return TREATMENT_EPROM_ERR_PARAM; }
	if(index == r){
		// 追加路径: 带外键确保患者(同 id 复用, 新 id 建患者), 再追加记录
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
	// 覆盖已有索引: 记录与患者均走"新槽两阶段+旧行墓碑"(非原地覆盖)
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

// 归一化记录按插入顺序排列, 不保留任意位置插入; 映射为末尾追加
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
	treatmentEpromErr_t ge;
	ge = writeGateCheck();
	if(ge != TREATMENT_EPROM_OK){ return ge; }
	memset(blank, 0xFF, sizeof(blank));
	while(addr <= REG_END){
		uint16_t chunk = ((REG_END + 1U - addr) > sizeof(blank))
		                 ? (uint16_t)sizeof(blank) : (uint16_t)(REG_END + 1U - addr);
		if(epromWrite(addr, blank, chunk) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;// 失败保留原计数
		}
		addr += chunk;
	}
	SetAt(DM_TREATMENT_PATIENT_NUM, 0U);
	SetAt(DM_TREATMENT_NUM, 0U);
	// 清空后下一个患者 ID 从 1 开始(0 为非法哨兵); 若写 0 且 g_ready 已置位,
	// CntNext()=0 会让 treatmentPatientCreate 误判 FULL、无法新建患者
	SetAt(DM_TREATMENT_NEXT_ID, 1U);
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

//============================================================================
// PVD 欠压写入门控
//  阈值 2.8V(PVDLEVEL_6), EXTI line16 双沿中断;
//  回调只置/清 volatile 标志, 不调用任何 RTOS/FRAM API, 可在高优先级执行。
//============================================================================
static volatile uint8_t g_writeBlocked = 0U;

uint8_t treatmentWriteBlocked(void){ return g_writeBlocked; }

// HAL 弱回调: PVD 中断经 HAL_PWR_PVD_IRQHandler 调用;
// PVDO=1 表示 Vdd 已低于阈值(门控关闭新写入), PVDO=0 表示恢复(解除)。
void HAL_PWR_PVDCallback(void){
	if(__HAL_PWR_GET_FLAG(PWR_FLAG_PVDO) != 0U){
		g_writeBlocked = 1U;
	}
	else {
		g_writeBlocked = 0U;
	}
}

void treatmentPvdInit(void){
	PWR_PVDTypeDef cfg;
	cfg.PVDLevel = PWR_PVDLEVEL_6;                 //2.8V
	cfg.Mode = PWR_PVD_MODE_IT_RISING_FALLING;    //双沿: 跌落与恢复都进中断
	(void)HAL_PWR_ConfigPVD(&cfg);
	HAL_NVIC_SetPriority(PVD_IRQn, CONFIG_PVD_IRQ_PREEMPT_PRIORITY, CONFIG_PVD_IRQ_SUB_PRIORITY);
	HAL_NVIC_EnableIRQ(PVD_IRQn);                 //HAL_PWR_EnablePVD 不使能 NVIC, 须显式开启
	HAL_PWR_EnablePVD();
}

// 写路径统一门控: 开启新事务前调用, 欠压则拒绝; 已在事务内的两阶段写入不受此限
static treatmentEpromErr_t writeGateCheck(void){
	if(g_writeBlocked != 0U){ return TREATMENT_EPROM_ERR_POWER_LOW; }
	return TREATMENT_EPROM_OK;
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

//============================================================================
// 虚拟病历生成(测试数据填充)
//============================================================================
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
#define DEMO_PROFILE_NUM          (sizeof(demoProfileTable) / sizeof(demoProfile_t))
#define DEMO_PROFILE_WEIGHT_TOTAL 100

//测试病历姓名池: 西方常用人名, 首字母大写、其余小写(区分大小写), 组合时"名前姓后"; 名+空格+姓总长不超过18字符
static const char *const demoSurnamePool[] = {
	"Smith", "Johnson", "Williams", "Brown", "Jones", "Garcia", "Miller", "Davis", "Martinez", "Lopez",
	"Gonzalez", "Wilson", "Anderson", "Thomas", "Taylor", "Moore", "Jackson", "Martin", "Lee", "Perez",
	"Thompson", "White", "Harris", "Sanchez", "Clark", "Ramirez", "Lewis", "Robinson", "Walker", "Hall"
};
static const char *const demoGivenMalePool[] = {
	"James", "Robert", "John", "Michael", "David", "William", "Richard", "Joseph", "Thomas", "Daniel",
	"Matthew", "Anthony", "Mark", "Steven", "Paul", "Andrew", "Joshua", "Kevin", "Brian", "George"
};
static const char *const demoGivenFemalePool[] = {
	"Mary", "Patricia", "Jennifer", "Linda", "Elizabeth", "Barbara", "Susan", "Jessica", "Sarah", "Karen",
	"Lisa", "Nancy", "Betty", "Margaret", "Sandra", "Ashley", "Kimberly", "Emily", "Donna", "Michelle"
};
#define DEMO_SURNAME_NUM      (sizeof(demoSurnamePool)/sizeof(demoSurnamePool[0]))
#define DEMO_GIVEN_MALE_NUM   (sizeof(demoGivenMalePool)/sizeof(demoGivenMalePool[0]))
#define DEMO_GIVEN_FEMALE_NUM (sizeof(demoGivenFemalePool)/sizeof(demoGivenFemalePool[0]))

static uint32_t demoRandState = 1U;
static void demoRandSeed(uint32_t seed){
	if(seed == 0U){
		//运行时刻随机种子: 滴答时间 + 芯片96位唯一ID + 上一次PRNG状态混合,
		//保证每次按键(即使同一毫秒内连点)都得到不同序列
		uint32_t uid0 = *(const volatile uint32_t*)(UID_BASE);
		uint32_t uid1 = *(const volatile uint32_t*)(UID_BASE + 4U);
		uint32_t uid2 = *(const volatile uint32_t*)(UID_BASE + 8U);
		seed = (uint32_t)HAL_GetTick();
		seed ^= uid0;
		seed ^= (uid1 << 7) | (uid1 >> 25);
		seed ^= (uid2 << 17) | (uid2 >> 15);
		seed ^= demoRandState;
		seed ^= 0x5A5A5A5AU;
	}
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

//姓名去重重试上限(无RAM已用表, 每次直接扫描已存患者)
#define DEMO_NAME_TRY_LIMIT                        100U

//姓名是否已被现有患者使用: 扫描患者表逐行比对(常量内存, 仅一个患者行变量), 替代原RAM内usedKeys
static uint8_t demoNameExistsInStorage(const char *name){
  uint16_t total = CntP();
  for(uint16_t i = 0U; i < total; i++){
    patientRecord_t row;
    if(RowRead(PatientAddr(i), &row, PAT_BYTES) != TREATMENT_EPROM_OK){
      continue;
    }
    if(strncmp(row.name, name, TREATMENT_NAME_SIZE) == 0){
      return 1U;
    }
  }
  return 0U;
}

//演示记录随机治疗时刻的完整年份范围; 下限避开2000(片上存0, 与"无时间"哨兵冲突无法回显)
#define DEMO_RTC_YEAR_MIN                          2001U
#define DEMO_RTC_YEAR_MAX                          2099U

//某年某月的合法天数, 处理闰年2月(闰年规则与RtcCheckDate一致)
static uint8_t demoDaysInMonth(uint16_t year, uint8_t month){
  static const uint8_t monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
  uint8_t days = monthDays[month - 1U];
  if(month == 2U){
    if(((year % 4U == 0U) && (year % 100U != 0U)) || (year % 400U == 0U)){
      days = 29U;
    }
  }
  return days;
}

//给演示记录随机附一条合规RTC: 年月日时分秒均在合法范围, 日期与月份/闰年匹配
static void demoStampRandomRtc(treatmentLog_t *rec){
  uint16_t year;
  uint8_t month;
  if(rec == NULL){
    return;
  }
  year = (uint16_t)demoRandRange(DEMO_RTC_YEAR_MIN, DEMO_RTC_YEAR_MAX);
  month = (uint8_t)demoRandRange(1U, 12U);
  rec->rtcYear = year;
  rec->rtcMonth = month;
  rec->rtcDay = (uint8_t)demoRandRange(1U, demoDaysInMonth(year, month));
  rec->rtcHour = (uint8_t)demoRandRange(0U, 23U);
  rec->rtcMinute = (uint8_t)demoRandRange(0U, 59U);
  rec->rtcSecond = (uint8_t)demoRandRange(0U, 59U);
}

static void demoBuildRecord(uint16_t id, treatmentLog_t *rec){
	const demoProfile_t *profile;
	int16_t power, powerCap;
	uint32_t timeSec, energy, surnameIdx, givenIdx;
	uint16_t nameTries;
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

	energy = (uint32_t)power * timeSec * (uint32_t)profile->duty / 10U;//0.1J(decijoule), 显示时除以10
	energy = energy * demoRandRange(96U, 104U) / 100U;
	if(energy < 1U){ energy = 1U; }
	rec->releaseEnergy = (int32_t)energy;

	//发射模式随机: 连续模式脉宽置0; 脉冲模式随机正/负脉宽(5..800ms); 方案编号0..2
	if(demoRandRange(0U, 1U) == 0U){
		rec->pulseMode = LASER_MODE_CW;
		rec->posWidth = 0U;
		rec->negWidth = 0U;
	}
	else{
		rec->pulseMode = LASER_MODE_MP;
		rec->posWidth = (uint16_t)demoRandRange(5U, 800U);
		rec->negWidth = (uint16_t)demoRandRange(5U, 800U);
	}
	rec->schemeIndex = (uint8_t)demoRandRange(0U, 2U);

	//姓名去重(无RAM表): 生成候选全名并扫描已存患者比对, 重试到未用姓名或达上限;
	//名字池共1200个全名, 达上限仍碰撞时接受最后候选(与原口径一致, 不报错)
	nameTries = 0U;
	do{
		surnameIdx = demoRandRange(0U, (uint32_t)DEMO_SURNAME_NUM - 1U);
		if(female != 0U){
			givenIdx = demoRandRange(0U, (uint32_t)DEMO_GIVEN_FEMALE_NUM - 1U);
			//西方习惯名前姓后(如"Mary Smith"), 大小写混合可验证搜索的大小写敏感口径
			(void)sprintf(rec->name, "%s %s", demoGivenFemalePool[givenIdx], demoSurnamePool[surnameIdx]);
		}
		else{
			givenIdx = demoRandRange(0U, (uint32_t)DEMO_GIVEN_MALE_NUM - 1U);
			(void)sprintf(rec->name, "%s %s", demoGivenMalePool[givenIdx], demoSurnamePool[surnameIdx]);
		}
		nameTries++;
	}while((nameTries < DEMO_NAME_TRY_LIMIT) &&
	       (demoNameExistsInStorage(rec->name) != 0U));
	//随机附合规治疗时刻(年月日时分秒合法, 与月/闰年匹配), 使记录页显示真实格式时间而非横线
	demoStampRandomRtc(rec);
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
	//能量上界按0.1J计(原整数J口径×10): 110%留抖动余量
	maxEnergy = (int32_t)rec->laserPower * rec->releaseTime * 110 / 10;
	if((rec->releaseEnergy <= 0) || (rec->releaseEnergy > maxEnergy)){ return 0U; }
	//发射模式: CW脉宽须为0; MP正/负脉宽须在有效范围
	if(rec->pulseMode == LASER_MODE_CW){
		if((rec->posWidth != 0U) || (rec->negWidth != 0U)){ return 0U; }
	}
	else if(rec->pulseMode == LASER_MODE_MP){
		if((rec->posWidth < 1U) || (rec->negWidth < 1U)){ return 0U; }
	}
	else{
		return 0U;
	}
	if(rec->schemeIndex >= CONFIG_HMI_SCHEME_NUM){ return 0U; }
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

// 默认每患者记录数范围(参数全 0 时启用)
#define DEMO_REC_MIN_DEFAULT 5U
#define DEMO_REC_MAX_DEFAULT 19U //每患者随机记录数上界(仅demo分布参数, 非存储上限, 与区块容量无关)

treatmentDemoErr_t treatmentDemoGenerate(uint32_t seed, uint8_t recMin, uint8_t recMax,
                                         uint8_t clearFirst,
                                         uint16_t *patientsWritten, uint16_t *recordsWritten){
	uint16_t patients = 0U, records = 0U;
#if (CONFIG_TREATMENT_DEMO_VERBOSE == 1)
	uint32_t tickStart;
#endif
	if(patientsWritten != NULL){ *patientsWritten = 0U; }
	if(recordsWritten != NULL){ *recordsWritten = 0U; }

	// 参数归一化: 两者同时为 0 时使用默认范围; 随后修正非法/倒挂范围
	if((recMin == 0U) && (recMax == 0U)){
		recMin = (uint8_t)DEMO_REC_MIN_DEFAULT;
		recMax = (uint8_t)DEMO_REC_MAX_DEFAULT;
	}
	if(recMin == 0U){ recMin = 1U; }
	if(recMax < recMin){ recMax = recMin; }

	demoRandSeed(seed);
	if(clearFirst != 0U){
		if(treatmentEpromClear() != TREATMENT_EPROM_OK){ return TREATMENT_DEMO_ERR_IO; }
	}
#if (CONFIG_TREATMENT_DEMO_VERBOSE == 1)
	tickStart = HAL_GetTick();
#endif

	// 填满模式(无患者数/记录数硬上限): 持续新建患者, 直到剩余空间不足以再容纳一个患者行+首条记录;
	// 每患者记录数在 [recMin, recMax] 内随机, 尾部空间不足时由内部循环安全截断, 写不下即停, 不产生越界;
	// 终止性由 FreeBytesPR 保证: 每个患者至少写 52 字节, 区块有限, 必然在有限步内退出
	while(1){
		treatmentLog_t base;
		treatmentEpromErr_t e;
		uint16_t wantRec, pid, k;

		// 唯一停止条件: 剩余空间放不下 患者行+至少1条记录
		if(FreeBytesPR(CntP(), CntR()) < (uint32_t)(PAT_BYTES + REC_BYTES)){ break; }

		// 该患者的目标记录数(每患者独立随机)
		wantRec = (uint16_t)demoRandRange((uint32_t)recMin, (uint32_t)recMax);

		// 首条: 建立新患者(随机身份, 姓名去重由demoBuildRecord内部扫描FRAM保证)并写入第 1 条记录;
		// 调用前取 next id 即实际分配 id
		pid = treatmentGetNextPatientId();
		demoBuildRecord(pid, &base);
		e = treatmentEpromAdd(&base);
		if((e == TREATMENT_EPROM_ERR_FULL) || (e == TREATMENT_EPROM_ERR_PATIENT_FULL)){ break; }
		if(e != TREATMENT_EPROM_OK){ return TREATMENT_DEMO_ERR_IO; }
		records++;

		// 第 2..wantRec 条: 复用患者身份(id/age/gender/name), 仅治疗参数随机
		for(k = 1U; k < wantRec; k++){
			treatmentLog_t more;
			// 第一重保险(空隙): 剩余空间不足一条记录则结束该患者
			if(FreeBytesPR(CntP(), CntR()) < REC_BYTES){ break; }
			demoBuildRecord(pid, &more);
			more.id = pid;
			more.age = base.age;
			more.gender = base.gender;
			(void)memcpy(more.name, base.name, sizeof(more.name));
			e = treatmentEpromAddToPatient(pid, &more);
			if((e == TREATMENT_EPROM_ERR_FULL) || (e == TREATMENT_EPROM_ERR_PATIENT_FULL)){ break; }
			if(e != TREATMENT_EPROM_OK){ return TREATMENT_DEMO_ERR_IO; }
			records++;
		}
		patients++;
	}

	if(demoVerify(records) != TREATMENT_DEMO_OK){ return TREATMENT_DEMO_ERR_VERIFY; }
	if(patientsWritten != NULL){ *patientsWritten = patients; }
	if(recordsWritten != NULL){ *recordsWritten = records; }
#if (CONFIG_TREATMENT_DEMO_VERBOSE == 1)
	printf("%s:fill-to-cap ok, patients=%u records=%u cost=%lums free=%lu\n",
		__func__, patients, records,
		(unsigned long)(HAL_GetTick() - tickStart),
		(unsigned long)treatmentGetFreeBytes());
#endif
	return TREATMENT_DEMO_OK;
}

//============================================================================
// 结构化诊断快照(主机侧 host_diag 自动读取/解析, 形成"写诊断->读诊断->判定"闭环)
//  统一输出 @DIAG key=value 行, 以 BEGIN/END 界定一次完整快照; 纯只读,
//  系统就绪后 CntP/CntR 内 Recovery 立即返回, 无副作用、无额外 FRAM 写入。
//============================================================================
void treatmentDumpDiagnostics(void){
  uint16_t patientCount = treatmentGetPatientCount();
  uint16_t recordCount = treatmentGetRecordCount();
  uint16_t capacity = (uint16_t)(REG_SIZE / REC_BYTES);
  uint32_t freeBytes = treatmentGetFreeBytes();
  printf("@DIAG BEGIN\n");
  printf("@DIAG patBytes=%u\n", (unsigned)PAT_BYTES);
  printf("@DIAG recBytes=%u\n", (unsigned)REC_BYTES);
  printf("@DIAG patBodyOffset=%lu\n", (unsigned long)PAT_BODY_OFFSET);
  printf("@DIAG recMagicOffset=%lu\n", (unsigned long)REC_MAGIC_OFFSET);
  printf("@DIAG regStart=%lu\n", (unsigned long)REG_START);
  printf("@DIAG regEnd=%lu\n", (unsigned long)REG_END);
  printf("@DIAG regSize=%lu\n", (unsigned long)REG_SIZE);
  printf("@DIAG capacity=%u\n", (unsigned)capacity);
  printf("@DIAG patientCount=%u\n", (unsigned)patientCount);
  printf("@DIAG recordCount=%u\n", (unsigned)recordCount);
  printf("@DIAG nextPatientId=%u\n", (unsigned)treatmentGetNextPatientId());
  printf("@DIAG freeBytes=%lu\n", (unsigned long)freeBytes);
  printf("@DIAG pvdBlocked=%u\n", (unsigned)treatmentWriteBlocked());
  printf("@DIAG deviceIdStatus=%d\n", (int)epromGetIdStatus());
  printf("@DIAG END\n");
}
