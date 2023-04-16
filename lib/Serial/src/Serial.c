#include "stm8s.h"
#include "delay.h"
#include "Serial.h"
#include <stdio.h>
#include <stdarg.h>

/**
 * @brief  Configure Serial monitor.
 * @param  BaudRate : Speed of serial monitor.
 * @retval None
 */
void Serial_Begin(uint32_t BaudRate)
{
    CLK_PeripheralClockConfig(CLK_PERIPHERAL_UART2, ENABLE);
    UART2_Init(BaudRate, UART2_WORDLENGTH_8D, UART2_STOPBITS_1, UART2_PARITY_NO, UART2_SYNCMODE_CLOCK_DISABLE, UART2_MODE_TXRX_ENABLE);
    UART2_Cmd(ENABLE);
    delay_ms(50);
}

void Serial_Print(const char *format, ...)
{
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
}
/**
 * @brief  Print string to serial monitor.
 * @param  message : message to write.
 * @retval None
 */
void Serial_Print_String(char message[])
{
    char i = 0;

    while (message[i] != 0x00)
    {
        UART2_SendData8(message[i]);

        while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET)
            ;
        i++;
    }
}

void Serial_Print_Char(char value)
{
    UART2_SendData8(value);
    while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET)
        ;
}

void Serial_Print_Int(int number)
{
    char count = 0;
    char digit[5] = "";
    while (number != 0)
    {
        digit[count] = number % 10;
        count++;
        number = number / 10;
    }
    {
        UART2_SendData8(digit[count - 1] + 0x30);
        while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET)
            ;
        count--;
    }
}

void Serial_Newline()
{
    UART2_SendData8(0x0a);
    while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET)
        ;
}

bool Serial_Available()
{
    if (UART2_GetFlagStatus(UART2_FLAG_RXNE) == TRUE)
        return TRUE;
    else
        return FALSE;
}

char Serial_Read_Char()
{
    while (UART2_GetFlagStatus(UART2_FLAG_RXNE) == RESET)
        ;
    UART2_ClearFlag(UART2_FLAG_RXNE);

    return UART2_ReceiveData8();
}

void Serial_Tab_Table(uint8_t *name, uint8_t *headers)
{
    Serial_Print("cmd:tab=\"%s\";type=\"table\"", name);
    delay_ms(100);
    Serial_Print("%s", headers);
}

void Serial_Tab_Chart(uint8_t *name)
{
    Serial_Print("cmd:tab=\"%s\";type=\"chart\"", name);
    delay_ms(1);
}

void Serial_Tab_End()
{
    Serial_Print("cmd:end");
    delay_ms(1);
}

int putchar(int c)
{
    UART2_SendData8(c);

    while (UART2_GetFlagStatus(UART2_FLAG_TXE) == RESET)
        ;

    return c;
}
