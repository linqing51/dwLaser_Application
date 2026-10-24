#include "treatment.h"
/*****************************************************************************/
treatmentLog_t treatmentLog;//患者记录全局变量
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
/*****************************************************************************/
#if defined(CONFIG_EPROM_TREATMENT_START)
//EPROM治疗记录历史病历区块管理(多副本病历,按索引定位,id自动生成=索引位置,紧凑存储无空洞)
/*****************************************************************************/
//计算指定索引病历槽位在EPROM中的起始地址
static uint32_t treatmentEpromSlotAddr(uint16_t index){
	return (uint32_t)CONFIG_EPROM_TREATMENT_START + (uint32_t)index * CONFIG_EPROM_TREATMENT_RECORD_SIZE;
}

//将指定槽位整块写成0xFF(空病历标记)
static HAL_StatusTypeDef treatmentEpromClearSlot(uint32_t addr){
	uint8_t ffBuf[CONFIG_EPROM_TREATMENT_RECORD_SIZE];
	memset(ffBuf, 0xFF, sizeof(ffBuf));
	return epromWrite(addr, ffBuf, sizeof(ffBuf));
}

uint16_t treatmentEpromGetCapacity(void){//获取区块可容纳病历数量上限(按区块容量自动计算)
	return (uint16_t)CONFIG_EPROM_TREATMENT_RECORD_MAX;
}

uint16_t treatmentEpromGetCount(void){//获取当前有效病历数量(紧凑存储:遇空槽即止)
	uint16_t count = 0;
	treatmentLog_t tmp;
	for(uint16_t i = 0; i < treatmentEpromGetCapacity(); i++){
		if(epromRead(treatmentEpromSlotAddr(i), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			break;
		}
		if(tmp.id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY){
			break;
		}
		count++;
	}
	return count;
}

treatmentEpromErr_t treatmentEpromGet(uint16_t index, treatmentLog_t *out){//按索引读取病历
	if((out == NULL) || (index >= treatmentEpromGetCapacity())){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	treatmentLog_t tmp;
	if(epromRead(treatmentEpromSlotAddr(index), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	if(tmp.id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY){
		return TREATMENT_EPROM_ERR_EMPTY;
	}
	*out = tmp;
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromAdd(const treatmentLog_t *log){//末尾追加病历(id自动=索引位置)
	if(log == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	uint16_t count = treatmentEpromGetCount();
	if(count >= treatmentEpromGetCapacity()){//自动判断容量限制
		return TREATMENT_EPROM_ERR_FULL;
	}
	treatmentLog_t rec = *log;
	rec.id = count;//程序自动生成id=索引位置
	if(epromWrite(treatmentEpromSlotAddr(count), (uint8_t*)&rec, sizeof(rec)) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromSaveCurrent(void){//储存当前治疗记录到区块末尾
	return treatmentEpromAdd(&treatmentLog);
}

treatmentEpromErr_t treatmentEpromInsert(uint16_t index, const treatmentLog_t *log){//插入病历到指定索引(后续病历后移并更新id)
	if(log == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	uint16_t count = treatmentEpromGetCount();
	if(index > count){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	if(count >= treatmentEpromGetCapacity()){//自动判断容量限制
		return TREATMENT_EPROM_ERR_FULL;
	}
	for(uint16_t i = count; i > index; i--){//从末尾向前逐个后移
		treatmentLog_t tmp;
		if(epromRead(treatmentEpromSlotAddr(i - 1), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		tmp.id = i;//id自动更新=新索引位置
		if(epromWrite(treatmentEpromSlotAddr(i), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
	}
	treatmentLog_t rec = *log;
	rec.id = index;//程序自动生成id=索引位置
	if(epromWrite(treatmentEpromSlotAddr(index), (uint8_t*)&rec, sizeof(rec)) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromDelete(uint16_t index){//删除指定索引病历(后续病历前移并更新id)
	uint16_t count = treatmentEpromGetCount();
	if(index >= count){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	for(uint16_t i = index + 1; i < count; i++){//后续病历逐个前移
		treatmentLog_t tmp;
		if(epromRead(treatmentEpromSlotAddr(i), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		tmp.id = i - 1;//id自动更新=新索引位置
		if(epromWrite(treatmentEpromSlotAddr(i - 1), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
	}
	if(treatmentEpromClearSlot(treatmentEpromSlotAddr(count - 1)) != HAL_OK){//清空原末尾槽位
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromUpdate(uint16_t index, const treatmentLog_t *log){//覆盖更新指定索引病历(id保持=索引位置)
	if(log == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	uint16_t count = treatmentEpromGetCount();
	if(index >= count){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	treatmentLog_t rec = *log;
	rec.id = index;//id保持=索引位置
	if(epromWrite(treatmentEpromSlotAddr(index), (uint8_t*)&rec, sizeof(rec)) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromClear(void){//清空整个治疗记录区块
	for(uint16_t i = 0; i < treatmentEpromGetCapacity(); i++){
		if(treatmentEpromClearSlot(treatmentEpromSlotAddr(i)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
	}
	return TREATMENT_EPROM_OK;
}

void treatmentEpromTraverse(treatmentEpromVisitFn fn){//遍历所有有效病历(索引升序)
	if(fn == NULL){
		return;
	}
	treatmentLog_t tmp;
	for(uint16_t i = 0; i < treatmentEpromGetCapacity(); i++){
		if(epromRead(treatmentEpromSlotAddr(i), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			break;
		}
		if(tmp.id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY){
			break;//紧凑存储:遇空槽即结束
		}
		fn(i, &tmp);
	}
}
#endif
/*****************************************************************************/
/*****************************************************************************/

