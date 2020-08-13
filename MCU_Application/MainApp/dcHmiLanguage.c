#include "dcHmiLanguage.h"
/*****************************************************************************/
char WARN_MSG_NO_ERROR[8][64]	        		 = {{""},
												    {""},
												    {""},
									                {""},
										            {""},
                                                    {""},
										            {""},
                                                    {""}};
			
char WARN_MSG_INTERLOCK_UNPLUG[8][64]		 	 = {{"Door interlock disconnected"},
												    {""},
												    {""},
													{""},
													{""},
													{""},
													{""},
													{""}};//安全连锁没插
													
char WARN_MSG_FOOTSWITCH_UNPLUG[8][64]		      ={{"Footswitch not connected"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//脚踏没插
													
char WARN_MSG_ESTOP_PRESS[8][64]                 = {{"ESTOP Press"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//急停按下

char WARN_MSG_FIBER_UNPLUG[8][64] 				 = {{"No fiber connected"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//光纤没插或者RFID不识别
													
char WARN_MSG_OUT_ENERGY[8][64] 				 = {{"Energy out of tolerance"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//功率偏差超20%，预留功能，可以以后实现
													
char WARN_MSG_DIODE_HTEMP[8][64] 				 = {{"Laser overheating"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//温度过高
													
char WARN_MSG_DIODE_LTEMP[8][64] 				 = {{"Laser NTC Open"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//温度过低
													
char WARN_MSG_DIODE0_OVERCURRENT[8][64] 		 = {{"Laser current exceeds set value"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//电流超过限定值，保护激光器
													
char WARN_MSG_DIODE1_OVERCURRENT[8][64] 		 = {{"Laser current exceeds set value"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//电流超过限定值，保护激光器
													
char WARN_MSG_NTC_ERROR[8][64] 					 = {{"Thermistor Error"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//热敏电阻故障
													
char WARN_MSG_ENVI_HTEMP[8][64] 				 = {{"Envi High Temperature"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//环境温度过高
													
char WARN_MSG_FOOT_DEPRESSED[8][64] 			 = {{"Foot/finger switch is depressed"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//脚踏按下去没弹起来
													
char WARN_MSG_LASER_EMIT[8][64] 				 = {{"Laser is firing"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//激光正在发射
													
char WARN_MSG_WAIT_TRIGGER[8][64] 				 = {{"Wait Laser Trigger"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};//等待激光触发
													
char WARN_MSG_FIBER_MISSMATE[8][64] 			 = {{"Fiber not mate"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};

char INFO_MSG_TYPE[8][64] 						 = {{"TYPE: Dual Git Engineering Sample"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};
													
char INFO_MSG_SN[8][64] 						 = {{"SN: 1234-67-AAAA"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};
													
char INFO_MSG_WAVELENGTH[8][64] 				 = {{"WAVE LENGTH: 980nM"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};
													
char INFO_MSG_LASER_POWER[8][64] 				 = {{"LASER_POWER: 30W"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};
													
char INFO_MSG_VERSION[8][64] 					 = {{"VERSION: 2.01"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};
													
char INFO_MSG_MANUFACTURE_DATE[8][64] 			 = {{"MANUFACTURE DATE:2020-08-13"},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""},
													{""}};
/*****************************************************************************/








