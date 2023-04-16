#include "main.h"
#include "delay.h"
#include "LCD_I2C.h"
#include "LCD_I2C_UI.h"
#include "Serial.h"
#include "encoder.h"
#include "milis.h"
#include "dsrtc.h"
#include "ui.h"
#include "string.h"
#include "eeprom.h"
#include "tone.h"
#include "rgb.h"
#include "peripherals.h"

Encoder_Config ENCODER_CONFIG = {
    .clk = GPIO_PIN_7,
    .ds = GPIO_PIN_6,
    .btn = GPIO_PIN_5,
    .onLeft = handleLeft,
    .onRight = handleRight,
    .onClick = handleClick,
};

void handleClick()
{
    peripheral_lcd._time = milis();
    tone_blink(peripheral_buzzer.frequnecy);

    if (!peripheral_lcd.isBacklightOn)
    {
        peripheral_lcd.isBacklightOn = TRUE;
        LCD_I2C_Backlight();
    }
    LCD_I2C_UI_HandleClickAction();
}

void handleLeft()
{
    peripheral_lcd._time = milis();

    tone_blink(peripheral_buzzer.frequnecy);

    if (!peripheral_lcd.isBacklightOn)
    {
        peripheral_lcd.isBacklightOn = TRUE;
        LCD_I2C_Backlight();
    }
    LCD_I2C_UI_HandleLeftAction();
}

void handleRight()
{
    peripheral_lcd._time = milis();
    tone_blink(peripheral_buzzer.frequnecy);

    if (!peripheral_lcd.isBacklightOn)
    {
        peripheral_lcd.isBacklightOn = TRUE;
        LCD_I2C_Backlight();
    }
    LCD_I2C_UI_HandleRightAction();
}

void setup(void)
{

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(peripheral_leds.port, GPIO_PIN_ALL, GPIO_MODE_OUT_PP_LOW_SLOW);
    LCD_I2C_Init(0x26, 16, 2);
    DSRTC_Init(0x68);
    Encoder_Init(&ENCODER_CONFIG);
    eeprom_init();
    LCD_I2C_UI_Init(&LCD_UI_CONFIG);
    milis_init();
    tone_init();
    rgb_init();
    memory_variables_init();
    delay_ms(1000);
    LCD_I2C_UI_Redirect("home");
}

void loop(void)
{
    LCD_I2C_UI_Render();

    if (milis() - peripheral_leds._time > peripheral_leds.period && peripheral_leds.isActive)
    {
        if (peripheral_leds.mode == BLINK)
        {
            peripheral_leds.value = ~peripheral_leds.value & eeprom_read(0x01);
            GPIO_Write(peripheral_leds.port, peripheral_leds.value);
        }

        if (peripheral_leds.mode == INVERT)
        {
            peripheral_leds.value = ~peripheral_leds.value;
            GPIO_Write(peripheral_leds.port, peripheral_leds.value);
        }

        if (peripheral_leds.mode == STATIC)
        {
            peripheral_leds.value = eeprom_read(0x01);

            GPIO_Write(peripheral_leds.port, peripheral_leds.value);
        }

        if (LCD_I2C_UI_CurrentPage()->name == "peripheral_leds" || LCD_I2C_UI_CurrentPage()->name == "home" && peripheral_home_page == LED_ARRAY)
        {
            LCD_I2C_UI_CurrentPage()->content[0].isFresh = FALSE;
        }

        peripheral_leds._time = milis();
    }

    if ((milis() - peripheral_lcd._time > (peripheral_lcd.backlightTimeOff * 1000)) && peripheral_lcd.isBacklightOn)
    {
        peripheral_lcd.isBacklightOn = FALSE;
        LCD_I2C_NoBacklight();

        peripheral_lcd._time = milis();
    }
}

void memory_variables_init(void)
{
    peripheral_leds.value = eeprom_read(0x01);
    peripheral_leds.mode = eeprom_read(0x02);
    peripheral_leds.period = eeprom_read32(0x03);
    peripheral_lcd.backlightTimeOff = eeprom_read(0x0A);
    peripheral_buzzer.volume = eeprom_read(0x0B);
    peripheral_buzzer.frequnecy = eeprom_read16(0x0C);
    peripheral_rgb_led.red = eeprom_read(0x10);
    peripheral_rgb_led.green = eeprom_read(0x20);
    peripheral_rgb_led.blue = eeprom_read(0x30);
    peripheral_rgb_led.alpha = eeprom_read(0x40);
    peripheral_home_page = eeprom_read(0xF0);

    tone_volume(peripheral_buzzer.volume);
    rgb_set(peripheral_rgb_led.red, peripheral_rgb_led.green, peripheral_rgb_led.blue, peripheral_rgb_led.alpha);

    GPIO_Write(peripheral_leds.port, peripheral_leds.value);

    if (eeprom_read(0x00) == 0)
    {
        LCD_I2C_NoCursor();
    }
    else
    {
        LCD_I2C_Cursor();
    }
}