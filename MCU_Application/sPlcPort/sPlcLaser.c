//TIM11->��ʱ
#include "sPlc.h"
/*****************************************************************************/
int8_t LaserTimer_Mode;
int16_t LaserTimer_TCounter;
int16_t LaserTimer_TMate;
int16_t LaserTimer_TOvertime;
int16_t LaserTimer_PCounter;
int16_t LaserTimer_PMate;
int16_t LaserTimer_POvertime;
int16_t LaserTimer_ReleaseTime;
int16_t LaserTimer_ReleaseCounter;
int8_t LaserFlag_Emiting;//���ⷢ���б�־
int8_t LaserFlag_Request;//���ⷢ���̤����
int8_t LaserFlag_Emitover;//���ⷢ����ϱ�־
/*****************************************************************************/
static void laserStop(void);
static void laserStart(void);
/*****************************************************************************/
#if CONFIG_SPLC_USING_LASER_TEST == 1
void sPlcLaserTimerTestBench(uint8_t st){//LASER���ⷢ�����
	EDLAR();
	if(st == 0){//CH0 CWģʽ����
		STLAR();
	}
	if(st == 1){//CH1 CWģʽ����
		STLAR();
	}
	if(st == 2){//CH0+CH1 CWģʽ����
		LaserTimer_Mode = LASER_MODE_CW;
		STLAR();
	}
	if(st == 3){//CH0 SPģʽ����
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_TMate = 5000;//�������������� 10mS
		STLAR();
	}
	if(st == 4){//CH1 SPģʽ����
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_TMate = 25;//�������������� 10mS
		STLAR();
	}
	if(st == 5){//CH0+CH1 SPģʽ����
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_TMate = 30;//�������������� 10mS
		STLAR();
	}
	if(st == 6){//CH0 MPģʽ����
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_TMate = 30;//�������������� 10mS
		LaserTimer_TOvertime = 90;//������������ 25mS
		STLAR();
	}
	if(st == 7){//CH1 MPģʽ����
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_TMate = 74;//�������������� 10mS
		LaserTimer_TOvertime = 96;//������������ 25mS
		STLAR();
	}
	if(st == 8){//CH0+CH1 MPģʽ����
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_TMate = 53;//�������������� 10mS
		LaserTimer_TOvertime = 130;//������������ 25mS
		STLAR();
	}
	if(st == 9){//CH0 GPģʽ����
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_TMate = 10;//�������������� 10mS
		LaserTimer_TOvertime = 15;//������������ 25mS
		LaserTimer_PMate = 10;//10������
		LaserTimer_POvertime = 33;//���33mS
		STLAR();
	}
	if(st == 10){//CH1 GPģʽ����
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_TMate = 19;//�������������� 10mS
		LaserTimer_TOvertime = 86;//������������ 25mS
		LaserTimer_PMate = 12;//10������
		LaserTimer_POvertime = 43;//���33mS
		STLAR();
	}
	if(st == 11){//CH0+CH1 GPģʽ����
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_TMate = 5;//�������������� 10mS
		LaserTimer_TOvertime = 24;//������������ 25mS
		LaserTimer_PMate = 6;//10������
		LaserTimer_POvertime = 60;//���33mS
		STLAR();
	}	
	if(st == 12){//CH0 DERMAģʽ����
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_TMate = 10;//�������������� 10mS
		LaserTimer_TOvertime = 15;//������������ 25mS
		STLAR();
	}
	if(st == 13){//CH1 DERMAģʽ����
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_TMate = 19;//�������������� 10mS
		LaserTimer_TOvertime = 86;//������������ 25mS
		STLAR();
	}
	if(st == 14){//CH0+CH1 DERMAģʽ����
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_TMate = 5;//�������������� 10mS
		LaserTimer_TOvertime = 24;//������������ 25mS
		STLAR();
	}	
	if(st == 15){//CH0 SIGNALģʽ����
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		LaserTimer_TMate = 10;//�������������� 10mS
		LaserTimer_TOvertime = 15;//������������ 25mS
		STLAR();
	}
	if(st == 16){//CH1 SIGNALģʽ����
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		STLAR();
	}
	if(st == 17){//CH0+CH1 SIGNALģʽ����
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		STLAR();
	}
}

#endif
void STLAR(void){//��ʼ��������
	int16_t tmp;
	printf("%s,%d,%s:laser start!\n",__FILE__, __LINE__, __func__);
	if(LD(R_ACOUSTIC_ENABLE) && ((NVRAM0[DM_SCHEME_NUM] < 3) || (NVRAM0[DM_SCHEME_NUM] > 5))){
		NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_4;//BEEP + ��ʾ��
	}
	else if((NVRAM0[DM_SCHEME_NUM] >= 3) && (NVRAM0[DM_SCHEME_NUM] <= 5)){
		NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_5;//
	}
	else{
		NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_2;//���ⷢ��̶����
	}
	NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_SPK_FREQ;
	NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
	NVRAM0[SPREG_BEEM_COUNTER]= 0;
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserTimer_ReleaseCounter = 0x0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = false;
	__HAL_TIM_SET_COUNTER(&htim10, 0x0);//�������ֵ
	HAL_TIM_Base_Start_IT(&htim10);//�򿪼�ʱ��
	if(NVRAM0[EM_LASER_POWER_635] != 0){//�켤�⹦�ʲ�Ϊ��
		tmp = NVRAM0[EM_LASER_POWER_635] * 1000;
		setRedLaserPwm(tmp);
	}
}
void EDLAR(void){//ֹͣ��������
	printf("%s,%d,%s:laser stop!\n",__FILE__, __LINE__, __func__);
	__HAL_TIM_SET_COUNTER(&htim10, 0x0);//�������ֵ
	HAL_TIM_Base_Stop_IT(&htim10);//ֹͣ��ʱ��
	laserStop();//�ر�DAC���
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = true;
}
void sPlcLaserInit(void){//�������幦�ܳ�ʼ��
	SET_LASER_1470_OFF;
	SET_LASER_980_OFF;
	//�趨��ʱ��
	LaserTimer_Mode = 0;
	LaserTimer_TCounter = 0;
	LaserTimer_TMate = 0;
	LaserTimer_TOvertime = 0;
	LaserTimer_PCounter = 0;
	LaserTimer_PMate = 0;
	LaserTimer_POvertime = 0;
	LaserTimer_ReleaseTime = 0;
	LaserTimer_ReleaseCounter = 0;
	LaserFlag_Emiting = false;//���ⷢ���б�־
	LaserFlag_Emitover = false;
	printf("%s,%d,%s:laser timer init......\n",__FILE__, __LINE__, __func__);
}
static void laserStart(void){//��ͨ��ѡ��򿪼���
	if(LaserFlag_Emiting == false){
		SET_LASER_1470_ON;
#if CONFIG_USING_LASER_980 == 1
		SET_LASER_980_ON;
#endif
		LaserFlag_Emiting = true;
	}
}
static void laserStop(void){//��ͨ��ѡ��رռ���
	if(LaserFlag_Emiting == true){
		SET_LASER_1470_OFF;
#if CONFIG_USING_LASER_980 == 1		
		SET_LASER_980_OFF;
#endif
		LaserFlag_Emiting = false;
	}
}
void sPlcLaserTimerIsr(void){//TIM �жϻص� ���ⷢ��	
	switch(LaserTimer_Mode){
		case LASER_MODE_CW:{//CW����ģʽ
			if(LaserTimer_TCounter == 0){
					laserStart();
					LaserTimer_TCounter ++;
			}
			break;
		}
		case LASER_MODE_MP:{//MP������ģʽ	
			if((LaserTimer_TCounter >= 0) && (LaserTimer_TCounter < LaserTimer_TMate)){//���ⷢ��
				laserStart();
			}
			if((LaserTimer_TCounter >= LaserTimer_TMate) && (LaserTimer_TCounter < LaserTimer_TOvertime)){//��ʱ��ƥ��
				laserStop();
			}
			if(LaserTimer_TCounter >= LaserTimer_TOvertime){//��ʱ�����
				LaserTimer_TCounter = -1;//����
			}	
			LaserTimer_TCounter ++;
			break;
		}
		default:break;
	}
}
	
void setRedLaserPwm(int16_t pwm){//���ú켤��ռ�ձ�
	if(pwm >= 5000){
		pwm = 5000;
	}
	if(pwm < 0){
		pwm = 0;
	}
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
	if(pwm != 0){
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//��TIM
	}
	else{
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);//�ر�TIM
	}
	printf("%s,%d,%s:set red laser(635) pwm:%d\n",__FILE__, __LINE__, __func__, pwm);

}

void setAimLaserPwm(int16_t pwm){//����ָʾ����ռ�ձ�
	if(pwm >= 50){
		pwm = 50;
	}
	if(pwm < 0){
		pwm = 0;
	}
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
	if(pwm != 0){
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//��TIM
	}
	else{
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);//�ر�TIM
	}
	printf("%s,%d,%s:set red laser(635) pwm:%d\n",__FILE__, __LINE__, __func__, pwm);

}