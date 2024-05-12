class LCD : public LCD_I2c_Object
{
    public:
        LCD();
        ~LCD();
    
    void init(void);
    void print_string(std::string string);
};



