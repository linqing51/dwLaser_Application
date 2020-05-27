#include "sPlc.h"
//����ָ��Ͷ�̬RAM���� ��ֲ�󲿷�8BIT��16BIT��Ƭ��Ч�ʵʹ�������
/*****************************************************************************/
int16_t NVRAM0[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��ǰ �����浵�Ĵ���
int16_t NVRAM1[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��һ��
int16_t FDRAM[CONFIG_FDRAM_SIZE];//�浵�Ĵ���
uint8_t TimerCounter_1mS = 0;
uint8_t TimerCounter_10mS = 0;
uint8_t TimerCounter_100mS = 0;
uint8_t TD_10MS_SP = 0;
uint8_t TD_100MS_SP = 0;
uint8_t TD_1000MS_SP = 0;
uint32_t sPlcEnterTime, sPlcExitTime, sPlcScanTime;
/******************************************************************************/
void assertCoilAddress(uint16_t adr){//�����Ȧ��ַ
#if CONFIG_SPLC_ASSERT == 1
	uint32_t maxCoilAdr = CONFIG_NVRAM_SIZE * 16 - 1;
	if(adr > (maxCoilAdr)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
void assertRegisterAddress(uint16_t adr){//���Ĵ�����ַ
#if CONFIG_SPLC_ASSERT == 1
	if(adr > (CONFIG_NVRAM_SIZE - 1)){
		while(1);
	}
#else
	adr = ~adr;
#endif
}
void loadNvram(void){//��EPROM������NVRAM
	uint16_t i;
#if CONFIG_SPLC_USING_EPROM == 1
	epromRead(CONFIG_EPROM_NVRAM_START, (uint8_t*)NVRAM0, (CONFIG_NVRAM_SIZE * 2));//��EPROM�лָ�MR
#endif
	for(i = R_START;i <= TMP_END;i ++){
		NVRAM0[i] = 0x0;
	}
	memcpy((uint8_t*)NVRAM1, (uint8_t*)NVRAM0, (CONFIG_NVRAM_SIZE * 2));
}
void saveNvram(void){//ǿ�ƽ�NVRAM����EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	epromWrite(CONFIG_EPROM_NVRAM_START, (uint8_t*)NVRAM0, ((MR_END + 1) * 2));
#endif
}
void updateNvram(void){//����NVRAM->EPROM
	uint8_t *sp0, *sp1;
	uint16_t i;
	sp0 = (uint8_t*)NVRAM0;
	sp1 = (uint8_t*)NVRAM1;
	//����MR��DM
	for(i = (CONFIG_EPROM_NVRAM_START + (MR_START * 2));i < ((DM_END + 1) * 2);i ++){//����MR
		if(*sp0 != *sp1){
#if CONFIG_SPLC_USING_EPROM == 1
			epromWriteByte(i, *sp0);
#endif
		}
		sp0 ++;
		sp1 ++;
	}
	memcpy((uint8_t*)(NVRAM1), (uint8_t*)(NVRAM0), (CONFIG_NVRAM_SIZE * 2));//����NVRAM1 �Ǳ��ּĴ���
}
void clearNvram(void){//���NVRAM����	
	uint16_t i = 0;
	enterSplcIsr();
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = CONFIG_EPROM_NVRAM_START; i< (CONFIG_NVRAM_SIZE * 2);i ++){
		epromWriteByte(i, 0x0);//?BUG
	}
#endif
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));//��ʼ��NVRAM0
	memset((uint8_t*)NVRAM1, 0x0, (CONFIG_NVRAM_SIZE * 2));//��ʼ��NVRAM1
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
	epromRead(CONFIG_EPROM_FDRAM_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));//��EPROM�лָ�MR
	feedWatchDog();
#endif
}
void saveFdram(void){//ǿ�ƽ�FDRAM����EPROM
#if CONFIG_SPLC_USING_EPROM == 1
	epromWrite(CONFIG_EPROM_FDRAM_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));
	feedWatchDog();
#endif
}
void clearFdram(void){//���FDRAM����
	uint16_t i;
	disableWatchDog();
#if CONFIG_SPLC_USING_EPROM == 1
	for(i = CONFIG_EPROM_FDRAM_START; i< (CONFIG_FDRAM_SIZE * 2) ; i++){
#if CONFIG_SPLC_USING_EPROM == 1
		epromWriteByte(i, 0x0);
#endif
	}
#endif
	memset(FDRAM, 0x0, (CONFIG_FDRAM_SIZE * 2));//��ʼ��FDRAM
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
	initSplcTimer();//��ʼ��Ӳ����ʱ��ģ��
	SSET(SPCOIL_ON);
#if CONFIG_SPLC_USING_BEEM == 1
	RRES(SPCOIL_BEEM_ENABLE);
	NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_BEEM_FREQ;
	NVRAM0[SPREG_BEEM_DUTYCYCLE] = CONFIG_SPLC_DEFAULT_BEEM_DUTYCYCLE;
	NVRAM0[SPREG_BEEM_COUNTER] = 0;
#endif

#if CONFIG_SPLC_USING_LEDAIM == 1
	RRES(SPCOIL_AIM_ENABEL);
	NVRAM0[SPREG_AIM_DUTYCYCLE] = 0;
	NVRAM0[SPREG_RED_LED_DUTYCYCLE] = 0;
	NVRAM0[SPREG_GREEN_LED_DUTYCYCLE] = 0;
	NVRAM0[SPREG_BLUE_LED_DUTYCYCLE] = 0;
#endif

#if CONFIG_SPLC_USING_MUSIC == 1
	NVRAM0[SPREG_MUSIC_VOLUME] = 0;									
	NVRAM0[SPREG_PLAYING_MUSIC_ID] = 0;							
	NVRAM0[SPREG_NEXT_MUSIC_ID] = 0;									
	NVRAM0[SPREG_CONTROL_MUSIC]	= CMD_MUSIC_STOP;									
#endif

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
	//enableSplcIsr();
#if CONFIG_SPLC_USING_DK25L == 1
	delayMs(100);
	DL25L_Init();//���жϺ�����
#endif
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




