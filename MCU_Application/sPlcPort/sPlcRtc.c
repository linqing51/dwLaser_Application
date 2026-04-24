#include "rtc.h"
#include "stdio.h"
/*****************************************************************************/
// 自定义魔术标记值
#define RTC_VALID_FLAG    0x52544346U   // "RTCF"
// 选用RTC备份寄存器 0
#define RTC_FLAG_BKP_REG  RTC_BKP_DR0

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
  HAL_PWR_EnableBkUpAccess();

  // 2. 判断备份寄存器标记
  if(HAL_RTCEx_BKUPRead(&hrtc, RTC_FLAG_BKP_REG) != RTC_VALID_FLAG){
    // 首次上电 / 电池没电丢失备份 → 设置初始时间
    RtcInitTimeDefault();
    // 写入有效标记，下次不再重置
    HAL_RTCEx_BKUPWrite(&hrtc, RTC_FLAG_BKP_REG, RTC_VALID_FLAG);
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
}

void RtcSetYear(uint8_t yy){
	uint8_t year, mon, day, hour, min, sec;
	if(yy >= 99){
		yy = 99;
	}
	RtcGetNowTime(&year, &mon, &day, &hour, &min, &sec);//获取当前时间可循环调用
	RtcSetTime(yy, mon, day, hour, min, sec);
}
