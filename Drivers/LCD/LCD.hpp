class LCD : public LCD_I2c_Object
{
    public:
        virtual void init(void);
        virtual void print(std::string string);
};



