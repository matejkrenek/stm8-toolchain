#include "LCD_I2C_UI.h"
#include "LCD_I2C.h"
#include "Serial.h"

#define len(arr) sizeof(arr) / sizeof(arr[0])

uint8_t _lcd_i2c_ui_current_page = 0;
LCD_I2C_UI_Page *_lcd_i2c_ui_pages;
bool _lcd_i2c_ui_is_fresh = FALSE;

void LCD_I2C_UI_Init(LCD_I2C_UI_Page pages[])
{
    _lcd_i2c_ui_pages = pages;
}

LCD_I2C_UI_Page *LCD_I2C_UI_Pages()
{
    return _lcd_i2c_ui_pages;
}

bool LCD_I2C_UI_Is_Fresh()
{
    return _lcd_i2c_ui_is_fresh;
}

void LCD_I2C_UI_Set_Fresh(bool value)
{
    _lcd_i2c_ui_is_fresh = value;
}

void LCD_I2C_UI_Redirect(uint8_t *page_name)
{
    for (int i = 0; i < 20; i++)
    {
        if (_lcd_i2c_ui_pages[i].name == page_name)
        {
            _lcd_i2c_ui_current_page = i;
            LCD_I2C_UI_Set_Fresh(FALSE);
        }
    }
}

void LCD_I2C_UI_Render()
{
    if (!LCD_I2C_UI_Is_Fresh())
    {

        LCD_I2C_Clear();
        for (int i = 0; i < len(_lcd_i2c_ui_pages[_lcd_i2c_ui_current_page].content); i++)
        {
            if (_lcd_i2c_ui_pages[_lcd_i2c_ui_current_page].content[i].text)
            {
                LCD_I2C_SetCursor(_lcd_i2c_ui_pages[_lcd_i2c_ui_current_page].content[i].col, _lcd_i2c_ui_pages[_lcd_i2c_ui_current_page].content[i].row);
                LCD_I2C_Print(_lcd_i2c_ui_pages[_lcd_i2c_ui_current_page].content[i].text);
            }
        }

        LCD_I2C_UI_Set_Fresh(TRUE);
    }
}
