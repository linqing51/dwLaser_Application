#ifndef __DCHMILANGUAGE_H__
#define __DCHMILANGUAGE_H__
#include "sPlc.h"
#include "appConfig.h"
/*****************************************************************************/
typedef struct{
	const char *NO_ERROR;			
	const char *INTERLOCK_UNPLUG;//安全连锁没插													
	const char *FOOTSWITCH_UNPLUG;//脚踏没插
	const char *ESTOP_PRESS;//急停按下
	const char *FIBER_UNPLUG;//光纤没插或者RFID不识别													
	const char *OUT_ENERGY;//功率偏差超20%，预留功能，可以以后实现
	const char *LASER_EMIT;//激光正在发射
	const char *WAIT_TRIGGER;//等待激光触发
	const char *FIBER_MISSMATE;
	const char *LASER_DIODE_A_TEMP_HIGH;
	const char *LASER_DIODE_B_TEMP_HIGH;					
	const char *LASER_DIODE_A_TEMP_LOW;				
	const char *LASER_DIODE_B_TEMP_LOW;							
	const char *LASER_COUPLER_A_TEMP_HIGH;          
	const char *LASER_COUPLER_B_TEMP_HIGH;         
	const char *LASER_CRYST0_A_TEMP_HIGH;						
	const char *LASER_CRYST1_A_TEMP_HIGH;					
	const char *LASER_CRYST0_B_TEMP_HIGH;					
	const char *LASER_CRYST1_B_TEMP_HIGH;					
	const char *LASER_CRYST0_A_TEMP_LOW;     
	const char *LASER_CRYST0_B_TEMP_LOW;      
	const char *LASER_CRYST1_A_TEMP_LOW; 
	const char *LASER_CRYST1_B_TEMP_LOW;  
	const char *HT0_TEMP_HIGH;				
	const char *HT1_TEMP_HIGH;				
	const char *HT2_TEMP_HIGH;				
	const char *HT3_TEMP_HIGH;			
	const char *HWATER_TEMP_HIGH;	
	const char *HWATER_TEMP_LOW;		
	const char *CWATER_TEMP_HIGH;										
	const char *CWATER_TEMP_LOW;											
	const char *AMBIENT0_TEMP_HIGH;									
	const char *AMBIENT0_TEMP_LOW;											
	const char *AMBIENT1_TEMP_HIGH;									
	const char *AMBIENT1_TEMP_LOW;				            
	const char *AMBIENT2_TEMP_HIGH;			            
	const char *AMBIENT2_TEMP_LOW;										
	const char *AMBIENT3_TEMP_HIGH;			            
	const char *AMBIENT3_TEMP_LOW;				            
	const char *HDC1080_TEMP_HIGH;													
	const char *HDC1080_TEMP_LOW;										
	const char *HDC1080_HUMIDITY_HIGH;									
	const char *HDC1080_HUMIDITY_LOW;								
	const char *DHT11_TEMP_HIGH;											
	const char *DHT11_TEMP_LOW;												
	const char *DHT11_HUMIDITY_HIGH;										
	const char *DHT11_HUMIDITY_LOW;											
	const char *MCU_TEMP_HIGH;													
	const char *MCU_TEMP_LOW;													
	const char *MBAT_TEMP_HIGH;												
	const char *MBAT_TEMP_LOW;													
	const char *DIODE_A_OVERCURRENT;										
	const char *DIODE_B_OVERCURRENT;									
	const char *FLOW_ABNORMAL;																					
	const char *HUMIDITY_ABNORMAL;	
}WARN_MSG;

typedef struct{
	const char *TYPE;
	const char *SN;
	const char *WAVELENGTH;
	const char *LASER_POWER;
	const char *SW_VER;
	const char *HW_VER;
	const char *MANUFACTURE_DATE;
}INFO_MSG;
/*****************************************************************************/
extern const WARN_MSG warn_msg_en;
extern const INFO_MSG info_msg;
#endif




