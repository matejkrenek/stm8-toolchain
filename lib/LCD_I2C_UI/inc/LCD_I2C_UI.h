#ifndef __LCD_I2C_UI_H
#define __LCD_I2C_UI_H

#include "stm8s.h"

#define len(arr) sizeof(arr) / sizeof(arr[0])
#define SCROLLER_WINDOW_HEIGHT 2

typedef struct
{
    uint8_t *text;
    void (*onClick)();
    void (*onLeft)();
    void (*onRight)();
    void (*onRender)();
    uint8_t *redirectName;
    bool isFresh;
} LCD_I2C_UI_Page_Content;

typedef struct
{
    uint8_t *name;
    int content_length;
    bool hasScrollbar;
    LCD_I2C_UI_Page_Content *content;
} LCD_I2C_UI_Page;

typedef struct
{
    int page_length;
    LCD_I2C_UI_Page *pages;
} LCD_I2C_UI_Config;

void LCD_I2C_UI_Init(LCD_I2C_UI_Config *config);
LCD_I2C_UI_Config *LCD_I2C_UI_GetConfig();
LCD_I2C_UI_Page *LCD_I2C_UI_CurrentPage();
void LCD_I2C_UI_Redirect(uint8_t *name);
void LCD_I2C_UI_RedirectBack();
void LCD_I2C_UI_RedirectDynamically();
bool LCD_I2C_UI_IsFresh();
void LCD_I2C_UI_SetFresh(bool is_frash);
void LCD_I2C_UI_Render();
void LCD_I2C_UI_RenderScrollerCursor();
void LCD_I2C_UI_ScrollDown();
void LCD_I2C_UI_ScrollUp();
void LCD_I2C_UI_HandleClickAction();
void LCD_I2C_UI_HandleLeftAction();
void LCD_I2C_UI_HandleRightAction();
extern int _lcd_i2c_ui_current_page;
extern int _lcd_i2c_ui_scroller_cursor;
extern int _lcd_i2c_ui_previous_page;
extern int _lcd_i2c_ui_active_row_index;
extern int _lcd_i2c_ui_prev_active_row_index;
extern LCD_I2C_UI_Config *_lcd_i2c_ui_config;
extern bool _lcd_i2c_ui_is_fresh;

#endif