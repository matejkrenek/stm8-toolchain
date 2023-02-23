#ifndef _MILIS_H_
#define _MILIS_H_ 1

#define MILIS_32BIT_TIME 1

// configure PRESCALER and PERIOD according to your clock, to setup 1ms time base
#if F_CPU == 16000000
// varianta pro 16MHz
#define PRESCALER TIM4_PRESCALER_128
#define PERIOD (125 - 1)

#elif F_CPU == 2000000
// varianta pro 2MHz
#define _PRESCALER TIM4_PRESCALER_16
#define _PERIOD (125 - 1)

#else
#warning "milis timer parameters not defined for this clock !"

#endif

#if MILIS_32BIT_TIME != 0
#define MILIS_PROTOTYPE uint32_t milis(void)
#else
#define MILIS_PROTOTYPE uint16_t milis(void)
#endif

void milis_init(void);
MILIS_PROTOTYPE;

#endif