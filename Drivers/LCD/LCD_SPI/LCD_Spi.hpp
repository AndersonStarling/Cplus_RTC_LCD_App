class LCD_Spi_Object
{
    private:
        std::uint8_t data_1;
        std::uint8_t data_2;
        bool send_cmd(std::uint8_t command);
        bool send_data(std::uint8_t data);

    public:
        LCD_Spi_Object();
        LCD_Spi_Object(std::uint8_t data_1, std::uint8_t data_2);
        ~LCD_Spi_Object();
        virtual void init(void);
        virtual void print_string(std::string string);
        virtual LCD_TYPES::LCD_Types_enum_t get_lcd_type(void);
};



