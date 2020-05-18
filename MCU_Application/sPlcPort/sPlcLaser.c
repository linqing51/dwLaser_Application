//TIM11
#include "sPlcLaser.h"
/*****************************************************************************/
#define LASER_CH0_ON				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);						
#define LASER_CH1_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_SET);
#define LASER_CH2_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
#define LASER_CH3_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_SET);
#define LASER_CH4_ON				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
#define LASER_CH0_OFF				HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);			
#define LASER_CH1_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, GPIO_PIN_RESET);
#define LASER_CH2_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
#define LASER_CH3_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, GPIO_PIN_RESET);
#define LASER_CH4_OFF				HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
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
volatile int8_t LaserFlag_Emiting;//激光发射中标志
volatile int8_t LaserFlag_Emitover;//激光发射完毕标志
volatile int32_t LaserRelease_TotalTime;//激光发射总时间
volatile int32_t LaserRelease_TotalEnergy;//激光发射总能量
/*****************************************************************************/
static void laserStop(void);
static void laserStart(void);
/*****************************************************************************/
#if CONFIG_SPLC_USING_LASER_TIMER_TEST == 1
void testBenchLaserTimer(uint8_t st){//LASER激光发射测试
	EDLAR();
	if(st == 0){//CH0 CW模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_CW;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		STLAR();
	}
	if(st == 1){//CH1 CW模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_CW;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		STLAR();
	}
	if(st == 2){//CH0+CH1 CW模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_CW;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		STLAR();
	}
	if(st == 3){//CH0 SP模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 50;//激光脉冲正脉宽 10mS
		STLAR();
	}
	if(st == 4){//CH1 SP模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		NVRAM0[SPREG_LASER_TMATE] = 25;//激光脉冲正脉宽 10mS
		STLAR();
	}
	if(st == 5){//CH0+CH1 SP模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		NVRAM0[SPREG_LASER_TMATE] = 30;//激光脉冲正脉宽 10mS
		STLAR();
	}
	if(st == 6){//CH0 MP模式测试
		LaserTimer_Mode = LASER_MODE_MP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 30;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 90;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 7){//CH1 MP模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_MP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		NVRAM0[SPREG_LASER_TMATE] = 74;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 96;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 8){//CH0+CH1 MP模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_MP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		NVRAM0[SPREG_LASER_TMATE] = 53;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 130;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 9){//CH0 GP模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_GP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 10;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 15;//激光脉冲周期 25mS
		NVRAM0[SPREG_LASER_PMATE] = 10;//10个脉冲
		NVRAM0[SPREG_LASER_POVERTIME] = 33;//间隔33mS
		STLAR();
	}
	if(st == 10){//CH1 GP模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_GP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		NVRAM0[SPREG_LASER_TMATE] = 19;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 86;//激光脉冲周期 25mS
		NVRAM0[SPREG_LASER_PMATE] = 12;//10个脉冲
		NVRAM0[SPREG_LASER_POVERTIME] = 43;//间隔33mS
		STLAR();
	}
	if(st == 11){//CH0+CH1 GP模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_GP;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		NVRAM0[SPREG_LASER_TMATE] = 5;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 24;//激光脉冲周期 25mS
		NVRAM0[SPREG_LASER_PMATE] = 6;//10个脉冲
		NVRAM0[SPREG_LASER_POVERTIME] = 60;//间隔33mS
		STLAR();
	}	
	if(st == 12){//CH0 DERMA模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_DERMA;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 10;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 15;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 13){//CH1 DERMA模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_DERMA;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		NVRAM0[SPREG_LASER_TMATE] = 19;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 86;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 14){//CH0+CH1 DERMA模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_DERMA;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		NVRAM0[SPREG_LASER_TMATE] = 5;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 24;//激光脉冲周期 25mS
		STLAR();
	}	
	if(st == 15){//CH0 SIGNAL模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SIGNAL;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH0;
		NVRAM0[SPREG_LASER_TMATE] = 10;//激光脉冲正脉宽 10mS
		NVRAM0[SPREG_LASER_TOVERTIME] = 15;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 16){//CH1 SIGNAL模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SIGNAL;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_CH1;
		STLAR();
	}
	if(st == 17){//CH0+CH1 SIGNAL模式测试
		NVRAM0[SPREG_LASER_MODE] = LASER_MODE_SIGNAL;
		NVRAM0[SPREG_LASER_SELECT] = LASER_SELECT_ALL;
		STLAR();
	}
}

#endif
void STLAR(void){//开始发射脉冲
#if CONFIG_SPLC_USING_LASER_TIMER == 1			
//	if(LD(MR_BEEM_TONE) || (LaserTimer_Mode == LASER_MODE_SIGNAL)){
//		BeemMode = BEEM_MODE_1;	
//	}
//	else{
//		BeemMode = BEEM_MODE_2;
//	}
//	BeemFreq = BEEM_FREQ_0;
//	BeemDuty = getBeemDuty(NVRAM0[DM_BEEM_VOLUME]);
//	BeemCounter = 0;
	//BeemEnable = true;
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserTimer_ReleaseCounter = 0x0;
	LaserTimer_BeemSwitchCounter = 0x0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = false;	
#endif
}
void EDLAR(void){//停止发射脉冲
	laserStop();//关闭DAC输出
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = true;
}
void sPlcLaserInit(void){//激光脉冲功能初始化	
	LASER_CH0_OFF;
	LASER_CH1_OFF;
	LASER_CH2_OFF;
	LASER_CH3_OFF;
	LASER_CH4_OFF;
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
	LaserFlag_Emiting = false;//激光发射中标志
	LaserFlag_Emitover = false;
	LaserRelease_TotalTime = 0;
	LaserRelease_TotalEnergy = 0;
}
static void laserStart(void){//按通道选择打开激光
	//setLedEmit(true);//打开激光发射指示
	LASER_CH0_ON; 
	LASER_CH1_ON;
	LaserFlag_Emiting = true;	
}
static void laserStop(void){//按通道选择关闭激光
	LASER_CH0_OFF;
	LASER_CH1_OFF;//翻转输出	
	LaserFlag_Emiting = false;	
}
void laserTimerCallback(void){//TIM 中断回调 激光发射	
	switch(LaserTimer_Mode){
		case LASER_MODE_CW:{//CW连续模式
			if(LaserTimer_TCounter == 0){
				laserStart();
				LaserTimer_TCounter ++;
			}
			if(LaserTimer_ReleaseTime < CONFIG_RELEASE_SECOND_DEF){
				LaserTimer_ReleaseTime ++;//发射时间累计
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
					LaserTimer_ReleaseTime ++;//发射时间累计
				}
				else{
					LaserTimer_ReleaseTime = 0;
					if(LaserRelease_TotalTime < 99999){
						LaserRelease_TotalTime ++;
					}
				}
				if((((int32_t)LaserTimer_BeemSwitchCounter * NVRAM0[EM_TOTAL_POWER]) / 10000) >= NVRAM0[EM_LASER_SIGNAL_ENERGY_INTERVAL]){
					//if(TH0 != BEEM_FREQ_1){
//						TH0 = BEEM_FREQ_1;
//						TL0 = TH0;
					//LaserTimer_BeemSwtichLength ++;
				}
				if(LaserTimer_BeemSwtichLength >= CONFIG_BEEM_ENERGY_INTERVAL_TIME){
//					if(TH0 != BEEM_FREQ_0){
//						TH0 = BEEM_FREQ_0;
//						TL0 = TH0;
	//				}
					LaserTimer_BeemSwitchCounter = 0;
					LaserTimer_BeemSwtichLength = 0;
				}
			}
			break;
		}
		case LASER_MODE_DERMA:{//与MP模式相同
		}
		case LASER_MODE_MP:{//MP多脉冲模式	
			if(LaserTimer_TCounter == 0){//翻转
				laserStart();
			}
			if(LaserTimer_TCounter >= LaserTimer_TMate){//计时器匹配
				laserStop();
			}
			if(LaserTimer_TCounter < LaserTimer_TMate){//激光发射中
				if(LaserTimer_ReleaseTime < CONFIG_RELEASE_SECOND_DEF){
					LaserTimer_ReleaseTime ++;//发射时间累计
				}
				else{
					LaserTimer_ReleaseTime = 0;
					if(LaserRelease_TotalTime < 99999){
						LaserRelease_TotalTime ++;
					}
				}
			}
			if(LaserTimer_TCounter >= LaserTimer_TOvertime){//计时器溢出
				LaserTimer_TCounter = -1;//清零
			}
			LaserTimer_TCounter ++;
			break;
		}
		case LASER_MODE_GP:{//GP可编程脉冲模式
			if(LaserTimer_PCounter < LaserTimer_PMate){//脉冲串输出
				if(LaserTimer_TCounter == 0){//翻转	
					laserStart();
				}
				if(LaserTimer_TCounter < LaserTimer_PMate){//激光发射中
					if(LaserTimer_ReleaseTime < CONFIG_RELEASE_SECOND_DEF){
						LaserTimer_ReleaseTime ++;//发射时间累计
					}
					else{
						LaserTimer_ReleaseTime = 0;
						if(LaserRelease_TotalTime < 99999){
							LaserRelease_TotalTime ++;
						}
					}
				}
				if(LaserTimer_TCounter == LaserTimer_TMate){//计时器匹配
					laserStop();					
				}
				if(LaserTimer_TCounter >= LaserTimer_TOvertime){//计时器溢出
					LaserTimer_TCounter = -1;//清零
					LaserTimer_PCounter ++;
				}
				LaserTimer_TCounter ++;
			}
			if(LaserTimer_PCounter >= LaserTimer_PMate){//多脉冲间隔		
				if(LaserTimer_PCounter >= (LaserTimer_POvertime + LaserTimer_PMate)){//脉冲个数发现匹配
					LaserTimer_PCounter = -1;
					LaserTimer_TCounter = 0;
				}
				LaserTimer_PCounter ++;
			}
			break;
		}
		case LASER_MODE_SP:{//单脉冲模式
			if(LaserTimer_TCounter == 0){//翻转
				laserStart();		
			}
			if(LaserTimer_TCounter >= LaserTimer_TMate){//计时器匹配
				laserStop();//关闭DAC输出
				//TMR3CN &= ~(uint8_t)(1 << 2);//Stop Timer 4
				//EIE2 &= ~(uint8_t)(1 << 0);//关闭Timer4中断
				//TMR3CN &= ~(uint8_t)(1 << 7);//Clear Timer 4 High Byte Overflow Flag.
				//EIP2 &= 0xFB;//T3 低优先级
				LaserFlag_Emitover = true;
			}
			if(LaserTimer_ReleaseTime < CONFIG_RELEASE_SECOND_DEF){
				LaserTimer_ReleaseTime ++;//发射时间累计
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
	

