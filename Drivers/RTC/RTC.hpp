
class RTC_Object
{
private:
    /* data */
    std::uint8_t day;
    std::uint8_t month;
    std::uint8_t year;

    std::uint8_t second;
    std::uint8_t minute;
    std::uint8_t hour;

    RTC_HandleTypeDef hrtc;
    HAL_StatusTypeDef rtc_status;

public:
    RTC_Object(/* args */);
    ~RTC_Object();

    void init(RTC_Object &self);

    /* Day in year */
    std::uint8_t get_day(RTC_Object &self);
    std::uint8_t get_month(RTC_Object &self);
    std::uint8_t get_year(RTC_Object &self);
    void set_day(RTC_Object &self, std::uint8_t day);
    void set_month(RTC_Object &self, std::uint8_t month);
    void set_year(RTC_Object &self, std::uint8_t year);

    /* Hour in day */
    std::uint8_t get_second(RTC_Object &self);
    std::uint8_t get_minute(RTC_Object &self);
    std::uint8_t get_hour(RTC_Object &self);
    void set_second(RTC_Object &self, std::uint8_t second);
    void set_minute(RTC_Object &self, std::uint8_t minute);
    void set_hour(RTC_Object &self, std::uint8_t hour);
};








