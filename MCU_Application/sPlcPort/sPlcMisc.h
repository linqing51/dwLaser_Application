#include "sPlc.h"
/*****************************************************************************/
#define BEEM_MODE_0													0x10//连续模式
#define BEEM_MODE_1													0x11//声光同步
#define BEEM_MODE_2													0x12//激光发射固定间隔
#define BEEM_MODE_3													0x13//异常报警
/*****************************************************************************/
void resetInit(void);
void bootLoadInit(void);
/*****************************************************************************/
void sPlcLoudspeakerLoop(void);//蜂鸣器轮询
void sPlcAimLoop(void);//瞄准光轮询
void sPlcAutoFanLoop(void);//风扇速轮询程序
void setLoudspeakerFreq(int16_t freq);//设置喇叭频率
void setLoudspeakerVolume(int16_t volume);//设置喇叭音量
void setLoudspeakerEnable(void);//打开喇叭数据流
void setLoudspeakerDisable(void);//关闭喇叭数据流
void initLoudspeaker(void);//喇叭初始化
void setAimFreq(int16_t freq);//设置AIM PWM频率
void setLedFreq(int16_t freq);//设置LED PWM频率
void setFanFreq(int16_t freq);//设置FAN PWM频率
void setAimBrightness(int16_t brg);//设置瞄准光亮度
void setRedLedBrightness(int16_t brg);//设置R LED亮度
void setGreenLedBrightness(int16_t brg);//设置G LED亮度
void setYellowLedBrightness(int16_t brg);//设置Y LED亮度
/*****************************************************************************/







