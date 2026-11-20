/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------
 * 病历存储模块 (归一化双结构 + 双区对向增长 + 断电原子提交)
 *
 * 设计要点:
 *  - 片上只存两类紧凑、自然对齐的定长结构:
 *      patientRecord_t   24 字节, 每个患者一行, 从区块低端向上增长;
 *      treatmentRecord_t 24 字节, 每次治疗一行, 从区块高端向下增长。
 *  - 患者身份(name 等)只存一次, 治疗记录以 patientId 外键引用, 不再重复。
 *  - 患者数/记录数默认无预设上限, 由两表之间的剩余空闲空间动态决定;
 *    同时保留两个可由板级配置覆盖的显式业务上限(0=不预设, 完全由空间决定):
 *      CONFIG_EPROM_TREATMENT_PATIENT_MAX             可动态分配的最大病人数;
 *      CONFIG_EPROM_TREATMENT_RECORD_MAX_PER_PATIENT  每个病人对应的最大病历数。
 *  - 断电原子性:
 *      患者行以 id 字段(0xFFFF=空白)为提交点, 先写正文再写 id;
 *      记录行以 magic 字段为状态机, 先写 PENDING 再翻 COMMIT;
 *      删除=单字节墓碑(TOMB), 随后基于空洞指针做安全压缩(可重入、可去重)。
 *  - 开机 Sanitize 为权威扫描恢复: 分类 blank/pending/commit/tomb, 去重、
 *    外键完整性校验、回收孤儿, 重建 P/R/nextId, 容忍 0xFF 与 0x00 两种空白态。
 *  - treatmentLog_t 仅为 RAM 内复合视图(供 HMI/CSV 复用), 不落 EPROM。
 *  - 所有地址计算均做 [START,END] 区间与空闲空间校验, 防止越界。
 *----------------------------------------------------------------------------*/
#ifndef __TREATMENT_H__
#define __TREATMENT_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
/* 患者姓名长度: 最多 CONFIG_TREATMENT_NAME_LEN 个字符(不含结束符), 缓冲区另加 1 字节结束符;
   片上患者行与 RAM 复合视图共用同一长度, 改此值即同时改变 EPROM 患者行尺寸(存量病历按固件CRC变化整片清空) */
#ifndef CONFIG_TREATMENT_NAME_LEN
#define CONFIG_TREATMENT_NAME_LEN										18
#endif
#define TREATMENT_NAME_SIZE													(CONFIG_TREATMENT_NAME_LEN + 1)
/*****************************************************************************/
/* 性别 */
typedef enum{
	MALE = 1,
	FEMALE = 2
}GENDER_ENUM;

/* 激光波长 */
typedef enum{
	WAVE_450 = 1,
	WAVE_915,
	WAVE_980,
	WAVE_1064,
	WAVE_1470,
	WAVE_1920,
	WAVE_635,
	WAVE_1940,
	WAVE_1470_980
}LASER_WAVE_ENUM;

/* 工作协议 */
typedef enum{
	ePhlebology = 0,
	eProctology,
	eGynecology,
	eENT,
	eNeurosurgery,
	eDermatology,
	eLiposuction,
	eDentistry,
	eTherapy,
	eCustiom
}PROTOCOL_ENUM;
/*****************************************************************************/
/* RAM 内复合视图(仅内存使用; 存储层负责与片上结构 split/join) */
typedef struct{
	uint16_t id;                       //患者编号
	uint8_t  age;
	int16_t  laserPower;               //激光功率
	int32_t  releaseEnergy;            //已发射能量 焦耳
	int32_t  releaseTime;              //发射时间 秒
	char     name[TREATMENT_NAME_SIZE];//患者姓名(最多CONFIG_TREATMENT_NAME_LEN个字符)
	GENDER_ENUM gender;                //患者性别
	LASER_WAVE_ENUM laserWave;         //选择的波长
	PROTOCOL_ENUM protocol;            //选择的预设方案
	uint16_t rtcYear;                  //治疗时刻RTC完整年份(2000-2099), 0表示未记录时间
	uint8_t  rtcMonth;                 //月 1-12
	uint8_t  rtcDay;                   //日 1-31
	uint8_t  rtcHour;                  //时 0-23
	uint8_t  rtcMinute;                //分 0-59
	uint8_t  rtcSecond;                //秒 0-59
}treatmentLog_t;

/*----------------------------------------------------------------------------
 * 片上结构: 患者主表行 (24B, 自然对齐)
 *   id 兼作提交点: 0xFFFF=空白/未提交, 有效非零 id=已提交。
 *----------------------------------------------------------------------------*/
typedef struct {
	uint16_t id;                       //稳定患者编号(单调, 删除不重编号)
	uint8_t  age;
	uint8_t  gender;                   //GENDER_ENUM 收窄为 uint8
	char     name[TREATMENT_NAME_SIZE];//患者姓名(最多CONFIG_TREATMENT_NAME_LEN个字符)
}patientRecord_t;

/*----------------------------------------------------------------------------
 * 片上结构: 治疗记录行 (24B, 自然对齐)
 *   recSeq: 稳定唯一记录序列(压缩/掉电去重依据), 开机扫描重建游标;
 *   waveProto: 高 nibble=laserWave, 低 nibble=protocol(各自取值 ≤9);
 *   magic: 行状态机(见 ROW_MAGIC_*);
 *   rtc*: 治疗时刻(停光瞬间)RTC, rtcYear存年份后两位(实际年=+2000), 0=未记录;
 *   reserved*: 显式保留对齐字节, 写入时置0, 不依赖编译器隐式填充。
 *----------------------------------------------------------------------------*/
typedef struct {
	uint16_t patientId;                //外键 -> patientRecord_t.id
	uint16_t recSeq;                   //稳定唯一记录序列
	int16_t  laserPower;
	uint8_t  waveProto;                //(laserWave<<4)|protocol
	uint8_t  magic;                    //ROW_MAGIC_* 状态
	int32_t  releaseEnergy;
	int32_t  releaseTime;
	uint8_t  rtcYear;                  //治疗时刻年份后两位(0-99, 实际年=+2000)
	uint8_t  rtcMonth;                 //月 1-12
	uint8_t  rtcDay;                   //日 1-31
	uint8_t  rtcHour;                  //时 0-23
	uint8_t  rtcMinute;                //分 0-59
	uint8_t  rtcSecond;                //秒 0-59
	uint8_t  reserved0;                //保留对齐(置0)
	uint8_t  reserved1;                //保留对齐(置0)
}treatmentRecord_t;

extern treatmentLog_t treatmentLog;
/*****************************************************************************/
const char* treatmentProtocolName(PROTOCOL_ENUM protocol);
const char* treatmentLaserWaveName(LASER_WAVE_ENUM wave);
/*****************************************************************************/
#if defined(CONFIG_EPROM_TREATMENT_START)
/* 片上定长行尺寸 */
#define CONFIG_EPROM_PATIENT_RECORD_SIZE								(sizeof(patientRecord_t))
#define CONFIG_EPROM_TREATMENT_RECORD_SIZE								(sizeof(treatmentRecord_t))
#define CONFIG_EPROM_TREATMENT_SLOT_EMPTY								0xFFFFu

/* 行状态机(刻意避开 0x00 与 0xFF, 使 clearEprom 的 0x00 与空白 FRAM 的 0xFF 都被识别为非有效) */
#define ROW_MAGIC_BLANK													0xFFu
#define ROW_MAGIC_PENDING												0x33u
#define ROW_MAGIC_COMMIT												0x5Au
#define ROW_MAGIC_TOMB													0xA5u

/* 患者/记录元数据硬边界(受 u16 与 DM int16 宽度约束) */
#define PATIENT_ID_LIMIT												32767u
#define RECORD_SEQ_LIMIT												65534u
#define PATIENT_AGE_LIMIT												150u

/* 错误码: 保留基线 TREATMENT_EPROM_ERR_* 语义, 新增患者/记录级别名 */
typedef enum{
	TREATMENT_EPROM_OK = 0,
	TREATMENT_EPROM_ERR_PARAM,        //参数错误(索引越界/指针为空)
	TREATMENT_EPROM_ERR_FULL,         //剩余空间不足/编号耗尽
	TREATMENT_EPROM_ERR_EMPTY,        //索引处无记录
	TREATMENT_EPROM_ERR_IO,           //EPROM 读写失败
	TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND,
	TREATMENT_EPROM_ERR_PATIENT_FULL
}treatmentEpromErr_t;

/* 语义别名(存储层内部及新代码使用) */
#define PATIENT_FULL						TREATMENT_EPROM_ERR_FULL
#define PATIENT_NOT_FOUND					TREATMENT_EPROM_ERR_PATIENT_NOT_FOUND
#define PATIENT_INVALID						TREATMENT_EPROM_ERR_PARAM

/* 显式业务上限(默认 0 = 不预设, 完全由剩余空间决定; >0 时启用封顶)。
 * 板级配置(如 G5 BoardConfig.h)可在包含本头前显式定义, 覆盖此处默认值。 */
/* 可动态分配的最大病人数 */
#ifndef CONFIG_EPROM_TREATMENT_PATIENT_MAX
#define CONFIG_EPROM_TREATMENT_PATIENT_MAX 0
#endif

/* 每个病人对应的最大病历数(治疗记录数) */
#ifndef CONFIG_EPROM_TREATMENT_RECORD_MAX_PER_PATIENT
#define CONFIG_EPROM_TREATMENT_RECORD_MAX_PER_PATIENT 0
#endif

/*============================================================================
 * 一级 API: 患者 / 记录 归一化操作
 *============================================================================*/
uint16_t treatmentGetNextPatientId(void);                                   //下一个可分配患者编号
uint16_t treatmentGetPatientCount(void);                                    //当前患者数
uint16_t treatmentGetRecordCount(void);                                     //当前治疗记录总数
uint16_t treatmentGetRecordCountForPatient(uint16_t patientId);             //指定患者的记录数
uint32_t treatmentGetFreeBytes(void);                                       //两表之间剩余空闲字节

treatmentEpromErr_t treatmentPatientCreate(const patientRecord_t *in, uint16_t *newId);  //新建患者
treatmentEpromErr_t treatmentPatientDelete(uint16_t patientId);            //删除患者(级联删除其全部记录)
treatmentEpromErr_t treatmentPatientGetByIndex(uint16_t index, patientRecord_t *out);    //按表内索引读患者
treatmentEpromErr_t treatmentPatientFind(uint16_t patientId, uint16_t *indexOut);        //按编号定位患者索引

treatmentEpromErr_t treatmentRecordAdd(const treatmentRecord_t *in);        //追加治疗记录(外键须存在)
treatmentEpromErr_t treatmentRecordDeleteByIndex(uint16_t index);           //删除单条记录(墓碑+安全压缩)
treatmentEpromErr_t treatmentRecordGetByIndex(uint16_t index, treatmentRecord_t *out);   //按索引读记录
treatmentEpromErr_t treatmentRecordUpdateByIndex(uint16_t index, const treatmentRecord_t *in); //更新记录

/*============================================================================
 * 扁平复合视图 API (供 HMI/CSV 复用, 内部映射到归一化存储)
 *============================================================================*/
uint16_t treatmentEpromGetCapacity(void);                                   //全为记录时可容纳条数上限
uint16_t treatmentEpromGetCount(void);                                      //当前治疗记录总数
uint16_t treatmentEpromGetPatientCount(void);                               //患者(人数)
uint16_t treatmentEpromGetPatientRecordCount(uint16_t patientId);           //指定患者已存记录数
treatmentEpromErr_t treatmentEpromAdd(const treatmentLog_t *log);           //追加(新患者自动建患者并分配ID)
treatmentEpromErr_t treatmentEpromAddToPatient(uint16_t patientId, const treatmentLog_t *log);
treatmentEpromErr_t treatmentEpromWriteAt(uint16_t index, const treatmentLog_t *log);
treatmentEpromErr_t treatmentEpromSaveCurrent(void);
treatmentEpromErr_t treatmentEpromInsert(uint16_t index, const treatmentLog_t *log);
treatmentEpromErr_t treatmentEpromDelete(uint16_t index);
treatmentEpromErr_t treatmentEpromUpdate(uint16_t index, const treatmentLog_t *log);
treatmentEpromErr_t treatmentEpromGet(uint16_t index, treatmentLog_t *out);
treatmentEpromErr_t treatmentEpromClear(void);
uint32_t treatmentEpromCalcFwCrc(void);
typedef void (*treatmentEpromVisitFn)(uint16_t index, const treatmentLog_t *log);
void treatmentEpromTraverse(treatmentEpromVisitFn fn);
/*****************************************************************************/
#ifndef CONFIG_TREATMENT_DEMO_VERBOSE
#define CONFIG_TREATMENT_DEMO_VERBOSE										0
#endif
/* 已废弃: 随机填充不再使用固定数量, 保留仅为兼容, 不参与逻辑 */
#ifndef CONFIG_TREATMENT_DEMO_COUNT
#define CONFIG_TREATMENT_DEMO_COUNT											200
#endif
#ifndef CONFIG_TREATMENT_DEMO_SEED
#define CONFIG_TREATMENT_DEMO_SEED											0
#endif
/* 虚拟病历生成: 直接写入本区块, 各子项按真实治疗场景自洽模拟 */
typedef enum{
	TREATMENT_DEMO_OK = 0,
	TREATMENT_DEMO_ERR_PARAM,
	TREATMENT_DEMO_ERR_IO,
	TREATMENT_DEMO_ERR_FULL,
	TREATMENT_DEMO_ERR_VERIFY
}treatmentDemoErr_t;
/* 随机虚拟病历填充: 随机病人数, 每个病人的记录数在 [recMin, recMax] 内随机。
 * recMin 与 recMax 同时为 0 时使用默认范围 5..20。
 * 所有 EPROM 写入经 FreeBytesPR(空隙) + RowWrite/InRegion(区间) 双重越界校验。
 * patientsWritten/recordsWritten 可为 NULL, 分别返回实际写入的病人数与记录数。 */
treatmentDemoErr_t treatmentDemoGenerate(uint32_t seed,
                                         uint8_t recMin, uint8_t recMax,
                                         uint8_t clearFirst,
                                         uint16_t *patientsWritten,
                                         uint16_t *recordsWritten);
#endif /* defined(CONFIG_EPROM_TREATMENT_START) */
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
