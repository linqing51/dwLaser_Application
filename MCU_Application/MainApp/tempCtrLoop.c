#include "dcHmiApp.h"
#include "tempCtrLoop.h"
/*****************************************************************************/
#if (CONFIG_USING_CLASSIC_PID == 1)
PID_Controller_t ClassicPid_A,ClassicPid_B;//恒温控制器
#endif

#if (CONFIG_USING_FUZZY_PID == 1)
FuzzyPID_HandleTypeDef FuzzyPid_A, FuzzyPid_B;
#endif

#if (CONFIG_USING_SMART_PID == 1)
SmartPID_Controller SmartPid_A, SmartPid_B;
#endif

FanController AutoFan0, AutoFan1, AutoFan2;// 创建风扇控制器实例
int16_t LaserTecOutCounter0, LaserTecOut0;
int16_t LaserTecOutCounter1, LaserTecOut1;
/*****************************************************************************/
void tempControlInit(void){
#if (CONFIG_USING_CLASSIC_PID == 1)
	PID_Init(&ClassicPid_A, 5.0f, 0.6f, 2.0f, NVRAM0[EM_LASER_A_DIODE_TEMP], 500);
	PID_Init(&ClassicPid_B, 5.0f, 0.6f, 2.0f, NVRAM0[EM_LASER_B_DIODE_TEMP], 500);
#endif

#if CONFIG_USING_FUZZY_PID == 1
	FuzzyPID_Init(&FuzzyPid_A, 
									2.0f, 0.5f, 10.0f,  // 基础 Kp, Ki, Kd
                  0, 4095,            // 输出限幅 0~1000
                  500.0f,             // 积分限幅
                  200,                // 控制周期 200ms
                  1,                 // 误差范围 ±10℃
                  1);                // 误差变化率范围 ±1℃/s
	FuzzyPID_Init(&FuzzyPid_B, 
									2.0f, 0.5f, 10.0f,  // 基础 Kp, Ki, Kd
                  0, 4095,            // 输出限幅 0~1000
                  500.0f,             // 积分限幅
                  200,                // 控制周期 200ms
                  1,                 // 误差范围 ±50℃
                  1);                // 误差变化率范围 ±1℃/s
#endif

#if CONFIG_USING_SMART_PID == 1
	 SmartPID_Init(&SmartPid_A, (float_t)NVRAM0[EM_LASER_A_DIODE_TEMP] / 10.0F);
	 SmartPID_Init(&SmartPid_B, (float_t)NVRAM0[EM_LASER_B_DIODE_TEMP] / 10.0F);
#endif	
	
	FanController_Init(&AutoFan0, fan_curve_0, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan1, fan_curve_1, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan2, fan_curve_2, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
}

void tempControlLoop(void){//温度风扇控制循环
	float32_t ftmp0, ftmp1;
	ftmp0 = !ftmp0;
	ftmp1 = !ftmp1;
	//温控执行 激光等待发射及错误状态启动温控
	if(LDP(SPCOIL_PS100MS)){//0.2秒间隔
		if(LD(R_TEMP_FAULT)){//温度异常无条件打开风扇
			 	NVRAM0[EM_FAN0_SET_SPEED] = 100;
		}
		else{
			AutoFan0.current_temp = ((float32_t)NVRAM0[EM_HT0_TEMP] / 10.0F);//关联温度
			AutoFan1.current_temp = ((float32_t)NVRAM0[EM_HT1_TEMP] / 10.0F);//关联温度
			AutoFan2.current_temp = ((float32_t)NVRAM0[EM_HT2_TEMP] / 10.0F);//关联温度
			FanController_Run(&AutoFan0);// 更新风扇控制
			FanController_Run(&AutoFan1);// 更新风扇控制
			FanController_Run(&AutoFan2);// 更新风扇控制
			NVRAM0[EM_FAN0_SET_SPEED] = AutoFan0.current_speed;
			NVRAM0[EM_FAN1_SET_SPEED] = AutoFan1.current_speed;
			NVRAM0[EM_FAN2_SET_SPEED] = AutoFan2.current_speed;
		}
		setFanSpeed(NVRAM0[EM_FAN0_SET_SPEED]);
		
#if CONFIG_USING_CLASSIC_PID == 1
		ClassicPid_A.setpoint = deviceConfig.laserDiodeA_Temp;
		ClassicPid_B.setpoint = deviceConfig.laserDiodeB_Temp;
		LaserTecOut0 = PID_Compute(&ClassicPid_A, NVRAM0[EM_LASER_A_DIODE_TEMP]);	
		LaserTecOut1 = PID_Compute(&ClassicPid_B, NVRAM0[EM_LASER_B_DIODE_TEMP]);	
#endif

#if CONFIG_USING_FUZZY_PID == 1
		  FuzzyPID_SetSetpoint(&FuzzyPid_A, deviceConfig.laserDiodeA_Temp); // 设定目标温度为 25℃
		  FuzzyPID_SetSetpoint(&FuzzyPid_B, deviceConfig.laserDiodeA_Temp); // 设定目标温度为 25℃
			LaserTecOut0 = FuzzyPID_Compute(&FuzzyPid_A, NVRAM0[EM_LASER_A_DIODE_TEMP]);
			LaserTecOut1 = FuzzyPID_Compute(&FuzzyPid_B, NVRAM0[EM_LASER_B_DIODE_TEMP]);
#endif		
		
#if CONFIG_USING_SMART_PID == 1		
		//辨识未完成期间，保持小功率输出或零输出，等待辨识结束
		if(!SmartPID_Identify(&SmartPid_A, (float32_t)NVRAM0[EM_LASER_A_DIODE_TEMP] / 10.0F, &ftmp0)){
		}
		else{//辨识完成或跳过辨识后，执行常规PID闭环控制
			ftmp0 = SmartPID_Compute(&SmartPid_A, (float32_t)NVRAM0[EM_LASER_A_DIODE_TEMP]);
		}
		
		if(!SmartPID_Identify(&SmartPid_B, (float32_t)NVRAM0[EM_LASER_B_DIODE_TEMP] / 10.0F, &ftmp1)){
		}
		else{
			ftmp1 = SmartPID_Compute(&SmartPid_A, (float32_t)NVRAM0[EM_LASER_B_DIODE_TEMP]);
		}
		LaserTecOut0 =(int16_t)(ftmp0 * 4095);
		LaserTecOut1 =(int16_t)(ftmp1 * 4095);
#endif
		NVRAM0[EM_TPID0_OUT] = LaserTecOut0;
		NVRAM0[EM_TPID1_OUT] = LaserTecOut1;
		NVRAM0[SPREG_DAC_8] = LaserTecOut0;
		NVRAM0[SPREG_DAC_9] = LaserTecOut1;
		if(LaserTecOut0 <= 0 ){
			SET_TEC_CH0_OFF;
		}
		else{
			SET_TEC_CH0_ON;
			
		}
		if(LaserTecOut1 <= 0){
			SET_TEC_CH1_OFF;
		}
		else{
			SET_TEC_CH1_ON;
		}
		UPDAC8();UPDAC9();
		LaserTecOut0 = LaserTecOut0 / 20;
		LaserTecOutCounter0 = 0;
	}	
	if(LaserTecOutCounter0 == 0){
		SSET(Y_TEC);
	}
	if(LDP(SPCOIL_PS10MS)){
		if(LaserTecOutCounter0 >= LaserTecOut0){
			RRES(Y_TEC);
		}
		LaserTecOutCounter0 ++;
	}
}








