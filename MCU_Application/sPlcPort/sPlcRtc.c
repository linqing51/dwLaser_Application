#include "rtc.h"
#include "stdio.h"
#include "sPlc.h"
#include "BoardConfig.h"
/*****************************************************************************/
// 自定义魔术标记值
#define RTC_VALID_FLAG    0x52544346U   // "RTCF"
// 选用RTC备份寄存器 0
#define RTC_FLAG_BKP_REG  RTC_BKP_DR19

RTC_TimeTypeDef sTime;
RTC_DateTypeDef sDate;

void RtcInitTimeDefault(void){
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

void RtcCheckAndInit(void){
  // 1. 开启后备域时钟，解除写保护
  __HAL_RCC_PWR_CLK_ENABLE();
	printf("%s,%d,%s:BKP DR0:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0));
	printf("%s,%d,%s:BKP DR1:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1));
	printf("%s,%d,%s:BKP DR2:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2));
	printf("%s,%d,%s:BKP DR3:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3));
	printf("%s,%d,%s:BKP DR4:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4));
	printf("%s,%d,%s:BKP DR5:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5));
	printf("%s,%d,%s:BKP DR6:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR6));
	printf("%s,%d,%s:BKP DR7:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR7));
	printf("%s,%d,%s:BKP DR8:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR8));
	printf("%s,%d,%s:BKP DR9:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR9));
	printf("%s,%d,%s:BKP DR10:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR10));
	printf("%s,%d,%s:BKP DR11:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR11));
	printf("%s,%d,%s:BKP DR12:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR12));
	printf("%s,%d,%s:BKP DR13:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR13));
	printf("%s,%d,%s:BKP DR14:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR14));
	printf("%s,%d,%s:BKP DR15:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR15));
	printf("%s,%d,%s:BKP DR16:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR16));
	printf("%s,%d,%s:BKP DR17:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR17));
	printf("%s,%d,%s:BKP DR18:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR18));
	printf("%s,%d,%s:BKP DR19:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR19));
  // 2. 判断备份寄存器标记
  if(HAL_RTCEx_BKUPRead(&hrtc, RTC_FLAG_BKP_REG) != RTC_VALID_FLAG){
    // 首次上电 / 电池没电丢失备份 → 设置初始时间
#if (CONFIG_DEBUG_RTC == 1)
    printf("%s,%d,%s:Check BKSRAM fail,reInit RTC\n", __FILE__, __LINE__, __func__);
#endif
		HAL_PWR_EnableBkUpAccess();	
		RtcInitTimeDefault();
    // 写入有效标记，下次不再重置
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_FLAG_BKP_REG, RTC_VALID_FLAG);
		HAL_PWR_DisableBkUpAccess();
		printf("%s,%d,%s:BKP DR0:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR0));
		printf("%s,%d,%s:BKP DR1:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR1));
		printf("%s,%d,%s:BKP DR2:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR2));
		printf("%s,%d,%s:BKP DR3:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR3));
		printf("%s,%d,%s:BKP DR4:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR4));
		printf("%s,%d,%s:BKP DR5:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR5));
		printf("%s,%d,%s:BKP DR6:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR6));
		printf("%s,%d,%s:BKP DR7:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR7));
		printf("%s,%d,%s:BKP DR8:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR8));
		printf("%s,%d,%s:BKP DR9:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR9));
		printf("%s,%d,%s:BKP DR10:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR10));
		printf("%s,%d,%s:BKP DR11:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR11));
		printf("%s,%d,%s:BKP DR12:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR12));
		printf("%s,%d,%s:BKP DR13:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR13));
		printf("%s,%d,%s:BKP DR14:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR14));
		printf("%s,%d,%s:BKP DR15:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR15));
		printf("%s,%d,%s:BKP DR16:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR16));
		printf("%s,%d,%s:BKP DR17:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR17));
		printf("%s,%d,%s:BKP DR18:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR18));
		printf("%s,%d,%s:BKP DR19:05%d\n", __FILE__, __LINE__, __func__, HAL_RTCEx_BKUPRead(&hrtc, RTC_BKP_DR19));		
  }
	else{
#if (CONFIG_DEBUG_RTC == 1)
	printf("%s,%d,%s:Check BKSRAM pass\n", __FILE__, __LINE__, __func__);
#endif
		}
  // 否则：直接沿用RTC现有时间，不操作
}

void RtcGetNowTime(uint8_t *year,uint8_t *mon,uint8_t *day, uint8_t *hour,uint8_t *min,uint8_t *sec){//获取当前时间可循环调用
  // 规范：必须先读Time，再读Date
  HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
  *year = sDate.Year;
  *mon  = sDate.Month;
  *day  = sDate.Date;
  *hour = sTime.Hours;
  *min  = sTime.Minutes;
  *sec  = sTime.Seconds;
}

// 功能：设置 RTC 日期和时间
// 输入：年(后两位)、月、日、时、分、秒、星期
void RtcSetTime(uint8_t year, uint8_t month, uint8_t day, uint8_t hour, uint8_t min, uint8_t sec){
	HAL_PWR_EnableBkUpAccess();	
	RTC_TimeTypeDef sTime = {0};
	RTC_DateTypeDef sDate = {0};
	// 1. 设置时间
	sTime.Hours = hour;
	sTime.Minutes = min;
	sTime.Seconds = sec;
	sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	sTime.StoreOperation = RTC_STOREOPERATION_RESET;

	HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
	// 2. 设置日期
	sDate.Year = year;     // 只填后两位，如 25 代表 2025
	sDate.Month = month;
	sDate.Date = day;
	HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
	HAL_PWR_DisableBkUpAccess();	
#if (CONFIG_DEBUG_RTC == 1)
	printf("%s,%d,%s:Get RTC YY-MM-DD:%d-%d-%d,HH-MM-SS:%d-%d-%d\n", __FILE__, __LINE__, __func__, year, month, day, hour, min, sec);
#endif
}

void RtcSetYear(uint8_t tmp){
	uint8_t year, mon, date, hour, min, sec;
	if(tmp >= 99){
		tmp = 99;
	}
	RtcGetNowTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetTime(tmp, mon, date, hour, min, sec);
}

void RtcSetMonth(uint8_t tmp){
	uint8_t year, mon, date, hour, min, sec;
	if(tmp >= 12){
		tmp = 12;
	}
	RtcGetNowTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetTime(year, tmp, date, hour, min, sec);
}

void RtcSetDate(uint8_t tmp){
	uint8_t year, mon, date, hour, min, sec;
	if(tmp >= 31){
		tmp = 31;
	}
	RtcGetNowTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetTime(year, mon, tmp, hour, min, sec);
}

void RtcSetHours(uint8_t tmp){
	uint8_t year, mon, date, hour, min, sec;
	if(tmp >= 31){
		tmp = 31;
	}
	RtcGetNowTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetTime(year, mon, date, tmp, min, sec);
}

void RtcSetMinutes(uint8_t tmp){
	uint8_t year, mon, date, hour, min, sec;
	if(tmp >= 60){
		tmp = 60;
	}
	RtcGetNowTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetTime(year, mon, date, hour, tmp, sec);
}

void RtcSetSeconds(uint8_t tmp){
	uint8_t year, mon, date, hour, min, sec;
	if(tmp >= 60){
		tmp = 60;
	}
	RtcGetNowTime(&year, &mon, &date, &hour, &min, &sec);
	RtcSetTime(year, mon, date, hour, min, tmp);
}

