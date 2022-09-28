#include "MainApp.h"
#include "pid_fuzzy.h"
/*****************************************************************************/
fuzzyPid_t laserPid;
extern IWDG_HandleTypeDef hiwdg;
/*****************************************************************************/
void temperatureMeasureLoop(void){//�¶Ȳɼ�
	double ftmp;
	TNTC(EM_LASER_TEMP, SPREG_ADC_1);//CODEת��ΪNTC�����¶��¶�
	TENV(EM_MCU_TEMP, SPREG_ADC_8);//CODEת��ΪMCU�¶�
	if(LDP(SPCOIL_PS100MS)){
		ftmp = fuzzyPidRealize(&laserPid, ((double)NVRAM0[EM_LASER_TEMP_SET] / 250.0F), ((double)NVRAM0[EM_LASER_TEMP] / 250.0F));
		NVRAM0[SPREG_DAC_2] = (uint16_t)ftmp;
		NVRAM0[SPREG_DAC_3] = (uint16_t)ftmp;
		UPDAC2();UPDAC3();
		NVRAM0[EM_COOL_RATE] = (int16_t)(ftmp / 65535 * 100);
	}
	//�ж϶�����0�Ƿ����
	if(NVRAM0[EM_LASER_TEMP] >= CONFIG_DIODE_HIGH_TEMP){//����������
		SSET(R_LASER_TEMP_HIGH);
	}
	if(NVRAM0[EM_LASER_TEMP] <= (CONFIG_DIODE_HIGH_TEMP - 50)){//�������ָ������¶�
		RRES(R_LASER_TEMP_HIGH);
	}
	//�жϻ����Ƿ����
	if(NVRAM0[EM_MCU_TEMP] > CONFIG_ENVI_HIGH_TEMP){//�����¶ȹ���
		SSET(R_MCU_TEMP_HIGH);
	}
	else{
		RRES(R_MCU_TEMP_HIGH);
	}
}
void currentMeasureLoop(void){//�����ɼ�
	float fA0, fA1, fB0, fB1, fC0;
	fA0 = (3300.0F * CONFIG_VREF_CAL * (float)(NVRAM0[SPREG_ADC_0] - NVRAM0[DM_ADC_OFFSET_0])) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹ
	fA1 = (3300.0F * CONFIG_VREF_CAL * (float)(NVRAM0[SPREG_ADC_7] - NVRAM0[DM_ADC_OFFSET_7])) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹ
	fB0 = (3300.0F * CONFIG_VREF_CAL * (float)(NVRAM0[SPREG_ADC_6] - NVRAM0[DM_ADC_OFFSET_6])) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹ
	fB1 = (3300.0F * CONFIG_VREF_CAL * (float)(NVRAM0[SPREG_ADC_5] - NVRAM0[DM_ADC_OFFSET_5])) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹ
	fC0 = (3300.0F * CONFIG_VREF_CAL * (float)(NVRAM0[SPREG_ADC_4] - NVRAM0[DM_ADC_OFFSET_4])) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹ
	fA0 = fA0 / CONFIG_ISAB_RS / 20.0F;
	fA1 = fA1 / CONFIG_ISAB_RS / 20.0F;
	fB0 = fB0 / CONFIG_ISAB_RS / 20.0F;
	fB1 = fB1 / CONFIG_ISAB_RS / 20.0F;
	fC0 = fC0 / CONFIG_ISC_RS / 20.0F;
	NVRAM0[EM_LASER_CURRENT_CH0] = (int16_t)fA0;
	NVRAM0[EM_LASER_CURRENT_CH1] = (int16_t)fA1;
	NVRAM0[EM_LASER_CURRENT_CH2] = (int16_t)fB0;
	NVRAM0[EM_LASER_CURRENT_CH3] = (int16_t)fB1;
	NVRAM0[EM_LASER_CURRENT_CH4] = (int16_t)fC0;
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = 9999;
	LIMS16(EM_LASER_CURRENT_CH0, TMP_REG_0, TMP_REG_1);
	LIMS16(EM_LASER_CURRENT_CH1, TMP_REG_0, TMP_REG_1);
	LIMS16(EM_LASER_CURRENT_CH2, TMP_REG_0, TMP_REG_1);
	LIMS16(EM_LASER_CURRENT_CH3, TMP_REG_0, TMP_REG_1);
	LIMS16(EM_LASER_CURRENT_CH4, TMP_REG_0, TMP_REG_1);
}
void powerMeasureLoop(void){//���ʲɼ�
	float pd1, pd2;
	pd1 = (3300.0F * CONFIG_VREF_CAL * (float)(NVRAM0[SPREG_ADC_2] - NVRAM0[DM_ADC_OFFSET_2])) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹ
	pd2 = (3300.0F * CONFIG_VREF_CAL * (float)(NVRAM0[SPREG_ADC_3] - NVRAM0[DM_ADC_OFFSET_3])) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹ
	if(pd1 > 9999){
		pd1 = 9999;
	}
	if(pd1 < 0){
		pd1 = 0;
	}
	if(pd2 > 9999){
		pd2 = 9999;
	}
	if(pd2 < 0){
		pd2 = 0;
	}
	NVRAM0[EM_LASER_PD_CH0] = (int16_t)pd1;
	NVRAM0[EM_LASER_PD_CH1] = (int16_t)pd2;
}
void returnToZero(void){//����ֵ����
	if(LD(R_RETURN_ZERO)){	
		NVRAM0[DM_ADC_OFFSET_0] = NVRAM0[SPREG_ADC_0];
		NVRAM0[DM_ADC_OFFSET_1] = NVRAM0[SPREG_ADC_1];								
		NVRAM0[DM_ADC_OFFSET_2] = NVRAM0[SPREG_ADC_2];						
		NVRAM0[DM_ADC_OFFSET_3] = NVRAM0[SPREG_ADC_3];						
		NVRAM0[DM_ADC_OFFSET_4] = NVRAM0[SPREG_ADC_4];					
		NVRAM0[DM_ADC_OFFSET_5] = NVRAM0[SPREG_ADC_5];					
		NVRAM0[DM_ADC_OFFSET_6] = NVRAM0[SPREG_ADC_6];
		NVRAM0[DM_ADC_OFFSET_7] = NVRAM0[SPREG_ADC_7];
		NVRAM0[DM_ADC_OFFSET_8] = NVRAM0[SPREG_ADC_8];
		NVRAM0[DM_ADC_OFFSET_9] = NVRAM0[SPREG_ADC_9];
		RRES(R_RETURN_ZERO);
	}
}

void watchDogTask(void *argument){//���Ź�����
	while(1){
#if CONFIG_USING_IWDG == 1
		HAL_IWDG_Refresh(&hiwdg); //ι������װ���Ź�����Ϊ4095.
#endif
		vTaskDelay(500);
	}
}

void mainAppTask(void *argument){
	int pidTmp;
	sPlcInit();
	fuzzyPidInit(&laserPid);
	SET_LINK_LED(GPIO_PIN_SET);
	SET_ALARM_LED(GPIO_PIN_SET);
	SET_LASER1_LED(GPIO_PIN_SET);
	SET_LASER2_LED(GPIO_PIN_SET);
	vTaskDelay(1000);
	SET_LINK_LED(GPIO_PIN_RESET);
	SET_ALARM_LED(GPIO_PIN_RESET);
	SET_LASER1_LED(GPIO_PIN_RESET);
	SET_LASER2_LED(GPIO_PIN_RESET);
	while(1){
		sPlcProcessStart();
		if(LD(SPCOIL_START_UP)){//
			RRES(Y_LINK_LED);
			RRES(Y_ALARM_LED);
			RRES(Y_LASER1_LED);
			RRES(Y_LASER2_LED);
			RRES(Y_AIM1_ENA);
			RRES(Y_AIM2_ENA);
			SSET(Y_ERR_LED);
			SSET(Y_TEC_ENA);
			NVRAM0[EM_LASER_TEMP_SET] = CONFIG_DIODE_SET_TEMP;			
		}	
		//�Ĵ�����Χ����		
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_POWER_CH0, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_POWER_CH1, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_PWM_CH0, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_PWM_CH1, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_POSWIDTH, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 200;NVRAM0[TMP_REG_1] = 350;LIMS16(EM_LASER_TEMP_SET, TMP_REG_0, TMP_REG_1);
		//��ز���
		if(LD(X_EXT_ENABLE) && LD(X_LASER_TRIG)){//��ش���
			SSET(R_LASER_START);
		}
		if(LD(X_EXT_ENABLE) && LDB(X_LASER_TRIG)){
			RRES(R_LASER_START);
			SSET(R_LASER_STOP);
		}
		if(LDN(X_EXT_ENABLE)){//�л��ڿ�ģʽֹͣ���伤��
			RRES(R_LASER_START);
			SSET(R_LASER_STOP);
		}
		//
		if(LDP(R_LASER_START) && LD(X_INTERLOCK_NC)){//�򿪼���
			NVRAM0[SPREG_DAC_0] = NVRAM0[EM_LASER_POWER_CH0] * 65535 / 1000;
			NVRAM0[SPREG_DAC_1] = NVRAM0[EM_LASER_POWER_CH1] * 65535 / 1000;
			//�жϼ��ⷢ��ģʽCW����SP
			if(NVRAM0[EM_LASER_POSWIDTH] == 0){//CWģʽ
				LaserTimer_Mode = LASER_MODE_CW;
			}
			else{//SPģʽ
				LaserTimer_Mode = LASER_MODE_SP;
				LaserTimer_TMate = NVRAM0[EM_LASER_POSWIDTH] * 10;
			}
			UPDAC0();//����ͨ��1 DAC
			UPDAC1();//����ͨ��2 DAC
			STLAR();
			SSET(R_LASER_BEEM);
			RRES(R_LASER_START);
		}
		else{
			RRES(R_LASER_START);
		}
		if(LDP(R_LASER_STOP) || LDN(X_INTERLOCK_NC)){//�رռ���
			NVRAM0[SPREG_DAC_0] = 0;
			NVRAM0[SPREG_DAC_1] = 0;
			UPDAC0();//����ͨ��1 DAC
			UPDAC1();//����ͨ��2 DAC
			EDLAR();
			RRES(R_LASER_BEEM);
			RRES(R_LASER_STOP);
		}
		else{
			RRES(R_LASER_STOP);
		}
		//ָʾ�����
		if(LDP(R_AIM_ENABLE_CH0)){
			SSET(Y_AIM1_ENA);
		}
		if(LDB(R_AIM_ENABLE_CH0)){
			RRES(Y_AIM1_ENA);
		}
		if(LDP(R_AIM_ENABLE_CH1)){
			SSET(Y_AIM2_ENA);
		}
		if(LDB(R_AIM_ENABLE_CH1)){
			RRES(Y_AIM2_ENA);
		}
		//ָʾ��
		if(NVRAM0[EM_LASER_CURRENT_CH0] >= CONFIG_DIODE_THRESHOLD){
			SSET(Y_LASER1_LED);
		}
		if(NVRAM0[EM_LASER_CURRENT_CH0] <= CONFIG_DIODE_THRESHOLD - 100){
			RRES(Y_LASER1_LED);
		}
		if(NVRAM0[EM_LASER_CURRENT_CH1] >= CONFIG_DIODE_THRESHOLD){
			SSET(Y_LASER2_LED);
		}
		if(NVRAM0[EM_LASER_CURRENT_CH1] <= CONFIG_DIODE_THRESHOLD - 100){
			RRES(Y_LASER2_LED);
		}
		if(LD(R_ALRAM)){
			SSET(Y_ALARM_LED);
		}
		else{
			RRES(Y_ALARM_LED);
		}
		
		temperatureMeasureLoop();
		currentMeasureLoop();
		powerMeasureLoop();
		returnToZero();
		sPlcProcessEnd();
	}
}



