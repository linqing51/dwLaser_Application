#ifndef __TEMPCTRLOOP_H__
#define __TEMPCTRLOOP_H__
/*****************************************************************************/
#include "fan_controller.h"
#include "pid_temp_control.h"
/*****************************************************************************/
extern PID_Controller_t TempPid_A,TempPid_B;//ºãÎÂ¿ØÖÆÆ÷
extern void tempControlInit(void);
#endif








