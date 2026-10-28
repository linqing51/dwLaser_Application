#ifndef __TEMPCTRLOOP_H__
#define __TEMPCTRLOOP_H__
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#include "fan_controller.h"

#if CONFIG_USING_CLASSIC_PID == 1
#include "classic_pid.h"

extern PID_Controller_t TempPid_A,TempPid_B;//恒温控制器
#endif
#if CONFIG_USING_FUZZY_PID == 1
#include "fuzzy_pid.h"
#endif
#if CONFIG_USING_SMART_PID == 1
#include "smart_pid.h"
#endif
#if CONFIG_USING_NN_PID == 1
#include "nn_pid.h"
#endif
#if CONFIG_USING_RLS_PID == 1
#include "rls_pid.h"
#endif
#if CONFIG_USING_ADRC_PID == 1
#include "adrc_pid.h"
#endif
#if CONFIG_USING_MPC_PID == 1
#include "mpc_pid.h"
#endif
#if CONFIG_USING_IMC_PID == 1
#include "imc_pid.h"
#endif
#if CONFIG_USING_ILC_PID == 1
#include "ilc_pid.h"
#endif


/*****************************************************************************/



extern void tempControlInit(void);
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif








