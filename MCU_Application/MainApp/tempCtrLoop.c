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
  //Kp: 0.21, Ki: 0.0046, Kd: 0.57
  PID_Init(&ClassicPid_A, 0.21f, 0.0046f, 0.57f, 250, 4095);
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

void tempControlLoop(void){//温度风扇控制循环
	float32_t ftmp0, ftmp1;
	ftmp0 = !ftmp0;
	ftmp1 = !ftmp1;
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
		ClassicPid_A.setpoint = deviceConfig.laserDiodeA_Temp;	
		LaserTecOut0 = PID_Compute(&ClassicPid_A, NVRAM0[EM_LASER_A_DIODE_TEMP]);	
#endif

#if CONFIG_USING_FUZZY_PID == 1
		FuzzyPID_SetSetpoint(&FuzzyPid_A, deviceConfig.laserDiodeA_Temp); // 设定目标温度为 25℃
		LaserTecOut0 = FuzzyPID_Compute(&FuzzyPid_A, NVRAM0[EM_LASER_A_DIODE_TEMP]);
#endif		
		
#if CONFIG_USING_SMART_PID == 1		
		//辨识未完成期间，保持小功率输出或零输出，等待辨识结束
		if(!SmartPID_Identify(&SmartPid_A, (float32_t)NVRAM0[EM_LASER_A_DIODE_TEMP] / 10.0F, &ftmp0)){
		}
		else{//辨识完成或跳过辨识后，执行常规PID闭环控制
			ftmp0 = SmartPID_Compute(&SmartPid_A, (float32_t)NVRAM0[EM_LASER_A_DIODE_TEMP]);
		}
		LaserTecOut0 =(int16_t)(ftmp0 * 4095);
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








