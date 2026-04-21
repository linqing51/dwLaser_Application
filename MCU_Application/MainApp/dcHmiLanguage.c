#include "dcHmiLanguage.h"
/*****************************************************************************/
const WARN_MSG warn_msg_en = {
	.NO_ERROR	        								= "",			
	.INTERLOCK_UNPLUG		 							= "E01:Door interlock disconnected",//安全连锁没插													
	.FOOTSWITCH_UNPLUG								= "E02:Footswitch not connected",//脚踏没插
	.ESTOP_PRESS           						= "E03:ESTOP Press",//急停按下
	.FIBER_UNPLUG											= "E04:No fiber connected",//光纤没插或者RFID不识别													
	.OUT_ENERGY 				 							= "E05:Energy out of tolerance",//功率偏差超20%，预留功能，可以以后实现
	.LASER_EMIT 				 							= "E06:Laser is firing",//激光正在发射
	.WAIT_TRIGGER 				 						= "E07:Wait Laser Trigger",//等待激光触发
	.FIBER_MISSMATE 			 						= "E08:Fiber not mate",
	.LASER_DIODE_A_TEMP_HIGH    			= "E10:Laser Diode A high temperature",
	.LASER_DIODE_B_TEMP_HIGH					= "E11:Laser Diode B high temperature",					
	.LASER_DIODE_A_TEMP_LOW						= "E12:Laser Diode B low temperature",			
	.LASER_DIODE_B_TEMP_LOW						= "E13:Laser Diode B low temperature",				
	.LASER_COUPLER_A_TEMP_HIGH  			= "E14:",        
	.LASER_COUPLER_B_TEMP_HIGH  			= "E15:",       
	.LASER_CRYST0_A_TEMP_HIGH					= "E16:",				
	.LASER_CRYST1_A_TEMP_HIGH					= "E17:",		
	.LASER_CRYST0_B_TEMP_HIGH					= "E18:",			
	.LASER_CRYST1_B_TEMP_HIGH					= "E19:",			
	.LASER_CRYST0_A_TEMP_LOW    			= "E20:", 
	.LASER_CRYST0_B_TEMP_LOW    			= "E21:",  
	.LASER_CRYST1_A_TEMP_LOW    			= "E22:", 
	.LASER_CRYST1_B_TEMP_LOW    			= "E23:",
	.HT0_TEMP_HIGH 										= "E24:Heat sink 0 high temperature",									
	.HT1_TEMP_HIGH 										= "E25:Heat sink 1 high temperature",									
	.HT2_TEMP_HIGH 										= "E26:Heat sink 2 high temperature",								
	.HT3_TEMP_HIGH 										= "E27:Heat sink 3 high temperature",												
	.HWATER_TEMP_HIGH									= "E28:Hot water high temperature",
	.HWATER_TEMP_LOW									= "E29:Hot water low temperature",
	.CWATER_TEMP_HIGH									= "E30:Cool water high temperature",
	.CWATER_TEMP_LOW									= "E31:Cool water low temperature",
	.AMBIENT0_TEMP_HIGH								= "E32:",
	.AMBIENT0_TEMP_LOW								= "E33:",	
	.AMBIENT1_TEMP_HIGH								= "E34:",
	.AMBIENT1_TEMP_LOW				        = "E35:",
	.AMBIENT2_TEMP_HIGH			          = "E36:",
	.AMBIENT2_TEMP_LOW								= "E37:",
	.AMBIENT3_TEMP_HIGH			          = "E38:",
	.AMBIENT3_TEMP_LOW				        = "E39:",
	.HDC1080_TEMP_HIGH								= "E40:",			
	.HDC1080_TEMP_LOW									= "E41:",
	.HDC1080_HUMIDITY_HIGH						= "E42:",	
	.HDC1080_HUMIDITY_LOW							= "E43:",
	.DHT11_TEMP_HIGH									= "E44:",
	.DHT11_TEMP_LOW										= "E45:",	
	.DHT11_HUMIDITY_HIGH							= "E46:",	
	.DHT11_HUMIDITY_LOW								= "E47:",	
	.MCU_TEMP_HIGH										= "E48:",	
	.MCU_TEMP_LOW											= "E49:",	
	.MBAT_TEMP_HIGH										= "E50:",	
	.MBAT_TEMP_LOW										= "E51:",	
	.DIODE_A_OVERCURRENT							= "E52:Laser current exceeds set value",	
	.DIODE_B_OVERCURRENT							= "E53:Laser current exceeds set value",
	.FLOW_ABNORMAL										= "E54:Water Flow Low",									
	.HUMIDITY_ABNORMAL								= "E55:Humidity abnormal"	

};

const INFO_MSG info_msg = {
	.INFO_MSG_SN 						 					= "SN: ",
	.INFO_MSG_HW_VERSION 					 		= "HW:"HW_VERSION"",
	.INFO_MSG_SW_VERSION 					 		= "App:"SW_VERSION"",
	.INFO_MSG_MANUFACTURE_DATE 				= "MANUFACTURE DATE: ",
	
	#if defined(APP_CONFIG_WAVE_1470_650)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS 1470/15"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 15W+0.5W"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1470nm+635nm"};
#endif



#if defined(MODEL_PVGLS_7W_1940_A0)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS 1940/7"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 7W"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1940nm"};
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS 1940/10"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 10W"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1940nm"};
#endif

#if defined(MODEL_PVGLS_TRI_A0)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS - TRI"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 15w+15w+0.5w"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1470nm+980nm+635nm"};
#endif

#if defined(LDR2P1_G5_A1_20250731_TRIP)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS - TRI"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 15w+15w+0.5w"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1470nm+980nm+635nm"};
#endif

#if defined(LDR2P1_G5_A1_20250910_TRIP)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS - TRI"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 15w+30w+0.5w"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1470nm+980nm+635nm"};
#endif

#if defined(LYPE_MCU_1V0_20260106)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS - DUAL"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 200w+50w+5mw"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 450nm+980nm+635nm"};
#endif
	
	
};
const char 

/*****************************************************************************/
#if defined(APP_CONFIG_WAVE_1470_650)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS 1470/15"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 15W+0.5W"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1470nm+635nm"};
#endif



#if defined(MODEL_PVGLS_7W_1940_A0)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS 1940/7"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 7W"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1940nm"};
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS 1940/10"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 10W"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1940nm"};
#endif

#if defined(MODEL_PVGLS_TRI_A0)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS - TRI"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 15w+15w+0.5w"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1470nm+980nm+635nm"};
#endif

#if defined(LDR2P1_G5_A1_20250731_TRIP)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS - TRI"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 15w+15w+0.5w"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1470nm+980nm+635nm"};
#endif

#if defined(LDR2P1_G5_A1_20250910_TRIP)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS - TRI"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 15w+30w+0.5w"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 1470nm+980nm+635nm"};
#endif

#if defined(LYPE_MCU_1V0_20260106)
const char INFO_MSG_TYPE[] 						 			= {"TYPE: PVGLS - DUAL"};
const char INFO_MSG_LASER_POWER[] 				 	= {"LASER_POWER: 200w+50w+5mw"};
const char INFO_MSG_WAVELENGTH[] 				 		= {"WAVE LENGTH: 450nm+980nm+635nm"};
#endif

/*****************************************************************************/








