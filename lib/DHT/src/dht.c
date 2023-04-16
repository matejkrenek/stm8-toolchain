#include "stm8s.h"
#include "milis.h"
#include "Serial.h"
#include "dht.h"

DHT_Error _dht_status = OK;
DHT_State _dht_state = SLEEP;
uint64_t _dht_data;
uint16_t _dht_last_counter;
uint32_t _dht_last_time = 0;
GPIO_Pin_TypeDef _dht_pin;

INTERRUPT_HANDLER(EXTI_PORTD_IRQHandler, 6)
{
    uint16_t pulse_length = TIM2_GetCounter() - _dht_last_counter;
    _dht_last_counter = TIM2_GetCounter();

    if (GPIO_ReadInputPin(GPIOD, GPIO_PIN_2) == RESET)
    {
        if (pulse_length > 15 && pulse_length < 30)
        {
            _dht_data = _dht_data << 1;
        }
        if (pulse_length > 40 && pulse_length < 74)
        {
            _dht_data <<= 1;
            _dht_data = _dht_data | 1;
        }
    }
}

void DHT_Init(GPIO_Pin_TypeDef pin)
{
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_OD_HIZ_SLOW);
    EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOD, EXTI_SENSITIVITY_RISE_FALL);
    ITC_SetSoftwarePriority(ITC_IRQ_PORTD, ITC_PRIORITYLEVEL_1);
    TIM2_TimeBaseInit(TIM2_PRESCALER_16, 0xFFFF);
    TIM2_Cmd(ENABLE);
    enableInterrupts();
}

void DHT_Read()
{
    _dht_last_time = 0;
    _dht_state = SLEEP;
    GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_OD_HIZ_SLOW);

    while (1)
    {
        switch (_dht_state)
        {
        case SLEEP:
            _dht_last_time = milis();
            _dht_state = WAKE;
            break;
        case WAKE:
            if (milis() - _dht_last_time < 19)
            {
                GPIO_WriteLow(GPIOD, GPIO_PIN_2);
            }
            else
            {
                _dht_last_time = milis();
                TIM2_SetCounter(0);
                _dht_last_counter = 0;
                _dht_data = 0LL;
                GPIO_WriteHigh(GPIOD, GPIO_PIN_2);
                GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_IN_PU_IT);
                _dht_state = READING;
            }
            break;
        case READING:

            if (milis() - _dht_last_time > 6)
            {
                _dht_last_time = milis();
                Serial_Print_String("\ndata: 0b ");
                uint64_t m = 1LL << 39;
                uint8_t i = 0;
                while (m)
                {
                    if (_dht_data & m)
                    {
                        Serial_Print_String("1");
                    }
                    else
                    {
                        Serial_Print_String("0");
                    }
                    if (++i % 8 == 0)
                        Serial_Print_String(" ");
                    m >>= 1;
                }
                uint8_t m2 = 11111111 << 7;
                i = 0;
                uint8_t temperatureL = _dht_data >> 8;
                while (m2)
                {
                    if (temperatureL & m2)
                    {
                        Serial_Print_String("1");
                    }
                    else
                    {
                        Serial_Print_String("0");
                    }
                    if (++i % 8 == 0)
                        Serial_Print_String(" ");
                    m2 >>= 1;
                }
                GPIO_Init(GPIOD, GPIO_PIN_2, GPIO_MODE_OUT_OD_HIZ_SLOW);
                _dht_state = SLEEP;
            }
            break;

        default:
            break;
        }
    }
}