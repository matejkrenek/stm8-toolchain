#ifndef __LCD_I2C_UI_H
#define __LCD_I2C_UI_H

#include "stm8s.h"

typedef struct
{
    uint8_t type;
} LCD_I2C_UI_Action;

typedef struct
{
    uint8_t col;
    uint8_t row;
    uint8_t *text;
    LCD_I2C_UI_Action action;

} LCD_I2C_UI_Page_Content;

typedef struct
{
    uint8_t *name;
    LCD_I2C_UI_Page_Content content[5];
} LCD_I2C_UI_Page;

void LCD_I2C_UI_Init(LCD_I2C_UI_Page pages[]);
LCD_I2C_UI_Page *LCD_I2C_UI_Pages();
bool LCD_I2C_UI_Is_Fresh();
void LCD_I2C_UI_Redirect(uint8_t *page_name);
void LCD_I2C_UI_Set_Fresh(bool value);
void LCD_I2C_UI_Render();

extern uint8_t _lcd_i2c_ui_current_page;
extern LCD_I2C_UI_Page *_lcd_i2c_ui_pages;

#endif