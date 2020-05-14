#include "sPlcLaser.h"
/*****************************************************************************/
sbit LASER_CH0_MODPIN = P2^7;
sbit LASER_CH1_MODPIN = P2^6;
volatile int8_t data LaserTimer_Mode;
volatile int8_t data LaserTimer_Select;
volatile int16_t data LaserTimer_TCounter;
volatile int16_t data LaserTimer_TMate;
volatile int16_t data LaserTimer_TOvertime;
volatile int16_t data LaserTimer_PCounter;
volatile int16_t data LaserTimer_PMate;
volatile int16_t data LaserTimer_POvertime;
volatile int16_t data LaserTimer_ReleaseTime;
volatile int16_t data LaserTimer_ReleaseCounter;
volatile int16_t data LaserTimer_BeemSwitchCounter;
volatile int16_t data LaserTimer_BeemSwtichLength;
volatile int8_t data  LaserFlag_Emiting;//���ⷢ���б�־
volatile int8_t data  LaserFlag_Emitover;//���ⷢ����ϱ�־
volatile int32_t data LaserRelease_TotalTime;//���ⷢ����ʱ��
volatile int32_t data LaserRelease_TotalEnergy;//���ⷢ��������
/*****************************************************************************/
static void initTimer4(void);
static void laserStop(void);
static void laserStart(void);
/*****************************************************************************/
#if CONFIG_SPLC_USING_LASER_TIMER_TEST == 1
void testBenchLaserTimer(uint8_t st){//LASER���ⷢ�����
	EDLAR();
	if(st == 0){//CH0 CWģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_CW;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		STLAR();
	}
	if(st == 1){//CH1 CWģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_CW;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		STLAR();
	}
	if(st == 2){//CH0+CH1 CWģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_CW;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		STLAR();
	}
	if(st == 3){//CH0 SPģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 50;//�������������� 10mS
		STLAR();
	}
	if(st == 4){//CH1 SPģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		NVRAM0[SPREG_LASER_TMATE] = 25;//�������������� 10mS
		STLAR();
	}
	if(st == 5){//CH0+CH1 SPģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		NVRAM0[SPREG_LASER_TMATE] = 30;//�������������� 10mS
		STLAR();
	}
	if(st == 6){//CH0 MPģʽ����
		LaserTimer_Mode = LASER_MODE_MP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 30;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 90;//������������ 25mS
		STLAR();
	}
	if(st == 7){//CH1 MPģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_MP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		NVRAM0[SPREG_LASER_TMATE] = 74;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 96;//������������ 25mS
		STLAR();
	}
	if(st == 8){//CH0+CH1 MPģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_MP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		NVRAM0[SPREG_LASER_TMATE] = 53;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 130;//������������ 25mS
		STLAR();
	}
	if(st == 9){//CH0 GPģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_GP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 10;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 15;//������������ 25mS
		NVRAM0[SPREG_LASER_PMATE] = 10;//10������
		NVRAM0[SPREG_LASER_POVERTIME] = 33;//���33mS
		STLAR();
	}
	if(st == 10){//CH1 GPģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_GP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		NVRAM0[SPREG_LASER_TMATE] = 19;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 86;//������������ 25mS
		NVRAM0[SPREG_LASER_PMATE] = 12;//10������
		NVRAM0[SPREG_LASER_POVERTIME] = 43;//���33mS
		STLAR();
	}
	if(st == 11){//CH0+CH1 GPģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_GP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		NVRAM0[SPREG_LASER_TMATE] = 5;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 24;//������������ 25mS
		NVRAM0[SPREG_LASER_PMATE] = 6;//10������
		NVRAM0[SPREG_LASER_POVERTIME] = 60;//���33mS
		STLAR();
	}	
	if(st == 12){//CH0 DERMAģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_DERMA;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 10;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 15;//������������ 25mS
		STLAR();
	}
	if(st == 13){//CH1 DERMAģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_DERMA;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		NVRAM0[SPREG_LASER_TMATE] = 19;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 86;//������������ 25mS
		STLAR();
	}
	if(st == 14){//CH0+CH1 DERMAģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_DERMA;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		NVRAM0[SPREG_LASER_TMATE] = 5;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 24;//������������ 25mS
		STLAR();
	}	
	if(st == 15){//CH0 SIGNALģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SIGNAL;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 10;//�������������� 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 15;//������������ 25mS
		STLAR();
	}
	if(st == 16){//CH1 SIGNALģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SIGNAL;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		STLAR();
	}
	if(st == 17){//CH0+CH1 SIGNALģʽ����
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SIGNAL;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		STLAR();
	}
}

#endif
void STLAR(void){//��ʼ��������
#if CONFIG_SPLC_USING_LASER_TIMER == 1	
	uint8_t SFRPAGE_save;		
	if(LD(MR_BEEM_TONE) || (LaserTimer_Mode == LASER_MODE_SIGNAL)){
		BeemMode = BEEM_MODE_1;	
	}
	else{
		BeemMode = BEEM_MODE_2;
	}
	BeemFreq = BEEM_FREQ_0;
	BeemDuty = getBeemDuty(NVRAM0[DM_BEEM_VOLUME]);
	BeemCounter = 0;
	//BeemEnable = true;
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserTimer_ReleaseCounter = 0x0;
	LaserTimer_BeemSwitchCounter = 0x0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = false;	
	SFRPAGE_save = SFRPAGE;
	SFRPAGE = TMR3_PAGE;
	TMR3CN &= ~(uint8_t)(1 << 7);//TF3 �����־����
	EIE2 |= (1 << 0);//T3 ET3�ж�ʹ��
	EIP2 |= 1 << 2;//T3 �����ȼ�
	TMR3L = 0xFF;
	TMR3H = 0xFF;
	TMR3CN |= (1 << 2);//TR3 ʹ��TIMER3��ʱ��
	SFRPAGE = SFRPAGE_save;
#endif
}
void EDLAR(void) reentrant {//ֹͣ��������
#if CONFIG_SPLC_USING_LASER_TIMER == 1 	
	uint8_t SFRPAGE_save;
	SFRPAGE = TMR3_PAGE;	
	TMR3CN &= ~(uint8_t)(1 << 2);//Stop Timer 3
	EIE2 &= ~(uint8_t)(1 << 0);//�ر�Timer3�ж�
	EIP2 &= 0xFB;//T3 �����ȼ�
	TMR3CN &= ~(uint8_t)(1 << 7);//Clear Timer 3 High Byte Overflow Flag.
	SFRPAGE = SFRPAGE_save;
	laserStop();//�ر�DAC���
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = true;
#endif
}
void sPlcLaserInit(void){//�������幦�ܳ�ʼ��
#if CONFIG_SPLC_USING_LASER_TIMER ==1
	uint16_t temp;
	uint8_t SFRPAGE_SAVE;
	LASER_CH0_MODPIN = 0;
	LASER_CH1_MODPIN = 0;
	SFRPAGE = TMR3_PAGE;
	temp = (uint16_t)(65536 - (CONFIG_SYSCLK / 12 / CONFIG_LASER_TIMER_TICK));
	TMR3CF = 0;//	
	RCAP3 = temp;// Reload value to be used in Timer3
	TMR3 = RCAP3;// Init the Timer3 register
	TMR3CN = 0;//16Bit AutoReload
	RES(SPCOIL_LASER_DRIVER_INIT_FAIL);
	SFRPAGE = SFRPAGE_SAVE; 
	//EIP2 |= 1 << 2;
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
	LaserRelease_TotalTime = 0;
	LaserRelease_TotalEnergy = 0;
#endif
}
static void laserStart(void){//��ͨ��ѡ��򿪼���
	setLedEmit(true);
	LASER_CH0_MODPIN = true; 
	LASER_CH1_MODPIN = true;
	LaserFlag_Emiting = true;	
}
static void laserStop(void){//��ͨ��ѡ��رռ���
	LASER_CH0_MODPIN = false;
	LASER_CH1_MODPIN = false;//��ת���	
	LaserFlag_Emiting = false;	
}
void laserTimerIsr(void) interrupt INTERRUPT_TIMER3{//TIMER3 �ж� ���ⷢ��	
	uint8_t data SFRPAGE_save = SFRPAGE;
	TMR3CN &= 0x7F;//Clear Timer 4 High Byte Overflow Flag
	switch(LaserTimer_Mode){
		case LASER_MODE_CW:{//CW����ģʽ
			if(LaserTimer_TCounter == 0){
				laserStart();
				LaserTimer_TCounter ++;
			}
			if(LaserTimer_ReleaseTime < CONFIG_RELEASE_SECOND_DEF){
				LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
			}
			else{
				LaserTimer_ReleaseTime = 0;
				if(LaserRelease_TotalTime < 99999){
					LaserRelease_TotalTime ++;
				}
			}
			break;
		}
		case LASER_MODE_SIGNAL:{
			if(LaserTimer_TCounter == 0){
				laserStart();
				LaserTimer_TCounter ++;
				LaserTimer_BeemSwitchCounter = 0;
				LaserTimer_BeemSwtichLength = 0;
			}
			else{
				LaserTimer_BeemSwitchCounter += 1;
				if(LaserTimer_ReleaseTime < CONFIG_RELEASE_SECOND_DEF){
					LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
				}
				else{
					LaserTimer_ReleaseTime = 0;
					if(LaserRelease_TotalTime < 99999){
						LaserRelease_TotalTime ++;
					}
				}
				if((((int32_t)LaserTimer_BeemSwitchCounter * NVRAM0[EM_TOTAL_POWER]) / 10000) >= NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL]){
					SFRPAGE = TIMER01_PAGE;
					if(TH0 != BEEM_FREQ_1){
						TH0 = BEEM_FREQ_1;
						TL0 = TH0;
					}
					SFRPAGE = SFRPAGE_save;
					LaserTimer_BeemSwtichLength ++;
				}
				if(LaserTimer_BeemSwtichLength >= CONFIG_BEEM_ENERGY_INTERVAL_TIME){
					SFRPAGE = TIMER01_PAGE;
					if(TH0 != BEEM_FREQ_0){
						TH0 = BEEM_FREQ_0;
						TL0 = TH0;
					}
					SFRPAGE = SFRPAGE_save;
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
				if(LaserTimer_ReleaseTime < CONFIG_RELEASE_SECOND_DEF){
					LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
				}
				else{
					LaserTimer_ReleaseTime = 0;
					if(LaserRelease_TotalTime < 99999){
						LaserRelease_TotalTime ++;
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
					if(LaserTimer_ReleaseTime < CONFIG_RELEASE_SECOND_DEF){
						LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
					}
					else{
						LaserTimer_ReleaseTime = 0;
						if(LaserRelease_TotalTime < 99999){
							LaserRelease_TotalTime ++;
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
				TMR3CN &= ~(uint8_t)(1 << 2);//Stop Timer 4
				EIE2 &= ~(uint8_t)(1 << 0);//�ر�Timer4�ж�
				TMR3CN &= ~(uint8_t)(1 << 7);//Clear Timer 4 High Byte Overflow Flag.
				EIP2 &= 0xFB;//T3 �����ȼ�
				LaserFlag_Emitover = true;
			}
			if(LaserTimer_ReleaseTime < CONFIG_RELEASE_SECOND_DEF){
				LaserTimer_ReleaseTime ++;//����ʱ���ۼ�
			}
			else{
				LaserTimer_ReleaseTime = 0;
				if(LaserRelease_TotalTime < 99999){
					LaserRelease_TotalTime ++;
				}
			}
			LaserTimer_TCounter ++;
			break;
		}
		default:break;
	}
}