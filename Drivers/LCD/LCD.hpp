class LCD : public LCD_I2c_Object, public LCD_Spi_Object
{
    public:
        LCD();
        ~LCD();

    void init(void);
    void print_string(std::string string);
    LCD_TYPES::LCD_Types_enum_t get_lcd_type(void);
};



