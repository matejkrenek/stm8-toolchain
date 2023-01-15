#include "stm8s.h"
#include "delay.h"
#include "Serial.h"
#include "LCD_I2C.h"

#define LED_PORT GPIOD
#define LED_PIN GPIO_PIN_3

int main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    Serial_Begin(9600);
    LCD_I2C_Init(0x26, 16, 2);

    while (1)
    {
        GPIO_WriteReverse(LED_PORT, LED_PIN);
        LCD_I2C_SetCursor(0, 0);
        LCD_I2C_Print("LED: TOGGLED\n");
        delay_ms(1000);
    }
}