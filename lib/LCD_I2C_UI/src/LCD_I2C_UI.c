#include "LCD_I2C_UI.h"
#include "LCD_I2C.h"
#include "delay.h"
#include "Serial.h"

int _lcd_i2c_ui_current_page;
int _lcd_i2c_ui_previous_page;
LCD_I2C_UI_Config *_lcd_i2c_ui_config;
bool _lcd_i2c_ui_is_fresh = FALSE;
int _lcd_i2c_ui_scroller_cursor;
int _lcd_i2c_ui_active_row_index;
int _lcd_i2c_ui_prev_active_row_index;

void LCD_I2C_UI_Init(LCD_I2C_UI_Config *config)
{
    _lcd_i2c_ui_config = config;
    _lcd_i2c_ui_current_page = 0;
    _lcd_i2c_ui_scroller_cursor = 0;
    _lcd_i2c_ui_active_row_index = 0;
    _lcd_i2c_ui_prev_active_row_index = 0;
}

LCD_I2C_UI_Config *LCD_I2C_UI_GetConfig()
{
    return _lcd_i2c_ui_config;
}

LCD_I2C_UI_Page *LCD_I2C_UI_CurrentPage()
{
    return &LCD_I2C_UI_GetConfig()->pages[_lcd_i2c_ui_current_page];
}

bool LCD_I2C_UI_IsFresh()
{
    return _lcd_i2c_ui_is_fresh;
}

void LCD_I2C_UI_SetFresh(bool is_frash)
{
    _lcd_i2c_ui_is_fresh = is_frash;

    if (is_frash == FALSE)
    {
        for (int i = 0; i < LCD_I2C_UI_CurrentPage()->content_length; i++)
        {
            LCD_I2C_UI_CurrentPage()->content[i].isFresh = FALSE;
        }
    }
}

void LCD_I2C_UI_Redirect(uint8_t *name)
{
    for (int i = 0; i < _lcd_i2c_ui_config->page_length; i++)
    {
        if (_lcd_i2c_ui_config->pages[i].name == name)
        {
            _lcd_i2c_ui_previous_page = _lcd_i2c_ui_current_page;
            _lcd_i2c_ui_current_page = i;

            if (_lcd_i2c_ui_previous_page != _lcd_i2c_ui_current_page)
            {

                _lcd_i2c_ui_scroller_cursor = 0;
                _lcd_i2c_ui_prev_active_row_index = 0;
                _lcd_i2c_ui_active_row_index = 0;
            }
        }
    }
    LCD_I2C_UI_SetFresh(FALSE);
}

void LCD_I2C_UI_RedirectDynamically()
{
    if (LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].redirectName)
    {
        LCD_I2C_UI_Redirect(LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].redirectName);
    }
}

void LCD_I2C_UI_RedirectBack()
{
    if (_lcd_i2c_ui_current_page != _lcd_i2c_ui_previous_page)
    {
        _lcd_i2c_ui_current_page = _lcd_i2c_ui_previous_page;
        _lcd_i2c_ui_scroller_cursor = 0;
        LCD_I2C_UI_SetFresh(FALSE);
    }
}

void LCD_I2C_UI_ScrollDown()
{
    if (_lcd_i2c_ui_scroller_cursor < LCD_I2C_UI_CurrentPage()->content_length - 1 && LCD_I2C_UI_CurrentPage()->hasScrollbar == TRUE && _lcd_i2c_ui_active_row_index <= 0)
    {
        _lcd_i2c_ui_scroller_cursor++;
        _lcd_i2c_ui_prev_active_row_index = 0;
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_UI_SetFresh(FALSE);
        delay_ms(100);
    }
}

void LCD_I2C_UI_ScrollUp()
{
    if (_lcd_i2c_ui_scroller_cursor > 0 && LCD_I2C_UI_CurrentPage()->hasScrollbar == TRUE && _lcd_i2c_ui_active_row_index <= 0)
    {
        _lcd_i2c_ui_scroller_cursor--;
        _lcd_i2c_ui_prev_active_row_index = 0;
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_UI_SetFresh(FALSE);
        delay_ms(100);
    }
}

void LCD_I2C_UI_RenderScrollerCursor()
{
    if (LCD_I2C_UI_CurrentPage()->content_length > SCROLLER_WINDOW_HEIGHT - 1)
    {
        LCD_I2C_SetCursor(0, _lcd_i2c_ui_scroller_cursor == 0 ? 0 : 1);
        LCD_I2C_Print(">");
    }
}

void LCD_I2C_UI_HandleClickAction()
{
    if (LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].onClick)
    {
        _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;
        _lcd_i2c_ui_active_row_index++;
        LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].onClick();
    }
}

void LCD_I2C_UI_HandleLeftAction()
{
    if (LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].onLeft && _lcd_i2c_ui_active_row_index > 0)
    {
        LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].onLeft();
    }
    else
    {
        LCD_I2C_UI_ScrollUp();
    }
}

void LCD_I2C_UI_HandleRightAction()
{
    if (LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].onRight && _lcd_i2c_ui_active_row_index > 0)
    {
        LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].onRight();
    }
    else
    {
        LCD_I2C_UI_ScrollDown();
    }
}

void LCD_I2C_UI_Render()
{
    delay_ms(100);
    if (!LCD_I2C_UI_IsFresh())
    {
        LCD_I2C_Clear();
        LCD_I2C_UI_SetFresh(TRUE);
    }

    if ((LCD_I2C_UI_CurrentPage()->content_length > SCROLLER_WINDOW_HEIGHT - 1) && LCD_I2C_UI_CurrentPage()->hasScrollbar != FALSE)
    {

        if (_lcd_i2c_ui_scroller_cursor < 2)
        {
            if (LCD_I2C_UI_CurrentPage()->content[0].isFresh == FALSE)
            {
                LCD_I2C_UI_RenderScrollerCursor();
                LCD_I2C_SetCursor(1, 0);
                LCD_I2C_Print(LCD_I2C_UI_CurrentPage()->content[0].text);
                LCD_I2C_UI_CurrentPage()->content[0].isFresh = TRUE;

                if (LCD_I2C_UI_CurrentPage()->content[0].onRender)
                {
                    LCD_I2C_UI_CurrentPage()->content[0].onRender();
                }
            }

            if (LCD_I2C_UI_CurrentPage()->content[1].isFresh == FALSE)
            {
                LCD_I2C_UI_RenderScrollerCursor();
                LCD_I2C_SetCursor(1, 1);
                LCD_I2C_Print(LCD_I2C_UI_CurrentPage()->content[1].text);
                LCD_I2C_UI_CurrentPage()->content[1].isFresh = TRUE;

                if (LCD_I2C_UI_CurrentPage()->content[1].onRender)
                {
                    LCD_I2C_UI_CurrentPage()->content[1].onRender();
                }
            }
        }
        else
        {
            if (LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor - 1].isFresh == FALSE)
            {
                LCD_I2C_UI_RenderScrollerCursor();
                LCD_I2C_SetCursor(1, 0);
                LCD_I2C_Print(LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor - 1].text);
                LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor - 1].isFresh = TRUE;

                if (LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor - 1].onRender)
                {
                    LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor - 1].onRender();
                }
            }

            if (LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].isFresh == FALSE)
            {
                LCD_I2C_UI_RenderScrollerCursor();
                LCD_I2C_SetCursor(1, 1);
                LCD_I2C_Print(LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].text);
                LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].isFresh = TRUE;

                if (LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].onRender)
                {
                    LCD_I2C_UI_CurrentPage()->content[_lcd_i2c_ui_scroller_cursor].onRender();
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < LCD_I2C_UI_CurrentPage()->content_length; i++)
        {
            if (LCD_I2C_UI_CurrentPage()->content[i].isFresh == FALSE)
            {
                LCD_I2C_SetCursor(0, i);
                LCD_I2C_Print(LCD_I2C_UI_CurrentPage()->content[i].text);
                LCD_I2C_UI_CurrentPage()->content[i].isFresh = TRUE;

                if (LCD_I2C_UI_CurrentPage()->content[i].onRender)
                {
                    LCD_I2C_UI_CurrentPage()->content[i].onRender();
                }
            }
        }
    }
}
