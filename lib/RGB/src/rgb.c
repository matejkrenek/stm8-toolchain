#include "rgb.h"

void rgb_init(void)
{
    TIM2_TimeBaseInit(TIM2_PRESCALER_4, 65535);
    TIM2_OC1Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
    TIM2_OC2Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
    TIM2_OC3Init(TIM2_OCMODE_PWM2, TIM2_OUTPUTSTATE_ENABLE, 0, TIM2_OCPOLARITY_HIGH);
    TIM2_Cmd(ENABLE);
    TIM2_OC1PreloadConfig(ENABLE);
    TIM2_OC2PreloadConfig(ENABLE);
    TIM2_OC3PreloadConfig(ENABLE);
}

void rgb_set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
{
    uint16_t base = (((uint16_t)65535 / 255) / 100) * alpha;

    uint16_t red_val = base * red;
    uint16_t green_val = base * green;
    uint16_t blue_val = base * blue;

    TIM2_SetCompare1(red_val);
    TIM2_SetCompare2(green_val);
    TIM2_SetCompare3(blue_val);
}