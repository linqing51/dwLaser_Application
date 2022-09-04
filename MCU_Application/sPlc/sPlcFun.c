#include "sPlcFun.h"
#include "pid_fuzzy.h"
//
extern CRC_HandleTypeDef hcrc;
/*****************************************************************************/
void REBOOT(void) {//�����λ	
	__set_FAULTMASK(1);
	NVIC_SystemReset();
}
void ORG(uint16_t A) {
}
//λָ��
void OUT(uint16_t A) {
}
void SSET(uint16_t A){//��Ȧ��λ
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//����ַ��Χ
#endif
	NVRAM0[(A / 16)] |= 1 << (A % 16);
}
void RRES(uint16_t A){//��Ȧ����
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//����ַ��Χ
#endif
	NVRAM0[(A / 16)] &= ~(1 << (A % 16));
}
void FLIP(uint16_t A){//��ת
	uint16_t temp;
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//����ַ��Χ
#endif
	temp= (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;;
	if(temp)
		RRES(A);
	else
		SSET(A);
}
uint8_t LD(uint16_t A){//����
	uint8_t res = 0;
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//����ַ��Χ
#endif
	res = (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;
	if(res)
		return true;
	else
		return false;
}
uint8_t LDB(uint16_t A){//��������
	uint8_t res = 0;
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//����ַ��Χ
#endif
	res = (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;
	if(res)
		return false;
	else
		return true;
}
uint8_t LDP(uint16_t A){//����������
	uint8_t temp0 = 0, temp1 = 0;
#if CONFIG_SPLC_ASSERT == 1
	assertCoilAddress(A);//����ַ��Χ
#endif
	temp0 = (uint8_t)(NVRAM0[(A / 16)] >> (A % 16)) & 0x01;
	temp1 = (uint8_t)(NVRAM1[(A / 16)] >> (A % 16)) & 0x01;
	if(temp0 == 1 && temp1 == 0)
		return true;
	else
		return false;
}
uint8_t LDN(uint16_t A){//�����½���
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
//��ʱ��ָ��
void T10MS(uint8_t A, uint8_t start, uint16_t value){//10MS��ʱ��
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
void T100MS(uint8_t A, uint8_t start, uint16_t value){//100MS��ʱ��
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
//����ָ��
void CLR(uint16_t A){//16λ�Ĵ�������
#if CONFIG_SPLC_ASSERT == 1
	assertRegisterAddress(A);//���Ĵ�����ַ
#endif
	NVRAM0[A] = 0x0;
}
void CLRD(uint16_t A){//32λ�Ĵ�������
#if CONFIG_SPLC_ASSERT == 1
	assertRegisterAddress(A);//���Ĵ�����ַ
	assertRegisterAddress(A + 1);//���Ĵ�����ַ
#endif
	NVRAM0[A] = 0x0;NVRAM0[A + 1] = 0x0;
}
void MOV(uint16_t dist, uint16_t src){//16λ�Ĵ�������
#if CONFIG_SPLC_ASSERT == 1
	assertRegisterAddress(dist);//���Ĵ�����ַ
	assertRegisterAddress(src);//���Ĵ�����ַ
#endif
	NVRAM0[dist] = NVRAM0[src];
}
void MOVD(uint16_t dist, uint16_t src){//32λ�Ĵ�������
#if CONFIG_SPLC_ASSERT == 1
	assertRegisterAddress(dist);//���Ĵ�����ַ
	assertRegisterAddress(dist+1);//���Ĵ�����ַ
	assertRegisterAddress(src);//���Ĵ�����ַ
	assertRegisterAddress(src+1);//���Ĵ�����ַ
#endif
	NVRAM0[dist] = NVRAM0[src];
	NVRAM0[dist + 1] = NVRAM0[src + 1];
}
//void AND(uint16_t A, uint16_t A){//16λ�� ��λ����
//	
//}
//void ANDD(uint16_t dist){//32λ�� ��λ����
//}
void TNTC(uint16_t dist, uint16_t src){//CODEת��ΪNTC�����¶��¶�
	float32_t ftemp;
#if CONFIG_SPLC_ASSERT == 1
	assertRegisterAddress(dist);//���Ĵ�����ַ
	assertRegisterAddress(src);//���Ĵ�����ַ
#endif
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = 0xFFF;
	LIMS16(src, TMP_REG_0, TMP_REG_1);
	//ʹ���ڲ���׼У׼
	if(NVRAM0[SPREG_ADC_4]  == 0){
		NVRAM0[SPREG_ADC_4] = 1;
	}
	if(NVRAM0[src] >= 10){	
		ftemp = (3300.0F * CONFIG_VREF_CAL * NVRAM0[src]) / (NVRAM0[SPREG_ADC_4] * 4096.0F);//�����ѹ
		ftemp = ftemp * CONFIG_NTC_RS / (CONFIG_NTC_VREF - ftemp);//�����ѹ
	}
	else{
 
		ftemp = 0.1F;
	}
	ftemp = 1 / (1 / (273.15F + 25.0F) + 1 / CONFIG_NTC_B * log(ftemp / CONFIG_NTC_R25)) - 273.15;
	if(ftemp >= 100) ftemp = 100;
	if(ftemp <= -100) ftemp = -100;
	NVRAM0[dist] = (int16_t)(ftemp * 10);
}
void TENV(uint16_t dist, uint16_t src){//CODEת��ΪMCU�¶�
	float32_t ftemp;
	ftemp = (3300.0F * CONFIG_VREF_CAL * NVRAM0[src]) / (NVRAM0[SPREG_ADC_4] * 4096.0F);
	//ftemp = NVRAM0[SPREG_VREF]* NVRAM0[src] / 4096;//��λmV
	ftemp = ((ftemp - CONFIG_ADC_V25) / CONFIG_ADC_AVG_SLOPE) + 25.0F;
	if(ftemp >= 100)
		ftemp =100;
	if(ftemp <= -40){
		ftemp = -40;
	}
	NVRAM0[dist] = (int16_t)(ftemp * 10);
}
void ADD1(uint16_t Sa){//16λ�Ǳ����Լ�
	NVRAM0[Sa] += 1;
}
void ADDS1(uint16_t Sa){//16λ�����Լ�
	if(NVRAM0[Sa] < SHRT_MAX){
		NVRAM0[Sa] += 1;
	}
}
void DEC1(uint16_t Sa){//16λ�Ǳ����Լ�
	NVRAM0[Sa] -= 1;
}
void DECS1(uint16_t Sa){//16λ�����Լ�
	if(NVRAM0[Sa] > SHRT_MIN){
		NVRAM0[Sa] -= 1;
	}
}
void ADL1(uint16_t Sa){//32λ�Ǳ����Լ�
	int32_t temp = 0;
	temp = NVRAM0[(Sa + 1)];
	temp = (temp << 16) & 0xFFFF0000;
	temp |= NVRAM0[Sa];
	temp += 1;
	NVRAM0[Sa] = temp & 0x0000FFFF;
	NVRAM0[(Sa + 1)] = (temp >> 16) & 0x0000FFFF;
}
void ADLS1(uint16_t Sa){//32λ�����Լ�
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
void DEL1(uint16_t Sa){//32λ�Ǳ����Լ�
	int32_t temp = 0;
	temp = NVRAM0[(Sa + 1)];
	temp = (temp << 16) & 0xFFFF0000;
	temp |= NVRAM0[Sa];
	temp -= 1;
	NVRAM0[Sa] = temp & 0x0000FFFF;
	NVRAM0[(Sa + 1)] = (temp >> 16) & 0x0000FFFF;
}
void DELS1(uint16_t Sa){//32λ�����Լ�
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
void ADD16(uint16_t Sa, uint16_t Sb, uint16_t D){//16λ�Ǳ��ͼӷ� D = Sa + Sb
	NVRAM0[D] = NVRAM0[Sa] + NVRAM0[Sb];
}
void ADDS16(uint16_t Sa, uint16_t Sb, uint16_t D){//16λ���ͼӷ� D = Sa + Sb
	int32_t tmp;
	tmp = NVRAM0[Sa] + NVRAM0[Sb];
	if(tmp >= SHRT_MAX)
		tmp = SHRT_MAX;
	if(tmp <= SHRT_MIN)
		tmp = SHRT_MIN;
	NVRAM0[D] = tmp;
}
void ADD32(uint16_t Sa, uint16_t Sb, uint16_t D){//32λ�Ǳ��ӷ� D = Sa + Sb
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
void ADDS32(uint16_t Sa, uint16_t Sb, uint16_t D){//32λ���ͼӷ� D = Sa + Sb
	int32_t tmpSa = 0, tmpSb = 0, tmpD = 0;
	double fD;
	tmpSa = NVRAM0[(Sa + 1)];
	tmpSa = (tmpSa << 16) & 0xFFFF0000;
	tmpSa |= NVRAM0[Sa];
	
	tmpSb = NVRAM0[(Sb + 1)];
	tmpSb = (tmpSb << 16) & 0xFFFF0000;
	tmpSb |= NVRAM0[Sb];

	fD = (double)tmpSa + (double)tmpSb;
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
void ADDS32D(uint16_t Sa, uint16_t Sb, uint16_t D){//32λ���ͼӷ� D(32) = Sa(32) + Sb(16)
	int32_t tmpSa = 0, tmpD = 0;
	double fD;
	tmpSa = NVRAM0[(Sa + 1)];
	tmpSa = (tmpSa << 16) & 0xFFFF0000;
	tmpSa |= NVRAM0[Sa];
	
	fD = (double)tmpSa + (double)NVRAM0[Sb];
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
void SUB16(uint16_t Sa, uint16_t Sb, uint16_t D){//16λ�Ǳ��ͼ��� D = Sa - Sb
	NVRAM0[D] = NVRAM0[Sa] - NVRAM0[Sb];
}
void SUBS16(uint16_t Sa, uint16_t Sb, uint16_t D){//16λ���ͼ��� D = Sa - Sb
	int32_t tmp;
	tmp = (int32_t)NVRAM0[Sa] - (int32_t)NVRAM0[Sb];
	if(tmp >= SHRT_MAX)
		tmp = SHRT_MAX;
	if(tmp <= SHRT_MIN)
		tmp = SHRT_MIN;
	NVRAM0[D] = tmp;
}
void SUB32(uint16_t Sa, uint16_t Sb, uint16_t D){//32λ�Ǳ��ͼ��� D = Sa - Sb
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
void MULT16(uint16_t Sa, uint16_t Sb, uint16_t D){//16*16->16�Ǳ��ͳ˷� D = Sa * Sb
	int32_t tmp = (int32_t)NVRAM0[Sa] * (int32_t)NVRAM0[Sb];
	NVRAM0[D] = (int16_t)(tmp & 0xFFFF);
}
void MULTS16(uint16_t Sa, uint16_t Sb, uint16_t D){//16*16->16���ͳ˷� D = Sa * Sb
	int32_t tmp = (int32_t)NVRAM0[Sa] * (int32_t)NVRAM0[Sb];
	if(tmp >= SHRT_MAX)
		tmp = SHRT_MAX;
	if(tmp <= SHRT_MIN)
		tmp = SHRT_MIN;
	NVRAM0[D] = (int16_t)tmp;
}
void MULT32(uint16_t Sa, uint16_t Sb, uint16_t D){//16*16->32�Ǳ��ͳ˷� D = Sa * Sb
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
void SUM16(uint16_t index, uint16_t length, uint16_t sum){//16BIT�����->32BIT
	int32_t tmp = 0;
	uint16_t i = 0;
	for(i = 0; i < NVRAM0[length]; i++)
	{
		tmp += NVRAM0[index + i];
	}
	*((int32_t*)&NVRAM0[sum]) = tmp;
}
void UMAX16(uint16_t index, uint16_t length, uint16_t max){//16λ�޷������������ֵ
	uint16_t i = 0;
	uint16_t tmp = 0;
	for(i = 0;i < NVRAM0[length];i ++ ){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[max] = tmp;
}
void UMIN16(uint16_t index, uint16_t length, uint16_t min){//16λ�޷�����������Сֵ
	uint16_t i = 0;
	uint16_t tmp = 0;
	for(i = 0;i < NVRAM0[length];i ++){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[min] = tmp;
}
void SMAX16(uint16_t index, uint16_t length, uint16_t max){//16λ�з������������ֵ
	uint16_t i = 0;
	int16_t tmp = 0;
	for(i = 0;i < NVRAM0[length];i ++ ){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[max] = tmp;
}
void SMIN16(uint16_t index, uint16_t length, uint16_t min){//16λ�з�����������Сֵ
	uint16_t i = 0;
	int16_t tmp = 0;
	for(i = 0;i < NVRAM0[length];i ++){
		if(tmp < NVRAM0[index + i]){
			tmp = NVRAM0[index + i];
		}
	}
	NVRAM0[min] = tmp;
}
void ABS16(uint16_t dist, uint16_t src){//16λ�������ֵ
	if(NVRAM0[src] >= 0){
		NVRAM0[dist] = NVRAM0[src];
	}
	else{
		NVRAM0[dist] = NVRAM0[src] * -1;
	}
}
void ABS32(uint16_t dist, uint16_t src){//32λ�������ֵ
	if(NVRAM0[src] >= 0){
		NVRAM0[dist] = NVRAM0[src];
	}
	else{
		NVRAM0[dist] = NVRAM0[src] * -1;
	}
}
void SWAP(uint16_t dist, uint16_t src){//����A�ĸߵ��ֽ�
	uint16_t tmpL = 0, tmpH = 0;
	tmpL = (NVRAM0[src] & 0x00FF);
	tmpH = (NVRAM0[src] >> 8) & 0x00FF;
	tmpH |= tmpL;
	NVRAM0[dist] = tmpH;
}
void LIMS16(uint16_t src, uint16_t min, uint16_t max){//�з���16λ�����Ʒ���ָ��
	if(NVRAM0[src] > NVRAM0[max]){
		NVRAM0[src] = NVRAM0[max];
	}
	if(NVRAM0[src] < NVRAM0[min]){
		NVRAM0[src] = NVRAM0[min];
	}
}
/*****************************************************************************/
void BCPY(uint16_t dist, uint16_t src, uint16_t length) {//�鸴��
	uint16_t i;
	for(i = 0;i < length;i ++){
		NVRAM0[dist + i] = NVRAM0[src + i];
	}
}
void NVFSAVE(void){//NVRAMȫ��д��EPROM
	disableSplcIsr();
	saveNvram();
	enableSplcIsr();
}
void NVSAVE(void){//����NVRAM�������ݵ�EPROM
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
void FDSAV_ONE(int16_t cn){//����һ��������EPROM��
	uint32_t crc32;
	disableSplcIsr();
	if(cn > (CONFIG_HMI_SCHEME_NUM - 1)){
		cn = (CONFIG_HMI_SCHEME_NUM - 1);
	}
	if(cn < 0){
		cn = 0;
	}
	epromWrite((cn * 128 + CONFIG_EPROM_FD_START), (uint8_t*)(cn * 64 + FDRAM), 128);
	crc32 = HAL_CRC_Calculate(&hcrc, (uint32_t *)(FDRAM), (CONFIG_FDRAM_SIZE / 2));
	epromWriteDword(CONFIG_EPROM_FD_CRC, &crc32);//�ڵ�ָ����ַ��ʼд��32λ��	
	printf("%s,%d,%s:save One FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	enableSplcIsr();
}
void FDLAD(void){//FDRAM<-EPROM
	disableSplcIsr();
	loadFdram();
	enableSplcIsr();
}



/*****************************************************************************/
//IOָ��
void IMDIO(void) {//��������IO��״̬���������

}
//��ָ��
//void TO(uint16_t SA) {//������ʼָ��
//}
//void STP(uint16_t SA) {//����ָ��
//}
//void STPEND(void) {//��������ָ��
//}
//void FROM(uint16_t SA) {//����ִ��ָ��
//}

void PRTM(uint16_t adr, uint8_t len){//�ڴ����ж��ϴ�ӡ�ڴ�����
	uint16_t index;
	index = adr;
	printf("NVRAM MEMORY TABLE:\n");
	printf("  ADR:  +0,  +1,  +2,  +3,  +4,  +5,  +6   +7,  +8,  +9, +10, +11, +12, +13, +14, +15\n");
	printf("00000:FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF,FFFF\n");
	for(index = adr & 0xFFF0;index < (adr + len);index ++){
		if(index > UINT16_MAX){
			printf("\n\n");
			printf("END OF NVRAM\n");
			break;
		}
		if((index & 0x000F) == 0x0){//����ʼ
			printf("%5d:", (index & 0xFFF0));
		}
		printf(",%04X",NVRAM0[index]);
		if((index & 0x000F) == 0xF){//���һ��
			printf("\n");
		}
	}
}






