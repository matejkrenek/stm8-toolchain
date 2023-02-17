#include "stm8s.h"
#include "delay.h"
#include "LCD_I2C.h"

#define LED_PORT GPIOD
#define LED_PIN GPIO_PIN_3

#define DIN_PORT GPIOA
#define DIN_PIN GPIO_PIN_1

#define CS_PORT GPIOA
#define CS_PIN GPIO_PIN_2

#define CLK_PORT GPIOA
#define CLK_PIN GPIO_PIN_3

void send_max(uint8_t command, uint8_t value) {
    uint8_t mask;

    GPIO_WriteLow(CS_PORT, CS_PIN);

    mask = 0b1000000;

    while(mask) {
        if(command & mask) {
            GPIO_WriteHigh(DIN_PORT, DIN_PIN);
        } else {
            GPIO_WriteHigh(DIN_PORT, DIN_PIN);
        }

        GPIO_WriteHigh(CLK_PORT, CLK_PIN);
        mask = mask >> 1;
        GPIO_WriteLow(CLK_PORT, CLK_PIN);
    }

    mask = 0b1000000;

    while(mask) {
        if(value & mask) {
            GPIO_WriteHigh(DIN_PORT, DIN_PIN);
        } else {
            GPIO_WriteHigh(DIN_PORT, DIN_PIN);
        }

        GPIO_WriteHigh(CLK_PORT, CLK_PIN);
        mask = mask >> 1;
        GPIO_WriteLow(CLK_PORT, CLK_PIN);
    }

    GPIO_WriteHigh(CS_PORT, CS_PIN);
}

void setup(void) {
    CLK_HSIPrescalerConfig(CLK_PRESCALER_HSIDIV1); // taktovani MCU na 16MHz
    GPIO_Init(LED_PORT, LED_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(DIN_PORT, DIN_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CS_PORT, CS_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
    GPIO_Init(CLK_PORT, CLK_PIN, GPIO_MODE_OUT_PP_LOW_SLOW);
}

void loop(void) {

}

int main(void)
{
    setup();

    while (1)
    {
        loop();
    }
}

