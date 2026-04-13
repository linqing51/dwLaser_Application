#include "dcHmiApp.h"
#include "tempCtrLoop.h"
/*****************************************************************************/
PID_Controller_t TempPid_A,TempPid_B;//恒温控制器
FanController AutoFan0, AutoFan1;// 创建风扇控制器实例
int16_t LaserTecOutCounter, LaserTecOut;
/*****************************************************************************/
void tempControlInit(void){
	PID_Init(&TempPid_A, 5.0f, 0.6f, 2.0f, NVRAM0[EM_LASER_A_DIODE_TEMP], 500);
	PID_Init(&TempPid_B, 5.0f, 0.6f, 2.0f, NVRAM0[EM_LASER_B_DIODE_TEMP], 500);
	FanController_Init(&AutoFan0, fan_curve, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
	FanController_Init(&AutoFan1, fan_curve, CONFIG_FAN_CURVE_POINTS, 3, 0.3f, 10, 100);//初始化风扇控制器（核心算法与硬件接口绑定）
}

void tempControlLoop(void){
	//温控执行 激光等待发射及错误状态启动温控
	if(LDP(SPCOIL_PS100MS)){//0.2秒间隔
		if(LD(R_TEMP_FAULT)){//温度异常无条件打开风扇
			 	NVRAM0[EM_FAN0_SET_SPEED] = 100;
		}
		else{
			AutoFan0.current_temp = ((float)NVRAM0[EM_HT0_TEMP] / 10.0F);//关联温度
			AutoFan1.current_temp = ((float)NVRAM0[EM_HT1_TEMP] / 10.0F);//关联温度
			FanController_Run(&AutoFan0);// 更新风扇控制
			FanController_Run(&AutoFan1);// 更新风扇控制
			NVRAM0[EM_FAN0_SET_SPEED] = AutoFan0.current_speed;
		}
		setFanSpeed(NVRAM0[EM_FAN0_SET_SPEED]);
		TempPid_A.setpoint = deviceConfig.laserDiodeA_Temp;
		TempPid_B.setpoint = deviceConfig.laserDiodeB_Temp;
		LaserTecOut = PID_Compute(&TempPid_A, NVRAM0[EM_LASER_A_DIODE_TEMP]);	
		LaserTecOut = PID_Compute(&TempPid_B, NVRAM0[EM_LASER_B_DIODE_TEMP]);	
		
		NVRAM0[EM_TPID0_OUT] = LaserTecOut;
		NVRAM0[EM_TPID1_OUT] = LaserTecOut;
		NVRAM0[SPREG_DAC_8] = LaserTecOut;
		NVRAM0[SPREG_DAC_9] = LaserTecOut;
		if(LaserTecOut <= 0 ){
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
		LaserTecOut = LaserTecOut / 20;
		LaserTecOutCounter = 0;
	}	
	if(LaserTecOutCounter == 0){
		SSET(Y_TEC);
	}
	if(LDP(SPCOIL_PS10MS)){
		if(LaserTecOutCounter >= LaserTecOut){
			RRES(Y_TEC);
		}
		LaserTecOutCounter ++;
	}
}








