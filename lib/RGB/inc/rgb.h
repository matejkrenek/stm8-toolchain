#ifndef _RGB_H_
#define _RGB_H_

#include "stm8s.h"

void rgb_init(void);
void rgb_set(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha);

#endif