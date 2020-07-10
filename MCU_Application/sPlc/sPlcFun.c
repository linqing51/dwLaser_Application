#include "sPlcFun.h"
/*****************************************************************************/
void REBOOT(void) {//软件复位	
	__set_FAULTMASK(1);
	NVIC_SystemReset();
}
void ORG(uint16_t A) {
}
//位指令
void OUT(uint16_t A) {
}
void SSET(uint16_t A){//线圈置位
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//检查地址范围
#endif
	NVRAM0[(A / 16)] |= 1 << (A % 16);
}
void RRES(uint16_t A){//线圈置零
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//检查地址范围
#endif
	NVRAM0[(A / 16)] &= ~(1 << (A % 16));
}
void FLIP(uint16_t A){//翻转
	uint16_t temp;
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//检查地址范围
#endif
	temp= (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;;
	if(temp)
		RRES(A);
	else
		SSET(A);
}
uint8_t LD(uint16_t A){//载入
	uint8_t res = 0;
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//检查地址范围
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
	assertCoilAddress(A);//检查地址范围
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
	assertCoilAddress(A);//检查地址范围
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
	assertCoilAddress(A);
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
	assertRegisterAddress(A);//检查寄存器地址
#endif
	NVRAM0[A] = 0x0;
}
void CLRD(uint16_t A){//32位寄存器清零
#if CONFIG_SPLC_ASSERT == 1
	assertRegisterAddress(A);//检查寄存器地址
	assertRegisterAddress(A + 1);//检查寄存器地址
#endif
	NVRAM0[A] = 0x0;NVRAM0[A + 1] = 0x0;
}
void MOV(uint16_t dist, uint16_t src){//16位寄存器传输
#if CONFIG_SPLC_ASSERT == 1
	assertRegisterAddress(dist);//检查寄存器地址
	assertRegisterAddress(src);//检查寄存器地址
#endif
	NVRAM0[dist] = NVRAM0[src];
}
void MOVD(uint16_t dist, uint16_t src){//32位寄存器传输
#if CONFIG_SPLC_ASSERT == 1
	assertRegisterAddress(dist);//检查寄存器地址
	assertRegisterAddress(dist+1);//检查寄存器地址
	assertRegisterAddress(src);//检查寄存器地址
	assertRegisterAddress(src+1);//检查寄存器地址
#endif
	NVRAM0[dist] = NVRAM0[src];
	NVRAM0[dist + 1] = NVRAM0[src + 1];
}
//void AND(uint16_t A, uint16_t A){//16位数 按位求与
//	
//}
//void ANDD(uint16_t dist){//32位数 按位求与
//}
void TNTC(uint16_t dist, uint16_t src){//CODE转换为NTC测量温度温度
	fp32_t ftemp;
#if CONFIG_SPLC_ASSERT == 1
	assertRegisterAddress(dist);//检查寄存器地址
	assertRegisterAddress(src);//检查寄存器地址
#endif
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = 0xFFF;
	LIMS16(src, TMP_REG_0, TMP_REG_1);
	ftemp = (3300.0F * CONFIG_VREF_CAL * NVRAM0[src]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);
	ftemp = (uint16_t)(CONFIG_NTC_RS * (CONFIG_NTC_VREF - ftemp) / ftemp);
	ftemp = 1 / (1 / (273.15F + 25.0F) + 1 / CONFIG_NTC_B * log(ftemp / CONFIG_NTC_R25)) - 273.15;
	//ftemp = ((1.0 / CONFIG_NTC_B) * log(ftemp) / 10000) + (1 / (CONFIG_AMBIENT_TEMP + 273.0));//limo R25=10740,B=3450	 uniquemode 3988
	//ftemp = (fp32_t)(( 1.0F / ftemp ) - 273.0F);
	if(ftemp >= 100) ftemp = 100;
	if(ftemp <= -100) ftemp = -100;
	NVRAM0[dist] = (int16_t)(ftemp * 10);
}
void TENV(uint16_t dist, uint16_t src){//CODE转换为MCU温度
	fp32_t ftemp;
	ftemp = (3300.0F * CONFIG_VREF_CAL * NVRAM0[src]) / (NVRAM0[SPREG_ADC_9] * 4096.0F);
	//ftemp = NVRAM0[SPREG_VREF]* NVRAM0[src] / 4096;//单位mV
	ftemp = ((ftemp - CONFIG_ADC_V25) / CONFIG_ADC_AVG_SLOPE) + 25.0F;
	if(ftemp >= 100)
		ftemp =100;
	if(ftemp <= -40){
		ftemp = -40;
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
	int32_t temp = 0;
	temp = NVRAM0[(Sa + 1)];
	temp = (temp << 16) & 0xFFFF0000;
	temp |= NVRAM0[Sa];
	temp += 1;
	NVRAM0[Sa] = temp & 0x0000FFFF;
	NVRAM0[(Sa + 1)] = (temp >> 16) & 0x0000FFFF;
}
void ADLS1(uint16_t Sa){//32位饱和自加
	int32_t temp = 0;
	temp = NVRAM0[(Sa + 1)];
	temp = (temp << 16) & 0xFFFF0000;
	temp |= NVRAM0[Sa];
	if(temp < LONG_MAX){
		temp ++;
		NVRAM0[Sa] = temp & 0x0000FFFF;
		NVRAM0[(Sa + 1)] = (temp >> 16) & 0x0000FFFF;
	}
}
void DEL1(uint16_t Sa){//32位非饱和自减
	int32_t temp = 0;
	temp = NVRAM0[(Sa + 1)];
	temp = (temp << 16) & 0xFFFF0000;
	temp |= NVRAM0[Sa];
	temp -= 1;
	NVRAM0[Sa] = temp & 0x0000FFFF;
	NVRAM0[(Sa + 1)] = (temp >> 16) & 0x0000FFFF;
}
void DELS1(uint16_t Sa){//32位饱和自减
	int32_t temp = 0;
	temp = NVRAM0[(Sa + 1)];
	temp = (temp << 16) & 0xFFFF0000;
	temp |= NVRAM0[Sa];
	if(temp < LONG_MAX){
		temp --;
		NVRAM0[Sa] = temp & 0x0000FFFF;
		NVRAM0[(Sa + 1)] = (temp >> 16) & 0x0000FFFF;
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
	int32_t tmpSa = 0, tmpSb = 0, tmpD = 0;
	tmpSa = NVRAM0[(Sa + 1)];
	tmpSa = (tmpSa << 16) & 0xFFFF0000;
	tmpSa |= NVRAM0[Sa];
	
	tmpSb = NVRAM0[(Sb + 1)];
	tmpSb = (tmpSb << 16) & 0xFFFF0000;
	tmpSb |= NVRAM0[Sb];
	
	tmpD = tmpSa + tmpSb;
	NVRAM0[D] = tmpD & 0x0000FFFF;
	NVRAM0[(D + 1)] = (tmpD >> 16) & 0x0000FFFF;
}
void ADDS32(uint16_t Sa, uint16_t Sb, uint16_t D){//32位饱和加法 D = Sa + Sb
	int32_t tmpSa = 0, tmpSb = 0, tmpD = 0;
	fp64_t fD;
	tmpSa = NVRAM0[(Sa + 1)];
	tmpSa = (tmpSa << 16) & 0xFFFF0000;
	tmpSa |= NVRAM0[Sa];
	
	tmpSb = NVRAM0[(Sb + 1)];
	tmpSb = (tmpSb << 16) & 0xFFFF0000;
	tmpSb |= NVRAM0[Sb];

	fD = (fp64_t)tmpSa + (fp64_t)tmpSb;
	if(fD >= LONG_MAX){
		fD = LONG_MAX;
	}
	if(fD <= LONG_MIN){
		fD = LONG_MIN;
	}
	tmpD = (int32_t)fD;
	NVRAM0[D] = tmpD & 0x0000FFFF;
	NVRAM0[(D + 1)] = (tmpD >> 16) & 0x0000FFFF;
	
}
void ADDS32D(uint16_t Sa, uint16_t Sb, uint16_t D){//32位饱和加法 D(32) = Sa(32) + Sb(16)
	int32_t tmpSa = 0, tmpD = 0;
	fp64_t fD;
	tmpSa = NVRAM0[(Sa + 1)];
	tmpSa = (tmpSa << 16) & 0xFFFF0000;
	tmpSa |= NVRAM0[Sa];
	
	fD = (fp64_t)tmpSa + (fp64_t)NVRAM0[Sb];
	if(fD >= LONG_MAX){
		fD = LONG_MAX;
	}
	if(fD <= LONG_MIN){
		fD = LONG_MIN;
	}
	tmpD = (int32_t)fD;
	NVRAM0[D] = tmpD & 0x0000FFFF;
	NVRAM0[(D + 1)] = (tmpD >> 16) & 0x0000FFFF;
}
void SUB16(uint16_t Sa, uint16_t Sb, uint16_t D){//16位非饱和减法 D = Sa - Sb
	NVRAM0[D] = NVRAM0[Sa] - NVRAM0[Sb];
}
void SUBS16(uint16_t Sa, uint16_t Sb, uint16_t D){//16位饱和减法 D = Sa - Sb
	int32_t tmp;
	tmp = (int32_t)NVRAM0[Sa] - (int32_t)NVRAM0[Sb];
	if(tmp >= SHRT_MAX)
		tmp = SHRT_MAX;
	if(tmp <= SHRT_MIN)
		tmp = SHRT_MIN;
	NVRAM0[D] = tmp;
}
void SUB32(uint16_t Sa, uint16_t Sb, uint16_t D){//32位非饱和减法 D = Sa - Sb
	int32_t tmpSa = 0, tmpSb = 0, tmpD = 0;
	tmpSa = NVRAM0[(Sa + 1)];
	tmpSa = (tmpSa << 16) & 0xFFFF0000;
	tmpSa |= NVRAM0[Sa];
	
	tmpSb = NVRAM0[(Sb + 1)];
	tmpSb = (tmpSb << 16) & 0xFFFF0000;
	tmpSb |= NVRAM0[Sb];
	
	tmpD = tmpSa - tmpSb;
	NVRAM0[D] = tmpD & 0x0000FFFF;
	NVRAM0[(D + 1)] = (tmpD >> 16) & 0x0000FFFF;
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
	uint16_t i = 0;
	for(i = 0; i < NVRAM0[length]; i++)
	{
		tmp += NVRAM0[index + i];
	}
	*((int32_t*)&NVRAM0[sum]) = tmp;
}
void UMAX16(uint16_t index, uint16_t length, uint16_t max){//16位无符号数组找最大值
	uint16_t i = 0;
	uint16_t tmp = 0;
	for(i = 0;i < NVRAM0[length];i ++ ){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[max] = tmp;
}
void UMIN16(uint16_t index, uint16_t length, uint16_t min){//16位无符号数组找最小值
	uint16_t i = 0;
	uint16_t tmp = 0;
	for(i = 0;i < NVRAM0[length];i ++){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[min] = tmp;
}
void SMAX16(uint16_t index, uint16_t length, uint16_t max){//16位有符号数组找最大值
	uint16_t i = 0;
	int16_t tmp = 0;
	for(i = 0;i < NVRAM0[length];i ++ ){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[max] = tmp;
}
void SMIN16(uint16_t index, uint16_t length, uint16_t min){//16位有符号数组找最小值
	uint16_t i = 0;
	int16_t tmp = 0;
	for(i = 0;i < NVRAM0[length];i ++){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[min] = tmp;
}
void ABS16(uint16_t dist, uint16_t src){//16位数球绝对值
	if(NVRAM0[src] >= 0){
		NVRAM0[dist] = NVRAM0[src];
	}
	else{
		NVRAM0[dist] = NVRAM0[src] * -1;
	}
}
void ABS32(uint16_t dist, uint16_t src){//32位数求绝对值
	if(NVRAM0[src] >= 0){
		NVRAM0[dist] = NVRAM0[src];
	}
	else{
		NVRAM0[dist] = NVRAM0[src] * -1;
	}
}
void SWAP(uint16_t dist, uint16_t src){//交换A的高低字节
	uint16_t tmpL = 0, tmpH = 0;
	tmpL = (NVRAM0[src] & 0x00FF);
	tmpH = (NVRAM0[src] >> 8) & 0x00FF;
	tmpH |= tmpL;
	NVRAM0[dist] = tmpH;
}
void LIMS16(uint16_t src, uint16_t min, uint16_t max){//有符号16位数限制幅度指令
	if(NVRAM0[src] > NVRAM0[max]){
		NVRAM0[src] = NVRAM0[max];
	}
	if(NVRAM0[src] < NVRAM0[min]){
		NVRAM0[src] = NVRAM0[min];
	}
}

/*****************************************************************************/
void BCPY(uint16_t dist, uint16_t src, uint16_t length) {//块复制
	uint16_t i;
	for(i = 0;i < length;i ++){
		NVRAM0[dist + i] = NVRAM0[src + i];
	}
}
void NVSAV(void){//强制立即更新NVRAM
	disableSplcIsr();
	updateNvram();
	enableSplcIsr();
}
void NVLOAD(void){
	disableSplcIsr();
	loadNvram();
	enableSplcIsr();	
}

void FDSAV(void){//FDRAM->EPROM
	disableSplcIsr();
	saveFdram();
	enableSplcIsr();
}
void FDSAV_ONE(int16_t cn){//储存一个方案到EPROM中
	disableSplcIsr();
	if(cn > (CONFIG_HMI_SCHEME_NUM - 1)){
		cn = (CONFIG_HMI_SCHEME_NUM - 1);
	}
	if(cn < 0){
		cn = 0;
	}
#if CONFIG_SPLC_USING_EPROM == 1
	epromWrite((cn * 128 + CONFIG_EPROM_FD_START), (uint8_t*)(cn * 64 + FDRAM), 128);
#endif
	enableSplcIsr();
}
void FDLAD(void){//FDRAM<-EPROM
	disableSplcIsr();
	loadFdram();
	enableSplcIsr();
}



/*****************************************************************************/
//IO指令
void IMDIO(void) {//立即更新IO点状态含输入输出

}
/*****************************************************************************/
/*****************************************************************************/
void STPID(uint16_t adr){//位置PID指令
	//adr + 0:Input 输入值
	//adr + 1:ref 设定值
	//adr + 2:Output 输出值
	//adr + 3:Ts 采样周期 1-60000mS       		[1-60000] 
	//adr + 4:Kp 比例操作的常数 0.01-60.000   	[1-60000]
	//adr + 5:Ki 积分操作的常数 0.00-600.00	  	[1-30000]
	//adr + 6:Td 微分操作的常数 0.00-600.00   	[1-30000]
	//adr + 7:Mvll 操作量的下限值		      	[-32768-32766]
	//adr + 8:Mvhl 操作量的上限制			  	[-32767-32767]
	//adr + 9:Oper 正操作/反操作 1正操作 0反操作
	//adr + 10:dead 误差死区 0.000-60.000		[0-60000]
	//adr + 11:separate 积分分离常数 0.0-6000.0 [0-60000]
	//adr + 12:工作区 计时
	//adr + 13:工作区 计时
	//adr + 16:工作区 当前偏差pek0 FP32
	//adr + 17:工作区 当前偏差pek0 FP32
	//adr + 18:工作区 上次偏差pek1 FP32 
	//adr + 19:工作区 上次偏差pek1 FP32
	//adr + 20:工作区 累计偏差plocSum FP32 
	//adr + 21:工作区 累计偏差plocSum FP32
	fp32_t kp, ki, kd, pidOut, dead, separate;
	fp32_t *pek0, *pek1, *plocSum;
	uint32_t lastTime, nextTime;
	lastTime = (uint32_t)&NVRAM0[adr + 12];//上次PID执行时间
	nextTime = lastTime + NVRAM0[adr + 3];//下次PID执行时间
	if(sPlcTick > nextTime){
		kp = (fp32_t)NVRAM0[adr + 4] / 1000.0F;
		ki = (fp32_t)NVRAM0[adr + 5] / 100.0F;
		kd = (fp32_t)NVRAM0[adr + 6] / 100.0F;
		dead = (fp32_t)NVRAM0[adr + 10] / 1000.0F;
		separate = (fp32_t)NVRAM0[adr + 11] / 10.0F;
		pek0 = (fp32_t*)&NVRAM0[adr + 11];
		pek1 = (fp32_t*)&NVRAM0[adr + 13];
		plocSum = (fp32_t*)&NVRAM0[adr + 15]; 
		*pek0 = (fp32_t)NVRAM0[adr + 0] - (fp32_t)NVRAM0[adr + 1];//计算误差
		if(fabs(*pek0) < dead){//计算误差死区
			*pek0 = 0;
		}
		if(*pek0 > separate){//分离积分
			pidOut = (kp * (*pek0)) + kd * (*pek1 - *pek0);
			*plocSum = 0;
		}
		else{//不分离积分
			*plocSum = *plocSum + *pek0;//计算累计误差
			pidOut = (kp * (*pek0)) + (ki * (*plocSum)) + kd * (*pek1 - *pek0);
		}
		*pek1 = *pek0;
		if(pidOut > NVRAM0[adr + 8]){
			pidOut = (fp32_t)NVRAM0[adr + 8];
		}
		if(pidOut < NVRAM0[adr + 7]){
			pidOut = (fp32_t)NVRAM0[adr + 7];
		}
		NVRAM0[adr + 2] = (int16_t)pidOut;
		lastTime = sPlcTick;
	}
}
void FUPID(uint16_t adr){//模糊PID指令
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


