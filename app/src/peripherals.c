#include "peripherals.h"

Peripheral_LED_Array peripheral_leds = {
    .value = 0b11111111,
    .mode = 0,
    .period = 700,
    ._time = 0,
    .isActive = TRUE,
    .port = GPIOB,
};

Peripheral_RTC peripheral_rtc = {
    ._time = 0,
    .isActive = TRUE,
};

Peripheral_Buzzer peripheral_buzzer = {
    .frequnecy = 100,
    .volume = 100,
    ._time = 0,
    .isActive = TRUE,
};

Peripheral_RGB_LED peripheral_rgb_led = {
    .red = 255,
    .green = 255,
    .blue = 255,
    .alpha = 100,
    ._time = 0,
    .isActive = TRUE,
};

Peripheral_LCD peripheral_lcd = {
    .isFirstRender = TRUE,
    .isBacklightOn = TRUE,
    .backlightTimeOff = 5,
    ._time = 0,
    .isActive = TRUE,
};

Peripherals peripheral_home_page = RTC;
