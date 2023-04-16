#ifndef __MAIN_H
#define __MAIN_H

#include "stm8s.h"

#define len(arr) sizeof(arr) / sizeof(arr[0])
#define LED_PORT GPIOD
#define LED_PIN GPIO_PIN_4

void setup(void);
void loop(void);

int main(void)
{
    setup();

    while (1)
    {
        loop();
    }
}

#endif /* __MAIN_H */