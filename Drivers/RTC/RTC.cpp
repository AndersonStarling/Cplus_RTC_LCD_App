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

    /** Initialize RTC Only */
    self.hrtc.Instance = RTC;
    self.hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
    self.hrtc.Init.AsynchPrediv = 127;
    self.hrtc.Init.SynchPrediv = 255;
    self.hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
    self.hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
    self.hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
    self.rtc_status = HAL_RTC_Init(&self.hrtc);
}

/* Day in year */
void RTC_Object::get_day(RTC_Object &self)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    HAL_RTC_GetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
    self.rtc_status = HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);

    self.day = sDate.Date;
}

void RTC_Object::get_month(RTC_Object &self)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    HAL_RTC_GetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
    self.rtc_status = HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);

    self.month = sDate.Month;
}

void RTC_Object::get_year(RTC_Object &self)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    HAL_RTC_GetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
    self.rtc_status = HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);

    self.year = sDate.Year;
}

/* Hour in day */
void RTC_Object::get_second(RTC_Object &self)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    self.rtc_status = HAL_RTC_GetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);

    self.second = sTime.Seconds;

}

void RTC_Object::get_minute(RTC_Object &self)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    self.rtc_status = HAL_RTC_GetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
    while(rtc_status != HAL_OK);

    self.minute = sTime.Minutes;
}

void RTC_Object::get_hour(RTC_Object &self)
{
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    while(HAL_OK != HAL_RTC_WaitForSynchro(&self.hrtc));

    self.rtc_status = HAL_RTC_GetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
    HAL_RTC_GetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
    while(rtc_status != HAL_OK);

    self.hour = sTime.Hours;
}

void RTC_Object::set_day(RTC_Object &self, std::uint8_t day)
{
    HAL_StatusTypeDef rtc_status;
    RTC_DateTypeDef sDate = {0};

    self.day = day;
    sDate.Date  = self.day;
    sDate.Month = self.month;
    sDate.Year  = self.year;

    self.rtc_status = HAL_RTC_SetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
}

void RTC_Object::set_month(RTC_Object &self, std::uint8_t month)
{
    HAL_StatusTypeDef rtc_status;
    RTC_DateTypeDef sDate = {0};

    self.month = month;
    sDate.Date  = self.day;
    sDate.Month = self.month;
    sDate.Year  = self.year;

    self.rtc_status = HAL_RTC_SetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
}

void RTC_Object::set_year(RTC_Object &self, std::uint8_t year)
{
    HAL_StatusTypeDef rtc_status;
    RTC_DateTypeDef sDate = {0};

    self.year = year;
    sDate.Date  = self.day;
    sDate.Month = self.month;
    sDate.Year  = self.year;

    self.rtc_status = HAL_RTC_SetDate(&self.hrtc, &sDate, RTC_FORMAT_BCD);
}

void RTC_Object::set_second(RTC_Object &self, std::uint8_t second)
{
    HAL_StatusTypeDef rtc_status;
    RTC_TimeTypeDef sTime;

    self.second = second;
    sTime.Seconds = self.second;
    sTime.Minutes = self.minute;
    sTime.Hours   = self.hour;

    self.rtc_status = HAL_RTC_SetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
}

void RTC_Object::set_minute(RTC_Object &self, std::uint8_t minute)
{
    HAL_StatusTypeDef rtc_status;
    RTC_TimeTypeDef sTime;

    self.minute = minute;
    sTime.Seconds = self.second;
    sTime.Minutes = self.minute;
    sTime.Hours   = self.hour;

    self.rtc_status = HAL_RTC_SetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
}

void RTC_Object::set_hour(RTC_Object &self, std::uint8_t hour)
{
    HAL_StatusTypeDef rtc_status;
    RTC_TimeTypeDef sTime;

    self.hour = hour;
    sTime.Seconds = self.second;
    sTime.Minutes = self.minute;
    sTime.Hours   = self.hour;

    self.rtc_status = HAL_RTC_SetTime(&self.hrtc, &sTime, RTC_FORMAT_BCD);
}
