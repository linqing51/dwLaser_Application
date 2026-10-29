/*----------------------------------------------------------------------------
 * 文件编码约定: 本文件为 UTF-8 编码(带BOM)。
 * 本工程源码统一使用 UTF-8(带BOM) 保存: 新建或修改任何源文件时,
 * 请以 UTF-8 编码保存, 并在文件头保留本注释。
 *----------------------------------------------------------------------------*/
#include "rtc.h"
#include "stdio.h"
#include "sPlc.h"
#include "..\config\myConfig.h"
/*****************************************************************************/
// 自定义魔术标记值: 用于检测RTC/BKSRAM备份域是否掉电
#define RTC_VALID_FLAG    0x52544346U   // "RTCF"
// 选用RTC备份寄存器 19 存储RTC有效标志
#define RTC_FLAG_BKP_REG  RTC_BKP_DR19
// STM32F4的RTC备份寄存器在结构体中为BKP0R~BKP19R独立成员(没有BKPxR数组),
// 按BKP0R基址+4*索引访问(idx取值RTC_BKP_DR0~RTC_BKP_DR19)
#define RTC_BKP_REG(idx)  (*(__IO uint32_t *)((uint32_t)&(RTC->BKP0R) + (((uint32_t)(idx)) << 2)))

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;
/*****************************************************************************/
//内部工具: 根据公历日期计算星期(蔡勒公式) 返回 1=周一 ... 7=周日
static uint8_t RtcCalcWeekDay(uint16_t year, uint8_t month, uint8_t day){
	uint16_t y;
	uint8_t m, w;
	if(month < 3){
		y = year - 1;
		m = month + 12;
	}
	else{
		y = year;
		m = month;
	}
	w = (uint8_t)((day + 13 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7);
	//w: 0=周六,1=周日,2=周一,3=周二,4=周三,5=周四,6=周五
	static const uint8_t wkTab[7] = {7, 1, 2, 3, 4, 5, 6};
	return wkTab[w];
}
/*****************************************************************************/
//内部工具: 校验年月日为合法自然日期,返回1合法
static uint8_t RtcCheckDate(uint16_t year, uint8_t month, uint8_t day){
	uint8_t monthDays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	if((year < 2000) || (year > 2099)){
		return 0;
	}
	if((month < 1) || (month > 12)){
		return 0;
	}
	//闰年2月
	if(month == 2){
		if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)){
			if(day > 29){
				return 0;
			}
			return 1;
		}
	}
	if(day > monthDays[month - 1]){
		return 0;
	}
	return 1;
}
/*****************************************************************************/
void RtcInitTimeDefault(void){//设置默认时间(仅首次上电/备份域掉电时调用)
	sTime.Hours          	= 12;
  sTime.Minutes        	= 0;
  sTime.Seconds        	= 0;
  sTime.DayLightSaving 	= RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation 	= RTC_STOREOPERATION_RESET;
  HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);

  sDate.Year   					= 26;    // 2026
  sDate.Month  					= 4;
  sDate.Date   					= 23;
  sDate.WeekDay					= RTC_WEEKDAY_THURSDAY;
  HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
}

void RtcCheckAndInit(void){//RTC掉电检测与防锁死初始化
	//1.使能PWR时钟
	__HAL_RCC_PWR_CLK_ENABLE();
	//2.解除备份域写保护(RTC寄存器/备份寄存器/BKSRAM可访问)
	HAL_PWR_EnableBkUpAccess();
	//3.使能BKPSRAM接口时钟(BK 2K区块映射硬件BKSRAM 4K使用)
	__HAL_RCC_BKPSRAM_CLK_ENABLE();
	//4.确保RTC APB接口时钟已使能(兼容在MX_RTC_Init之前调用RtcCheckAndInit的情况)
	__HAL_RCC_RTC_ENABLE();
	//5.掉电检测:备份寄存器魔法字有效 -> RTC已在走时且备份域未掉电,
	//  必须跳过重复初始化,否则会卡在RTC寄存器同步等待导致模块锁死,并清零已有时间
	//  (直接访问RTC备份寄存器,不依赖hrtc句柄,兼容MX_RTC_Init之前调用)
	if(READ_REG(RTC_BKP_REG(RTC_FLAG_BKP_REG)) == RTC_VALID_FLAG){
#if (CONFIG_DEBUG_RTC == 1)
		printf("%s,%d,%s:RTC already initialized, skip init(anti-lock)\n",__FILE__, __LINE__, __func__);
#endif
		return;
	}
	//6.首次上电或电池掉电(备份域被清空):重新初始化RTC并写入有效标志
	//  若RTC句柄尚未初始化(在MX_RTC_Init之前调用),交由后续MX_RTC_Init完成初始化
	if(hrtc.Instance == 0){
#if (CONFIG_DEBUG_RTC == 1)
		printf("%s,%d,%s:RTC handle not ready, init deferred to MX_RTC_Init\n",__FILE__, __LINE__, __func__);
#endif
		return;
	}
	RtcInitTimeDefault();
	WRITE_REG(RTC_BKP_REG(RTC_FLAG_BKP_REG), RTC_VALID_FLAG);
#if (CONFIG_DEBUG_RTC == 1)
	printf("%s,%d,%s:RTC first init(default time set)\n",__FILE__, __LINE__, __func__);
#endif
}

void RtcGetNowTime(uint8_t *year,uint8_t *mon,uint8_t *day, uint8_t *hour,uint8_t *min,uint8_t *sec){//获取当前时间可循环调用(兼容接口:year为后两位)
	uint16_t y;
	RtcGetDateTime(&y, mon, day, hour, min, sec);
	if(year){
		*year = (uint8_t)(y - 2000);
	}
}

void RtcGetDateTime(uint16_t *year, uint8_t *mon, uint8_t *day, uint8_t *hour, uint8_t *min, uint8_t *sec){//获取当前时间 常规自然输入(year完整4位数)
	// 规范：必须先读Time，再读Date
	HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	if(year){	*year = (uint16_t)(sDate.Year + 2000);}
	if(mon){	*mon  = sDate.Month;}
	if(day){	*day  = sDate.Date;}
	if(hour){	*hour = sTime.Hours;}
	if(min){	*min  = sTime.Minutes;}
	if(sec){	*sec  = sTime.Seconds;}
}

// 功能：设置 RTC 日期和时间(常规年月日自然输入)
// 输入：year 完整4位数(如2026)、month 1-12、day 1-31、hour 0-23、min 0-59、sec 0-59
// 返回：1成功, 0参数非法或写入失败
uint8_t RtcSetDateTime(uint16_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec){
	//1.常规自然输入范围校验
	if(RtcCheckDate(year, month, day) == 0){
#if (CONFIG_DEBUG_RTC == 1)
		printf("%s,%d,%s:invalid date Y:%d M:%d D:%d\n",__FILE__, __LINE__, __func__, year, month, day);
#endif
		return 0;
	}
	if((hour > 23) || (min > 59) || (sec > 59)){
#if (CONFIG_DEBUG_RTC == 1)
		printf("%s,%d,%s:invalid time H:%d M:%d S:%d\n",__FILE__, __LINE__, __func__, hour, min, sec);
#endif
		return 0;
	}
	//2.解除备份域写保护(RTC写入必须)
	__HAL_RCC_PWR_CLK_ENABLE();
	HAL_PWR_EnableBkUpAccess();
	//3.设置时间(RTC句柄防御:确保已绑定RTC外设)
	if(hrtc.Instance == 0){
		hrtc.Instance = RTC;
	}
	sTime.Hours = hour;
	sTime.Minutes = min;
	sTime.Seconds = sec;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;
	if(HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK){
		return 0;
	}
	//4.设置日期(星期自动计算)
	sDate.Year = (uint8_t)(year - 2000);     // 完整年份转RTC后两位
	sDate.Month = month;
	sDate.Date = day;
	sDate.WeekDay = RtcCalcWeekDay(year, month, day);
	if(HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK){
		return 0;
	}
	//5.写RTC有效标志,下次上电(备份域未掉电)不再重复初始化
	WRITE_REG(RTC_BKP_REG(RTC_FLAG_BKP_REG), RTC_VALID_FLAG);
#if (CONFIG_DEBUG_RTC == 1)
	printf("%s,%d,%s:Set RTC YYYY-MM-DD:%d-%d-%d,HH-MM-SS:%d-%d-%d\n", __FILE__, __LINE__, __func__, year, month, day, hour, min, sec);
#endif
	return 1;
}

// 功能：设置 RTC 日期和时间(兼容接口:year为后两位)
void RtcSetTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec){
	RtcSetDateTime((uint16_t)year + 2000, month, day, hour, min, sec);
}

void RtcSetYear(uint8_t tmp){
	uint16_t year;
	uint8_t mon, date, hour, min, sec;
	if(tmp >= 99){
		tmp = 99;
	}
	RtcGetDateTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetDateTime((uint16_t)tmp + 2000, mon, date, hour, min, sec);
}

void RtcSetMonth(uint8_t tmp){
	uint16_t year;
	uint8_t mon, date, hour, min, sec;
	if(tmp >= 12){
		tmp = 12;
	}
	RtcGetDateTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetDateTime(year, tmp, date, hour, min, sec);
}

void RtcSetDate(uint8_t tmp){
	uint16_t year;
	uint8_t mon, date, hour, min, sec;
	if(tmp >= 31){
		tmp = 31;
	}
	RtcGetDateTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetDateTime(year, mon, tmp, hour, min, sec);
}

void RtcSetHours(uint8_t tmp){
	uint16_t year;
	uint8_t mon, date, hour, min, sec;
	if(tmp >= 24){
		tmp = 23;
	}
	RtcGetDateTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetDateTime(year, mon, date, tmp, min, sec);
}

void RtcSetMinutes(uint8_t tmp){
	uint16_t year;
	uint8_t mon, date, hour, min, sec;
	if(tmp >= 60){
		tmp = 59;
	}
	RtcGetDateTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetDateTime(year, mon, date, hour, tmp, sec);
}

void RtcSetSeconds(uint8_t tmp){
	uint16_t year;
	uint8_t mon, date, hour, min, sec;
	if(tmp >= 60){
		tmp = 59;
	}
	RtcGetDateTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetDateTime(year, mon, date, hour, min, tmp);
}
