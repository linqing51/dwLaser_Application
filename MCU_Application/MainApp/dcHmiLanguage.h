#ifndef __DCHMILANGUAGE_H__
#define __DCHMILANGUAGE_H__
#include "sPlc.h"
/*****************************************************************************/
extern const char WARN_MSG_NO_ERROR[];
extern const char WARN_MSG_INTERLOCK_UNPLUG[];//安全连锁没插
extern const char WARN_MSG_FOOTSWITCH_UNPLUG[];//脚踏没插
extern const char WARN_MSG_ESTOP_PRESS[];
extern const char WARN_MSG_FIBER_UNPLUG[];//光纤没插或者RFID不识别
extern const char WARN_MSG_OUT_ENERGY[];//功率偏差超20%，预留功能，可以以后实现
extern const char WARN_MSG_DIODE_HTEMP[];//温度过高
extern const char WARN_MSG_DIODE_LTEMP[];//温度过低
extern const char WARN_MSG_DIODE0_OVERCURRENT[];//电流超过限定值，保护激光器
extern const char WARN_MSG_DIODE1_OVERCURRENT[];//电流超过限定值，保护激光器
extern const char WARN_MSG_NTC_ERROR[];//热敏电阻故障
extern const char WARN_MSG_ENVI_HTEMP[];//环境温度过高
extern const char WARN_MSG_ENVI_LTEMP[];//环境温度过低
extern const char WARN_MSG_FOOT_DEPRESSED[];//脚踏按下去没弹起来
extern const char WARN_MSG_LASER_EMIT[];//激光正在发射
extern const char WARN_MSG_WAIT_TRIGGER[];//等待激光触发
extern const char WARN_MSG_FIBER_MISSMATE[];
extern const char INFO_MSG_TYPE[];
extern const char INFO_MSG_SN[];
extern const char INFO_MSG_WAVELENGTH[];
extern const char INFO_MSG_LASER_POWER[];
extern const char INFO_MSG_VERSION[];
extern const char INFO_MSG_MANUFACTURE_DATE[];
/*****************************************************************************/

#endif






