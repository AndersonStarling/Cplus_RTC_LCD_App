
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

public:
    RTC_Object(/* args */);
    ~RTC_Object();

    void init(RTC_Object &self);

    /* Day in year */
    void get_day(RTC_Object &self);
    void get_month(RTC_Object &self);
    void get_year(RTC_Object &self);

    /* Hour in day */
    void get_second(RTC_Object &self);
    void get_minute(RTC_Object &self);
    void get_hour(RTC_Object &self);
};








