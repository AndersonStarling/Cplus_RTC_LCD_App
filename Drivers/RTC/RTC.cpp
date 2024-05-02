#include <cstdint>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_rtc.h"
#include "RTC.hpp"

void RTC_Object::init(RTC_Object &self)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    /** Initialize RTC Only */
    self.hrtc.Instance = RTC;
    self.hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    self.hrtc.Init.AsynchPrediv = 127;
    self.hrtc.Init.SynchPrediv = 255;
    self.hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    self.hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    self.hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    while(HAL_RTC_Init(&hrtc) != HAL_OK);
  
    /** Initialize RTC and set the Time and Date */
    sTime.Hours = 0x20;
    sTime.Minutes = 0x25;
    sTime.Seconds = 0x18;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    while(HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK);
  
    sDate.WeekDay = RTC_WEEKDAY_THURSDAY;
    sDate.Month = RTC_MONTH_MAY;
    sDate.Date = 0x2;
    sDate.Year = 0x0;
    while(HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK);

}

/* Day in year */
void RTC_Object::get_day(RTC &self)
{

}

void RTC_Object::get_month(RTC &self)
{

}

void RTC_Object::get_year(RTC &self)
{

}

/* Hour in day */
void RTC_Object::get_second(RTC &self)
{
    HAL_StatusTypeDef rtc_status;

    rtc_status = HAL_RTC_GetTime(RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef *sTime, uint32_t Format);
}

void RTC_Object::get_minute(RTC &self)
{

}

void RTC_Object::get_hour(RTC &self)
{
    
}
