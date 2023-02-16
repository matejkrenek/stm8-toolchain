
#define DHT11_port GPIOA
#define DHT11_pin GPIO_PIN_3

#define DHT11_INPUT()                                            \
    do                                                           \
    {                                                            \
        GPIO_DeInit(DHT11_port);                                 \
        GPIO_Init(DHT11_port, DHT11_pin, GPIO_MODE_IN_FL_NO_IT); \
    } while (0)
#define DHT11_OUTPUT()                                                \
    do                                                                \
    {                                                                 \
        GPIO_DeInit(DHT11_port);                                      \
        GPIO_Init(DHT11_port, DHT11_pin, GPIO_MODE_OUT_PP_HIGH_FAST); \
    } while (0)

#define DHT11_IN() GPIO_ReadInputPin(DHT11_port, DHT11_pin)

#define DHT11_OUT_LOW() GPIO_WriteLow(DHT11_port, DHT11_pin)
#define DHT11_OUT_HIGH() GPIO_WriteHigh(DHT11_port, DHT11_pin)

extern unsigned char values[5];

void DHT11_init(void);
unsigned char get_byte(void);
unsigned char get_data(void);
