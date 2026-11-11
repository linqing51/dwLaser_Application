/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "treatment.h"
/*****************************************************************************/
treatmentLog_t treatmentLog;//患者记录全局变量
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

//编译期容量断言: 容量×单条字节数不得超出区块字节数(不成立则编译报错, 防止结构调整或区块配置改动后越界写)
typedef char treatmentEpromCapacityAssert[
	(((uint32_t)CONFIG_EPROM_TREATMENT_RECORD_MAX * (uint32_t)CONFIG_EPROM_TREATMENT_RECORD_SIZE)
	 <= (uint32_t)CONFIG_EPROM_TREATMENT_SIZE) ? 1 : -1];

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

//分配新患者ID: 取现有病历中最大ID加1(空区块从1开始), 对应文件头ID编码规则"AR + 空格 + 至少4位递增数字"
//ID与患者绑定: 插入/删除只移动记录所在槽位, 不重新编号已有患者
static uint16_t treatmentEpromNextId(void){
	uint16_t count = treatmentEpromGetCount();
	uint16_t maxId = 0U;
	treatmentLog_t tmp;
	for(uint16_t i = 0; i < count; i++){
		if(epromRead(treatmentEpromSlotAddr(i), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			break;
		}
		if(tmp.id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY){//紧凑存储: 遇空槽即结束
			break;
		}
		if(tmp.id > maxId){
			maxId = tmp.id;
		}
	}
	if(maxId >= (uint16_t)(CONFIG_EPROM_TREATMENT_SLOT_EMPTY - 1U)){
		return CONFIG_EPROM_TREATMENT_SLOT_EMPTY;//ID号已用尽
	}
	return (uint16_t)(maxId + 1U);
}

treatmentEpromErr_t treatmentEpromAdd(const treatmentLog_t *log){//末尾追加病历(自动分配新患者ID)
	if(log == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	uint16_t count = treatmentEpromGetCount();
	if(count >= treatmentEpromGetCapacity()){//自动判断容量限制
		return TREATMENT_EPROM_ERR_FULL;
	}
	treatmentLog_t rec = *log;
	uint16_t newId = treatmentEpromNextId();
	if(newId == CONFIG_EPROM_TREATMENT_SLOT_EMPTY){
		return TREATMENT_EPROM_ERR_FULL;//ID号已用尽
	}
	rec.id = newId;//新患者分配新ID, 与患者绑定
	if(epromWrite(treatmentEpromSlotAddr(count), (uint8_t*)&rec, sizeof(rec)) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	NVRAM0[DM_TREATMENT_NUM] = (int16_t)(count + 1);//同步有效病历数量
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromSaveCurrent(void){//储存当前治疗记录到区块末尾
	return treatmentEpromAdd(&treatmentLog);
}

treatmentEpromErr_t treatmentEpromWriteAt(uint16_t index, const treatmentLog_t *log){//按索引直接写槽位(id由调用方按ID规则给出)
//与treatmentEpromAdd的区别: 不扫描现有数量、不更新DM_TREATMENT_NUM, 每条写入耗时恒定O(1),
//用于虚拟病历填充/区块镜像恢复等已知目标索引的一次性批量写入; 调用方负责先清空区块并同步计数。
	if(log == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	if(index >= treatmentEpromGetCapacity()){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	treatmentLog_t rec = *log;
	if(rec.id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY){//空槽标记不是合法患者ID
		return TREATMENT_EPROM_ERR_PARAM;
	}
	if(epromWrite(treatmentEpromSlotAddr(index), (uint8_t*)&rec, sizeof(rec)) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromInsert(uint16_t index, const treatmentLog_t *log){//插入病历到指定索引(后续病历后移, 各患者ID保持不变)
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
	uint16_t newId = treatmentEpromNextId();
	if(newId == CONFIG_EPROM_TREATMENT_SLOT_EMPTY){
		return TREATMENT_EPROM_ERR_FULL;//ID号已用尽
	}
	for(uint16_t i = count; i > index; i--){//从末尾向前逐个后移
		treatmentLog_t tmp;
		if(epromRead(treatmentEpromSlotAddr(i - 1), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		//后移时保持原患者ID不变
		if(epromWrite(treatmentEpromSlotAddr(i), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
	}
	treatmentLog_t rec = *log;
	rec.id = newId;//插入的是新患者, 只有它分配新ID
	if(epromWrite(treatmentEpromSlotAddr(index), (uint8_t*)&rec, sizeof(rec)) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	NVRAM0[DM_TREATMENT_NUM] = (int16_t)(count + 1);//插入后有效病历数量+1
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromDelete(uint16_t index){//删除指定索引病历(后续病历前移, 各患者ID保持不变)
	uint16_t count = treatmentEpromGetCount();
	if(index >= count){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	for(uint16_t i = index + 1; i < count; i++){//后续病历逐个前移
		treatmentLog_t tmp;
		if(epromRead(treatmentEpromSlotAddr(i), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
		//前移时保持原患者ID不变(否则ID会跟着位置跑, 和姓名错位)
		if(epromWrite(treatmentEpromSlotAddr(i - 1), (uint8_t*)&tmp, sizeof(tmp)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;
		}
	}
	if(treatmentEpromClearSlot(treatmentEpromSlotAddr(count - 1)) != HAL_OK){//清空原末尾槽位
		return TREATMENT_EPROM_ERR_IO;
	}
	NVRAM0[DM_TREATMENT_NUM] = (int16_t)(count - 1);//删除后有效病历数量-1
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromUpdate(uint16_t index, const treatmentLog_t *log){//覆盖更新指定索引病历(保留原患者ID, 只改其余字段)
	if(log == NULL){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	uint16_t count = treatmentEpromGetCount();
	if(index >= count){
		return TREATMENT_EPROM_ERR_PARAM;
	}
	treatmentLog_t rec = *log;
	treatmentLog_t old;
	if(epromRead(treatmentEpromSlotAddr(index), (uint8_t*)&old, sizeof(old)) != HAL_OK){//读出原记录以保留其ID
		return TREATMENT_EPROM_ERR_IO;
	}
	rec.id = old.id;//ID与患者绑定, 更新资料不换ID
	if(epromWrite(treatmentEpromSlotAddr(index), (uint8_t*)&rec, sizeof(rec)) != HAL_OK){
		return TREATMENT_EPROM_ERR_IO;
	}
	return TREATMENT_EPROM_OK;
}

treatmentEpromErr_t treatmentEpromClear(void){//清空整个治疗记录区块
	for(uint16_t i = 0; i < treatmentEpromGetCapacity(); i++){
		if(treatmentEpromClearSlot(treatmentEpromSlotAddr(i)) != HAL_OK){
			return TREATMENT_EPROM_ERR_IO;//清空失败:保留原数量,不更新DM_TREATMENT_NUM
		}
	}
	NVRAM0[DM_TREATMENT_NUM] = 0;//清空后有效病历数量为0
	return TREATMENT_EPROM_OK;
}

uint32_t treatmentEpromCalcFwCrc(void){//计算当前APP内部Flash固件区CRC32(硬件CRC,与bootloader getOriginAppCrc同算法同范围)
	uint32_t crc32;
	crc32Clear();
	for(uint32_t addr = APPLICATION_FLASH_START_ADDRESS; addr < APPLICATION_FLASH_END_ADDRESS; addr++){
		crc32 = crc32CalculateAdd(*(__IO uint8_t*)addr);
	}
	return crc32;
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
/*****************************************************************************/
//患者 ID 的编码规则是：
//AR + 一个空格 + 至少 4 位的递增数字，例如：AR 0001、AR 0002、AR 0011。
//自动生成、不可手动修改：取现有患者 ID 中最大的数字加 1，不足 4 位时前面补零。
//新患者分配新 ID：目前 Demo 已有编号到 AR 0010，所以下一位是 AR 0011。
//已有患者继续使用原 ID：再次治疗时追加治疗记录，不重新编号。
//同名不代表同一患者：选择已有患者就复用其 ID；选择「Create New Patient」则生成新 ID。

/*****************************************************************************/
//虚拟病历生成(测试数据填充): 按真实治疗场景模拟各子项, 用于灌入测试数据/演示数据。
//术式占比、性别年龄、波长、功率、时间、能量、姓名规则见文件末尾说明。
//模块常驻编译(无开关宏); 由触摸屏诊断页按钮GDDC_PAGE_DISGNOSIS_KEY_AUTOFILL触发生成。
/*****************************************************************************/
/*****************************************************************************/
//术式画像表: 方案/占比(%)/最小年龄/最大年龄/女性占比(%)/最小功率(W)/最大功率(W)/最短时间(s)/最长时间(s)/出光占空比(%)
//占空比: 100=连续出光(CW), 其余为脉冲模式平均出光占比, 用于把功率/时间换算成自洽的能量
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
	{ePhlebology,   30, 28, 78,  55,  6, 13,  120,  600, 100},//大隐静脉腔内激光闭合: 连续出光/中等功率/数分钟
	{eProctology,   12, 22, 80,  45,  8, 15,   60,  360,  60},//肛肠: 较高功率脉冲
	{eGynecology,   12, 20, 58, 100,  4, 10,   60,  420,  75},//妇科: 仅女性
	{eENT,           8,  5, 70,  50,  3,  8,   30,  180,  50},//耳鼻喉: 含儿童/低功率短时
	{eNeurosurgery,  2, 18, 72,  50,  2,  6,   60,  300,  40},//神经外科: 低功率短脉冲
	{eDermatology,  14, 14, 68,  65,  1,  8,   30,  300,  50},//皮肤: 低功率脉冲
	{eLiposuction,   8, 22, 55,  80,  8, 15,  300, 1200, 100},//吸脂: 高功率长时间, 能量最大
	{eDentistry,     6,  8, 75,  55,  1,  4,   20,  120,  30},//牙科: 最低功率/最短时间
	{eTherapy,       8, 18, 78,  50,  2, 10,   60,  600,  60} //理疗: 中等功率
};
#define DEMO_PROFILE_NUM														(sizeof(demoProfileTable) / sizeof(demoProfileTable[0]))
#define DEMO_PROFILE_WEIGHT_TOTAL											100
/*****************************************************************************/
//姓名池(英文/拼音): 姓最长5字节, 名最长5字节, "姓 名"最长11字节, 适配name[16]
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
#define DEMO_SURNAME_NUM														(sizeof(demoSurnamePool) / sizeof(demoSurnamePool[0]))
#define DEMO_GIVEN_MALE_NUM													(sizeof(demoGivenMalePool) / sizeof(demoGivenMalePool[0]))
#define DEMO_GIVEN_FEMALE_NUM												(sizeof(demoGivenFemalePool) / sizeof(demoGivenFemalePool[0]))
/*****************************************************************************/
//随机源: xorshift32, 状态局部保存, 同一种子可完全复现, 不依赖库rand()
static uint32_t demoRandState = 1U;

static void demoRandSeed(uint32_t seed){
	if(seed == 0U){//未指定种子:按运行时刻取, 保证每次生成数据不同
		seed = (uint32_t)HAL_GetTick() ^ 0x5A5A5A5AU;
	}
	demoRandState = (seed == 0U) ? 1U : seed;
}

static uint32_t demoRandNext(void){
	uint32_t x = demoRandState;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	demoRandState = x;
	return x;
}

static uint32_t demoRandRange(uint32_t min, uint32_t max){//闭区间均匀抽取
	if(max <= min){
		return min;
	}
	return min + (demoRandNext() % (max - min + 1U));
}

static uint32_t demoRandTri(uint32_t min, uint32_t max){//三角分布:两次均匀抽取取均值, 概率向区间中部集中
	if(max <= min){
		return min;
	}
	return (demoRandRange(min, max) + demoRandRange(min, max) + 1U) / 2U;
}
/*****************************************************************************/
static int16_t demoPowerCap(void){//本机型治疗通道功率上限(W):配置单位为0.1W
#if defined(CONFIG_MAX_LASER_POWER_CH0)
	int16_t cap = (int16_t)(CONFIG_MAX_LASER_POWER_CH0 / 10);
	if(cap < 1){
		cap = 1;
	}
	return cap;
#else
	return 15;
#endif
}

static LASER_WAVE_ENUM demoPrimaryWave(void){//本机型治疗主波长(与HMI READY页通道波长映射一致)
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

static const demoProfile_t* demoPickProfile(void){//按占比抽取术式
	uint32_t r = demoRandRange(1U, (uint32_t)DEMO_PROFILE_WEIGHT_TOTAL);
	uint32_t acc = 0;
	for(uint16_t i = 0; i < (uint16_t)DEMO_PROFILE_NUM; i++){
		acc += demoProfileTable[i].weight;
		if(r <= acc){
			return &demoProfileTable[i];
		}
	}
	return &demoProfileTable[DEMO_PROFILE_NUM - 1U];
}
/*****************************************************************************/
//按画像生成单条病历(id由生成器按ID规则分配)
static void demoBuildRecord(uint16_t id, treatmentLog_t *rec){
	const demoProfile_t *profile;
	int16_t power, powerCap;
	uint32_t timeSec, energy, surnameIdx, givenIdx;
	uint8_t female;

	profile = demoPickProfile();
	female = (demoRandRange(0U, 99U) < (uint32_t)profile->femaleRate) ? 1U : 0U;

	memset(rec, 0x0, sizeof(treatmentLog_t));
	rec->id = id;
	rec->gender = (female != 0U) ? FEMALE : MALE;
	rec->age = (uint8_t)demoRandTri(profile->ageMin, profile->ageMax);
	rec->protocol = profile->protocol;
	rec->laserWave = demoPrimaryWave();

	powerCap = demoPowerCap();
	power = (int16_t)demoRandTri((uint32_t)profile->powerMin, (uint32_t)profile->powerMax);
	if(power > powerCap){//钳位到硬件上限
		power = powerCap;
	}
	if(power < 1){
		power = 1;
	}
	rec->laserPower = power;

	timeSec = demoRandTri(profile->timeMin, profile->timeMax);
	rec->releaseTime = (int32_t)timeSec;

	energy = (uint32_t)power * timeSec * (uint32_t)profile->duty / 100U;//功率×时间×出光占空比
	energy = energy * demoRandRange(96U, 104U) / 100U;//±4%抖动, 模拟能量计量取整误差
	if(energy < 1U){
		energy = 1U;
	}
	rec->releaseEnergy = (int32_t)energy;

	surnameIdx = demoRandRange(0U, (uint32_t)DEMO_SURNAME_NUM - 1U);
	if(female != 0U){
		givenIdx = demoRandRange(0U, (uint32_t)DEMO_GIVEN_FEMALE_NUM - 1U);
		sprintf(rec->name, "%s %s", demoSurnamePool[surnameIdx], demoGivenFemalePool[givenIdx]);
	}
	else{
		givenIdx = demoRandRange(0U, (uint32_t)DEMO_GIVEN_MALE_NUM - 1U);
		sprintf(rec->name, "%s %s", demoSurnamePool[surnameIdx], demoGivenMalePool[givenIdx]);
	}
}

static uint8_t demoNameValid(const char *name){//姓名须在字段内正常结束且非空
	for(uint8_t i = 0; i < (uint8_t)sizeof(((treatmentLog_t*)0)->name); i++){
		if(name[i] == '\0'){
			return (i > 0U) ? 1U : 0U;
		}
	}
	return 0U;
}

static uint8_t demoRecordValid(const treatmentLog_t *rec){//单条病历字段合法性
	int32_t maxEnergy;

	if((rec->id == 0U) || (rec->id == CONFIG_EPROM_TREATMENT_SLOT_EMPTY)){//ID须为有效患者编号
		return 0U;
	}
	if((rec->gender != MALE) && (rec->gender != FEMALE)){
		return 0U;
	}
	if((rec->age == 0U) || (rec->age > 110U)){
		return 0U;
	}
	if((rec->laserPower < 1) || (rec->laserPower > demoPowerCap())){
		return 0U;
	}
	if(rec->releaseTime <= 0){
		return 0U;
	}
	if((rec->laserWave < WAVE_450) || (rec->laserWave > WAVE_1470_980)){
		return 0U;
	}
	if(rec->protocol > eCustiom){//枚举从ePhlebology(0)开始, 只校验上界
		return 0U;
	}
	maxEnergy = (int32_t)rec->laserPower * rec->releaseTime * 110 / 100;//上限含±4%抖动余量
	if((rec->releaseEnergy <= 0) || (rec->releaseEnergy > maxEnergy)){//能量须与功率/时间自洽
		return 0U;
	}
	if(demoNameValid(rec->name) == 0U){
		return 0U;
	}
	return 1U;
}

static treatmentDemoErr_t demoVerify(uint16_t start, uint16_t count){//抽样回读校验(首条/中间/末条)
	uint16_t sample[3];
	uint16_t sampleNum = 0;
	treatmentLog_t rec;

	if(count == 0U){
		return TREATMENT_DEMO_OK;
	}
	sample[sampleNum++] = start;
	if(count > 2U){
		sample[sampleNum++] = (uint16_t)(start + count / 2U);
	}
	sample[sampleNum++] = (uint16_t)(start + count - 1U);

	for(uint16_t i = 0; i < sampleNum; i++){
		if(treatmentEpromGet(sample[i], &rec) != TREATMENT_EPROM_OK){
			return TREATMENT_DEMO_ERR_VERIFY;
		}
		if(demoRecordValid(&rec) == 0U){
			return TREATMENT_DEMO_ERR_VERIFY;
		}
	}
	return TREATMENT_DEMO_OK;
}
/*****************************************************************************/
treatmentDemoErr_t treatmentDemoGenerate(uint16_t count, uint32_t seed, uint8_t clearFirst, uint16_t *written){
	uint16_t capacity, start, target, idBase;
	treatmentEpromErr_t err;
	uint32_t tickStart;

	if(written != NULL){
		*written = 0U;
	}
	if(count == 0U){
		return TREATMENT_DEMO_ERR_PARAM;
	}
	capacity = treatmentEpromGetCapacity();
	if(capacity == 0U){
		return TREATMENT_DEMO_ERR_PARAM;
	}

	demoRandSeed(seed);
	if(clearFirst != 0U){//覆盖填充:先清空区块(逐槽写0xFF), 数量精确等于count
		if(treatmentEpromClear() != TREATMENT_EPROM_OK){
			return TREATMENT_DEMO_ERR_IO;
		}
		start = 0U;
		target = (count > capacity) ? capacity : count;
	}
	else{//追加填充:从现有末尾继续写, 超出剩余容量按容量截断
		start = treatmentEpromGetCount();
		if(start >= capacity){
			return TREATMENT_DEMO_ERR_FULL;
		}
		target = count;
		if(target > (uint16_t)(capacity - start)){
			target = (uint16_t)(capacity - start);
		}
	}

	idBase = treatmentEpromNextId();//新病历ID起点: 清空后从1开始, 追加时接在现有最大ID之后
	if((uint32_t)idBase + (uint32_t)target > (uint32_t)(CONFIG_EPROM_TREATMENT_SLOT_EMPTY - 1U)){
		return TREATMENT_DEMO_ERR_PARAM;//ID号将用尽
	}

	tickStart = HAL_GetTick();
	for(uint16_t i = 0; i < target; i++){
		treatmentLog_t rec;
		demoBuildRecord((uint16_t)(idBase + i), &rec);
		err = treatmentEpromWriteAt((uint16_t)(start + i), &rec);//O(1)定位槽位, 不逐条扫描数量
		if(err != TREATMENT_EPROM_OK){//写失败:按实际可读条数同步计数后返回
			NVRAM0[DM_TREATMENT_NUM] = (int16_t)treatmentEpromGetCount();
			return TREATMENT_DEMO_ERR_IO;
		}
	}

	NVRAM0[DM_TREATMENT_NUM] = (int16_t)treatmentEpromGetCount();//回读有效数量并同步计数寄存器
	if(NVRAM0[DM_TREATMENT_NUM] != (int16_t)(start + target)){
		return TREATMENT_DEMO_ERR_VERIFY;
	}
	if(demoVerify(start, target) != TREATMENT_DEMO_OK){
		return TREATMENT_DEMO_ERR_VERIFY;
	}
	if(written != NULL){
		*written = target;
	}

#if (CONFIG_TREATMENT_DEMO_VERBOSE == 1)
	treatmentLog_t first, last;
	printf("%s,%d,%s:demo fill ok, start=%u count=%u capacity=%u seed=%08X cost=%lums\n",
		__FILE__, __LINE__, __func__, start, target, capacity, demoRandState,
		(unsigned long)(HAL_GetTick() - tickStart));
	if((treatmentEpromGet(start, &first) == TREATMENT_EPROM_OK) &&
	   (treatmentEpromGet((uint16_t)(start + target - 1U), &last) == TREATMENT_EPROM_OK)){
		printf("%s,%d,%s:first[%u] %s %s age=%u %dW %s %s %ldJ %lds\n",
			__FILE__, __LINE__, __func__, start, first.name,
			(first.gender == MALE) ? "M" : "F", first.age, first.laserPower,
			treatmentLaserWaveName(first.laserWave), treatmentProtocolName(first.protocol),
			(long)first.releaseEnergy, (long)first.releaseTime);
		printf("%s,%d,%s:last [%u] %s %s age=%u %dW %s %s %ldJ %lds\n",
			__FILE__, __LINE__, __func__, (uint16_t)(start + target - 1U), last.name,
			(last.gender == MALE) ? "M" : "F", last.age, last.laserPower,
			treatmentLaserWaveName(last.laserWave), treatmentProtocolName(last.protocol),
			(long)last.releaseEnergy, (long)last.releaseTime);
	}
#endif
	return TREATMENT_DEMO_OK;
}
