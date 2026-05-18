#ifndef __DCHMILANGUAGE_H__
#define __DCHMILANGUAGE_H__
#include "sPlc.h"
#include "appConfig.h"
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
typedef enum{
	ERR_NO_ERROR = 0,
	ERR_INTERLOCK_UNPLUG,											
	ERR_FOOTSWITCH_UNPLUG,										
	ERR_ESTOP_PRESS,													
	ERR_FIBER_UNPLUG,													
	ERR_OUT_ENERGY,														
	ERR_LASER_EMIT,														
	ERR_WAIT_TRIGGER,													
	ERR_FIBER_MISSMATE,												
	ERR_LASER_A_DIODE_TEMP_HIGH,									
	ERR_LASER_B_DIODE_TEMP_HIGH,									
	ERR_LASER_A_DIODE_TEMP_LOW,									
	ERR_LASER_B_DIODE_TEMP_LOW,									
	ERR_LASER_A_COUPLER_TEMP_HIGH,               
	ERR_LASER_B_COUPLER_TEMP_HIGH,
	ERR_LASER_A_COUPLER_TEMP_LOW,               
	ERR_LASER_B_COUPLER_TEMP_LOW,  	
	ERR_LASER_A_CRYST0_TEMP_HIGH,								
	ERR_LASER_A_CRYST1_TEMP_HIGH,								
	ERR_LASER_B_CRYST0_TEMP_HIGH,								
	ERR_LASER_B_CRYST1_TEMP_HIGH,								
	ERR_LASER_A_CRYST0_TEMP_LOW,                
	ERR_LASER_A_CRYST1_TEMP_LOW,                
	ERR_LASER_B_CRYST0_TEMP_LOW,                
	ERR_LASER_B_CRYST1_TEMP_LOW,                
	ERR_HT0_TEMP_HIGH,												
	ERR_HT1_TEMP_HIGH,												
	ERR_HT2_TEMP_HIGH,												
	ERR_HT3_TEMP_HIGH,												
	ERR_HWATER_TEMP_HIGH,											
	ERR_HWATER_TEMP_LOW,											
	ERR_CWATER_TEMP_HIGH,											
	ERR_CWATER_TEMP_LOW,											
	ERR_AMBIENT0_TEMP_HIGH,										
	ERR_AMBIENT0_TEMP_LOW,										
	ERR_AMBIENT1_TEMP_HIGH,										
	ERR_AMBIENT1_TEMP_LOW,				            
	ERR_AMBIENT2_TEMP_HIGH,			              
	ERR_AMBIENT2_TEMP_LOW,										
	ERR_AMBIENT3_TEMP_HIGH,
	ERR_AMBIENT3_TEMP_LOW,
	ERR_HDC1080_TEMP_HIGH,		
	ERR_HDC1080_TEMP_LOW,
	ERR_HDC1080_HUMIDITY_HIGH,	
	ERR_HDC1080_HUMIDITY_LOW,
	ERR_DHT11_TEMP_HIGH,	
	ERR_DHT11_TEMP_LOW,
	ERR_DHT11_HUMIDITY_HIGH,
	ERR_DHT11_HUMIDITY_LOW,
	ERR_MCU_TEMP_HIGH,
	ERR_MCU_TEMP_LOW,
	ERR_MBAT_TEMP_HIGH,	
	ERR_MBAT_TEMP_LOW,	
	ERR_DIODE_CH0_OVCP,
	ERR_DIODE_CH1_OVCP,
	ERR_DIODE_CH2_OVCP,
	ERR_DIODE_CH3_OVCP,
	ERR_DIODE_CH4_OVCP,
	ERR_DIODE_CH5_OVCP,
	ERR_DIODE_CH6_OVCP,
	ERR_DIODE_CH7_OVCP,
	ERR_HWATER_FLOW_LOW,									
	ERR_CWATER_FLOW_LOW, 
  ERR_MAX_COUNT// 错误总数
}MSG_ID_T;

typedef struct{
	const char *TYPE;
	const char *SN;
	const char *WAVELENGTH;
	const char *LASER_POWER;
	const char *SW_VER;
	const char *HW_VER;
	const char *MANUFACTURE_DATE;
}INFO_MSG_T;
/*****************************************************************************/
extern const INFO_MSG_T info_msg;
const char *getErrorString(MSG_ID_T err_code);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif




