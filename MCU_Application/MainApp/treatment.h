/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
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
typedef enum{
	MALE = 1,
	FEMALE = 2	
}GENDER_ENUM;

typedef enum{
	WAVE_450 = 1,
	WAVE_915,
	WAVE_980,
	WAVE_1064,
	WAVE_1470,
	WAVE_1920,
	WAVE_635,//635nm
	WAVE_1940,//1940nm
	WAVE_1470_980//1470nm+980nm
}LASER_WAVE_ENUM;

typedef enum{
	ePhlebology = 0,
	eProctology,//1
	eGynecology,//2
	eENT,//3
	eNeurosurgery,//4
	eDermatology,//5
	eLiposuction,//6
	eDentistry,//7
	eTherapy,//8
	eCustiom
}PROTOCOL_ENUM;
/*****************************************************************************/
//病历数据模型: 一位患者 = 一个患者档案块(患者信息 + 最多N条病历), 一条病历 = 一次治疗的参数
//下面的结构体仅作RAM视图使用(会话/界面/临时变量), 不直接写入FRAM, 也不参与寻址:
//落盘格式由 CONFIG_EPROM_TREATMENT_*_BYTES / OFF_* 常量定义, 由 treatment.c 内的小端编解码负责转换,
//因此结构体尺寸/对齐/枚举宽度随编译器变化时, FRAM中的字节与病历容量都不会变
#ifndef CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT
#define CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT		10//每位患者最多保存病历条数(可在板型AppConfig中覆盖)
#endif
#ifndef CONFIG_EPROM_TREATMENT_OVERWRITE_OLDEST
#define CONFIG_EPROM_TREATMENT_OVERWRITE_OLDEST			0//该患者病历已满时的策略: 0=拒绝保存(需先删旧病历), 1=整体前移覆盖最旧一条
#endif

typedef struct{//单次治疗参数 = 一条病历的RAM视图(落盘12字节, 字段顺序见 CONFIG_EPROM_TREATMENT_REC_OFF_*)
	int32_t releaseEnergy;//已发射能量 单位焦耳
	int32_t releaseTime;//发射时间 单位秒
	int16_t laserPower;//激光功率 单位W
	uint8_t laserWave;//选择的波长(LASER_WAVE_ENUM取值)
	uint8_t protocol;//选择的预设方案(PROTOCOL_ENUM取值)
}treatmentRecord_t;

typedef struct{//患者档案块的RAM视图(落盘144字节, 字段偏移见 CONFIG_EPROM_TREATMENT_OFF_*)
	char name[19];//患者名字, 未用字节填0(19B正好填满块头, 无对齐浪费)
	uint8_t age;//患者年龄
	uint8_t gender;//患者性别(GENDER_ENUM取值)
	uint8_t recordCount;//已保存病历条数(0~CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT)
	uint16_t patientId;//患者ID: 1~0xFFFE有效, 0或0xFFFF表示空块(放在三个uint8之后, 2字节对齐无需填充)
	treatmentRecord_t record[CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT];//索引0为最早一次治疗
}treatmentPatient_t;
/*****************************************************************************/
typedef struct{//本次治疗会话(待保存): 患者信息可编辑 + 实时治疗参数, 仅存在于RAM
	uint16_t patientId;//0=新患者(保存时自动分配ID), 非0=追加到该患者
	char name[19];//患者名字(与患者块NAME_BYTES一致, 可容纳19B)
	uint8_t age;//患者年龄
	GENDER_ENUM gender;//患者性别
	int16_t laserPower;//激光功率
	int32_t releaseEnergy;//已发射能量 单位焦耳
	int32_t releaseTime;//发射时间 单位秒
	LASER_WAVE_ENUM laserWave;//选择的波长
	PROTOCOL_ENUM protocol;//选择的预设方案
}treatmentLog_t;
/*****************************************************************************/
extern treatmentLog_t treatmentLog;
/*****************************************************************************/
extern uint8_t treatmentLogValid;//当前治疗记录有效性:任意一次激光发射后置1,上电复位/保存病历后清0
void treatmentLogToRecord(const treatmentLog_t *session, treatmentRecord_t *rec);//会话参数转成一条病历(功率/能量/时间/波长/方案)
const char* treatmentProtocolName(PROTOCOL_ENUM protocol);//治疗方案名称映射
const char* treatmentLaserWaveName(LASER_WAVE_ENUM wave);//激光波长名称映射
/*****************************************************************************/
#if defined(CONFIG_EPROM_TREATMENT_START)
//落盘布局采用"字节常量 + 小端编解码"的二进制契约: 患者块大小/容量/地址/字段偏移全部由下面的纯整数宏决定,
//不再使用 sizeof(结构体) 或 指针相减求偏移, 因此无论用 AC5(armcc)/AC6(armclang)/GCC, 写进FRAM的字节与可存患者数量完全一致
//结构体只作为RAM视图(会话/临时), 仅在RAM内使用, 不参与任何落盘寻址
#define CONFIG_EPROM_TREATMENT_RECORD_BYTES								12u//单条病历落盘字节数
#define CONFIG_EPROM_TREATMENT_NAME_BYTES									19u//姓名落盘字节数(由16扩到19, 吃掉原reserved+2B对齐填充, 块头仍24B)
#define CONFIG_EPROM_TREATMENT_HEAD_BYTES									24u//患者块头落盘字节数(19姓名+2ID+1年龄+1性别+1条数=24, 无填充)
#define CONFIG_EPROM_TREATMENT_PATIENT_BYTES								(CONFIG_EPROM_TREATMENT_HEAD_BYTES + (CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT * CONFIG_EPROM_TREATMENT_RECORD_BYTES))//单个患者块字节数(144B, 容量不变)

//患者块头字段的字节偏移(格式契约, 不可随意调整, 字段紧凑排列无空隙)
#define CONFIG_EPROM_TREATMENT_OFF_NAME									0u//姓名 19B
#define CONFIG_EPROM_TREATMENT_OFF_PATIENT_ID							19u//患者ID 2B 小端
#define CONFIG_EPROM_TREATMENT_OFF_AGE									21u//年龄 1B
#define CONFIG_EPROM_TREATMENT_OFF_GENDER								22u//性别 1B(GENDER_ENUM取值)
#define CONFIG_EPROM_TREATMENT_OFF_RECORD_COUNT						23u//病历条数 1B
#define CONFIG_EPROM_TREATMENT_OFF_RECORD								24u//病历数组起始(必须4字节对齐)

//病历字段的字节偏移(格式契约, 不可随意调整)
#define CONFIG_EPROM_TREATMENT_REC_OFF_ENERGY							0u//已发射能量 int32 小端
#define CONFIG_EPROM_TREATMENT_REC_OFF_TIME								4u//发射时间 int32 小端
#define CONFIG_EPROM_TREATMENT_REC_OFF_POWER							8u//激光功率 int16 小端
#define CONFIG_EPROM_TREATMENT_REC_OFF_WAVE								10u//波长 1B(LASER_WAVE_ENUM取值)
#define CONFIG_EPROM_TREATMENT_REC_OFF_PROTOCOL							11u//预设方案 1B(PROTOCOL_ENUM取值)

#define CONFIG_EPROM_TREATMENT_RECORD_SIZE								CONFIG_EPROM_TREATMENT_RECORD_BYTES//单条病历字节数
#define CONFIG_EPROM_TREATMENT_PATIENT_SIZE								CONFIG_EPROM_TREATMENT_PATIENT_BYTES//单个患者块字节数
#define CONFIG_EPROM_TREATMENT_PATIENT_MAX									(CONFIG_EPROM_TREATMENT_SIZE / CONFIG_EPROM_TREATMENT_PATIENT_SIZE)//区块可容纳患者数量上限(按区块容量自动计算)
#define CONFIG_EPROM_TREATMENT_RECORD_MAX									(CONFIG_EPROM_TREATMENT_PATIENT_MAX * CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT)//区块可容纳病历总条数上限
#define CONFIG_EPROM_TREATMENT_PATIENT_EMPTY								0xFFFF//空块标记
#define CONFIG_EPROM_TREATMENT_PATIENT_ID_MIN									1//患者ID最小值(0与0xFFFF均视为空)
#define CONFIG_EPROM_TREATMENT_PATIENT_ID_MAX									0xFFFE//患者ID最大值(避免与空块标记混淆)

//应用级边界: 病历人数 / 每人病历条数 的硬上限, 可小于物理容量(便于产品限流或临时收缩),
//写入接口(PatientAdd/RecordAdd/RecordInsert)一律按这两个上限拦截, 超出返回TREATMENT_EPROM_ERR_FULL
//说明: 上限超过物理容量/块内槽位数时, 由 treatmentEpromPatientLimit()/treatmentEpromRecordLimit() 自动钳位
#ifndef CONFIG_EPROM_TREATMENT_PATIENT_LIMIT
#define CONFIG_EPROM_TREATMENT_PATIENT_LIMIT							CONFIG_EPROM_TREATMENT_PATIENT_MAX//病历人数上限: 默认用满病历区物理容量
#endif
#ifndef CONFIG_EPROM_TREATMENT_RECORD_LIMIT
#define CONFIG_EPROM_TREATMENT_RECORD_LIMIT								CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT//每人病历条数上限: 默认用满块内槽位
#endif

//边界配置自检: 宏已全部是纯整数表达式, 可编译期判定(配置越界直接报错, 不再依赖运行时钳位)
#if ((CONFIG_EPROM_TREATMENT_PATIENT_LIMIT < 1) || (CONFIG_EPROM_TREATMENT_RECORD_LIMIT < 1))
	#error "病历人数上限与每人病历条数上限都必须大于0"
#endif
#if (CONFIG_EPROM_TREATMENT_PATIENT_LIMIT > CONFIG_EPROM_TREATMENT_PATIENT_MAX)
	#error "CONFIG_EPROM_TREATMENT_PATIENT_LIMIT 超过病历区物理容量: 请调小人数上限或扩大病历区"
#endif
#if (CONFIG_EPROM_TREATMENT_RECORD_LIMIT > CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT)
	#error "CONFIG_EPROM_TREATMENT_RECORD_LIMIT 超过块内病历槽位数: 请调小条数上限或增大 CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT"
#endif

//落盘格式自检(全部是纯整数表达式, 编译期即可判定)
#if (CONFIG_EPROM_TREATMENT_HEAD_BYTES != (CONFIG_EPROM_TREATMENT_OFF_RECORD)) || ((CONFIG_EPROM_TREATMENT_OFF_RECORD & 3u) != 0u)
	#error "病历块头字节数与病历数组偏移不一致, 或病历数组起点未4字节对齐: 请核对 CONFIG_EPROM_TREATMENT_OFF_RECORD"
#endif
#if (CONFIG_EPROM_TREATMENT_REC_OFF_PROTOCOL != (CONFIG_EPROM_TREATMENT_RECORD_BYTES - 1u))
	#error "病历字段偏移与单条病历字节数不一致: 请核对 CONFIG_EPROM_TREATMENT_REC_OFF_* 与 CONFIG_EPROM_TREATMENT_RECORD_BYTES"
#endif
#if ((CONFIG_EPROM_TREATMENT_OFF_NAME + CONFIG_EPROM_TREATMENT_NAME_BYTES) != CONFIG_EPROM_TREATMENT_OFF_PATIENT_ID) \
	|| ((CONFIG_EPROM_TREATMENT_OFF_PATIENT_ID + 2u) != CONFIG_EPROM_TREATMENT_OFF_AGE) \
	|| ((CONFIG_EPROM_TREATMENT_OFF_AGE + 1u) != CONFIG_EPROM_TREATMENT_OFF_GENDER) \
	|| ((CONFIG_EPROM_TREATMENT_OFF_GENDER + 1u) != CONFIG_EPROM_TREATMENT_OFF_RECORD_COUNT) \
	|| ((CONFIG_EPROM_TREATMENT_OFF_RECORD_COUNT + 1u) != CONFIG_EPROM_TREATMENT_HEAD_BYTES)
	#error "患者块头字段未紧凑填满24B(存在对齐浪费): 请核对 CONFIG_EPROM_TREATMENT_OFF_* 与 NAME_BYTES"
#endif
#if (CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT > 255)
	#error "每位患者病历条数超过255: 块头 recordCount 为1字节, 无法表示"
#endif
//容量自检: 区域至少要能放下16位患者, 否则说明分区或块大小配置有误
#if (CONFIG_EPROM_TREATMENT_SIZE < (CONFIG_EPROM_TREATMENT_PATIENT_BYTES * 16u))
	#error "EPROM 病历区块容量不足: 请缩减 CONFIG_EPROM_TREATMENT_RECORDS_PER_PATIENT 或扩大病历区块"
#endif

typedef enum{
	TREATMENT_EPROM_OK = 0,//成功
	TREATMENT_EPROM_ERR_PARAM,//参数错误(索引越界/指针为空)
	TREATMENT_EPROM_ERR_FULL,//患者表已满或该患者病历已满
	TREATMENT_EPROM_ERR_EMPTY,//索引处无患者/无病历
	TREATMENT_EPROM_ERR_IO//EPROM读写失败
}treatmentEpromErr_t;
/*****************************************************************************/
//容量/计数
uint16_t treatmentEpromPatientCapacity(void);//获取病历区可容纳患者数量(物理容量)
uint16_t treatmentEpromPatientLimit(void);//获取应用层患者人数上限(<=物理容量, 写入按此拦截)
uint8_t treatmentEpromRecordLimit(void);//获取应用层每人病历条数上限(<=块内槽位数, 写入按此拦截)
uint16_t treatmentEpromPatientCount(void);//获取当前有效患者数量(紧凑存储:遇空块即止)
uint16_t treatmentEpromFlatRecordCount(void);//获取全部病历总条数(界面扁平浏览用)
/*****************************************************************************/
//患者级
uint16_t treatmentEpromNextPatientId(void);//生成新患者ID(现有最大ID+1, 无有效患者时返回1; 空间用尽返回0xFFFF)
treatmentEpromErr_t treatmentEpromPatientFind(uint16_t patientId, uint16_t *outPatientIndex);//按患者ID查找患者块索引
uint16_t treatmentEpromPatientIdAt(uint16_t patientIndex);//只读取患者ID(不占144B栈, 无效返回0)
treatmentEpromErr_t treatmentEpromPatientGet(uint16_t patientIndex, treatmentPatient_t *out);//按患者块索引读取患者档案
treatmentEpromErr_t treatmentEpromPatientAdd(const treatmentLog_t *session, uint16_t *outPatientIndex);//新建患者档案(仅患者信息, 暂无病历)
treatmentEpromErr_t treatmentEpromPatientUpdate(uint16_t patientIndex, const treatmentPatient_t *patient);//覆盖更新患者信息(病历条数保持原值)
treatmentEpromErr_t treatmentEpromPatientDelete(uint16_t patientIndex);//删除整个患者档案(后续患者块前移)
/*****************************************************************************/
//病历级(操作患者块内部的病历数组)
uint8_t treatmentEpromRecordCount(uint16_t patientIndex);//读取该患者已保存病历条数(异常返回0)
treatmentEpromErr_t treatmentEpromRecordAdd(uint16_t patientIndex, const treatmentRecord_t *rec, uint8_t *outRecIndex);//末尾追加病历(满后按CONFIG_EPROM_TREATMENT_OVERWRITE_OLDEST策略处理)
treatmentEpromErr_t treatmentEpromRecordInsert(uint16_t patientIndex, uint8_t recIndex, const treatmentRecord_t *rec, uint8_t *outRecIndex);//插入病历到指定位置(后续病历后移)
treatmentEpromErr_t treatmentEpromRecordGet(uint16_t patientIndex, uint8_t recIndex, treatmentRecord_t *out);//按位置读取病历
treatmentEpromErr_t treatmentEpromRecordUpdate(uint16_t patientIndex, uint8_t recIndex, const treatmentRecord_t *rec);//覆盖更新病历
treatmentEpromErr_t treatmentEpromRecordDelete(uint16_t patientIndex, uint8_t recIndex);//删除病历(后续病历前移, 不删患者块)
/*****************************************************************************/
//会话保存(病历储存页"保存"按钮): patientId=0新建患者, patientId非0追加到该患者
treatmentEpromErr_t treatmentEpromSaveSession(const treatmentLog_t *session, uint16_t *outPatientIndex, uint8_t *outRecIndex);
/*****************************************************************************/
//扁平视图(界面按"病历"顺序浏览): 把(患者,病历)两级结构摊平成一维索引, 顺序=患者块顺序×病历顺序
treatmentEpromErr_t treatmentEpromFlatLocate(uint16_t flatIndex, uint16_t *outPatientIndex, uint8_t *outRecIndex);
/*****************************************************************************/
treatmentEpromErr_t treatmentEpromClear(void);//清空整个病历区块(全部写成0xFF空块标记)
typedef void (*treatmentEpromVisitFn)(uint16_t patientIndex, const treatmentPatient_t *patient);//遍历回调函数指针类型
void treatmentEpromTraverse(treatmentEpromVisitFn fn);//遍历所有有效患者档案(索引升序)
/*****************************************************************************/
#endif
/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
