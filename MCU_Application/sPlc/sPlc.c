#include "sPlc.h"
/*****************************************************************************/
int16_t NVRAM0_MR[MR_SIZE];//��Ȧ ����
int16_t NVRAM1_MR[MR_SIZE];//��Ȧ ����
/*****************************************************************************/
int16_t NVRAM0_DM[DM_SIZE];//���ݼĴ���
int16_t NVRAM1_DM[DM_SIZE];//���ݼĴ���
/*****************************************************************************/
int16_t NVRAM0_R[R_SIZE];//��Ȧ�Ǳ���
int16_t NVRAM1_R[R_SIZE];//��Ȧ�Ǳ���
/*****************************************************************************/
int16_t NVRAM0_EM[EM_SIZE];//���ݼĴ����Ǳ���
/*****************************************************************************/
int16_t NVRAM0_T_1MS[T_1MS_SIZE];//��ʱ��Ȧ1MS
int16_t NVRAM1_T_1MS[T_1MS_SIZE];//��ʱ��Ȧ1MS
int16_t NVRAM0_T_10MS[T_10MS_SIZE];//��ʱ��Ȧ10MS
int16_t NVRAM1_T_10MS[T_10MS_SIZE];//��ʱ��Ȧ10MS
int16_t NVRAM0_T_100MS[T_100MS_SIZE];//��ʱ��Ȧ100MS
int16_t NVRAM1_T_100MS[T_100MS_SIZE];//��ʱ��Ȧ100MS
/*****************************************************************************/
int16_t NVRAM0_T_1MS_ENA[T_1MS_ENA_SIZE];//��ʱ��ʹ��1MS
int16_t NVRAM1_T_1MS_ENA[T_1MS_ENA_SIZE];//��ʱ��ʹ��1MS
int16_t NVRAM0_T_10MS_ENA[T_10MS_ENA_SIZE];//��ʱ��ʹ��10MS
int16_t NVRAM1_T_10MS_ENA[T_10MS_ENA_SIZE];//��ʱ��ʹ��10MS
int16_t NVRAM0_T_100MS_ENA[T_100MS_ENA_SIZE];//��ʱ��ʹ��100MS
int16_t NVRAM1_T_100MS_ENA[T_100MS_ENA_SIZE];//��ʱ��ʹ��100MS
/*****************************************************************************/
int16_t NVRAM0_TD_1MS[TD_1MS_SIZE];//��ʱ��ʱ��1MS
int16_t NVRAM0_TD_10MS[TD_10MS_SIZE];//��ʱ��ʱ��10MS
int16_t NVRAM0_TD_100MS[TD_100MS_SIZE];//��ʱ��ʱ��100MS
/*****************************************************************************/
int16_t NVRAM0_X[X_SIZE];//����λ�Ĵ���
int16_t NVRAM1_X[X_SIZE];//����λ�Ĵ���
/*****************************************************************************/
int16_t NVRAM0_Y[Y_SIZE];//���λ�Ĵ���
int16_t NVRAM1_Y[Y_SIZE];//���λ�Ĵ���
/*****************************************************************************/
int16_t NVRAM0_SPREG[SPREG_SIZE];//����Ĵ���
/*****************************************************************************/
int16_t NVRAM0_SPCOIL[SPCOIL_SIZE];//������Ȧ
int16_t NVRAM1_SPCOIL[SPCOIL_SIZE];//������Ȧ
/*****************************************************************************/
int16_t NVRAM0_TMP[TMP_SIZE];//��ʱ�Ĵ���
/*****************************************************************************/
int16_t FDRAM0[FDRAM_SIZE];//�浵�Ĵ���
/*****************************************************************************/
uint8_t TimerCounter_1mS = 0;
uint8_t TimerCounter_10mS = 0;
uint8_t TimerCounter_100mS = 0;
uint8_t TD_10MS_SP = 0;
uint8_t TD_100MS_SP = 0;
uint8_t TD_1000MS_SP = 0;
uint32_t sPlcEnterTime, sPlcExitTime, sPlcScanTime;
/******************************************************************************/
void assertAddress(uint8_t tp, uint16_t adr){//����ַ
#if CONFIG_SPLC_ASSERT == 1
	adr += 1;
	switch(tp){
		case TYPE_MR:{
			if(adr > (MR_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_DM:{
			if(adr > DM_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_R:{
			if(adr > (R_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_EM:{
			if(adr > EM_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_T_1MS:{
			if(adr > (T_1MS_SIZE * 16)){
				while(1);
			}
		}
		case TYPE_T_10MS:{
			if(adr > (T_10MS_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_T_100MS:{
			if(adr > (T_100MS_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_T_1MS_ENA:{
			if(adr > (T_1MS_ENA_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_T_10MS_ENA:{
			if(adr > (T_10MS_ENA_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_T_100MS_ENA:{
			if(adr > (T_100MS_ENA_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_TD_1MS:{
			if(adr > TD_1MS_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_TD_10MS:{
			if(adr > TD_10MS_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_TD_100MS:{
			if(adr > TD_100MS_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_X:{
			if(adr > (TYPE_X_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_Y:{
			if(adr > (TYPE_Y_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_SPREG:{
			if(adr > TYPE_SPREG_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_SPCOIL:{
			if(adr >> (TYPE_SPCOIL_SIZE * 16)){
				while(1);
			}
			break;
		}
		case TYPE_TMP:{
			if(adr > TYPE_TMP_SIZE){
				while(1);
			}
			break;
		}
		case TYPE_FDRAM:{
			if(adr > TYPE_FDRAM_SIZE){
				while(1);
			}
			break;
		}
		default:break;
	}
#endif
}
void loadNvram(void){//��EPROM������NVRAM
	uint16_t i;
#if CONFIG_SPLC_USING_EPROM == 1
	epromRead(CONFIG_EPROM_MR_START, (uint8_t*)NVRAM0_MR, (MR_SIZE * 2));//��EPROM�лָ�MR
	epromRead(CONFIG_EPROM_DM_START, (uint8_t*)NVRAM0_DM, (DM_SIZE * 2));//��EPROM�лָ�DM
#endif
	memcpy((uint8_t*)NVRAM1_MR, (uint8_t*)NVRAM0_MR, (MR_SIZE * 2));
	memcpy((uint8_t*)NVRAM1_DM, (uint8_t*)NVRAM0_DM, (DM_SIZE * 2));
}
void saveNvram(void){//ǿ�ƽ�NVRAM����EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	epromWrite(CONFIG_EPROM_MR_START, (uint8_t*)NVRAM0_MR, (MR_SIZE * 2));//��MR����EPROM
	epromWrite(CONFIG_EPROM_DM_START, (uint8_t*)NVRAM0_DM, (DM_SIZE * 2));//��DM����EPROM
#endif
}
void updateNvram(void){//����NVRAM->EPROM
	uint8_t *sp0, *sp1;
	uint16_t i;
	//����MR
	sp0 = (uint8_t*)NVRAM0_MR;
	sp1 = (uint8_t*)NVRAM1_MR;
	for(i = CONFIG_EPROM_MR_START;i < (MR_SIZE * 2);i ++){//����MR
		if(*sp0 != *sp1){
#if CONFIG_SPLC_USING_EPROM == 1
			epromWriteByte(i, *sp0);
#endif
		}
		sp0 ++;
		sp1 ++;
	}
	//����DM
	sp0 = (uint8_t*)NVRAM0_DM;
	sp1 = (uint8_t*)NVRAM1_DM;
	for(i = CONFIG_EPROM_DM_START;i < (DM_SIZE * 2);i ++){//����DM
		if(*sp0 != *sp1){
#if CONFIG_SPLC_USING_EPROM == 1
			epromWriteByte(i, *sp0);
#endif
		}
		sp0 ++;
		sp1 ++;
	}
	memcpy((uint8_t*)(NVRAM1_MR),          (uint8_t*)(NVRAM0_MR),          (MR_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_DM),          (uint8_t*)(NVRAM0_DM),          (DM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_R),           (uint8_t*)(NVRAM0_R),           (R_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_1MS),       (uint8_t*)(NVRAM0_T_1MS),       (T_1MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_10MS),      (uint8_t*)(NVRAM0_T_10MS),      (T_10MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_100MS),     (uint8_t*)(NVRAM0_T_100MS),     (T_100MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_1MS_ENA),   (uint8_t*)(NVRAM0_T_1MS_ENA),   (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_10MS_ENA),  (uint8_t*)(NVRAM0_T_10MS_ENA),  (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_100MS_ENA), (uint8_t*)(NVRAM0_T_100MS_ENA), (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_X_SIZE),      (uint8_t*)(NVRAM0_X_SIZE),      (X_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_Y_SIZE),      (uint8_t*)(NVRAM0_Y_SIZE),      (Y_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_SPCOIL),      (uint8_t*)(NVRAM0_SPCOIL),      (SPCOIL_SIZE * 2));
}
void clearNvram(void){//���NVRAM����	
	uint16_t i = 0;
	enterSplcIsr();
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = CONFIG_EPROM_MR_START; i< (MR_SIZE * 2);i ++){
		epromWriteByte(i, 0x00);
	}
	for(i = CONFIG_EPROM_DM_START; i< (DM_SIZE * 2);i ++){
		epromWriteByte(i, 0x00);
	}
#endif
	memset((uint8_t*)(NVRAM0_MR), 			0x0, (MR_SIZE * 2));
	memset((uint8_t*)(NVRAM1_MR), 			0x0, (MR_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_DM), 			0x0, (DM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_DM), 			0x0, (DM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_R), 			0x0, (R_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_R), 			0x0, (R_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_EM), 			0x0, (EM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_EM), 			0x0, (EM_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_1MS), 		0x0, (T_1MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_1MS), 		0x0, (T_1MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_10MS), 		0x0, (T_10MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_10MS), 		0x0, (T_10MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_100MS), 		0x0, (T_100MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_100MS), 		0x0, (T_100MS_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_1MS_ENA),   	0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_1MS_ENA),   	0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_10MS_ENA),  	0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_10MS_ENA),  	0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_T_100MS_ENA),  0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_T_100MS_ENA),  0x0, (T_1MS_ENA_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_X_SIZE),       0x0, (X_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_X_SIZE),       0x0, (X_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_Y_SIZE),       0x0, (Y_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_Y_SIZE),       0x0, (Y_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_SPCOIL),       0x0, (SPCOIL_SIZE * 2));
	memcpy((uint8_t*)(NVRAM1_SPCOIL),       0x0, (SPCOIL_SIZE * 2));
	memcpy((uint8_t*)(NVRAM0_TMP),          0x0, (TMP_SIZE * 2));
	exitSplcIsr();//�ָ��ж�
}
void clearEprom(void){
	uint16_t i;
	//���EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = 0;i < CONFIG_EPROM_SIZE;i ++){
		epromWriteByte(i, 0x0);
	}
	//д��У����
	epromWriteByte((CONFIG_EPROM_SIZE - 4), 0x55);
	epromWriteByte((CONFIG_EPROM_SIZE - 3), 0xAA);
	epromWriteByte((CONFIG_EPROM_SIZE - 2), 0xBC);
	epromWriteByte((CONFIG_EPROM_SIZE - 1), 0xD4);
#endif
}
extern void loadDefault(void);
void checkEprom(void){
	uint16_t i;
	uint8_t checkCode[4];
#if CONFIG_SPLC_USING_EPROM == 1
	checkCode[0] = 0;
	checkCode[1] = 0;
	checkCode[2] = 0;
	checkCode[3] = 0;
	epromRead((CONFIG_EPROM_SIZE - 4), checkCode, 4);//��EPROM�лָ�MR
	if((checkCode[0] != 0x55) || (checkCode[1] != 0xAA) || (checkCode[2] != 0xBC) || (checkCode[3] != 0xD1)){
		//��⵽У����������EPROM
#if CONFIG_SPLC_USING_EPROM == 1
		for(i = 0; i< CONFIG_EPROM_SIZE;i ++){
			epromWriteByte(i, 0x0);
		}
		epromWriteByte((CONFIG_EPROM_SIZE - 4), 0x55);
		epromWriteByte((CONFIG_EPROM_SIZE - 3), 0xAA);
		epromWriteByte((CONFIG_EPROM_SIZE - 2), 0xBC);
		epromWriteByte((CONFIG_EPROM_SIZE - 1), 0xD1);
#endif
		loadDefault();
	}
#endif
}

void loadFdram(void){//��EPROM������FDRAM
#if CONFIG_SPLC_USING_EPROM == 1
	epromRead(CONFIG_EPROM_FDRAM_START, (uint8_t*)FDRAM, (FDRAM_SIZE * 2));//��EPROM�лָ�MR
	feedWatchDog();
#endif
}
void saveFdram(void){//ǿ�ƽ�FDRAM����EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	epromWrite(CONFIG_EPROM_FDRAM_START, (uint8_t*)FDRAM, (FDRAM_SIZE * 2));
	feedWatchDog();
#endif
}
void clearFdram(void){//���FDRAM����
	uint16_t i;
	disableWatchDog();
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = CONFIG_EPROM_FDRAM_START; i< (FDRAM_SIZE * 2) ; i++){
#if CONFIG_SPLC_USING_EPROM == 1
		epromWriteByte(i, 0x0);
#endif
	}
#endif
	memset(FDRAM, 0x0, (FDRAM_SIZE * 2));//��ʼ��FDRAM
}

void sPlcSpwmLoop(void){//SPWM��ѯ	
	if(LDP(SPCOIL_PS10MS)){//ÿ10mSִ��һ��
		//SPWM0
		if(LD(SPCOIL_SPWM_RESET_0)){//��λ
			NVRAM0[SPREG_SPWM_COUNTER_0] = SHRT_MAX;
			RRES(SPCOIL_SPWM_RESET_0);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_0] == NVRAM0[SPREG_SPWM_POS_SHADOW_0]){//����ƥ�䷭ת���
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
			RRES(SPCOIL_SPWM_OUT_0);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_0] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0]){//�������
			NVRAM0[SPREG_SPWM_COUNTER_0] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_0] = NVRAM0[SPREG_SPWM_POS_0];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = NVRAM0[SPREG_SPWM_CYCLE_0];
			SSET(SPCOIL_SPWM_OUT_0);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
		}
		//SPWM1
		if(LD(SPCOIL_SPWM_RESET_1)){//��λ
			NVRAM0[SPREG_SPWM_COUNTER_1] = SHRT_MAX;
			RRES(SPCOIL_SPWM_RESET_1);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_1] == NVRAM0[SPREG_SPWM_POS_SHADOW_1]){//����ƥ�䷭ת���
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
			RRES(SPCOIL_SPWM_OUT_1);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_1] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1]){//�������
			NVRAM0[SPREG_SPWM_COUNTER_1] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_1] = NVRAM0[SPREG_SPWM_POS_1];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = NVRAM0[SPREG_SPWM_CYCLE_1];
			SSET(SPCOIL_SPWM_OUT_1);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
		}
		//SPWM2
		if(LD(SPCOIL_SPWM_RESET_2)){//��λ
			NVRAM0[SPREG_SPWM_COUNTER_2] = SHRT_MAX;
			RRES(SPCOIL_SPWM_RESET_2);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_2] == NVRAM0[SPREG_SPWM_POS_SHADOW_2]){//����ƥ�䷭ת���
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
			RRES(SPCOIL_SPWM_OUT_2);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_2] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2]){//�������
			NVRAM0[SPREG_SPWM_COUNTER_2] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_2] = NVRAM0[SPREG_SPWM_POS_2];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2] = NVRAM0[SPREG_SPWM_CYCLE_2];
			SSET(SPCOIL_SPWM_OUT_2);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
		}
		//SPWM3
		if(LD(SPCOIL_SPWM_RESET_3)){//��λ
			NVRAM0[SPREG_SPWM_COUNTER_3] = SHRT_MAX;
			RRES(SPCOIL_SPWM_RESET_3);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_3] == NVRAM0[SPREG_SPWM_POS_SHADOW_3]){//����ƥ�䷭ת���
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
			RRES(SPCOIL_SPWM_OUT_3);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_3] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3]){//�������
			NVRAM0[SPREG_SPWM_COUNTER_3] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_3] = NVRAM0[SPREG_SPWM_POS_3];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = NVRAM0[SPREG_SPWM_CYCLE_3];
			SSET(SPCOIL_SPWM_OUT_3);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
		}
	}
}

/*****************************************************************************/
void sPlcInit(void){//���߼���ʼ��
	loadNvram();//�ϵ�ָ�NVRAM
	SSET(SPCOIL_ON);
	RRES(SPCOIL_BEEM_ENABLE);
	NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_BEEM_FREQ;
	NVRAM0[SPREG_BEEM_DUTYCYCLE] = CONFIG_SPLC_DEFAULT_BEEM_DUTYCYCLE;
	NVRAM0[SPREG_BEEM_COUNTER] = 0;
	RRES(SPCOIL_AIM_ENABEL);
	NVRAM0[SPREG_AIM_DUTYCYCLE] = 0;
	NVRAM0[SPREG_RED_LED_DUTYCYCLE] = 0;
	NVRAM0[SPREG_GREEN_LED_DUTYCYCLE] = 0;
	NVRAM0[SPREG_BLUE_LED_DUTYCYCLE] = 0;
	NVRAM0[SPREG_MUSIC_VOLUME] = 0;									
	NVRAM0[SPREG_PLAYING_MUSIC_ID] = 0;							
	NVRAM0[SPREG_NEXT_MUSIC_ID] = 0;									
	NVRAM0[SPREG_CONTROL_MUSIC]	= CMD_MUSIC_STOP;									
#if CONFIG_SPLC_USING_IO_INPUT == 1
	inputInit();
#endif
#if CONFIG_SPLC_USING_IO_OUTPUT == 1
	outputInit();
#endif
#if CONFIG_SPLC_USING_DAC == 1	
	initChipDac();//��ʼ��DACģ��
#endif
#if CONFIG_SPLC_USING_ADC == 1
	initChipAdc();//��ʼ��ADCģ��
#endif
#if CONFIG_SPLC_USING_LASER == 1
	sPlcLaserInit();
#endif
	SSET(SPCOIL_ON);
	SSET(SPCOIL_START_UP);
	NVRAM0[SPREG_IDENTITY] = CONFIG_SPLC_DEV;
#if CONFIG_SPLC_USING_DK25L == 1
	delayMs(100);
	DL25L_Init();//���жϺ�����
#endif
	initSplcTimer();//��ʼ��Ӳ����ʱ��ģ�� ������ʱ��
}
void sPlcProcessStart(void){//sPLC��ѯ��ʼ
	sPlcEnterTime = HAL_GetTick();
	if(TD_10MS_SP >= 1){
		FLIP(SPCOIL_PS10MS);
		TD_10MS_SP = 0;
	}
	if(TD_100MS_SP >= 1){
		FLIP(SPCOIL_PS100MS);
		TD_100MS_SP = 0;
	}
	if(TD_1000MS_SP >= 1){
		FLIP(SPCOIL_PS1000MS);
		TD_1000MS_SP = 0;
	}
#if CONFIG_SPLC_USING_CLEAR_NVRAM == 1 && CONFIG_SPLC_USING_EPROM == 1
	if(NVRAM0[SPREG_CLEAR_NVRAM] == (int16_t)CONFIG_SPLC_CLEAR_CODE){
		disableSplcTimer();//�ر��ж�	
		if(epromTest()){//EPROM���Գɹ�
			__nop();
		}
		else{//EPROM����ʧ��
			__nop();
		}
		clearNvram();
		REBOOT();	
	}
#endif
#if CONFIG_SPLC_USING_IO_INPUT == 1
	inputRefresh();//��ȡX������
#endif
#if CONFIG_SPLC_USING_SPWM == 1
	sPlcSpwmLoop();
#endif
#if CONFIG_SPLC_USING_ADC == 1
	chipAdcProcess();//ADC ����NVRAM
#endif
}
void sPlcProcessEnd(void){//sPLC��ѯ����
#if CONFIG_SPLC_USING_IO_OUTPUT == 1
	outputRefresh();//����Y�����
#endif
#if CONFIG_SPLC_USING_BEEM == 1
	sPlcBeemLoop();
#endif
#if	CONFIG_SPLC_USING_LEDAIM == 1
	sPlcAimLoop();
#endif
	updateNvram();//����NVRAM
	RRES(SPCOIL_START_UP);
	sPlcExitTime = HAL_GetTick();
	sPlcScanTime = sPlcExitTime - sPlcEnterTime;
	NVRAM0[SPREG_SCAN_TIME] = (uint16_t)sPlcScanTime;
}




