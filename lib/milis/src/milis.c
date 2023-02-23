#include "stm8s.h"
#include "milis.h"

#if defined(STM8S003) || defined(STM8S103) || defined(STM8S105) || defined(STM8S208)

#if MILIS_32BIT_TIME == 1
volatile uint32_t miliseconds = 0; // global variable storing milis value
#else
volatile uint16_t miliseconds = 0; // global variable storing milis value
#endif

// return value of milisecond timestamp ("atomic" read)
MILIS_PROTOTYPE
{
#if MILIS_32BIT_TIME == 1
    uint32_t tmp;
#else
    uint16_t tmp;
#endif
    TIM4_ITConfig(TIM4_IT_UPDATE, DISABLE);
    tmp = miliseconds;
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
    return tmp;
}

INTERRUPT_HANDLER(TIM4_UPD_OVF_IRQHandler, 23)
{
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    miliseconds++;
}

// init TIM4 as source for milis interrupt (low priority)
void milis_init(void)
{
    TIM4_TimeBaseInit(PRESCALER, PERIOD); // (16MHz / 128) / 125 = 1000Hz
    TIM4_ClearFlag(TIM4_FLAG_UPDATE);
    TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
    ITC_SetSoftwarePriority(ITC_IRQ_TIM4_OVF, ITC_PRIORITYLEVEL_1); // nízká priorita pøerušení
    enableInterrupts();
    TIM4_Cmd(ENABLE);
}

#else
#warning "millis not defined for this platform !"
#endif