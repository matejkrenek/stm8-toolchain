#include "eeprom.h"

void eeprom_init()
{
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    FLASH_SetProgrammingTime(FLASH_PROGRAMTIME_STANDARD);
}

void eeprom_write(uint32_t address, uint8_t data)
{
    FLASH_ProgramByte(EEPROM_ADDRESS_START + address, data);
}

void eeprom_write16(uint32_t address, uint16_t data)
{
    uint8_t buffer[2];

    buffer[1] = data & 0x00FF;
    buffer[0] = (data & 0xFF00) >> 8;

    for (short i = 0; i < 2; i++)
    {
        eeprom_write(address + i, buffer[i]);
    }
}

void eeprom_write32(uint32_t address, uint32_t data)
{
    uint8_t buffer[4];

    buffer[3] = data & 0x000000FF;
    buffer[2] = (data & 0x0000FF00) >> 8;
    buffer[1] = (data & 0x00FF0000) >> 16;
    buffer[0] = (data & 0xFF000000) >> 24;

    for (short i = 0; i < 4; ++i)
    {
        eeprom_write(address + i, buffer[i]);
    }
}

uint8_t eeprom_read(uint32_t address)
{
    return FLASH_ReadByte(EEPROM_ADDRESS_START + address);
}

uint16_t eeprom_read16(uint32_t address)
{
    uint8_t buffer[2];

    for (short i = 0; i < 2; i++)
    {
        buffer[i] = eeprom_read(address + i);
    }

    return ((uint16_t)buffer[0] << 8 |
            (uint16_t)buffer[1]);
}

uint32_t eeprom_read32(uint32_t address)
{
    uint32_t data;
    uint8_t buffer[4];

    buffer[0] = eeprom_read(address + 0);
    buffer[1] = eeprom_read(address + 1);
    buffer[2] = eeprom_read(address + 2);
    buffer[3] = eeprom_read(address + 3);

    data = (uint32_t)buffer[0] << 24 |
           (uint32_t)buffer[1] << 16 |
           (uint32_t)buffer[2] << 8 |
           (uint32_t)buffer[3];

    return data;
}