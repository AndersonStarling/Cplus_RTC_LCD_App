class LCD_Object
{
    private:
 
    public:
        LCD_Object();
        ~LCD_Object();
        void init(LCD_Object &self);
        void print(LCD_Object &self, std::string &string);
};



