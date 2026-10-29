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
extern uint8_t treatmentLogValid;//当前治疗记录有效性:任意一次激光发射后置1,上电复位/保存病历后清0
const char* treatmentProtocolName(PROTOCOL_ENUM protocol);//治疗方案名称映射
const char* treatmentLaserWaveName(LASER_WAVE_ENUM wave);//激光波长名称映射
/*****************************************************************************/
#if defined(CONFIG_EPROM_TREATMENT_START)
//EPROM治疗记录历史病历区块管理:多个treatmentLog_t结构体副本,按索引定位,id自动生成=索引位置
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
treatmentEpromErr_t treatmentEpromAdd(const treatmentLog_t *log);//末尾追加病历(id自动=索引位置)
treatmentEpromErr_t treatmentEpromSaveCurrent(void);//储存当前treatmentLog病历到区块末尾
treatmentEpromErr_t treatmentEpromInsert(uint16_t index, const treatmentLog_t *log);//插入病历到指定索引(后续病历后移,id自动更新)
treatmentEpromErr_t treatmentEpromDelete(uint16_t index);//删除指定索引病历(后续病历前移,id自动更新)
treatmentEpromErr_t treatmentEpromUpdate(uint16_t index, const treatmentLog_t *log);//覆盖更新指定索引病历(id保持=索引位置)
treatmentEpromErr_t treatmentEpromGet(uint16_t index, treatmentLog_t *out);//按索引读取病历
treatmentEpromErr_t treatmentEpromClear(void);//清空整个治疗记录区块
typedef void (*treatmentEpromVisitFn)(uint16_t index, const treatmentLog_t *log);//遍历回调函数指针类型
void treatmentEpromTraverse(treatmentEpromVisitFn fn);//遍历所有有效病历(索引升序)
#endif
/******************************************************************************/
#ifdef __cplusplus
}
#endif
#endif





