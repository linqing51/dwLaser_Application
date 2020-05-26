#include "sPlc.h"
/*****************************************************************************/
extern char WARN_MSG_NO_ERROR[8][64];
extern char WARN_MSG_INTERLOCK_UNPLUG[8][64];//安全连锁没插
extern char WARN_MSG_FOOTSWITCH_UNPLUG[8][64];//脚踏没插
extern char WARN_MSG_ESTOP_PRESS[8][64];
extern char WARN_MSG_FIBER_UNPLUG[8][64];//光纤没插或者RFID不识别
extern char WARN_MSG_OUT_ENERGY[8][64];//功率偏差超20%，预留功能，可以以后实现
extern char WARN_MSG_DIODE_HTEMP[8][64];//温度过高
extern char WARN_MSG_DIODE_LTEMP[8][64];//温度过低
extern char WARN_MSG_DIODE0_OVERCURRENT[8][64];//电流超过限定值，保护激光器
extern char WARN_MSG_DIODE1_OVERCURRENT[8][64];//电流超过限定值，保护激光器
extern char WARN_MSG_NTC_ERROR[8][64];//热敏电阻故障
extern char WARN_MSG_ENVI_HTEMP[8][64];//环境温度过高
extern char WARN_MSG_FOOT_DEPRESSED[8][64];//脚踏按下去没弹起来
extern char WARN_MSG_LASER_EMIT[8][64];//激光正在发射
extern char WARN_MSG_WAIT_TRIGGER[8][64];//等待激光触发
extern char WARN_MSG_FIBER_MISSMATE[8][64];
extern char INFO_MSG_TYPE[8][64];
extern char INFO_MSG_SN[8][64];
extern char INFO_MSG_WAVELENGTH[8][64];
extern char INFO_MSG_LASER_POWER[8][64];
extern char INFO_MSG_VERSION[8][64];
extern char INFO_MSG_MANUFACTURE_DATE[8][64];
/*****************************************************************************/






