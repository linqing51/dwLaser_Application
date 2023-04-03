//TIM11->计时
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
int8_t LaserFlag_Emiting;//激光发射中标志
int8_t LaserFlag_Request;//激光发射脚踏请求
int8_t LaserFlag_Emitover;//激光发射完毕标志
/*****************************************************************************/
static void laserStop(void);
static void laserStart(void);
/*****************************************************************************/
#if CONFIG_SPLC_USING_LASER_TEST == 1
void sPlcLaserTimerTestBench(uint8_t st){//LASER激光发射测试
	EDLAR();
	if(st == 0){//CH0 CW模式测试
		STLAR();
	}
	if(st == 1){//CH1 CW模式测试
		STLAR();
	}
	if(st == 2){//CH0+CH1 CW模式测试
		LaserTimer_Mode = LASER_MODE_CW;
		STLAR();
	}
	if(st == 3){//CH0 SP模式测试
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_TMate = 5000;//激光脉冲正脉宽 10mS
		STLAR();
	}
	if(st == 4){//CH1 SP模式测试
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_TMate = 25;//激光脉冲正脉宽 10mS
		STLAR();
	}
	if(st == 5){//CH0+CH1 SP模式测试
		LaserTimer_Mode = LASER_MODE_SP;
		LaserTimer_TMate = 30;//激光脉冲正脉宽 10mS
		STLAR();
	}
	if(st == 6){//CH0 MP模式测试
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_TMate = 30;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 90;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 7){//CH1 MP模式测试
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_TMate = 74;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 96;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 8){//CH0+CH1 MP模式测试
		LaserTimer_Mode = LASER_MODE_MP;
		LaserTimer_TMate = 53;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 130;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 9){//CH0 GP模式测试
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_TMate = 10;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 15;//激光脉冲周期 25mS
		LaserTimer_PMate = 10;//10个脉冲
		LaserTimer_POvertime = 33;//间隔33mS
		STLAR();
	}
	if(st == 10){//CH1 GP模式测试
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_TMate = 19;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 86;//激光脉冲周期 25mS
		LaserTimer_PMate = 12;//10个脉冲
		LaserTimer_POvertime = 43;//间隔33mS
		STLAR();
	}
	if(st == 11){//CH0+CH1 GP模式测试
		LaserTimer_Mode = LASER_MODE_GP;
		LaserTimer_TMate = 5;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 24;//激光脉冲周期 25mS
		LaserTimer_PMate = 6;//10个脉冲
		LaserTimer_POvertime = 60;//间隔33mS
		STLAR();
	}	
	if(st == 12){//CH0 DERMA模式测试
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_TMate = 10;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 15;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 13){//CH1 DERMA模式测试
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_TMate = 19;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 86;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 14){//CH0+CH1 DERMA模式测试
		LaserTimer_Mode = LASER_MODE_DERMA;
		LaserTimer_TMate = 5;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 24;//激光脉冲周期 25mS
		STLAR();
	}	
	if(st == 15){//CH0 SIGNAL模式测试
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		LaserTimer_TMate = 10;//激光脉冲正脉宽 10mS
		LaserTimer_TOvertime = 15;//激光脉冲周期 25mS
		STLAR();
	}
	if(st == 16){//CH1 SIGNAL模式测试
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		STLAR();
	}
	if(st == 17){//CH0+CH1 SIGNAL模式测试
		LaserTimer_Mode = LASER_MODE_SIGNAL;
		STLAR();
	}
}

#endif
void STLAR(void){//开始发射脉冲
	int16_t tmp;
	printf("%s,%d,%s:laser start!\n",__FILE__, __LINE__, __func__);
	if(LD(R_ACOUSTIC_ENABLE) && ((NVRAM0[DM_SCHEME_NUM] < 3) || (NVRAM0[DM_SCHEME_NUM] > 5))){
		NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_4;//BEEP + 提示音
	}
	else if((NVRAM0[DM_SCHEME_NUM] >= 3) && (NVRAM0[DM_SCHEME_NUM] <= 5)){
		NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_5;//
	}
	else{
		NVRAM0[SPREG_BEEM_MODE] = BEEM_MODE_2;//激光发射固定间隔
	}
	NVRAM0[SPREG_BEEM_FREQ] = CONFIG_SPLC_DEFAULT_SPK_FREQ;
	NVRAM0[SPREG_BEEM_VOLUME] = NVRAM0[DM_BEEM_VOLUME];
	NVRAM0[SPREG_BEEM_COUNTER]= 0;
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserTimer_ReleaseCounter = 0x0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = false;
	__HAL_TIM_SET_COUNTER(&htim10, 0x0);//清零计数值
	HAL_TIM_Base_Start_IT(&htim10);//打开计时器
	if(NVRAM0[EM_LASER_POWER_635] != 0){//红激光功率不为零
		tmp = NVRAM0[EM_LASER_POWER_635] * 1000;
		setRedLaserPwm(tmp);
	}
}
void EDLAR(void){//停止发射脉冲
	printf("%s,%d,%s:laser stop!\n",__FILE__, __LINE__, __func__);
	__HAL_TIM_SET_COUNTER(&htim10, 0x0);//清零计数值
	HAL_TIM_Base_Stop_IT(&htim10);//停止计时器
	laserStop();//关闭DAC输出
	LaserTimer_TCounter = 0X0;
	LaserTimer_PCounter = 0X0;
	LaserFlag_Emiting = false;
	LaserFlag_Emitover = true;
}
void sPlcLaserInit(void){//激光脉冲功能初始化
	SET_LASER_1470_OFF;
	SET_LASER_980_OFF;
	//设定计时器
	LaserTimer_Mode = 0;
	LaserTimer_TCounter = 0;
	LaserTimer_TMate = 0;
	LaserTimer_TOvertime = 0;
	LaserTimer_PCounter = 0;
	LaserTimer_PMate = 0;
	LaserTimer_POvertime = 0;
	LaserTimer_ReleaseTime = 0;
	LaserTimer_ReleaseCounter = 0;
	LaserFlag_Emiting = false;//激光发射中标志
	LaserFlag_Emitover = false;
	printf("%s,%d,%s:laser timer init......\n",__FILE__, __LINE__, __func__);
}
static void laserStart(void){//按通道选择打开激光
	if(LaserFlag_Emiting == false){
		SET_LASER_1470_ON;
#if CONFIG_USING_LASER_980 == 1
		SET_LASER_980_ON;
#endif
		LaserFlag_Emiting = true;
	}
}
static void laserStop(void){//按通道选择关闭激光
	if(LaserFlag_Emiting == true){
		SET_LASER_1470_OFF;
#if CONFIG_USING_LASER_980 == 1		
		SET_LASER_980_OFF;
#endif
		LaserFlag_Emiting = false;
	}
}
void sPlcLaserTimerIsr(void){//TIM 中断回调 激光发射	
	switch(LaserTimer_Mode){
		case LASER_MODE_CW:{//CW连续模式
			if(LaserTimer_TCounter == 0){
					laserStart();
					LaserTimer_TCounter ++;
			}
			break;
		}
		case LASER_MODE_MP:{//MP多脉冲模式	
			if((LaserTimer_TCounter >= 0) && (LaserTimer_TCounter < LaserTimer_TMate)){//激光发射
				laserStart();
			}
			if((LaserTimer_TCounter >= LaserTimer_TMate) && (LaserTimer_TCounter < LaserTimer_TOvertime)){//计时器匹配
				laserStop();
			}
			if(LaserTimer_TCounter >= LaserTimer_TOvertime){//计时器溢出
				LaserTimer_TCounter = -1;//清零
			}	
			LaserTimer_TCounter ++;
			break;
		}
		default:break;
	}
}
	
void setRedLaserPwm(int16_t pwm){//设置红激光占空比
	if(pwm >= 5000){
		pwm = 5000;
	}
	if(pwm < 0){
		pwm = 0;
	}
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
	if(pwm != 0){
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//打开TIM
	}
	else{
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);//关闭TIM
	}
	printf("%s,%d,%s:set red laser(635) pwm:%d\n",__FILE__, __LINE__, __func__, pwm);

}

void setAimLaserPwm(int16_t pwm){//设置指示激光占空比
	if(pwm >= 50){
		pwm = 50;
	}
	if(pwm < 0){
		pwm = 0;
	}
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, pwm);
	if(pwm != 0){
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);//打开TIM
	}
	else{
		HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);//关闭TIM
	}
	printf("%s,%d,%s:set red laser(635) pwm:%d\n",__FILE__, __LINE__, __func__, pwm);

}