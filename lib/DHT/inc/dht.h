#ifndef __DHT_H
#define __DHT_H

typedef enum
{
    OK,
    CHECKSUM_ERROR
} DHT_Error;

typedef enum
{
    SLEEP,
    WAKE,
    READING
} DHT_State;

extern DHT_Error _dht_status;
extern DHT_State _dht_state;
extern uint64_t _dht_data;
extern uint16_t _dht_last_counter;
extern uint32_t _dht_last_time;
extern GPIO_Pin_TypeDef _dht_pin;

void DHT_Init(GPIO_Pin_TypeDef pin);
void DHT_Read();
DHT_Error DHT_Status();

#endif /* __DHT_H */