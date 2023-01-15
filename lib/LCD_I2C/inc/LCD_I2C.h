#ifndef __LCD_I2C_H
#define __LCD_I2C_H

#define LCD_I2C_CLEARDISPLAY 0x01
#define LCD_I2C_RETURNHOME 0x02
#define LCD_I2C_ENTRYMODESET 0x04
#define LCD_I2C_DISPLAYCONTROL 0x08
#define LCD_I2C_CURSORSHIFT 0x10
#define LCD_I2C_FUNCTIONSET 0x20
#define LCD_I2C_SETCGRAMADDR 0x40
#define LCD_I2C_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_I2C_ENTRYRIGHT 0x00
#define LCD_I2C_ENTRYLEFT 0x02
#define LCD_I2C_ENTRYSHIFTINCREMENT 0x01
#define LCD_I2C_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_I2C_DISPLAYON 0x04
#define LCD_I2C_DISPLAYOFF 0x00
#define LCD_I2C_CURSORON 0x02
#define LCD_I2C_CURSOROFF 0x00
#define LCD_I2C_BLINKON 0x01
#define LCD_I2C_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_I2C_DISPLAYMOVE 0x08
#define LCD_I2C_CURSORMOVE 0x00
#define LCD_I2C_MOVERIGHT 0x04
#define LCD_I2C_MOVELEFT 0x00

// flags for function set
#define LCD_I2C_8BITMODE 0x10
#define LCD_I2C_4BITMODE 0x00
#define LCD_I2C_2LINE 0x08
#define LCD_I2C_1LINE 0x00
#define LCD_I2C_5x10DOTS 0x04
#define LCD_I2C_5x8DOTS 0x00

// flags for backlight control
#define LCD_I2C_BACKLIGHT 0x08
#define LCD_I2C_NOBACKLIGHT 0x00

#define LCD_I2C_En 0x04 // Enable bit
#define LCD_I2C_Rw 0x02 // Read/Write bit
#define LCD_I2C_Rs 0x01 // Register select bit

extern uint8_t _lcd_i2c_address;
extern uint8_t _lcd_i2c_cols;
extern uint8_t _lcd_i2c_rows;
extern uint8_t _lcd_i2c_backlight;
extern uint8_t _lcd_i2c_displayfunction;
extern uint8_t _lcd_i2c_displaycontrol;
extern uint8_t _lcd_i2c_displaymode;

void LCD_I2C_Init(uint8_t address, uint8_t cols, uint8_t rows);
void LCD_I2C_ExpanderWrite(uint8_t data);
void LCD_I2C_Write(uint8_t slave_address, uint8_t data);
void LCD_I2C_Write4Bits(uint8_t data);
void LCD_I2C_PulseEnable(uint8_t data);
void LCD_I2C_Command(uint8_t data);
void LCD_I2C_Send(uint8_t data, uint8_t mode);
void LCD_I2C_Display();
void LCD_I2C_Clear();
void LCD_I2C_Home();
void LCD_I2C_NoBacklight();
void LCD_I2C_Backlight();
void LCD_I2C_CreateChar(uint8_t location, uint8_t charmap[]);
void LCD_I2C_SetCursor(uint8_t col, uint8_t row);
void LCD_I2C_Print(uint8_t *string);
void LCD_I2C_PrintChar(uint8_t string);

#endif