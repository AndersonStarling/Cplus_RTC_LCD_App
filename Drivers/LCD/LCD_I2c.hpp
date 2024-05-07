class LCD_Object
{
    private:
        HAL_StatusTypeDef i2c_status;
        bool lcd_status;
        I2C_HandleTypeDef hi2c;
        std::uint16_t lcd_i2c_address;

        bool send_cmd(LCD_Object &self, std::uint8_t command);
        bool send_data(LCD_Object &self, std::uint8_t data);

    public:
        LCD_Object(HAL_StatusTypeDef i2c_status, bool lcd_status, I2C_HandleTypeDef hi2c, std::uint16_t lcd_i2c_address);
        ~LCD_Object();
        void init(LCD_Object &self);
        void print_string(LCD_Object &self, std::string string);
};



