#ifndef __Serial_H
#define __Serial_H

void Serial_Begin(uint32_t BaudRate);
void Serial_Print_String(char message[]);
void Serial_Print_Char(char message);
void Serial_Print_Int(int message);
void Serial_Newline(void);
bool Serial_Available(void);
char Serial_Read_Char(void);

#endif