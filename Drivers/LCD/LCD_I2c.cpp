#include <cstdint>
#include <cstring>
#include <string>
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_i2c.h"
#include "LCD_I2c.hpp"

#define P0 (1u << 0)
#define P1 (1u << 1)
#define P2 (1u << 2)
#define P3 (1u << 3)
#define P4 (1u << 4)
#define P5 (1u << 5)
#define P6 (1u << 6)
#define P7 (1u << 7)

#define LCD_I2C_RS  P0
#define LCD_I2C_RW  P1
#define LCD_I2C_E   P2
#define LCD_I2C_BLK P3
#define LCD_I2C_D4  P4
#define LCD_I2C_D5  P5
#define LCD_I2C_D6  P6
#define LCD_I2C_D7  P7

/* Private method */
bool LCD_Object::send_cmd(LCD_Object &self, std::uint8_t command)
{
    std::uint8_t data_upper = 0;
    std::uint8_t data_lower = 0;
    std::uint8_t data_send[4] = {0};

    /* extract 4 upper bit from command */
    data_upper = ((command & 0xF0) & (~LCD_I2C_RW));
    /*extract 4 lower bit from command */
    data_lower = (((command << 4) & 0xF0) & (~LCD_I2C_RW));

    /* Send 4 upper bit command to lcd */
    data_send[0] = data_upper | (LCD_I2C_BLK | LCD_I2C_E);
    /* Create dummy frame because LCD need delay between two intructions */
    data_send[1] = data_upper | (LCD_I2C_BLK);

    /* Send 4 upper bit command to lcd */
    data_send[2] = data_lower | (LCD_I2C_BLK | LCD_I2C_E);
    /* Create dummy frame because LCD need delay between two intructions */
    data_send[3] = data_lower | (LCD_I2C_BLK);

    self.i2c_status = HAL_I2C_Master_Transmit(&self.hi2c1, self.lcd_i2c_address, &data_send[0], 4, 0xffff);

    return (self.i2c_status == HAL_OK);
}

bool LCD_Object::send_data(LCD_Object &self, std::uint8_t data)
{
    std::uint8_t data_upper = 0;
    std::uint8_t data_lower = 0;
    std::uint8_t data_send[4] = {0};
    std::uint8_t ret = -1;

    /* extract 4 upper bit from command */
    data_upper = ((data & 0xF0) & (~LCD_I2C_RW));
    /*extract 4 lower bit from command */
    data_lower = (((data << 4) & 0xF0) & (~LCD_I2C_RW));

    /* Send 4 upper bit command to lcd */
    data_send[0] = data_upper | (LCD_I2C_BLK | LCD_I2C_E | LCD_I2C_RS);
    /* Create dummy frame because LCD need delay between two intructions */
    data_send[1] = data_upper | (LCD_I2C_BLK | LCD_I2C_RS);

    /* Send 4 upper bit command to lcd */
    data_send[2] = data_lower | (LCD_I2C_BLK | LCD_I2C_E | LCD_I2C_RS);
    /* Create dummy frame because LCD need delay between two intructions */
    data_send[3] = data_lower | (LCD_I2C_BLK | LCD_I2C_RS);

    self.i2c_status = HAL_I2C_Master_Transmit(&self.hi2c1, self.lcd_i2c_address, &data_send[0], 4, 0xffff);
}

/* Public method */
LCD_Object::LCD_Object()
{

}

LCD_Object::~LCD_Object()
{

}


void LCD_Object::init(LCD_Object &self)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* Init Object data */
    self.i2c_status = HAL_ERROR;
    self.lcd_i2c_address = 0x27;
    self.lcd_status = false;

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
    self.hi2c1.Instance = I2C1;
    self.hi2c1.Init.ClockSpeed = 100000;
    self.hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    self.hi2c1.Init.OwnAddress1 = 0;
    self.hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    self.hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    self.hi2c1.Init.OwnAddress2 = 0;
    self.hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    self.hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
     self.i2c_status = HAL_I2C_Init(&self.hi2c1);

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
        self.lcd_status &= LCD_Object::send_data(self, (std::uint8_t)string[index]);
    }
}














