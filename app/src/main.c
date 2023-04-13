#include "main.h"
#include "delay.h"
#include "LCD_I2C.h"
#include "LCD_I2C_UI.h"
#include "Serial.h"
#include "encoder.h"
#include "milis.h"
#include "DSRTC.h"
#include "ui.h"
#include "string.h"
#include "eeprom.h"

void handleLeft();
void handleRight();
void handleClick();

typedef enum
{
    BLINK,
    STATIC,
    INVERT,
    LENGTH
} Periferal_LED_Matrix_Mode;

typedef struct
{
    uint8_t value;
    Periferal_LED_Matrix_Mode mode;
    uint32_t period;
    uint32_t _time;
    bool isActive;
    GPIO_TypeDef *port;
} Periferal_LED_Matrix;

Periferal_LED_Matrix periferal_leds = {
    .value = 0b11111111,
    .mode = 0,
    .period = 700,
    ._time = 0,
    .isActive = TRUE,
    .port = GPIOB,
};

typedef struct
{
    DateTime *datetime;
    uint32_t _time;
    bool isActive;
} Periferal_RTC;

Periferal_RTC periferal_rtc = {
    ._time = 0,
    .isActive = TRUE,
};

Encoder_Config ENCODER_CONFIG = {
    .clk = GPIO_PIN_7,
    .ds = GPIO_PIN_6,
    .btn = GPIO_PIN_5,
    .onLeft = handleLeft,
    .onRight = handleRight,
    .onClick = handleClick,
};

bool lcd_ui_first_render = TRUE;
bool lcd_ui_backlight_on = TRUE;
uint8_t lcd_ui_backlight_time = 5;
uint32_t time = 0;

void UI_HomePage()
{
    if (milis() - periferal_rtc._time > 1000 || lcd_ui_first_render)
    {
        periferal_rtc.datetime = DSRTC_DateTime();
        uint8_t string[10];
        sprintf(string, "%02u:%02u:%02u", periferal_rtc.datetime->hours, periferal_rtc.datetime->minutes, periferal_rtc.datetime->seconds);
        LCD_I2C_Print(string);
        lcd_ui_first_render = FALSE;
        periferal_rtc._time = milis();
    }

    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_HomePageTemp()
{
    LCD_I2C_Print("27 C");
}

void UI_Periferal_LEDs()
{

    for (int i = 0; i < 8; i++)
    {
        if ((periferal_leds.value >> 7 - i) & 1)
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

    if (_lcd_i2c_ui_active_row_index > 0)
    {
        UI_Periferal_LEDs_Action();
    }
}

void UI_Periferal_LEDs_Mode()
{
    switch (periferal_leds.mode)
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

void UI_Periferal_LEDs_Mode_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0x02, periferal_leds.mode);

        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 1);
    }
}
void UI_Periferal_LEDs_Mode_ActionLeft()
{
    if (periferal_leds.mode > 0)
    {
        periferal_leds.mode--;
    }
    periferal_leds.value = eeprom_read(0x01);
    LCD_I2C_UI_CurrentPage()->content[2].isFresh = FALSE;
}
void UI_Periferal_LEDs_Mode_ActionRight()
{
    if (periferal_leds.mode < LENGTH)
    {
        periferal_leds.mode++;
    }
    periferal_leds.value = eeprom_read(0x01);
    LCD_I2C_UI_CurrentPage()->content[2].isFresh = FALSE;
}

void UI_Periferal_LEDs_Period()
{
    uint8_t string[10];
    sprintf(string, "%llu ms", periferal_leds.period);
    LCD_I2C_Print(string);
}

void UI_Periferal_LEDs_Period_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write32(0x03, periferal_leds.period);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}
void UI_Periferal_LEDs_Period_ActionLeft()
{
    if (periferal_leds.period > 100)
    {
        periferal_leds.period -= 50;
    }
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}
void UI_Periferal_LEDs_Period_ActionRight()
{
    if (periferal_leds.period < 10000)
    {
        periferal_leds.period += 50;
    }
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Periferal_LEDs_Action()
{
    Serial_Print("leds_action lcink\n");
    if (_lcd_i2c_ui_active_row_index > 8)
    {
        eeprom_write(0x01, periferal_leds.value);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
        periferal_leds.value = eeprom_read(0x01);
        periferal_leds.isActive = TRUE;
    }
    else
    {
        if (_lcd_i2c_ui_active_row_index == 1 && _lcd_i2c_ui_active_row_index != 1)
        {
            periferal_leds.value = eeprom_read(0x01);
            LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
        }
        periferal_leds.isActive = FALSE;
        if (_lcd_i2c_ui_active_row_index > 4)
        {
            LCD_I2C_SetCursor(strlen(LCD_UI_Page_Periferal_Leds[0].text) + _lcd_i2c_ui_active_row_index + 1, 0);
        }
        else
        {
            LCD_I2C_SetCursor(strlen(LCD_UI_Page_Periferal_Leds[0].text) + _lcd_i2c_ui_active_row_index, 0);
        }
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;

    GPIO_Write(periferal_leds.port, periferal_leds.value);
}

void UI_Periferal_LEDs_ActionLeft()
{
    periferal_leds.value &= ~(1 << (8 - _lcd_i2c_ui_active_row_index));
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Periferal_LEDs_ActionRight()
{
    periferal_leds.value |= 1 << (8 - _lcd_i2c_ui_active_row_index);

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

    _lcd_i2c_ui_active_row_index = 0;
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Actions_TempChart()
{
    Serial_Tab_Chart("Te. chart");
    delay_ms(100);
    Serial_Print("temp,12,32");
    delay_ms(100);
    Serial_Print("temp2,24,11");
    delay_ms(100);
    Serial_Tab_End();
    _lcd_i2c_ui_active_row_index = 0;
}
void UI_Actions_TempTable()
{
    Serial_Tab_Table("Te. table", "te,hu,ok");
    delay_ms(100);
    Serial_Print("32,72,1");
    delay_ms(100);
    Serial_Print("29,69,0");
    delay_ms(100);
    Serial_Tab_End();
    _lcd_i2c_ui_active_row_index = 0;
}
void UI_Actions_TempClassic()
{
    Serial_Print("\ntemp test from LCD\n");
    _lcd_i2c_ui_active_row_index = 0;
}

void UI_Periferal_RTC_Time()
{
    if (_lcd_i2c_ui_active_row_index == 1 && _lcd_i2c_ui_prev_active_row_index == 0)
    {
        periferal_rtc.datetime = DSRTC_DateTime();
    }
    uint8_t string[10];
    sprintf(string, "%02u:%02u:%02u", periferal_rtc.datetime->hours, periferal_rtc.datetime->minutes, periferal_rtc.datetime->seconds);
    LCD_I2C_Print(string);
}

void UI_Periferal_RTC_Time_Action()
{
    if (_lcd_i2c_ui_active_row_index > 3)
    {
        DSRTC_SetDateTime(periferal_rtc.datetime->seconds,
                          periferal_rtc.datetime->minutes,
                          periferal_rtc.datetime->hours,
                          periferal_rtc.datetime->dayOfWeek,
                          periferal_rtc.datetime->dayOfMonth,
                          periferal_rtc.datetime->month,
                          periferal_rtc.datetime->year);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Periferal_RTC_Time_ActionLeft()
{
    switch (_lcd_i2c_ui_active_row_index)
    {
    case 1:
        if (periferal_rtc.datetime->hours == 0)
        {
            periferal_rtc.datetime->hours = 23;
        }
        else
        {
            periferal_rtc.datetime->hours -= 1;
        }
        break;
    case 2:
        if (periferal_rtc.datetime->minutes == 0)
        {
            periferal_rtc.datetime->minutes = 59;
        }
        else
        {
            periferal_rtc.datetime->minutes -= 1;
        }
        break;
    case 3:
        if (periferal_rtc.datetime->seconds == 0)
        {
            periferal_rtc.datetime->seconds = 59;
        }
        else
        {
            periferal_rtc.datetime->seconds -= 1;
        }
        break;

    default:
        break;
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Periferal_RTC_Time_ActionRight()
{
    switch (_lcd_i2c_ui_active_row_index)
    {
    case 1:
        if (periferal_rtc.datetime->hours == 23)
        {
            periferal_rtc.datetime->hours = 0;
        }
        else
        {
            periferal_rtc.datetime->hours += 1;
        }
        break;
    case 2:
        if (periferal_rtc.datetime->minutes == 59)
        {
            periferal_rtc.datetime->minutes = 0;
        }
        else
        {
            periferal_rtc.datetime->minutes += 1;
        }
        break;
    case 3:
        if (periferal_rtc.datetime->seconds == 59)
        {
            periferal_rtc.datetime->seconds = 00;
        }
        else
        {
            periferal_rtc.datetime->seconds += 1;
        }
        break;

    default:
        break;
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void UI_Periferal_RTC_Date()
{
    if (_lcd_i2c_ui_active_row_index == 1 && _lcd_i2c_ui_prev_active_row_index == 0)
    {
        periferal_rtc.datetime = DSRTC_DateTime();
    }
    uint8_t string[10];
    sprintf(string, "%02u/%02u/%02u", periferal_rtc.datetime->dayOfMonth, periferal_rtc.datetime->month, periferal_rtc.datetime->year);
    LCD_I2C_Print(string);
}

void UI_Periferal_RTC_Date_Action()
{
    if (_lcd_i2c_ui_active_row_index > 3)
    {
        DSRTC_SetDateTime(periferal_rtc.datetime->seconds,
                          periferal_rtc.datetime->minutes,
                          periferal_rtc.datetime->hours,
                          periferal_rtc.datetime->dayOfWeek,
                          periferal_rtc.datetime->dayOfMonth,
                          periferal_rtc.datetime->month,
                          periferal_rtc.datetime->year);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}

void UI_Periferal_RTC_Date_ActionLeft()
{
    switch (_lcd_i2c_ui_active_row_index)
    {
    case 1:
        if (periferal_rtc.datetime->dayOfMonth == 1)
        {
            periferal_rtc.datetime->dayOfMonth = 31;
        }
        else
        {
            periferal_rtc.datetime->dayOfMonth -= 1;
        }
        break;
    case 2:
        if (periferal_rtc.datetime->month == 1)
        {
            periferal_rtc.datetime->month = 12;
        }
        else
        {
            periferal_rtc.datetime->month -= 1;
        }
        break;
    case 3:
        if (periferal_rtc.datetime->year == 0)
        {
            periferal_rtc.datetime->year = 99;
        }
        else
        {
            periferal_rtc.datetime->year -= 1;
        }
        break;

    default:
        break;
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Periferal_RTC_Date_ActionRight()
{
    switch (_lcd_i2c_ui_active_row_index)
    {
    case 1:
        if (periferal_rtc.datetime->dayOfMonth == 31)
        {
            periferal_rtc.datetime->dayOfMonth = 1;
        }
        else
        {
            periferal_rtc.datetime->dayOfMonth += 1;
        }
        break;
    case 2:
        if (periferal_rtc.datetime->month == 12)
        {
            periferal_rtc.datetime->month = 1;
        }
        else
        {
            periferal_rtc.datetime->month += 1;
        }
        break;
    case 3:
        if (periferal_rtc.datetime->year == 99)
        {
            periferal_rtc.datetime->year = 0;
        }
        else
        {
            periferal_rtc.datetime->year += 1;
        }
        break;

    default:
        break;
    }

    _lcd_i2c_ui_prev_active_row_index = _lcd_i2c_ui_active_row_index;
    LCD_I2C_UI_CurrentPage()->content[1].isFresh = FALSE;
}

void UI_Periferal_Settings_Light()
{
    uint8_t string[10];
    sprintf(string, "%02u s", lcd_ui_backlight_time);
    LCD_I2C_Print(string);
}

void UI_Periferal_Settings_Light_Action()
{
    if (_lcd_i2c_ui_active_row_index > 1)
    {
        eeprom_write(0x0A, lcd_ui_backlight_time);
        _lcd_i2c_ui_active_row_index = 0;
        LCD_I2C_SetCursor(0, 0);
    }
}
void UI_Periferal_Settings_Light_ActionLeft()
{
    if (lcd_ui_backlight_time > 1)
    {
        lcd_ui_backlight_time--;
    }
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}
void UI_Periferal_Settings_Light_ActionRight()
{
    if (lcd_ui_backlight_time < 99)
    {
        lcd_ui_backlight_time++;
    }
    LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
}

void handleClick()
{
    time = milis();

    if (!lcd_ui_backlight_on)
    {
        lcd_ui_backlight_on = TRUE;
        LCD_I2C_Backlight();
    }
    LCD_I2C_UI_HandleClickAction();
}

void handleLeft()
{
    time = milis();

    if (!lcd_ui_backlight_on)
    {
        lcd_ui_backlight_on = TRUE;
        LCD_I2C_Backlight();
    }
    LCD_I2C_UI_HandleLeftAction();
}

void handleRight()
{
    time = milis();
    if (!lcd_ui_backlight_on)
    {
        lcd_ui_backlight_on = TRUE;
        LCD_I2C_Backlight();
    }
    LCD_I2C_UI_HandleRightAction();
}

void setup(void)
{

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(GPIOB, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);

    Serial_Begin(9600);
    delay_ms(1000);
    LCD_I2C_Init(0x26, 16, 2);
    DSRTC_Init(0x68);
    Encoder_Init(&ENCODER_CONFIG);
    eeprom_init();
    LCD_I2C_UI_Init(&LCD_UI_CONFIG);
    delay_ms(10);
    LCD_I2C_UI_Redirect("home");
    TIM1_Cmd(ENABLE);
    milis_init();
    // DSRTC_SetDateTime(30, 14, 16, 4, 13, 4, 23);

    bool cursor_on = eeprom_read(0x00) == 0 ? FALSE : TRUE;
    periferal_leds.value = eeprom_read(0x01);
    periferal_leds.mode = eeprom_read(0x02);
    periferal_leds.period = eeprom_read32(0x03);
    lcd_ui_backlight_time = eeprom_read(0x0A);

    GPIO_Write(periferal_leds.port, periferal_leds.value);

    if (cursor_on)
    {
        LCD_I2C_Cursor();
    }
    else
    {
        LCD_I2C_NoCursor();
    }
}

void loop(void)
{
    LCD_I2C_UI_Render();

    if (milis() - periferal_leds._time > periferal_leds.period && periferal_leds.isActive)
    {
        if (periferal_leds.mode == BLINK)
        {
            periferal_leds.value = ~periferal_leds.value & eeprom_read(0x01);
            GPIO_Write(periferal_leds.port, periferal_leds.value);
        }

        if (periferal_leds.mode == INVERT)
        {
            periferal_leds.value = ~periferal_leds.value;
            GPIO_Write(periferal_leds.port, periferal_leds.value);
        }

        if (periferal_leds.mode == STATIC)
        {
            periferal_leds.value = eeprom_read(0x01);

            GPIO_Write(periferal_leds.port, periferal_leds.value);
        }

        if (LCD_I2C_UI_CurrentPage()->name == "periferal_leds")
        {
            LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
        }

        periferal_leds._time = milis();
    }

    if ((milis() - time > (lcd_ui_backlight_time * 1000)) && lcd_ui_backlight_on)
    {
        lcd_ui_backlight_on = FALSE;
        LCD_I2C_NoBacklight();

        time = milis();
    }
}