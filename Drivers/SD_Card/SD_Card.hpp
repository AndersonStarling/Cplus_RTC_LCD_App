#ifndef SD_CARD_HPP
#define SD_CARD_HPP

class SD_Object
{
    private:
        HAL_StatusTypeDef SD_status;
    public:
        SD_Object();
        ~SD_Object();
        void init(void);
        void write(std::uint32_t address, std::uint8_t * Data, std::uint32_t length);
        void read(std::uint32_t address, std::uint8_t * Data, std::uint32_t length);
        void erase(std::uint32_t address, std::uint32_t length);
}


#endif /* SD_CARD_HPP */





