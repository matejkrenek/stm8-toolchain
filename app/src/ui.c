#include "ui.h"

void UI_HomePage()
{
    uint8_t string[10];

    switch (peripheral_home_page)
    {
    case LED_ARRAY:
        switch (peripheral_leds.mode)
        {
        case BLINK:
            sprintf(string, "LEDs mode BLINK:");
            break;

        case INVERT:
            sprintf(string, "LEDs mode INVERT:");

            break;

        case STATIC:
            sprintf(string, "LEDs mode STATIC:");

            break;

        default:
            break;
        }
        LCD_I2C_Print(string);
        LCD_I2C_SetCursor(0, 1);

        for (int i = 0; i < 8; i++)
        {
            if ((peripheral_leds.value >> 7 - i) & 1)
            {
                LCD_I2C_Print("1");
            }
            else
            {
                LCD_I2C_Print("0");
            }

            if (i == 3)
            {
                LCD_I2C_Print(" ");
            }
        }

        break;
    case RGB_LED:
        LCD_I2C_Print("RGB LED:");
        LCD_I2C_SetCursor(0, 1);
        sprintf(string, "(%u,%u,%u,%u.%u)", peripheral_rgb_led.red, peripheral_rgb_led.green, peripheral_rgb_led.blue, peripheral_rgb_led.alpha / 100, peripheral_rgb_led.alpha % 100);
        LCD_I2C_Print(string);

        break;
    case RTC:
        if (milis() - peripheral_rtc._time > 1000 || peripheral_lcd.isFirstRender)
        {
            LCD_I2C_Print("Real Time Clock:");
            LCD_I2C_SetCursor(0, 1);
            peripheral_rtc.datetime = DSRTC_DateTime();
            sprintf(string, "%02u.%02u. %02u:%02u:%02u", peripheral_rtc.datetime->dayOfMonth, peripheral_rtc.datetime->month, peripheral_rtc.datetime->hours, peripheral_rtc.datetime->minutes, peripheral_rtc.datetime->seconds);
            LCD_I2C_Print(string);
            tone_blink(peripheral_buzzer.frequnecy - (peripheral_buzzer.frequnecy / 2));
            peripheral_lcd.isFirstRender = FALSE;
            peripheral_rtc._time = milis();
        }
        LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;

        break;
    default:
        break;
    }
}

void UI_Peripheral_LEDs()
{
    for (int i = 0; i < 8; i++)
    {
        if ((peripheral_leds.value >> 7 - i) & 1)
        {
            LCD_I2C_Print("1");
        }
        else
        {
            LCD_I2C_Print("0");
        }

        if (i == 3)
        {
            LCD_I2C_Print(" ");
        }
    }

    if (_lcd_i2c_ui_active_row_index > 0 && peripheral_leds.isActive == FALSE)
    {
        UI_Peripheral_LEDs_Action();
    }
}

void UI_Peripheral_LEDs_Mode()
{
    switch (peripheral_leds.mode)
    {
    case BLINK:
        LCD_I2C_Print("blink ");

        break;

    case INVERT:
        LCD_I2C_Print("invert");

        break;

    case STATIC:
        LCD_I2C_Print("static");

        break;

    default:
        break;
    }
}

void UI_Peripheral_LEDs_Mode_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0x02, peripheral_leds.mode);
        tone_success(peripheral_buzzer.frequnecy);

        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 1);
    }
}

void UI_Peripheral_LEDs_Mode_ActionLeft()
{
    if (peripheral_leds.mode > 0)
    {
        peripheral_leds.mode--;
    }
    else
    {
        peripheral_leds.mode = LED_ARRAY_MODE_LENGTH - 1;
    }
    peripheral_leds.value = eeprom_read(0x01);
    LCD_I2C_UI_CurrentPage()->content[2].isFresh = FALSE;
}

void UI_Peripheral_LEDs_Mode_ActionRight()
{
    if (peripheral_leds.mode < LED_ARRAY_MODE_LENGTH - 1)
    {
        peripheral_leds.mode++;
    }
    else
    {
        peripheral_leds.mode = 0;
    }
    peripheral_leds.value = eeprom_read(0x01);
    LCD_I2C_UI_CurrentPage()->content[2].isFresh = FALSE;
}

void UI_Peripheral_LEDs_Period()
{
    uint8_t string[10];
    sprintf(string, "%llu ms", peripheral_leds.period);
    LCD_I2C_Print(string);
}

void UI_Peripheral_LEDs_Period_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write32(0x03, peripheral_leds.period);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Peripheral_LEDs_Period_ActionLeft()
{
    if (peripheral_leds.period > 100)
    {
        peripheral_leds.period -= 50;
    }
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Peripheral_LEDs_Period_ActionRight()
{
    if (peripheral_leds.period < 10000)
    {
        peripheral_leds.period += 50;
    }
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Peripheral_LEDs_Action()
{
    if (_lcd_i2c_ui_active_row_index > 8)
    {
        eeprom_write(0x01, peripheral_leds.value);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
        peripheral_leds.value = eeprom_read(0x01);
        peripheral_leds.isActive = TRUE;
    }
    else
    {
        if (_lcd_i2c_ui_active_row_index == 1 && _lcd_i2c_ui_prev_active_row_index != 1)
        {
            peripheral_leds.value = eeprom_read(0x01);
            LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
        }
        peripheral_leds.isActive = FALSE;
        if (_lcd_i2c_ui_active_row_index > 4)
        {
            LCD_I2C_SetCursor(strlen(LCD_UI_Page_Peripheral_Leds[0].text) + _lcd_i2c_ui_active_row_index + 1, 0);
        }
        else
        {
            LCD_I2C_SetCursor(strlen(LCD_UI_Page_Peripheral_Leds[0].text) + _lcd_i2c_ui_active_row_index, 0);
        }
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;

    GPIO_Write(peripheral_leds.port, peripheral_leds.value);
}

void UI_Peripheral_LEDs_ActionLeft()
{
    peripheral_leds.value &= ~(1 << (8 - _lcd_i2c_ui_active_row_index));
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Peripheral_LEDs_ActionRight()
{
    peripheral_leds.value |= 1 << (8 - _lcd_i2c_ui_active_row_index);

    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_SettingsCursor()
{
    if (LCD_I2C_HasCursor())
    {
        LCD_I2C_Print("on ");
    }
    else
    {
        LCD_I2C_Print("off");
    }
}

void UI_Action_SettingsCursor()
{
    LCD_I2C_ToggleCursor();

    if (LCD_I2C_HasCursor())
    {
        eeprom_write(0x00, 1);
    }
    else
    {
        eeprom_write(0x00, 0);
    }
    tone_success(peripheral_buzzer.frequnecy);

    _lcd_i2c_ui_active_row_index = 0;
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Peripheral_RTC_Time()
{
    if (_lcd_i2c_ui_active_row_index == 0)
    {
        peripheral_rtc.datetime = DSRTC_DateTime();
    }
    uint8_t string[10];
    sprintf(string, "%02u:%02u:%02u", peripheral_rtc.datetime->hours, peripheral_rtc.datetime->minutes, peripheral_rtc.datetime->seconds);
    LCD_I2C_Print(string);
}

void UI_Peripheral_RTC_Time_Action()
{
    if (_lcd_i2c_ui_active_row_index > 3)
    {
        DSRTC_SetDateTime(peripheral_rtc.datetime->seconds,
                          peripheral_rtc.datetime->minutes,
                          peripheral_rtc.datetime->hours,
                          peripheral_rtc.datetime->dayOfWeek,
                          peripheral_rtc.datetime->dayOfMonth,
                          peripheral_rtc.datetime->month,
                          peripheral_rtc.datetime->year);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Peripheral_RTC_Time_ActionLeft()
{
    switch (_lcd_i2c_ui_active_row_index)
    {
    case 1:
        if (peripheral_rtc.datetime->hours == 0)
        {
            peripheral_rtc.datetime->hours = 23;
        }
        else
        {
            peripheral_rtc.datetime->hours -= 1;
        }
        break;
    case 2:
        if (peripheral_rtc.datetime->minutes == 0)
        {
            peripheral_rtc.datetime->minutes = 59;
        }
        else
        {
            peripheral_rtc.datetime->minutes -= 1;
        }
        break;
    case 3:
        if (peripheral_rtc.datetime->seconds == 0)
        {
            peripheral_rtc.datetime->seconds = 59;
        }
        else
        {
            peripheral_rtc.datetime->seconds -= 1;
        }
        break;

    default:
        break;
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Peripheral_RTC_Time_ActionRight()
{
    switch (_lcd_i2c_ui_active_row_index)
    {
    case 1:
        if (peripheral_rtc.datetime->hours == 23)
        {
            peripheral_rtc.datetime->hours = 0;
        }
        else
        {
            peripheral_rtc.datetime->hours += 1;
        }
        break;
    case 2:
        if (peripheral_rtc.datetime->minutes == 59)
        {
            peripheral_rtc.datetime->minutes = 0;
        }
        else
        {
            peripheral_rtc.datetime->minutes += 1;
        }
        break;
    case 3:
        if (peripheral_rtc.datetime->seconds == 59)
        {
            peripheral_rtc.datetime->seconds = 00;
        }
        else
        {
            peripheral_rtc.datetime->seconds += 1;
        }
        break;

    default:
        break;
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Peripheral_RTC_Date()
{
    if (_lcd_i2c_ui_active_row_index == 0)
    {
        peripheral_rtc.datetime = DSRTC_DateTime();
    }
    uint8_t string[10];
    sprintf(string, "%02u/%02u/%02u", peripheral_rtc.datetime->dayOfMonth, peripheral_rtc.datetime->month, peripheral_rtc.datetime->year);
    LCD_I2C_Print(string);
}

void UI_Peripheral_RTC_Date_Action()
{
    if (_lcd_i2c_ui_active_row_index > 3)
    {
        DSRTC_SetDateTime(peripheral_rtc.datetime->seconds,
                          peripheral_rtc.datetime->minutes,
                          peripheral_rtc.datetime->hours,
                          peripheral_rtc.datetime->dayOfWeek,
                          peripheral_rtc.datetime->dayOfMonth,
                          peripheral_rtc.datetime->month,
                          peripheral_rtc.datetime->year);
        tone_success(peripheral_buzzer.frequnecy);

        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Peripheral_RTC_Date_ActionLeft()
{
    switch (_lcd_i2c_ui_active_row_index)
    {
    case 1:
        if (peripheral_rtc.datetime->dayOfMonth == 1)
        {
            peripheral_rtc.datetime->dayOfMonth = 31;
        }
        else
        {
            peripheral_rtc.datetime->dayOfMonth -= 1;
        }
        break;
    case 2:
        if (peripheral_rtc.datetime->month == 1)
        {
            peripheral_rtc.datetime->month = 12;
        }
        else
        {
            peripheral_rtc.datetime->month -= 1;
        }
        break;
    case 3:
        if (peripheral_rtc.datetime->year == 0)
        {
            peripheral_rtc.datetime->year = 99;
        }
        else
        {
            peripheral_rtc.datetime->year -= 1;
        }
        break;

    default:
        break;
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Peripheral_RTC_Date_ActionRight()
{
    switch (_lcd_i2c_ui_active_row_index)
    {
    case 1:
        if (peripheral_rtc.datetime->dayOfMonth == 31)
        {
            peripheral_rtc.datetime->dayOfMonth = 1;
        }
        else
        {
            peripheral_rtc.datetime->dayOfMonth += 1;
        }
        break;
    case 2:
        if (peripheral_rtc.datetime->month == 12)
        {
            peripheral_rtc.datetime->month = 1;
        }
        else
        {
            peripheral_rtc.datetime->month += 1;
        }
        break;
    case 3:
        if (peripheral_rtc.datetime->year == 99)
        {
            peripheral_rtc.datetime->year = 0;
        }
        else
        {
            peripheral_rtc.datetime->year += 1;
        }
        break;

    default:
        break;
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Peripheral_Settings_Light()
{
    uint8_t string[10];
    sprintf(string, "%02u s", peripheral_lcd.backlightTimeOff);
    LCD_I2C_Print(string);
}

void UI_Peripheral_Settings_Light_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0x0A, peripheral_lcd.backlightTimeOff);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Peripheral_Settings_Light_ActionLeft()
{
    if (peripheral_lcd.backlightTimeOff > 1)
    {
        peripheral_lcd.backlightTimeOff--;
    }
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Peripheral_Settings_Light_ActionRight()
{
    if (peripheral_lcd.backlightTimeOff < 99)
    {
        peripheral_lcd.backlightTimeOff++;
    }
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Settings_Sound_Volume()
{
    uint8_t string[10];
    sprintf(string, "%u %%", peripheral_buzzer.volume);
    LCD_I2C_Print(string);
}

void UI_Settings_Sound_Volume_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0x0B, peripheral_buzzer.volume);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Settings_Sound_Volume_ActionLeft()
{
    if (peripheral_buzzer.volume > 0)
    {
        peripheral_buzzer.volume--;
        tone_volume(peripheral_buzzer.volume);
    }

    LCD_I2C_UI_CurrentPage()->content[2].isFresh = FALSE;
}

void UI_Settings_Sound_Volume_ActionRight()
{
    if (peripheral_buzzer.volume < 100)
    {
        peripheral_buzzer.volume++;
        tone_volume(peripheral_buzzer.volume);
    }

    LCD_I2C_UI_CurrentPage()->content[2].isFresh = FALSE;
}

void UI_Settings_Sound_Freq()
{
    uint8_t string[10];
    sprintf(string, "%u Hz", peripheral_buzzer.frequnecy);
    LCD_I2C_Print(string);
}

void UI_Settings_Sound_Freq_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write16(0x0C, peripheral_buzzer.frequnecy);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Settings_Sound_Freq_ActionLeft()
{
    if (peripheral_buzzer.frequnecy > 100)
    {
        peripheral_buzzer.frequnecy -= 5;
    }
    LCD_I2C_UI_CurrentPage()->content[3].isFresh = FALSE;
}

void UI_Settings_Sound_Freq_ActionRight()
{
    if (peripheral_buzzer.frequnecy < 1200)
    {
        peripheral_buzzer.frequnecy += 5;
    }
    LCD_I2C_UI_CurrentPage()->content[3].isFresh = FALSE;
}

void UI_Peripheral_RGB_Red()
{
    uint8_t string[10];
    sprintf(string, "%u", peripheral_rgb_led.red);
    LCD_I2C_Print(string);
    rgb_set(peripheral_rgb_led.red, peripheral_rgb_led.green, peripheral_rgb_led.blue, peripheral_rgb_led.alpha);
}

void UI_Peripheral_RGB_Red_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0x10, peripheral_rgb_led.red);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Peripheral_RGB_Red_ActionLeft()
{
    if (peripheral_rgb_led.red > 0)
    {
        peripheral_rgb_led.red -= 1;
    }

    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Peripheral_RGB_Red_ActionRight()
{
    if (peripheral_rgb_led.red < 255)
    {
        peripheral_rgb_led.red += 1;
    }

    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Peripheral_RGB_Green()
{
    uint8_t string[10];
    sprintf(string, "%u", peripheral_rgb_led.green);
    LCD_I2C_Print(string);
    rgb_set(peripheral_rgb_led.red, peripheral_rgb_led.green, peripheral_rgb_led.blue, peripheral_rgb_led.alpha);
}

void UI_Peripheral_RGB_Green_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0x20, peripheral_rgb_led.green);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Peripheral_RGB_Green_ActionLeft()
{
    if (peripheral_rgb_led.green > 0)
    {
        peripheral_rgb_led.green -= 1;
    }

    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Peripheral_RGB_Green_ActionRight()
{
    if (peripheral_rgb_led.green < 255)
    {
        peripheral_rgb_led.green += 1;
    }

    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Peripheral_RGB_Blue()
{
    uint8_t string[10];
    sprintf(string, "%u", peripheral_rgb_led.blue);
    LCD_I2C_Print(string);
    rgb_set(peripheral_rgb_led.red, peripheral_rgb_led.green, peripheral_rgb_led.blue, peripheral_rgb_led.alpha);
}

void UI_Peripheral_RGB_Blue_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0x30, peripheral_rgb_led.blue);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Peripheral_RGB_Blue_ActionLeft()
{
    if (peripheral_rgb_led.blue > 0)
    {
        peripheral_rgb_led.blue -= 1;
    }

    LCD_I2C_UI_CurrentPage()->content[2].isFresh = FALSE;
}

void UI_Peripheral_RGB_Blue_ActionRight()
{
    if (peripheral_rgb_led.blue < 255)
    {
        peripheral_rgb_led.blue += 1;
    }

    LCD_I2C_UI_CurrentPage()->content[2].isFresh = FALSE;
}

void UI_Peripheral_RGB_Alpha()
{
    uint8_t string[10];
    sprintf(string, "%u %%", peripheral_rgb_led.alpha);
    LCD_I2C_Print(string);
    rgb_set(peripheral_rgb_led.red, peripheral_rgb_led.green, peripheral_rgb_led.blue, peripheral_rgb_led.alpha);
}

void UI_Peripheral_RGB_Alpha_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0x40, peripheral_rgb_led.alpha);
        tone_success(peripheral_buzzer.frequnecy);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Peripheral_RGB_Alpha_ActionLeft()
{
    if (peripheral_rgb_led.alpha > 0)
    {
        peripheral_rgb_led.alpha -= 1;
    }

    LCD_I2C_UI_CurrentPage()->content[3].isFresh = FALSE;
}

void UI_Peripheral_RGB_Alpha_ActionRight()
{
    if (peripheral_rgb_led.alpha < 100)
    {
        peripheral_rgb_led.alpha += 1;
    }

    LCD_I2C_UI_CurrentPage()->content[3].isFresh = FALSE;
}

void UI_MainPage_Peripheral()
{
    switch (peripheral_home_page)
    {
    case LED_ARRAY:
        LCD_I2C_Print("LEDs");

        break;

    case RGB_LED:
        LCD_I2C_Print("RGB");

        break;

    case RTC:
        LCD_I2C_Print("RTC");

        break;

    default:
        break;
    }
}

void UI_MainPage_Peripheral_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0xF0, peripheral_home_page);
        tone_success(peripheral_buzzer.frequnecy);

        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_MainPage_Peripheral_ActionLeft()
{
    if (peripheral_home_page > 0)
    {
        peripheral_home_page--;
    }
    else
    {
        peripheral_home_page = PERIPHERAL_LENGTH - 1;
    }

    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_MainPage_Peripheral_ActionRight()
{
    if (peripheral_home_page < PERIPHERAL_LENGTH - 1)
    {
        peripheral_home_page++;
    }
    else
    {
        peripheral_home_page = 0;
    }

    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}
