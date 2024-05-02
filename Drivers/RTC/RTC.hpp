
class RTC
{
private:
    /* data */
    std::uint8_t day;
    std::uint8_t month;
    std::uint8_t year;

    std::uint8_t second;
    std::uint8_t minute;
    std::uint8_t hour;

public:
    RTC(/* args */);
    ~RTC();

    void init(void);

    /* Day in year */
    void get_day(RTC &self);
    void get_month(RTC &self);
    void get_year(RTC &self);

    /* Hour in day */
    void get_second(RTC &self);
    void get_minute(RTC &self);
    void get_hour(RTC &self);
};

RTC::RTC(/* args */)
{
}

RTC::~RTC()
{
}








