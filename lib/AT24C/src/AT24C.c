#include "stm8s.h"
#include "delay.h"
#include "Serial.h"
#include "AT24C.h"

uint8_t _at24c_address;
uint32_t _at24c_size;

void AT24C_Init(uint8_t address, uint32_t size)
{
    _at24c_address = address << 1;
    _at24c_size = size;

    GPIO_Init(GPIOB, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOB, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);

    I2C_DeInit();
    I2C_Init(100000, _at24c_address, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, CLK_GetClockFreq() / 1000000);
    I2C_Cmd(ENABLE);

    delay_ms(50);
}

uint32_t AT24C_Length()
{
    return _at24c_size * 1024;
}

uint8_t AT24C_Read(uint16_t address)
{
    uint8_t data;
    Serial_Print_String("FLAG BUSY 1");
    while (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY))
        ;
    Serial_Print_String("FLAG BUSY 2");

    I2C_GenerateSTART(ENABLE);
    Serial_Print_String("FLAG BUSY #");

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))
        ;

    I2C_Send7bitAddress(_at24c_address, I2C_DIRECTION_TX);

    Serial_Print_String("Address");

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;

    I2C_SendData(highByte(address));

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    I2C_SendData(lowByte(address));

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;
    I2C_GenerateSTOP(ENABLE);

    I2C_GenerateSTART(ENABLE);

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))
        ;

    I2C_Send7bitAddress(_at24c_address, I2C_DIRECTION_RX);
    Serial_Print_String("Address 2");

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED))
        ;

    while (!I2C_GetFlagStatus(I2C_FLAG_TRANSFERFINISHED))
        ;

    data = I2C_ReceiveData();

    I2C_GenerateSTOP(ENABLE);

    return data;
}

void AT24C_Write(uint16_t address, uint8_t value)
{

    while (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY))
        ;

    I2C_GenerateSTART(ENABLE);

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))
        ;

    I2C_Send7bitAddress(_at24c_address, I2C_DIRECTION_TX);

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;

    I2C_SendData(highByte(address));

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    I2C_SendData(lowByte(address));

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    I2C_SendData(value);

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    I2C_GenerateSTOP(ENABLE);
}

void AT24C_Update(uint16_t address, uint8_t value)
{
}