#include "stm8s.h"
#include "delay.h"
#include "LCD_I2C.h"

uint8_t _lcd_i2c_address;
uint8_t _lcd_i2c_cols;
uint8_t _lcd_i2c_rows;
uint8_t _lcd_i2c_backlight;
uint8_t _lcd_i2c_displayfunction;
uint8_t _lcd_i2c_displaycontrol;
uint8_t _lcd_i2c_displaymode;

void LCD_I2C_Init(uint8_t address, uint8_t cols, uint8_t rows)
{
    _lcd_i2c_address = address << 1;
    _lcd_i2c_cols = cols;
    _lcd_i2c_rows = rows;
    _lcd_i2c_backlight = LCD_I2C_BACKLIGHT;
    _lcd_i2c_displayfunction = LCD_I2C_4BITMODE | LCD_I2C_2LINE | LCD_I2C_5x8DOTS;

    GPIO_Init(GPIOC, GPIO_PIN_5, GPIO_MODE_OUT_PP_HIGH_FAST);
    GPIO_Init(GPIOC, GPIO_PIN_4, GPIO_MODE_OUT_PP_HIGH_FAST);

    I2C_DeInit();
    I2C_Init(100000, _lcd_i2c_address, I2C_DUTYCYCLE_2, I2C_ACK_CURR, I2C_ADDMODE_7BIT, CLK_GetClockFreq() / 1000000);
    I2C_Cmd(ENABLE);
    delay_ms(50);
    LCD_I2C_ExpanderWrite(_lcd_i2c_backlight);
    delay_ms(1000);
    LCD_I2C_Write4Bits(0x03 << 4);
    delay_us(4500);
    LCD_I2C_Write4Bits(0x03 << 4);
    delay_us(4500);
    LCD_I2C_Write4Bits(0x03 << 4);
    delay_us(150);
    LCD_I2C_Write4Bits(0x02 << 4);
    LCD_I2C_Command(LCD_I2C_FUNCTIONSET | _lcd_i2c_displayfunction);
    _lcd_i2c_displaycontrol = LCD_I2C_DISPLAYON | LCD_I2C_CURSOROFF | LCD_I2C_BLINKOFF;
    LCD_I2C_Display();
    LCD_I2C_Clear();
    _lcd_i2c_displaymode = LCD_I2C_ENTRYLEFT | LCD_I2C_ENTRYSHIFTDECREMENT;
    LCD_I2C_Command(LCD_I2C_ENTRYMODESET | _lcd_i2c_displaymode);
    LCD_I2C_Home();
}

void LCD_I2C_Write(uint8_t slave_address, uint8_t data)
{
    while (I2C_GetFlagStatus(I2C_FLAG_BUSBUSY))
        ;

    I2C_GenerateSTART(ENABLE);

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_MODE_SELECT))
        ;

    I2C_Send7bitAddress(slave_address, I2C_DIRECTION_TX);

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
        ;

    I2C_SendData(data);

    while (!I2C_CheckEvent(I2C_EVENT_MASTER_BYTE_TRANSMITTED))
        ;

    I2C_GenerateSTOP(ENABLE);
}

void LCD_I2C_ExpanderWrite(uint8_t data)
{
    LCD_I2C_Write(_lcd_i2c_address, data | _lcd_i2c_backlight);
}

void LCD_I2C_Write4Bits(uint8_t data)
{
    LCD_I2C_ExpanderWrite(data);
    LCD_I2C_PulseEnable(data);
}

void LCD_I2C_PulseEnable(uint8_t data)
{
    LCD_I2C_ExpanderWrite(data | LCD_I2C_En);
    delay_us(1);

    LCD_I2C_ExpanderWrite(data & ~LCD_I2C_En);
    delay_us(50);
}

void LCD_I2C_Command(uint8_t data)
{
    LCD_I2C_Send(data, 0);
}

void LCD_I2C_Send(uint8_t data, uint8_t mode)
{
    uint8_t highnib = data & 0xf0;
    uint8_t lownib = (data << 4) & 0xf0;
    LCD_I2C_Write4Bits(highnib | mode);
    LCD_I2C_Write4Bits(lownib | mode);
}

void LCD_I2C_Display()
{
    _lcd_i2c_displaycontrol |= LCD_I2C_DISPLAYON;
    LCD_I2C_Command(LCD_I2C_DISPLAYCONTROL | _lcd_i2c_displaycontrol);
}

void LCD_I2C_Clear()
{
    LCD_I2C_Command(LCD_I2C_CLEARDISPLAY);
    delay_us(2000);
}

void LCD_I2C_Home()
{
    LCD_I2C_Command(LCD_I2C_RETURNHOME);
    delay_us(2000);
}

void LCD_I2C_NoBacklight()
{
    _lcd_i2c_backlight = LCD_I2C_NOBACKLIGHT;
    LCD_I2C_ExpanderWrite(0);
}

void LCD_I2C_Backlight()
{
    _lcd_i2c_backlight = LCD_I2C_BACKLIGHT;
    LCD_I2C_ExpanderWrite(0);
}

void LCD_I2C_CreateChar(uint8_t location, uint8_t charmap[])
{
    location &= 0x7;
    LCD_I2C_Command(LCD_I2C_SETCGRAMADDR | (location << 3));
    for (int i = 0; i < 8; i++)
    {
        LCD_I2C_Send(charmap[i], LCD_I2C_Rs);
    }
}

void LCD_I2C_SetCursor(uint8_t col, uint8_t row)
{
    int row_offsets[] = {0x00, 0x40, 0x14, 0x54};

    if (row > _lcd_i2c_rows)
    {
        row = _lcd_i2c_rows - 1;
    }

    LCD_I2C_Command(LCD_I2C_SETDDRAMADDR | (col + row_offsets[row]));
}

void LCD_I2C_Print(uint8_t *string)
{
    while (*string)
    {
        LCD_I2C_Send(*string, LCD_I2C_Rs);
        string++;
    }
}

void LCD_I2C_PrintChar(uint8_t character)
{
    LCD_I2C_Send(character, LCD_I2C_Rs);
}