#include "tone.h"
#include "delay.h"

uint8_t _tone_volume = 100;

void tone_init()
{
    TIM3_TimeBaseInit(TIM2_PRESCALER_4, 65535);
    TIM3_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
    TIM3_Cmd(ENABLE);
    TIM3_OC1PreloadConfig(ENABLE);
    tone_off();
}

void tone_off()
{
    TIM3_SetCompare1(0);
}

void tone_volume(uint8_t volume)
{
    _tone_volume = volume;
}

void tone_on(uint16_t freq)
{
    uint16_t counter = (CLK_GetClockFreq() / (freq * 4));

    TIM3_TimeBaseInit(TIM2_PRESCALER_4, counter);
    TIM3_SetCompare1((((counter + 1) / 100) * _tone_volume));
}

void tone_success(uint16_t freq)
{
    tone_on(freq);
    delay_ms(50);
    tone_on(freq + 100);
    delay_ms(50);
    tone_on(freq + 200);
    delay_ms(50);
    tone_on(freq + 300);
    delay_ms(50);
    tone_on(freq + 400);
    delay_ms(50);
    tone_on(freq + 500);
    delay_ms(50);
    tone_off();
}

void tone_blink(uint16_t freq)
{
    tone_on(freq);
    delay_ms(10);
    tone_off();
}