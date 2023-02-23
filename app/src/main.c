#include "stm8s.h"
#include "delay.h"
#include "LCD_I2C.h"
#include "LCD_I2C_UI.h"
#include "Serial.h"
#include "encoder.h"
#include "milis.h"

#define len(arr) sizeof(arr) / sizeof(arr[0])
#define LED_PORT GPIOD
#define LED_PIN GPIO_PIN_4

void handleLeft();
void handleRight();
void handleClick();

uint32_t time = 0;
bool display_backlight = TRUE;
Encoder_Config ENCODER_CONFIG = {
    .clk = GPIO_PIN_5,
    .ds = GPIO_PIN_4,
    .btn = GPIO_PIN_3,
    .onLeft = &handleLeft,
    .onRight = &handleRight,
    .onClick = &handleClick,
};
LCD_I2C_UI_Page LCD_UI_PAGES[] = {
    {
        .name = "HOME",
        .content = {
            {
                .text = "home",
            },
        },
    },
    {
        .name = "ABOUT",
        .content = {
            {
                .text = "about",
            },
        },
    },
};

void handleLeft()
{
    if (!display_backlight)
    {
        display_backlight = TRUE;
        LCD_I2C_Backlight();
        time = milis();
    }
}

void handleRight()
{
    if (!display_backlight)
    {
        display_backlight = TRUE;
        LCD_I2C_Backlight();
        time = milis();
    }
}

void handleClick()
{
    if (!display_backlight)
    {
        display_backlight = TRUE;
        LCD_I2C_Backlight();
        time = milis();
    }
    LCD_I2C_UI_Redirect("ABOUT");
}

int main(void)
{

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    Serial_Begin(9600);
    LCD_I2C_Init(0x26, 16, 2);
    LCD_I2C_UI_Init(LCD_UI_PAGES);
    Encoder_Init(&ENCODER_CONFIG);
    milis_init();

    while (1)
    {
        LCD_I2C_UI_Render();

        if (milis() - time > 15000 && display_backlight)
        {
            display_backlight = FALSE;
            LCD_I2C_NoBacklight();
            time = milis();
        }
    }
}