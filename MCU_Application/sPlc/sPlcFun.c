/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "sPlcFun.h"
#include "..\config\myConfig.h"
/*****************************************************************************/
static void sPlcAssertWord32Address(uint16_t A){//32位操作地址检查: 字索引必须偶数(自然对齐),且(A+1)不越界
#if CONFIG_SPLC_ASSERT == 1
	if(((A & 1U) != 0U) || (A >= (CONFIG_NVRAM_SIZE - 1U))){
		while(1);
	}
#endif
}
static void sPlcAssertArrayRange(uint16_t index, int16_t cnt){//数组遍历范围检查: 元素数非负,且[index,index+cnt)不越界
#if CONFIG_SPLC_ASSERT == 1
	if(cnt < 0){
		while(1);
	}
	if((cnt > 0) && (((uint32_t)index + (uint32_t)cnt) > (uint32_t)CONFIG_NVRAM_SIZE)){
		while(1);
	}
#endif
}
/*****************************************************************************/
void REBOOT(void) {//软件复位	
	__set_FAULTMASK(1);
	NVIC_SystemReset();
}
void ORG(uint16_t A) {//程序起点(origin):标记一段梯形图逻辑的母线起始地址,本运行时无全局能流累加器,无需内部状态操作
	(void)A;//预留参数,保持指令签名统一
}
//位指令
void OUT(uint16_t A) {//线圈输出(普通线圈):在能流为真的分支中调用,对应位置1;能流为假时由调用分支保持或复位
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertCoilAddress(A);//检查地址范围
#endif
	NVRAM0[(A / 16)] |= (uint16_t)1 << (A % 16);
}
void SSET(uint16_t A){//线圈置位
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertCoilAddress(A);//检查地址范围
#endif
	NVRAM0[(A / 16)] |= 1 << (A % 16);
}
void RRES(uint16_t A){//线圈置零
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertCoilAddress(A);//检查地址范围
#endif
	NVRAM0[(A / 16)] &= ~(1 << (A % 16));
}
void FLIP(uint16_t A){//翻转
	uint16_t temp;
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertCoilAddress(A);//检查地址范围
#endif
	temp= (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;
	if(temp)
		RRES(A);
	else
		SSET(A);
}
uint8_t LD(uint16_t A){//载入
	uint8_t res = 0;
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertCoilAddress(A);//检查地址范围
#endif
	res = (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;
	if(res)
		return true;
	else
		return false;
}
uint8_t LDB(uint16_t A){//反向载入
	uint8_t res = 0;
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertCoilAddress(A);//检查地址范围
#endif
	res = (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;
	if(res)
		return false;
	else
		return true;
}
uint8_t LDP(uint16_t A){//脉冲上升沿
	uint8_t temp0 = 0, temp1 = 0;
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertCoilAddress(A);//检查地址范围
#endif
	temp0 = (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;
	temp1 = (uint8_t)(NVRAM1[(A / 16)] >> (A % 16)) & 0x01;
	if(temp0 == 1 && temp1 == 0)
		return true;
	else
		return false;
}
uint8_t LDN(uint16_t A){//脉冲下降沿
	uint8_t temp0 = 0, temp1 = 0;
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertCoilAddress(A);
#endif
	temp0 = (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;
	temp1 = (uint8_t)(NVRAM1[(A / 16)] >> (A % 16)) & 0x01;
	if(temp0 == 0 && temp1 == 1)
		return true;
	else
		return false;
}
/*****************************************************************************/
//延时器指令
void T10MS(uint8_t A, uint8_t start, uint16_t value){//10MS延时器
#if CONFIG_SPLC_ASSERT == 1
	if(A >= (CONFIG_T_10MS_SIZE * 16)){ while(1); }//定时器编号范围检查
#endif
	if(start){
		SSET(T_10MS_ENA_START * 16 + A);
		if(NVRAM0[(TD_10MS_START + A)] >= value){
			NVRAM0[(T_10MS_START + (A / 16))] |= 1 << (A % 16);
		}
		else{
			NVRAM0[(T_10MS_START + (A / 16))] &= ~(1 << (A % 16));
		}
	}
	else{
		RRES(T_10MS_ENA_START * 16 + A);
		NVRAM0[(T_10MS_START + (A / 16))] &= ~(1 << (A % 16));
		NVRAM0[(TD_10MS_START + A)] = 0x0;
	}	
}
void T100MS(uint8_t A, uint8_t start, uint16_t value){//100MS延时器
#if CONFIG_SPLC_ASSERT == 1
	if(A >= (CONFIG_T_100MS_SIZE * 16)){ while(1); }//定时器编号范围检查
#endif
	if(start){
		SSET(T_100MS_ENA_START * 16 + A);
		if(NVRAM0[(TD_100MS_START + A)] >= value){
			NVRAM0[(T_100MS_START + (A / 16))] |= 1 << (A % 16);
		}
		else{		
			NVRAM0[(T_100MS_START + (A / 16))] &= ~(1 << (A % 16));
		}	
	}
	else{
		RRES(T_100MS_ENA_START * 16 + A);
		NVRAM0[(T_100MS_START + (A / 16))] &= ~(1 << (A % 16));
		NVRAM0[(TD_100MS_START + A)] = 0x0;
	}
}
/*****************************************************************************/
//计算指令
void CLR(uint16_t A){//16位寄存器清零
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertRegisterAddress(A);//检查寄存器地址
#endif
	NVRAM0[A] = 0x0;
}
void CLRD(uint16_t A){//32位寄存器清零
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertRegisterAddress(A);//检查寄存器地址
	sPlcAssertRegisterAddress(A + 1);//检查寄存器地址
#endif
	NVRAM0[A] = 0x0;NVRAM0[A + 1] = 0x0;
}
void MOV(uint16_t dist, uint16_t src){//16位寄存器传输
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertRegisterAddress(dist);//检查寄存器地址
	sPlcAssertRegisterAddress(src);//检查寄存器地址
#endif
	NVRAM0[dist] = NVRAM0[src];
}
void MOVD(uint16_t dist, uint16_t src){//32位寄存器传输
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertRegisterAddress(dist);//检查寄存器地址
	sPlcAssertRegisterAddress(dist+1);//检查寄存器地址
	sPlcAssertRegisterAddress(src);//检查寄存器地址
	sPlcAssertRegisterAddress(src+1);//检查寄存器地址
#endif
	NVRAM0[dist] = NVRAM0[src];
	NVRAM0[dist + 1] = NVRAM0[src + 1];
}
//void AND(uint16_t A, uint16_t A){//16位数 按位求与
//	
//}
//void ANDD(uint16_t dist){//32位数 按位求与
//}
void TNTUC(uint16_t dist, uint16_t src, float ntc_rs, float ntc_b){//CODE转换为NTC测量温度温度 电阻上拉
	float ftemp;
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertRegisterAddress(dist);//检查寄存器地址
	sPlcAssertRegisterAddress(src);//检查寄存器地址
#endif
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = 0xFFF;
	LIMS16(src, TMP_REG_0, TMP_REG_1);
	//使用内部基准校准
	if(NVRAM0[src] >= 10){
		if(NVRAM0[CONFIG_VREF_ADC]  > 0){
			ftemp = (CONFIG_MCU_VREF * CONFIG_VREF_CAL * NVRAM0[src]) / (NVRAM0[CONFIG_VREF_ADC] * 4096.0F);//计算电压
		}
		else{
			ftemp = (CONFIG_MCU_VREF * CONFIG_VREF_CAL * NVRAM0[src]) / 4096.0F;//计算电压
		}
		if(ftemp >= CONFIG_NTC_VREF){//满量程:原浮点==判断不可靠,改>=防(CONFIG_NTC_VREF-ftemp)除零
			ftemp = 999999.9F;//计算电阻
		}
		else{
			ftemp = ftemp * ntc_rs / (CONFIG_NTC_VREF - ftemp);//计算电阻
		}
	}
	else{
		ftemp = 0.1F;
	}
	ftemp = 1 / (1 / (273.15F + 25.0F) + 1 / ntc_b * logf(ftemp / CONFIG_NTC_R25)) - 273.15F;//log(双精度软浮点)→logf(单精度硬件FPU)
	if(ftemp >= 100) ftemp = 100;
	if(ftemp <= -100) ftemp = -100;
	NVRAM0[dist] = (int16_t)(ftemp * 10);
}

void TNTLC(uint16_t dist, uint16_t src, float ntc_rs, float ntc_b){//CODE转换为NTC测量温度温度 电阻下拉
	float ftemp;
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertRegisterAddress(dist);//检查寄存器地址
	sPlcAssertRegisterAddress(src);//检查寄存器地址
#endif
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = 0xFFF;
	LIMS16(src, TMP_REG_0, TMP_REG_1);
	//使用内部基准校准
	if(NVRAM0[src] >= 10){
		if(NVRAM0[CONFIG_VREF_ADC]  > 0){
			ftemp = (CONFIG_MCU_VREF * CONFIG_VREF_CAL * NVRAM0[src]) / (NVRAM0[CONFIG_VREF_ADC] * 4096.0F);//计算电压
		}
		else{
			ftemp = (CONFIG_MCU_VREF * CONFIG_VREF_CAL * NVRAM0[src]) / 4096.0F;//计算电压
		}
		if(ftemp >= ntc_rs){//原浮点==判断不可靠,改>=防下拉分压除零
			ftemp = 999999.9F;//计算电阻
		}
		else{
			ftemp = ntc_rs * CONFIG_NTC_VREF / ftemp - ntc_rs;//计算电阻
		}
	}
	else{
		ftemp = 0.1F;
	}
	ftemp = 1 / (1 / (273.15F + 25.0F) + 1 / ntc_b * logf(ftemp / CONFIG_NTC_R25)) - 273.15F;//log(双精度软浮点)→logf(单精度硬件FPU)
	if(ftemp >= 100) ftemp = 100;
	if(ftemp <= -100) ftemp = -100;
	NVRAM0[dist] = (int16_t)(ftemp * 10);
}

void TENV(uint16_t dist, uint16_t src){//CODE转换为MCU温度
	float ftemp;
#if CONFIG_SPLC_ASSERT == 1
	sPlcAssertRegisterAddress(dist);//检查寄存器地址
	sPlcAssertRegisterAddress(src);//检查寄存器地址
#endif
	if(NVRAM0[CONFIG_VREF_ADC]  > 0){
		ftemp = (CONFIG_MCU_VREF * CONFIG_VREF_CAL * NVRAM0[src]) / (NVRAM0[CONFIG_VREF_ADC] * 4096.0F);
	}
	else{
		ftemp = (CONFIG_MCU_VREF * CONFIG_VREF_CAL * NVRAM0[src]) / 4096.0F;
	}
	ftemp = ((ftemp - CONFIG_ADC_V25) / CONFIG_ADC_AVG_SLOPE) + 25.0F;
	if(ftemp >= 100)
		ftemp =100;
	if(ftemp <= -25){
		ftemp = -25;
	}
	NVRAM0[dist] = (int16_t)(ftemp * 10);
}
void ADD1(uint16_t Sa){//16位非饱和自加
	NVRAM0[Sa] += 1;
}
void ADDS1(uint16_t Sa){//16位饱和自加
	if(NVRAM0[Sa] < SHRT_MAX){
		NVRAM0[Sa] += 1;
	}
}
void DEC1(uint16_t Sa){//16位非饱和自减
	NVRAM0[Sa] -= 1;
}
void DECS1(uint16_t Sa){//16位饱和自减
	if(NVRAM0[Sa] > SHRT_MIN){
		NVRAM0[Sa] -= 1;
	}
}
void ADL1(uint16_t Sa){//32位非饱和自加
	int32_t *p;
	sPlcAssertWord32Address(Sa);
	p = (int32_t*)(&NVRAM0[Sa]);	
	(*p) ++;
}
void ADLS1(uint16_t Sa){//32位饱和自加
	int32_t *p;
	sPlcAssertWord32Address(Sa);
	p = (int32_t*)(&NVRAM0[Sa]);
	if(*p < LONG_MAX){
		(*p) ++;
	}
}
void DEL1(uint16_t Sa){//32位非饱和自减
	int32_t *p;
	sPlcAssertWord32Address(Sa);
	p = (int32_t*)(&NVRAM0[Sa]);
	(*p) --;
}
void DELS1(uint16_t Sa){//32位饱和自减
	int32_t *p;
	sPlcAssertWord32Address(Sa);
	p = (int32_t*)(&NVRAM0[Sa]);
	if(*p > LONG_MIN){
		(*p) --;
	}
}
void ADD16(uint16_t Sa, uint16_t Sb, uint16_t D){//16位非饱和加法 D = Sa + Sb
	NVRAM0[D] = NVRAM0[Sa] + NVRAM0[Sb];
}
void ADDS16(uint16_t Sa, uint16_t Sb, uint16_t D){//16位饱和加法 D = Sa + Sb
	int32_t tmp;
	tmp = NVRAM0[Sa] + NVRAM0[Sb];
	if(tmp >= SHRT_MAX)
		tmp = SHRT_MAX;
	if(tmp <= SHRT_MIN)
		tmp = SHRT_MIN;
	NVRAM0[D] = tmp;
}
void ADD32(uint16_t Sa, uint16_t Sb, uint16_t D){//32位非饱加法 D = Sa + Sb
	int32_t tmpSa, tmpSb, tmpD;
	sPlcAssertWord32Address(Sa);
	sPlcAssertWord32Address(Sb);
	sPlcAssertWord32Address(D);
	tmpSa = *((int32_t*)(&NVRAM0[Sa]));
	tmpSb = *((int32_t*)(&NVRAM0[Sb]));
	tmpD = tmpSa + tmpSb;
	*((int32_t*)(&NVRAM0[D])) = tmpD; 
	
}
void ADDS32(uint16_t Sa, uint16_t Sb, uint16_t D){//32位饱和加法 D = Sa + Sb
	int32_t tmpSa, tmpSb;
	int64_t tmpD;
	sPlcAssertWord32Address(Sa);
	sPlcAssertWord32Address(Sb);
	sPlcAssertWord32Address(D);
	tmpSa = *((int32_t*)(&NVRAM0[Sa]));
	tmpSb = *((int32_t*)(&NVRAM0[Sb]));
	tmpD = tmpSa + tmpSb;
	if(tmpD >= LONG_MAX){
		tmpD = LONG_MAX;
	}
	if(tmpD <= LONG_MIN){
		tmpD = LONG_MIN;
	}
	*((int32_t*)(&NVRAM0[D])) = tmpD;
}
void ADDS32D(uint16_t Sa, uint16_t Sb, uint16_t D){//32位饱和加法 D(32) = Sa(32) + Sb(16)
	int32_t tmpSa;
	int16_t tmpSb;
	int64_t tmpD;
	sPlcAssertWord32Address(Sa);
	sPlcAssertWord32Address(D);
	tmpSa = *((int32_t*)(&NVRAM0[Sa]));
	tmpSb = NVRAM0[Sb];//修复:按16位有符号读取(原实现误按32位读取)
	tmpD = (int64_t)tmpSa + (int64_t)tmpSb;
	if(tmpD >= LONG_MAX){
		tmpD = LONG_MAX;
	}
	if(tmpD <= LONG_MIN){
		tmpD = LONG_MIN;
	}
	*((int32_t*)(&NVRAM0[D])) = tmpD; 
}
void SUB16(uint16_t Sa, uint16_t Sb, uint16_t D){//16位非饱和减法 D = Sa - Sb
	NVRAM0[D] = NVRAM0[Sa] - NVRAM0[Sb];
}
void SUBS16(uint16_t Sa, uint16_t Sb, uint16_t D){//16位饱和减法 D = Sa - Sb
	int32_t tmp;
	tmp = NVRAM0[Sa] - NVRAM0[Sb];
	if(tmp >= SHRT_MAX)
		tmp = SHRT_MAX;
	if(tmp <= SHRT_MIN)
		tmp = SHRT_MIN;
	NVRAM0[D] = tmp;
}
void SUB32(uint16_t Sa, uint16_t Sb, uint16_t D){//32位非饱和减法 D = Sa - Sb
	int32_t tmpSa, tmpSb, tmpD;
	sPlcAssertWord32Address(Sa);
	sPlcAssertWord32Address(Sb);
	sPlcAssertWord32Address(D);
	tmpSa = *((int32_t*)(&NVRAM0[Sa]));
	tmpSb = *((int32_t*)(&NVRAM0[Sb]));
	tmpD = tmpSa - tmpSb;
	*((int32_t*)(&NVRAM0[D])) = tmpD;//修复:原实现误做饱和钳位且未写入D
}
void MULT16(uint16_t Sa, uint16_t Sb, uint16_t D){//16*16->16非饱和乘法 D = Sa * Sb
	int32_t tmp = (int32_t)NVRAM0[Sa] * (int32_t)NVRAM0[Sb];
	NVRAM0[D] = (int16_t)(tmp & 0xFFFF);
}
void MULTS16(uint16_t Sa, uint16_t Sb, uint16_t D){//16*16->16饱和乘法 D = Sa * Sb
	int32_t tmp = (int32_t)NVRAM0[Sa] * (int32_t)NVRAM0[Sb];
	if(tmp >= SHRT_MAX)
		tmp = SHRT_MAX;
	if(tmp <= SHRT_MIN)
		tmp = SHRT_MIN;
	NVRAM0[D] = (int16_t)tmp;
}
void MULT32(uint16_t Sa, uint16_t Sb, uint16_t D){//16*16->32非饱和乘法 D = Sa * Sb
	int32_t tmpSa = 0, tmpSb = 0, tmpD = 0;
	sPlcAssertWord32Address(Sa);//拼字风格不依赖指针,但32位数据按约定偶数对齐且+1不越界
	sPlcAssertWord32Address(Sb);
	sPlcAssertWord32Address(D);
	tmpSa = NVRAM0[(Sa + 1)];
	tmpSa = (tmpSa << 16) & 0xFFFF0000;
	tmpSa |= NVRAM0[Sa];
	
	tmpSb = NVRAM0[(Sb + 1)];
	tmpSb = (tmpSb << 16) & 0xFFFF0000;
	tmpSb |= NVRAM0[Sb];
	
	tmpD = tmpSa * tmpSb;
	NVRAM0[D] = tmpD & 0x0000FFFF;
	NVRAM0[(D + 1)] = (tmpD >> 16) & 0x0000FFFF;
}
void SUM16(uint16_t index, uint16_t length, uint16_t sum){//16BIT数求和->32BIT
	int32_t tmp = 0;
	int16_t cnt;
	uint16_t i = 0;
	sPlcAssertWord32Address(sum);
	cnt = NVRAM0[length];
	sPlcAssertArrayRange(index, cnt);
	for(i = 0; i < cnt; i++)
	{
		tmp += NVRAM0[index + i];
	}
	*((int32_t*)&NVRAM0[sum]) = tmp;
}
void UMAX16(uint16_t index, uint16_t length, uint16_t max){//16位无符号数组找最大值
	uint16_t i = 0;
	uint16_t tmp;
	int16_t cnt = NVRAM0[length];
	sPlcAssertArrayRange(index, cnt);
	if(cnt <= 0){
		return;
	}
	tmp = NVRAM0[index];//首元素初始化,避免初值0在全负数组时误判
	for(i = 1;i < cnt;i ++ ){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[max] = tmp;
}
void UMIN16(uint16_t index, uint16_t length, uint16_t min){//16位无符号数组找最小值
	uint16_t i = 0;
	uint16_t tmp;
	int16_t cnt = NVRAM0[length];
	sPlcAssertArrayRange(index, cnt);
	if(cnt <= 0){
		return;
	}
	tmp = NVRAM0[index];
	for(i = 1;i < cnt;i ++){
		if(tmp > NVRAM0[index + i]){//修复:原实现误用<(MAX逻辑),永远找不出最小值
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[min] = tmp;
}
void SMAX16(uint16_t index, uint16_t length, uint16_t max){//16位有符号数组找最大值
	uint16_t i = 0;
	int16_t tmp;
	int16_t cnt = NVRAM0[length];
	sPlcAssertArrayRange(index, cnt);
	if(cnt <= 0){
		return;
	}
	tmp = NVRAM0[index];
	for(i = 1;i < cnt;i ++ ){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[max] = tmp;
}
void SMIN16(uint16_t index, uint16_t length, uint16_t min){//16位有符号数组找最小值
	uint16_t i = 0;
	int16_t tmp;
	int16_t cnt = NVRAM0[length];
	sPlcAssertArrayRange(index, cnt);
	if(cnt <= 0){
		return;
	}
	tmp = NVRAM0[index];
	for(i = 1;i < cnt;i ++){
		if(tmp > NVRAM0[index + i]){//修复:原实现误用<(MAX逻辑)
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[min] = tmp;
}
void ABS16(uint16_t dist, uint16_t src){//16位数求绝对值
	int16_t v = NVRAM0[src];
	if(v >= 0){
		NVRAM0[dist] = v;
	}
	else if(v == SHRT_MIN){
		NVRAM0[dist] = SHRT_MAX;//SHRT_MIN的绝对值32768超出int16,钳到SHRT_MAX
	}
	else{
		NVRAM0[dist] = (int16_t)(-v);
	}
}
void ABS32(uint16_t dist, uint16_t src){//32位数求绝对值
	int32_t v;
	sPlcAssertWord32Address(src);
	sPlcAssertWord32Address(dist);
	v = *((int32_t*)(&NVRAM0[src]));//修复:原实现仅按16位单字操作
	if(v < 0){
		v = -v;//LONG_MIN取负位模式仍为0x80000000(边界保持,不触发异常)
	}
	*((int32_t*)(&NVRAM0[dist])) = v;
}
void SWAP(uint16_t dist, uint16_t src){//交换A的高低字节
	uint16_t tmpL = 0, tmpH = 0;
	tmpL = (NVRAM0[src] & 0x00FF);
	tmpH = (NVRAM0[src] >> 8) & 0x00FF;
	tmpH |= tmpL;
	NVRAM0[dist] = tmpH;
}
void LIMS16(uint16_t src, uint16_t min, uint16_t max){//有符号16位数限制幅度指令
	if(NVRAM0[src] >= NVRAM0[max]){
		NVRAM0[src] = NVRAM0[max];
	}
	if(NVRAM0[src] <= NVRAM0[min]){
		NVRAM0[src] = NVRAM0[min];
	}
}
/*****************************************************************************/
void BCPY(uint16_t dist, uint16_t src, uint16_t length) {//块复制(memmove语义,支持区间重叠)
	uint16_t i;
	if((length == 0U) || (dist == src)){
		return;
	}
#if CONFIG_SPLC_ASSERT == 1
	if(((uint32_t)dist + length > (uint32_t)CONFIG_NVRAM_SIZE) ||
	   ((uint32_t)src + length > (uint32_t)CONFIG_NVRAM_SIZE)){
		while(1);
	}
#endif
	if((dist > src) && ((uint32_t)dist < ((uint32_t)src + length))){//重叠且目标在后:从后向前复制
		for(i = length; i > 0U; i--){
			NVRAM0[dist + i - 1U] = NVRAM0[src + i - 1U];
		}
	}
	else{//不重叠或目标在前:正向复制
		for(i = 0;i < length;i ++){
			NVRAM0[dist + i] = NVRAM0[src + i];
		}
	}
}
void NVFSAVE(void){//NVRAM全部写入EPROM
	sPlcNvramSave();
}
void NVSAVE(void){//储存NVRAM更新数据到EPROM
	sPlcNvramUpdate();
}
void NVLOAD(void){
	sPlcNvramLoad();
}

void FDSAV(void){//FDRAM->EPROM
	sPlcFdramSave();
}
void FDSAV_ONE(int16_t cn){//储存一个方案到EPROM中
  uint32_t crc32_eprom_fd;
  HAL_StatusTypeDef ref;
  if((cn < 0) || (cn >= (CONFIG_FDRAM_SIZE / 64))){//方案编号范围检查(共32个方案,每方案64字)
		printf("%s,%d,%s:invalid FD scheme number:%d\n",__FILE__, __LINE__, __func__, cn);
		return;
	}
  crc32_eprom_fd = sPlcCrc32Calc((uint32_t *)(FDRAM0), (CONFIG_FDRAM_SIZE / 2));
	//注意:此处CRC按整区FDRAM计算(历史布局),单方案独立加载时不用于校验,仅保持兼容
	ref = epromWrite((cn * 128 + CONFIG_EPROM_FD_START), (uint8_t*)(cn * 64 + FDRAM0), 128);
	if(ref != HAL_OK){
		printf("%s,%d,%s:save FD NVRAM fail...\n",__FILE__, __LINE__, __func__);
		return;
	}
	ref = epromWriteDword(CONFIG_EPROM_FD_CRC, &crc32_eprom_fd);//在的指定地址开始写入32位数
  if(ref != HAL_OK){
		printf("%s,%d,%s:save FD CRC fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
    printf("%s,%d,%s:save one FDRAM done...(cn:%d FDRAM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, cn, crc32_eprom_fd);
	}
}
void FDLAD_ONE(int16_t cn){//从EPROM载入一个方案到FDRAM对应位置
	HAL_StatusTypeDef ref;
	if((cn < 0) || (cn >= (CONFIG_FDRAM_SIZE / 64))){//方案编号范围检查
		printf("%s,%d,%s:invalid FD scheme number:%d\n",__FILE__, __LINE__, __func__, cn);
		return;
	}
	ref = epromRead((cn * 128 + CONFIG_EPROM_FD_START), (uint8_t*)(cn * 64 + FDRAM0), 128);
	if(ref != HAL_OK){
		printf("%s,%d,%s:load one FDRAM fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load one FDRAM done...(cn:%d)\n",__FILE__, __LINE__, __func__, cn);
	}
}
void FDLAD(void){//FDRAM<-EPROM
	sPlcFdramLoad();
}

/*****************************************************************************/
//IO指令
void IMDIO(void) {//立即更新IO点状态含输入输出
	sPlcInputRefresh();//立即读取X口输入
	sPlcOutputRefresh();//立即刷新Y口输出
}
//步指令
//void TO(uint16_t SA) {//步进开始指令
//}
//void STP(uint16_t SA) {//步进指令
//}
//void STPEND(void) {//步进结束指令
//}
//void FROM(uint16_t SA) {//步进执行指令
//}

void PRTM(uint16_t adr, uint8_t len){//在串口中断上打印内存数据
	uint16_t index;
	uint32_t endAddr = (uint32_t)adr + (uint32_t)len;//32位求和,防uint16回绕
	index = adr;
	printf("NVRAM MEMORY TABLE:\n");
	printf("  ADR:  +0,  +1,  +2,  +3,  +4,  +5,  +6   +7,  +8,  +9, +10, +11, +12, +13, +14, +15\n");
	printf("00000:FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF\n");
	for(index = adr & 0xFFF0;index < endAddr;index ++){
		if(index >= CONFIG_NVRAM_SIZE){//修复:原index>UINT16_MAX为恒假死代码,改为NVRAM边界检查防越界
			printf("\n\n");
			printf("END OF NVRAM\n");
			break;
		}
		if((index & 0x000F) == 0x0){//行起始
			printf("%5d:", (index & 0xFFF0));
		}
		printf(",%04X",NVRAM0[index]);
		if((index & 0x000F) == 0xF){//最后一个
			printf("\n");
		}
	}
}







