#include "sPlc.h"
//����ָ��Ͷ�̬RAM���� ��ֲ�󲿷�8BIT��16BIT��Ƭ��Ч�ʵʹ�������
/*****************************************************************************/
#pragma pack(push, 4)
int16_t NVRAM0[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��ǰ �����浵�Ĵ���
int16_t NVRAM1[CONFIG_NVRAM_SIZE];//���籣�ּĴ��� ��һ��
int16_t FDRAM[CONFIG_FDRAM_SIZE];//�浵�Ĵ���
uint8_t LKSRAM[CONFIG_LKSRAM_SIZE];//ͨ�ŷ��ͻ�����
uint8_t LKRRAM[CONFIG_LKRRAM_SIZE];//ͨ�Ž��ջ�����
#pragma pack(pop)
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
	uint32_t crc32_mr, crc32_dm;
	uint32_t crc32_eprom_mr, crc32_eprom_dm;
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));
	//��EPROM�лָ�MR NVRAM
	epromRead(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE * 2));//��EPROM�лָ�MR
	epromReadDword(CONFIG_EPROM_MR_CRC, &crc32_eprom_mr);
	crc32_mr = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE / 2));
	
	//��EPROM�лָ�DM NVRAM
	epromRead(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE * 2));//��EPROM�лָ�DM
	epromReadDword(CONFIG_EPROM_DM_CRC, &crc32_eprom_dm);
	crc32_dm = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE / 2));
	
	memcpy((uint8_t*)NVRAM1, (uint8_t*)NVRAM0, (CONFIG_NVRAM_SIZE * 2));

	if((crc32_eprom_mr != crc32_mr) && (crc32_eprom_dm != crc32_dm)){
		printf("%s,%d,%s:load NVRAM crc fail...\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load NVRAM done...\n",__FILE__, __LINE__, __func__);
	}
}
void saveNvram(void){//ǿ�ƽ�NVRAM����EPROM
	uint32_t crc32_mr, crc32_dm;
	//MR NVRAMд��EPROM
	epromWrite(CONFIG_EPROM_MR_START, (uint8_t*)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE * 2));//��NVRAM��MR������EPROM																				
	crc32_mr = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE / 2));
	epromWriteDword(CONFIG_EPROM_MR_CRC, &crc32_mr);//�ڵ�ָ����ַ��ʼд��32λ��
	//DM NVRAMд��EPROM
	epromWrite(CONFIG_EPROM_DM_START, (uint8_t*)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE * 2));//��NVRAM��DM������EPROM
	crc32_dm = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE / 2));
	epromWriteDword(CONFIG_EPROM_DM_CRC, &crc32_dm);//�ڵ�ָ����ַ��ʼд��32λ��
	printf("%s,%d,%s:save NVRAM done...(MR CRC:0x%08X,DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr, crc32_dm);
}
void updateNvram(void){//����NVRAM->EPROM
	uint8_t *sp0, *sp1;
	uint8_t updateFlagMr, updateFlagDm;
	uint16_t i;
	uint32_t crc32_mr, crc32_dm;
	//����MR
	updateFlagMr = 0;
	sp0 = (uint8_t*)(NVRAM0 + MR_START);
	sp1 = (uint8_t*)(NVRAM1 + MR_START);
	for(i = 0;i < (CONFIG_MRRAM_SIZE * 2);i ++){//����MR
		if(*sp0 != *sp1){
			epromWriteByte((i + CONFIG_EPROM_MR_START), sp0);
			updateFlagMr |= 0xFF;
		}
		sp0 ++;
		sp1 ++;
	}
	if(updateFlagMr){
		crc32_mr = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + MR_START), (CONFIG_MRRAM_SIZE / 2));
		epromWriteDword(CONFIG_EPROM_MR_CRC, &crc32_mr);//�ڵ�ָ����ַ��ʼд��32λ��
	}
	//����DM
	updateFlagDm = 0;
	sp0 = (uint8_t*)(NVRAM0 + DM_START);
	sp1 = (uint8_t*)(NVRAM1 + DM_START);
	for(i = 0;i < (CONFIG_DMRAM_SIZE * 2);i ++){//����MR
		if(*sp0 != *sp1){
			epromWriteByte((i + CONFIG_EPROM_DM_START), sp0);
			updateFlagDm |= 0xFF;
		}
		sp0 ++;
		sp1 ++;
	}
	if(updateFlagDm){
		crc32_dm = HAL_CRC_Calculate(&hcrc,(uint32_t *)(NVRAM0 + DM_START), (CONFIG_DMRAM_SIZE / 2));
		epromWriteDword(CONFIG_EPROM_DM_CRC, &crc32_dm);//�ڵ�ָ����ַ��ʼд��32λ��
	}
	memcpy((uint8_t*)(NVRAM1), (uint8_t*)(NVRAM0), (CONFIG_NVRAM_SIZE * 2));//����NVRAM1 �Ǳ��ּĴ���
	if(updateFlagMr){
		printf("%s,%d,%s:update MR NVRAM done...(MR CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_mr);
	}
	if(updateFlagDm){
		printf("%s,%d,%s:update DM NVRAM done...(DM CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32_dm);
	}
}
void clearNvram(void){//���NVRAM����	
	enterSplcIsr();
	clearEprom(CLEAR_EPROM_NVRAM);//clear mr dm
	memset((uint8_t*)NVRAM0, 0x0, (CONFIG_NVRAM_SIZE * 2));//��ʼ��NVRAM0
	memset((uint8_t*)NVRAM1, 0x0, (CONFIG_NVRAM_SIZE * 2));//��ʼ��NVRAM1
	exitSplcIsr();//�ָ��ж�
	printf("%s,%d,%s:clear NVRAM done...\n",__FILE__, __LINE__, __func__);
}
void loadFdram(void){//��EPROM������FDRAM
	uint32_t crc32_eprom_fd, crc32_fd;
	enterSplcIsr();
	epromRead(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));//��EPROM�лָ�MR
	epromReadDword(CONFIG_EPROM_FD_CRC, &crc32_eprom_fd);
	crc32_fd = HAL_CRC_Calculate(&hcrc,(uint32_t *)FDRAM, (CONFIG_FDRAM_SIZE / 2));
	exitSplcIsr();//�ָ��ж�
	if(crc32_eprom_fd != crc32_fd){
		printf("%s,%d,%s:load FD NVRAM crc fail!!!\n",__FILE__, __LINE__, __func__);
	}
	else{
		printf("%s,%d,%s:load FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	}
}
void saveFdram(void){//ǿ�ƽ�FDRAM����EPROM
	uint32_t crc32;
	enterSplcIsr();
	epromWrite(CONFIG_EPROM_FD_START, (uint8_t*)FDRAM, (CONFIG_FDRAM_SIZE * 2));
	crc32 = HAL_CRC_Calculate(&hcrc,(uint32_t *)(FDRAM), (CONFIG_FDRAM_SIZE / 2));
	epromWriteDword(CONFIG_EPROM_FD_CRC, &crc32);//�ڵ�ָ����ַ��ʼд��32λ��	
	printf("%s,%d,%s:save FD NVRAM done...(FD CRC:0x%08X)\n",__FILE__, __LINE__, __func__, crc32);
	exitSplcIsr();//�ָ��ж�
}
void clearFdram(void){//���FDRAM����
	enterSplcIsr();
	clearEprom(CLEAR_EPROM_FDRAM);//clear mr dm
	memset(FDRAM, 0x0, (CONFIG_FDRAM_SIZE * 2));//��ʼ��FDRAM
	printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	exitSplcIsr();//�ָ��ж�
}
void clearDeviceConfig(void){//����豸���ò���
	enterSplcIsr();
	clearEprom(CLEAR_EPROM_DEVICE_CONFIG);
	printf("%s,%d,%s:clear FD NVRAM done...\n",__FILE__, __LINE__, __func__);
	exitSplcIsr();//�ָ��ж�	
}
void clearDeviceLog(void){//����豸��¼
	enterSplcIsr();
	clearEprom(CLEAR_EPROM_LOG_INFO);
	printf("%s,%d,%s:clear device log done...\n",__FILE__, __LINE__, __func__);
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
void sPlcLoudspeakerLoop(void){//��������ѯ
	int8_t laserStatus0, laserStatus1, laserStatus2, laserStatus3;
	if(LD(SPCOIL_BEEM_ENABLE)){
		setLoudspeakerVolume(NVRAM0[SPREG_BEEM_VOLUME]);
		switch(NVRAM0[SPREG_BEEM_MODE]){//ģʽ
			case BEEM_MODE_0:{
				if(LDB(SPCOIL_BEEM_BUSY)){
					setLoudspeakerEnable();//������Ƶ
					SSET(SPCOIL_BEEM_BUSY);//����������
				}
				break;
			}
			case BEEM_MODE_1:{//ģʽ1 ����ͬ��
				laserStatus0 = getLaserEnable(LASER_CHANNEL_0);
				laserStatus1 = getLaserEnable(LASER_CHANNEL_1);
				laserStatus2 = getLaserEnable(LASER_CHANNEL_2);
				laserStatus3 = getLaserEnable(LASER_CHANNEL_3);
				if(laserStatus0 || laserStatus1 || laserStatus2 || laserStatus3){//LT3763 PWM ON
					if(LDB(SPCOIL_BEEM_BUSY)){//���PWM�����-> �����
						setLoudspeakerEnable();//������Ƶ
						SSET(SPCOIL_BEEM_BUSY);//����������
					}
				}
				else{
					if(LD(SPCOIL_BEEM_BUSY)){
						setLoudspeakerDisable();//������Ƶ
						RRES(SPCOIL_BEEM_BUSY);//�رշ�����	
					}
				}
				break;
			}
			case BEEM_MODE_2:{//ģʽ2 ����� ���ⷢ����		
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 20){//1
					setLoudspeakerEnable();//������Ƶ
					SSET(SPCOIL_BEEM_BUSY);//����������
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 20 && NVRAM0[SPREG_BEEM_COUNTER] < 120){//0
					setLoudspeakerDisable();//ֹͣ��Ƶ
					RRES(SPCOIL_BEEM_BUSY);//�رշ�����
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 120){
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			case BEEM_MODE_3:{//ģʽ3 �ε�����һͣ ������
				if(NVRAM0[SPREG_BEEM_COUNTER] >= 0 && NVRAM0[SPREG_BEEM_COUNTER] < 50){//1
					setLoudspeakerEnable();//������Ƶ
					SSET(SPCOIL_BEEM_BUSY);//����������
					
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 50 && NVRAM0[SPREG_BEEM_COUNTER] < 100){//0
					setLoudspeakerDisable();//�ر���Ƶ
					RRES(SPCOIL_BEEM_BUSY);//�رշ�����
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 100 && NVRAM0[SPREG_BEEM_COUNTER] < 150){//1
					setLoudspeakerEnable();//������Ƶ
					SSET(SPCOIL_BEEM_BUSY);//����������
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 150 && NVRAM0[SPREG_BEEM_COUNTER] < 250){//0
					setLoudspeakerDisable();//�ر���Ƶ
					RRES(SPCOIL_BEEM_BUSY);//�رշ�����
				}
				else if(NVRAM0[SPREG_BEEM_COUNTER] >= 250){//ͣ1��
					NVRAM0[SPREG_BEEM_COUNTER] = -1;
				}
				break;
			}
			default:break;
		}
	}
	else{
		setLoudspeakerDisable();//�ر���Ƶ
		RRES(SPCOIL_BEEM_BUSY);//�رշ�����
		NVRAM0[SPREG_BEEM_COUNTER]  = 0;
	}
}
void sPlcAimLoop(void){//AIM��ѯ����
	if(LDP(SPCOIL_AIM_ENABEL) && (NVRAM0[DM_AIM_BRG] > 0)){
		setAimBrightness(NVRAM0[DM_AIM_BRG]);
		SSET(SPCOIL_AIM_BUSY);
	}
	if(LDN(SPCOIL_AIM_ENABEL)){
		setAimBrightness(0);
		RRES(SPCOIL_AIM_BUSY);
	}
}
void sPlcAutoFanLoop(void){//��������ѯ����
	if(NVRAM0[SPREG_LAS_FAN_SPEED] > 0 && NVRAM0[SPREG_LAS_FAN_SPEED] < CONFIG_SPLC_FAN_MIN_PWM){
		NVRAM0[SPREG_LAS_FAN_SPEED] = CONFIG_SPLC_FAN_MIN_PWM;
	}

	if(NVRAM0[SPREG_LAS_FAN_SPEED] <= 0){//�����ٶ�С��0
		HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_RESET);
	}
	else{
		HAL_GPIO_WritePin(LAS_FAN_GPIO_Port, LAS_FAN_Pin, GPIO_PIN_SET);
	}
/*
	uint8_t lasFanPwm;
	if(NVRAM0[SPREG_LAS_FAN_SPEED] <= 0){
		NVRAM0[SPREG_LAS_FAN_SPEED] = 0;
	}
	if(NVRAM0[SPREG_LAS_FAN_SPEED] >= 100){
		NVRAM0[SPREG_LAS_FAN_SPEED] = 100;
	}
	if(NVRAM0[SPREG_LAS_FAN_SPEED] > 0){
		lasFanPwm = NVRAM0[SPREG_LAS_FAN_SPEED] * 255 / 100;
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, lasFanPwm);
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);//��TIM
	}
	else{
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_4);//�ر�TIM
	}
#if CONFIG_DEBUG_FAN == 1
	printf("%s,%d,%s:set laser fan pwm,:%d\n",__FILE__, __LINE__, __func__, lasFanPwm);
#endif	
*/
}

/*****************************************************************************/
void sPlcInit(void){//���߼���ʼ��
	printf("%s,%d,%s:start App......\n",__FILE__, __LINE__, __func__);
	listEpromTable();
	readStm32UniqueID();
#if CONFIG_SPLC_USING_EPROM_TEST == 1
	sPlcEpromTest();
#endif
	printf("%s,%d,%s:start load Config......\n",__FILE__, __LINE__, __func__);
	loadDeviceConfig();
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

#if CONFIG_SPLC_USING_FAN_PWM == 1
	printf("%s,%d,%s:start fan timer pwm init......\n",__FILE__, __LINE__, __func__);
	setFanFreq(CONFIG_SPLC_FAN_PWM_FREQ);
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
#endif
	updateNvram();//����NVRAM
	RRES(SPCOIL_START_UP);
	sPlcExitTime = HAL_GetTick();
	sPlcScanTime = sPlcExitTime - sPlcEnterTime;
	NVRAM0[SPREG_SCAN_TIME] = (uint16_t)sPlcScanTime;
}




