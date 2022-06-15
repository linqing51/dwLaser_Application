#ifndef __SPLCSPEAKER_H__
#define __SPLCSPEAKER_H__
/*****************************************************************************/
#include "sPlc.h"
/*****************************************************************************/
void setLoudspeakerFreq(int16_t freq);//设置喇叭频率
void setLoudspeakerVolume(int16_t volume);//设置喇叭音量
void setLoudspeakerEnable(void);//打开喇叭数据流
void setLoudspeakerDisable(void);//关闭喇叭数据流
void initLoudspeaker(void);//喇叭初始化



#endif




