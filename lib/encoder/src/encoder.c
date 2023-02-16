
#include "encoder.h"
#include "delay.h"
#include "Serial.h"

static Encoder_Config *encoder_config;
BitStatus PREV_STATE;
BitStatus CURR_STATE;
BitStatus BUTTON_STATE;

INTERRUPT_HANDLER(EXTI_PORTC_IRQHandler, 5)
{
    CURR_STATE = GPIO_ReadInputPin(GPIOC, encoder_config->clk);
    BUTTON_STATE = GPIO_ReadInputPin(GPIOC, encoder_config->btn);

    if (CURR_STATE != PREV_STATE && !CURR_STATE)
    {
        if (GPIO_ReadInputPin(GPIOC, encoder_config->ds) != CURR_STATE)
        {
            Serial_Print_String("left\n");
        }
        else
        {
            Serial_Print_String("right\n");
        }
    }
    else if (!BUTTON_STATE)
    {
        Serial_Print_String("pressed\n");
    }

    PREV_STATE = CURR_STATE;

    delay_ms(1);
}

void Encoder_Init(Encoder_Config *config)
{
    encoder_config = config;

    GPIO_Init(GPIOC, encoder_config->clk, GPIO_MODE_IN_PU_IT);
    GPIO_Init(GPIOC, encoder_config->ds, GPIO_MODE_IN_PU_IT);
    GPIO_Init(GPIOC, encoder_config->btn, GPIO_MODE_IN_PU_IT);
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC, EXTI_SENSITIVITY_RISE_FALL);
    ITC_SetSoftwarePriority(ITC_IRQ_PORTC, ITC_PRIORITYLEVEL_1);
    enableInterrupts();

    PREV_STATE = GPIO_ReadInputPin(GPIOC, encoder_config->clk);
}