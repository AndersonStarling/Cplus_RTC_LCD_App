class LCD_I2c_Object
{
    private:
        HAL_StatusTypeDef i2c_status;
        bool lcd_status;
        I2C_HandleTypeDef hi2c;
        std::uint16_t lcd_i2c_address;

        bool send_cmd(std::uint8_t command);
        bool send_data(std::uint8_t data);

    public:
        LCD_I2c_Object();
        LCD_I2c_Object(HAL_StatusTypeDef i2c_status, bool lcd_status, I2C_HandleTypeDef hi2c, std::uint16_t lcd_i2c_address);
        ~LCD_I2c_Object();
        virtual void init(void);
        virtual void print_string(std::string string);
        LCD_TYPES::LCD_Types_enum_t get_lcd_type(void);
};



