#include "dcHmiApp.h"
#include "tempCtrLoop.h"
/*****************************************************************************/
#if (CONFIG_USING_CLASSIC_PID == 1)
PID_Controller_t ClassicPid_A;//恒温控制器
#endif

#if (CONFIG_USING_FUZZY_PID == 1)
FuzzyPID_HandleTypeDef FuzzyPid_A;
#endif

#if (CONFIG_USING_SMART_PID == 1)
SmartPID_Controller SmartPid_A;
#endif

FanController AutoFan0, AutoFan1, AutoFan2, AutoFan3, AutoFan4, AutoFan5, AutoFan6, AutoFan7;// 创建风扇控制器实例
int16_t LaserTecOutCounter0, LaserTecOut0;
/*****************************************************************************/
void tempControlInit(void){
#if (CONFIG_USING_CLASSIC_PID == 1)	
  //Kp: 0.21, Ki: 0.0046, Kd: 0.57 (单位%/℃, 输出0~4095)
  PID_Init(&ClassicPid_A, 0.21f, 0.0046f, 0.57f, deviceConfig.laserDiodeA_Temp, 4095);
#endif

#if CONFIG_USING_FUZZY_PID == 1
	FuzzyPID_Init(&FuzzyPid_A, 
									2.2f, 0.1f, 0.1f,  // 基础 Kp, Ki, Kd
                  0, 4095,            // 输出限幅 0~1000
                  500.0f,             // 积分限幅
                  1000,                // 控制周期 200ms
                  1,                 // 误差范围 ±10℃
                  1);                // 误差变化率范围 ±1℃/s
#endif

#if CONFIG_USING_SMART_PID == 1
 SmartPID_Init(&SmartPid_A, (float_t)deviceConfig.laserDiodeA_Temp / 10.0F);

#endif	
	FanController_Init(&AutoFan0, fan_curve_0, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan1, fan_curve_1, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan2, fan_curve_2, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan3, fan_curve_3, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan4, fan_curve_4, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan5, fan_curve_5, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan6, fan_curve_6, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan7, fan_curve_7, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
		
}

static int16_t tecOutPrev = 0;      //上次TEC输出(slew-rate限幅基准)
static int16_t tecTempFilt = 0;     //反馈温度一阶滤波值(×10单位)
static uint8_t tecTempFiltInit = 0; //反馈温度滤波初始化标志

void tempControlLoop(void){//温度风扇控制循环
	//温控执行 激光等待发射及错误状态启动温控
	if(LDP(SPCOIL_PS500MS)){//1秒间隔
		if(LD(R_TEMP_FAULT)){//温度异常无条件打开风扇
			 	NVRAM0[EM_FAN0_SET_SPEED] = 100;
		}
		else{
			AutoFan0.current_temp = ((float32_t)NVRAM0[EM_HT0_TEMP] / 10.0F);//关联温度
			AutoFan1.current_temp = ((float32_t)NVRAM0[EM_HT1_TEMP] / 10.0F);//关联温度
			AutoFan2.current_temp = ((float32_t)NVRAM0[EM_HT2_TEMP] / 10.0F);//关联温度
			AutoFan3.current_temp = ((float32_t)NVRAM0[EM_HT3_TEMP] / 10.0F);//关联温度
			AutoFan4.current_temp = ((float32_t)NVRAM0[EM_HT1_TEMP] / 10.0F);//关联温度
			AutoFan5.current_temp = ((float32_t)NVRAM0[EM_AMBIENT0_TEMP] / 10.0F);//关联温度->环境进风温度
			AutoFan6.current_temp = ((float32_t)NVRAM0[EM_HWATER_TEMP] / 10.0F);//关联温度->热水温度
			AutoFan7.current_temp = ((float32_t)NVRAM0[EM_HDC1080_TEMP] / 10.0F);//关联温度->板载传感器温度
				
			FanController_Run(&AutoFan0);// 更新风扇控制
			FanController_Run(&AutoFan1);// 更新风扇控制
			FanController_Run(&AutoFan2);// 更新风扇控制
			FanController_Run(&AutoFan3);// 更新风扇控制
			FanController_Run(&AutoFan4);// 更新风扇控制
			FanController_Run(&AutoFan5);// 更新风扇控制
			FanController_Run(&AutoFan6);// 更新风扇控制
			FanController_Run(&AutoFan7);// 更新风扇控制
			
			NVRAM0[EM_FAN0_SET_SPEED] = AutoFan0.current_speed;
			NVRAM0[EM_FAN1_SET_SPEED] = AutoFan1.current_speed;
			NVRAM0[EM_FAN2_SET_SPEED] = AutoFan2.current_speed;
			NVRAM0[EM_FAN3_SET_SPEED] = AutoFan3.current_speed;
			NVRAM0[EM_FAN4_SET_SPEED] = AutoFan4.current_speed;
			NVRAM0[EM_FAN5_SET_SPEED] = AutoFan5.current_speed;
			NVRAM0[EM_FAN6_SET_SPEED] = AutoFan6.current_speed;
			NVRAM0[EM_FAN7_SET_SPEED] = AutoFan7.current_speed;
		}
		setFanSpeed(FAN_CH0, NVRAM0[EM_FAN0_SET_SPEED]);
		setFanSpeed(FAN_CH1, NVRAM0[EM_FAN1_SET_SPEED]);
		setFanSpeed(FAN_CH2, NVRAM0[EM_FAN2_SET_SPEED]);
		setFanSpeed(FAN_CH3, NVRAM0[EM_FAN3_SET_SPEED]);
		setFanSpeed(FAN_CH4, NVRAM0[EM_FAN4_SET_SPEED]);
		setFanSpeed(FAN_CH5, NVRAM0[EM_FAN5_SET_SPEED]);
		setFanSpeed(FAN_CH6, NVRAM0[EM_FAN6_SET_SPEED]);
		setFanSpeed(FAN_CH7, NVRAM0[EM_FAN7_SET_SPEED]);
			
#if CONFIG_USING_CLASSIC_PID == 1
		//反馈温度一阶低通滤波, 抑制NTC噪声经微分项放大
		if(tecTempFiltInit == 0){
			tecTempFilt = NVRAM0[EM_LASER_A_DIODE_TEMP];
			tecTempFiltInit = 1;
		}
		else{
			tecTempFilt += (int16_t)(((int32_t)NVRAM0[EM_LASER_A_DIODE_TEMP] - tecTempFilt) * CONFIG_TEC_TEMP_FILTER_ALPHA);
		}
		ClassicPid_A.setpoint = deviceConfig.laserDiodeA_Temp;	
		LaserTecOut0 = PID_Compute(&ClassicPid_A, tecTempFilt);
		//散热器温度前馈: 散热器温度高于设定时叠加制冷输出(单冷TEC, 仅正前馈)
		{
			int32_t ff = (int32_t)(((int32_t)NVRAM0[EM_HT0_TEMP] - deviceConfig.laserDiodeA_Temp) * CONFIG_TEC_HT_FF_GAIN);
			if(ff > 0){
				LaserTecOut0 += (int16_t)ff;
			}
		}
		if(LaserTecOut0 > 4095){
			LaserTecOut0 = 4095;
		}
#endif

#if CONFIG_USING_FUZZY_PID == 1
		//反馈温度一阶低通滤波, 抑制NTC噪声经微分项放大
		if(tecTempFiltInit == 0){
			tecTempFilt = NVRAM0[EM_LASER_A_DIODE_TEMP];
			tecTempFiltInit = 1;
		}
		else{
			tecTempFilt += (int16_t)(((int32_t)NVRAM0[EM_LASER_A_DIODE_TEMP] - tecTempFilt) * CONFIG_TEC_TEMP_FILTER_ALPHA);
		}
		FuzzyPID_SetSetpoint(&FuzzyPid_A, deviceConfig.laserDiodeA_Temp); // 设定目标温度(×10单位)
		LaserTecOut0 = FuzzyPID_Compute(&FuzzyPid_A, tecTempFilt);
		//散热器温度前馈: 散热器温度高于设定时叠加制冷输出(单冷TEC, 仅正前馈)
		{
			int32_t ff = (int32_t)(((int32_t)NVRAM0[EM_HT0_TEMP] - deviceConfig.laserDiodeA_Temp) * CONFIG_TEC_HT_FF_GAIN);
			if(ff > 0){
				LaserTecOut0 += (int16_t)ff;
			}
		}
		if(LaserTecOut0 > 4095){
			LaserTecOut0 = 4095;
		}
#endif		
		
#if CONFIG_USING_SMART_PID == 1		
		float32_t ftmp0 = 0.0f;
		//反馈温度一阶低通滤波, 抑制NTC噪声经微分先行项放大
		if(tecTempFiltInit == 0){
			tecTempFilt = NVRAM0[EM_LASER_A_DIODE_TEMP];
			tecTempFiltInit = 1;
		}
		else{
			tecTempFilt += (int16_t)(((int32_t)NVRAM0[EM_LASER_A_DIODE_TEMP] - tecTempFilt) * CONFIG_TEC_TEMP_FILTER_ALPHA);
		}
		//辨识未完成期间, ftmp0保持小功率(step_power)输出等待辨识结束; 完成后执行常规PID闭环
		if(!SmartPID_Identify(&SmartPid_A, (float32_t)tecTempFilt / 10.0F, &ftmp0)){
		}
		else{//辨识完成或跳过辨识后，执行常规PID闭环控制(量纲统一℃, 原实现漏除10导致输出恒为0)
			ftmp0 = SmartPID_Compute(&SmartPid_A, (float32_t)tecTempFilt / 10.0F);
		}
		LaserTecOut0 =(int16_t)(ftmp0 * 4095);
		//散热器温度前馈: 散热器温度高于设定时叠加制冷输出(单冷TEC, 仅正前馈)
		{
			int32_t ff = (int32_t)(((int32_t)NVRAM0[EM_HT0_TEMP] - deviceConfig.laserDiodeA_Temp) * CONFIG_TEC_HT_FF_GAIN);
			if(ff > 0){
				LaserTecOut0 += (int16_t)ff;
			}
		}
		if(LaserTecOut0 > 4095){
			LaserTecOut0 = 4095;
		}
#endif
		NVRAM0[EM_TPID0_OUT] = LaserTecOut0;
		NVRAM0[SPREG_DAC_8] = LaserTecOut0;
		NVRAM0[SPREG_DAC_9] = LaserTecOut0;
		if(LaserTecOut0 <= 0 ){
			SET_TEC_CH0_OFF;
			SET_TEC_CH1_OFF;
			SET_TEC_CH2_OFF;
			SET_TEC_CH3_OFF;
			SET_TEC_CH4_OFF;
			SET_TEC_CH5_OFF;
			SET_TEC_CH6_OFF;
			SET_TEC_CH7_OFF;
		}
		else{
			SET_TEC_CH0_ON;
			SET_TEC_CH1_ON;
			SET_TEC_CH2_ON;
			SET_TEC_CH3_ON;
			SET_TEC_CH4_ON;
			SET_TEC_CH5_ON;
			SET_TEC_CH6_ON;
			SET_TEC_CH7_ON;
		}
		//输出变化率限幅(slew-rate): 每500ms最多变化CONFIG_TEC_SLEW_STEP计数, 禁止驱动电压突跳
		{
			int16_t delta = (int16_t)(LaserTecOut0 - tecOutPrev);
			if(delta > CONFIG_TEC_SLEW_STEP){
				LaserTecOut0 = tecOutPrev + CONFIG_TEC_SLEW_STEP;
			}
			else if(delta < -CONFIG_TEC_SLEW_STEP){
				LaserTecOut0 = tecOutPrev - CONFIG_TEC_SLEW_STEP;
			}
			tecOutPrev = LaserTecOut0;
			if(LaserTecOut0 < 0){
				LaserTecOut0 = 0;
			}
		}
		NVRAM0[EM_TPID0_OUT] = LaserTecOut0;
		NVRAM0[SPREG_DAC_8] = LaserTecOut0;
		UPDAC8();//DAC8: TIM9 CH2 PWM占空比 -> GP8101C-SH模拟电压
		//注: 原Y_TEC软件PWM斩波段已移除, TEC由TIM9 CH2连续PWM驱动(模拟电压连续可调)
	}
	(void)LaserTecOutCounter0;//保留变量兼容, 原软件PWM计数器不再使用
}








