#include "stm8s.h"
#include "delay.h"

void delay_cycles(uint32_t value)
{
    for (uint32_t i = 0; i < value; i++)
    {
        nop();
    }
}

void delay_ms(uint32_t ms)
{
    uint32_t clock_freq = CLK_GetClockFreq();

    for (uint32_t i = 0; i < ((clock_freq / 18 / 1000UL) * ms); i++)
    {
        nop();
    }
}

void delay_us(uint32_t us)
{
    uint32_t clock_freq = CLK_GetClockFreq();

    for (uint32_t i = 0; i < ((clock_freq / 18 / 1000UL) * (us / 1000)); i++)
    {
        nop();
    }
}