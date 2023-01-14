#include "stm8s.h"

#define LED_PORT GPIOD
#define LED_PIN GPIO_PIN_3

int main(void)
{
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);

    while (1)
    {
        GPIO_WriteReverse(LED_PORT, LED_PIN);
    }
}