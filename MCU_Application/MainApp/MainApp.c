#include "MainApp.h"
#include "pid_fuzzy.h"
/*****************************************************************************/
fuzzyPid_t laserPid;
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
	pd1 = (3300.0F * CONFIG_VREF_CAL * (NVRAM0[SPREG_ADC_2] - NVRAM0[SPREG_ADC_2])) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹ
	pd2 = (3300.0F * CONFIG_VREF_CAL * (NVRAM0[SPREG_ADC_3] - NVRAM0[SPREG_ADC_3])) / (NVRAM0[SPREG_ADC_9] * 4096.0F);//�����ѹ
	NVRAM0[EM_LASER_PD_CH0] = (int16_t)pd1;
	NVRAM0[EM_LASER_PD_CH1] = (int16_t)pd2;
	NVRAM0[TMP_REG_0] = 0;
	NVRAM0[TMP_REG_1] = 9999;
	LIMS16(EM_LASER_PD_CH0, TMP_REG_0, TMP_REG_1);
	LIMS16(EM_LASER_PD_CH1, TMP_REG_0, TMP_REG_1);
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

void mainAppTask(void *argument){
	int pidTmp;
	sPlcInit();
	fuzzyPidInit(&laserPid);
	while(1){
		sPlcProcessStart();
		if(LD(SPCOIL_START_UP)){//
			SSET(Y_ERR_LED);
			SSET(Y_TEC_ENA);
			NVRAM0[EM_LASER_TEMP_SET] = 250;//Ĭ�ϼ�������ȴ�¶�25.0��
			NVRAM0[SPREG_DAC_2] = 0xFFFF;
			NVRAM0[SPREG_DAC_3] = 0xFFFF;
			UPDAC2();
			UPDAC3();
			NVRAM0[EM_LASER_POWER_CH0] = 500;
			NVRAM0[EM_LASER_POWER_CH1] = 700;
			NVRAM0[EM_LASER_POSWIDTH] = 50;
		}
		//�Ĵ�����Χ����		
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_POWER_CH0, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_POWER_CH1, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_PWM_CH0, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_PWM_CH1, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 0;NVRAM0[TMP_REG_1] = 999;LIMS16(EM_LASER_POSWIDTH, TMP_REG_0, TMP_REG_1);
		NVRAM0[TMP_REG_0] = 200;NVRAM0[TMP_REG_1] = 350;LIMS16(EM_LASER_TEMP_SET, TMP_REG_0, TMP_REG_1);
		//
		if(LDP(R_LASER_START) && LD(X_INTERLOCK_NC)){//�򿪼���ͨ��1
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
			RRES(R_LASER_START);
		}
		else{
			RRES(R_LASER_START);
		}
		if(LDP(R_LASER_STOP) || LDB(X_INTERLOCK_NC)){//�رռ���ͨ��1
			NVRAM0[SPREG_DAC_0] = 0;
			NVRAM0[SPREG_DAC_1] = 0;
			UPDAC0();//����ͨ��1 DAC
			UPDAC1();//����ͨ��2 DAC
			EDLAR();
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
		temperatureMeasureLoop();
		currentMeasureLoop();
		powerMeasureLoop();
		returnToZero();
		
		sPlcProcessEnd();
	}
}



