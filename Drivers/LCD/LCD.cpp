#include <cstdint>
#include <cstring>
#include <string>
#include "LCD_I2c.hpp"
#include "LCD.hpp"

namespace LCD_RETURN_CODE
{
    constexpr INVALID_METHOD = 0xff;
};

void LCD::init(void)
{
    return LCD_RETURN_CODE::INVALID_METHOD;
}

void LCD::print(std::string string)
{
    return LCD_RETURN_CODE::INVALID_METHOD;
}








