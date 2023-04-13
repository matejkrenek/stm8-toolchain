#ifndef __EEPROM_H
#define __EEPROM_H

#include "stm8s.h"

#define EEPROM_ADDRESS_START FLASH_DATA_START_PHYSICAL_ADDRESS
#define EEPROM_ADDRESS_END FLASH_DATA_END_PHYSICAL_ADDRESS

void eeprom_init();
void eeprom_write(uint32_t address, uint8_t data);
void eeprom_write16(uint32_t address, uint16_t data);
void eeprom_write32(uint32_t address, uint32_t data);
uint8_t eeprom_read(uint32_t address);
uint16_t eeprom_read16(uint32_t address);
uint32_t eeprom_read32(uint32_t address);

#endif