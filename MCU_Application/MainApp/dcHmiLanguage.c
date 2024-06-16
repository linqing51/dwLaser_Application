#include "dcHmiLanguage.h"
/*****************************************************************************/
const char WARN_MSG_NO_ERROR[]	        		 		= {""};			
const char WARN_MSG_INTERLOCK_UNPLUG[]		 	 	= {"Door interlock disconnected"};//安全连锁没插													
const char WARN_MSG_FOOTSWITCH_UNPLUG[]			= {"Footswitch not connected"};//脚踏没插
const char WARN_MSG_ESTOP_PRESS[]            	= {"ESTOP Press"};//急停按下
const char WARN_MSG_FIBER_UNPLUG[] 					= {"No fiber connected"};//光纤没插或者RFID不识别													
const char WARN_MSG_OUT_ENERGY[] 				 		= {"Energy out of tolerance"};//功率偏差超20%，预留功能，可以以后实现
const char WARN_MSG_DIODE_HTEMP[] 				 		= {"Laser overheating"};//温度过高
const char WARN_MSG_DIODE_LTEMP[] 				 		= {"Laser NTC open or lowheating"};//温度过低
const char WARN_MSG_DIODE0_OVERCURRENT[] 		= {"Laser current exceeds set value"};//电流超过限定值，保护激光器
const char WARN_MSG_DIODE1_OVERCURRENT[] 		= {"Laser current exceeds set value"};//电流超过限定值，保护激光器
const char WARN_MSG_NTC_ERROR[] 					 		= {"Thermistor Error"};//热敏电阻故障									
const char WARN_MSG_ENVI_HTEMP[] 				 		= {"Envi High Temperature"};//环境温度过高
const char WARN_MSG_ENVI_LTEMP[] 				 		= {"Envi Low Temperature"};//环境温度过高													
const char WARN_MSG_FOOT_DEPRESSED[] 			 	= {"Foot/finger switch is depressed"};//脚踏按下去没弹起来
const char WARN_MSG_LASER_EMIT[] 				 		= {"Laser is firing"};//激光正在发射
const char WARN_MSG_WAIT_TRIGGER[] 				 	= {"Wait Laser Trigger"};//等待激光触发
const char WARN_MSG_FIBER_MISSMATE[] 			 	= {"Fiber not mate"};
const char INFO_MSG_SN[] 						 				= {"SN: "};
#ifdef MODEL_PVGLS_15W_1470
const char INFO_MSG_VERSION[] 					 			= {"App Version: 3.1a13b1-Dual"};
#endif
#ifdef MODEL_PVGLS_TRI
const char INFO_MSG_VERSION[] 					 			= {"App Version: 3.1a13b1-Triple"};
#endif

const char INFO_MSG_MANUFACTURE_DATE[] 			= {"MANUFACTURE DATE: "};

#ifdef MODEL_PVGLS_7W_1940
const char INFO_MSG_TYPE[] 						 				= {"TYPE: PVGLS 1940/7"};
const char INFO_MSG_LASER_POWER[] 				 		= {"LASER_POWER: 7W"};
const char INFO_MSG_WAVELENGTH[] 				 			= {"WAVE LENGTH: 1940nm"};
#endif

#ifdef MODEL_PVGLS_15W_1470
const char INFO_MSG_TYPE[] 						 				= {"TYPE: PVGLS 1470/15"};
const char INFO_MSG_LASER_POWER[] 				 		= {"LASER_POWER: 15W+0.5W"};
const char INFO_MSG_WAVELENGTH[] 				 			= {"WAVE LENGTH: 1470nm+635nm"};
#endif

#ifdef MODEL_PVGLS_TRI
const char INFO_MSG_TYPE[] 						 				= {"TYPE: PVGLS - TRI"};
const char INFO_MSG_LASER_POWER[] 				 		= {"LASER_POWER: 15w+15w+0.5w"};
const char INFO_MSG_WAVELENGTH[] 				 			= {"WAVE LENGTH: 1470nm+980nm+635nm"};
#endif



/*****************************************************************************/








