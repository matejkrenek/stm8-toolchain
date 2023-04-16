#ifndef __TONE_H
#define __TONE_H

#include "stm8s.h"

void tone_init();
void tone_off();
void tone_on(uint16_t freq);
void tone_volume(uint8_t volume);
void tone_success(uint16_t freq);
void tone_blink(uint16_t freq);

extern uint8_t _tone_volume;

#endif