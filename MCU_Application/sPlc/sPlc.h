/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#ifndef __SPLC_H__
#define __SPLC_H__
/*****************************************************************************/
//stm32
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h" 
/*****************************************************************************/
//cdev
#include "math.h"
#include <stdio.h>
#include <stddef.h> 
#include <stdlib.h> 
#include <string.h>
#include <ctype.h>
#include <LIMITS.H>
#include "stdbool.h"
#include "stdint.h"
#include "string.h"
/*****************************************************************************/
//lib
#include "..\config\myConfig.h"
#include "sPlcEprom.h"
#include "libcrc.h"
#include "libdbg.h"
#include "libcpu.h"
#include "flash_if.h"
#include "minicsv.h"
#include "treatment.h"
/*****************************************************************************/
#include "classic_pid.h"
/*****************************************************************************/
//usb
#include "usbh_msc.h"
#include "usb_host.h"
#include "usbh_core.h"
/*****************************************************************************/
//fatfs
#include "ff.h"
#include "ff_gen_drv.h"
#include "flash_if.h"
/*****************************************************************************/
#if CONFIG_SPLC_USING_FUNTEST == 1
#include "sPlcTest.h"
#endif
/*****************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif
/*****************************************************************************/
#define BEEM_MODE_0														0x10//杩炵画妯″紡
#define BEEM_MODE_1														0x11//澹板厜鍚屾
#define BEEM_MODE_2														0x12//婵€鍏夊彂灏勫浐瀹氶棿闅?
#define BEEM_MODE_3														0x13//寮傚父鎶ヨ
#define BEEM_MODE_4														0x14//婵€鍏夊彂灏勫浐瀹氶棿闅?鎻愮ず闊?
#define BEEM_MODE_5														0x15
/*****************************************************************************/
#define LASER_MODE_CW													0x01//杩炵画妯″紡
#define LASER_MODE_MP													0x02//澶氳剦鍐叉ā寮?
/*****************************************************************************/


typedef struct{
	uint16_t calibrationPwr0[20];//閫氶亾0鍔熺巼鏍℃琛?
	uint16_t calibrationPwr1[20];//閫氶亾1鍔熺巼鏍℃琛?
	uint16_t calibrationPwr2[20];//閫氶亾2鍔熺巼鏍℃琛?
	uint16_t calibrationPwr3[20];//閫氶亾3鍔熺巼鏍℃琛?
	uint16_t calibrationPwr4[20];//閫氶亾4鍔熺巼鏍℃琛?
	uint16_t calibrationPwr5[20];//閫氶亾5鍔熺巼鏍℃琛?
	uint16_t calibrationPwr6[20];//閫氶亾6鍔熺巼鏍℃琛?
	uint16_t calibrationPwr7[20];//閫氶亾7鍔熺巼鏍℃琛?
	char serialNumber[16];//搴忓垪鍙?
	int16_t mfg_year;//鐢熶骇骞?
	int16_t mfg_month;//鐢熶骇鏈?
	int16_t mfg_day;//鐢熶骇鏃?
	int8_t redLedDc;//绾㈢伅浜害
	int8_t greenLedDc;//缁跨伅浜害
	int8_t blueLedDc;//钃濈伅浜害
	int8_t redAimGain;//绾㈡寚绀哄厜澧炵泭
	int8_t greenAimGain;//缁挎寚绀哄厜澧炵泭
	int16_t fiberDetect;//鍏夌氦鎺㈡祴闃堝€?
	int16_t laserDiodeA_Temp;//婵€鍏夊櫒A璁剧疆娓╁害
	int16_t laserDiodeB_Temp;//婵€鍏夊櫒B璁剧疆娓╁害
	char normalOpenInterLock;
}deviceConfig_t;

typedef struct{
	uint32_t powerUpCycle;//寮€鏈烘鏁?
	uint32_t runTime;//杩愯绱鏃堕棿 鍗曚綅鍒嗛挓
	int16_t laserMaxPhotoDiode;//婵€鍏夊櫒鏈€澶у姛鐜?
	int16_t mucMaxTemper;//澶勭悊鍣ㄦ渶楂樻俯搴?
}deviceLogInfo_t;

/*****************************************************************************/
extern deviceConfig_t deviceConfig;
extern deviceLogInfo_t deviceLogInfo;
extern uint32_t	UniqueId[3];//澶勭悊鍣ㄥ簭鍒楀彿 
/*****************************************************************************/
extern int16_t NVRAM0[CONFIG_NVRAM_SIZE];//鎺夌數淇濇寔瀵勫瓨鍣?褰撳墠 鍖呭惈瀛樻。瀵勫瓨鍣?
extern int16_t NVRAM1[CONFIG_NVRAM_SIZE];//鎺夌數淇濇寔瀵勫瓨鍣?涓婁竴娆?
extern int16_t FDRAM0[CONFIG_FDRAM_SIZE], FDRAM1[CONFIG_FDRAM_SIZE];//瀛樻。瀵勫瓨鍣?
#ifdef CONFIG_BKRAM_SIZE
#define CONFIG_BKSRAM_BASE_ADDR								(0x40024000UL)//STM32F405 BKPSRAM 4K 鎺夌數淇濇寔鍖鸿捣濮嬪湴鍧€
#define BKRAM																	((int16_t *)CONFIG_BKSRAM_BASE_ADDR)//BK 2K鍖哄潡 鐩存帴鏄犲皠纭欢BKSRAM
#endif
extern uint16_t TimerCounter_10mS;//10姣
extern uint16_t TimerCounter_100mS;//100姣
extern uint16_t TimerCounter_200mS;//200姣
extern uint16_t TimerCounter_500mS;//500姣
extern uint16_t TimerCounter_1000mS;//1绉?
extern uint16_t TimerCounter_60000mS;//1鍒嗛挓
extern uint8_t TD_10MS_SP;
extern uint8_t TD_100MS_SP;
extern uint8_t TD_200MS_SP;
extern uint8_t TD_500MS_SP;
extern uint8_t TD_1000MS_SP;
extern uint8_t TD_60000MS_SP;
extern uint32_t sPlcTick;
extern uint32_t BootloadCrc, ApplicationCrc;
/*****************************************************************************/
extern int8_t LaserTimer_Mode;
extern int16_t LaserTimer_TCounter;
extern int16_t LaserTimer_TMate;
extern int16_t LaserTimer_TOvertime;
extern int16_t LaserTimer_PCounter;
extern int16_t LaserTimer_PMate;
extern int16_t LaserTimer_POvertime;
extern int16_t LaserTimer_ReleaseTime;
extern int16_t LaserTimer_ReleaseCounter;
extern int8_t  LaserFlag_Emiting;//婵€鍏夊彂灏勪腑鏍囧織
extern int8_t LaserFlag_Emitover;//婵€鍏夊彂灏勫畬姣曟爣蹇?
/*****************************************************************************/
extern void sPlcInit(void);//杞€昏緫鍒濆鍖?
extern void sPlcProcessStart(void);//sPLC杞璧峰
extern void sPlcProcessEnd(void);//sPLC杞缁撴潫
extern void sPlcPortProcess(void);//sPLC骞冲彴绋嬪簭
extern void sPlcAssertCoilAddress(uint16_t adr);
extern void sPlcAssertRegisterAddress(uint16_t adr);
/*****************************************************************************/
extern void sPlcIsrDisable(void);
extern void sPlcIsrEnable(void);
extern void sPlcSpeakerFreq(int16_t freq);//璁剧疆鍠囧彮棰戠巼
extern void sPlcSpeakerVolume(int16_t volume);//璁剧疆鍠囧彮闊抽噺
extern void sPlcSpeakerEnable(void);//鎵撳紑鍠囧彮鏁版嵁娴?
extern void sPlcSpeakerDisable(void);//鍏抽棴鍠囧彮鏁版嵁娴?
extern void sPlcSpeakerInit(void);//鍠囧彮鍒濆鍖?
extern void sPlcNvramUpdate(void);//鏇存柊NVRAM->EPROM	
extern void sPlcNvramLoad(void);
extern void sPlcNvramSave(void);
extern void sPlcNvramClear(void);//娓呴櫎NVRAM鏁版嵁
extern void sPlcFdramLoad(void);
extern void sPlcFdramSave(void);
extern void sPlcFdramClear(void);
#ifdef CONFIG_BKRAM_SIZE
extern void sPlcBkramLoad(void);//浠嶦PROM涓浇鍏K(鏄犲皠BKSRAM)
extern void sPlcBkramSave(void);//BKSRAM->EPROM 寮哄埗淇濆瓨
extern void sPlcBkramClear(void);//娓呴櫎BK鏁版嵁(鍚獷PROM BK鍖?
#endif
extern void sPlcDeviceConfigClear(void);
extern void sPlcDeviceLogClear(void);
extern void mucReboot(void);//杞欢澶嶄綅
extern void resetInit(void);
extern void SystemClock_Reset(void);//澶嶄綅绯荤粺鏃堕挓
extern void setRedLaserPwm(int16_t pwm);//璁剧疆绾㈡縺鍏夊崰绌烘瘮
extern void setGreenLaserPwm(int16_t pwm);//璁剧疆缁挎縺鍏夊崰绌烘瘮
extern void setPower_635(int16_t pwr);//璁剧疆绾㈡縺鍏夊姛鐜?
extern void morseCodeDiag(uint8_t diag);//璇婃柇鐮?
extern void saveDeviceConfig(void);//灏嗛厤缃啓鍏PROM
extern void loadDeviceConfig(void);//浠嶦PROM杞藉叆閰嶇疆鏂囦欢
extern void saveCalibrationTable(uint8_t channel);//鍌ㄥ瓨閫夊畾閫氶亾鐨勫姛鐜囨牎鍑嗚〃
extern uint32_t getOriginBootloadCrc(void);//璁＄畻MCU Bootload CRC32
extern uint32_t getOriginAppCrc(void);//璁＄畻MCU App CRC32
extern uint8_t updateBootloadReq(void);//鏇存柊BOOTLOAD璇锋眰
extern void confirmBootloadUpdate(void);//鎵цBootload鏇存柊
extern void exitBootloadUpdate(void);//閫€鍑築ootload鏇存柊
/*****************************************************************************/
extern void RtcInitTimeDefault(void);
extern void RtcCheckAndInit(void);//RTC鎺夌數妫€娴嬩笌闃查攣姝诲垵濮嬪寲(鍚獴KSRAM浣胯兘)
extern void RtcGetNowTime(uint8_t *year,uint8_t *mon,uint8_t *day, uint8_t *hour,uint8_t *min,uint8_t *sec);
extern void RtcSetTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec);
extern void RtcGetDateTime(uint16_t *year, uint8_t *mon, uint8_t *day, uint8_t *hour, uint8_t *min, uint8_t *sec);//鑾峰彇褰撳墠鏃堕棿 甯歌鑷劧杈撳叆(year瀹屾暣4浣嶆暟)
extern uint8_t RtcSetDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec);//璁剧疆褰撳墠鏃堕棿 甯歌鑷劧杈撳叆,鎴愬姛杩斿洖1
extern void RtcSetYear(uint8_t tmp);
extern void RtcSetMonth(uint8_t tmp);
extern void RtcSetDate(uint8_t tmp);
extern void RtcSetHours(uint8_t tmp);
extern void RtcSetMinutes(uint8_t tmp);
extern void RtcSetSeconds(uint8_t tmp);
/*****************************************************************************/
extern void REBOOT(void) ;//澶嶄綅
//浣嶆寚浠?
extern void SSET(uint16_t A);//绾垮湀缃綅
extern void RRES(uint16_t A);//绾垮湀澶嶄綅
extern void FLIP(uint16_t A) ;//缈昏浆
extern uint8_t LD(uint16_t A) ;//杞藉叆
extern uint8_t LDB(uint16_t A) ;//鏂瑰悜杞藉叆
extern uint8_t LDP(uint16_t A) ;//鑴夊啿涓婂崌娌?
extern uint8_t LDN(uint16_t A) ;//鑴夊啿涓嬮檷娌?
//璁℃椂鍣ㄦ寚浠?
extern void T10MS(uint8_t A, uint8_t start, uint16_t value) ;//10mS璁℃椂鍣ㄥ惎鍔?
extern void T100MS(uint8_t A, uint8_t start, uint16_t value) ;//100mS璁℃椂鍣ㄥ惎鍔?
//杩愮畻鎸囦护
extern void CLR(uint16_t A) ;//瀵勫瓨鍣ㄦ竻闆?
extern void CLRD(uint16_t A) ;//32浣嶅瘎瀛樺櫒娓呴浂
extern void MOV(uint16_t dist, uint16_t src) ;//16浣嶅瘎瀛樺櫒浼犺緭
extern void MOVD(uint16_t dist, uint16_t src) ;//32浣嶅瘎瀛樺櫒浼犺緭
extern void SWAP(uint16_t dist, uint16_t src) ;//浜ゆ崲A鐨勯珮浣庡瓧鑺?
extern void ABS16(uint16_t dist, uint16_t src) ;//16浣嶆暟鐞冪粷瀵瑰€?
extern void ABS32(uint16_t dist, uint16_t src) ;//32浣嶆暟姹傜粷瀵瑰€?
extern void SMIN16(uint16_t index, uint16_t length, uint16_t min) ;//16浣嶆湁绗﹀彿鏁扮粍鎵炬渶灏忓€?
extern void SMAX16(uint16_t index, uint16_t length, uint16_t max) ;//16浣嶆湁绗﹀彿鏁扮粍鎵炬渶澶у€?
extern void UMIN16(uint16_t index, uint16_t length, uint16_t min) ;//16浣嶆棤绗﹀彿鏁扮粍鎵炬渶灏忓€?
extern void UMAX16(uint16_t index, uint16_t length, uint16_t max) ;//16浣嶆棤绗﹀彿鏁扮粍鎵炬渶澶у€?
extern void SUM16(uint16_t index, uint16_t length, uint16_t sum) ;//16BIT鏁版眰鍜?>32BIT
extern void MULT32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->32闈為ケ鍜屼箻娉?D = Sa * Sb
extern void MULTS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->16楗卞拰涔樻硶 D = Sa * Sb
extern void MULT16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16*16->16闈為ケ鍜屼箻娉?D = Sa * Sb
extern void SUB32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32浣嶉潪楗卞拰鍑忔硶 D = Sa - Sb
extern void SUBS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16浣嶉ケ鍜屽噺娉?D = Sa - Sb
extern void SUB16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16浣嶉潪楗卞拰鍑忔硶 D = Sa - Sb
extern void ADD32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32浣嶉潪楗卞姞娉?D = Sa + Sb
extern void ADDS32(uint16_t Sa, uint16_t Sb, uint16_t D) ;//32浣嶉ケ鍜屽姞娉?D = Sa + Sb
extern void ADDS16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16浣嶉ケ鍜屽姞娉?D = Sa + Sb
extern void ADD16(uint16_t Sa, uint16_t Sb, uint16_t D) ;//16浣嶉潪楗卞拰鍔犳硶 D = Sa + Sb
extern void ADD1(uint16_t Sa) ;//16浣嶉潪楗卞拰鑷姞
extern void ADDS1(uint16_t Sa) ;//16浣嶉ケ鍜岃嚜鍔?
extern void DEC1(uint16_t Sa) ;//16浣嶉潪楗卞拰鑷噺
extern void DECS1(uint16_t Sa) ;//16浣嶉ケ鍜岃嚜鍑?
extern void ADL1(uint16_t Sa) ;//32浣嶉潪楗卞拰鑷姞
extern void ADLS1(uint16_t Sa) ;//32浣嶉ケ鍜岃嚜鍔?
extern void DEL1(uint16_t Sa) ;//32浣嶉潪楗卞拰鑷噺
extern void DELS1(uint16_t Sa) ;//32浣嶉ケ鍜岃嚜鍑?
extern void TNTLC(uint16_t dist, uint16_t src, float ntc_rs, float ntc_b);//CODE杞崲涓虹幆澧冩俯搴?涓嬬數闃?
extern void TNTUC(uint16_t dist, uint16_t src, float ntc_rs, float ntc_b);//CODE杞崲涓虹幆澧冩俯搴?涓婄數闃?
extern void TENV(uint16_t dist, uint16_t src);//CODE杞崲涓篘TC娴嬮噺娓╁害娓╁害
extern void BCPY(uint16_t dist, uint16_t src, uint16_t length);//鍧楀鍒?
extern void LIMS16(uint16_t src, uint16_t min, uint16_t max);//鏈夌鍙?6浣嶆暟闄愬埗骞呭害鎸囦护
extern void UPDAC0(void);//绔嬪嵆鏇存柊LASER DAC0
extern void UPDAC1(void);//绔嬪嵆鏇存柊LASER DAC1
extern void UPDAC2(void);//绔嬪嵆鏇存柊LASER DAC2
extern void UPDAC3(void);//绔嬪嵆鏇存柊LASER DAC3
extern void UPDAC4(void);//绔嬪嵆鏇存柊LASER DAC4
extern void UPDAC5(void);//绔嬪嵆鏇存柊LASER DAC5
extern void UPDAC6(void);//绔嬪嵆鏇存柊LASER DAC6
extern void UPDAC7(void);//绔嬪嵆鏇存柊LASER DAC7
extern void UPDAC8(void);//绔嬪嵆鏇存柊TEC DAC8
extern void UPDAC9(void);//绔嬪嵆鏇存柊TEC DAC9
extern void UPDAC10(void);//绔嬪嵆鏇存柊TEC DAC10
extern void UPDAC11(void);//绔嬪嵆鏇存柊TEC DAC11
extern void UPDAC12(void);//绔嬪嵆鏇存柊TEC DAC12
extern void UPDAC13(void);//绔嬪嵆鏇存柊TEC DAC13
extern void UPDAC14(void);//绔嬪嵆鏇存柊TEC DAC14
extern void UPDAC15(void);//绔嬪嵆鏇存柊TEC DAC15
extern void UPDAC16(void);//绔嬪嵆鏇存柊650 DAC16
extern void UPDAC17(void);//绔嬪嵆鏇磋532 DAC17
extern void CLDAC(void);//绔嬪嵆娓呯┖鍏ㄩ儴DAC
extern void IMDIO(void) ;//绔嬪嵆鏇存柊IO鐐圭姸鎬佸惈杈撳叆杈撳嚭
extern void NVSAVE(void);//寮哄埗绔嬪嵆鏇存柊NVRAM
extern void NVFSAVE(void);//NVRAM鍏ㄩ儴鍐欏叆EPROM
extern void NVLOAD(void);
extern void FDSAV(void);
extern void FDLAD(void);
extern void FDSAV_ONE(int16_t cn);
extern void FDLAD_ONE(int16_t cn);
extern void PRTM(uint16_t adr, uint8_t len);
extern void LINKS(void);//浠庢満鎺ユ敹
extern void LINKM(void);//涓绘満鍙戦€?
extern void EDLAR(void);//鍋滄鍙戝皠鑴夊啿
extern void STLAR(void);//寮€濮嬪彂灏勮剦鍐?
extern void sPlcTimerInit(void);//硬件sTimer计时器初始化
extern void sPlcPortInit(void);//sPlcPort端口驱动初始化(ADC/IO/DAC)
extern void sPlcInputRefresh(void);//读取X口输入
extern void sPlcAdcProcessBuffer(void);//ADC 更新NVRAM
extern void sPlcInputInit(void);//IO输入滤波器初始化
extern void sPlcOutputInit(void);//IO输出初始化
extern void sPlcAdcInit(void);//ADC模块初始化
extern void sPlcDacInit(void);//DAC初始化
extern void sPlcOutputRefresh(void);//更新Y口输出
extern void setFanSpeed(FAN_CHANNLE_ENMU ch, int16_t speed);//设置风扇转速
extern uint8_t hdc1080_init(void);//初始化HDC1080
extern void hdc1080_read(int16_t *temp, int16_t *humi);//读取温湿度数据
/*****************************************************************************/
#ifdef __cplusplus
}
#endif
#endif
