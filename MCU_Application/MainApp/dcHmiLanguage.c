#include "dcHmiLanguage.h"
/*****************************************************************************/
const char *errorCodeToString[ERR_MAX_COUNT] = {
	[ERR_NO_ERROR]                          = "",
	[ERR_INTERLOCK_UNPLUG]                  = "E01:Door interlock disconnected",
	[ERR_FOOTSWITCH_UNPLUG]                 = "E02:Footswitch not connected",
	[ERR_ESTOP_PRESS]                       = "E03:ESTOP Press",
	[ERR_FIBER_UNPLUG]                      = "E04:No fiber connected",
	[ERR_OUT_ENERGY]                        = "E05:Energy out of tolerance",
	[ERR_LASER_EMIT]                        = "E06:Laser is firing",
	[ERR_WAIT_TRIGGER]                      = "E07:Wait Laser Trigger",
	[ERR_FIBER_MISSMATE]                    = "E08:Fiber not mate",
	[ERR_LASER_A_DIODE_TEMP_HIGH]           = "E10:Laser Diode A high temperature",
	[ERR_LASER_B_DIODE_TEMP_HIGH]           = "E11:Laser Diode B high temperature",
	[ERR_LASER_A_DIODE_TEMP_LOW]            = "E12:Laser Diode B low temperature",
	[ERR_LASER_B_DIODE_TEMP_LOW]            = "E13:Laser Diode B low temperature",
	[ERR_LASER_A_COUPLER_TEMP_HIGH]         = "E14:Laser Couple A high temperature",
	[ERR_LASER_B_COUPLER_TEMP_HIGH]         = "E15:",
	[ERR_LASER_A_COUPLER_TEMP_LOW]					= "E16",             
	[ERR_LASER_B_COUPLER_TEMP_LOW] 					= "E17",
	[ERR_LASER_A_CRYST0_TEMP_HIGH]          = "E18:",
	[ERR_LASER_A_CRYST1_TEMP_HIGH]          = "E17:",
	[ERR_LASER_B_CRYST0_TEMP_HIGH]          = "E18:",
	[ERR_LASER_B_CRYST1_TEMP_HIGH]          = "E19:",
	[ERR_LASER_A_CRYST0_TEMP_LOW]           = "E20:",
	[ERR_LASER_A_CRYST1_TEMP_LOW]           = "E21:",
	[ERR_LASER_B_CRYST0_TEMP_LOW]           = "E22:",
	[ERR_LASER_B_CRYST1_TEMP_LOW]           = "E23:",
	[ERR_HT0_TEMP_HIGH]                     = "E24:Heat sink 0 high temperature",
	[ERR_HT1_TEMP_HIGH]                     = "E25:Heat sink 1 high temperature",
	[ERR_HT2_TEMP_HIGH]                     = "E26:Heat sink 2 high temperature",
	[ERR_HT3_TEMP_HIGH]                     = "E27:Heat sink 3 high temperature",
	[ERR_HWATER_TEMP_HIGH]                  = "E28:Hot water high temperature",
	[ERR_HWATER_TEMP_LOW]                   = "E29:Hot water low temperature",
	[ERR_CWATER_TEMP_HIGH]                  = "E30:Cool water high temperature",
	[ERR_CWATER_TEMP_LOW]                   = "E31:Cool water low temperature",
	[ERR_AMBIENT0_TEMP_HIGH]                = "E32:",
	[ERR_AMBIENT0_TEMP_LOW]                 = "E33:",
	[ERR_AMBIENT1_TEMP_HIGH]                = "E34:",
	[ERR_AMBIENT1_TEMP_LOW]                 = "E35:",
	[ERR_AMBIENT2_TEMP_HIGH]                = "E36:",
	[ERR_AMBIENT2_TEMP_LOW]                 = "E37:",
	[ERR_AMBIENT3_TEMP_HIGH]                = "E38:",
	[ERR_AMBIENT3_TEMP_LOW]                 = "E39:",
	[ERR_HDC1080_TEMP_HIGH]                 = "E40:",
	[ERR_HDC1080_TEMP_LOW]                  = "E41:",
	[ERR_HDC1080_HUMIDITY_HIGH]             = "E42:",
	[ERR_HDC1080_HUMIDITY_LOW]              = "E43:",
	[ERR_DHT11_TEMP_HIGH]                   = "E44:",
	[ERR_DHT11_TEMP_LOW]                    = "E45:",
	[ERR_DHT11_HUMIDITY_HIGH]               = "E46:",
	[ERR_DHT11_HUMIDITY_LOW]                = "E47:",
	[ERR_MCU_TEMP_HIGH]                     = "E48:",
	[ERR_MCU_TEMP_LOW]                      = "E49:",
	[ERR_MBAT_TEMP_HIGH]                    = "E50:",
	[ERR_MBAT_TEMP_LOW]                     = "E51:",
	[ERR_DIODE_CH0_OVCP]                    = "E52:Laser current exceeds set value",
	[ERR_DIODE_CH1_OVCP]                    = "E53:Laser current exceeds set value",
	[ERR_DIODE_CH2_OVCP]                    = "E54:",
	[ERR_DIODE_CH3_OVCP]                    = "E55:",
	[ERR_DIODE_CH4_OVCP]                    = "E56:",
	[ERR_DIODE_CH5_OVCP]                    = "E57:",
	[ERR_DIODE_CH6_OVCP]                    = "E58:",
	[ERR_DIODE_CH7_OVCP]                    = "E59:",
	[ERR_HWATER_FLOW_LOW]                   = "E60:Water Flow Low",					
	[ERR_CWATER_FLOW_LOW]										=	"E61:"
};

const INFO_MSG_T info_msg = {
	.SN 						 									= "SN: ",
	.HW_VER					 									= "HW:"HW_VERSION"",
	.SW_VER 					 								= "App:"SW_VERSION"",
	.MANUFACTURE_DATE 								= "MANUFACTURE DATE: ",
	
#if defined(APP_CONFIG_WAVE_1470_650)
	.TYPE 						 								= "TYPE: PVGLS 1470/15",
	.LASER_POWER 				 							= "LASER_POWER: 15W+0.5W",
	.WAVELENGTH 				 							= "WAVE LENGTH: 1470nm+635nm"
#endif

#if defined(MODEL_PVGLS_7W_1940_A0)
	.TYPE 						 								= "TYPE: PVGLS 1940/7",
	.LASER_POWER 				 							= "LASER_POWER: 7W",
	.WAVELENGTH 				 							= "WAVE LENGTH: 1940nm"
#endif

#if defined(MODEL_PVGLS_10W_1940_A1)
	.TYPE 						 								= "TYPE: PVGLS 1940/10",
	.LASER_POWER 				 							= "LASER_POWER: 10W",
	.WAVELENGTH 				 							= "WAVE LENGTH: 1940nm"
#endif

#if defined(MODEL_PVGLS_TRI_A0)
	.TYPE 						 								= "TYPE: PVGLS - TRI",
	.LASER_POWER				 							= "LASER_POWER: 15w+15w+0.5w",
	.WAVELENGTH 				 							= "WAVE LENGTH: 1470nm+980nm+635nm"
#endif

#if defined(LDR2P1_G5_A1_20250731_TRIP)
	.TYPE 						 								= "TYPE: PVGLS - TRI",
	.LASER_POWER 				 							= "LASER_POWER: 15w+15w+0.5w",
	.WAVELENGTH 				 							= "WAVE LENGTH: 1470nm+980nm+635nm"
#endif

#if defined(LDR2P1_G5_A1_20250910_TRIP)
	.TYPE 						 								= "TYPE: PVGLS - TRI",
	.LASER_POWER 				 							= "LASER_POWER: 15w+30w+0.5w",
	.WAVELENGTH 				 							= "WAVE LENGTH: 1470nm+980nm+635nm"
#endif

#if defined(LYPE_MCU_1V0_20260106)
	.INFO_MSG_TYPE 						 				= "TYPE: PVGLS - DUAL",
	.INFO_MSG_LASER_POWER 				 		= "LASER_POWER: 200w+50w+5mw",
	.INFO_MSG_WAVELENGTH 				 			= "WAVE LENGTH: 450nm+980nm+635nm"
#endif
	
};

/*****************************************************************************/
const char *getErrorString(MSG_ID_T err_code){//根据错误码获取错误提示字符串
	// 越界保护
	if (err_code >= ERR_MAX_COUNT) {
			return "Unknown error code";
	}
	return errorCodeToString[err_code];
}




