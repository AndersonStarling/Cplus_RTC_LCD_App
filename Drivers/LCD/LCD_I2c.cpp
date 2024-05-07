#include <cstdint>
#include <cstring>
#include <string>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_i2c.h"
#include "LCD_I2c.hpp"

/* LCD namespace */
namespace LCD
{
    /* LCD Pin */
    std::uint8_t constexpr PIN_0 = (1u << 0);
    std::uint8_t constexpr PIN_1 = (1u << 1);
    std::uint8_t constexpr PIN_2 = (1u << 2);
    std::uint8_t constexpr PIN_3 = (1u << 3);
    std::uint8_t constexpr PIN_4 = (1u << 4);
    std::uint8_t constexpr PIN_5 = (1u << 5);
    std::uint8_t constexpr PIN_6 = (1u << 6);
    std::uint8_t constexpr PIN_7 = (1u << 7);

    std::uint8_t constexpr RS  = PIN_0;
    std::uint8_t constexpr RW  = PIN_1;
    std::uint8_t constexpr E   = PIN_2;
    std::uint8_t constexpr BLK = PIN_3;
    std::uint8_t constexpr D4  = PIN_4;
    std::uint8_t constexpr D5  = PIN_5;
    std::uint8_t constexpr D6  = PIN_6;
    std::uint8_t constexpr D7  = PIN_7;
}

/* Private method */
bool LCD_Object::send_cmd(LCD_Object &self, std::uint8_t command)
{
    std::uint8_t data_upper = 0;
    std::uint8_t data_lower = 0;
    std::uint8_t data_send[4] = {0};

    /* extract 4 upper bit from command */
    data_upper = ((command & 0xF0) & (~LCD::RW));
    /*extract 4 lower bit from command */
    data_lower = (((command << 4) & 0xF0) & (~LCD::RW));

    /* Send 4 upper bit command to lcd */
    data_send[0] = data_upper | (LCD::BLK | LCD::E);
    /* Create dummy frame because LCD need delay between two intructions */
    data_send[1] = data_upper | (LCD::BLK);

    /* Send 4 upper bit command to lcd */
    data_send[2] = data_lower | (LCD::BLK | LCD::E);
    /* Create dummy frame because LCD need delay between two intructions */
    data_send[3] = data_lower | (LCD::BLK);

    self.i2c_status = HAL_I2C_Master_Transmit(&self.hi2c, ((self.lcd_i2c_address << 1) | 1), &data_send[0], 4, 0xffff);

    return (self.i2c_status == HAL_OK);
}

bool LCD_Object::send_data(LCD_Object &self, std::uint8_t data)
{
    std::uint8_t data_upper = 0;
    std::uint8_t data_lower = 0;
    std::uint8_t data_send[4] = {0};

    /* extract 4 upper bit from command */
    data_upper = ((data & 0xF0) & (~LCD::RW));
    /*extract 4 lower bit from command */
    data_lower = (((data << 4) & 0xF0) & (~LCD::RW));

    /* Send 4 upper bit command to lcd */
    data_send[0] = data_upper | (LCD::BLK | LCD::E | LCD::RS);
    /* Create dummy frame because LCD need delay between two intructions */
    data_send[1] = data_upper | (LCD::BLK | LCD::RS);

    /* Send 4 upper bit command to lcd */
    data_send[2] = data_lower | (LCD::BLK | LCD::E | LCD::RS);
    /* Create dummy frame because LCD need delay between two intructions */
    data_send[3] = data_lower | (LCD::BLK | LCD::RS);

    self.i2c_status = HAL_I2C_Master_Transmit(&self.hi2c, ((self.lcd_i2c_address << 1) | 1), &data_send[0], 4, 0xffff);

    return (self.i2c_status == HAL_OK);
}

/* Public method */
LCD_Object::LCD_Object(HAL_StatusTypeDef i2c_status, bool lcd_status, I2C_HandleTypeDef hi2c, std::uint16_t lcd_i2c_address)
{
    this->i2c_status = i2c_status;
    this->lcd_status = lcd_status;
    this->hi2c = hi2c;
    this->lcd_i2c_address = lcd_i2c_address;
}

LCD_Object::~LCD_Object()
{
    this->i2c_status = HAL_ERROR;
    this->lcd_status = false;
    this->lcd_i2c_address = 0;
}


void LCD_Object::init(LCD_Object &self)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Init Gpio as I2c functionality */
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_RCC_I2C1_CLK_ENABLE();

    /* Init I2c */
    self.hi2c.Instance = I2C1;
    self.hi2c.Init.ClockSpeed = 100000;
    self.hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    self.hi2c.Init.OwnAddress1 = 0;
    self.hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    self.hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    self.hi2c.Init.OwnAddress2 = 0;
    self.hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    self.hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
     self.i2c_status = HAL_I2C_Init(&self.hi2c);

    /* Init LCD */
    HAL_Delay(50);
    self.lcd_status = LCD_Object::send_cmd(self, 0x30);
    HAL_Delay(5);
    self.lcd_status = LCD_Object::send_cmd(self, 0x30);
    HAL_Delay(1);
    self.lcd_status = LCD_Object::send_cmd(self, 0x30);
    HAL_Delay(10);
    self.lcd_status = LCD_Object::send_cmd(self, 0x20);
    HAL_Delay(10);
    self.lcd_status = LCD_Object::send_cmd(self, 0x28);
    HAL_Delay(1);
    self.lcd_status = LCD_Object::send_cmd(self, 0x08);
    HAL_Delay(1);
    self.lcd_status = LCD_Object::send_cmd(self, 0x01);
    HAL_Delay(2);
    self.lcd_status = LCD_Object::send_cmd(self, 0x06);
    HAL_Delay(1);
    self.lcd_status = LCD_Object::send_cmd(self, 0x0C);

}

void LCD_Object::print_string(LCD_Object &self, std::string string)
{
    std::uint32_t index = 0;

    for(index = 0; index < string.length(); index ++)
    {
        self.lcd_status = LCD_Object::send_data(self, (std::uint8_t)string[index]);
    }
}














