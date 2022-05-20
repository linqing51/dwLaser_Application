#include "sPlc.h"
//����ָ��Ͷ�̬RAM���� ��ֲ�󲿷�8BIT��16BIT��Ƭ��Ч�ʵʹ�������
/*****************************************************************************/
int16_t NVRAM0[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��ǰ �����浵�Ĵ���
int16_t NVRAM1[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��һ��
int16_t FDRAM[CONFIG_FDRAM_SIZE];//�浵�Ĵ���
uint8_t LKSRAM[CONFIG_LKSRAM_SIZE];//ͨ�ŷ��ͻ�����
uint8_t LKRRAM[CONFIG_LKRRAM_SIZE];//ͨ�Ž��ջ�����
/*****************************************************************************/
uint16_t TimerCounter_10mS = 0;//10����
uint16_t TimerCounter_100mS = 0;//100����
uint16_t TimerCounter_200mS = 0;//200����
uint16_t TimerCounter_500mS = 0;//500����
uint16_t TimerCounter_1000mS = 0;//1��
uint16_t TimerCounter_60000mS = 0;//1����
/*****************************************************************************/
uint8_t TD_10MS_SP = 0;
uint8_t TD_100MS_SP = 0;
uint8_t TD_200MS_SP = 0;
uint8_t TD_500MS_SP = 0;
uint8_t TD_1000MS_SP = 0;
uint8_t TD_60000MS_SP = 0;
uint32_t sPlcEnterTime, sPlcExitTime, sPlcScanTime;
/******************************************************************************/
extern CRC_HandleTypeDef hcrc;
/******************************************************************************/
void errorHandler(uint16_t errCode){
	while(1);
}

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
void loadNvram(void){//��EPROM������NVRAM MR��DM
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));
	//��EPROM�лָ�MR NVRAM
	epromRead(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE * 2));//��EPROM�лָ�MR
	//��EPROM�лָ�DM NVRAM
	epromRead(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE * 2));//��EPROM�лָ�DM
	memcpy((uint8_t*)NVRAM1, (uint8_t*)NVRAM0, (CONFIG_NVRAM_SIZE * 2));
}
void saveNvram(void){//ǿ�ƽ�NVRAM����EPROM
	//MR NVRAMд��EPROM
	epromWrite(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE * 2));//��NVRAM��MR������EPROM																				
	//DM NVRAMд��EPROM
	epromWrite(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE * 2));//��NVRAM��DM������EPROM
}
void updateNvram(void){//����NVRAM->EPROM
	uint8_t *sp0, *sp1;
	uint16_t i;
	//����MR
	sp0 = (uint8_t*)(NVRAM0 + MR_START);
	sp1 = (uint8_t*)(NVRAM1 + MR_START);
	for(i = 0;i < (CONFIG_MRRAM_SIZE * 2);i ++){//����MR
		if(*sp0 != *sp1){
			epromWriteByte((i + CONFIG_EPROM_MR_START), sp0);
		}
		sp0 ++;
		sp1 ++;
	}
	//����DM
	sp0 = (uint8_t*)(NVRAM0 + DM_START);
	sp1 = (uint8_t*)(NVRAM1 + DM_START);
	for(i = 0;i < (CONFIG_DMRAM_SIZE * 2);i ++){//����MR
		if(*sp0 != *sp1){
			epromWriteByte((i + CONFIG_EPROM_DM_START), sp0);
		}
		sp0 ++;
		sp1 ++;
	}	
	memcpy((uint8_t*)(NVRAM1), (uint8_t*)(NVRAM0), (CONFIG_NVRAM_SIZE * 2));//����NVRAM1 �Ǳ��ּĴ���
}
void clearNvram(void){//���NVRAM����	
	uint16_t i = 0;
	enterSplcIsr();
	//���EPROM MR��
	for(i = CONFIG_EPROM_MR_START; i< (CONFIG_MRRAM_SIZE * 2);i ++){
		epromWriteByte(i, 0x0);//
	}
	//���EPROM DM��
	for(i = CONFIG_EPROM_DM_START; i< (CONFIG_DMRAM_SIZE * 2);i ++){
		epromWriteByte(i, 0x0);//
	}
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));//��ʼ��NVRAM0
	memset((uint8_t*)NVRAM1, 0x0, (CONFIG_NVRAM_SIZE * 2));//��ʼ��NVRAM1
	exitSplcIsr();//�ָ��ж�
}

void loadFdram(void){//��EPROM������FDRAM
	HAL_StatusTypeDef ret;
	ret = epromRead(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));//��EPROM�лָ�MR
	if(ret == HAL_OK){
		printf("%s,%d,%s:load FD NVRAM ok...\n",__FILE__, __LINE__, __func__);
	}		
	else{
		printf("%s,%d,%s:load DM NVRAM fail...\n",__FILE__, __LINE__, __func__);
	}
}
void saveFdram(void){//ǿ�ƽ�FDRAM����EPROM
	HAL_StatusTypeDef ret;
	ret = epromWrite(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));
	if(ret == HAL_OK){
		printf("%s,%d,%s:save FD NVRAM ok...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:save FD NVRAM fail...\n",__FILE__, __LINE__, __func__);
	}
}
void clearFdram(void){//���FDRAM����
	uint8_t temp = 0;
	HAL_StatusTypeDef ret;
	enterSplcIsr();
	ret = epromWrite(CONFIG_EPROM_FD_START, &temp, (CONFIG_FDRAM_SIZE * 2));
	memset(FDRAM, 0x0, (CONFIG_FDRAM_SIZE * 2));//��ʼ��FDRAM
	if(ret == HAL_OK){
		printf("%s,%d,%s:clear FD NVRAM ok...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:clear FD NVRAM fail...\n",__FILE__, __LINE__, __func__);
	}
	exitSplcIsr();//�ָ��ж�
}

void clearDeviceConfig(void){//����豸���ò���
	uint16_t i;
	HAL_StatusTypeDef ret;
	enterSplcIsr();
	for(i = CONFIG_EPROM_CONFIG_START; i< CONFIG_EPROM_LOGINFO_START; i++){
		epromWriteByte(i, 0x0);
	}
	if(ret == HAL_OK){
		printf("%s,%d,%s:clear CONFIG NVMAM ok...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:clear FD NVRAM fail...\n",__FILE__, __LINE__, __func__);
	}
	exitSplcIsr();//�ָ��ж�	
}
void clearDeviceLog(void){//����豸��¼
	uint16_t i;
	enterSplcIsr();
	for(i = CONFIG_EPROM_LOGINFO_START; i< (CONFIG_EPROM_LOGINFO_START + 512); i++){
		epromWriteByte(i, 0x0);
	}
	exitSplcIsr();//�ָ��ж�	
}

void sPlcSpwmLoop(void){//SPWM��ѯ	
	if(LDP(SPCOIL_PS10MS)){//ÿ10mSִ��һ��
		//SPWM0
		if(LD(SPCOIL_SPWM_RESET_0)){//��λ
			NVRAM0[SPREG_SPWM_COUNTER_0] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = 0;
			RRES(SPCOIL_SPWM_RESET_0);
			RRES(SPCOIL_SPWM_OUT_0);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_0] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0]){//�������
			NVRAM0[SPREG_SPWM_COUNTER_0] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_0] = NVRAM0[SPREG_SPWM_POS_0];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_0] = NVRAM0[SPREG_SPWM_CYCLE_0];
			SSET(SPCOIL_SPWM_OUT_0);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_0] == NVRAM0[SPREG_SPWM_POS_SHADOW_0]){//����ƥ�䷭ת���
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
			RRES(SPCOIL_SPWM_OUT_0);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_0] = NVRAM0[SPREG_SPWM_COUNTER_0] + 1;
		}
		//SPWM1
		if(LD(SPCOIL_SPWM_RESET_1)){//��λ
			NVRAM0[SPREG_SPWM_COUNTER_1] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = 0; 
			RRES(SPCOIL_SPWM_RESET_1);
			RRES(SPCOIL_SPWM_OUT_1);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_1] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1]){//�������
			NVRAM0[SPREG_SPWM_COUNTER_1] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_1] = NVRAM0[SPREG_SPWM_POS_1];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = NVRAM0[SPREG_SPWM_CYCLE_1];
			SSET(SPCOIL_SPWM_OUT_1);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_1] == NVRAM0[SPREG_SPWM_POS_SHADOW_1]){//����ƥ�䷭ת���
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
			RRES(SPCOIL_SPWM_OUT_1);
		}
		
		else{
			NVRAM0[SPREG_SPWM_COUNTER_1] = NVRAM0[SPREG_SPWM_COUNTER_1] + 1;
		}
		//SPWM2
		if(LD(SPCOIL_SPWM_RESET_2)){//��λ
			NVRAM0[SPREG_SPWM_COUNTER_2] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_1] = 0;
			RRES(SPCOIL_SPWM_RESET_2);
			RRES(SPCOIL_SPWM_OUT_2);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_2] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2]){//�������
			NVRAM0[SPREG_SPWM_COUNTER_2] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_2] = NVRAM0[SPREG_SPWM_POS_2];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_2] = NVRAM0[SPREG_SPWM_CYCLE_2];
			SSET(SPCOIL_SPWM_OUT_2);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_2] == NVRAM0[SPREG_SPWM_POS_SHADOW_2]){//����ƥ�䷭ת���
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
			RRES(SPCOIL_SPWM_OUT_2);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_2] = NVRAM0[SPREG_SPWM_COUNTER_2] + 1;
		}
		//SPWM3
		if(LD(SPCOIL_SPWM_RESET_3)){//��λ
			NVRAM0[SPREG_SPWM_COUNTER_3] = SHRT_MAX;
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = 0;
			RRES(SPCOIL_SPWM_RESET_3);
			RRES(SPCOIL_SPWM_OUT_3);
		}
		if(NVRAM0[SPREG_SPWM_COUNTER_3] >= NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3]){//�������
			NVRAM0[SPREG_SPWM_COUNTER_3] = 0;
			NVRAM0[SPREG_SPWM_POS_SHADOW_3] = NVRAM0[SPREG_SPWM_POS_3];
			NVRAM0[SPREG_SPWM_CYCLE_SHADOW_3] = NVRAM0[SPREG_SPWM_CYCLE_3];
			SSET(SPCOIL_SPWM_OUT_3);
		}
		else if(NVRAM0[SPREG_SPWM_COUNTER_3] == NVRAM0[SPREG_SPWM_POS_SHADOW_3]){//����ƥ�䷭ת���
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
			RRES(SPCOIL_SPWM_OUT_3);
		}
		else{
			NVRAM0[SPREG_SPWM_COUNTER_3] = NVRAM0[SPREG_SPWM_COUNTER_3] + 1;
		}
	}
}
/*****************************************************************************/
void sPlcInit(void){//���߼���ʼ��
	readStm32UniqueID();
#if CONFIG_SPLC_USING_EPROM_TEST == 1
	sPlcEpromTest();
#endif
	printf("\r\r\r\n\n\n");
	printf("MR EPROM:08%XH->08%XH\n", (uint32_t)CONFIG_EPROM_MR_START, (uint32_t)CONFIG_EPROM_MR_END);
	printf("DM EPROM:08%XH->08%XH\n", (uint32_t)CONFIG_EPROM_DM_START, (uint32_t)CONFIG_EPROM_DM_END);
	printf("FD EPROM:08%XH->08%XH\n", (uint32_t)CONFIG_EPROM_FD_START, (uint32_t)CONFIG_EPROM_FD_END);
	printf("CONFIG EPROM:08%X->08%X\n", (uint32_t)CONFIG_EPROM_CONFIG_START, (uint32_t)CONFIG_EPROM_CONFIG_END);
	printf("LOGINFO EPROM:08%XH->08%XH\n", (uint32_t)CONFIG_EPROM_LOGINFO_START,(uint32_t)CONFIG_EPROM_LOGINFO_END);
	printf("%s,%d,%s:start load Nvram......\n",__FILE__, __LINE__, __func__);
	loadNvram();//�ϵ�ָ�NVRAM
	printf("%s,%d,%s:start load Fdram......\n",__FILE__, __LINE__, __func__);
	loadFdram();//�ϵ�ָ�FDRAM
#if CONFIG_USING_DCHMI_APP == 1
	lockPreScheme();//�ָ�Ԥ�跽��
#endif
	SSET(SPCOIL_ON);
	SSET(SPCOIL_START_UP);
	NVRAM0[SPREG_IDENTITY] = CONFIG_SPLC_DEV;
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
	printf("%s,%d,%s:start input init......\n",__FILE__, __LINE__, __func__);
	inputInit();
#endif

#if CONFIG_SPLC_USING_IO_OUTPUT == 1
	printf("%s,%d,%s:start output init......\n",__FILE__, __LINE__, __func__);
	outputInit();
#endif

#if CONFIG_SPLC_USING_DAC == 1	
	printf("%s,%d,%s:start Dac init......\n",__FILE__, __LINE__, __func__);
	initChipDac();//��ʼ��DACģ��
	UPDAC0();
	UPDAC1();
	UPDAC2();
	UPDAC3();
#endif

#if CONFIG_SPLC_USING_ADC == 1
	printf("%s,%d,%s:start adc init......\n",__FILE__, __LINE__, __func__);
	initChipAdc();//��ʼ��ADCģ��
#endif

#if CONFIG_SPLC_USING_LASER == 1
	printf("%s,%d,%s:start laser timer init......\n",__FILE__, __LINE__, __func__);
	sPlcLaserInit();
#endif

#if CONFIG_SPLC_USING_DK25L == 1
	printf("%s,%d,%s:start NFC init......\n",__FILE__, __LINE__, __func__);
	delayMs(100);
	DL25L_Init();//���жϺ�����
#endif

	printf("%s,%d,%s:start splc timer init......\n",__FILE__, __LINE__, __func__);
	initSplcTimer();//��ʼ��Ӳ����ʱ��ģ�� ������ʱ��
#if CONFIG_SPLC_USING_SPK == 1	
	printf("%s,%d,%s:start loudspeaker dma init......\n",__FILE__, __LINE__, __func__);
	initLoudspeaker();
#endif
#if CONFIG_SPLC_USING_AIM_PWM == 1
	printf("%s,%d,%s:start aim timer pwm init......\n",__FILE__, __LINE__, __func__);
	setAimFreq(CONFIG_SPLC_AIM_PWM_FREQ);
#endif
#if CONFIG_SPLC_USING_LED_PWM == 1
	printf("%s,%d,%s:start led timer pwm init......\n",__FILE__, __LINE__, __func__);
	setLedFreq(CONFIG_SPLC_LED_PWM_FREQ);
#endif
}
void sPlcProcessStart(void){//sPLC��ѯ��ʼ
	sPlcEnterTime = HAL_GetTick();
	if(TD_10MS_SP >= 1){
		FLIP(SPCOIL_PS10MS);
		TD_10MS_SP = 0;
		if(NVRAM0[SPREG_BEEM_COUNTER] < INT16_MAX){
			NVRAM0[SPREG_BEEM_COUNTER] ++;
		}
	}
	if(TD_100MS_SP >= 1){
		FLIP(SPCOIL_PS100MS);
		TD_100MS_SP = 0;
	}
	if(TD_200MS_SP >= 1){
		FLIP(SPCOIL_PS200MS);
		TD_200MS_SP = 0;
	}
	if(TD_500MS_SP >= 1){
		FLIP(SPCOIL_PS500MS);
		TD_500MS_SP = 0;
	}
	if(TD_1000MS_SP >= 1){
		FLIP(SPCOIL_PS1000MS);
		TD_1000MS_SP = 0;
	}
	if(TD_60000MS_SP >= 1){
		FLIP(SPCOIL_PS1MINS);
		TD_60000MS_SP = 0;
	}
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
	if(LDP(SPCOIL_PS1000MS)){
		SSET(Y_TICK_LED);
	}
	if(LDN(SPCOIL_PS1000MS)){
		RRES(Y_TICK_LED);
	}
#if CONFIG_SPLC_USING_ADC == 1 && CONFIG_DEBUB_ADC == 1
	if(LDP(SPCOIL_PS1000MS)){
		printf("\n\n");
		printf("%s,%d,%s:SPREG_ADC_0=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_0]);
		printf("%s,%d,%s:SPREG_ADC_1=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_1]);
		printf("%s,%d,%s:SPREG_ADC_2=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_2]);
		printf("%s,%d,%s:SPREG_ADC_3=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_3]);
		printf("%s,%d,%s:SPREG_ADC_4=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_4]);
		printf("%s,%d,%s:SPREG_ADC_5=%d\n", __FILE__, __LINE__, __func__, NVRAM0[SPREG_ADC_5]);
	}
#endif
#if CONFIG_SPLC_USING_IO_OUTPUT == 1
	outputRefresh();//����Y�����
#endif
#if CONFIG_SPLC_USING_SPK == 1
	sPlcLoudspeakerLoop();
#endif
#if	CONFIG_SPLC_USING_AIM_PWM == 1
	sPlcAimLoop();
#endif
#if CONFIG_SPLC_USING_AIM_PWM == 1
	sPlcAutoFanLoop();
#else
	NVRAM0[SPREG_LAS_FAN_SPEED] = 9;
	sPlcAutoFanLoop();
#endif
	updateNvram();//����NVRAM
	RRES(SPCOIL_START_UP);
	sPlcExitTime = HAL_GetTick();
	sPlcScanTime = sPlcExitTime - sPlcEnterTime;
	NVRAM0[SPREG_SCAN_TIME] = (uint16_t)sPlcScanTime;
}




