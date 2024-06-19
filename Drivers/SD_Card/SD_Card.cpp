#include <cstdint>
#include "sdio.h"
#include "stm32f4xx_hal_sd.h"
#include "SD_Card.hpp"

SD_Object::SD_Object()
{

}

SD_Object::~SD_Object()
{

}

void SD_Object::init(void)
{
    this->SD_status = HAL_SD_Init(&hsd);
}

void SD_Object::write(std::uint32_t address, std::uint8_t * data, std::uint32_t length)
{
    std::uint32_t BlockAdd = 0;
    std::uint32_t NumberOfBlocks = 0;

    if(address % BLOCKSIZE == 0)
    {
        NumberOfBlocks = (length / BLOCKSIZE) + 1;
        BlockAdd = address / BLOCKSIZE;
        this->SD_status = HAL_SD_WriteBlocks(&hsd, &data[0], BlockAdd, NumberOfBlocks, 65536);
    }
}

void SD_Object::read(std::uint32_t address, std::uint8_t * Data, std::uint32_t length)
{

}

void SD_Object::erase(std::uint32_t address, std::uint32_t length)
{

}
