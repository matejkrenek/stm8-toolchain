#ifndef __ENCODER_H
#define __ENCODER_H

#include "stm8s.h"

typedef struct
{
    GPIO_Pin_TypeDef clk;
    GPIO_Pin_TypeDef ds;
    GPIO_Pin_TypeDef btn;
    uint8_t counter;
    bool changed;
    BitStatus curr_state;
    BitStatus prev_state;
} Encoder_Config;

void Encoder_Init(Encoder_Config *config);

#endif