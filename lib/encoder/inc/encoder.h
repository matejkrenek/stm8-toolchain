#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm8s.h"

/**
 * @brief  Rotary Encoder configuaration
 */
typedef struct
{
    GPIO_Pin_TypeDef clk;
    GPIO_Pin_TypeDef ds;
    GPIO_Pin_TypeDef btn;
    BitStatus curr_state;
    BitStatus prev_state;
    BitStatus btn_state;
    void (*onLeft)();
    void (*onRight)();
    void (*onClick)();
} Encoder_Config;

void Encoder_Init(Encoder_Config *config);

#endif