#ifndef __PERIPHERALS_H
#define __PERIPHERALS_H

#include "stm8s.h"
#include "dsrtc.h"

typedef enum
{
    LED_ARRAY,
    RGB_LED,
    RTC,
    PERIPHERAL_LENGTH
} Peripherals;

typedef enum
{
    BLINK,
    STATIC,
    INVERT,
    LED_ARRAY_MODE_LENGTH
} Peripheral_LED_Array_Mode;

typedef struct
{
    uint8_t value;
    Peripheral_LED_Array_Mode mode;
    uint32_t period;
    uint32_t _time;
    bool isActive;
    GPIO_TypeDef *port;
} Peripheral_LED_Array;

typedef struct
{
    DateTime *datetime;
    uint32_t _time;
    bool isActive;
} Peripheral_RTC;

typedef struct
{
    uint16_t frequnecy;
    uint8_t volume;
    uint32_t _time;
    bool isActive;
} Peripheral_Buzzer;

typedef struct
{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    uint8_t alpha;
    uint32_t _time;
    bool isActive;
} Peripheral_RGB_LED;

typedef struct
{
    bool isFirstRender;
    bool isBacklightOn;
    uint8_t backlightTimeOff;
    uint32_t _time;
    bool isActive;
} Peripheral_LCD;

extern Peripheral_LED_Array peripheral_leds;
extern Peripheral_RTC peripheral_rtc;
extern Peripheral_Buzzer peripheral_buzzer;
extern Peripheral_RGB_LED peripheral_rgb_led;
extern Peripheral_LCD peripheral_lcd;
extern Peripherals peripheral_home_page;

#endif /* __PERIPHERALS_H */