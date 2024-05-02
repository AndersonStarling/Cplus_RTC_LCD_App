#include <cstdint>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_rtc.h"
#include "RTC.hpp"

RTC_Object::RTC_Object(/* args */)
{

}

RTC_Object::~RTC_Object()
{

}

void RTC_Object::init(RTC_Object &self)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};
    HAL_StatusTypeDef rtc_status;

    /** Initialize RTC Only */
    self.hrtc.Instance = RTC;
    self.hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    self.hrtc.Init.AsynchPrediv = 127;
    self.hrtc.Init.SynchPrediv = 255;
    self.hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    self.hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    self.hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    rtc_status = HAL_RTC_Init(&self.hrtc);
    while(rtc_status != HAL_OK);
  
    /** Initialize RTC and set the Time and Date */
    sTime.Hours = 0x20;
    sTime.Minutes = 0x25;
    sTime.Seconds = 0x18;
    sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sTime.StoreOperation = RTC_STOREOPERATION_RESET;
    rtc_status = HAL_RTC_SetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
    while(rtc_status != HAL_OK);
  
    sDate.WeekDay = RTC_WEEKDAY_THURSDAY;
    sDate.Month = RTC_MONTH_MAY;
    sDate.Date = 0x2;
    sDate.Year = 0x0;
    rtc_status = HAL_RTC_SetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
    while(rtc_status != HAL_OK);

}

/* Day in year */
void RTC_Object::get_day(RTC_Object &self)
{
    HAL_StatusTypeDef rtc_status;
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    rtc_status = HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
    HAL_RTC_GetTime(&self.hrtc, &sTime, self.hrtc.Init.HourFormat);
    while(rtc_status != HAL_OK);

    self.day = sDate.Date;
}

void RTC_Object::get_month(RTC_Object &self)
{
    HAL_StatusTypeDef rtc_status;
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    rtc_status = HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
    HAL_RTC_GetTime(&self.hrtc, &sTime, self.hrtc.Init.HourFormat);
    while(rtc_status != HAL_OK);

    self.month = sDate.Month;
}

void RTC_Object::get_year(RTC_Object &self)
{
    HAL_StatusTypeDef rtc_status;
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    rtc_status = HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
    HAL_RTC_GetTime(&self.hrtc, &sTime, self.hrtc.Init.HourFormat);
    while(rtc_status != HAL_OK);

    self.year = sDate.Year;
}

/* Hour in day */
void RTC_Object::get_second(RTC_Object &self)
{
    HAL_StatusTypeDef rtc_status;
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    rtc_status = HAL_RTC_GetTime(&self.hrtc, &sTime, self.hrtc.Init.HourFormat);
    HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
    while(rtc_status != HAL_OK);

    self.second = sTime.Seconds;

}

void RTC_Object::get_minute(RTC_Object &self)
{
    HAL_StatusTypeDef rtc_status;
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    rtc_status = HAL_RTC_GetTime(&self.hrtc, &sTime, self.hrtc.Init.HourFormat);
    HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
    while(rtc_status != HAL_OK);

    self.minute = sTime.Minutes;
}

void RTC_Object::get_hour(RTC_Object &self)
{
    HAL_StatusTypeDef rtc_status;
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    rtc_status = HAL_RTC_GetTime(&self.hrtc, &sTime, self.hrtc.Init.HourFormat);
    HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
    while(rtc_status != HAL_OK);

    self.hour = sTime.Hours;
}
