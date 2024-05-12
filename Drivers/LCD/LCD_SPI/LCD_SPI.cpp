#include <cstdint>
#include <cstring>
#include <string>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_i2c.h"
#include "LCD_Types.hpp"
#include "LCD_Spi.hpp"

/* Private method */
bool LCD_Spi_Object::send_cmd(std::uint8_t command)
{
    return false;
}

bool LCD_Spi_Object::send_data(std::uint8_t data)
{
    return false;
}

/* Public method */
void LCD_Spi_Object::init(void)
{

}

void LCD_Spi_Object::print_string(std::string string)
{

}

LCD_TYPES::LCD_Types_enum_t get_lcd_type(void)
{
    return LCD_TYPES::LCD_SPI;
}

