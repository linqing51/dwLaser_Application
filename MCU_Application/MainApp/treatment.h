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
typedef struct{//定义患者记录
	uint16_t id;//患者ID
	uint8_t age;//患者年龄
	int16_t laserPower;//激光功率	
	int32_t releaseEnergy; //已发射能量 单位焦耳
	int32_t releaseTime;//发射时间文本 单位秒
	char name[16];//患者名字
	GENDER_ENUM gender;//患者性别
	LASER_WAVE_ENUM laserWave;//选择的波长
	PROTOCOL_ENUM protocol;//选择的预设方案
}treatmentLog_t;
/*****************************************************************************/
extern treatmentLog_t treatmentLog;
/*****************************************************************************/
const char* treatmentProtocolName(PROTOCOL_ENUM protocol);//治疗方案名称映射
const char* treatmentLaserWaveName(LASER_WAVE_ENUM wave);//激光波长名称映射
/*****************************************************************************/
#if defined(CONFIG_EPROM_TREATMENT_START)
//EPROM治疗记录历史病历区块管理:多个treatmentLog_t结构体副本,按索引定位,id自动分配(现有最大ID+1)且与患者绑定
#define CONFIG_EPROM_TREATMENT_RECORD_SIZE								(sizeof(treatmentLog_t))//单条病历结构体字节数
#define CONFIG_EPROM_TREATMENT_RECORD_MAX									(CONFIG_EPROM_TREATMENT_SIZE / CONFIG_EPROM_TREATMENT_RECORD_SIZE)//区块可容纳病历数量上限(按区块容量自动计算)
#define CONFIG_EPROM_TREATMENT_SLOT_EMPTY									0xFFFF//空槽位标记(id=0xFFFF表示该槽无病历)

typedef enum{
	TREATMENT_EPROM_OK = 0,//成功
	TREATMENT_EPROM_ERR_PARAM,//参数错误(索引越界/指针为空)
	TREATMENT_EPROM_ERR_FULL,//区块已满
	TREATMENT_EPROM_ERR_EMPTY,//索引处无病历
	TREATMENT_EPROM_ERR_IO//EPROM读写失败
}treatmentEpromErr_t;

uint16_t treatmentEpromGetCapacity(void);//获取区块可容纳病历数量上限
uint16_t treatmentEpromGetCount(void);//获取当前有效病历数量
treatmentEpromErr_t treatmentEpromAdd(const treatmentLog_t *log);//末尾追加病历(自动分配新患者ID)
treatmentEpromErr_t treatmentEpromWriteAt(uint16_t index, const treatmentLog_t *log);//按索引直接写槽位(id由调用方按ID规则给出;不扫描数量,供批量填充使用)
treatmentEpromErr_t treatmentEpromSaveCurrent(void);//储存当前treatmentLog病历到区块末尾
treatmentEpromErr_t treatmentEpromInsert(uint16_t index, const treatmentLog_t *log);//插入病历到指定索引(后续病历后移,各患者ID保持不变)
treatmentEpromErr_t treatmentEpromDelete(uint16_t index);//删除指定索引病历(后续病历前移,各患者ID保持不变)
treatmentEpromErr_t treatmentEpromUpdate(uint16_t index, const treatmentLog_t *log);//覆盖更新指定索引病历(保留原患者ID)
treatmentEpromErr_t treatmentEpromGet(uint16_t index, treatmentLog_t *out);//按索引读取病历
treatmentEpromErr_t treatmentEpromClear(void);//清空整个治疗记录区块
uint32_t treatmentEpromCalcFwCrc(void);//计算当前APP内部Flash固件区CRC32(固件变化清空判据,与bootloader同算法)
typedef void (*treatmentEpromVisitFn)(uint16_t index, const treatmentLog_t *log);//遍历回调函数指针类型
void treatmentEpromTraverse(treatmentEpromVisitFn fn);//遍历所有有效病历(索引升序)
/*****************************************************************************/
//虚拟病历生成默认参数(机型配置未定义时取此值)
#ifndef CONFIG_TREATMENT_DEMO_VERBOSE
#define CONFIG_TREATMENT_DEMO_VERBOSE										0//串口输出生成摘要(1=输出)
#endif
#ifndef CONFIG_TREATMENT_DEMO_COUNT
#define CONFIG_TREATMENT_DEMO_COUNT											200//按钮触发生成默认数量(0=填满整个区块)
#endif
#ifndef CONFIG_TREATMENT_DEMO_SEED
#define CONFIG_TREATMENT_DEMO_SEED											0//按钮触发默认种子(0=按运行时刻)
#endif
//虚拟病历生成(测试数据填充):模块常驻编译;直接写入本区块,各子项按真实治疗场景自洽模拟
//  - 方案按术式占比抽取;妇科只出女性,牙科/耳鼻喉年龄下探到儿童,年龄三角分布集中中年
//  - 波长为本机型治疗主波长(635nm仅作指示光,不生成治疗记录)
//  - 功率按术式区间抽取,并按CONFIG_MAX_LASER_POWER_CH0钳位
//  - 能量=功率×时间×出光占空比±4%抖动,保证与功率/时间/脉冲模式自洽
//  - 姓名为英文/拼音"姓 名",男女分池,最长11字节(适配name[16])
//  - id按ID规则分配(现有最大ID+1), 与患者绑定, 插入/删除不重新编号
typedef enum{
	TREATMENT_DEMO_OK = 0,//成功(写入并回读校验通过)
	TREATMENT_DEMO_ERR_PARAM,//参数错误(数量为0/区块容量为0)
	TREATMENT_DEMO_ERR_IO,//EPROM读写失败
	TREATMENT_DEMO_ERR_FULL,//追加模式下区块已满
	TREATMENT_DEMO_ERR_VERIFY//回读校验不一致
}treatmentDemoErr_t;

//生成虚拟病历并写入EPROM
//count: 须>0, 超出区块剩余容量按容量截断
//seed: 0=按HAL_GetTick取; 同一种子生成的数据完全一致
//clearFirst: 1=先清空整个区块再填充; 0=追加到现有病历末尾
//written: 输出实际写入条数, 可传NULL
treatmentDemoErr_t treatmentDemoGenerate(uint16_t count, uint32_t seed, uint8_t clearFirst, uint16_t *written);
#endif
/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif





