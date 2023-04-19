#include "main.h"
#include "milis.h"

uint32_t time = 0;

void setup(void)
{

    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1);
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
}

void loop(void)
{

    if (milis() - time > 1000)
    {
        GPIO_WriteReverse(LED_PORT, LED_PIN);
        time = milis();
    }
}