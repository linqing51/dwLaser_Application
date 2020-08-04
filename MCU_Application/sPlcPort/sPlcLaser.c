//TIM11->��ʱ
#include "sPlcLaser.h"
/*****************************************************************************/
extern TIM_HandleTypeDef htim10;
/*****************************************************************************/
volatile int8_t LaserTimer_Mode;
volatile int8_t LaserTimer_Select;
volatile int16_t LaserTimer_TCounter;
volatile int16_t LaserTimer_TMate;
volatile int16_t LaserTimer_TOvertime;
volatile int16_t LaserTimer_PCounter;
volatile int16_t LaserTimer_PMate;
volatile int16_t LaserTimer_POvertime;
volatile int16_t LaserTimer_ReleaseTime;
volatile int16_t LaserTimer_ReleaseCounter;
volatile int16_t LaserTimer_BeemSwitchCounter;
volatile int16_t LaserTimer_BeemSwtichLength;
volatile int8_t LaserFlag_Emiting;//���ⷢ���б�־
volatile int8_t LaserFlag_Request;//���ⷢ���̤����
volatile int8_t LaserFlag_Emitover;//���ⷢ����ϱ�־
volatile int32_t LaserRelease_TotalTime0;//���ⷢ����ʱ��
volatile int32_t LaserRelease_TotalEnergy0;//���ⷢ��������
int32_t LaserRelease_TotalTime1;//���ⷢ����ʱ��
int32_t LaserRelease_TotalEnergy1;//���ⷢ��������
/*****************************************************************************/
static void laserStop(void);
static void laserStart(void);
/*****************************************************************************/
#if CONFIG_SPLC_USING_LASER_TEST == 1
void testBenchLaserTimer(uint8_t st){//LASER���ⷢ�����
	EDLAR();
	if(st == 0){//CH0 CWģʽ����
		LaserTimer_Mode = LASER_MODE_CW;
		LaserTimer_Select = LASER_SELECT_CH0;
		STLAR();
	}
	if(st == 1){//CH1 CWģʽ����
		LaserTimer_Mode = LASER_MODE_CW;
		LaserTimer_Select = LASER_SELECT_CH1;
		STLAR();
	}
	if(st == 2){//CH0+CH1 CWģʽ����
		LaserTimer_Mode = LASER_MODE_CW;
		LaserTimer_Select = LASER_SELECT_ALL;
		STLAR();
	}
	if(st == 3){//CH0 SPģʽ����
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_Select = LASER_SELECT_CH0;
		LaserTimer_TMate = 5000;//�������������� 10mS
		STLAR();
	}
	if(st == 4){//CH1 SPģʽ����
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_Select = LASER_SELECT_CH1;
		LaserTimer_TMate = 25;//�������������� 10mS
		STLAR();
	}
	if(st == 5){//CH0+CH1 SPģʽ����
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_Select = LASER_SELECT_ALL;
		LaserTimer_TMate = 30;//�������������� 10mS
		STLAR();
	}
	if(st == 6){//CH0 MPģʽ����
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_Select = LASER_SELECT_CH0;
		LaserTimer_TMate = 30;//�������������� 10mS
		LaserTimer_TOvertime = 90;//������������ 25mS
		STLAR();
	}
	if(st == 7){//CH1 MPģʽ����
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_Select = LASER_SELECT_CH1;
		LaserTimer_TMate = 74;//�������������� 10mS
		LaserTimer_TOvertime = 96;//������������ 25mS
		STLAR();
	}
	if(st == 8){//CH0+CH1 MPģʽ����
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_Select = LASER_SELECT_ALL;
		LaserTimer_TMate = 53;//�������������� 10mS
		LaserTimer_TOvertime = 130;//������������ 25mS
		STLAR();
	}
	if(st == 9){//CH0 GPģʽ����
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_Select = LASER_SELECT_CH0;
		LaserTimer_TMate = 10;//�������������� 10mS
		LaserTimer_TOvertime = 15;//������������ 25mS
		LaserTimer_PMate = 10;//10������
		LaserTimer_POvertime = 33;//���33mS
		STLAR();
	}
	if(st == 10){//CH1 GPģʽ����
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_Select = LASER_SELECT_CH1;
		LaserTimer_TMate = 19;//�������������� 10mS
		LaserTimer_TOvertime = 86;//������������ 25mS
		LaserTimer_PMate = 12;//10������
		LaserTimer_POvertime = 43;//���33mS
		STLAR();
	}
	if(st == 11){//CH0+CH1 GPģʽ����
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_Select = LASER_SELECT_ALL;
		LaserTimer_TMate = 5;//�������������� 10mS
		LaserTimer_TOvertime = 24;//������������ 25mS
		LaserTimer_PMate = 6;//10������
		LaserTimer_POvertime = 60;//���33mS
		STLAR();
	}	
	if(st == 12){//CH0 DERMAģʽ����
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_Select = LASER_SELECT_CH0;
		LaserTimer_TMate = 10;//�������������� 10mS
		LaserTimer_TOvertime = 15;//������������ 25mS
		STLAR();
	}
	if(st == 13){//CH1 DERMAģʽ����
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_Select = LASER_SELECT_CH1;
		LaserTimer_TMate = 19;//�������������� 10mS
		LaserTimer_TOvertime = 86;//������������ 25mS
		STLAR();
	}
	if(st == 14){//CH0+CH1 DERMAģʽ����
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_Select = LASER_SELECT_ALL;
		LaserTimer_TMate = 5;//�������������� 10mS
		LaserTimer_TOvertime = 24;//������������ 25mS
		STLAR();
	}	
	if(st == 15){//CH0 SIGNALģʽ����
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		LaserTimer_Select = LASER_SELECT_CH0;
		LaserTimer_TMate = 10;//�������������� 10mS
		LaserTimer_TOvertime = 15;//������������ 25mS
		STLAR();
	}
	if(st == 16){//CH1 SIGNALģʽ����
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		LaserTimer_Select = LASER_SELECT_CH1;
		STLAR();
	}
	if(st == 17){//CH0+CH1 SIGNALģʽ����
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		LaserTimer_Select = LASER_SELECT_ALL;
		STLAR();
	}
}

#endif
void STLAR(void){//��ʼ��������
#if CONFIG_DEBUG_LASER == 1
	printf("sPlc->sPlcLaser:Laser start!\n");
#endif	
#if CONFIG_SPLC_USING_MUSIC == 1	
	SetMusicVolume(NVRAM0[SPREG_MUSIC_VOLUME]);//��GDDC��������������
#endif
	if(LD(MR_BEEM_TONE) || (LaserTimer_Mode == LASER_MODE_SIGNAL)){
		//�ж��Ƿ������� ��������������������С��100mS��ѡ��MODE2
		switch(NVRAM0[EM_LASER_PULSE_MODE]){
			case LASER_MODE_CW:{
				NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_1;//����ͬ��
				break;
			}
			case LASER_MODE_SP:{
				if(NVRAM0[EM_LASER_SP_POSWIDTH] > 30){//���������100mS
					NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_1;//����ͬ��
				}
				else{
					NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_2;//�̶����
				}
				break;
			}
			case LASER_MODE_MP:{
				if((NVRAM0[EM_LASER_MP_POSWIDTH] > 30) || (NVRAM0[EM_LASER_MP_NEGWIDTH] > 30)){//���������30mS
					NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_1;//����ͬ��
				}
				else{
					NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_2;//�̶����
				}
				break;
			}
			case LASER_MODE_GP:{
				if((NVRAM0[EM_LASER_GP_POSWIDTH] > 30) || (NVRAM0[EM_LASER_GP_NEGWIDTH] > 30)){//���������30mS
					NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_1;//����ͬ��
				}
				else{
					NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_2;//�̶����
				}
				break;
			}
			case LASER_MODE_DERMA:{
				if((NVRAM0[EM_LASER_DERMA_POSWIDTH] > 30) || (NVRAM0[EM_LASER_DERMA_NEGWIDTH] > 30)){//���������30mS
					NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_1;//����ͬ��
				}
				else{
					NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_2;//�̶����
				}
				break;
			}
			case LASER_MODE_SIGNAL:{
				NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_1;//����ͬ��
				break;
			}
			default:{
				NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_1;//����ͬ��
				break;
			}
		}
	}
	else{
		NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_2;//�̶����
	}
	NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_BEEM_FREQ;
	NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
	NVRAM0[SPREG_BEEM_COUNTER]= 0;
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserTimer_ReleaseCounter = 0x0;
	LaserTimer_BeemSwitchCounter = 0x0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = false;
	__HAL_TIM_SET_COUNTER(&htim10, 0x0);//�������ֵ
	HAL_TIM_Base_Start_IT(&htim10);//�򿪼�ʱ��
}
void EDLAR(void){//ֹͣ��������
#if CONFIG_DEBUG_LASER == 1
	printf("sPlc->sPlcLaser:Laser stop!\n");
#endif
	NVRAM0[SPREG_CONTROL_MUSIC] = CMD_MUSIC_STOP;//�ر�MP3
	__HAL_TIM_SET_COUNTER(&htim10, 0x0);//�������ֵ
	HAL_TIM_Base_Stop_IT(&htim10);//ֹͣ��ʱ��
	laserStop();//�ر�DAC���
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = true;
}
void sPlcLaserInit(void){//�������幦�ܳ�ʼ��
#if CONFIG_DEBUG_LASER == 1
	printf("sPlc->sPlcLaser:Laser init!\n");
#endif	
	SET_LASER_CH0(GPIO_PIN_RESET);
	SET_LASER_CH1(GPIO_PIN_RESET);
	SET_LASER_CH2(GPIO_PIN_RESET);
	SET_LASER_CH3(GPIO_PIN_RESET);
	SET_LASER_CH4(GPIO_PIN_RESET);
	//�趨��ʱ��
	RRES(SPCOIL_LASER_DRIVER_INIT_FAIL);
	LaserTimer_Mode = 0;
	LaserTimer_Select = 0;
	LaserTimer_TCounter = 0;
	LaserTimer_TMate = 0;
	LaserTimer_TOvertime = 0;
	LaserTimer_PCounter = 0;
	LaserTimer_PMate = 0;
	LaserTimer_POvertime = 0;
	LaserTimer_ReleaseTime = 0;
	LaserTimer_ReleaseCounter = 0;
	LaserTimer_BeemSwitchCounter = 0;
	LaserTimer_BeemSwtichLength = 0;
	LaserFlag_Emiting = false;//���ⷢ���б�־
	LaserFlag_Emitover = false;
	LaserRelease_TotalTime0 = 0;
	LaserRelease_TotalEnergy0 = 0;
	LaserRelease_TotalTime1 = -1;
	LaserRelease_TotalEnergy1 = -1;
}
static void laserStart(void){//��ͨ��ѡ��򿪼���
#if CONFIG_USING_SINGLE_WAVE == 1//������
	SET_LASER_CH0(GPIO_PIN_SET);
	SET_LASER_CH1(GPIO_PIN_RESET);
	SET_LASER_CH2(GPIO_PIN_RESET);
	SET_LASER_CH3(GPIO_PIN_RESET);
	SET_LASER_CH4(GPIO_PIN_RESET);
#endif
#if CONFIG_USING_DUAL_WAVE == 1//˫����
	SET_LASER_CH0(GPIO_PIN_SET);
	SET_LASER_CH1(GPIO_PIN_SET);
	SET_LASER_CH2(GPIO_PIN_RESET);
	SET_LASER_CH3(GPIO_PIN_RESET);
	SET_LASER_CH4(GPIO_PIN_RESET);
#endif
#if CONFIG_USING_TRIPE_WAVE == 1//������
	SET_LASER_CH0(GPIO_PIN_SET);
	SET_LASER_CH1(GPIO_PIN_SET);
	SET_LASER_CH2(GPIO_PIN_SET);
	SET_LASER_CH3(GPIO_PIN_RESET);
	SET_LASER_CH4(GPIO_PIN_RESET);
#endif
#if CONFIG_USING_QUAD_WAVE == 1//�Ĳ���
	SET_LASER_CH0(GPIO_PIN_SET);
	SET_LASER_CH1(GPIO_PIN_SET);
	SET_LASER_CH2(GPIO_PIN_SET);
	SET_LASER_CH3(GPIO_PIN_SET);
	SET_LASER_CH4(GPIO_PIN_RESET);
#endif
#if CONFIG_USING_FIVE_WAVE == 1//�岨��
	SET_LASER_CH0(GPIO_PIN_SET);
	SET_LASER_CH1(GPIO_PIN_SET);
	SET_LASER_CH2(GPIO_PIN_SET);
	SET_LASER_CH3(GPIO_PIN_SET);
	SET_LASER_CH4(GPIO_PIN_SET);
#endif
	LaserFlag_Emiting = true;
	if(LD(MR_BEEM_TONE) || LaserTimer_Mode == LASER_MODE_SIGNAL){//����ͬ��
		//����MP3 ID 0
		NVRAM0[SPREG_PLAYING_MUSIC_ID] = 0;
		NVRAM0[SPREG_NEXT_MUSIC_ID] = CMD_MUSIC_PLAY;
	}
	else{//���
		//����MP3 ID 1
		NVRAM0[SPREG_PLAYING_MUSIC_ID] = 1;
		NVRAM0[SPREG_NEXT_MUSIC_ID] = CMD_MUSIC_PLAY;
	}
}
static void laserStop(void){//��ͨ��ѡ��رռ���
	SET_LASER_CH0(GPIO_PIN_RESET);
	SET_LASER_CH1(GPIO_PIN_RESET);
	SET_LASER_CH2(GPIO_PIN_RESET);
	SET_LASER_CH3(GPIO_PIN_RESET);
	SET_LASER_CH4(GPIO_PIN_RESET);	
	LaserFlag_Emiting = false;
}
void laserTimerIsr(void){//TIM �жϻص� ���ⷢ��	
	switch(LaserTimer_Mode){
		case LASER_MODE_CW:{//CW����ģʽ
			if(LaserTimer_TCounter == 0){
				laserStart();
				LaserTimer_TCounter ++;				
			}
			if(LaserTimer_ReleaseTime < 1000){
				LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
			}
			else{
				LaserTimer_ReleaseTime = 0;
				if(LaserRelease_TotalTime0 < 99999){
					LaserRelease_TotalTime0 ++;
				}
			}
			break;
		}
		case LASER_MODE_SIGNAL:{//����ģʽ ��Ƶ�ı�
			if(LaserTimer_TCounter == 0){
				laserStart();
				LaserTimer_TCounter ++;
				LaserTimer_BeemSwitchCounter = 0;
				LaserTimer_BeemSwtichLength = 0;
			}
			else{
				LaserTimer_BeemSwitchCounter += 1;
				if(LaserTimer_ReleaseTime < 1000){
					LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
				}
				else{
					LaserTimer_ReleaseTime = 0;
					if(LaserRelease_TotalTime0 < 99999){
						LaserRelease_TotalTime0 ++;
					}
				}
				if((((fp32_t)LaserTimer_BeemSwitchCounter * (fp32_t)NVRAM0[EM_TOTAL_POWER]) / 10000.0F) >= (fp32_t)NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL]){
					NVRAM0[SPREG_NEXT_MUSIC_ID] = 1;//��ʼ����MP3 ID 1
					NVRAM0[SPREG_CONTROL_MUSIC] = CMD_MUSIC_PLAY;
					if(NVRAM0[SPREG_BEEM_FREQ] != CONFIG_SPLC_DEFORM_BEEM_FREQ){
						NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFORM_BEEM_FREQ;
#if CONFIG_SPLC_USING_BEEM == 1
						setBeemFreq(NVRAM0[SPREG_BEEM_FREQ]);
#endif
						__NOP();
					}
					LaserTimer_BeemSwtichLength ++;			
				}
				if(LaserTimer_BeemSwtichLength >= CONFIG_BEEM_ENERGY_INTERVAL_TIME){
					//ֹͣ����
					NVRAM0[SPREG_NEXT_MUSIC_ID] = 0;//��ʼ����MP3 ID0
					NVRAM0[SPREG_CONTROL_MUSIC] = CMD_MUSIC_PLAY;					
					if(NVRAM0[SPREG_BEEM_FREQ] != CONFIG_SPLC_DEFAULT_BEEM_FREQ){
						NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_BEEM_FREQ;
#if CONFIG_SPLC_USING_BEEM == 1						
						setBeemFreq(NVRAM0[SPREG_BEEM_FREQ]);
#endif
						__NOP();
					}			
					LaserTimer_BeemSwitchCounter = 0;
					LaserTimer_BeemSwtichLength = 0;
				}
			}
			break;
		}
		case LASER_MODE_DERMA:{//��MPģʽ��ͬ
		}
		case LASER_MODE_MP:{//MP������ģʽ	
			if(LaserTimer_TCounter == 0){//��ת
				laserStart();
			}
			if(LaserTimer_TCounter >= LaserTimer_TMate){//��ʱ��ƥ��
				laserStop();
			}
			if(LaserTimer_TCounter < LaserTimer_TMate){//���ⷢ����
				if(LaserTimer_ReleaseTime < 1000){
					LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
				}
				else{
					LaserTimer_ReleaseTime = 0;
					if(LaserRelease_TotalTime0 < 99999){
						LaserRelease_TotalTime0 ++;
					}
				}
			}
			if(LaserTimer_TCounter >= LaserTimer_TOvertime){//��ʱ�����
				LaserTimer_TCounter = -1;//����
			}
			LaserTimer_TCounter ++;
			break;
		}
		case LASER_MODE_GP:{//GP�ɱ������ģʽ
			if(LaserTimer_PCounter < LaserTimer_PMate){//���崮���
				if(LaserTimer_TCounter == 0){//��ת	
					laserStart();
				}
				if(LaserTimer_TCounter < LaserTimer_PMate){//���ⷢ����
					if(LaserTimer_ReleaseTime < 1000){
						LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
					}
					else{
						LaserTimer_ReleaseTime = 0;
						if(LaserRelease_TotalTime0 < 99999){
							LaserRelease_TotalTime0 ++;
						}
					}
				}
				if(LaserTimer_TCounter == LaserTimer_TMate){//��ʱ��ƥ��
					laserStop();					
				}
				if(LaserTimer_TCounter >= LaserTimer_TOvertime){//��ʱ�����
					LaserTimer_TCounter = -1;//����
					LaserTimer_PCounter ++;
				}
				LaserTimer_TCounter ++;
			}
			if(LaserTimer_PCounter >= LaserTimer_PMate){//��������		
				if(LaserTimer_PCounter >= (LaserTimer_POvertime + LaserTimer_PMate)){//�����������ƥ��
					LaserTimer_PCounter = -1;
					LaserTimer_TCounter = 0;
				}
				LaserTimer_PCounter ++;
			}
			break;
		}
		case LASER_MODE_SP:{//������ģʽ
			if(LaserTimer_TCounter == 0){//��ת
				laserStart();		
			}
			if(LaserTimer_TCounter >= LaserTimer_TMate){//��ʱ��ƥ��
				laserStop();//�ر�DAC���
				HAL_TIM_Base_Stop(&htim10);
				LaserFlag_Emitover = true;
			}
			if(LaserTimer_ReleaseTime < 1000){
				LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
			}
			else{
				LaserTimer_ReleaseTime = 0;
				if(LaserRelease_TotalTime0 < 99999){
					LaserRelease_TotalTime0 ++;
				}
			}
			LaserTimer_TCounter ++;
			break;
		}
		default:break;
	}
}
	

