#include "stm8s.h"
#include "delay.h"
#include "Serial.h"
#include "LCD_I2C.h"
#include "encoder.h"

#define LED_PORT GPIOD
#define LED_PIN GPIO_PIN_4

void handleLeft(uint8_t *message)
{
    LCD_I2C_Clear();
    LCD_I2C_Print("left");
}

void handleRight(uint8_t *message)
{
    LCD_I2C_Clear();
    LCD_I2C_Print("right");
}

void handleClick(uint8_t *message)
{
    LCD_I2C_Clear();
    LCD_I2C_Print(message);
}

int main(void)
{
    Encoder_Config encoder_config = {
        .clk = GPIO_PIN_5,
        .ds = GPIO_PIN_4,
        .btn = GPIO_PIN_3,
    };
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    Serial_Begin(9600);
    LCD_I2C_Init(0x26, 16, 2);
    Encoder_Init(&encoder_config);

    while (1)
    {
        GPIO_WriteReverse(LED_PORT, LED_PIN);
        delay_ms(1000);
    }
}
